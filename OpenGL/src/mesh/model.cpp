#include "model.h"
/**
 * @brief Class description
 */

/*Constructors--------------------------------*/
/**
 * @brief Model constructor
 */
Model::Model()
{
    
}

/**
 * @brief Model desctructor
 */
Model::~Model()
{
    this->ClearModel();
}

/*Methods-------------------------------------*/


void Model::LoadModel(const std::string& param_filename)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
            param_filename, 
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if(!scene)
    {
        std::cerr << "Model " << param_filename << " failed to load : " << importer.GetErrorString() << std::endl;
        return;
    }

    LoadNode(scene->mRootNode, scene);

    LoadMaterials(scene);
}

void Model::RenderModel()
{
    for (size_t i = 0; i < m_mesh_list.size(); i++)
    {
        unsigned int material_index = m_mesh_to_tex[i];

        if (material_index < m_texture_list.size() && m_texture_list[material_index])
        {
            m_texture_list[material_index]->UseTexture();
        }

        m_mesh_list[i]->RenderMesh();
    }
}

void Model::ClearModel()
{
    for (size_t i = 0; i < m_mesh_list.size(); i++)
    {
        if(m_mesh_list[i])
        {
            delete m_mesh_list[i];
            m_mesh_list[i] = nullptr;
        }
    }

    for (size_t i = 0; i < m_texture_list.size(); i++)
    {
        if(m_texture_list[i])
        {
            delete m_texture_list[i];
            m_texture_list[i] = nullptr;
        }
    }
}

void Model::LoadNode(aiNode* param_node, const aiScene* param_scene)
{
    for (size_t i = 0; i < param_node->mNumMeshes; i++)
    {
        LoadMesh(param_scene->mMeshes[param_node->mMeshes[i]], param_scene);
    }

    for (size_t j = 0; j < param_node->mNumChildren; j++)
    {
        LoadNode(param_node->mChildren[j], param_scene);
    }
}

void Model::LoadMesh(aiMesh* param_mesh, const aiScene* param_scene)
{
    /* Vetices stored in array*/
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    /* Add the vertices, the text coords and the normals*/
    for (size_t i =0; i < param_mesh->mNumVertices; i++)
    {
        /* Vertices */
        vertices.insert(
            vertices.end(), 
            {
                param_mesh->mVertices[i].x, 
                param_mesh->mVertices[i].y, 
                param_mesh->mVertices[i].z});

        /* Texture Coordinates */
        if (param_mesh->mTextureCoords[0])
        {
            vertices.insert(
                vertices.end(), 
                {
                    param_mesh->mTextureCoords[0][i].x, 
                    param_mesh->mTextureCoords[0][i].y});
        }
        else 
        {
            vertices.insert(
                vertices.end(), 
                {
                    0.0f, 
                    0.0f});
        }

        /* Normals */
        vertices.insert(
            vertices.end(), 
            {
                -param_mesh->mNormals[i].x, 
                -param_mesh->mNormals[i].y, 
                -param_mesh->mNormals[i].z});
    }
    /* Faces */
    for (size_t i = 0; i < param_mesh->mNumFaces; i++)
    {
        aiFace face = param_mesh->mFaces[i];

        for(size_t j = 0; j < face.mNumIndices;j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh* new_mesh = new Mesh();
    new_mesh->CreateMesh(
        &vertices[0], 
        &indices[0], 
        vertices.size(), 
        indices.size());

    m_mesh_list.push_back(new_mesh);
    m_mesh_to_tex.push_back(param_mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene* param_scene)
{
    m_texture_list.resize(param_scene->mNumMaterials);

    for(size_t i = 0; i < param_scene->mNumMaterials; i++)
    {
        aiMaterial* material = param_scene->mMaterials[i];

        m_texture_list[i] = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {
                int idx = std::string(path.data).rfind("\\");
                std::string file_name = std::string(path.data).substr(idx + 1);

                std::string text_path = std::string("../textures/") + file_name;

                m_texture_list[i] = new Texture(text_path.c_str());

                if(!m_texture_list[i]->LoadTexture())
                {
                    std::cerr << "Failed to laod texture at:" << text_path << std::endl;
                    delete m_texture_list[i];
                    m_texture_list[i] = nullptr;
                }
            }
        }

        if (!m_texture_list[i])
        {
            m_texture_list[i] = new Texture("../textures/plain.png");
            m_texture_list[i]->LoadTextureAlpha();
        }
    }
}

 