# vulkan-first-chapter

> Vulkan test

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue)
![License](https://img.shields.io/badge/license-MIT-green)

---

## Sumário

- [Sobre](#sobre)
- [Requisitos](#requisitos)
- [Build](#build)
- [Testes](#testes)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Contribuindo](#contribuindo)
- [Licença](#licença)

---

## Sobre

Vulkan test

**Autor:** Matheus  
**Versão:** 1.0.0
**Padrão C++:** C++23

---

## Requisitos

| Ferramenta | Versão Mínima | Observação |
|------------|:-------------:|------------|
| CMake      | 3.20          | Necessário para CMakePresets.json |
| GCC        | 11+           | Alternativa: Clang 14+ ou MSVC 19.29+ |
| Clang      | 14+           | Recomendado com Clangd |
| Ninja      | 1.10+         | Gerador padrão dos presets |
| VCPKG      | recente       | Defina `VCPKG_ROOT` no ambiente |

### Instalação das dependências (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install -y cmake ninja-build gcc g++ clang
```

### Instalação das dependências (macOS)

```bash
brew install cmake ninja llvm
```

### Configuração do VCPKG

```bash
# Clone e bootstrap do VCPKG
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh        # Linux / macOS
# ~/vcpkg/bootstrap-vcpkg.bat     # Windows

# Adicione ao seu shell profile (~/.bashrc, ~/.zshrc, etc.)
export VCPKG_ROOT="$HOME/vcpkg"
export PATH="$VCPKG_ROOT:$PATH"
```

---

## Build

Este projeto usa **CMakePresets.json** para gerenciar as configurações de build.
Todos os presets são compatíveis com VSCode CMake Tools, CLion e a CLI do CMake.

### Listar presets disponíveis

```bash
cmake --list-presets
```

### Build de desenvolvimento (Debug)

```bash
# Com VCPKG (requer VCPKG_ROOT definido)
cmake --preset vcpkg-debug
cmake --build --preset build-vcpkg-debug
```

### Build de produção (Release)

```bash
cmake --preset vcpkg-release
cmake --build --preset build-vcpkg-release
```

### Executar

```bash
./build/vcpkg-debug/bin/vulkan-first-chapter
```

### Build sem presets (modo manual)

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

---

## Testes

Os testes são registrados com **CTest** e podem ser executados com:

```bash
# Após o build de debug
ctest --preset test-vcpkg-debug

# Ou manualmente
cd build/debug
ctest --output-on-failure
```

---

## Estrutura do Projeto

```
vulkan-first-chapter/
├── CMakeLists.txt          # Configuração principal do CMake
├── CMakePresets.json       # Presets de configure, build e test
├── README.md               # Este arquivo
├── .gitignore              # Padrões de arquivos ignorados pelo Git
├── .clangd                 # Configuração do servidor LSP Clangd
├── .clang-format           # Regras de formatação de código
├── cmake/
│   ├── CompilerWarnings.cmake  # Flags de warning para GCC/Clang/MSVC
│   └── (vcpkg via toolchain)   # Integração VCPKG via CMakePresets.json
├── src/
│   ├── CMakeLists.txt      # Target principal
│   └── main.cpp            # Ponto de entrada
├── include/
│   └── vulkan-first-chapter/
│       └── (headers públicos)
├── tests/
│   ├── CMakeLists.txt      # Targets de teste
│   └── test_main.cpp       # Testes unitários
└── docs/                   # Documentação (Doxygen, Markdown, etc.)
```

---

## Contribuindo

1. Faça um fork do repositório
2. Crie uma branch para sua feature: `git checkout -b feature/minha-feature`
3. Commit suas mudanças: `git commit -m 'feat: adiciona minha feature'`
4. Push para a branch: `git push origin feature/minha-feature`
5. Abra um Pull Request

### Convenção de commits

Este projeto segue o padrão [Conventional Commits](https://www.conventionalcommits.org/):

- `feat:` — nova funcionalidade
- `fix:` — correção de bug
- `docs:` — documentação
- `refactor:` — refatoração sem mudança de comportamento
- `test:` — adição ou correção de testes
- `chore:` — tarefas de manutenção (build, CI, deps)

---

## Licença

Copyright © 2026 Matheus. Todos os direitos reservados.

> Substitua esta seção pela licença do seu projeto.
> Exemplos: [MIT](https://opensource.org/licenses/MIT), [Apache 2.0](https://opensource.org/licenses/Apache-2.0), [GPL-3.0](https://opensource.org/licenses/GPL-3.0).

---

*Gerado com ❤️ por [cpp-gen](https://github.com/matpdev/cpp-gen) em 2026.*
