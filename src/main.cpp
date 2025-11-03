#include <GLFW/glfw3.h>
#include <iostream>

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool wireframe = false;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        wireframe = !wireframe;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam) return;

    static bool firstMouse = true;
    static float lastX = SCR_WIDTH / 2.0f;
    static float lastY = SCR_HEIGHT / 2.0f;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    
    cam->ProcessMouseMovement(xoffset, yoffset);
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
    glfwSetWindowUserPointer(window, &camera);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	glEnable(GL_DEPTH_TEST);

    //build and compile our shader program
    Shader defaultShader("shaders/defaultShader.VS.glsl", "shaders/defaultShader.FS.glsl");

    //build and compile our texture
    Texture containerTexture("textures/container.jpg");
    Texture awesomefaceTexture("textures/awesomeface.png");

    Vertex cube;

	//vertex data
    cube.position = {
        // Front face
        -0.5f,  0.5f,  0.5f,  // top-left
         0.5f,  0.5f,  0.5f,  // top-right
        -0.5f, -0.5f,  0.5f,  // bottom-left
         0.5f, -0.5f,  0.5f,  // bottom-right

        // Back face
         0.5f,  0.5f, -0.5f,  // top-left
        -0.5f,  0.5f, -0.5f,  // top-right
         0.5f, -0.5f, -0.5f,  // bottom-left
        -0.5f, -0.5f, -0.5f,  // bottom-right

        // Left face
        -0.5f,  0.5f, -0.5f,  // top-left
        -0.5f,  0.5f,  0.5f,  // top-right
        -0.5f, -0.5f, -0.5f,  // bottom-left
        -0.5f, -0.5f,  0.5f,  // bottom-right

        // Right face
        0.5f,  0.5f,  0.5f,  // top-left
        0.5f,  0.5f, -0.5f,  // top-right
        0.5f, -0.5f,  0.5f,  // bottom-left
        0.5f, -0.5f, -0.5f,  // bottom-right

        // Top face
        -0.5f,  0.5f, -0.5f,  // top-left
         0.5f,  0.5f, -0.5f,  // top-right
        -0.5f,  0.5f,  0.5f,  // bottom-left
         0.5f,  0.5f,  0.5f,  // bottom-right

        // Bottom face
        -0.5f, -0.5f,  0.5f,  // top-left
         0.5f, -0.5f,  0.5f,  // top-right
        -0.5f, -0.5f, -0.5f,  // bottom-left
         0.5f, -0.5f, -0.5f   // bottom-right
    };

    cube.color = {
        // Front
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        // Back
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        // Left
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        // Right
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        // Top
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        // Bottom
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f
    };

    cube.texCoords = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };

    cube.indices = {
        0, 1, 2,  1, 3, 2,        // Front face
        4, 5, 6,  5, 7, 6,        // Back face
        8, 9,10,  9,11,10,        // Left face
       12,13,14, 13,15,14,        // Right face
       16,17,18, 17,19,18,        // Top face
	   20,21,22, 21,23,22         // Bottom face
    };

	Mesh cubeMesh(cube);

    defaultShader.use();

    defaultShader.setInt("texture1", 0);
    defaultShader.setInt("texture2", 1);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);
        glfwSetKeyCallback(window, key_callback);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);

        // camera input
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        // render
		if (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // we do stuff
        defaultShader.use();
		float timeValue = glfwGetTime();

		// create transformations
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);
		int modelLoc = glGetUniformLocation(defaultShader.ID, "model");

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        for (unsigned int i = 0; i < 10; i++) {
			float angle = 20.0f * i + (timeValue * 50.0f);

            glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            defaultShader.setMat4("model", model);
            cubeMesh.draw();
        }

		defaultShader.setMat4("view", view);
		defaultShader.setMat4("projection", projection);

		defaultShader.setFloat("time", timeValue);

        containerTexture.bind(0);
        awesomefaceTexture.bind(1);

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