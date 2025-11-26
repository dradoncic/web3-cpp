# Find the GMP library and headers
# Sets GMP_FOUND, GMP_INCLUDE_DIRS, and GMP_LIBRARIES

find_path(GMP_INCLUDE_DIR gmp.h
    HINTS ${GMP_ROOT}/include
    /opt/homebrew/opt/gmp/include
    /usr/local/include
    /usr/include
)

find_library(GMP_LIBRARY gmp
    HINTS ${GMP_ROOT}/lib
    /opt/homebrew/opt/gmp/lib
    /usr/local/lib
    /usr/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG GMP_LIBRARY GMP_INCLUDE_DIR)

if(GMP_FOUND)
    set(GMP_LIBRARIES ${GMP_LIBRARY})
    set(GMP_INCLUDE_DIRS ${GMP_INCLUDE_DIR})
    if(NOT TARGET GMP::GMP)
        add_library(GMP::GMP UNKNOWN IMPORTED)
        set_target_properties(GMP::GMP PROPERTIES
            IMPORTED_LOCATION "${GMP_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}"
        )
    endif()
endif()

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARY)
