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
        sceneNode->parent = this;
    }
    
    bool SceneNode::removeNode(std::shared_ptr<SceneNode> sceneNode)
    {
        return false;
    }
    
    bool SceneNode::removeNode(int index)
    {
        return false;
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

    void SceneNode::onUpdate(float delta)
    {
        
    }

    void SceneNode::draw()
    {

    }

    glm::mat4 SceneNode::getLocalMatrix()
    {
        glm::mat4 localMatrix(1.0f);
        localMatrix *= glm::translate(glm::mat4(1.0f), position);
        localMatrix *= glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(0.0f, 0.0f, 1.0f));
        localMatrix *= glm::scale(glm::mat4(1.0f), scale);
        return localMatrix;
    }

    glm::mat4 SceneNode::updateMatrix()
    {
        glm::mat4 globalMatrix(1.0f);
        if (parent)
        {
            globalMatrix = parent->updateMatrix() * getLocalMatrix();
        }
        else
        {
            globalMatrix = getLocalMatrix();
        }
        return globalMatrix;
    }
}