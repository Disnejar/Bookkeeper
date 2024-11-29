#pragma once
#include "backends/imgui_impl_vulkan.h"

// Data

extern VkAllocationCallbacks *g_Allocator;
extern VkInstance g_Instance;
extern VkPhysicalDevice g_PhysicalDevice;
extern VkDevice g_Device;
extern uint32_t g_QueueFamily;
extern VkQueue g_Queue;
extern VkDebugReportCallbackEXT g_DebugReport;
extern VkPipelineCache g_PipelineCache;
extern VkDescriptorPool g_DescriptorPool;

extern ImGui_ImplVulkanH_Window g_MainWindowData;
extern int g_MinImageCount;
extern bool g_SwapChainRebuild;

// #define APP_USE_UNLIMITED_FRAME_RATE
#ifdef DEBUG_MODE
#define APP_USE_VULKAN_DEBUG_REPORT
#endif

void check_vk_result(VkResult err);

#ifdef APP_USE_VULKAN_DEBUG_REPORT
    VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char *pLayerPrefix, const char *pMessage, void *pUserData);
#endif // APP_USE_VULKAN_DEBUG_REPORT

bool IsExtensionAvailable(const ImVector<VkExtensionProperties> &properties, const char *extension);

VkPhysicalDevice SetupVulkan_SelectPhysicalDevice(VkInstance instance);

void SetupVulkan(ImVector<const char *> instance_extensions);

void SetupVulkanWindow(ImGui_ImplVulkanH_Window *wd, VkSurfaceKHR surface, int width, int height);

void CleanupVulkan();

void CleanupVulkanWindow();

void FrameRender(ImGui_ImplVulkanH_Window *wd, ImDrawData *draw_data);

void FramePresent(ImGui_ImplVulkanH_Window *wd);
    
uint32_t findMemoryType(uint32_t type_filter, VkMemoryPropertyFlags properties);

//static void CreateVulkanTexture(ImageTexture *tex_data);
