#ifndef _LIGHT_
#define _LIGHT_

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
    Light();

    Light(
        GLfloat param_red, 
        GLfloat param_green,
        GLfloat param_blue,
        GLfloat param_ambient_intensity,
        GLfloat param_diffuse_intensity);

    ~Light();

protected:
    glm::vec3 m_color;
    GLfloat m_ambient_intensity;
    GLfloat m_diffuse_intensity;
};


#endif //_LIGHT_