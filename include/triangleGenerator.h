#include <cstdint>
#include <optional>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capibilites;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class TriangleGenerator {
public:
  TriangleGenerator();
  ~TriangleGenerator();

  void run();

  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  const std::vector<const char *> validationLayers = {
      "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

private:
  static void error_callback(int error, const char *description);
  void initWindow();
  void initVulkan();
  void mainLoop();
  void cleanUp();
  void setupDebugMessenger();
  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &createInfo);
  void pickPhysicalDevice();
  void createLogicalDevice();
  void createSurface();
  void createSwapChain();
  void createImageViews();
  void createInstance();
  void createGraphicsPipeline();
  bool checkValidationLayerSupport();
  void createRenderPass();
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffer();
  bool isDeviceSuitable(VkPhysicalDevice device);
  std::vector<const char *> getRequiredExtensions();
  int rateDeviceSuitability(VkPhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
  VkShaderModule createShaderModule(const std::vector<char> &code);
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

  static std::vector<char> readFile(const std::string &filename);

  const std::vector<const char *> deviceExtensions = {
      VK_KHR_SWAPCHAIN_EXTENSION_NAME,
  };

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

  VkResult CreateDebugUtilsMessengerEXT(
      VkInstance instance,
      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
      const VkAllocationCallbacks *pAllocator,
      VkDebugUtilsMessengerEXT *pDebugMessenger);

  void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                     VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks *pAllocator);

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
  VkPipelineLayout pipelineLayout;
  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkCommandPool commandPool;
  VkCommandBuffer commandBuffer;
};
