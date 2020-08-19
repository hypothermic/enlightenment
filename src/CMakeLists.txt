# ============================================================================
# Copyright (c) 2020 Hypothermic IT
# All rights reserved.
#
# See COPYING file for license information.
# ============================================================================

##############################################################################
# @file  CMakeLists.txt
# @brief Build configuration of software.
##############################################################################

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-error=main -Wno-main)
endif()

basis_add_library(enl-common common/column.c common/database.c common/descriptor.c common/row.c common/server.c common/table.c)
basis_target_link_libraries(enl-common glib-2.0)
basis_target_link_libraries(enl-common gio-2.0)
basis_target_link_libraries(enl-common gobject-2.0)
basis_target_link_libraries(enl-common gmodule-2.0)

basis_add_library(enl-server server/server.c)
basis_target_link_libraries(enl-server enl-common)

basis_add_executable(enl-server-cli server/main.c)
basis_target_link_libraries(enl-server enl-common)

basis_add_executable(enl-example-1 ../example/example-1.c)
basis_target_link_libraries(enl-example-1 enl-server)
