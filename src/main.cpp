#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"
#include "mesh.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool wireframe = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        wireframe = !wireframe;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    Vertex quad;

	//vertex data
    quad.position = {
        -0.5f,  0.5f, 0.0f,  // top-left 
         0.5f,  0.5f, 0.0f,  // top-right
		-0.5f, -0.5f, 0.0f,  // bottom-left
		 0.5f, -0.5f, 0.0f,  // bottom-right
    };
    quad.color = {
        1.0f, 0.0f, 0.0f, // top-left
        0.0f, 1.0f, 0.0f, // top-right
        0.0f, 0.0f, 1.0f, // bottom-left
		1.0f, 1.0f, 0.0f  // bottom-right
	};
    quad.texCoords = {
        0.0f, 1.0f, // top-left
        1.0f, 1.0f, // top-right
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f  // bottom-right
	};
    quad.indices = {
        0, 1, 2,   // first triangle
        1, 2, 3   // second triangle
    };
	Mesh quadMesh(quad);

    //build and compile our shader program
    Shader defaultShader("shaders/defaultShader.VS.glsl", "shaders/defaultShader.FS.glsl");

    //build and compile our texture
    Texture containerTexture("textures/container.jpg");
    Texture awesomefaceTexture("textures/awesomeface.png");

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
		if (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // we do stuff
		defaultShader.use();
		float timeValue = glfwGetTime();

		containerTexture.bind(0);
		awesomefaceTexture.bind(1);

		glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(defaultShader.ID, "transform");

		defaultShader.setMat4("transform", transform);
		defaultShader.setFloat("time", timeValue);
		defaultShader.setInt("texture1", 0);
		defaultShader.setInt("texture2", 1);
		
		quadMesh.draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}