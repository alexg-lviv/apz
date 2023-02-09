if(LIBSPDLOG_INCLUDE_DIRS AND LIBSPDLOG_LIBRARIES)
    set(LIBSPDLOG_FOUND TRUE)

else(LIBSPDLOG_INCLUDE_DIRS AND LIBSPDLOG_LIBRARIES)
    find_path(LIBSPDLOG_INCLUDE_DIRS spdlog
      /usr/include
      /usr/include/spdlog
      /usr/local/include/
      /usr/local/include/spdlog
      )

  find_library(LIBSPDLOG_LIBRARIES NAMES spdlog
      PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      )

  if(LIBSPDLOG_INCLUDE_DIRS AND LIBSPDLOG_LIBRARIES)
      set(LIBSPDLOG_FOUND TRUE)
      message(STATUS "Found libspdlog: ${LIBSPDLOG_INCLUDE_DIRS}, ${LIBSPDLOG_LIBRARIES}")
  else(LIBSPDLOG_INCLUDE_DIRS AND LIBSPDLOG_LIBRARIES)
      set(LIBSPDLOG_FOUND FALSE)
    message(STATUS "libspdlog not found.")
  endif(LIBSPDLOG_INCLUDE_DIRS AND LIBSPDLOG_LIBRARIES)

  mark_as_advanced(LIBSPDLOG_INCLUDE_DIRS LIBSPDLOG_LIBRARIES)

endif(LIBSPDLOG_INCLUDE_DIRS AND LIBSPDLOG_LIBRARIES)
