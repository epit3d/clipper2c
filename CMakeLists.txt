cmake_minimum_required(VERSION 3.18)
project(clipper2c LANGUAGES CXX C)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# turn off unused parts of Clipper2
set(CLIPPER2_TESTS OFF)
set(CLIPPER2_EXAMPLES OFF)
set(CLIPPER2_UTILS OFF)

option(BUILD_SHARED_LIBS ON)

add_compile_options(-fPIC)

add_subdirectory(vendor/Clipper2/CPP)

file(GLOB_RECURSE SOURCE_FILES  src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.h) 

set(PCFILE "${CMAKE_CURRENT_BINARY_DIR}/clipper2c.pc")

add_library(clipper2c SHARED ${INCLUDE_FILES} ${SOURCE_FILES})

# add executable if CLIPPER2_EXAMPLES is ON
if(CLIPPER2_EXAMPLES)
    add_executable(offset examples/offset.c)

    # link offset.c
    target_link_libraries(
            offset
            PRIVATE clipper2c Clipper2
    )
endif()

target_include_directories(offset PUBLIC clipper2c/include)

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


CONFIGURE_FILE(clipper2c.pc.cmakein "${PCFILE}" @ONLY)

install(TARGETS clipper2c
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/clipper2c
)

install(FILES ${PCFILE} DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

target_compile_features(clipper2c PUBLIC cxx_std_17)
