#ifndef _GL_WINDOW_
#define _GL_WINDOW_

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow
{
public:
    GLWindow();

    GLWindow(
        GLint param_window_width,
        GLint param_window_height);

    ~GLWindow();

    int Initialize();

    GLfloat GetBufferWidth();

    GLfloat GetBufferHeight();

    bool GetShouldClose();

    bool* GetKeys();

    GLfloat GetXChange();
    
    GLfloat GetYChange();

    void SwapBuffers();

private:
    static void HandleKeys(
        GLFWwindow* param_window,
        int param_key,
        int param_code,
        int param_action,
        int param_mode);

    static void HandleMouse(
        GLFWwindow* param_window,
        double param_x_pos,
        double param_y_pos);

    void CreateCallbacks();

private:
    GLFWwindow* m_main_window;

    GLint m_window_width;
    GLint m_window_height;

    GLint m_buffer_width;
    GLint m_buffer_heigth;

    bool m_keys[1024];

    GLfloat m_last_x;
    GLfloat m_last_y;
    GLfloat m_x_change;
    GLfloat m_y_change;

    bool m_mouse_first_moved;
};


#endif //_GL_WINDOW_