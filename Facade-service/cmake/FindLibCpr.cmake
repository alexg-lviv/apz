if(LIBCPR_INCLUDE_DIRS AND LIBCPR_LIBRARIES)
    set(LIBCPR_FOUND TRUE)

else(LIBCPR_INCLUDE_DIRS AND LIBCPR_LIBRARIES)
    find_path(LIBCPR_INCLUDE_DIRS cpr
      /usr/include
      /usr/include/cpr
      /usr/local/include/
      /usr/local/include/cpr
      )

  find_library(LIBCPR_LIBRARIES NAMES cpr
      PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      )

  if(LIBCPR_INCLUDE_DIRS AND LIBCPR_LIBRARIES)
      set(LIBCPR_FOUND TRUE)
      message(STATUS "Found libcpr: ${LIBCPR_INCLUDE_DIRS}, ${LIBCPR_LIBRARIES}")
  else(LIBCPR_INCLUDE_DIRS AND LIBCPR_LIBRARIES)
      set(LIBCPR_FOUND FALSE)
    message(STATUS "libcpr not found.")
  endif(LIBCPR_INCLUDE_DIRS AND LIBCPR_LIBRARIES)

  mark_as_advanced(LIBCPR_INCLUDE_DIRS LIBCPR_LIBRARIES)

endif(LIBCPR_INCLUDE_DIRS AND LIBCPR_LIBRARIES)
