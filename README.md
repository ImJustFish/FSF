# Fidel Save System (FSF)

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![C++17](https://img.shields.io/badge/C++-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-brightgreen)
![CMake](https://img.shields.io/badge/Build-CMake-informational)

> ⚠️ **IMPORTANTE LEGAL**: Este proyecto utiliza la biblioteca estándar de C++. 
> Asegúrate de cumplir con los términos de licencia de tu compilador.

## 📋 Tabla de Contenidos
- [Descripción](#-descripción)
- [Características](#✨-características)
- [Requisitos](#📋-requisitos)
- [Instalación](#📦-instalación)
- [Uso](#🚀-uso)
- [API](#📚-api)
- [Ejemplos](#🎮-ejemplos)
- [Construcción](#🔧-construcción)
- [Pruebas](#🧪-pruebas)
- [Contribuir](#🤝-contribuir)
- [Licencia](#📄-licencia)
- [Avisos Legales](#⚠️-avisos-legales)
- [Autor](#👤-autor)

## 📖 Descripción

**Fidel Save System (FSF)** es una biblioteca C++ ligera y multiplataforma para manejo de archivos de guardado con cifrado integrado. Diseñada específicamente para videojuegos y aplicaciones que requieren persistencia de datos segura.

**Casos de uso ideales:**
- Sistemas de guardado en videojuegos
- Configuración de aplicaciones
- Datos de usuario persistentes
- Archivos de progreso cifrados

## ✨ Características

- ✅ **Cifrado básico** con semilla personalizable (0-255)
- ✅ **Múltiples tipos de datos**: `int`, `float`, `string`, `vector`
- ✅ **Gestión automática de archivos**
- ✅ **Sin dependencias externas** - Solo C++17
- ✅ **Diseño seguro ante excepciones**
- ✅ **Multiplataforma**: Windows, Linux, macOS
- ✅ **Interfaz simple e intuitiva**
- ✅ **Modo header-only disponible**

## 📋 Requisitos

### Compilador (uno de los siguientes):
- **GCC** 7.0 o superior
- **Clang** 5.0 o superior  
- **MSVC** 2017 o superior (Visual Studio 15.7+)

### Estándar C++:
- **C++17** o superior

### Sistema (cualquiera):
- **Linux** (Ubuntu 18.04+, Fedora 30+, etc.)
- **Windows** (7, 10, 11)
- **macOS** (10.14+)

### Herramientas recomendadas:
- **CMake** 3.15+
- **Git** 2.20+
- **Make** o **Ninja**

## 📦 Instalación

### Método 1: CMake (Recomendado)

```cmake
# En tu CMakeLists.txt
cmake_minimum_required(VERSION 3.15)

# Opción 1: Como subdirectorio
add_subdirectory(path/to/fsf)
target_link_libraries(tu_proyecto fsf)

# Opción 2: Usando find_package (después de install)
find_package(fsf REQUIRED)
target_link_libraries(tu_proyecto fsf::fsf)
