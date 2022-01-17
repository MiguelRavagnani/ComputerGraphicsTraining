#ifndef _MATERIAL_
#define _MATERIAL_

#include <iostream>

#include <GL/glew.h>

class Material
{
public:
    Material();

    Material(
        GLfloat param_specular_intensity,
        GLfloat param_shine);

    ~Material();

    void UseMaterial(
        GLuint param_specular_intensity_location,
        GLuint param_shininess_location
    );

private:
    GLfloat m_specular_intensity;
    GLfloat m_shininess;
};

#endif //_MATERIAL_