# Find the secp256k1 library and headers
# Sets SECP256K1_FOUND, SECP256K1_INCLUDE_DIRS, and SECP256K1_LIBRARIES

find_path(SECP256K1_INCLUDE_DIR secp256k1.h
    HINTS ${secp256k1_ROOT}/include
          /opt/homebrew/opt/secp256k1/include
          /usr/local/include
          /usr/include
)

find_library(SECP256K1_LIBRARY secp256k1
    HINTS ${secp256k1_ROOT}/lib
          /opt/homebrew/opt/secp256k1/lib
          /usr/local/lib
          /usr/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SECP256K1 DEFAULT_MSG SECP256K1_LIBRARY SECP256K1_INCLUDE_DIR)

if(SECP256K1_FOUND)
    set(SECP256K1_LIBRARIES ${SECP256K1_LIBRARY})
    set(SECP256K1_INCLUDE_DIRS ${SECP256K1_INCLUDE_DIR})
    if(NOT TARGET SECP256K1::SECP256K1)
        add_library(SECP256K1::SECP256K1 UNKNOWN IMPORTED)
        set_target_properties(SECP256K1::SECP256K1 PROPERTIES
            IMPORTED_LOCATION "${SECP256K1_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${SECP256K1_INCLUDE_DIR}"
            IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        )
    endif()
endif()

mark_as_advanced(SECP256K1_INCLUDE_DIR SECP256K1_LIBRARY)
