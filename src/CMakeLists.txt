# =============================================================================
# =============================================================================
# CMakeLists.txt — Target principal de vulkan-first-chapter
# =============================================================================
# Layout ativo: two-root
# Para detalhes sobre o layout, veja o CMakeLists.txt raiz.
# =============================================================================

# ── Executável ────────────────────────────────────────────────────────────────

add_executable(${PROJECT_NAME}
    main.cpp
    # Adicione outros arquivos .cpp aqui conforme o projeto crescer.
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        project_warnings
        # Adicione dependências aqui:
        # fmt::fmt
        # nlohmann_json::nlohmann_json
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD          23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS        OFF
)


