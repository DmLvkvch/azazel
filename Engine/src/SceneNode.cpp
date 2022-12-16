#include "SceneNode.h"

#include <algorithm>

namespace Azazel
{
    SceneNode::SceneNode(float width, float height)
    {

    }
    
    SceneNode::~SceneNode()
    {

    }
    
    void SceneNode::addNode(SceneNode* sceneNode)
    {
        child.push_back(sceneNode);

    }
    
    bool SceneNode::removeNode(SceneNode* sceneNode)
    {
        std::remove_if(child.begin(), child.end(), [&](SceneNode* node) {
            return node == sceneNode;
        });
        return sceneNode;
    }
    
    bool SceneNode::removeNode(int index)
    {
        SceneNode* node = nullptr;
        if (index >= 0 && index < child.size())
        {
            node = child[index];
            child.erase(child.begin() + index);
        }
        return node;
    }
    
    bool SceneNode::removeAll()
    {

    }

    void SceneNode::setScale(glm::vec2 scale)
    {
        this->scale.x = scale.x;
        this->scale.y = scale.y;
    }

    void SceneNode::setRotation(float rotation)
    {
        this->rotation.x = rotation;
    }
    
    void SceneNode::setPosition(glm::vec2 position)
    {
        this->position.x = position.x;
        this->position.y = position.y;
    }
}