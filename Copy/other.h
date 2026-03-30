#pragma once

// INCLUDES //

#define  GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <optional>
#include <limits>
#include <algorithm>

#include "file_utils.h"

// ************ //

constexpr int Window_Width = 800;
constexpr int Window_Height = 600;

constexpr int MAX_FRAMES_IN_FLIGHT = 3;

constexpr char App_Name[] = "Vulkan App";

constexpr char Vert_Spv_Dir[] = "../Shaders/vert.spv";
constexpr char Frag_Spv_Dir[] = "../Shaders/frag.spv";

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

// ************ //

// APPLICATION //

class Vulkan_App
{
    public:

        void Run() 
        {
            init_Vulkan();
            main_Loop();
            clean_Up();
        }

    private:

        // Variables //

        VkInstance       vk_instance;
        VkPhysicalDevice vk_physicalDevice = VK_NULL_HANDLE;
        VkDevice         vk_device;

        VkSwapchainKHR           vk_swapChain; 
        std::vector<VkImage>     vk_swapChainImages;
        VkFormat                 vk_swapChainImageFormat;
        VkExtent2D               vk_swapChainExtent;
          
        std::vector<VkImageView>   vk_swapChainImageViews;
        std::vector<VkFramebuffer> vk_swapChainFramebuffers;

        VkQueue          vk_graphicsQueue;
        VkQueue          vk_presentQueue;
        
        VkPipeline       vk_graphicsPipeline;
        VkRenderPass     vk_renderPass;
        VkPipelineLayout vk_pipelineLayout;

        VkCommandPool   vk_commandPool;
        std::vector<VkCommandBuffer> vk_commandBuffers;

        std::vector<VkSemaphore> vk_imageAvailableSemaphores;
        std::vector<VkSemaphore> vk_renderFinishedSemaphores;
        std::vector<VkFence    > vk_inFlightFences;

        bool vk_framebufferResized = false;

        VkSurfaceKHR     vk_surface;
        GLFWwindow*         window;

        uint32_t currentFrame = 0;

        const std::vector<const char*> deviceExtensions = 
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        struct SwapChainSupportDetails 
        {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR>    present_Modes;
        };

        SwapChainSupportDetails query_SwapChainSupport   (VkPhysicalDevice device);
        VkSurfaceFormatKHR      choose_SwapSurfaceFormat (const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR        choose_SwapPresentMode   (const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D              choose_SwapExtent        (const VkSurfaceCapabilitiesKHR& capabilities);

        struct QueueFamilyIndices 
        {
            std::optional<uint32_t> graphics_Family;
            std::optional<uint32_t> present_Family;

            bool is_Complete() 
            {
                return graphics_Family.has_value() && present_Family.has_value();
            }
        };

        QueueFamilyIndices find_QueueFamilies(VkPhysicalDevice device);
    
        void init_Vulkan();
        void main_Loop();
        void clean_Up();

        static void framebuffer_ResizeCallback(GLFWwindow* window, int width, int height) 
        {
            auto app = reinterpret_cast<Vulkan_App*>(glfwGetWindowUserPointer(window));
            app->vk_framebufferResized = true;
        }
        
        void draw_Frame         ();
        void cleanup_SwapChain  ();
        void recreate_SwapChain ();

        void create_SyncObjects    ();
        void record_CommandBuffer  (VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void create_CommandBuffers ();

        void create_CommandPool      ();
        void create_Framebuffers     ();
        void create_RenderPass       ();
        void create_GraphicsPipeline ();

        VkShaderModule create_ShaderModule(const std::vector<char>& code);

        void create_Instance      ();
        void create_LogicalDevice ();
        void create_ImageViews    ();
        void create_SwapChain     ();

        void create_Surface               ();
        void pick_PhysicalDevice          ();
        bool is_DeviceSuitable            (VkPhysicalDevice device);
        bool check_DeviceExtensionSupport (VkPhysicalDevice device);
        bool check_ValidationLayerSupport ();
};