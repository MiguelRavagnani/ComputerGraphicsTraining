#include "spot_light.h"


SpotLight::SpotLight()
    : PointLight(),
      m_direction (glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f))),
      m_edge (0),
      m_process_edge (cosf(glm::radians(m_edge))){}

SpotLight::SpotLight(
    GLfloat param_red, 
    GLfloat param_green,
    GLfloat param_blue,
    GLfloat param_ambient_intensity,
    GLfloat param_diffuse_intensity,
    GLfloat param_x_position,
    GLfloat param_y_position,
    GLfloat param_z_position,
    GLfloat param_x_direction,
    GLfloat param_y_direction,   
    GLfloat param_z_direction,   
    GLfloat param_constant,
    GLfloat param_linear,
    GLfloat param_exponent,
    GLfloat param_edge)
    
    : PointLight(
        param_red, 
        param_blue, 
        param_green, 
        param_ambient_intensity, 
        param_diffuse_intensity,
        param_x_position,
        param_y_position,
        param_z_position,
        param_constant, 
        param_linear,
        param_exponent),
    m_direction (glm::normalize(glm::vec3(
        param_x_direction, 
        param_y_direction, 
        param_z_direction))),
    m_edge (param_edge),
    m_process_edge (cosf(glm::radians(m_edge))){}

void SpotLight::UseLight(
    GLuint param_ambient_intensity_location,
    GLuint param_ambient_color_location,
    GLuint param_diffuse_intensity_location,
    GLuint param_position_location,
    GLuint param_direction_location,
    GLuint param_constant_location,
    GLuint param_linear_location,
    GLuint param_exponent_location,
    GLuint param_edge_location)
{

    glUniform3f(param_ambient_color_location, m_color.x, m_color.y, m_color.z);
    glUniform1f(param_ambient_intensity_location, m_ambient_intensity);
    glUniform1f(param_diffuse_intensity_location, m_diffuse_intensity);

    glUniform3f(param_position_location, m_position.x, m_position.y, m_position.y);
    glUniform1f(param_constant_location, m_constant);
    glUniform1f(param_linear_location, m_linear);
    glUniform1f(param_exponent_location, m_exponent);

    glUniform3f(param_direction_location, m_direction.x, m_direction.y, m_direction.z);
    glUniform1f(param_edge_location, m_process_edge);
}

void SpotLight::SetFlash(glm::vec3 param_position, glm::vec3 param_direction)
{
    m_position = param_position;
    m_direction = param_direction;
}

SpotLight::~SpotLight(){}