cmake_minimum_required(VERSION 3.10)
project(sema_top)

option(SEMA_TESTS "Enable Tests" OFF)
option(SEMA_EXAMPLES "Enable Examples" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build Type" FORCE)
endif()

# Add dependencies
add_subdirectory(third_party/bln_log)
add_subdirectory(third_party/bln_net)

add_compile_options(-Wall -Wextra -pedantic)

# Sema lib
set(SEMA_LIB sema)
add_library(${SEMA_LIB} "")

set_target_properties(${SEMA_LIB} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_sources(${SEMA_LIB} PRIVATE
    include/sema/actions.h
    include/sema/client.h
    include/sema/log.h
    include/sema/protocol.h
    include/sema/sema.h
    include/sema/state.h
    include/sema/types.h    

    src/client.cpp
    src/protocol.cpp
    src/sema.cpp
)

target_include_directories(${SEMA_LIB} PUBLIC include)
target_compile_features(${SEMA_LIB} PUBLIC cxx_std_20)

target_link_libraries(${SEMA_LIB} PUBLIC
    bln_log
    bln_net
)

# Sema service
set(SEMA_SERVICE sema_service)
add_executable(${SEMA_SERVICE} src/service.cpp)

set_target_properties(${SEMA_SERVICE} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)

target_compile_features(${SEMA_SERVICE} PUBLIC cxx_std_20)
target_link_libraries(${SEMA_SERVICE} PUBLIC sema)

# Log Level
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${SEMA_LIB}     PUBLIC  BLN_LOG_DBG)
    target_compile_definitions(${SEMA_SERVICE} PRIVATE BLN_LOG_DBG)
endif()

if (SEMA_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if (SEMA_EXAMPLES)
    add_subdirectory(example)
endif()
