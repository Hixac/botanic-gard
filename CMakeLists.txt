cmake_minimum_required(VERSION 3.20...3.27 FATAL_ERROR)

project(
  botanic-gard
  VERSION 0.1
  DESCRIPTION "Метковая садовая"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -g) # убрать в случае ненадобности
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# TODO: Make file adder into application
FILE(COPY res/gard.jpg DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY res/gard.jpg DESTINATION "${CMAKE_BINARY_DIR}/Debug")
FILE(COPY res/JetBrainsMonoNLNerdFontMono-Regular.ttf DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY res/JetBrainsMonoNLNerdFontMono-Regular.ttf DESTINATION "${CMAKE_BINARY_DIR}/Debug")

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC src/)
add_subdirectory(src/) # исходный код
target_include_directories(src PUBLIC src/)
target_link_libraries(${PROJECT_NAME} src)

target_include_directories(src PUBLIC ext/)
add_subdirectory(ext/)  # файлы с библиотекой imgui
target_link_libraries(src imgui)

target_include_directories(src PUBLIC nativefiledialog-extended/)
add_subdirectory(nativefiledialog-extended/)  # файлы с библиотекой imgui
target_link_libraries(src nfd)

target_include_directories(${PROJECT_NAME} PUBLIC glfw/include/GLFW/)
target_include_directories(src PUBLIC glfw/include/GLFW/)
add_subdirectory(glfw/) # библиотека с загрузкой окна
target_link_libraries(src glfw ${GLFW_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
