cmake_policy(SET CMP0140 NEW)
cmake_minimum_required(VERSION 3.25)

project(MyMain)

set(str "apa\\\;kaka\\\;burk")

set(str2 "prutt=${str}")

message("Den e ${str}")

set(command_exe "${CMAKE_SOURCE_DIR}/foo.sh hej")

function(fie)
  message("Fie gets ${ARGV0}")
  set(a ${ARGV0})
  set(a "${a};ny")
  message("i fie a = ${a}")
  return(PROPAGATE a)
endfunction(fie)

function(fum)
  message("Fum gets ${ARGV0}")
  set(a ${ARGV0})
  fie("${a}")
  message("i fum a = ${a}")
endfunction(fum)

fum("hej;daa")

add_custom_command(
  OUTPUT foo_result.txt
  COMMAND ${CMAKE_SOURCE_DIR}/foo.sh "${str2}"
  COMMAND_EXPAND_LISTS
)

add_custom_target(
  foo
  DEPENDS foo_result.txt
)

add_executable(
  main
  hello.cpp
)
