#ifndef _SPOT_LIGHT_
#define _SPOT_LIGHT_

#include <iostream>

#include "point_light.h"

class SpotLight : public PointLight
{
public:
    SpotLight();

    SpotLight(
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
        GLfloat param_edge);

    /* Params should be GLuint*/
    void UseLight(
        GLuint param_ambient_intensity_location,
        GLuint param_ambient_color_location,
        GLuint param_diffuse_intensity_location,
        GLuint param_position_location,
        GLuint param_direction_location,
        GLuint param_constant_location,
        GLuint param_linear_location,
        GLuint param_exponent_location,
        GLuint param_edge_location);

    void SetFlash(glm::vec3 param_position, glm::vec3 param_direction);

    ~SpotLight();

protected:
    glm::vec3 m_direction;

    GLfloat m_edge;
    GLfloat m_process_edge;
};


#endif //_SPOT_LIGHT_