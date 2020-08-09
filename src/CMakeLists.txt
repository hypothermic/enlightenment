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

basis_add_library(enl-build build/exports.c build/exports.h)
basis_add_library(enl-common common/table.c common/database.c common/descriptor.c)

basis_add_executable(enl-server server/main.c server/server.c)
basis_target_link_libraries(enl-server enl-build)
basis_target_link_libraries(enl-server enl-common)
basis_target_link_libraries(enl-server glib-2.0)
