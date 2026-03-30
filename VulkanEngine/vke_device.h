#pragma once

// INCLUDES //

#include "vke_window.h"

#include <string>
#include <vector>

// MAIN //

namespace vke
{

struct SwapChainSupportDetails 
{
  VkSurfaceCapabilitiesKHR        capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR>   presentModes;
};

struct QueueFamilyIndices 
{
  uint32_t graphicsFamily;
  uint32_t presentFamily;

  bool graphicsFamilyHasValue = false;
  bool presentFamilyHasValue = false;

  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};


class VkeDevice 
{
    public:

        #ifdef NDEBUG
            const bool enableValidationLayers = false;
        #else
            const bool enableValidationLayers = true;
        #endif

        VkeDevice(VkeWindow &window);
        ~VkeDevice();

        VkeDevice            (const VkeDevice &) = delete;
        VkeDevice &operator= (const VkeDevice &) = delete;
        VkeDevice            (VkeDevice &&)      = delete;
        VkeDevice &operator= (VkeDevice &&)      = delete;

        VkCommandPool getCommandPool() { return commandPool;       }
        VkDevice device()              { return __device__;        }
        VkSurfaceKHR surface()         { return __surface__;       }
        VkQueue graphicsQueue()        { return __graphicsQueue__; }
        VkQueue presentQueue()         { return __presentQueue__;  }

        SwapChainSupportDetails getSwapChainSupport()  { return querySwapChainSupport (physicalDevice); }
        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies     (physicalDevice); }

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        void createBuffer
        (
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer &buffer,
            VkDeviceMemory &bufferMemory
        );

        VkCommandBuffer beginSingleTimeCommands();

        void endSingleTimeCommands (VkCommandBuffer commandBuffer);
        void copyBuffer            (VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void copyBufferToImage     (VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

        void createImageWithInfo
        (
            const VkImageCreateInfo &imageInfo,
            VkMemoryPropertyFlags properties,
            VkImage &image,
            VkDeviceMemory &imageMemory
        );

        VkPhysicalDeviceProperties properties;

    private:

        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createCommandPool();

        bool isDeviceSuitable(VkPhysicalDevice device);
        
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        bool checkValidationLayerSupport();
        
        std::vector<const char *> getRequiredExtensions();

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void hasGflwRequiredInstanceExtensions();

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkeWindow &window;
        VkCommandPool commandPool;

        VkDevice __device__;
        VkSurfaceKHR __surface__;
        VkQueue __graphicsQueue__;
        VkQueue __presentQueue__;

        const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
        const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
};

} // namespace vke