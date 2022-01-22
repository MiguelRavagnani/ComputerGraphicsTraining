#include "camera.h"

Camera::Camera() {}

Camera::Camera(
    glm::vec3 param_start_position,
    glm::vec3 param_start_world_up,
    GLfloat param_start_yaw,
    GLfloat param_start_pitch,
    GLfloat param_start_move_speed,
    GLfloat param_start_turn_speed)

    : m_position (param_start_position),
      m_world_up (param_start_world_up),
      m_yaw (param_start_yaw),
      m_pitch (param_start_pitch),
      m_front (glm::vec3(0.0f, 0.0f, -1.0f)),
      m_movement_speed (param_start_move_speed),
      m_turn_speed (param_start_turn_speed)
{
    Update();
}

Camera::~Camera()
{
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::KeyControl(bool* param_keys, GLfloat param_delta_time)
{
    GLfloat velocity = m_movement_speed * param_delta_time;
    if (param_keys[GLFW_KEY_W])
    {
        m_position += m_front * velocity;
    }

    if (param_keys[GLFW_KEY_S])
    {
        m_position -= m_front * velocity;
    }

    if (param_keys[GLFW_KEY_A])
    {
        m_position -= m_right * velocity;
    }

    if (param_keys[GLFW_KEY_D])
    {
        m_position += m_right * velocity;
    }
}

void Camera::MouseControl(GLfloat param_x_change, GLfloat param_y_change)
{
    param_x_change *= m_turn_speed;
    param_y_change *= m_turn_speed;

    m_yaw += param_x_change;
    m_pitch += param_y_change;

    if (m_pitch > 89.0f)
    {
        m_pitch = 89.0f;
    }

    if (m_pitch < -89.0f)
    {
        m_pitch = -89.0f;
    }

    Update();
}

glm::vec3 Camera::GetCameraPosition(){return m_position;}

glm::vec3 Camera::GetCameraDirection(){return glm::normalize(m_front);}

glm::mat4 Camera::CalculateViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::Update()
{
    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(m_front);

    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}