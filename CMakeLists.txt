cmake_minimum_required(VERSION 3.15)
project(SangeEngine LANGUAGES CXX)

# ─────────────────────────────
# C++ SETTINGS
# ─────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─────────────────────────────
# FOLDER PATHS
# ─────────────────────────────
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/External)

# ─────────────────────────────
# SOURCE + HEADER FILES
# ─────────────────────────────
# Your engine’s code (.cpp files)
file(GLOB_RECURSE SRC_ENGINE ${SRC_DIR}/*.cpp)

# External sources (like glad.c)
file(GLOB_RECURSE SRC_EXTERNAL ${EXTERNAL_DIR}/src/*.c)

# Header files
file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.h)

# ─────────────────────────────
# EXECUTABLE
# ─────────────────────────────
add_executable(${PROJECT_NAME}
    ${SRC_ENGINE}
    ${SRC_EXTERNAL}
    ${HEADER_FILES}
)

# ─────────────────────────────
# INCLUDE DIRECTORIES
# ─────────────────────────────
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${INCLUDE_DIR}
        ${EXTERNAL_DIR}/include
)

# ─────────────────────────────
# LIBRARY DIRECTORIES & LINKING
# ─────────────────────────────
target_link_directories(${PROJECT_NAME}
    PRIVATE
        ${EXTERNAL_DIR}/lib
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw3
        opengl32
)

# ─────────────────────────────
# FOLDER ORGANIZATION (for Visual Studio)
# ─────────────────────────────
# Group source files by folder tree
source_group(TREE ${SRC_DIR} FILES ${SRC_ENGINE})
source_group(TREE ${INCLUDE_DIR} FILES ${HEADER_FILES})

# Option 1: put external source (like glad.c) in a simple "External" virtual folder
source_group("External" FILES ${SRC_EXTERNAL})

# ─────────────────────────────
# OUTPUT DIRECTORY (optional)
# ─────────────────────────────
# Place built executables in /bin/Debug or /bin/Release
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>
)
