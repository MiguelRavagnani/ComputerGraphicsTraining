#include "point_light.h"

PointLight::PointLight()
    : Light(), 
      m_position (glm::vec3(0.0f, 0.0f, 0.0f)),
      m_constant (1.0f),
      m_linear (0.0f),
      m_exponent (0.0f){}

PointLight::PointLight(
    GLfloat param_red, 
    GLfloat param_green,
    GLfloat param_blue,
    GLfloat param_ambient_intensity,
    GLfloat param_diffuse_intensity,
    GLfloat param_x_position,
    GLfloat param_y_position,
    GLfloat param_z_position,
    GLfloat param_constant,
    GLfloat param_linear,
    GLfloat param_exponent)
    
    : Light(
      param_red, 
      param_green,
      param_blue,
      param_ambient_intensity,
      param_diffuse_intensity),
      m_position (glm::vec3(
        param_x_position,
        param_y_position,
        param_z_position)),
      m_constant (param_constant),
      m_linear (param_linear),
      m_exponent (param_exponent){}

PointLight::~PointLight(){}

void PointLight::UseLight(
    GLuint param_ambient_intensity_location,
    GLuint param_ambient_color_location,
    GLuint param_diffuse_intensity_location,
    GLuint param_position_location,
    GLuint param_constant_location,
    GLuint param_linear_location,
    GLuint param_exponent_location)
{
    glUniform3f(param_ambient_color_location, m_color.x, m_color.y, m_color.z);
    glUniform1f(param_ambient_intensity_location, m_ambient_intensity);
    glUniform1f(param_diffuse_intensity_location, m_diffuse_intensity);

    glUniform3f(param_position_location, m_position.x, m_position.y, m_position.z);
    glUniform1f(param_constant_location, m_constant);
    glUniform1f(param_linear_location, m_linear);
    glUniform1f(param_exponent_location, m_exponent);
}