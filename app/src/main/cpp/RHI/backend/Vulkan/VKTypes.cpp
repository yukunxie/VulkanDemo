//
// Created by realxie on 2019-10-04.
//

#include "VKTypes.h"

NS_RHI_BEGIN

VkFormat ToVkFormat(Format format)
{
    return (VkFormat)format;
}

VkSampleCountFlagBits ToVkSampleCountFlagBits(SampleCountFlagBits bit)
{
    return (VkSampleCountFlagBits)bit;
}

VkAttachmentLoadOp ToVkAttachmentLoadOp(AttachmentLoadOp op)
{
    return (VkAttachmentLoadOp) op;
}

VkAttachmentStoreOp ToVkAttachmentStoreOp(AttachmentStoreOp op)
{
    return (VkAttachmentStoreOp) op;
}

VkImageLayout ToVkImageLayout(ImageLayout layout)
{
    return (VkImageLayout)layout;
}

VkShaderStageFlagBits ToVkShaderStageFlagBits(ShaderStageFlagBits bits)
{
    return (VkShaderStageFlagBits) bits;
}

VkVertexInputRate ToVkVertexInputRate(VertexInputRate inputRate)
{
    return (VkVertexInputRate)inputRate;
}


NS_RHI_END
