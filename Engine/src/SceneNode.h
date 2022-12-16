#pragma once

#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Azazel
{
    class SceneNode
    {
    public:
        SceneNode(float width = 0, float height = 0);
        virtual ~SceneNode();
        void addNode(SceneNode* sceneNode);
        bool removeNode(SceneNode* sceneNode);
        bool removeNode(int index);
        bool removeAll();
        void setScale(glm::vec2 scale);
        void setRotation(float rotation);
        void setPosition(glm::vec2 position);
        void draw();
    private:
        std::vector<SceneNode*> child;
        SceneNode* parent;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        float width;
        float height;
        bool matrixDirty;
    };
}