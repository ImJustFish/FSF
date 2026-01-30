### Description
Just making a random library.

### Method 1: CMake (Recomended)

```cmake
# In CMakeLists.txt
cmake_minimum_required(VERSION 3.15)

# Option 1: as a subdirectory
add_subdirectory(path/to/fsf)
target_link_libraries(your_project fsf)

# Option 2: Using find_package (after install)
find_package(fsf REQUIRED)
target_link_libraries(your_project fsf::fsf)
```

### Method 2: Use the dynamic library

```bash
# Compile the project
cd /path/to/library/fsf
mkdir build && cd build
cmake ..

#Windows
cmake --build
#Linux
make
```
