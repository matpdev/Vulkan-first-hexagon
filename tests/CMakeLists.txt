# =============================================================================
# =============================================================================
# tests/CMakeLists.txt — Testes de vulkan-first-chapter
# =============================================================================
# Layout ativo: two-root
#
# Os testes são executados com:
#   cmake --preset debug && ctest --preset test-debug --output-on-failure
#   cd build && ctest -V                  (verbose)
#   cd build && ctest -R <nome>           (filtrar por nome)
# =============================================================================

# ── Target de teste principal ─────────────────────────────────────────────────

add_executable(vulkan_first_chapter_tests
    test_main.cpp
    # Adicione arquivos de teste adicionais aqui:
    # test_feature_a.cpp
    # test_feature_b.cpp
)

target_include_directories(vulkan_first_chapter_tests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vulkan_first_chapter_tests
    PRIVATE
        project_warnings
        # Adicione frameworks de teste aqui se necessário:
        # Catch2::Catch2WithMain
        # GTest::gtest_main
        # doctest::doctest
)

set_target_properties(vulkan_first_chapter_tests PROPERTIES
    CXX_STANDARD          23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS        OFF
)

# ── Registro no CTest ─────────────────────────────────────────────────────────

# Registra o executável como um teste no CTest.
# O executável deve retornar 0 para indicar sucesso.
add_test(
    NAME    vulkan-first-chapter_unit_tests
    COMMAND vulkan_first_chapter_tests
)

# Propriedades do teste (timeout em segundos, variáveis de ambiente, etc.)
set_tests_properties(vulkan-first-chapter_unit_tests PROPERTIES
    TIMEOUT 30
    LABELS  "unit"
)

# ── Dica: Adicionando testes individuais ──────────────────────────────────────
# Para granularidade maior (cada função de teste separada no CTest), use:
#
# add_test(NAME vulkan-first-chapter_test_greet   COMMAND vulkan_first_chapter_tests greet)
# add_test(NAME vulkan-first-chapter_test_feature COMMAND vulkan_first_chapter_tests feature)
#
# Isso requer que seu executável de testes aceite o nome do teste como argumento.
