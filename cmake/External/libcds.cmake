if (NOT __LIBCDS_INCLUDED) # guard against multiple includes
  set(__LIBCDS_INCLUDED TRUE)

  # use the system-wide libcds if present
  find_package(libcds QUIET)
  if (LIBCDS_FOUND)
    set(LIBCDS_EXTERNAL FALSE)
  else ()
    # build directory
    set(libcds_PREFIX ${CMAKE_BINARY_DIR}/external/libcds-prefix)

    # install directory
    set(libcds_INSTALL ${CMAKE_BINARY_DIR}/external/libcds-install)

    # compilation flags
    set(LIBCDS_CXX_FLAGS ${CMAKE_CXX_FLAGS} -DCDS_DISABLE_128BIT_ATOMIC)
    set(LIBCDS_C_FLAGS ${CMAKE_C_FLAGS} -DCDS_DISABLE_128BIT_ATOMIC)

    ExternalProject_Add(libcds
            PREFIX ${libcds_PREFIX}
            DOWNLOAD_COMMAND ""
            SOURCE_DIR ${PROJECT_SOURCE_DIR}/third_party/libcds
            UPDATE_COMMAND ""
            INSTALL_DIR ${libcds_INSTALL}
            CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${libcds_INSTALL}
            -DBUILD_SHARED_LIBS=ON
            -DBUILD_PACKAGING=OFF
            -DBUILD_TESTING=OFF
            -DBUILD_NC_TESTS=OFF
            -BUILD_CONFIG_TESTS=OFF
            -DINSTALL_HEADERS=ON
            -DCMAKE_C_FLAGS=${LIBCDS_C_FLAGS}
            -DCMAKE_CXX_FLAGS=${LIBCDS_CXX_FLAGS}
            LOG_DOWNLOAD 1
            LOG_INSTALL 1
            )

    set(LIBCDS_FOUND TRUE)
    set(LIBCDS_EXTERNAL TRUE)

    set(LIBCDS_INCLUDE_DIRS ${libcds_INSTALL}/include)
    set(LIBCDS_INCLUDE_DIRECTORY ${libcds_INSTALL}/include)

    set(LIBCDS_LIBRARY_DIRS ${capnp_INSTALL}/lib)
    set(LIBCDS_LIBRARIES
            ${libcds_INSTALL}/lib64/libcds_d.2.3.2.dylib
            )
    list(APPEND external_project_dependencies libcds)

  endif ()
endif ()