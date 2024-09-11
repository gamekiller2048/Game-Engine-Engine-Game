#include <resourceloader/modelloader.hpp>
#include <fstream>
#include <sstream>

namespace mrl
{
    ModelData ModelLoader::load(const std::string& filePath)
    {
        return ModelData{};
    }

    ObjModelData ModelLoader::loadObj(const std::string& filePath)
	{
        ObjModelData data;

        std::string line;
        std::ifstream file(filePath);
        
        std::vector<mml::vec3> positions;
        std::vector<mml::vec2> texUVs;
        std::vector<mml::vec3> normals;
        std::vector<mgl::Vertex3DUVN> vertices;
        std::vector<GLuint> indices;

        while(std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string flag;
            lineStream >> flag;

            if(flag == "v") {
                float x, y, z;
                lineStream >> x >> y >> z;
                positions.push_back(mml::vec3(x, y, z));
            }
            else if(flag == "vt") {
                float x, y;
                lineStream >> x >> y;
                texUVs.push_back(mml::vec2(x, y));
            }
            else if(flag == "vn") {
                float x, y, z;
                lineStream >> x >> y >> z;

                normals.push_back(mml::vec3(x, y, z));
            }
            else if(flag == "f") {
                std::string vertex;
                int c = 0;

                while(lineStream >> vertex) {
                    vertices.push_back(mgl::Vertex3DUVN{});

                    std::string pos, texUV, normal;
                    std::istringstream vss(vertex);

                    std::getline(vss, pos, '/');
                    std::getline(vss, texUV, '/');
                    std::getline(vss, normal, '/');

                    vertices[vertices.size() - 1].pos = positions[std::stoi(pos) - 1];
                    if(texUV != "")
                        vertices[vertices.size() - 1].texUV = texUVs[std::stoi(texUV) - 1];
                    if(normal != "")
                        vertices[vertices.size() - 1].normal = normals[std::stoi(normal) - 1];

                    c++;
                }

                // primitive is square
                if(c == 4) {
                    indices.push_back(vertices.size() - 4);
                    indices.push_back(vertices.size() - 3);
                    indices.push_back(vertices.size() - 2);

                    indices.push_back(vertices.size() - 4);
                    indices.push_back(vertices.size() - 2);
                    indices.push_back(vertices.size() - 1);
                }
                else {
                    indices.push_back(vertices.size() - 3);
                    indices.push_back(vertices.size() - 2);
                    indices.push_back(vertices.size() - 1);
                }

            }
            else if(flag == "o") {
                // skip first mesh
                if(vertices.size() > 0) {
                    data.meshes[data.meshes.size() - 1]->mesh->setGeometry(mgl::Geometry<mgl::Vertex3DUVN, GLuint>{vertices, indices});
                    data.meshes[data.meshes.size() - 1]->vertices = vertices;
                    data.meshes[data.meshes.size() - 1]->indices = indices;
                    indices.clear();
                }

                std::string meshName;
                lineStream >> meshName;

                mgl::Ref<ObjMesh> m = mgl::CreateRef<ObjMesh>();
                m->mesh = mgl::CreateRef<mgl::ModelMesh>();
                m->mesh->create();
                m->name = meshName;
                data.meshes.push_back(m);
            }
        }

        // add the last mesh
        if(data.meshes.size() > 0) {
            data.meshes[data.meshes.size() - 1]->mesh->setGeometry(mgl::Geometry<mgl::Vertex3DUVN, GLuint>{vertices, indices});
            data.meshes[data.meshes.size() - 1]->vertices = vertices;
            data.meshes[data.meshes.size() - 1]->indices = indices;
        }
        // some models don't specify o flag if it only has 1 mesh so create and add another mesh
        else {
            mgl::Ref<ObjMesh> m = mgl::CreateRef<ObjMesh>();
            
            m->mesh = mgl::CreateRef<mgl::ModelMesh>();
            m->mesh->create();
            m->mesh->setGeometry(mgl::Geometry<mgl::Vertex3DUVN, GLuint>{vertices, indices});
            m->vertices = vertices;
            m->indices = indices;
            data.meshes.push_back(m);
        }

        return data;
	}
}
