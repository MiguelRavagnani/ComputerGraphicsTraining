#ifndef _CAMERA_
#define _CAMERA_

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera();

    Camera(
        glm::vec3 param_start_position,
        glm::vec3 param_start_world_up,
        GLfloat param_start_yaw,
        GLfloat param_start_pitch,
        GLfloat param_start_move_speed,
        GLfloat param_start_turn_speed);

    ~Camera();

    void KeyControl(bool* param_keys, GLfloat param_delta_time);

    void MouseControl(GLfloat param_x_change, GLfloat param_y_change);

    glm::vec3 GetCameraPosition();

    glm::mat4 CalculateViewMatrix();

private:
    void Update();

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;

    GLfloat m_yaw;
    GLfloat m_pitch;

    GLfloat m_movement_speed;
    GLfloat m_turn_speed;
};


#endif //_CAMERA_