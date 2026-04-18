#include "triangleGenerator.h"
#include <cstdlib>

#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  TriangleGenerator app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
