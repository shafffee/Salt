#Assimp

add_library(assimp STATIC IMPORTED)

set_target_properties(assimp PROPERTIES
    IMPORTED_LOCATION "/lib/assimp-vc143-mtd.lib"
)

#idk why is it here
add_library(unit STATIC IMPORTED)
set_target_properties(unit PROPERTIES
    IMPORTED_LOCATION "/lib/unit.lib"
)