#pragma once

#include <bitset>
#include <stdint.h>

namespace Azazel
{
    using Entity = std::uint32_t;

    const Entity MAX_ENTITIES = 25000;

    using ComponentType = std::uint8_t;

    const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}