#pragma once

#include "vulkan_core.h"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vulkan/vulkan_core.h>

class Application {
public:
  Application();
  ~Application();

  void run();

  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  const std::vector<const char *> validationLayers = {
      "VK_LAYER_KHRONOS_validation"};

  const std::vector<Vertex> vertices = {
      {.pos = {0.0F, 0.0F}, .color = {1.0F, 1.0F, 1.0F}},

      {.pos = {0.500F, 0.000F}, .color = {1.0F, 0.0F, 0.0F}},
      {.pos = {0.250F, 0.433F}, .color = {1.0F, 0.8F, 0.0F}},
      {.pos = {-0.250F, 0.433F}, .color = {0.0F, 1.0F, 0.0F}},
      {.pos = {-0.500F, 0.000F}, .color = {0.0F, 1.0F, 1.0F}},
      {.pos = {-0.250F, -0.433F}, .color = {0.0F, 0.0F, 1.0F}},
      {.pos = {0.250F, -0.433F}, .color = {1.0F, 0.0F, 1.0F}},
  };

  // 6 triângulos a partir do centro
  const std::vector<uint16_t> indices = {
      0, 1, 2, 0, 2, 3, 0, 3, 4, 0,
      4, 5, 0, 5, 6, 0, 6, 1, // fecha o hexágono ligando o último ao primeiro
  };

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

private:
  // --- Window ---
  static void error_callback(int error, const char *description);
  void initWindow();
  static void framebufferResizedCallback(GLFWwindow *window, int width,
                                         int height);

  // --- Lifecycle ---
  void initVulkan();
  void mainLoop();
  void cleanUp();

  // --- Instance ---
  void createInstance();
  bool checkValidationLayerSupport();
  std::vector<const char *> getRequiredExtensions();
  uint32_t findMemoryType(uint32_t typeFilter,
                          VkMemoryPropertyFlags properties);

  // --- Debug ---
  void setupDebugMessenger();
  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &createInfo);
  VkResult CreateDebugUtilsMessengerEXT(
      VkInstance instance,
      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
      const VkAllocationCallbacks *pAllocator,
      VkDebugUtilsMessengerEXT *pDebugMessenger);
  void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                     VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks *pAllocator);
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData) {

    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
      std::cerr << "Validation layer: " << pCallbackData->pMessage << '\n';
    }

    return VK_FALSE;
  }

  // --- Surface & Physical Device ---
  void createSurface();
  void pickPhysicalDevice();
  bool isDeviceSuitable(VkPhysicalDevice device);
  int rateDeviceSuitability(VkPhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

  // --- Logical Device ---
  void createLogicalDevice();

  // --- Swap Chain ---
  void createSwapChain();
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
  void recreateSwapChain();
  void cleanupSwapChain();

  // --- Image Views & Render Pass ---
  void createImageViews();
  void createRenderPass();
  void createVertexBuffer();
  void createIndexBuffer();
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  // --- Graphics Pipeline ---
  void createGraphicsPipeline();
  VkShaderModule createShaderModule(const std::vector<char> &code);
  static std::vector<char> readFile(const std::string &filename);
  void createDescriptorSetLayout();

  // --- Framebuffers & Commands ---
  void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                    VkMemoryPropertyFlags properties, VkBuffer &buffer,
                    VkDeviceMemory &bufferMemory);
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffers();
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
  void createUniformBuffers();
  void updateUniformBuffer(uint32_t currentImage);
  void createDescriptorPool();
  void createDescriptorSets();
  void createTextureImage();
  VkImageView createImageView(VkImage image, VkFormat format);
  void createTextureImageView();
  void createTextureSampler();

  // --- Rendering ---
  void drawFrame();
  void createSyncObjects();

  void createImage(uint32_t width, uint32_t height, VkFormat format,
                   VkImageTiling tiling, VkImageUsageFlags usage,
                   VkMemoryPropertyFlags properties, VkImage &image,
                   VkDeviceMemory &imageMemory);

  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);

  void transitionImageLayout(VkImage image, VkFormat format,
                             VkImageLayout oldLayout, VkImageLayout newLayout);

  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width,
                         uint32_t height);

  // --- Device Extensions ---
  const std::vector<const char *> deviceExtensions = {
      VK_KHR_SWAPCHAIN_EXTENSION_NAME,
  };

  // --- Constants ---
  static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

  // --- Member Variables ---
  GLFWwindow *window = nullptr;

  VkInstance instance = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;
  VkQueue graphicsQueue;
  VkQueue presentQueue;
  VkSurfaceKHR surface;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  std::vector<VkImageView> swapChainImageViews;

  VkRenderPass renderPass;
  VkPipeline graphicsPipeline;
  VkDescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout pipelineLayout;

  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;
  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;
  void *vertexBufferMapped = nullptr;

  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSets;

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;

  VkImage textureImage;
  VkDeviceMemory textureImageMemory;

  VkImageView textureImageView;
  VkSampler textureSampler;

  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;
  std::vector<void *> uniformBuffersMapped;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  uint32_t currentFrame = 0;
  bool framebufferResized = false;
};
