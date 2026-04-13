cmake_minimum_required(VERSION 3.20)

# =============================================================================
# Declaração do projeto
# =============================================================================
# A versão aqui definida é automaticamente acessível via
# VULKAN_FIRST_CHAPTER_VERSION_MAJOR, VULKAN_FIRST_CHAPTER_VERSION_MINOR, etc.
project(
    vulkan-first-chapter
    VERSION 1.0.0
    DESCRIPTION "Vulkan test"
    LANGUAGES CXX
)

# Impede builds in-source, que misturam artefatos com o código fonte.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
        "Build in-source detectado!\n"
        "Por favor, crie um diretório separado para o build:\n"
        "  cmake -B build\n"
    )
endif()

# =============================================================================
# Padrão e configurações C++
# =============================================================================

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Desabilita extensões específicas do compilador (ex: gnu++20) para garantir
# portabilidade entre GCC, Clang e MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

# Exporta compile_commands.json para uso com Clangd, clang-tidy e IDEs.
# O arquivo é gerado no diretório de build e vinculado à raiz pelo .clangd.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Organiza os binários em subdiretórios padrão dentro do build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# =============================================================================
# Módulos CMake auxiliares
# =============================================================================

# Adiciona cmake/ ao caminho de busca de módulos, permitindo usar
# include(CompilerWarnings) e outros módulos do projeto.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# =============================================================================
# Integração VCPKG
# =============================================================================
# O VCPKG é integrado via toolchain file, que deve ser definido ANTES do
# primeiro projeto(). A forma recomendada é usar CMakePresets.json (já
# configurado neste projeto) ou passar na linha de comando:
#
#   cmake -B build --preset vcpkg-debug
#
# Variável de ambiente necessária:
#   VCPKG_ROOT=/caminho/para/vcpkg
#
# Para instalar dependências listadas em vcpkg.json, execute:
#   vcpkg install
# (ou deixe o CMake fazer automaticamente via manifest mode)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "VCPKG toolchain file"
    )
    message(STATUS "VCPKG: usando toolchain em ${CMAKE_TOOLCHAIN_FILE}")
endif()

# =============================================================================
# Módulos internos
# =============================================================================

# Flags de warning do compilador definidas em cmake/CompilerWarnings.cmake.
# Aplique ao seu target com: target_link_libraries(<target> PRIVATE project_warnings)
include(CompilerWarnings)

# =============================================================================
# Subdiretórios
# =============================================================================
# Layout: Two-Root
# Headers públicos em include/ (sem subdir de namespace), implementações em src/.
# Referência: convenção simples para bibliotecas com interface mínima.


add_subdirectory(src)


# =============================================================================
# Testes
# =============================================================================

# Opção de build que pode ser desabilitada externamente:
#   cmake -B build -DVULKAN_FIRST_CHAPTER_BUILD_TESTS=OFF
option(VULKAN_FIRST_CHAPTER_BUILD_TESTS "Compilar os testes de vulkan-first-chapter" ON)

if(VULKAN_FIRST_CHAPTER_BUILD_TESTS)
    message(STATUS "vulkan-first-chapter: testes habilitados")
    enable_testing()
    add_subdirectory(tests)
endif()

# =============================================================================
# Informações de configuração (exibidas ao final do cmake)
# =============================================================================

message(STATUS "")
message(STATUS "=== vulkan-first-chapter v${PROJECT_VERSION} ===")
message(STATUS "  Compilador       : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Padrão C++       : C++${CMAKE_CXX_STANDARD}")
message(STATUS "  Tipo de build    : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Diretório de build: ${CMAKE_BINARY_DIR}")
message(STATUS "  Layout           : two-root")
message(STATUS "  Testes           : ${VULKAN_FIRST_CHAPTER_BUILD_TESTS}")
message(STATUS "")
