# ============================================================================
# Copyright (c) 2020 Hypothermic IT
# All rights reserved.
#
# See COPYING file for license information.
# ============================================================================

##############################################################################
# @file  CMakeLists.txt
# @brief Build configuration of Enlightenment drivers.
##############################################################################

basis_add_library(enl-driver-ercp SHARED
        ercp.c
        )
set_target_properties(enl-driver-ercp PROPERTIES SUFFIX ".edm.so")

basis_target_link_libraries(enl-driver-ercp enl-api)