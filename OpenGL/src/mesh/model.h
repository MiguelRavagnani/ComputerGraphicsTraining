#ifndef _MODEL_
#define _MODEL_

/** 
 *  @file   Model.h 
 *  @brief  Class description
 *  @author Miguel Ravagnani de Carvalho 
 *  @date   2022-28-01 
 **************************************************/

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "texture.h"

/**
 * @brief Class description
 */
class Model
{
public:
    /*Constructors--------------------------------*/
    /**
     * @brief Model constructor
     */
    Model();

    /**
     * @brief Model desctructor
     */
    ~Model();

    /*Methods-------------------------------------*/
    
    void LoadModel(const std::string& param_filename);
    void RenderModel();
    void ClearModel();

private:
    /*--------------------------------------------*/
    void LoadNode(aiNode* param_node, const aiScene* param_scene);
    void LoadMesh(aiMesh* param_mesh, const aiScene* param_scene);
    void LoadMaterials(const aiScene* param_scene);

private:
    /*--------------------------------------------*/
    /*Member variables starting with m_*/

    std::vector<Mesh* > m_mesh_list;
    std::vector<Texture* > m_texture_list;

    /* References the offset from the current 
     * texture index and the mesh index
     */
    std::vector<unsigned int> m_mesh_to_tex;
};

#endif //_MODEL_
 