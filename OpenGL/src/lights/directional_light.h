#ifndef _DIRECTIONAL_LIGHT_
#define _DIRECTIONAL_LIGHT_

#include <iostream>

#include "light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight();

    DirectionalLight(
        GLfloat param_red, 
        GLfloat param_green,
        GLfloat param_blue,
        GLfloat param_ambient_intensity,
        GLfloat param_diffuse_intensity,
        GLfloat param_x_direction,
        GLfloat param_y_direction,
        GLfloat param_z_direction);

    /* Params should be GLuint*/
    void UseLight(
        GLfloat param_ambient_intensity_location,
        GLfloat param_ambient_color_location,
        GLfloat param_diffuse_intensity_location,
        GLfloat param_direction_location);

    ~DirectionalLight();

private:
    glm::vec3 m_direction;
};


#endif //_DIRECTIONAL_LIGHT_