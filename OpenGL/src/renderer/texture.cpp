#include "texture.h"

Texture::Texture()
    : m_width (0),
      m_height (0),
      m_depth (0),
      m_file_location (""){}

Texture::Texture(const char* param_file_location)
    : m_width (0),
      m_height (0),
      m_depth (0),
      m_file_location (param_file_location){}

Texture::~Texture()
{
    ClearTexture();
}

bool Texture::LoadTexture()
{
    unsigned char *tex_data = stbi_load(m_file_location, &m_width, &m_height, &m_depth, 0);
    if (!tex_data)
    {
        std::cerr << "Failed to find path " << m_file_location << std::endl;
        return false;
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGB, 
        m_width, 
        m_height, 
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE, 
        tex_data);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(tex_data);

    return true;
}

bool Texture::LoadTextureAlpha()
{
    unsigned char *tex_data = stbi_load(m_file_location, &m_width, &m_height, &m_depth, 0);
    if (!tex_data)
    {
        std::cerr << "Failed to find path " << m_file_location << std::endl;
        return false;
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        m_width, 
        m_height, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        tex_data);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(tex_data);

    return true;
}

void Texture::UseTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::ClearTexture()
{
    glDeleteTextures(1, &m_texture_id);
    m_texture_id = 0;
    m_width = 0;
    m_height = 0;
    m_depth = 0;
    m_file_location = "";
}
