cmake_minimum_required(VERSION 3.18)
project(clipper2c LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS ON)

add_compile_options(-fPIC)

add_subdirectory(vendor/Clipper2/CPP)

file(GLOB_RECURSE SOURCE_FILES  src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.h) 

add_library(clipper2c SHARED ${INCLUDE_FILES} ${SOURCE_FILES})

target_link_libraries(
  clipper2c
  PRIVATE Clipper2
)

target_include_directories(clipper2c PUBLIC clipper2c/include)


set_target_properties(clipper2c PROPERTIES FOLDER Libraries
                                VERSION ${PROJECT_VERSION}
                                SOVERSION ${PROJECT_VERSION_MAJOR}
                                PUBLIC_HEADER "${INCLUDE_FILES}"
)

install(TARGETS clipper2c
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/clipper2c
)

target_compile_features(clipper2c PUBLIC cxx_std_17)
