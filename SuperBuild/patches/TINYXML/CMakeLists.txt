cmake_minimum_required(VERSION 2.8.3)

project(tinyXMLlib)

set(BUILD_SHARED_LIBS ON)
if(MSVC)
set(BUILD_SHARED_LIBS OFF) #force off
endif()

file(GLOB tinyXMLlib_SRCS "*.cpp")
file(GLOB tinyXMLlib_HDRS "*.h")
add_library(tinyxml ${tinyXMLlib_SRCS})

install(TARGETS tinyxml
    RUNTIME DESTINATION bin COMPONENT RuntimeLibraries
    LIBRARY DESTINATION lib COMPONENT RuntimeLibraries
    ARCHIVE DESTINATION lib COMPONENT Development)

install(FILES ${tinyXMLlib_HDRS}
    DESTINATION include
    COMPONENT Development)


#set(TINYXML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
#set(TINYXML_LIBRARIES tinyXML)
