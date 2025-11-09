# =========================================================
# FindExternalDeps.cmake
# Ensures all required external dependencies are found
# =========================================================

message(STATUS "Checking external dependencies...")

set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/External")

# Helper macro for clear error handling
macro(require_path PATH DESCRIPTION)
    if(NOT EXISTS "${PATH}")
        message(FATAL_ERROR "Missing ${DESCRIPTION}: ${PATH}")
    else()
        message(STATUS "Found ${DESCRIPTION}: ${PATH}")
    endif()
endmacro()

# --- Check essential folder structure ---
require_path("${EXTERNAL_DIR}/include" "External include folder")
require_path("${EXTERNAL_DIR}/lib" "External library folder")
require_path("${EXTERNAL_DIR}/bin" "External binary folder")

# --- Check specific includes ---
set(REQUIRED_INCLUDES
    "${EXTERNAL_DIR}/include/glad/glad.h"
    "${EXTERNAL_DIR}/include/GLFW/glfw3.h"
    "${EXTERNAL_DIR}/include/glm/glm.hpp"
    "${EXTERNAL_DIR}/include/stb_image.h"
)

foreach(INC ${REQUIRED_INCLUDES})
    if(NOT EXISTS "${INC}")
        message(WARNING "Missing header: ${INC}")
    else()
        message(STATUS "Found header: ${INC}")
    endif()
endforeach()

# --- Check library files ---
set(REQUIRED_LIBS
    "${EXTERNAL_DIR}/lib/glfw3.lib"
    "${EXTERNAL_DIR}/lib/assimp-vc143-mt.lib"
)

foreach(LIB ${REQUIRED_LIBS})
    if(NOT EXISTS "${LIB}")
        message(WARNING "Missing library: ${LIB}")
    else()
        message(STATUS "Found library: ${LIB}")
    endif()
endforeach()

# --- Check runtime DLLs ---
set(REQUIRED_DLLS
    "${EXTERNAL_DIR}/bin/assimp-vs143-mt.dll"
)

foreach(DLL ${REQUIRED_DLLS})
    if(NOT EXISTS "${DLL}")
        message(WARNING "Missing DLL: ${DLL}")
    else()
        message(STATUS "Found DLL: ${DLL}")
    endif()
endforeach()

message(STATUS "External dependency check complete.")
