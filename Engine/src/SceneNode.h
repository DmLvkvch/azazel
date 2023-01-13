#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <memory>

namespace Azazel
{
    class SceneNode
    {
    public:
        SceneNode(float width = 0, float height = 0);
        virtual ~SceneNode();
        void addNode(std::shared_ptr<SceneNode> sceneNode);
        bool removeNode(std::shared_ptr<SceneNode> sceneNode);
        bool removeNode(int index);
        bool removeAll();
        void setScale(glm::vec2 scale);
        void setRotation(float rotation);
        void setPosition(glm::vec2 position);
        void onUpdate(float delta);
        void draw();
        glm::mat4 getLocalMatrix();
        glm::mat4 updateMatrix();
    private:
        std::vector<std::shared_ptr<SceneNode>> child;
        SceneNode* parent;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        float width;
        float height;
        bool matrixDirty;
    };
}