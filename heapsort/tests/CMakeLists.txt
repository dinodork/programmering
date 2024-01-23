find_package(Catch2 REQUIRED)

add_executable(heapsort-test
  test.cpp
)

target_compile_options(heapsort-test PRIVATE -Wall -Werror -Wextra)

target_include_directories(heapsort-test
  PUBLIC ${CMAKE_SOURCE_DIR}
)

target_link_libraries(heapsort-test
  PRIVATE Catch2::Catch2WithMain
)
