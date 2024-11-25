#pragma once
#include "imgui.h"
#include "imgui_impl_vulkan.h"

struct ImageTextureData
{
    VkDescriptorSet DS; // Descriptor set: this is what you'll pass to Image()
    int Width;
    int Height;
    int Channels;

    // Need to keep track of these to properly cleanup
    VkImageView ImageView;
    VkImage Image;
    VkDeviceMemory ImageMemory;
    VkSampler Sampler;
    VkBuffer UploadBuffer;
    VkDeviceMemory UploadBufferMemory;

    ImageTextureData() { memset(this, 0, sizeof(*this)); }
};

class Image
{
    ImageTextureData data;

    Image(uint8_t *data, int w, int h, char fmt);

    ~Image();

    operator ImTextureID() const { return (ImTextureID)data.DS; }
};
