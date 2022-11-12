#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <streambuf>


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Mesh.h"
#include "Camera.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "imgui/ControllersWindow.h"
#include "events/Event.h"
#include "events/KeyEvent.h"
#include "events/ApplicationEvent.h"

#include <renderer/rhi/gl/GLESTexture.h>
#include <renderer/rhi/gl/GLESShader.h>
#include <renderer/rhi/gl/GLESIndexBuffer.h>
#include <renderer/rhi/gl/GLESVertexBuffer.h>
#include <renderer/rhi/gl/GLESVertexArray.h>
#include <renderer/rhi/gl/GLESVertexBufferLayout.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Azazel::Camera& camera);

const unsigned int SCR_WIDTH = 940;
const unsigned int SCR_HEIGHT = 560;

using namespace Azazel;

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
    Event* e = new AppTickEvent();
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
    float left = 1 * 200.0f;
    float top = 1 * 200.0f;
    float front = 1 * 200.0f;
    float bottom = 1 * 200.0f;
    float back = 1 * 200.0f;
    float right = 1 * 200.0f;

    std::vector<glm::vec3> positions = {
        glm::vec3(-left, top, front), // 0
        glm::vec3(-left, -bottom, front), // 1
        glm::vec3(-left, top, -back), // 2
        glm::vec3(-left, -bottom, -back), // 3
        glm::vec3(right, top, front), // 4
        glm::vec3(right, -bottom, front), // 5
        glm::vec3(right, top, -back), // 6
        glm::vec3(right, -bottom, -back), // 7
    };

    std::vector<glm::vec3> vertices;
    vertices.push_back(positions[4]);
    vertices.push_back(positions[2]);
    vertices.push_back(positions[0]);
    vertices.push_back(positions[2]);
    vertices.push_back(positions[7]);
    vertices.push_back(positions[3]);
    vertices.push_back(positions[6]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[7]);
    vertices.push_back(positions[1]);
    vertices.push_back(positions[7]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[0]);
    vertices.push_back(positions[3]);
    vertices.push_back(positions[1]);
    vertices.push_back(positions[4]);
    vertices.push_back(positions[1]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[4]);
    vertices.push_back(positions[6]);
    vertices.push_back(positions[2]);
    vertices.push_back(positions[2]);
    vertices.push_back(positions[6]);
    vertices.push_back(positions[7]);
    vertices.push_back(positions[6]);
    vertices.push_back(positions[4]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[1]);
    vertices.push_back(positions[3]);
    vertices.push_back(positions[7]);
    vertices.push_back(positions[0]);
    vertices.push_back(positions[2]);
    vertices.push_back(positions[3]);
    vertices.push_back(positions[4]);
    vertices.push_back(positions[0]);
    vertices.push_back(positions[1]);

    std::vector<glm::vec2> texC;

   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));
   texC.push_back(glm::vec2(1.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 1.0f));
   texC.push_back(glm::vec2(0.0f, 0.0f));


    std::vector<glm::vec3> normals;

    for (int i = 0; i < vertices.size(); i+=3)
    {
        glm::vec3& p1 = vertices[i + 0];
        glm::vec3& p2 = vertices[i + 1];
        glm::vec3& p3 = vertices[i + 2];
        glm::vec3 normal = glm::triangleNormal(p1, p2, p3);
        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }

    std::vector<unsigned int> indices;
    for (int i = 0; i < vertices.size(); i++)
    {
        indices.push_back(i);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    glm::vec3 rotation{};
    glm::vec3 scaleM {1.0f, 1.0f, 1.0f};
    glm::vec3 translation {};

    GLESTexture texture("images/cat.png");

    GLESIndexBuffer indexBuffer(indices.data(), indices.size());
    GLESVertexBuffer vertexBuffer(vertices.data(), sizeof(float) * vertices.size() * 3);
    GLESVertexBuffer vertexBufferT(texC.data(), sizeof(float) * texC.size() * 2);
    GLESVertexBuffer vertexBufferN(normals.data(), sizeof(float) * normals.size() * 3);


    GLESVertexArray vertexArray;
    GLESVertexBufferLayout vbo;
    vbo.add<float> (3);
    vertexArray.addBuffer(vertexBuffer, vbo);
    GLESVertexBufferLayout vbo1;
    vbo1.add<float> (2);
    vertexArray.addBuffer(vertexBufferT, vbo1, 1);
    GLESVertexBufferLayout vbo2;
    vbo2.add<float> (3);
    vertexArray.addBuffer(vertexBufferN, vbo2, 2);


    std::string vertCode = readFile("shaders/light/diffuse.light.vert.glsl");

    std::string fragCode = readFile("shaders/light/diffuse.light.frag.glsl");

    GLESShader shader(vertCode, fragCode);
    shader.bind();
    shader.setUniform1i("u_texture_0", 0);

    glm::mat4 projection = glm::ortho(0.0f, 900.0f, 0.0f, 600.0f, -1000.0f, 1000.0f);
    projection = glm::perspective(glm::radians(60.0f), 1.5f, 0.1f, 2000.0f);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1000.0f));
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glm::mat4 proj;
    glm::vec3 lightPos {0.0f, 0.0f, 500.0f};

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SliderFloat("Rotation X", &rotation.x, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation Y", &rotation.y, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation Z", &rotation.z, 0.0f, 360.0f);

        ImGui::SliderFloat("Scale X", &scaleM.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Scale Y", &scaleM.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Scale Z", &scaleM.z, -10.0f, 10.0f);

        ImGui::SliderFloat("Light pos", &lightPos.x, -500.0f, 500.0f);
    shader.setVec3f("u_lightPos", lightPos);


        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotY= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), scaleM);

        proj = projection * view * scale * rotX * rotY * rotZ;

        shader.setMatrix4f("u_mvp", proj);
        shader.setMatrix4f("u_model", scale * rotX * rotY * rotZ);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        texture.bind();
        vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.moveUp(10.0f / 10);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.moveUp(-10.0f / 10);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.moveRight(-10.0f / 10);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.moveRight(10.0f / 10);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera.moveForward(10.0f / 10);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        camera.moveForward(-10.0f / 10);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}