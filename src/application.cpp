#include "application.h"
#include <cstdint>

// ============================================================
// Lifecycle
// ============================================================

Application::Application() = default;

Application::~Application() = default;

void Application::run() {
  initWindow();
  initVulkan();
  mainLoop();
  cleanUp();
}

void Application::mainLoop() {
  double lastTime = glfwGetTime();
  uint32_t frameCount = 0;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    drawFrame();

    frameCount++;
    double currentTime = glfwGetTime();
    if (currentTime - lastTime >= 1.0) {
      double fps = frameCount / (currentTime - lastTime);
      std::cout << "FPS: " << fps << std::endl;
      frameCount = 0;
      glfwSetWindowTitle(
          window, ("Vulkan Triangle - FPS: " + std::to_string(fps)).c_str());
      lastTime = currentTime;
    }
  }

  vkDeviceWaitIdle(device);
}

void Application::cleanUp() {
  cleanupSwapChain();

  vkUnmapMemory(device, vertexBufferMemory);
  vkDestroyBuffer(device, vertexBuffer, nullptr);
  vkFreeMemory(device, vertexBufferMemory, nullptr);

  vkDestroyPipeline(device, graphicsPipeline, nullptr);
  vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

  vkDestroyRenderPass(device, renderPass, nullptr);

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    vkDestroyFence(device, inFlightFences[i], nullptr);
  }

  vkDestroyCommandPool(device, commandPool, nullptr);

  vkDestroyDevice(device, nullptr);

  if (enableValidationLayers) {
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }

  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window);
  glfwTerminate();
}

// ============================================================
// Vulkan Initialization
// ============================================================

void Application::initVulkan() {
  createInstance();
  setupDebugMessenger();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
  createSwapChain();
  createImageViews();
  createRenderPass();
  createGraphicsPipeline();
  createFramebuffers();
  createCommandPool();
  createVertexBuffer();
  createCommandBuffers();
  createSyncObjects();
}
