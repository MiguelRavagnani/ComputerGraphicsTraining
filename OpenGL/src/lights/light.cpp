#include "light.h"

Light::Light()
    : m_color (glm::vec3(1.0f, 1.0f, 1.0f)),
      m_ambient_intensity (1.0f),
      m_diffuse_intensity (0.0f){}

Light::Light(
    GLfloat param_red, 
    GLfloat param_green,
    GLfloat param_blue,
    GLfloat param_ambient_intensity,
    GLfloat param_diffuse_intensity)
    : m_color (glm::vec3(param_red, param_green, param_blue)),
      m_ambient_intensity (param_ambient_intensity),
      m_diffuse_intensity (param_diffuse_intensity){}

Light::~Light(){}