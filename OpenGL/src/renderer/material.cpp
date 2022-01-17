#include "material.h"

Material::Material()
    : m_shininess (0.0f),
      m_specular_intensity (0.0f){}

Material::Material(
    GLfloat param_specular_intensity,
    GLfloat param_shine)
    : m_shininess (param_shine),
      m_specular_intensity (param_specular_intensity){}

void Material::UseMaterial(
    GLuint param_specular_intensity_location,
    GLuint param_shininess_location)
{
    glUniform1f(param_specular_intensity_location, m_specular_intensity);
    glUniform1f(param_shininess_location, m_shininess);
}

 Material::~Material(){}