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

#include <Mesh.h>
#include "Render.h"
#include "Camera.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "imgui/ControllersWindow.h"

#include "FrameBuffer.h"

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

    float vertices[] = {
         0.0f  , 0.0      ,0.0f,
         0.0f  , 200.0f   ,0.0f,
         200.0f, 200.0f   ,0.0f,
         200.0f, 0.0      ,0.0f,

         0.0f  , 0.0      ,-200.0f,
         0.0f  , 200.0f   ,-200.0f,
         200.0f, 200.0f   ,-200.0f,
         200.0f, 0.0      ,-200.0f,

         0.0f  , 0.0      ,0.0f,
         0.0f  , 200.0f   ,0.0f,
         0.0f, 200.0f     ,-200.0f,
         0.0f, 0.0        ,-200.0f,

         200.0f  , 0.0      ,0.0f,
         200.0f  , 200.0f   ,0.0f,
         200.0f, 200.0f     ,-200.0f,
         200.0f, 0.0        ,-200.0f,

         0.0f  , 200.0      ,0.0f,
         0.0f  , 200.0f     ,-200.0f,
         200.0f, 200.0f     ,-200.0f,
         200.0f, 200.0      ,0.0f,

         0.0f  , 0.0      ,0.0f,
         0.0f  , 0.0f     ,-200.0f,
         200.0f, 0.0f     ,-200.0f,
         200.0f, 0.0      ,0.0f
    };

    float texC[] = {
                    0 , 0,
                    0 , 1,
                    1 , 1,
                    1 , 0,

                    0 , 0,
                    0 , 1,
                    1 , 1,
                    1 , 0,

                    0 , 0,
                    0 , 1,
                    1 , 1,
                    1 , 0,

                    0 , 0,
                    0 , 1,
                    1 , 1,
                    1 , 0,

                    0 , 0,
                    0 , 1,
                    1 , 1,
                    1 , 0,

                    0 , 0,
                    0 , 1,
                    1 , 1,
                    1 , 0
                };

    float normals[] = {
            0 , 0, 1,
            0 , 0, 1,
            0 , 0, 1,
            0 , 0, 1,

            0 , 0, -1,
            0 , 0, -1,
            0 , 0, -1,
            0 , 0, -1,

            -1 , 0, 0,
            -1 , 0, 0,
            -1 , 0, 0,
            -1 , 0, 0,

            1 , 0, 0,
            1 , 0, 0,
            1 , 0, 0,
            1 , 0, 0,

            0 , 1, 0,
            0 , 1, 0,
            0 , 1, 0,
            0 , 1, 0,

            0 , -1, 0,
            0 , -1, 0,
            0 , -1, 0,
            0 , -1, 0
    };

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 1000.0f);
    //glm::mat4 projection = glm::ortho(0.0f, 940.0f, 0.0f, 560.0f, -100.0f, 100.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 200.0f));

    std::string vertCode = readFile("shaders/light/diffuse.light.vert.glsl");

    std::string fragCode = readFile("shaders/light/diffuse.light.frag.glsl");

    Shader shader(vertCode, fragCode);

    unsigned int indices[36] = { 0, 1, 2, 0, 2, 3,
                                4, 5, 6, 4, 6, 7,
                                8, 9, 10, 8, 10, 11,
                                12, 13, 14, 12, 14, 15,
                                16, 17, 18, 16, 18, 19,
                                20, 21, 22, 20, 22, 23,
                                };

    std::vector<float> norms;

    for (int i = 0; i < 36; i+=3)
    {
        float a = vertices[3 * indices[i] + 0];
        float b = vertices[3 * indices[i] + 1];
        float c = vertices[3 * indices[i] + 2];
        
        glm::vec3 A(a, b, c);

        a = vertices[3 * indices[i + 1] + 0];
        b = vertices[3 * indices[i + 1] + 1];
        c = vertices[3 * indices[i + 1] + 2];

        glm::vec3 B(a, b, c);

        a = vertices[3 * indices[i + 2] + 0];
        b = vertices[3 * indices[i + 2] + 1];
        c = vertices[3 * indices[i + 2] + 2];

        glm::vec3 C(a, b, c);

        glm::vec3 n = glm::normalize(glm::cross(B - A, C - A));

        norms.push_back(n.x);
        norms.push_back(n.y);
        norms.push_back(n.z);

        norms.push_back(n.x);
        norms.push_back(n.y);
        norms.push_back(n.z);
    }


    Mesh mesh = Mesh::genQuadMesh(0.0f, 0.0f, -100.0f, 300.0f, 300.0f);

    VertexArray va;
   // VertexBuffer vb(mesh.vertices.data(), sizeof (float) * mesh.vertices.size());
   // IndexBuffer ib(mesh.indices.data(), mesh.indices.size());
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBuffer vbt(texC, sizeof(texC));
    VertexBuffer vbn(normals, sizeof(normals));
    IndexBuffer ib(indices, 36);

    VertexBufferLayout layout;
    layout.addFloat(3);
    va.addBuffer(vb, layout);
    VertexBufferLayout cl;
    cl.addFloat(2);
    va.addBuffer(vbt, cl, 1);

    VertexBufferLayout cn;
    cn.addFloat(3);
    va.addBuffer(vbn, cn, 2);

    Texture texture("images/cat.png");
    shader.bind();
    shader.setUniform1i("texture_0", 0);

    Render render;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    Camera camera;
    glEnable(GL_DEPTH_TEST);
    ControllerWindow c;

    glm::vec3 lightPos(0.0, 0.0, 0.0);
    shader.setMatrix4f("model", model);

    FrameBuffer frameBuffer;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, camera);
        //frameBuffer.bind();
        render.clear();

        glm::mat4 mvp = projection * camera.getViewLookAtMatrix() * model;
        texture.bind();
        shader.bind();
        shader.setMatrix4f("mvp", mvp);
        shader.setVec3f("lightPos", lightPos);
        render.draw(va, ib, shader);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SliderFloat("Translation X", &lightPos.x, 0.0f, 940.0f);
        ImGui::SliderFloat("Translation Y", &lightPos.y, 0.0f, 560.0f);
        ImGui::SliderFloat("Translation Z", &lightPos.z, 0.0f, 560.0f);


        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
     //   frameBuffer.bind();
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