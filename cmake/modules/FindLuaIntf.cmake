# Copyright (c) 2015, Chris Hutchinson
#
# See LICENSE.md in the distribution for the full license text including,
# but not limited to, a notice of warranty and distribution rights.

# Find LuaIntf depdendency

include(FindPackageHandleStandardArgs)

if (LUAINTF_INCLUDE_DIR)
  set(LUAINTF_FIND_QUIETLY TRUE)
endif ()

# Set default search directories...

set (LUAINTF_SEARCH_DIRS
  "/usr/include"
  "/usr/local/include"
)

# If root specified then add more directories to the search paths

if (LUAINTF_ROOT_DIR)
  set(LUAINTF_SEARCH_DIRS "${LUAINTF_ROOT_DIR}"
                            "${LUAINTF_ROOT_DIR}/LuaIntf"
                             ${LUAINTF_SEARCH_DIRS})
endif ()

# Look for LUAINTF...

find_path(LUAINTF_INCLUDE_DIR LuaIntf.h
  PATHS ${LUAINTF_SEARCH_DIRS}
)

find_package_handle_standard_args(LUAINTF DEFAULT_MSG LUAINTF_INCLUDE_DIR)
mark_as_advanced(LUAINTF_INCLUDE_DIR)

# Set friendly / useful variables

if (LUAINTF_FOUND)
  set(LUAINTF_INCLUDE_DIRS "${LUAINTF_INCLUDE_DIR}")
endif ()
