#pragma once
#include "../VulkanBackend.h"

enum ImageColorFormat
{
    BGRA = 0,
    RGBA = 1
};

struct ImageTexture
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

    ImageTexture();
};

VkFormat GetVulkanColorFormat(ImageColorFormat fmt);

bool CreateVulkanTexture(ImageTexture *tex_data, uint8_t *data, ImageColorFormat fmt = ImageColorFormat::RGBA);

void RemoveVulkanTexture(ImageTexture *tex_data);
