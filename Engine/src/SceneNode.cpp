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
    
    void SceneNode::addNode(std::shared_ptr<SceneNode> sceneNode)
    {
        child.push_back(sceneNode);
    }
    
    bool SceneNode::removeNode(std::shared_ptr<SceneNode> sceneNode)
    {
        std::vector<std::shared_ptr<SceneNode>>::iterator it = std::remove_if(child.begin(), child.end(), [&](std::shared_ptr<SceneNode> node) {
            return node.get() == sceneNode.get();
        });
        return true;
    }
    
    bool SceneNode::removeNode(int index)
    {
        std::shared_ptr<SceneNode> node = nullptr;
        if (index >= 0 && index < child.size())
        {
            node = child[index];
            child.erase(child.begin() + index);
        }
        return true;
    }
    
    bool SceneNode::removeAll()
    {
        return true;
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