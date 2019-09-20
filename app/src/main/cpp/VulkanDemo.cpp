//
// Created by realxie on 2019/3/23.
//

#include "VulkanDemo.h"

#include <vector>

#include "vulkan_wrapper.h"

// Android log function wrappers
static const char* kTAG = "Vulkan-Tutorial01";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

// Vulkan call wrapper
#define CALL_VK(func)                                                 \
  if (VK_SUCCESS != (func)) {                                         \
    __android_log_print(ANDROID_LOG_ERROR, "Tutorial ",               \
                        "Vulkan error. File[%s], line[%d]", __FILE__, \
                        __LINE__);                                    \
  }


//VkInstance tutorialInstance;
//VkPhysicalDevice tutorialGpu;
//VkDevice tutorialDevice;
//VkSurfaceKHR tutorialSurface;
//bool         isInited = false;

bool initVulkanInstance(struct android_app* app)
{
//    if (!InitVulkan() || isInited) {
//        return false;
//    }
//
//    VkApplicationInfo appInfo = {
//            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
//            .pNext = nullptr,
//            .apiVersion = VK_MAKE_VERSION(1, 0, 0),
//            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
//            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
//            .pApplicationName = "Realxie's vulkan demo",
//            .pEngineName = "demo",
//    };
//
//    // prepare necessary extensions: Vulkan on Android need these to function
//    std::vector<const char *> instanceExt, deviceExt;
//    instanceExt.push_back("VK_KHR_surface");
//    instanceExt.push_back("VK_KHR_android_surface");
//    deviceExt.push_back("VK_KHR_swapchain");
//
//    // Create the Vulkan instance
//    VkInstanceCreateInfo instanceCreateInfo{
//            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
//            .pNext = nullptr,
//            .pApplicationInfo = &appInfo,
//            .enabledExtensionCount = static_cast<uint32_t>(instanceExt.size()),
//            .ppEnabledExtensionNames = instanceExt.data(),
//            .enabledLayerCount = 0,
//            .ppEnabledLayerNames = nullptr,
//    };
//
//    VkResult result;
//    CALL_VK(vkCreateInstance(&instanceCreateInfo, nullptr, &tutorialInstance));
//
//    // if we create a surface, we need the surface extension
//    VkAndroidSurfaceCreateInfoKHR createInfo{
//            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
//            .pNext = nullptr,
//            .flags = 0,
//            .window = app->window};
//    CALL_VK(vkCreateAndroidSurfaceKHR(tutorialInstance, &createInfo, nullptr, &tutorialSurface));
//
//    uint32_t gpuCount = 0;
//    CALL_VK(vkEnumeratePhysicalDevices(tutorialInstance, &gpuCount, nullptr));
//    VkPhysicalDevice tmpGpus[gpuCount];
//    CALL_VK(vkEnumeratePhysicalDevices(tutorialInstance, &gpuCount, tmpGpus));
//    tutorialGpu = tmpGpus[0];  // Pick up the first GPU Devicereturn true;
//
//    // check for vulkan info on this GPU device
//    VkPhysicalDeviceProperties gpuProperties;
//    vkGetPhysicalDeviceProperties(tutorialGpu, &gpuProperties);
//    LOGI("Vulkan Physical Device Name: %s", gpuProperties.deviceName);
//    LOGI("Vulkan Physical Device Info: apiVersion: %x \n\t driverVersion: %x",
//         gpuProperties.apiVersion, gpuProperties.driverVersion);
//    LOGI("API Version Supported: %d.%d.%d",
//         VK_VERSION_MAJOR(gpuProperties.apiVersion),
//         VK_VERSION_MINOR(gpuProperties.apiVersion),
//         VK_VERSION_PATCH(gpuProperties.apiVersion));
//
//    VkSurfaceCapabilitiesKHR surfaceCapabilities;
//    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(tutorialGpu, tutorialSurface,
//                                              &surfaceCapabilities);
//
//    LOGI("Vulkan Surface Capabilities:\n");
//    LOGI("\timage count: %u - %u\n", surfaceCapabilities.minImageCount,
//         surfaceCapabilities.maxImageCount);
//    LOGI("\tarray layers: %u\n", surfaceCapabilities.maxImageArrayLayers);
//    LOGI("\timage size (now): %dx%d\n", surfaceCapabilities.currentExtent.width,
//         surfaceCapabilities.currentExtent.height);
//    LOGI("\timage size (extent): %dx%d - %dx%d\n",
//         surfaceCapabilities.minImageExtent.width,
//         surfaceCapabilities.minImageExtent.height,
//         surfaceCapabilities.maxImageExtent.width,
//         surfaceCapabilities.maxImageExtent.height);
//    LOGI("\tusage: %x\n", surfaceCapabilities.supportedUsageFlags);
//    LOGI("\tcurrent transform: %u\n", surfaceCapabilities.currentTransform);
//    LOGI("\tallowed transforms: %x\n", surfaceCapabilities.supportedTransforms);
//    LOGI("\tcomposite alpha flags: %u\n", surfaceCapabilities.currentTransform);
//
//    // Find a GFX queue family
//    uint32_t queueFamilyCount;
//    vkGetPhysicalDeviceQueueFamilyProperties(tutorialGpu, &queueFamilyCount, nullptr);
//    assert(queueFamilyCount);
//    std::vector<VkQueueFamilyProperties>  queueFamilyProperties(queueFamilyCount);
//    vkGetPhysicalDeviceQueueFamilyProperties(tutorialGpu, &queueFamilyCount,
//                                             queueFamilyProperties.data());
//
//    uint32_t queueFamilyIndex;
//    for (queueFamilyIndex=0; queueFamilyIndex < queueFamilyCount;
//         queueFamilyIndex++) {
//        if (queueFamilyProperties[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//            break;
//        }
//    }
//    assert(queueFamilyIndex < queueFamilyCount);
//
//    // Create a logical device from GPU we picked
//    float priorities[] = {
//            1.0f,
//    };
//    VkDeviceQueueCreateInfo queueCreateInfo{
//            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
//            .pNext = nullptr,
//            .flags = 0,
//            .queueCount = 1,
//            .queueFamilyIndex = queueFamilyIndex,
//            .pQueuePriorities = priorities,
//    };
//
//    VkDeviceCreateInfo deviceCreateInfo{
//            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
//            .pNext = nullptr,
//            .queueCreateInfoCount = 1,
//            .pQueueCreateInfos = &queueCreateInfo,
//            .enabledLayerCount = 0,
//            .ppEnabledLayerNames = nullptr,
//            .enabledExtensionCount = static_cast<uint32_t>(deviceExt.size()),
//            .ppEnabledExtensionNames = deviceExt.data(),
//            .pEnabledFeatures = nullptr,
//    };
//
//    CALL_VK(
//            vkCreateDevice(tutorialGpu, &deviceCreateInfo, nullptr, &tutorialDevice));

            return true;
}

RealRenderer* RealRenderer::instance_ = nullptr;

RealRenderer* RealRenderer::getInstance()
{
    if (instance_)
    {
        return instance_;
    }
    instance_ =  new RealRenderer();
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

bool RealRenderer::initVulkanContext(struct android_app* app)
{
    if (app->window == nullptr || isReady())
    {
        return false;
    }

    vkInstance_         = createVKInstance(app);
    vkSurface_          = createVKSurface(app);
    vkGPU_              = createVKGPU(app);
    vkDevice_           = createVKDevice(app);
    vkPhysicalDevice_   = createVKPhysicalDevice(vkInstance_);
    vkSwapchain_        = createVKSwapChain(vkDevice_, vkPhysicalDevice_, vkSurface_);
    vkQueue_            = createVKQueue(vkDevice_, vkPhysicalDevice_, vkSurface_);

    VkFenceCreateInfo fenceCreateInfo{
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
    };
    vkCreateFence(vkDevice_, &fenceCreateInfo, nullptr, &vkFence_);

    setupSwapchainEnv();
    createImageViews();
    createSemaphores();
    createRenderPass();
    createFramebuffers();
    createCommandPool();
    createCommandBuffers();

    return true;
}

void RealRenderer::setupSwapchainEnv()
{
    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(vkDevice_, vkSwapchain_, &imageCount, nullptr);
    swapChainImages_.resize(imageCount);
    vkGetSwapchainImagesKHR(vkDevice_, vkSwapchain_, &imageCount,
                            swapChainImages_.data());

    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(vkPhysicalDevice_, vkSurface_);
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    swapChainImageFormat_ = surfaceFormat.format;
    swapChainExtent_ = extent;
}

VkInstance RealRenderer::createVKInstance(struct android_app* app)
{
    VkApplicationInfo appInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pNext = nullptr,
            .apiVersion = VK_MAKE_VERSION(1, 0, 0),
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .pApplicationName = "Realxie's vulkan demo",
            .pEngineName = "demo",
    };

    // prepare necessary extensions: Vulkan on Android need these to function
    std::vector<const char *> instanceExt;
    instanceExt.push_back("VK_KHR_surface");
    instanceExt.push_back("VK_KHR_android_surface");

    // Create the Vulkan instance
    VkInstanceCreateInfo instanceCreateInfo{
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext = nullptr,
            .pApplicationInfo = &appInfo,
            .enabledExtensionCount = static_cast<uint32_t>(instanceExt.size()),
            .ppEnabledExtensionNames = instanceExt.data(),
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = nullptr,
    };

    VkInstance instance;
    CALL_VK(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));

    return instance;
}

VkPhysicalDevice RealRenderer::createVKGPU(struct android_app* app)
{
    uint32_t gpuCount = 0;
    CALL_VK(vkEnumeratePhysicalDevices(vkInstance_, &gpuCount, nullptr));
    VkPhysicalDevice tmpGpus[10] = {nullptr};
    CALL_VK(vkEnumeratePhysicalDevices(vkInstance_, &gpuCount, tmpGpus));
    return tmpGpus[0];  // Pick up the first GPU Devicereturn true;
}

VkDevice RealRenderer::createVKDevice(struct android_app* app)
{
    // check for vulkan info on this GPU device
    VkPhysicalDeviceProperties gpuProperties;
    vkGetPhysicalDeviceProperties(vkGPU_, &gpuProperties);
    LOGI("Vulkan Physical Device Name: %s", gpuProperties.deviceName);
    LOGI("Vulkan Physical Device Info: apiVersion: %x \n\t driverVersion: %x",
         gpuProperties.apiVersion, gpuProperties.driverVersion);
    LOGI("API Version Supported: %d.%d.%d",
         VK_VERSION_MAJOR(gpuProperties.apiVersion),
         VK_VERSION_MINOR(gpuProperties.apiVersion),
         VK_VERSION_PATCH(gpuProperties.apiVersion));

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkGPU_, vkSurface_,
                                              &surfaceCapabilities);

    LOGI("Vulkan Surface Capabilities:\n");
    LOGI("\timage count: %u - %u\n", surfaceCapabilities.minImageCount,
         surfaceCapabilities.maxImageCount);
    LOGI("\tarray layers: %u\n", surfaceCapabilities.maxImageArrayLayers);
    LOGI("\timage size (now): %dx%d\n", surfaceCapabilities.currentExtent.width,
         surfaceCapabilities.currentExtent.height);
    LOGI("\timage size (extent): %dx%d - %dx%d\n",
         surfaceCapabilities.minImageExtent.width,
         surfaceCapabilities.minImageExtent.height,
         surfaceCapabilities.maxImageExtent.width,
         surfaceCapabilities.maxImageExtent.height);
    LOGI("\tusage: %x\n", surfaceCapabilities.supportedUsageFlags);
    LOGI("\tcurrent transform: %u\n", surfaceCapabilities.currentTransform);
    LOGI("\tallowed transforms: %x\n", surfaceCapabilities.supportedTransforms);
    LOGI("\tcomposite alpha flags: %u\n", surfaceCapabilities.currentTransform);

    // Find a GFX queue family
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(vkGPU_, &queueFamilyCount, nullptr);
    assert(queueFamilyCount);
    std::vector<VkQueueFamilyProperties>  queueFamilyProperties(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(vkGPU_, &queueFamilyCount,
                                             queueFamilyProperties.data());

    uint32_t queueFamilyIndex;
    for (queueFamilyIndex=0; queueFamilyIndex < queueFamilyCount;
         queueFamilyIndex++) {
        if (queueFamilyProperties[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            break;
        }
    }
    assert(queueFamilyIndex < queueFamilyCount);

    float priorities[] = {
            1.0f,
    };
    VkDeviceQueueCreateInfo queueCreateInfo{
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueCount = 1,
            .queueFamilyIndex = queueFamilyIndex,
            .pQueuePriorities = priorities,
    };

    // prepare necessary extensions: Vulkan on Android need these to function
    std::vector<const char *> deviceExt;
    deviceExt.push_back("VK_KHR_swapchain");

    VkDeviceCreateInfo deviceCreateInfo{
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pNext = nullptr,
            .queueCreateInfoCount = 1,
            .pQueueCreateInfos = &queueCreateInfo,
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = nullptr,
            .enabledExtensionCount = static_cast<uint32_t>(deviceExt.size()),
            .ppEnabledExtensionNames = deviceExt.data(),
            .pEnabledFeatures = nullptr,
    };

    VkDevice device;
    CALL_VK(vkCreateDevice(vkGPU_, &deviceCreateInfo, nullptr, &device));

    return device;
}

bool RealRenderer::isDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
}

VkPhysicalDevice RealRenderer::createVKPhysicalDevice(VkInstance instance)
{
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;

    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto &device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }
    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    return physicalDevice;
}

VkSurfaceKHR  RealRenderer::createVKSurface(struct android_app* app)
{
    // if we create a surface, we need the surface extension
    VkAndroidSurfaceCreateInfoKHR createInfo{
            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            .pNext = nullptr,
            .flags = 0,
            .window = app->window};
    VkSurfaceKHR surface;
    vkCreateAndroidSurfaceKHR(vkInstance_, &createInfo, nullptr, &surface);
    return surface;
}

VkSurfaceFormatKHR RealRenderer::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }
    return availableFormats[0];
}

VkPresentModeKHR RealRenderer::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        } else if (availablePresentMode ==
                   VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = availablePresentMode;
        } }
    return bestMode;
}

VkExtent2D RealRenderer::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {4096, 4096};
        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width,
                                               actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height,
                                                actualExtent.height));
        return actualExtent;
    }
}

SwapChainSupportDetails RealRenderer::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    SwapChainSupportDetails details;
    // Capabilities
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
    //formats
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }
    // presentMode
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }
    return details;
}

QueueFamilyIndices RealRenderer::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties>queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (queueFamily.queueCount > 0 && presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }
        i++;
    }

    return indices;
}

VkSwapchainKHR RealRenderer::createVKSwapChain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(vkPhysicalDevice_, vkSurface_);
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 &&
        imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
    uint32_t queueFamilyIndices[] = {(uint32_t) indices.graphicsFamily,
                                     (uint32_t) indices.presentFamily};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional   createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    VkSwapchainKHR swapChain;  // 声明

    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    return swapChain;
}

VkQueue RealRenderer::createVKQueue(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
    VkQueue queue;
    vkGetDeviceQueue(device, indices.presentFamily, 0, &queue);
    return queue;
}

void RealRenderer::createImageViews()
{
    swapChainImageViews_.resize(swapChainImages_.size());

    for (size_t i = 0; i < swapChainImages_.size(); i++) {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages_[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = swapChainImageFormat_;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        createInfo.subresourceRange.aspectMask =
                VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(vkDevice_, &createInfo, nullptr, &swapChainImageViews_[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void RealRenderer::createRenderPass()
{
    VkAttachmentDescription attachmentDescriptions = {
            .format = swapChainImageFormat_,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    };

    VkAttachmentReference colourReference = {
            .attachment = 0,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkSubpassDescription subpassDescription = {
            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .flags = 0,
            .inputAttachmentCount = 0,
            .pInputAttachments = nullptr,
            .colorAttachmentCount = 1,
            .pColorAttachments = &colourReference,
            .pResolveAttachments = nullptr,
            .pDepthStencilAttachment = nullptr,
            .preserveAttachmentCount = 0,
            .pPreserveAttachments = nullptr,
    };

    VkRenderPassCreateInfo renderPassInfo = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .pNext = nullptr,
            .attachmentCount = 1,
            .pAttachments = &attachmentDescriptions,
            .subpassCount = 1,
            .pSubpasses = &subpassDescription,
            .dependencyCount = 0,
            .pDependencies = nullptr,
    };
    if (auto code = vkCreateRenderPass(vkDevice_, &renderPassInfo, nullptr, &renderPass_); code != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}

void RealRenderer::createFramebuffers()
{
    swapChainFramebuffers_.resize(swapChainImageViews_.size());

    for (size_t i = 0; i < swapChainImageViews_.size(); i++) {
        VkImageView attachments[] = {
                swapChainImageViews_[i]
        };
        VkFramebufferCreateInfo framebufferInfo = {
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .pNext = nullptr,
                .renderPass = renderPass_,
                .layers = 1,
                .attachmentCount = 1,  // 2 if using depth
                .pAttachments = attachments,
                .width = static_cast<uint32_t>(swapChainExtent_.width),
                .height = static_cast<uint32_t>(swapChainExtent_.height),
        };

        if (vkCreateFramebuffer(vkDevice_, &framebufferInfo, nullptr, &swapChainFramebuffers_[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void RealRenderer::createCommandPool()
{
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(vkPhysicalDevice_, vkSurface_);
    VkCommandPoolCreateInfo poolInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .pNext = nullptr,
            .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex = 0,
    };

    if (auto code = vkCreateCommandPool(vkDevice_, &poolInfo, nullptr, &commandPool_); code != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

/*
 * setImageLayout():
 *    Helper function to transition color buffer layout
 */
void setImageLayout(VkCommandBuffer cmdBuffer, VkImage image,
                    VkImageLayout oldImageLayout, VkImageLayout newImageLayout,
                    VkPipelineStageFlags srcStages,
                    VkPipelineStageFlags destStages) {
    VkImageMemoryBarrier imageMemoryBarrier = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            .pNext = NULL,
            .srcAccessMask = 0,
            .dstAccessMask = 0,
            .oldLayout = oldImageLayout,
            .newLayout = newImageLayout,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = image,
            .subresourceRange =
                    {
                            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                            .baseMipLevel = 0,
                            .levelCount = 1,
                            .baseArrayLayer = 0,
                            .layerCount = 1,
                    },
    };

    switch (oldImageLayout) {
        case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_PREINITIALIZED:
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
            break;

        default:
            break;
    }

    switch (newImageLayout) {
        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            break;

        case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            break;

        case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
            imageMemoryBarrier.dstAccessMask =
                    VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
            break;

        default:
            break;
    }

    vkCmdPipelineBarrier(cmdBuffer, srcStages, destStages, 0, 0, NULL, 0, NULL, 1,
                         &imageMemoryBarrier);
}

void RealRenderer::createCommandBuffers()
{
    commandBuffers_.resize(swapChainFramebuffers_.size());

//    VkCommandBufferAllocateInfo allocInfo = {};
//    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//    allocInfo.commandPool = commandPool_;
//    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//    allocInfo.commandBufferCount = (uint32_t) commandBuffers_.size();
//    if (vkAllocateCommandBuffers(vkDevice_, &allocInfo, commandBuffers_.data()) != VK_SUCCESS) {
//        throw std::runtime_error("failed to allocate command buffers!");
//    }

    for (size_t i = 0; i < commandBuffers_.size(); i++) {
        VkCommandBufferAllocateInfo cmdBufferCreateInfo{
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                .pNext = nullptr,
                .commandPool = commandPool_,
                .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                .commandBufferCount = 1,
        };

        if (auto code = vkAllocateCommandBuffers(vkDevice_, &cmdBufferCreateInfo, &commandBuffers_[i]); code != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        VkCommandBufferBeginInfo cmdBufferBeginInfo{
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                .pNext = nullptr,
                .flags = 0,
                .pInheritanceInfo = nullptr,
        };
        CALL_VK(vkBeginCommandBuffer(commandBuffers_[i], &cmdBufferBeginInfo));

        // transition the display image to color attachment layout
        setImageLayout(commandBuffers_[i],
                       swapChainImages_[i],
                       VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                       VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                       VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                       VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

        // Now we start a renderpass. Any draw command has to be recorded in a
        // renderpass
        VkClearValue clearVals{
                .color.float32[0] = 0.0f,
                .color.float32[1] = 0.34f,
                .color.float32[2] = 0.90f,
                .color.float32[3] = 1.0f,
        };

        VkRenderPassBeginInfo renderPassBeginInfo{
                .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                .pNext = nullptr,
                .renderPass = renderPass_,
                .framebuffer = swapChainFramebuffers_[i],
                .renderArea = {.offset =
                        {
                                .x = 0, .y = 0,
                        },
                        .extent = swapChainExtent_},
                .clearValueCount = 1,
                .pClearValues = &clearVals};
        vkCmdBeginRenderPass(commandBuffers_[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdEndRenderPass(commandBuffers_[i]);
        // transition back to swapchain image to PRESENT_SRC_KHR
        setImageLayout(commandBuffers_[i],
                       swapChainImages_[i],
                       VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                       VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                       VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                       VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT);
        CALL_VK(vkEndCommandBuffer(commandBuffers_[i]));
    }
}

void RealRenderer::createSemaphores()
{
    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateSemaphore(vkDevice_, &semaphoreInfo, nullptr, &imageAvailableSemaphore_) !=
        VK_SUCCESS ||
        vkCreateSemaphore(vkDevice_, &semaphoreInfo, nullptr, &renderFinishedSemaphore_) !=
        VK_SUCCESS) {
        throw std::runtime_error("failed to create semaphores!");
    }
}

void RealRenderer::drawFrame()
{
    uint32_t imageIndex;
    vkAcquireNextImageKHR(vkDevice_, vkSwapchain_, std::numeric_limits<uint64_t>::max(),
                          imageAvailableSemaphore_, VK_NULL_HANDLE, &imageIndex);

    vkResetFences(vkDevice_, 1, &vkFence_);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    VkPipelineStageFlags waitStages[] =
            {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &imageAvailableSemaphore_;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers_[imageIndex];

    submitInfo.signalSemaphoreCount =  1;
    submitInfo.pSignalSemaphores = &renderFinishedSemaphore_;

    if (auto code = vkQueueSubmit(vkQueue_, 1, &submitInfo, vkFence_); code != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }
    vkWaitForFences(vkDevice_, 1, &vkFence_, VK_TRUE, 100000000);

    LOGI("Drawing frames......");

    VkResult result;
    VkPresentInfoKHR presentInfo{
            .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            .pNext = nullptr,
            .swapchainCount = 1,
            .pSwapchains = &vkSwapchain_,
            .pImageIndices = &imageIndex,
            .waitSemaphoreCount = 0,
            .pWaitSemaphores = nullptr,
            .pResults = &result,
    };
    vkQueuePresentKHR(vkQueue_, &presentInfo);
}
