# - Try to find Gio
# Once done this will define
#
#  GIO_FOUND - system has Gio
#  GIO_INCLUDE_DIR - the Gio include directory
#  GIO_LIBRARIES - the libraries needed to use Gio
#  GIO_DEFINITIONS - Compiler switches required for using Gio

IF (GIO_INCLUDE_DIR AND GIO_LIBRARIES)
    # in cache already
    SET(Gio_FIND_QUIETLY TRUE)
ELSE (GIO_INCLUDE_DIR AND GIO_LIBRARIES)
    SET(Gio_FIND_QUIETLY FALSE)
ENDIF (GIO_INCLUDE_DIR AND GIO_LIBRARIES)

IF (NOT WIN32)
    # use pkg-config to get the directories and then use these values
    # in the FIND_PATH() and FIND_LIBRARY() calls
    FIND_PACKAGE(PkgConfig)
    PKG_CHECK_MODULES(PC_GIO gio-2.0)
    #MESSAGE(STATUS "DEBUG: Gio include directory = ${GIO_INCLUDE_DIRS}")
    #MESSAGE(STATUS "DEBUG: Gio link directory = ${GIO_LIBRARY_DIRS}")
    #MESSAGE(STATUS "DEBUG: Gio CFlags = ${GIO_CFLAGS}")
    SET(GIO_DEFINITIONS ${PC_GIO_CFLAGS_OTHER})
ENDIF (NOT WIN32)

FIND_PATH(GIO_INCLUDE_DIR gio.h
        PATHS
        ${PC_GIO_INCLUDEDIR}
        ${PC_GIO_INCLUDE_DIRS}
        PATH_SUFFIXES glib-2.0/gio/
        )

FIND_LIBRARY(_GioLibs NAMES gio-2.0 libgio-2.0
        PATHS
        ${PC_GIO_LIBDIR}
        ${PC_GIO_LIBRARY_DIRS}
        )

SET( GIO_LIBRARIES ${_GioLibs} )
SET( GIO_INCLUDE_DIRS ${GIO_INCLUDE_DIR} )

IF (GIO_INCLUDE_DIR AND GIO_LIBRARIES)
    SET(GIO_FOUND TRUE)
ELSE (GIO_INCLUDE_DIR AND GIO_LIBRARIES)
    SET(GIO_FOUND FALSE)
ENDIF (GIO_INCLUDE_DIR AND GIO_LIBRARIES)

IF (GIO_FOUND)
    IF (NOT Gio_FIND_QUIETLY)
        MESSAGE(STATUS "Found Gio libraries: ${GIO_LIBRARIES}")
        MESSAGE(STATUS "Found Gio includes : ${GIO_INCLUDE_DIR}")
    ENDIF (NOT Gio_FIND_QUIETLY)
ELSE (GIO_FOUND)
    IF (Gio_FIND_REQUIRED)
        MESSAGE(STATUS "Could NOT find Gio")
    ENDIF(Gio_FIND_REQUIRED)
ENDIF (GIO_FOUND)

MARK_AS_ADVANCED(GIO_INCLUDE_DIR _GioLibs)