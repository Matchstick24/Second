#pragma once

// INCLUDES //

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "vke_device.h"
#include <glm/glm.hpp>
#include <vector>

// MAIN //

namespace vke
{
class VkeModel
{
    public:

        struct Vertex 
        {
            glm::vec3 position{};
            glm::vec3 color{};

            static std::vector<VkVertexInputBindingDescription>   getBindingDescriptions  ();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

        };

        VkeModel(VkeDevice &device, const std::vector<Vertex> &vertices);
        ~VkeModel();

        VkeModel(const VkeModel &) = delete;
        VkeModel &operator=(const VkeModel &) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

    private:

        void createVertexBuffers(const std::vector<Vertex> &vertices);
       
        VkeDevice &VkeDevice;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;

};
} // namespace vke