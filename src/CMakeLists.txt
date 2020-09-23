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

# TODO create separate CMakeFiles for dirs /engine /example

basis_add_library(enl-common common/data_column.c common/database.c common/descriptor.c common/error.c common/primary_column.c common/row.c common/server.c common/table.c)
basis_target_link_libraries(enl-common glib-2.0)
basis_target_link_libraries(enl-common gio-2.0)
basis_target_link_libraries(enl-common gobject-2.0)
basis_target_link_libraries(enl-common gmodule-2.0)

basis_add_library(enl-api api/engine.c api/driver.c)
basis_target_link_libraries(enl-api enl-common)

basis_add_library(enl-server server/server.c server/error.c server/driver.c)
basis_target_link_libraries(enl-server enl-api)

basis_add_library(enl-engine-imh ../engine/imh/imh.c ../engine/imh/error.c ../engine/imh/1d.c ../engine/imh/packing.c)
basis_target_link_libraries(enl-engine-imh enl-api)

basis_add_executable(enl-server-cli server/main.c)
basis_target_link_libraries(enl-server-cli enl-server)

basis_add_executable(enl-example-1 ../example/example-1.c)
basis_target_link_libraries(enl-example-1 enl-server)

basis_add_executable(enl-example-2 ../example/example-2.c)
basis_target_link_libraries(enl-example-2 enl-api enl-engine-imh)

add_subdirectory(../driver driver)