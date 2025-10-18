add_library(Utils Utils.h Utils.cpp Filework.h ObjLoader.h Containers/Containers.h Containers/NameID_Container.h Containers/Pack_Container.h)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Containers)

target_link_libraries(Utils PRIVATE Logging)
target_link_libraries(Utils PRIVATE Renderer)
target_link_libraries(Utils PRIVATE glm)
