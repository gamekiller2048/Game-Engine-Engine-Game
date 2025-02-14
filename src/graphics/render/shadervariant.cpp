#include <graphics/render/shadervariant.hpp>

namespace mgl
{
	static std::string standardForwardVert = R"(
		layout(location = 0) in vec3 v_pos;
		layout(location = 1) in vec2 v_texUV;
        
        #if !NORMAL_MAP
		    layout(location = 2) in vec3 v_normal;
		#endif

        uniform mat4 u_projection;
		uniform mat4 u_transform;
		uniform mat4 u_lightProjection;

		out vec2 texUV;
		out vec3 pos;
		out vec3 normal;

		void main()
		{
			vec4 p = vec4(v_pos, 1) * u_transform;
			pos = vec3(p);
			normal = v_normal;
			gl_Position = p * u_projection;

			texUV = v_texUV;
		})";

    static std::string standardForwardFrag = R"(
        in vec3 pos;
        in vec2 texUV;
        in vec3 normal;
        
        #if DIFFUSE_MAP
            uniform sampler2D u_diffuseMap;
        #else
            uniform vec4 u_albedo;
        #endif

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
				float intensity;
                float specIntensity;
                bool shadows;
                DirectionalShadow shadow;
				mat4 projection;
            };

            uniform DirectionalLight u_directionalLights[NUM_DIRECTIONAL_LIGHTS];

            vec4 directionalLightCalc(DirectionalLight light)
            {
                #if NORMAL_MAP
                    vec3 norm = normalize(texture(u_normalMap, texUV).xzy * 2.0f - 1.0f);
                #else
                    vec3 norm = normalize(normal);
	            #endif

				vec3 lightDir = normalize(-light.dir);
	            float diffuse = max(dot(norm, lightDir), 0.0f);
    
	            float specular = 0.0f;
	            if(diffuse != 0.0f)
	            {
		            vec3 viewDirection = normalize(u_cameraPos - pos);
		            vec3 halfwayVec = normalize(viewDirection + lightDir);
		            float specAmount = pow(max(dot(norm, halfwayVec), 0.0f), 16);
		            specular = specAmount * light.specIntensity;

                    #if SPECULAR_MAP
                        specular *= texture(u_specularMap, texUV).r;
                    #endif
	            };
                
                if(light.shadows) {
                    float shadow = 0.0f;
						
	                vec3 lightCoords = (vec4(pos, 1.0f) * light.projection).xyz;
	                if(lightCoords.z <= 1.0f)
	                {
		                lightCoords = (lightCoords + 1.0f) / 2.0f;
		                float currentDepth = lightCoords.z;
		                float bias = max(0.00025f * (1.0f - dot(norm, lightDir)), light.shadow.bias);

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
                    
                    #if DIFFUSE_MAP
                        return (texture(u_diffuseMap, texUV) * (diffuse * light.intensity * (1.0 - shadow) + light.ambient) + specular) * light.color;
                    #else
                        return (u_albedo * (diffuse * light.intensity * (1.0 - shadow) + light.ambient) + specular) * light.color;
                    #endif
                }
                #if DIFFUSE_MAP
                    return (texture(u_diffuseMap, texUV) * (diffuse * light.intensity + light.ambient) + specular) * light.color;
                #else
                    return (u_albedo * (diffuse * light.intensity + light.ambient) + specular) * light.color;
                #endif
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
				float intensity;
                float specIntensity;
                bool shadows;
                PointShadow shadow;
            };

            uniform PointLight u_pointLights[NUM_POINT_LIGHTS];


            vec4 pointLightCalc(PointLight light)
            {
                vec3 lightVec = light.pos - pos;
                float dist = length(lightVec);
                float intensity = light.intensity / (light.a * dist * dist + light.b * dist + 1.0f);
                
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
                    float bias = max(0.00025f * (1.0f - dot(norm, lightDirection)), light.shadow.bias);
                    float offset = 0.01f;

	                for(int z = -light.shadow.sampleRadius; z <= light.shadow.sampleRadius; z++)
	                {
		                for(int y = -light.shadow.sampleRadius; y <= light.shadow.sampleRadius; y++)
		                {
		                    for(int x = -light.shadow.sampleRadius; x <= light.shadow.sampleRadius; x++)
		                    {
		                        float closestDepth = texture(light.shadow.cubemap, fragToLight + vec3(x, y, z) * offset).r;
				                closestDepth *= 50; // TODO: this is farplane
				                if(currentDepth > closestDepth + bias)
					                shadow += 1.0f;     
		                    }    
		                }
	                }

	                // Average shadow
	                shadow /= pow((light.shadow.sampleRadius * 2 + 1), 3);

                    #if DIFFUSE_MAP
                        return (texture(u_diffuseMap, texUV) * (diffuse * (1.0 - shadow) + light.ambient) + specular * (1.0 - shadow) * intensity) * light.color;
                    #else
                        return (u_albedo * (diffuse * (1.0 - shadow) + light.ambient) + specular * (1.0 - shadow) * intensity) * light.color;
                    #endif
                }
                #if DIFFUSE_MAP
                    return (texture(u_diffuseMap, texUV) * (diffuse * intensity + light.ambient) + specular * intensity)  * light.color;
                #else
                    return (u_albedo * (diffuse * intensity + light.ambient) + specular * intensity)  * light.color;
                #endif
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
        })";

    static std::string standardDeferredVert = R"(
        layout(location = 0) in vec3 v_pos;
        layout(location = 1) in vec2 v_texUV;
        layout(location = 2) in vec3 v_normal;

        uniform mat4 u_projection;
        uniform mat4 u_transform;

        out vec2 texUV;
        out vec3 pos;
        out vec3 normal;

        void main()
        {
            vec4 p = vec4(v_pos, 1) * u_transform;
            pos = vec3(p);
            normal = normalize(v_normal);
            gl_Position = p * u_projection;

            texUV = v_texUV;
        })";

    static std::string standardDeferredFrag = R"(
		layout (location = 0) out vec3 gPosition;
		layout (location = 1) out vec3 gNormal;
		layout (location = 2) out vec4 gAlbedoSpec;

		in vec2 texUV;
		in vec3 pos;
		in vec3 normal;

		uniform sampler2D diffuse;
		uniform sampler2D specular;

		void main()
		{    
			gPosition = pos;
			gNormal = normal;
			gAlbedoSpec.rgb = texture(diffuse, texUV).rgb;
			gAlbedoSpec.a = texture(specular, texUV).r;
		})";

    static std::string defineString(const std::string& name, int value)
    {
        return "#define " + name + ' ' + std::to_string(value) + '\n';
    }

    static std::string versionString(int version, bool isCore)
    {
        return "#version " + std::to_string(version) + (isCore ? " core\n" : "\n");
    }

    StandardShaderVairant::StandardShaderVairant(RenderPipeline pipeline, bool diffuseMap, bool normalMap, bool specularMap, uint numDirLights, uint numPointLights) :
        pipeline(pipeline), diffuseMap(diffuseMap), normalMap(normalMap), specularMap(specularMap), numDirLights(numDirLights), numPointLights(numPointLights)
    {
        std::string defines;
        std::string baseVert;
        std::string baseFrag;

        if(pipeline == RenderPipeline::FORWARD) {
            baseVert = standardForwardVert;
            baseFrag = standardForwardFrag;
        }
        else if(pipeline == RenderPipeline::DEFERRED) {
            baseVert = standardDeferredVert;
            baseFrag = standardDeferredFrag;
        }

        defines += defineString("DIFFUSE_MAP", diffuseMap);
        defines += defineString("NORMAL_MAP", normalMap);
        defines += defineString("SPECULAR_MAP", specularMap);
        defines += defineString("NUM_DIRECTIONAL_LIGHTS", numDirLights);
        defines += defineString("NUM_POINT_LIGHTS", numPointLights);

        std::string version = versionString(430, true);
        srcVert = version + defines + baseVert;
        srcFrag = version + defines + baseFrag;
    }

    static std::string basicForwardVert = R"(
		layout(location = 0) in vec3 pos;
		uniform mat4 u_projection;
		uniform mat4 u_transform;
		void main()
		{
			gl_Position = vec4(pos, 1) * u_transform * u_projection;
		})";

    static std::string basicForwardFrag = R"(
		uniform vec4 u_albedo;
		void main()
		{
			gl_FragColor = u_albedo;
		})";

    BasicShaderVairant::BasicShaderVairant()
    {
        std::string version = versionString(430, true);
        srcVert = version + basicForwardVert;
        srcFrag = version + basicForwardFrag;
    }
}