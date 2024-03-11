#include "AZContext.h"

#include <memory>

namespace Azazel
{
    static AZContext* context = nullptr;

    void Azazel::setVulkanContext(AZContext& ctx)
    {
        context = std::addressof(ctx);
    }

    AZContext& Azazel::getVulkanContext()
    {
        return *context;
    }

}