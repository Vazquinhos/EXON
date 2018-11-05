#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ogl/shader.hpp"
#include "ogl/geometry.hpp"
#include "ogl/program.hpp"
#include "ogl/vertex.hpp"

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

    const std::string vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 Color;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   Color = aColor;\n"
        "}\0";

    const std::string fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 Color;\n"
        "void main()\n"
        "{\n"
        "   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "   FragColor = vec4(Color.rgb, 1.0f);\n"
        "}\n\0";

    Shader * vertexShader = new VertexShader(vertexShaderSource.c_str(), vertexShaderSource.length());
    Shader * fragmentShader = new FragmentShader(fragmentShaderSource.c_str(), fragmentShaderSource.length());
    Program * program = new Program(std::vector<Shader*>{vertexShader, fragmentShader});

    Geometry::Attribute positionAttribute { 3, 0, false };
    Geometry::Attribute colorAttribute{ 3, 3, false };
    
    std::vector<float> vertices =
    {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    };

    Geometry* geometry = new Geometry(vertices, 6, std::vector<Geometry::Attribute>{positionAttribute , colorAttribute});

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        // Bind all data 
        program->Bind();
        geometry->Bind();

        // Draw our geometry
        geometry->Draw();

		glfwSwapBuffers(window);
        glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}