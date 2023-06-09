#include "../Header/Model.h"

Model::Model(){

}

void Model::LoadModel(const std::string &fileName){

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices); 

    if (!scene)
    {
        printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
    }

    LoadNode(scene -> mRootNode, scene);
    LoadMaterials(scene);
    
}

void Model::Render3DModel(){
    
    for (size_t i = 0; i < meshList.size(); i++)
    {
        unsigned int materialIndex = meshToTex[i];

        if (materialIndex < textureList.size() && textureList[materialIndex])
        {
            textureList[materialIndex] -> UseTexture();
        }
        
        meshList[i] -> Render3DMesh();
    }
}

void Model::ClearModel(){

    for (size_t i = 0; i < meshList.size(); i++)
    {
        if (meshList[i])
        {
            delete meshList[i];
            meshList[i] = nullptr;
        }
    }

    for (size_t i = 0; i < textureList.size(); i++)
    {
        if (textureList[i])
        {
            delete textureList[i];
            textureList[i] = nullptr;
        }
    }

}

Model::~Model(){

}

void Model::LoadNode(aiNode *node, const aiScene *scene){
    
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        LoadMesh(scene -> mMeshes[i], scene);
    }

    for (size_t i = 0; i < node -> mNumChildren; i++)
    {
        LoadNode(node->mChildren[i], scene);
    }
    
}

void Model::LoadMesh(aiMesh *mesh, const aiScene *scene){
    
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;
    
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.insert(vertices.end(), { mesh-> mVertices[i].x, mesh-> mVertices[i].y, mesh-> mVertices[i].z });
        
        if (mesh -> mTextureCoords[0])
        {
            vertices.insert(vertices.end(), { mesh-> mTextureCoords[0][i].x, mesh-> mTextureCoords[0][i].y });
        } else{

            vertices.insert(vertices.end(), { 0.0f, 0.0f });
        }
        // Either this or the shaders (normalize(direction)) needs to be negative.
        vertices.insert(vertices.end(), { -mesh-> mNormals[i].x, -mesh-> mNormals[i].y, -mesh-> mNormals[i].z });
        
    }

    for (size_t i = 0; i < mesh -> mNumFaces; i++)
    {
        aiFace face = mesh -> mFaces[i];

        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh* newMesh = new Mesh();
    newMesh -> Create3DMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    meshList.push_back(newMesh);
    meshToTex.push_back(mesh -> mMaterialIndex);
}

void Model::LoadMaterials(const aiScene *scene){
    
    textureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial* material = scene->mMaterials[i];
        textureList[i] = nullptr;
        printf("I loaded a texture.");

        for (unsigned int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); j++)
        {
            aiString path;

            if (material->GetTexture(aiTextureType_DIFFUSE, j, &path) == AI_SUCCESS)
            {
                std::string fileName = std::string(path.data);
                const std::string texPath = "../Resources/Models/Texture/" + fileName;
                textureList[i] = new Texture(texPath.c_str());

                if (!textureList[i]->LoadTextureA())
                {
                    printf("Failed to load texture at: %s", texPath);
                    delete textureList[i];
                    textureList[i] = nullptr;
                }
            }
        }

        if (!textureList[i])
        {
            textureList[i] = new Texture("../Resources/Textures/Ground/plain.png");
            textureList[i]->LoadTextureA();
        }
    }
}


