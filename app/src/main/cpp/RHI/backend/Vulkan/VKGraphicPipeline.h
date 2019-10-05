//
// Created by realxie on 2019-10-04.
//

#ifndef ALITA_VKGRAPHICPIPELINE_H
#define ALITA_VKGRAPHICPIPELINE_H

#include "VKDevice.h"
#include "../../include/Macros.h"
#include "../../include/GraphicPipleine.h"
#include "../../include/Flags.h"
#include "drivers/vulkan/vulkan_wrapper.h"

#include <vulkan/vulkan.h>
#include <vector>

NS_RHI_BEGIN

class VKGraphicPipeline : public GraphicPipeline
{
public:
    VKGraphicPipeline(VKDevice* device, const std::vector<RHI::PipelineShaderStageCreateInfo>& shaderStageInfos
            , const PipelineVertexInputStateCreateInfo& vertexInputInfo
            , const PipelineViewportStateCreateInfo& viewportState);
    virtual ~VKGraphicPipeline();

    void Bind(VkCommandBuffer cmdBuffer);

private:
    VkPipeline                      vkGraphicsPipeline_; // tmp
    VkPipelineLayout                vkPipelineLayout_; // tmp

    friend class VKDevice;
};

NS_RHI_END


#endif //ALITA_VKGRAPHICPIPELINE_H
