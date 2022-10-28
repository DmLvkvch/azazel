#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <streambuf>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"
#include "Texture.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Render.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 940;
const unsigned int SCR_HEIGHT = 560;

std::string readFile(const std::string& file)
{
    std::fstream stream (file);
    if (!stream.is_open()) {
        std::cout << "Could not open the file - '" << file << "'" << std::endl;
    }
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    static const GLfloat vertices[] = {
         0.0f  , 0.0      ,0.0f, 0 , 0,
         0.0f  , 200.0f   ,0.0f, 0 , 1,
         200.0f, 200.0f   ,0.0f, 1 , 1,
         200.0f, 0.0      ,0.0f, 1 , 0
    };

    glm::mat4 proj = glm::ortho(0.0f, 940.0f, 0.0f, 560.0f, -1.0f, 1.0f);
 
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    std::string vertCode = readFile("shaders/2d/default.vert.glsl");

    std::string fragCode = readFile("shaders/default.frag.glsl");

    Shader shader(vertCode, fragCode);

    unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, 6);

    VertexBufferLayout layout;
    layout.addFloat(3);
    layout.addFloat(2);

    va.addBuffer(vb, layout);

    Texture texture("images/cat.png");

    shader.bind();
    shader.setUniform1i("texture_0", 0);
    shader.setMatrix4f("mvp", proj);

    Render render;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    glm::vec3 translation(0, 0, 0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glm::mat4 mvp = proj * view * glm::translate(glm::mat4(1.0f), translation);;

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        shader.bind();
        shader.setMatrix4f("mvp", mvp);
        render.draw(va, ib, shader);
        ImGui::SliderFloat("Translation X", &translation.x, 0.0f, 940.0f);
        ImGui::SliderFloat("Translation Y", &translation.y, 0.0f, 560.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);            

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}