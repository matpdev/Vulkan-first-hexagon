#include "application.h"

#include <stdexcept>

// ============================================================
// Window
// ============================================================

void Application::initWindow() {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    throw std::runtime_error("Falha ao inicializar o GLFW!");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Triangle", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Falha ao criar a janela GLFW!");
  }
}

void Application::error_callback(int error, const char *description) {
  std::cerr << "Erro do GLFW [" << error << "]: " << description << std::endl;
}
