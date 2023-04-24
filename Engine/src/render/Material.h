#pragma once

#include <glm/vec3.hpp>
#include "Texture.h"
#include "Shader.h"
#include <unordered_map>
#include <memory>
#include <variant>

namespace Azazel
{
    class MaterialProperty
    {
    public:
        enum ShaderPropertyType
        {
            INT,
            FLOAT,
            VEC2,
            VEC3,
            VEC4,
            MAT4,
            TEXTURE,
            BOOL,
            UNKNOWN
        };

        void setValue(float value)
        {
            this->value = value;
        }

        void setValue(int value)
        {
            this->value = value;
            type = FLOAT;
        }

        void setValue(const glm::vec2& value)
        {
            this->value = value;
            type = VEC2;
        }

        void setValue(const glm::vec3& value)
        {
            this->value = value;
            type = VEC3;
        }

        void setValue(const glm::vec4& value)
        {
            this->value = value;
            type = VEC4;
        }

        void setValue(const glm::mat4& value)
        {
            this->value = value;
            type = MAT4;
        }

        void setValue(std::shared_ptr<Texture> sampler)
        {
            this->value = sampler;
            type = TEXTURE;
        }

        void setValue(bool value)
        {
            this->value = value;
            type = BOOL;
        }

        void applyProperty(const std::string& name, Shader& shader, int& slot)
        {
            switch (type)
            {
            case Azazel::MaterialProperty::INT:
                break;
            case Azazel::MaterialProperty::FLOAT:
                shader.setFloat(name, std::get<float>(value));
                break;
            case Azazel::MaterialProperty::VEC2:
                shader.setVec2f(name, std::get<glm::vec2>(value));
                break;
            case Azazel::MaterialProperty::VEC3:
                shader.setVec3f(name, std::get<glm::vec3>(value));
                break;
            case Azazel::MaterialProperty::VEC4:
                shader.setVec4f(name, std::get<glm::vec4>(value));
                break;
            case Azazel::MaterialProperty::MAT4:
                shader.setMatrix4f(name, std::get<glm::mat4>(value));
                break;
            case Azazel::MaterialProperty::TEXTURE:
                shader.setTexture(name, *std::get<std::shared_ptr<Texture>>(value), slot);
                slot++;
                break;
            case Azazel::MaterialProperty::BOOL:
                shader.setBool(name, std::get<bool>(value));
                break;
            case Azazel::MaterialProperty::UNKNOWN:
                break;
            default:
                break;
            }
        }

        ShaderPropertyType type = UNKNOWN;
        std::variant<float, int, bool, glm::vec2, glm::vec3, glm::vec4, glm::mat4, std::shared_ptr<Texture>> value;

    };

    class Material
    {
    public:
        std::unordered_map<std::string, MaterialProperty> properties;

        void applyProperties(Shader& shader)
        {
            int slot = 0;
            for (auto& [propertyName, property] : properties)
            {
                property.applyProperty(propertyName, shader, slot);
            }
        }

        void setProperty(const std::string& name, MaterialProperty property)
        {
            properties[name] = property;
        }

        MaterialProperty& getProperty(const std::string name)
        {
            return properties[name];
        }
    };

   class PhysBasedMaterial : public Material
   {
        PhysBasedMaterial()
        {
        
        }
   };
}