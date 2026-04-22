# =============================================================================
# CMakeLists.txt — Target principal de vulkan-first-chapter
# =============================================================================

add_executable(${PROJECT_NAME}
    main.cpp
    application.cpp
    window.cpp
    vulkan_core.cpp
    swapchain.cpp
    graphics.cpp
    commands.cpp
    stb_image.cpp
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(Stb REQUIRED)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Stb_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        project_warnings
        glfw
        glm::glm
        spdlog::spdlog
        Vulkan::Vulkan
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD          23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS        OFF
)
