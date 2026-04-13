/**
 * @file main.cpp
 * @brief Ponto de entrada do projeto vulkan-first-chapter.
 *
 * @author Matheus
 * @version 1.0.0
 * @date 2026
 *
 * Layout: two-root
 */

#include <iostream>
#include <string_view>

// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief Exibe uma mensagem de boas-vindas no terminal.
 * @param project_name Nome do projeto a ser exibido.
 */
void greet(std::string_view project_name) {
    std::cout << "Hello from " << project_name << "!\n";
}

// ─────────────────────────────────────────────────────────────────────────────

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    greet("vulkan-first-chapter");
    return 0;
}
