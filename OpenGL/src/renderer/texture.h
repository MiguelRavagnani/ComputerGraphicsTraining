#ifndef _TEXTURE_
#define _TEXTURE_

#include <iostream>

#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
public:
    Texture();
    Texture(const char* param_file_location);
    ~Texture();

    bool LoadTexture();
    bool LoadTextureAlpha();

    void UseTexture();
    void ClearTexture();


private:
    GLuint m_texture_id;
    int m_width;
    int m_height;
    int m_depth;

    const char* m_file_location;
};


#endif //_TEXTURE_