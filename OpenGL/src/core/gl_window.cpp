#include "gl_window.h"

GLWindow::GLWindow()
    : m_window_width (800),
      m_window_height (600),
      m_x_change (0),
      m_y_change (0) 
{
    for (size_t i = 0; i < 1024; i++)
    {
        m_keys[i] = 0;
    }
}

GLWindow::GLWindow(
    GLint param_window_width,
    GLint param_window_height)
    : m_window_width (param_window_width),
      m_window_height (param_window_height),
      m_x_change (0),
      m_y_change (0) 
{
    for (size_t i = 0; i < 1024; i++)
    {
        m_keys[i] = 0;
    }
}

GLWindow::~GLWindow()
{
    glfwDestroyWindow(m_main_window);
    glfwTerminate();
}

int GLWindow::Initialize()
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* OpenGL 3.3*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Core profile*/
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_main_window = glfwCreateWindow(
        m_window_width, 
        m_window_height, 
        "OpenGL main window",
        NULL,
        NULL);

    if (!m_main_window)
    {
        std::cerr << "Failed to create OpenGL main window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Get buffer size information*/
    glfwGetFramebufferSize(m_main_window, &m_buffer_width, &m_buffer_heigth);

    /* Sets the m_main_window in current context after
     * instantiating it*/
    glfwMakeContextCurrent(m_main_window);

    /* Create callbacks*/
    CreateCallbacks();
    glfwSetInputMode(m_main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Allow modern extenstions*/
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwDestroyWindow(m_main_window);
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    /* Setup viewport size*/
    glViewport(0, 0, m_buffer_width, m_buffer_heigth);

    glfwSetWindowUserPointer(m_main_window, this);
    return 0;
}

GLfloat GLWindow::GetBufferWidth()
{
    return m_buffer_width;
}

GLfloat GLWindow::GetBufferHeight()
{
    return m_buffer_heigth;
}

bool GLWindow::GetShouldClose()
{
    return glfwWindowShouldClose(m_main_window);
}

bool* GLWindow::GetKeys()
{
    return m_keys;
}

GLfloat GLWindow::GetXChange()
{
    GLfloat the_change = m_x_change;
    m_x_change = 0.0f;
    return the_change;
}

GLfloat GLWindow::GetYChange()
{
    GLfloat the_change = m_y_change;
    m_y_change = 0.0f;
    return the_change;

}

void GLWindow::SwapBuffers()
{
    /* Swap to latter drawn scene*/
    glfwSwapBuffers(m_main_window);
}

void GLWindow::HandleKeys(
        GLFWwindow* param_window,
        int param_key,
        int param_code,
        int param_action,
        int param_mode)
{
    GLWindow* the_window = static_cast<GLWindow*>(glfwGetWindowUserPointer(param_window));

    if (param_key == GLFW_KEY_ESCAPE && param_action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(param_window, GL_TRUE);
    }

    if (param_key >= 0 && param_key < 1024)
    {
        if (param_action == GLFW_PRESS)
        {
            the_window->m_keys[param_key] = true;
            std::cout << "Pressed: " << param_key << std::endl;
        }

        else if (param_action == GLFW_RELEASE)
        {
            the_window->m_keys[param_key] = false;
            std::cout << "Released: " << param_key << std::endl;
        }
    }
}

void GLWindow::HandleMouse(
        GLFWwindow* param_window,
        double param_x_pos,
        double param_y_pos)
{
    GLWindow* the_window = static_cast<GLWindow*>(glfwGetWindowUserPointer(param_window));

    if (the_window->m_mouse_first_moved)
    {
        the_window->m_last_x = param_x_pos;
        the_window->m_last_y = param_y_pos;
        the_window->m_mouse_first_moved = false;
    }

    the_window->m_x_change = param_x_pos - the_window->m_last_x;
    the_window->m_y_change = the_window->m_last_y - param_y_pos;

    the_window->m_last_x = param_x_pos;
    the_window->m_last_y = param_y_pos;

    std::cout << "x: " << the_window->m_x_change << ", y: " << the_window->m_y_change << std::endl;
}

void GLWindow::CreateCallbacks()
{
    glfwSetKeyCallback(m_main_window, HandleKeys);
    glfwSetCursorPosCallback(m_main_window, HandleMouse);
}