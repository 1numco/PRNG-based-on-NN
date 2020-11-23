include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB files *.cpp)
add_library(Lib ${files})