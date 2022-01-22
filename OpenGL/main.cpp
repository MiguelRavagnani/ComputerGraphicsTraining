/* g++ main.cpp mesh.cpp shader.cpp gl_window.cpp camera.cpp texture.cpp light.cpp directional_light.cpp point_light.cpp material.cpp -lGL -lGLEW -lglfw -o exe*/
/* glm::mat4 model = glm::mat4(1.0f)*/
/* glm::mat4 model(1.0f)*/
#define STB_IMAGE_IMPLEMENTATION

#include <string.h>

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_window.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "common_values.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"
#include "material.h"

GLWindow main_window;
std::vector<Mesh* > mesh_list;
std::vector<Shader* > shader_list;
Camera main_camera;

Texture brick_texture;
Texture dirt_texture;
Texture plain_texture;

Material shiny_material;
Material rough_material;

DirectionalLight main_light;
PointLight point_lights[MAX_POINT_LIGHTS];
SpotLight spot_lights[MAX_SPOT_LIGHTS];

GLfloat delta_time = 0.0f;
GLfloat last_time = 0.0f;

/* Vertex shader*/
static const char* vertex_shader = "../shaders/vs.glsl";

/* Fragment shader*/
static const char* fragment_shader = "../shaders/fs.glsl";

void CalcAverageNormals(
    unsigned int* param_indices, 
    unsigned int param_indice_count, 
    GLfloat* param_vertices,
    unsigned int param_vertice_count,
    unsigned int param_vertex_lenght,
    unsigned int param_normal_offset)
{
    for (size_t i = 0; i < param_indice_count; i+=3)
    {
        /* Calculating the indexes of vertices. If the vertex
         * lenght is 3, each of the 'inx' will point to the
         * first vertex in a set of 3.*/
        unsigned int in0 = param_indices[i] * param_vertex_lenght;
        unsigned int in1 = param_indices[i + 1] * param_vertex_lenght;
        unsigned int in2 = param_indices[i + 2] * param_vertex_lenght;

        /* Finds lines between vertices*/
        glm::vec3 v1(
            param_vertices[in1] - param_vertices[in0],         /* subtracts the x Value of each set o vertices*/
            param_vertices[in1 + 1] - param_vertices[in0 + 1], /* subtracts the y Value of each set o vertices*/
            param_vertices[in1 + 2] - param_vertices[in0 + 2]);/* subtracts the z Value of each set o vertices*/

        glm::vec3 v2(
            param_vertices[in2] - param_vertices[in0],         /* subtracts the x Value of each set o vertices*/
            param_vertices[in2 + 1] - param_vertices[in0 + 1], /* subtracts the y Value of each set o vertices*/
            param_vertices[in2 + 2] - param_vertices[in0 + 2]);/* subtracts the z Value of each set o vertices*/

        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        /* Index jumps to the first normal vertex value*/
        in0 += param_normal_offset;
        in1 += param_normal_offset;
        in2 += param_normal_offset;

        param_vertices[in0] += normal.x;
        param_vertices[in0 + 1] += normal.y;
        param_vertices[in0 + 2] += normal.z;

        param_vertices[in1] += normal.x;
        param_vertices[in1 + 1] += normal.y;
        param_vertices[in1 + 2] += normal.z;

        param_vertices[in2] += normal.x;
        param_vertices[in2 + 1] += normal.y;
        param_vertices[in2 + 2] += normal.z;
    }

    for(size_t i = 0; i < param_vertice_count/param_vertex_lenght; i++)
    {
        unsigned int individual_normal_offset = i * param_vertex_lenght + param_normal_offset;

        glm::vec3 vec(
            param_vertices[individual_normal_offset],
            param_vertices[individual_normal_offset + 1],
            param_vertices[individual_normal_offset + 2]);
        
        vec = glm::normalize(vec);

        param_vertices[individual_normal_offset] = vec.x;
        param_vertices[individual_normal_offset + 1] = vec.y;
        param_vertices[individual_normal_offset + 2] = vec.z;
    }
}

void CreateObjects()
{
    unsigned int indices[] = 
    {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1 ,2
    };

    GLfloat vertices[] = {
    /*  x        y        z          u       v          nx      ny      nz   */
        -1.0f,  -1.0f,   -0.6f,      0.0f,   0.0f,      0.0f,   0.0f,   0.0f,
         0.0f,  -1.0f,    1.0f,      0.5f,   0.0f,      0.0f,   0.0f,   0.0f,
         1.0f,  -1.0f,   -0.6f,      1.0f,   0.0f,      0.0f,   0.0f,   0.0f,
         0.0f,   1.0f,    0.0f,      0.5f,   1.0f,      0.0f,   0.0f,   0.0f,
    };

    unsigned int floor_indices[] = 
    {
        0, 2, 1,
        1, 2, 3
    };

    GLfloat floor_vertices[] = {
    /*  x        y        z           u        v           nx       ny      nz   */
        -10.0f,  0.0f,   -10.0f,       0.0f,    0.0f,      0.0f,   -1.0f,   0.0f,
         10.0f,  0.0f,   -10.0f,      10.0f,    0.0f,      0.0f,   -1.0f,   0.0f,
        -10.0f,  0.0f,    10.0f,       0.0f,   10.0f,      0.0f,   -1.0f,   0.0f,
         10.0f,  0.0f,    10.0f,      10.0f,   10.0f,      0.0f,   -1.0f,   0.0f,
    };

    CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Mesh* object_1 = new Mesh();
    object_1->CreateMesh(vertices, indices, 32, 12);
    mesh_list.push_back(object_1);

    Mesh* object_2 = new Mesh();
    object_2->CreateMesh(vertices, indices, 32, 12);
    mesh_list.push_back(object_2);

    Mesh* object_3 = new Mesh();
    object_3->CreateMesh(floor_vertices, floor_indices, 32, 6);
    mesh_list.push_back(object_3);
}

void CreateShaders()
{
    Shader* shader_1 = new Shader();
    shader_1->CreateFromFile(vertex_shader, fragment_shader);
    shader_list.push_back(shader_1);
}

int main()
{
    main_window = GLWindow(800, 600);
    main_window.Initialize();

    CreateObjects();
    CreateShaders();

    main_camera = Camera(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        0.0f,
        3.0f,
        0.5f);

    brick_texture = Texture("../textures/brick.png");
    brick_texture.LoadTexture();

    dirt_texture = Texture("../textures/dirt.png");
    dirt_texture.LoadTexture();

    plain_texture = Texture("../textures/plain.png");
    plain_texture.LoadTexture();

    shiny_material = Material(2.0f, 256);
    rough_material = Material(0.3f, 2);

    main_light = DirectionalLight(
        1.0f, 1.0f, 1.0f, 
        0.1f, 0.1f, 
        0.0f, 0.0f, -1.0f);

    unsigned int point_light_count = 0;

    point_lights[0] = PointLight(
        0.9f, 0.2f, 0.3f,
        0.0f, 2.0f,
        -4.0f, 2.0f, 0.0f,
        0.3f, 0.2f, 0.1f);

    point_light_count++;

    point_lights[1] = PointLight(
        0.0f, 0.4f, 0.9f,
        0.0f, 1.0f,
        4.0f, 0.0f, 0.0f,
        0.0f, 0.2f, 0.1f);

    point_light_count++;

    unsigned int spot_light_count = 0;

    spot_lights[0] = SpotLight(
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        20.0f);

    spot_light_count++;

    GLuint uniform_ambient_intensity = 0;
    GLuint uniform_ambinet_color = 0;

    GLuint uniform_direction = 0;
    GLuint uniform_diffuse_intensity = 0;

    GLuint uniform_model = 0;
    GLuint uniform_projection = 0;
    GLuint uniform_view = 0;

    GLuint uniform_eye_position = 0;
    GLuint uniform_specular_intensity = 0;
    GLuint uniform_shininess = 0;

    glm::mat4 projection = glm::perspective(
        45.0f,
        (GLfloat)main_window.GetBufferWidth()/(GLfloat)main_window.GetBufferHeight(),
        0.1f,
        100.0f);

    /* Loop until closed*/
    while (!main_window.GetShouldClose())
    {
        GLfloat now = glfwGetTime();
        delta_time = now - last_time;
        last_time = now;

        /* Get and handle input events*/
        glfwPollEvents();

        main_camera.KeyControl(main_window.GetKeys(), delta_time);
        main_camera.MouseControl(main_window.GetXChange(), main_window.GetYChange());

        /* Clear window*/
        glClearColor(0.10f, 0.09f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Use the basic fragment and vertex shader for the 
         * shader list index 0*/
        shader_list[0]->UseShader();

        uniform_model = shader_list[0]->GetModelLocation();
        uniform_projection = shader_list[0]->GetProjectionLocation();
        uniform_view = shader_list[0]->GetViewLocation();
        
        uniform_eye_position = shader_list[0]->GetEyePositionLocation();
        uniform_specular_intensity = shader_list[0]->GetSpecularIntensityLocation();
        uniform_shininess = shader_list[0]->GetShininessLocation();

        spot_lights[0].SetFlash(
            main_camera.GetCameraPosition(),
            main_camera.GetCameraDirection());

        /* Sets up the uniforms inside the method*/
        shader_list[0]->SetDirectionalLight(&main_light);
        shader_list[0]->SetPointLights(point_lights, point_light_count);
        shader_list[0]->SetSpotLights(spot_lights, spot_light_count);

        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(main_camera.CalculateViewMatrix()));
        glUniform3f(
            uniform_eye_position, 
            main_camera.GetCameraPosition().x,
            main_camera.GetCameraPosition().y,
            main_camera.GetCameraPosition().z);

        glm::mat4 model = glm::mat4(1.0f);
       
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));

        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        shiny_material.UseMaterial(uniform_specular_intensity, uniform_shininess);
        brick_texture.UseTexture();

        mesh_list[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.4f, 1.4f, -2.5f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        rough_material.UseMaterial(uniform_specular_intensity, uniform_shininess);
        dirt_texture.UseTexture();

        mesh_list[1]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        shiny_material.UseMaterial(uniform_specular_intensity, uniform_shininess);
        dirt_texture.UseTexture();

        mesh_list[2]->RenderMesh();

        glUseProgram(0);

        main_window.SwapBuffers();
    }
    
    mesh_list[0]->ClearMesh();

    glfwTerminate();
    return 0;
}