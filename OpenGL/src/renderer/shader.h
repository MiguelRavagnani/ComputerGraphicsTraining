#ifndef _SHADER_
#define _SHADER_

#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>

#include "directional_light.h"
#include "point_light.h"

#include "common_values.h"

class Shader
{
public:
    Shader();
    ~Shader();

    void CreateFromString(
        const char* param_vertex_code,
        const char* param_fragment_code);

    void CreateFromFile(
        const char* param_vertex_location,
        const char* param_fragment_location);

    std::string ReadFile(const char* param_file_path);


    void SetDirectionalLight(DirectionalLight* param_directional_light);
    void SetPointLights(PointLight* param_point_light, unsigned int param_light_count);

    void UseShader();

    void ClearShader();

    GLuint GetProjectionLocation();
    
    GLuint GetModelLocation();

    GLuint GetViewLocation();

    GLuint GetAmbientIntensityLocation();

    GLuint GetAmbientColorLocation();

    GLuint GetDiffuseIntensityLocation();

    GLuint GetDirectionLocation();

    GLuint GetSpecularIntensityLocation();

    GLuint GetShininessLocation();

    GLuint GetEyePositionLocation();
private:
    void CompileShader(
        const char* param_vertex_code,
        const char* param_fragment_code);

    void AddShader(
        GLuint param_the_program, 
        const char* param_shader_code,
        GLenum param_shader_type);

private:
    GLuint m_shader_id;
    GLuint m_uniform_projection;
    GLuint m_uniform_model;
    GLuint m_uniform_view;

    GLuint m_uniform_eye_position;
    GLuint m_uniform_specular_intensity;
    GLuint m_uniform_shininess;

    GLuint m_uniform_point_light_count;

    int m_point_light_count;

    /* Directional light uniforms. Could be an array,
     * just like the point light*/
    struct 
    {
        GLuint m_uniform_color;
        GLuint m_uniform_ambient_intensity;
        GLuint m_uniform_diffuse_intensity;
        
        GLuint m_uniform_direction;
    } m_uniform_directional_light;

    /* Point light uniforms. Array to define several
     * point lightd*/
    struct 
    {
        GLuint m_uniform_color;
        GLuint m_uniform_ambient_intensity;
        GLuint m_uniform_diffuse_intensity;
        
        GLuint m_uniform_position;
        GLuint m_uniform_constant;
        GLuint m_uniform_linear;
        GLuint m_uniform_exponent;
    } m_uniform_point_light[MAX_POINT_LIGHTS];
};


#endif //_SHADER_