cmake_minimum_required(VERSION 3.25)

project(BST VERSION 0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 3.10)
project(MyProject)

message("[CHECK]Running environment checking")
######################################################################
# check platform
if(NOT CMAKE_SYSTEM_NAME MATCHES "Linux")
  message(FATAL_ERROR "This project only supports Linux platforms.")
endif()

######################################################################
# check CXX compiler
# compiler must be g++ or clang++
# g++
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  #g++ version >= 13
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} --version
    OUTPUT_VARIABLE GCC_VERSION_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  string(REGEX MATCH "[0-9]+\\.[0-9]+" GCC_VERSION ${GCC_VERSION_OUTPUT})
  list(GET GCC_VERSION 0 GCC_MAJOR_VERSION)
  message("g++ major version: ${GCC_MAJOR_VERSION}")
  if(${GCC_MAJOR_VERSION} LESS 13)
    message(FATAL_ERROR "[FAIL]g++ major version must be at least 13.")
  endif()

  # clang++
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # clang++ version >= 14
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} --version
    OUTPUT_VARIABLE CLANG_VERSION_OUTPUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  string(REGEX MATCH "[0-9]+\\.[0-9]+" CLANG_VERSION ${CLANG_VERSION_OUTPUT})
  list(GET CLANG_VERSION 0 CLANG_MAJOR_VERSION)
  message("clang++ major version: ${CLANG_MAJOR_VERSION}")
  if(${CLANG_MAJOR_VERSION} LESS 14)
    message(FATAL_ERROR
    "[FAIL]clang++ major version must be at least 14.Current: ${CLANG_MAJOR_VERSION}")
  endif()

  # error
else()
  message(FATAL_ERROR
  "[FAIL]This project requires g++ or clang++ as the compiler.")
endif()

######################################################################
# check qt version
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

message("Qt Version: ${QT_VERSION}")
if(${QT_VERSION} LESS 6.1.0 AND ${QT_VERSION} LESS 7.0.0)
  message(FATAL_ERROR
  "Qt version should 6.1.0 >= and < 7.0.0. Current: ${QT_VERSION}")
endif()

message("[PASS]Compiler and platform checks passed. Continuing with configuration...")


######################################################################
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

######################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


######################################################################
execute_process(
  COMMAND ${CMAKE_CXX_COMPILER} --version
  OUTPUT_VARIABLE COMPILER_VERSION_OUTPUT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "\n" "\\n" COMPILER_VERSION_OUTPUT_1L "${COMPILER_VERSION_OUTPUT}")
message("compiler information:\n${COMPILER_VERSION_OUTPUT}")

message("generator information: ${CMAKE_GENERATOR}")
message("cmake information: version ${CMAKE_VERSION}")

add_definitions(
  -DCOMPILER_VERION="${COMPILER_VERSION_OUTPUT_1L}"
  -DGENERATOR="${CMAKE_GENERATOR}"
  -DCMAKE_VERSION="${CMAKE_VERSION}"
  -DQT_VERSION="${QT_VERSION}"
)

######################################################################
add_compile_options(-Wall -Werror)
######################################################################
file(GLOB_RECURSE HPP_SOURCES "include/*.hpp")
file(GLOB_RECURSE CC_SOURCES "src/*.cc")
file(GLOB_RECURSE QT_RESOURCES "resources/*" "src/*.ui")

include_directories("include" "resources")

set(PROJECT_SOURCES
        ${HPP_SOURCES}
        ${CC_SOURCES}
        ${QT_RESOURCES}
)
message("Source files are listed below")
foreach(f IN LISTS PROJECT_SOURCES)
  message("${f}")
endforeach()
message("Source files end")

######################################################################
qt_add_executable(BST
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

target_link_libraries(BST PRIVATE Qt6::Widgets)

qt_finalize_executable(BST)

######################################################################
add_subdirectory(tests)
