project("C - Rust ffi calls playground")
cmake_minimum_required(VERSION 3.22)
add_library(ffi ffi.cpp)
add_custom_target(main
  ALL
  COMMAND rustc ${CMAKE_SOURCE_DIR}/main.rs -L. -lffi
  DEPENDS ffi
)
