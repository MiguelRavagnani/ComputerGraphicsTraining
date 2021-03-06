#ifndef _POINT_LIGHT_
#define _POINT_LIGHT_

#include <iostream>

#include "light.h"

class PointLight : public Light
{
public:
    PointLight();

    PointLight(
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
        GLfloat param_exponent);

    /* Params should be GLuint*/
    void UseLight(
        GLuint param_ambient_intensity_location,
        GLuint param_ambient_color_location,
        GLuint param_diffuse_intensity_location,
        GLuint param_position_location,
        GLuint param_constant_location,
        GLuint param_linear_location,
        GLuint param_exponent_location);

    ~PointLight();

protected:
    glm::vec3 m_position;

    GLfloat m_constant;
    GLfloat m_linear;
    GLfloat m_exponent;
};


#endif //_POINT_LIGHT_