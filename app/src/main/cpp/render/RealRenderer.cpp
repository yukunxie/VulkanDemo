//
// Created by realxie on 2019/3/23.
//

#include "RealRenderer.h"

#include <vector>
#include <array>
#include <chrono>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "../drivers/vulkan/vulkan_wrapper.h"
#include "../aux/AFileSystem.h"
#include "../external/glm/vec3.hpp"
#include "../external/glm/gtx/closest_point.inl"
#include "../aux/AFileSystem.h"

#include "../RHI/include/RHI.h"

#include "../external/stb/stb_image.h"

//
//// Android log function wrappers
//static const char *kTAG = "VulkanDemo";
//#define LOGI(...) \
//  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
//#define LOGW(...) \
//  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
//#define LOGE(...) \
//  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))
//
// Vulkan call wrapper
//#define CALL_VK(func)                                                 \
//  if (VK_SUCCESS != (func)) {                                         \
//    __android_log_print(ANDROID_LOG_ERROR, "Tutorial ",               \
//                        "Vulkan error. File[%s], line[%d]", __FILE__, \
//                        __LINE__);                                    \
//  }

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

RealRenderer *RealRenderer::instance_ = nullptr;

RealRenderer *RealRenderer::getInstance()
{
    if (instance_)
    {
        return instance_;
    }
    instance_ = new RealRenderer();
    return instance_;
}

RealRenderer::RealRenderer()
{
    auto ret = InitVulkan();
    assert(ret != 0);
}

RealRenderer::~RealRenderer()
{
}

bool RealRenderer::initVulkanContext(ANativeWindow *window)
{
    if (window == nullptr || isReady())
    {
        return false;
    }
    
    rhiDevice_ = new RHI::VKDevice(window);
    
    //    const std::vector<TVertex> vertices = {
    //            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    //            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    //            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    //            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
    //    };
    
    const std::vector<TVertex> vertices = {
            // Front face
            {{-1.0f, -1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f,  -1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f,  1.0f,  1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{-1.0f, 1.0f,  1.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            
            // Back face
            {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f,  -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f,  1.0f,  -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{1.0f,  -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            
            // Top face
            {{-1.0f, 1.0f,  -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f,  1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f,  1.0f,  1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{1.0f,  1.0f,  -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            
            // Bottom face
            {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f,  -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f,  -1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{-1.0f, -1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            
            // Right face
            {{1.0f,  -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f,  1.0f,  -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f,  1.0f,  1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{1.0f,  -1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            
            // Left face
            {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{-1.0f, -1.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{-1.0f, 1.0f,  1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            {{-1.0f, 1.0f,  -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    };
    
    // Create VertexBuffer
    {
        RHI::BufferSize vertexBufferSize = static_cast<std::uint32_t>(sizeof(vertices[0]) *
                                                                      vertices.size());
        RHI::BufferDescriptor vertexBufferDescriptor = {
                .usage = RHI::BufferUsage::VERTEX,
                .size  = vertexBufferSize,
        };
        rhiVertexBuffer_ = rhiDevice_->CreateBuffer(vertexBufferDescriptor);
        
        std::uint8_t *pVertexData = (std::uint8_t *) rhiVertexBuffer_->MapWriteAsync();
        memcpy(pVertexData, vertices.data(), vertexBufferSize);
        rhiVertexBuffer_->Unmap();
    }
    
    const std::vector<uint16_t> indices = {
            0, 1, 2, 0, 2, 3,    // front
            4, 5, 6, 4, 6, 7,    // back
            8, 9, 10, 8, 10, 11,   // top
            12, 13, 14, 12, 14, 15,   // bottom
            16, 17, 18, 16, 18, 19,   // right
            20, 21, 22, 20, 22, 23,   // left
    };
    
    // Create index buffer
    {
        RHI::BufferSize indexBufferSize = static_cast<std::uint32_t>(sizeof(indices[0]) *
                                                                     indices.size());
        RHI::BufferDescriptor indexBufferDescriptor = {
                .usage = RHI::BufferUsage::INDEX,
                .size  = indexBufferSize,
        };
        rhiIndexBuffer_ = rhiDevice_->CreateBuffer(indexBufferDescriptor);
        
        std::uint8_t *pIndexData = (std::uint8_t *) rhiIndexBuffer_->MapWriteAsync();
        memcpy(pIndexData, indices.data(), indexBufferSize);
        rhiIndexBuffer_->Unmap();
    }
    
    UniformBufferObject ubo = {};
    float time = 0.0f;
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f),
                            glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), rhiDevice_->GetViewport().width /
                                                     (float) rhiDevice_->GetViewport().height, 0.1f,
                                10.0f);
    ubo.proj[1][1] *= -1;
    
    // Create uniform buffer object
    {
        RHI::BufferSize bufferSize = static_cast<std::uint32_t>(sizeof(UniformBufferObject));
        RHI::BufferDescriptor bufferDescriptor = {
                .usage = RHI::BufferUsage::UNIFORM,
                .size  = bufferSize,
        };
        rhiUniformBuffer_ = rhiDevice_->CreateBuffer(bufferDescriptor);
        
        std::uint8_t *pData = (std::uint8_t *) rhiUniformBuffer_->MapWriteAsync();
        memcpy(pData, &ubo, bufferSize);
        rhiUniformBuffer_->Unmap();
    }
    
    // ------------ Start setup RenderPipeline object ---------------
    
    // Step 1. create shaders
    
    const TData &vertData = AFileSystem::getInstance()->readData("shaders/shader.vert.spv");
    const TData &fragData = AFileSystem::getInstance()->readData("shaders/shader.frag.spv");
    rhiVertShader_ = rhiDevice_->CreateShader(vertData);
    rhiFragShader_ = rhiDevice_->CreateShader(fragData);
    
    {
        RHI::BindGroupLayoutDescriptor descriptor;
        descriptor.bindings = {
            RHI::BindGroupLayoutBinding {
                .type = RHI::BindingType::UNIFORM_BUFFER,
                .binding = 0,
                .visibility = RHI::ShaderStage::VERTEX,
            },
            RHI::BindGroupLayoutBinding {
                .type = RHI::BindingType::SAMPLED_TEXTURE,
                .binding = 1,
                .visibility = RHI::ShaderStage::FRAGMENT,
            },
        };
        rhiBindGroupLayout_ = rhiDevice_->CreateBindGroupLayout(descriptor);
    }
    
    {
        RHI::PipelineLayoutDescriptor descriptor;
        descriptor.bindGroupLayouts = {rhiBindGroupLayout_};
        rhiPipelineLayout_ = rhiDevice_->CreatePipelineLayout(descriptor);
    }
  
    RHI::RenderPipelineDescriptor renderPipelineDescriptor;
    {
        renderPipelineDescriptor.layout = rhiPipelineLayout_;
        
        renderPipelineDescriptor.vertexStage = {
                .module = rhiVertShader_,
                .entryPoint = "main"
        };
        
        renderPipelineDescriptor.fragmentStage = {
                .module = rhiFragShader_,
                .entryPoint = "main"
        };
        
        renderPipelineDescriptor.primitiveTopology = RHI::PrimitiveTopology::TRIANGLE_LIST;
        
        renderPipelineDescriptor.depthStencilState = RHI::DepthStencilStateDescriptor{
                .depthWriteEnabled = true,
                .depthCompare = RHI::CompareFunction::LESS,
                .format = RHI::TextureFormat::DEPTH24PLUS_STENCIL8,
                .stencilFront = {},
                .stencilBack  = {},
        };
        
        renderPipelineDescriptor.vertexInput = {
                .indexFormat = RHI::IndexFormat::UINT32,
                .vertexBuffers = {
                        RHI::VertexBufferDescriptor{
                                .stride = sizeof(TVertex),
                                .stepMode = RHI::InputStepMode::VERTEX,
                                .attributeSet = {
                                        RHI::VertexAttributeDescriptor{
                                                .shaderLocation = 0,
                                                .format = RHI::VertexFormat::FLOAT3,
                                                .offset = offsetof(TVertex, pos),
                                        },
                                        RHI::VertexAttributeDescriptor{
                                                .shaderLocation = 1,
                                                .format = RHI::VertexFormat::FLOAT3,
                                                .offset = offsetof(TVertex, color),
                                        },
                                        RHI::VertexAttributeDescriptor{
                                                .shaderLocation = 2,
                                                .format = RHI::VertexFormat::FLOAT2,
                                                .offset = offsetof(TVertex, texCoord),
                                        },
                                },
                        },
                }
        };
        renderPipelineDescriptor.rasterizationState = {
                .frontFace = RHI::FrontFace::COUNTER_CLOCKWISE,
                .cullMode  = RHI::CullMode::BACK_BIT,
        };
        
        renderPipelineDescriptor.colorStates = {
                RHI::ColorStateDescriptor{
                        .format = RHI::TextureFormat::BGRA8UNORM,
                        .alphaBlend = {},
                        .colorBlend = {},
                        .writeMask  = RHI::ColorWrite::ALL,
                }
        };
        
        renderPipelineDescriptor.sampleCount = 1;
        renderPipelineDescriptor.sampleMask = 0xFFFFFFFF;
        renderPipelineDescriptor.alphaToCoverageEnabled = false;
    }
    
    rhiGraphicPipeline_ = rhiDevice_->CreateRenderPipeline(renderPipelineDescriptor);
    
    // ------------ End setup RenderPipeline object ---------------
    
    // setup image
    
    int texWidth, texHeight, texChannels;
    const TData &imageData = AFileSystem::getInstance()->readData("images/spiderman.jpg");
    stbi_uc *pixels = stbi_load_from_memory(imageData.data(), imageData.size(), &texWidth,
                                            &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    if (!pixels)
    {
        throw std::runtime_error("failed to load texture image!");
    }
    
    RHI::ImageCreateInfo imageCreateInfo{
            .imageType = RHI::ImageType::IMAGE_TYPE_2D,
            .format    = RHI::Format::R8G8B8A8_UNORM,
            .extent = {
                    .width = (std::uint32_t) texWidth,
                    .height= (std::uint32_t) texHeight,
                    .depth = 1
            },
            .mipLevels = 1,
            .arrayLayers = 1,
            .samples = RHI::SampleCountFlagBits::SAMPLE_COUNT_1_BIT,
            .tiling = RHI::ImageTiling::LINEAR,
            .sharingMode = RHI::SharingMode::EXCLUSIVE,
            .imageData = pixels,
    };
    
    //    rhiTexture_ = rhiDevice_->CreateTexture(imageCreateInfo);
    {
        RHI::TextureDescriptor descriptor;
        {
            descriptor.sampleCount = 1;
            descriptor.format = RHI::TextureFormat::RGBA8UNORM;
            descriptor.usage = RHI::TextureUsage::SAMPLED | RHI::TextureUsage::COPY_DST;
            descriptor.size = {(std::uint32_t) texWidth, (std::uint32_t) texHeight, 1};
            descriptor.arrayLayerCount = 1;
            descriptor.mipLevelCount = 1;
            descriptor.dimension = RHI::TextureDimension::TEXTURE_2D;
        };
        auto texture = rhiDevice_->CreateTexture(descriptor);
        
        RHI::BufferDescriptor bufferDescriptor;
        {
            bufferDescriptor.size = (std::uint32_t) texWidth * 4;
            bufferDescriptor.usage = RHI::BufferUsage::COPY_DST | RHI::BufferUsage::COPY_SRC;
        }
        
        auto buffer = rhiDevice_->CreateBuffer(bufferDescriptor);
        std::uint8_t *pData = (std::uint8_t *) buffer->MapWriteAsync();
        memcpy(pData, pixels, texWidth * texHeight * 4);
        buffer->Unmap();
        
        RHI::BufferCopyView bufferCopyView;
        {
            bufferCopyView.buffer = buffer;
            bufferCopyView.offset = 0;
            bufferCopyView.imageHeight = 0;
            bufferCopyView.rowPitch = texWidth * 4;
        }
        
        RHI::TextureCopyView textureCopyView;
        {
            textureCopyView.texture = texture;
            textureCopyView.origin = {0, 0, 0};
            textureCopyView.arrayLayer = 1;
            textureCopyView.mipLevel = 0;
        }
        
        auto commandEncoder = rhiDevice_->CreateCommandEncoder();
        RHI::Extent3D extent3D = {(std::uint32_t) texWidth, (std::uint32_t) texHeight, 1};
        commandEncoder->CopyBufferToTexture(bufferCopyView, textureCopyView, extent3D);
        
        rhiDevice_->GetQueue()->Submit(commandEncoder->Finish());
        RHI_SAFE_RELEASE(commandEncoder);
        
        rhiTexture_ = texture;
    }
    
    rhiTextureView_ = rhiTexture_->CreateView();
    
    stbi_image_free(pixels);
    
    // Create Depth Stencil texture and textureview
    {
        VkExtent2D extent2D = rhiDevice_->GetSwapChainExtent2D();
        
        RHI::TextureDescriptor descriptor;
        {
            descriptor.sampleCount = 1;
            descriptor.format = RHI::TextureFormat::DEPTH24PLUS_STENCIL8;
            descriptor.usage = RHI::TextureUsage::OUTPUT_ATTACHMENT;
            descriptor.size = {(std::uint32_t) extent2D.width, (std::uint32_t) extent2D.height, 1};
            descriptor.arrayLayerCount = 1;
            descriptor.mipLevelCount = 1;
            descriptor.dimension = RHI::TextureDimension::TEXTURE_2D;
        };
        rhiDSTexture_ = rhiDevice_->CreateTexture(descriptor);
        rhiDSTextureView_ = rhiDSTexture_->CreateView();
    }
    
    {
        RHI::SamplerDescriptor descriptor;
        descriptor.minFilter = RHI::FilterMode::LINEAR;
        descriptor.magFilter = RHI::FilterMode::LINEAR;
        descriptor.addressModeU = RHI::AddressMode::REPEAT;
        descriptor.addressModeV = RHI::AddressMode::REPEAT;
        descriptor.addressModeW = RHI::AddressMode::REPEAT;
        rhiSampler_ = rhiDevice_->CreateSampler(descriptor);
    }
    
    
    // setup UBO
    rhiBindingBuffer_ = rhiDevice_->CreateBindingResourceBuffer(0, rhiUniformBuffer_, 0,
                                                                sizeof(UniformBufferObject));
    rhiBindingCombined_ = rhiDevice_->CreateBindingResourceCombined(1, rhiTextureView_,
                                                                    rhiSampler_);
    
    {
        RHI::BindGroupDescriptor descriptor;
        descriptor.layout = rhiBindGroupLayout_;
        descriptor.bindings = {
            RHI::BindGroupBinding {
                .binding = 0,
                .resource = rhiBindingBuffer_
            },
            RHI::BindGroupBinding {
                .binding = 1,
                .resource = rhiBindingCombined_
            }
        };
        rhiBindGroup_ = rhiDevice_->CreateBindGroup(descriptor);
    }
    
    rhiCommandEncoder_ = rhiDevice_->CreateCommandEncoder();
    
    rhiSwapChain_ = rhiDevice_->CreateSwapChain();
    
    return true;
}

void RealRenderer::testRotate()
{
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(
            currentTime - startTime).count();
    
    UniformBufferObject ubo = {};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f),
                            glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(.0f, 8.0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), rhiDevice_->GetViewport().width /
                                                     (float) rhiDevice_->GetViewport().height, 2.0f,
                                20.0f);
    ubo.proj[1][1] *= -1;
    
    rhiDevice_->WriteBuffer(rhiUniformBuffer_, &ubo, 0, sizeof(UniformBufferObject));
}

void RealRenderer::drawFrame()
{
    testRotate();
    
    std::vector<RHI::RenderPassColorAttachmentDescriptor> colorAttachments = {
            RHI::RenderPassColorAttachmentDescriptor{
                    .attachment = rhiSwapChain_->GetCurrentTexture(),
                    .resolveTarget = nullptr,
                    .loadOp = RHI::LoadOp::CLEAR,
                    .loadValue = {0.0f, 0.0f, 0.0f, 1.0f},
                    .storeOp= RHI::StoreOp::STORE,
            }
    };
    
    RHI::RenderPassDescriptor renderPassDescriptor;
    renderPassDescriptor.colorAttachments = std::move(colorAttachments);
    renderPassDescriptor.depthStencilAttachment = {
            .attachment = rhiDSTextureView_,
            .depthLoadOp = RHI::LoadOp::CLEAR,
            .depthLoadValue = 1.0f,
            .depthStoreOp = RHI::StoreOp::STORE,
            .stencilLoadOp = RHI::LoadOp::CLEAR,
            .stencilLoadValue = 0,
            .stencilStoreOp = RHI::StoreOp::STORE,
    };
    
    auto renderPassEncoder = rhiCommandEncoder_->BeginRenderPass(renderPassDescriptor);
    
    // Render a tile with texture.
    {
        renderPassEncoder->SetGraphicPipeline(rhiGraphicPipeline_);
        renderPassEncoder->SetVertexBuffer(rhiVertexBuffer_, 0);
        renderPassEncoder->SetIndexBuffer(rhiIndexBuffer_, 0);
        renderPassEncoder->SetBindGroup(0, rhiBindGroup_);
        renderPassEncoder->SetViewport(0, 0, 1080, 1810, 0, 1);
        renderPassEncoder->SetScissorRect(0, 0, 1080, 1810);
        renderPassEncoder->DrawIndxed(36, 0);
    }
    
    renderPassEncoder->EndPass();
    
    auto commandBuffer = rhiCommandEncoder_->Finish();
    
    rhiDevice_->GetQueue()->Submit(commandBuffer);
    
    // Render to screen.
    rhiSwapChain_->Present(rhiDevice_->GetQueue());
}
