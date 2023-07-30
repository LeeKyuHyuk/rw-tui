cmake_minimum_required (VERSION 3.11)

project(rw-tui
  LANGUAGES CXX
  VERSION 1.0.0
)

file(GLOB_RECURSE RW_TUI_SRC
     "src/*.cpp"
)
 
add_executable(rw-tui ${RW_TUI_SRC})
target_include_directories(rw-tui PRIVATE src/include)

set_property(TARGET rw-tui PROPERTY CXX_STANDARD 17)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/ftxui ${CMAKE_BINARY_DIR}/ftxui EXCLUDE_FROM_ALL)
 
target_link_libraries(rw-tui
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  -static
)