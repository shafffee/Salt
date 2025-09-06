#Assimp
add_library(assimp STATIC IMPORTED GLOBAL)
set_target_properties(assimp PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp-vc143-mt.lib
)
#idk why is it here
add_library(unit STATIC IMPORTED GLOBAL)
set_target_properties(unit PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/unit.lib
)
#zlib
add_library(zlib STATIC IMPORTED GLOBAL)
set_target_properties(zlib PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/zlibstaticd.lib
)