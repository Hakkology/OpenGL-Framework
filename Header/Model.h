#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model{

public:
    
    Model();

    void LoadModel(const std::string &fileName, const std::string &directory);
    void Render3DModel();
    void ClearModel();

    std::string GetTexturePath(const aiString& aiPath);

    ~Model();

private:

    void LoadNode(aiNode *node, const aiScene *scene);
    void LoadMesh(aiMesh *mesh, const aiScene *scene);
    void LoadMaterials(const aiScene *scene, const std::string &directory);

    std::vector<Mesh*> meshList;
    std::vector<Texture*> textureList;
    std::vector<unsigned int> meshToTex;

};

#endif