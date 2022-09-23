set(SDL2_IMAGE_ROOT "" CACHE PATH "SDL2_image root directory")
set(SDL2_IMAGE_LIB_DIR "${SDL2_IMAGE_ROOT}/lib/x64")
set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_ROOT}/include")

if (NOT TARGET SDL2_image)
    if (WIN32)  # Windows, use clang or MSVC
        add_library(SDL2::IMAGE SHARED IMPORTED GLOBAL)
        set_target_properties(
            SDL2::IMAGE
            PROPERTIES
                IMPORTED_LOCATION "${SDL2_IMAGE_LIB_DIR}/SDL2_image.dll"
                IMPORTED_IMPLIB "${SDL2_IMAGE_LIB_DIR}/SDL2_image.lib"
                INTERFACE_INCLUDE_DIRECTORIES ${SDL2_IMAGE_INCLUDE_DIR}
        )
        add_library(SDL2_image INTERFACE IMPORTED GLOBAL)
        target_link_libraries(SDL2_image INTERFACE SDL2::IMAGE)
    else()  # Linux, MacOSX
        # TODO not finish
        message(FATAL_ERROR "don't implement FindSDL_image under Unix")
    endif()
endif()
