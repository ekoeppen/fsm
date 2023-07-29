cmake_minimum_required(VERSION 3.5)
project(FSM CXX)

add_custom_target(
  fmt
  COMMAND /usr/local/clang/bin/clang-format
  -i
  ${PROJECT_SOURCE_DIR}/test/main.cpp
  ${PROJECT_SOURCE_DIR}/include/fsm.h)

add_executable(fsm_test test/main.cpp)
target_include_directories(fsm_test PRIVATE include)
set_property(TARGET fsm_test PROPERTY CXX_STANDARD 14)
