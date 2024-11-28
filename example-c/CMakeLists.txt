cmake_minimum_required(VERSION 3.10)
project(example-c C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(example-c main.c)

#link_directories("C:/Users/danie/Code/Rust/example-ffi/example-ffi/build/lib")

find_library(EXAMPLE_FFI_LIB example-ffi
    PATHS "C:/Users/danie/Code/Rust/example-ffi/example-ffi/build/lib"
    REQUIRED
)

if(EXAMPLE_FFI_LIB)
    message(STATUS "Found example-ffi library: ${EXAMPLE_FFI_LIB}")
    target_link_libraries(example-c PRIVATE ${EXAMPLE_FFI_LIB})
else()
    message(FATAL_ERROR "example-ffi library not found.")
endif()

target_include_directories(example-c PRIVATE "C:/Users/danie/Code/Rust/example-ffi/example-ffi/build/include")