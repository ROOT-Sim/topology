# SPDX-FileCopyrightText: 2008-2023 HPDCS Group <rootsim@googlegroups.com>
# SPDX-License-Identifier: GPL-3.0-only

# Retrieve and make available the testing framework
include(FetchContent)
set(IMPORT_AS_LIB ON)
FetchContent_Declare(rstest
        GIT_REPOSITORY https://github.com/ROOT-Sim/testing-framework.git
        GIT_TAG        origin/master
        )
FetchContent_MakeAvailable(rstest)

test_program(generic generic.c)
target_include_directories(test_generic PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(test_generic rstopology)

test_program(graphs graphs.c)
target_include_directories(test_graphs PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(test_graphs rstopology)

test_program(networks networks.c)
target_include_directories(test_networks PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(test_networks rstopology)

test_program(planar planar.c)
target_include_directories(test_planar PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(test_planar rstopology)

test_program(rings rings.c)
target_include_directories(test_rings PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(test_rings rstopology)
