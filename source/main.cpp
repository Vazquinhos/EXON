#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ogl/shader.hpp"
#include "ogl/geometry.hpp"
#include "ogl/program.hpp"
#include "ogl/vertex.hpp"
#include "ogl/texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

using namespace exon::ogl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    TCHAR Buffer[MAX_PATH];
    DWORD dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
    std::string currentWorkingDirectory = Buffer;
    currentWorkingDirectory += "/../../data";

    if (!SetCurrentDirectory(currentWorkingDirectory.c_str()))
    {
        printf("SetCurrentDirectory failed (%d)\n", GetLastError());
        return 0;
    }

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		//std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

    Shader *vertexShader, *fragmentShader;
    if (!Shader::Read(GL_VERTEX_SHADER, "screen_position_color_uv.vert", &vertexShader) ||
        !Shader::Read(GL_FRAGMENT_SHADER, "screen_position_color_uv.frag", &fragmentShader))
    {
        return -1;
    }
    
    Texture* texture;
    if (!Texture::Read(GL_TEXTURE_2D, "textures/Tiles_Azulejos_004a_COLOR.jpg", &texture))
    {
        return -1;
    }

    Program * program = new Program(std::vector<Shader*>{vertexShader, fragmentShader});

    Geometry::Attribute positionAttribute { 3, 0, false };
    Geometry::Attribute colorAttribute{ 3, 3, false };
    Geometry::Attribute uvAttribute{ 2, 6, false };
    
    std::vector<float> vertices =
    {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,      0.0f, 0.0f, 1.0f,      0.5f, 1.0f,
    };

    Geometry* geometry = new Geometry(vertices, 8, std::vector<Geometry::Attribute>{positionAttribute , colorAttribute, uvAttribute});
    geometry->Create();

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        // Bind all data 
        program->Bind();
        texture->Bind();
        geometry->Bind();

        // Draw our geometry
        geometry->Draw();

        geometry->Unbind();
        //program->UnBind();

		glfwSwapBuffers(window);
        glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}