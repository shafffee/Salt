add_library(Logging Logging.h Logging.cpp)

target_include_directories(Logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})