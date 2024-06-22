cmake_minimum_required (VERSION 3.8)

project ("CDataStructures" LANGUAGES C)

set(CMAKE_C_STANDARD 11)

file(GLOB COOP_FILES "COOP/*.c")
file(GLOB TEST_FILES "Tests/*.c")
file(GLOB Q_FILES "DataStructures/*.c")
file(GLOB ANS_FILES "./*.c")
set(SOURCE_FILES "")
list(APPEND SOURCE_FILES ${COOP_FILES} ${TEST_FILES} ${Q_FILES} ${ANS_FILES})
include_directories("COOP" "Tests" "DataStructures")
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_executable(CDataStructures ${SOURCE_FILES})

if (UNIX AND NOT APPLE)
    # For non-osx platforms
    # Specify `-Wno-incompatible-pointer-types` for GCC to avoid it emitting
    # a lot of warnings due to the function parameter types
    target_compile_options(${PROJECT_NAME} PRIVATE -Wno-incompatible-pointer-types)
endif()

if (UNIX)

    # Add AddressSanitizer if supported by compiler:
    include(CheckCCompilerFlag)
    CHECK_C_COMPILER_FLAG("-fsanitize=address" COMPILER_SUPPORTS_ASAN)
    if(COMPILER_SUPPORTS_ASAN)
        target_compile_options(your_executable_name PUBLIC -fsanitize=address)
        target_link_libraries(your_executable_name -fsanitize=address)
    endif()

endif()