# Fidel Save System (FSF)

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![C++17](https://img.shields.io/badge/C++-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-brightgreen)
![CMake](https://img.shields.io/badge/Build-CMake-informational)

## 📋 Content table
- [Description](#-description)
- [Caracteristics](#-caracteristics)
- [Requirements](#📋-requirements)
- [Instalation](#📦-instalation)
- [Use](#🚀-use)
- [API](#📚-api)
- [Examples](#🎮-examples)
- [Construction](#🔧-construction)
- [Tests](#🧪-Tests)
- [Contribute](#🤝-contribute)
- [License](#📄-license)
- [Legal Warnings](#⚠️-legal-warnings)
- [Autor](#👤-autor)

## 📖 Description

**Fidel Save System (FSF)** is a C++ library for managing save files with integrated encryption. Designed specifically for video games and applications that require secure data safely.

## ✨ Caracteristics

- ✅ **Basic encpryption** with custom seed (0-255)
- ✅ **Multiple data types**: `int`, `float`, `string`, `vector`
- ✅ **Automatic file management**
- ✅ **No external dependencies** - C++17 only
- ✅ **Exception Safe Design**
- ✅ **Multiplataform**: Windows, Linux, macOS

## 📋 Requirements

### Compiler (one of the following):
- **GCC** 7.0+
- **Clang** 5.0+  
- **MSVC** 2017+ (Visual Studio 15.7+)

### Standar C++:
- **C++17+**

### System :
- **Linux** (Ubuntu 18.04+, Fedora 30+, etc.)
- **Windows** (7, 10, 11)
- **macOS** (10.14+)

### Recomendended tools:
- **CMake** 3.15+
- **Git** 2.20+
- **Make** or **Ninja**

## 📦 Instalation

### Método 1: CMake (Recomended)

```cmake
# In CMakeLists.txt
cmake_minimum_required(VERSION 3.15)

# Option 1: as a subdirectory
add_subdirectory(path/to/fsf)
target_link_libraries(your_project fsf)

# Option 2: Using find_package (after install)
find_package(fsf REQUIRED)
target_link_libraries(your_project fsf::fsf)
