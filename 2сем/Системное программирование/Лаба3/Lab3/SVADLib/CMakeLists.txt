add_library(SVADLib SHARED binary_search.c)

target_include_directories(SVADLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(SVADLib PROPERTIES
    LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/SVADLib.def"
)

target_compile_definitions(SVADLib PRIVATE BUILD_DLL)