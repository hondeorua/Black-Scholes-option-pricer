cmake_minimum_required(VERSION 3.15...4.0)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(bssolver LANGUAGES CXX)

set(PYBIND11_FINDPYTHON ON)

set(pybind11_DIR
    "/Users/hvu/Personal_Projects/BS_option_pricer/.venv/lib/python3.13/site-packages/pybind11/share/cmake/pybind11"
)

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(bssolver src/pybinding.cpp src/bssolver.cpp)

target_include_directories(bssolver PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

install(TARGETS bssolver DESTINATION .)

set(INIT_PY "${CMAKE_CURRENT_BINARY_DIR}/__init__.py")
if(NOT EXISTS ${INIT_PY})
file(WRITE ${INIT_PY} "")
endif()
