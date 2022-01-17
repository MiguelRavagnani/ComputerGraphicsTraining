#include <string.h>

#include "shader.h"

Shader::Shader()
    : m_shader_id (0),
      m_uniform_model (0),
      m_uniform_projection (0),
      m_point_light_count (0) {}

Shader::~Shader()
{
    this->ClearShader();
}

void Shader::CreateFromString(
    const char* param_vertex_code,
    const char* param_fragment_code)
{
    CompileShader(param_vertex_code, param_fragment_code);
}

void Shader::CreateFromFile(
    const char* param_vertex_location,
    const char* param_fragment_location)
{
    std::string vertex_string = ReadFile(param_vertex_location);
    std::string fragment_string = ReadFile(param_fragment_location);

    const char* vertex_code = vertex_string.c_str();
    const char* fragment_code = fragment_string.c_str();

    CompileShader(vertex_code, fragment_code);
}

std::string Shader::ReadFile(const char* param_file_path)
{
    std::string file_content;
    std::ifstream file_stream(param_file_path, std::ios::in);

    if (!file_stream.is_open())
    {
        std::cerr << "Failed to read " << param_file_path << "!. File doesn't exist" << std::endl;
        return "";
    }

    std::string line = "";

    while (!file_stream.eof())
    {
        std::getline(file_stream, line);
        file_content.append(line + "\n");
    }

    file_stream.close();
    return file_content;
}

void Shader::UseShader()
{
    glUseProgram(m_shader_id);
}

void Shader::ClearShader()
{
    if (m_shader_id != 0)
    {
        glDeleteProgram(m_shader_id);
        m_shader_id = 0;
    }

    m_uniform_model = 0;
    m_uniform_projection = 0;
}

void Shader::CompileShader(
        const char* param_vertex_code,
        const char* param_fragment_code)
{
    m_shader_id = glCreateProgram();

    if (!m_shader_id)
    {
        std::cerr << "Error creating shader program!" << std::endl;
        return;
    }

    AddShader(m_shader_id, param_vertex_code, GL_VERTEX_SHADER);
    AddShader(m_shader_id, param_fragment_code, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(m_shader_id);
    glGetProgramiv(m_shader_id, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_shader_id, sizeof(eLog), NULL, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return;
    }

    glValidateProgram(m_shader_id);
    glGetProgramiv(m_shader_id, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_shader_id, sizeof(eLog), NULL, eLog);
        std::cerr << "Error validating program: " << eLog << std::endl;
        return;
    }

    m_uniform_model = glGetUniformLocation(m_shader_id, "model");
    m_uniform_projection = glGetUniformLocation(m_shader_id, "projection");
    m_uniform_view = glGetUniformLocation(m_shader_id, "view");
    m_uniform_directional_light.m_uniform_color = glGetUniformLocation(m_shader_id, "directional_light.base.color");
    m_uniform_directional_light.m_uniform_ambient_intensity = glGetUniformLocation(m_shader_id, "directional_light.base.ambient_intensity");
    m_uniform_directional_light.m_uniform_direction = glGetUniformLocation(m_shader_id, "directional_light.direction");
    m_uniform_directional_light.m_uniform_diffuse_intensity = glGetUniformLocation(m_shader_id, "directional_light.base.diffuse_intensity");
    m_uniform_specular_intensity = glGetUniformLocation(m_shader_id, "material.specular_intensity");
    m_uniform_shininess = glGetUniformLocation(m_shader_id, "material.shininess");
    m_uniform_eye_position = glGetUniformLocation(m_shader_id, "eye_position");
    m_uniform_point_light_count = glGetUniformLocation(m_shader_id, "point_light_count");

    for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        char location_buffer[100] = {'\0'};

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].base.color", i);
        m_uniform_point_light[i].m_uniform_color = glGetUniformLocation(m_shader_id, location_buffer);
        
        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].base.ambient_intensity", i);
        m_uniform_point_light[i].m_uniform_ambient_intensity = glGetUniformLocation(m_shader_id, location_buffer);
        
        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].base.diffuse_intensity", i);
        m_uniform_point_light[i].m_uniform_diffuse_intensity = glGetUniformLocation(m_shader_id, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].position", i);
        m_uniform_point_light[i].m_uniform_position = glGetUniformLocation(m_shader_id, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].constant", i);
        m_uniform_point_light[i].m_uniform_constant = glGetUniformLocation(m_shader_id, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].linear", i);
        m_uniform_point_light[i].m_uniform_linear = glGetUniformLocation(m_shader_id, location_buffer);

        snprintf(location_buffer, sizeof(location_buffer), "point_lights[%d].exponent", i);
        m_uniform_point_light[i].m_uniform_exponent = glGetUniformLocation(m_shader_id, location_buffer);
    }
}

void Shader::SetDirectionalLight(DirectionalLight* param_directional_light)
{
    param_directional_light->UseLight(
        m_uniform_directional_light.m_uniform_ambient_intensity,
        m_uniform_directional_light.m_uniform_color,
        m_uniform_directional_light.m_uniform_diffuse_intensity,
        m_uniform_directional_light.m_uniform_direction);
}

void Shader::SetPointLights(PointLight* param_point_light, unsigned int param_light_count)
{
    if (param_light_count > MAX_POINT_LIGHTS)
    {
        param_light_count = MAX_POINT_LIGHTS;
    }

    glUniform1i(m_uniform_point_light_count, param_light_count);

    for (size_t i = 0; i < param_light_count; i++)
    {
        param_point_light[i].UseLight(
            m_uniform_point_light[i].m_uniform_ambient_intensity,
            m_uniform_point_light[i].m_uniform_color,
            m_uniform_point_light[i].m_uniform_diffuse_intensity,
            m_uniform_point_light[i].m_uniform_position,
            m_uniform_point_light[i].m_uniform_constant,
            m_uniform_point_light[i].m_uniform_linear,
            m_uniform_point_light[i].m_uniform_exponent);
    }
}

void Shader::AddShader(
        GLuint param_the_program, 
        const char* param_shader_code,
        GLenum param_shader_type)
{
    GLuint theShader = glCreateShader(param_shader_type);

    const GLchar* theCode[1];
    theCode[0] = param_shader_code;

    GLint codeLenght[1];
    codeLenght[0] = strlen(param_shader_code);

    glShaderSource(theShader, 1, theCode, codeLenght);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        std::cerr << "Error compiling the " << param_shader_type << " shader! Error: "<< eLog <<std::endl;
        return;
    }

    glAttachShader(param_the_program, theShader);
}

GLuint Shader::GetProjectionLocation() {return m_uniform_projection;}

GLuint Shader::GetModelLocation() {return m_uniform_model;}

GLuint Shader::GetViewLocation() {return m_uniform_view;}

GLuint Shader::GetAmbientIntensityLocation(){return m_uniform_directional_light.m_uniform_ambient_intensity;}

GLuint Shader::GetAmbientColorLocation(){return m_uniform_directional_light.m_uniform_color;}

GLuint Shader::GetDiffuseIntensityLocation(){return m_uniform_directional_light.m_uniform_diffuse_intensity;}

GLuint Shader::GetDirectionLocation(){return m_uniform_directional_light.m_uniform_direction;}

GLuint Shader::GetSpecularIntensityLocation(){return m_uniform_specular_intensity;}

GLuint Shader::GetShininessLocation(){return m_uniform_shininess;}

GLuint Shader::GetEyePositionLocation(){return m_uniform_eye_position;}