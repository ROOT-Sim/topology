# SPDX-FileCopyrightText: 2008-2023 HPDCS Group <rootsim@googlegroups.com>
# SPDX-License-Identifier: GPL-3.0-only

if(WIN32)
    set(EXTRA_LIBS ${EXTRA_LIBS} winmm)
endif()

add_library(rstopology STATIC topology.c random.c xxtea.c)
target_include_directories(rstopology PRIVATE . include)
target_link_libraries(rstopology ${EXTRA_LIBS})

install(DIRECTORY include/ DESTINATION include)
install(TARGETS rstopology LIBRARY DESTINATION lib)
