#pragma once

// Includes //

#include <memory>

#include "vke_window.h"
#include "vke_device.h"
#include "vke_pipeline.h"
#include "vke_swapchain.h"
#include "vke_model.h"

// Main //

namespace vke
{

class VkeApp
{
    public:

        static constexpr int WIDTH  = 800;
        static constexpr int HEIGHT = 600;

        VkeApp();
        ~VkeApp();

        VkeApp(const VkeApp &) = delete;
        VkeApp &operator=(const VkeApp &) = delete;

        void Run();

    private:

        VkeWindow vkeWindow{WIDTH, HEIGHT, "Vulkan Window"};
        VkeDevice vkeDevice{vkeWindow};
        VkeSwapchain vkeSwapchain{vkeDevice, vkeWindow.getExtent()};
        
        std::unique_ptr<VkePipeline> vkePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<VkeModel> vkeModel;

};

} // namespace vke
