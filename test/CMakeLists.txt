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

test_program(topology topology.c)
target_include_directories(test_topology PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(test_topology rstopology)
