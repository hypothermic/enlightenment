##############################################################################
# @file  BasisBootstrapping.cmake
# @brief Auxiliary function to bootstrap the build of CMake BASIS.
##############################################################################

#=============================================================================
# Copyright 2014-2016 Andreas Schuh
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#=============================================================================

function (basis_bootstrap)
  # parse arguments -- unparsed arguments are passed on to CMake using -D
  include (CMakeParseArguments)
  cmake_parse_arguments (BASIS "INFORM_USER" "VERSION;DOWNLOAD_URL" "" ${ARGN})
  if (NOT BASIS_VERSION)
    message (FATAL_ERROR "No CMake BASIS version specified! Use 'VERSION 3.3.0', for example.")
  endif ()
  # abort the first time to give users a chance to specify where their
  # CMake BASIS installation is located by setting BASIS_DIR in the GUI
  if (BASIS_INFORM_USER)
    if (DEFINED DEPENDS_BASIS_DIR AND NOT DEFINED BASIS_INSTALL_PREFIX)
      set (BASIS_INSTALL_PREFIX "" CACHE PATH "Installation prefix for CMake BASIS.")
      message (FATAL_ERROR "Could not find an existing CMake BASIS installation!\n"
                           "This project uses CMake BASIS for the build configuration."
                           " Next time you configure this build by running CMake again,"
                           " BASIS version ${BASIS_VERSION} will be automatically downloaded"
                           " and build as part of the build configuration of this project."
                           " If you want to install this version permanently,"
                           " specify an installation prefix for CMake BASIS using"
                           " BASIS_INSTALL_PREFIX. Otherwise, leave it blank.\n"
                           "If you installed CMake BASIS already on your system, please"
                           " specify its location by setting the DEPENDS_BASIS_DIR variable"
                           " before you re-configure the build system of this project.\n"
                           "Visit https://cmake-basis.github.io for"
                           " more information about the CMake BASIS package.\n")
    endif ()
  endif ()

  set (DOWNLOAD_PATH "${CMAKE_CURRENT_BINARY_DIR}")
  if (BASIS_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+(-[a-z]*)?$")
    if (WIN32)
      set (BASIS_ARCHIVE "BASIS-${BASIS_VERSION}.zip")
    else ()
      set (BASIS_ARCHIVE "BASIS-${BASIS_VERSION}.tar.gz")
    endif ()
    if (NOT BASIS_DOWNLOAD_URL)
      if (WIN32)
        set (BASIS_DOWNLOAD_URL "https://github.com/cmake-basis/BASIS/archive/v${BASIS_VERSION}.zip")
      else ()
        set (BASIS_DOWNLOAD_URL "https://github.com/cmake-basis/BASIS/archive/v${BASIS_VERSION}.tar.gz")
      endif ()
    endif ()
    if (NOT BASIS_DOWNLOAD_URL MATCHES "\\.(zip|tar\\.gz)$")
      set (BASIS_DOWNLOAD_URL "${BASIS_DOWNLOAD_URL}/${BASIS_ARCHIVE}")
    endif ()
  else ()
    set (BASIS_DOWNLOAD_URL "git@github.com:cmake-basis/BASIS.git")
  endif ()
  set (BASIS_SOURCE_DIR "${DOWNLOAD_PATH}/BASIS-${BASIS_VERSION}")
  set (BASIS_BINARY_DIR "${DOWNLOAD_PATH}/BASIS-${BASIS_VERSION}/build")

  # bootstrap BASIS build/installation only if not done before
  # or when BASIS_INSTALL_PREFIX has changed
  if (   NOT IS_DIRECTORY "${BASIS_BINARY_DIR}"
      OR NOT DEFINED BASIS_INSTALL_PREFIX_CONFIGURED
      OR NOT BASIS_INSTALL_PREFIX_CONFIGURED STREQUAL "${BASIS_INSTALL_PREFIX}")

    # download and extract source code if not done before
    if (NOT EXISTS "${BASIS_SOURCE_DIR}/BasisProject.cmake")

      # clone Git repository and checkout specified commit/branch
      if (BASIS_DOWNLOAD_URL MATCHES ".git$")

        find_package (Git QUIET)
        if (NOT GIT_FOUND)
          set (ERRMSG "Git client not found: GIT_EXECUTABLE")
        else ()
          mark_as_advanced (GIT_EXECUTABLE)
          message (STATUS "Cloning CMake BASIS repository...")
          execute_process (
            COMMAND "${GIT_EXECUTABLE}" clone --depth=1 "${BASIS_DOWNLOAD_URL}" "${BASIS_SOURCE_DIR}"
            RESULT_VARIABLE RETVAL
            ERROR_VARIABLE  ERRMSG
          )
          if (RETVAL EQUAL 0)
            execute_process (
              COMMAND "${GIT_EXECUTABLE}" checkout --detach "${BASIS_VERSION}"
              WORKING_DIRECTORY "${BASIS_SOURCE_DIR}"
              RESULT_VARIABLE   RETVAL
              ERROR_VARIABLE    ERRMSG
            )
            if (RETVAL EQUAL 0)
              set (ERRMSG)
              message (STATUS "Cloning CMake BASIS repository... - done")
            endif ()
          endif ()
        endif ()
        if (ERRMSG)
          message (FATAL_ERROR "Failed to clone CMake BASIS ${BASIS_VERSION} from\n"
                               "\t${BASIS_DOWNLOAD_URL}\n"
                               "Error: ${ERRMSG}\n"
                               "Ensure GIT_EXECUTABLE is set and try again or follow the instructions at\n"
                               "\thttps://cmake-basis.github.io\n"
                               "to download and install it manually before configuring this project.\n")
        endif ()

      else ()

        # download source code distribution package
        if (NOT EXISTS "${DOWNLOAD_PATH}/${BASIS_ARCHIVE}")
          message (STATUS "Downloading CMake BASIS v${BASIS_VERSION}...")
          find_program (CURL_EXECUTABLE NAMES curl)
          mark_as_advanced (CURL_EXECUTABLE)
          if (CURL_EXECUTABLE)
            execute_process (
              COMMAND "${CURL_EXECUTABLE}" -L -o "${DOWNLOAD_PATH}/${BASIS_ARCHIVE}" "${BASIS_DOWNLOAD_URL}"
              ERROR_VARIABLE  ERRMSG
              RESULT_VARIABLE RETVAL
            )
          else ()
            find_package (Wget QUIET)
            if (WGET_EXECUTABLE)
              execute_process (
                COMMAND "${WGET_EXECUTABLE}" -O "${DOWNLOAD_PATH}/${BASIS_ARCHIVE}" "${BASIS_DOWNLOAD_URL}"
                ERROR_VARIABLE  ERRMSG
                RESULT_VARIABLE RETVAL
              )
            else ()
              set (CMAKE_USE_OPENSSL ON)
              file (DOWNLOAD "${BASIS_DOWNLOAD_URL}" "${DOWNLOAD_PATH}/${BASIS_ARCHIVE}" STATUS RETVAL)
              list (GET RETVAL 1 ERRMSG)
              list (GET RETVAL 0 RETVAL)
            endif ()
          endif ()
          if (NOT RETVAL EQUAL 0)
            message (FATAL_ERROR "Failed to download CMake BASIS v${BASIS_VERSION} from\n"
                                 "\t${BASIS_DOWNLOAD_URL}\n"
                                 "Error: ${ERRMSG}\n"
                                 "Try again after installation either curl or wget or follow the instructions at\n"
                                 "\thttps://cmake-basis.github.io\n"
                                 "to download and install it manually before configuring this project.\n")
          endif ()
          message (STATUS "Downloading CMake BASIS v${BASIS_VERSION}... - done")
        endif ()
        # extract source package
        message (STATUS "Extracting CMake BASIS...")
        execute_process (COMMAND ${CMAKE_COMMAND} -E tar -xvzf "${DOWNLOAD_PATH}/${BASIS_ARCHIVE}" RESULT_VARIABLE RETVAL)
        if (NOT RETVAL EQUAL 0)
          file (REMOVE_RECURSE "${BASIS_SOURCE_DIR}")
          message (FATAL_ERROR "Failed to extract the downloaded archive file ${DOWNLOAD_PATH}/${BASIS_ARCHIVE}!")
        endif ()
        message (STATUS "Extracting CMake BASIS... - done")

      endif ()
    endif ()

    # configure
    file (MAKE_DIRECTORY "${BASIS_BINARY_DIR}")
    set (CMAKE_ARGUMENTS "-DBASIS_REGISTER:BOOL=OFF") # do not register this BASIS build/installation
                                                      # as it should only be used by this project
    if (BASIS_INSTALL_PREFIX)
      list (APPEND CMAKE_ARGUMENTS "-DCMAKE_INSTALL_PREFIX=${BASIS_INSTALL_PREFIX}")
    endif ()
    list (LENGTH BASIS_UNPARSED_ARGUMENTS N)
    while (N GREATER 0)
      list (GET BASIS_UNPARSED_ARGUMENTS 0 VARIABLE_NAME)
      list (GET BASIS_UNPARSED_ARGUMENTS 1 VARIABLE_VALUE)
      list (APPEND CMAKE_ARGUMENTS "-D${VARIABLE_NAME}=${VARIABLE_VALUE}")
      list (REMOVE_AT BASIS_UNPARSED_ARGUMENTS 0 1)
      math (EXPR N "${N} - 2")
    endwhile ()
    execute_process (
      COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" ${CMAKE_ARGUMENTS} "${BASIS_SOURCE_DIR}"
      WORKING_DIRECTORY "${BASIS_BINARY_DIR}"
    )
    # build
    execute_process (COMMAND "${CMAKE_COMMAND}" --build "${BASIS_BINARY_DIR}" --config Release WORKING_DIRECTORY "${BASIS_BINARY_DIR}")
    # install
    if (BASIS_INSTALL_PREFIX)
      execute_process (COMMAND "${CMAKE_COMMAND}" --build "${BASIS_BINARY_DIR}" --config Release --target install WORKING_DIRECTORY "${BASIS_BINARY_DIR}")
      set (BASIS_DIR "${BASIS_INSTALL_PREFIX}")
    else ()
      set (BASIS_DIR "${BASIS_BINARY_DIR}")
    endif ()

    # remember in which directory BASIS was installed to avoid re-running
    # the bootstrapping every time the project needs to be re-configured
    set (BASIS_INSTALL_PREFIX_CONFIGURED "${BASIS_INSTALL_PREFIX}" CACHE INTERNAL "" FORCE)

  elseif (BASIS_INSTALL_PREFIX_CONFIGURED)
    set (BASIS_DIR "${BASIS_INSTALL_PREFIX_CONFIGURED}")
  else ()
    set (BASIS_DIR "${BASIS_BINARY_DIR}")
  endif ()

  # return location of local CMake BASIS installation
  set (BASIS_DIR "${BASIS_DIR}" PARENT_SCOPE)
endfunction (basis_bootstrap)
