#include "directional_light.h"

DirectionalLight::DirectionalLight()
    : Light(), 
      m_direction (glm::vec3(0.0f, -1.0f, 0.0f)){}

DirectionalLight::DirectionalLight(
    GLfloat param_red, 
    GLfloat param_green,
    GLfloat param_blue,
    GLfloat param_ambient_intensity,
    GLfloat param_diffuse_intensity,
    GLfloat param_x_direction,
    GLfloat param_y_direction,
    GLfloat param_z_direction)
    
    : Light(
        param_red, 
        param_green,
        param_blue,
        param_ambient_intensity,
        param_diffuse_intensity),
      m_direction (glm::vec3(
        param_x_direction, 
        param_y_direction, 
        param_z_direction)){}

DirectionalLight::~DirectionalLight(){}

void DirectionalLight::UseLight(
    GLfloat param_ambient_intensity_location,
    GLfloat param_ambient_color_location,
    GLfloat param_diffuse_intensity_location,
    GLfloat param_direction_location)
{
    glUniform3f(param_ambient_color_location, m_color.x, m_color.y, m_color.z);
    glUniform1f(param_ambient_intensity_location, m_ambient_intensity);

    glUniform3f(param_direction_location, m_direction.x, m_direction.y, m_direction.z);
    glUniform1f(param_diffuse_intensity_location, m_diffuse_intensity);
}