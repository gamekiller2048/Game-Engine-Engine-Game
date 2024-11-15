#include <graphics/render/material.hpp>
#include <graphics/render/directionalshadow.hpp>
#include <graphics/render/modelmesh.hpp>

namespace mgl
{
    BasicMaterial::BasicMaterial(const mml::color& color) :
        color(color) {}

    void BasicMaterial::use() const
    {
        shader.use();
        shader.uniformVec4(shader.getUniform("u_color"), color);
    }

    void BasicMaterial::create()
    {
        shader.create();
        shader.attachShaders(
            R"(#version 430 core

            layout(location = 0) in vec3 v_pos;

            uniform mat4 u_projection;
            uniform mat4 u_model;

            void main()
            {
                gl_Position = vec4(v_pos, 1) * u_projection;
            })",

            R"(#version 430 core

            uniform vec4 u_color;

            void main()
            {
                gl_FragColor = u_color;
            })"
        );
    }


    StandardMaterial::StandardMaterial(const Ref<Texture2D>& diffuseMap, const Ref<Texture2D>& normalMap, const Ref<Texture2D>& specularMap) :
        diffuseMap(diffuseMap), normalMap(normalMap), specularMap(specularMap) {}

    void StandardMaterial::use() const
    {
        shader.use();

        if(diffuseMap)
            shader.uniformInt(shader.getUniform("u_diffuseMap"), diffuseMap->getUnit());
        if(normalMap)
            shader.uniformInt(shader.getUniform("u_normalMap"), normalMap->getUnit());
        if(specularMap)
            shader.uniformInt(shader.getUniform("u_specularMap"), specularMap->getUnit());

        //diffuseMap->bind();
        //normalMap->bind();
        //specularMap->bind();
    }

    void StandardMaterial::usePointLight(const Ref<PointLight>& light, uint index) const
    {
        const std::string uniform = "u_pointLights[" + std::to_string(index) + ']';
        shader.uniformVec3(shader.getUniform(uniform + ".pos"), light->pos);
        shader.uniformVec4(shader.getUniform(uniform + ".color"), (mml::vec4)light->color);
        shader.uniformFloat(shader.getUniform(uniform + ".ambient"), light->ambient);
        shader.uniformFloat(shader.getUniform(uniform + ".a"), light->a);
        shader.uniformFloat(shader.getUniform(uniform + ".b"), light->b);
        shader.uniformFloat(shader.getUniform(uniform + ".specIntensity"), light->specIntensity);

        if(light->shadows) {
            const Ref<PointShadow>& shadow = std::static_pointer_cast<PointShadow>(light->shadow);

            shader.uniformInt(shader.getUniform(uniform + ".shadows"), true);
            shader.uniformFloat(shader.getUniform(uniform + ".shadow.bias"), shadow->bias);
            shader.uniformInt(shader.getUniform(uniform + ".shadow.sampleRadius"), shadow->sampleRadius);
            shader.uniformInt(shader.getUniform(uniform + ".shadow.cubemap"), shadow->cubemap.getUnit());
            shadow->cubemap.bind();
        }
    }

    void StandardMaterial::useDirectionalLight(const Ref<DirectionalLight>& light, uint index) const
    {
        const std::string uniform = "u_directionalLights[" + std::to_string(index) + ']';
        shader.uniformVec4(shader.getUniform(uniform + ".color"), (mml::vec4)light->color);
        shader.uniformVec3(shader.getUniform(uniform + ".dir"), light->dir);
        shader.uniformFloat(shader.getUniform(uniform + ".ambient"), light->ambient);
        shader.uniformFloat(shader.getUniform(uniform + ".specIntensity"), light->specIntensity);

        if(light->shadows) {
            const Ref<DirectionalShadow>& shadow = std::static_pointer_cast<DirectionalShadow>(light->shadow);

            shader.uniformMat4("u_lightSpaceTransform", light->getSpaceTransform());
            shader.uniformInt(shader.getUniform(uniform + ".shadows"), true);
            shader.uniformFloat(shader.getUniform(uniform + ".shadow.bias"), shadow->bias);
            shader.uniformInt(shader.getUniform(uniform + ".shadow.sampleRadius"), shadow->sampleRadius);
            shader.uniformInt(shader.getUniform(uniform + ".shadow.map"), shadow->map.getUnit());
            shadow->map.bind();
        }
    }

    void StandardMaterial::useCamera(const Ref<Camera>& camera)
    {
        shader.uniformMat4("u_projection", camera->matrix);
    }

    void StandardMaterial::useMeshTransform(const Ref<ModelMesh>& mesh)
    {
        shader.uniformMat4("u_model", mesh->getTransform());
    }

    void StandardMaterial::create()
    {
        shader.create();
        shader.attachShaders(
            R"(#version 430 core

            layout (location = 0) in vec3 v_pos;
            layout (location = 1) in vec2 v_texUV;
            layout (location = 2) in vec3 v_normal;

            out vec3 pos;
            out vec3 normal;
            out vec2 texUV;
            out vec4 fragPosLight;

            uniform mat4 u_projection;
            uniform mat4 u_lightSpaceTransform;
            uniform mat4 u_model;

            void main()
            {
                texUV = v_texUV;
                pos = v_pos * mat3(u_model);
                normal = mat3(inverse(u_model)) * v_normal;
                fragPosLight = vec4(pos, 1.0f) * u_lightSpaceTransform;

                gl_Position = vec4(v_pos, 1.0) * u_model * u_projection;
            })",

            R"(#version 430 core

            in vec3 pos;
            in vec2 texUV;
            in vec3 normal;
            in vec4 fragPosLight;

            #define NUM_DIRECTIONAL_LIGHTS 0
            #define NUM_POINT_LIGHTS 1
            #define NORMAL_MAP 0
            #define SPECULAR_MAP 0

            uniform sampler2D u_diffuseMap;

            #if NORMAL_MAP
                uniform sampler2D u_normalMap;
            #endif

            #if SPECULAR_MAP            
                uniform sampler2D u_specularMap;
            #endif

            uniform vec3 u_cameraPos;

            #if NUM_DIRECTIONAL_LIGHTS
                struct DirectionalShadow {
                    float bias;
                    int sampleRadius;
                    sampler2D map;
                };

                struct DirectionalLight {
                    vec3 dir;
                    vec4 color;
                    float ambient;
                    float specIntensity;
                    bool shadows;
                    DirectionalShadow shadow;
                };

                uniform DirectionalLight u_directionalLights[NUM_DIRECTIONAL_LIGHTS];

                vec4 directionalLightCalc(DirectionalLight light)
                {
                    #if NORMAL_MAP
                        vec3 norm = normalize(texture(u_normalMap, texUV).xzy * 2.0f - 1.0f);
                    #else
                        vec3 norm = normalize(normal);
	                #endif

	                float diffuse = max(dot(norm, light.dir), 0.0f);
    
	                float specular = 0.0f;
	                if(diffuse != 0.0f)
	                {
		                vec3 viewDirection = normalize(u_cameraPos - pos);
		                vec3 halfwayVec = normalize(viewDirection + light.dir);
		                float specAmount = pow(max(dot(norm, halfwayVec), 0.0f), 16);
		                specular = specAmount * light.specIntensity;

                        #if SPECULAR_MAP
                            specular *= texture(u_specularMap, texUV).r;
                        #endif
	                };
                
                    if(light.shadows) {
                        float shadow = 0.0f;
	                    vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
	                    if(lightCoords.z <= 1.0f)
	                    {
		                    lightCoords = (lightCoords + 1.0f) / 2.0f;
		                    float currentDepth = lightCoords.z;
		                    float bias = max(0.05f * (1.0f - dot(norm, light.dir)), light.shadow.bias);

		                    vec2 pixelSize = 1.0 / textureSize(light.shadow.map, 0);
		                    for(int y = -light.shadow.sampleRadius; y <= light.shadow.sampleRadius; y++)
		                    {
		                        for(int x = -light.shadow.sampleRadius; x <= light.shadow.sampleRadius; x++)
		                        {
		                            float closestDepth = texture(light.shadow.map, lightCoords.xy + vec2(x, y) * pixelSize).r;
				                    if (currentDepth > closestDepth + bias)
					                    shadow += 1.0f;     
		                        }    
		                    }
		                    shadow /= pow((light.shadow.sampleRadius * 2 + 1), 2);
        	            }

                        return (texture(u_diffuseMap, texUV) * (diffuse * (1.0 - shadow) + light.ambient) + specular) * light.color;
                    }
                
                    return (texture(u_diffuseMap, texUV) * (diffuse + light.ambient) + specular) * light.color;
                }
            #endif    
        
            #if NUM_POINT_LIGHTS
                struct PointShadow {
                    float bias;
                    int sampleRadius;
                    float farPlane;
                    samplerCube cubemap;
                };

                struct PointLight {
                    vec3 pos;
                    vec4 color;
                    float ambient;
                    float a;
                    float b;
                    float specIntensity;
                    bool shadows;
                    PointShadow shadow;
                };

                uniform PointLight u_pointLights[NUM_POINT_LIGHTS];


                vec4 pointLightCalc(PointLight light)
                {
                    vec3 lightVec = light.pos - pos;
                    float dist = length(lightVec);
                    float intensity = 1.0f / (light.a * dist * dist + light.b * dist + 1.0f);
                
                    #if NORMAL_MAP
                        vec3 norm = normalize(texture(u_normalMap, texUV).xzy * 2.0f - 1.0f);
                    #else
                        vec3 norm = normalize(normal);
	                #endif
                
                    vec3 lightDirection = normalize(lightVec);
	                float diffuse = max(dot(norm, lightDirection), 0.0f);

                    float specular = 0.0f;
	                if(diffuse != 0.0f)
	                {
		                vec3 viewDirection = normalize(u_cameraPos - pos);
		                vec3 halfwayVec = normalize(viewDirection + lightDirection);
		                float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		                specular = specAmount * light.specIntensity;

                        #if SPECULAR_MAP
                            specular *= texture(u_specularMap, texUV).r;
                        #endif
	                };

                    if(light.shadows) {
                        float shadow = 0.0f;
	                    vec3 fragToLight = pos - light.pos;
                        float currentDepth = length(fragToLight);
                        float bias = max(0.05f * (1.0f - dot(norm, lightDirection)), light.shadow.bias);
                        float offset = 0.1f;

	                    for(int z = -light.shadow.sampleRadius; z <= light.shadow.sampleRadius; z++)
	                    {
		                    for(int y = -light.shadow.sampleRadius; y <= light.shadow.sampleRadius; y++)
		                    {
		                        for(int x = -light.shadow.sampleRadius; x <= light.shadow.sampleRadius; x++)
		                        {
		                            float closestDepth = texture(light.shadow.cubemap, fragToLight + vec3(x, y, z) * offset).r;
				                    closestDepth *= 50;
				                    if (currentDepth > closestDepth + bias)
					                    shadow += 1.0f;     
		                        }    
		                    }
	                    }
	                    // Average shadow
	                    shadow /= pow((light.shadow.sampleRadius * 2 + 1), 3);

                        return (texture(u_diffuseMap, texUV) * (diffuse * (1.0 - shadow) + light.ambient) + specular * (1.0 - shadow) * intensity) * light.color;
                    }

                    return (texture(u_diffuseMap, texUV) * (diffuse * intensity + light.ambient) + specular * intensity)  * light.color;
                }
            #endif
          
            void main()
            {
                vec4 finalColor = vec4(0.0f);

                #if NUM_DIRECTIONAL_LIGHTS
                    for(int i=0; i < NUM_DIRECTIONAL_LIGHTS; i++)
                        finalColor += directionalLightCalc(u_directionalLights[i]);
                #endif

                #if NUM_POINT_LIGHTS
                    for(int i=0; i < NUM_POINT_LIGHTS; i++)
                        finalColor += pointLightCalc(u_pointLights[i]);
                #endif

                gl_FragColor = finalColor;
            })"
        );
    }


    Basic2DTextureMaterial::Basic2DTextureMaterial(const Ref<Texture2D>& texture) :
        texture(texture) {}

    void Basic2DTextureMaterial::use() const
    {
        shader.use();
        shader.uniformVec4(shader.getUniform("u_tex"), texture->getUnit());
    }

    void Basic2DTextureMaterial::create()
    {
        shader.create();
        shader.attachShaders(
            R"(#version 430 core

            layout(location = 0) in vec3 v_pos;
            layout(location = 1) in vec3 v_texUV;

            uniform mat4 u_projection;
            out vec2 texUV;

            void main()
            {
                texUV = v_texUV;
                gl_Position = vec4(v_pos, 1) * u_projection;
            })",

            R"(#version 430 core

            uniform sampler2D tex;
            in vec2 texUV;

            void main()
            {
                gl_FragColor = texture(tex, texUV);
            })"
        );
    }
}
