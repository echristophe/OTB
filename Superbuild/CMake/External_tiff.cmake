set(proj TIFF)

if(NOT __EXTERNAL_${proj}__)
set(__EXTERNAL_${proj}__ 1)

message(STATUS "Setup libtiff...")

#ADD_SYSTEM_LOCATION(PROJECT ${proj} VARIABLES ${proj}_LIBRARY ${proj}_INCLUDE_DIR)

#ADD_SYSTEM_PREFIX(PROJECT ${proj})

if(USE_SYSTEM_TIFF)
  find_package ( TIFF )
  add_custom_target(${proj})
  message(STATUS "  Using libtiff system version")
else()
  SETUP_SUPERBUILD(PROJECT ${proj})
  message(STATUS "  Using libtiff SuperBuild version")
  
  # declare dependencies
  set(${proj}_DEPENDENCIES ZLIB)
  if(MSVC)
    list(APPEND ${proj}_DEPENDENCIES JPEG)
  endif()
  INCLUDE_SUPERBUILD_DEPENDENCIES(${${proj}_DEPENDENCIES})
  # set proj back to its original value
  set(proj TIFF)
  
  ADD_SUPERBUILD_CONFIGURE_VAR(ZLIB_INCLUDE_DIR --with-zlib-include-dir)
  
  if(MSVC)
    #is JPEG required for linux also?
    
    STRING(REGEX REPLACE "/$" "" CMAKE_WIN_INSTALL_PREFIX ${SB_INSTALL_PREFIX})    
    STRING(REGEX REPLACE "/" "\\\\" CMAKE_WIN_INSTALL_PREFIX ${CMAKE_WIN_INSTALL_PREFIX})    
    configure_file(${CMAKE_SOURCE_DIR}/patches/${proj}/nmake.opt ${CMAKE_BINARY_DIR}/nmake_libtiff_extra.opt)
    
     ExternalProject_Add(${proj}_build
      PREFIX ${proj}
      URL "http://download.osgeo.org/libtiff/tiff-4.0.3.tar.gz"
      URL_MD5 051c1068e6a0627f461948c365290410
      SOURCE_DIR ${TIFF_SB_SRC}
      BINARY_DIR ${TIFF_SB_SRC}
      INSTALL_DIR ${SB_INSTALL_PREFIX}
      DEPENDS ${${proj}_DEPENDENCIES}
      PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/nmake_libtiff_extra.opt ${TIFF_SB_SRC}/nmake.opt
      CONFIGURE_COMMAND ""
      BUILD_COMMAND nmake /f ${TIFF_SB_SRC}/Makefile.vc
      INSTALL_COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_SOURCE_DIR}/patches/${proj}/CMakeLists.txt
      ${CMAKE_BINARY_DIR}/${proj}/_install
    )

    ExternalProject_Add(${proj}
      PREFIX ${proj}/_install
      DOWNLOAD_COMMAND ""
      SOURCE_DIR ${proj}/_install
      BINARY_DIR ${TIFF_SB_BUILD_DIR}
      INSTALL_DIR ${SB_INSTALL_PREFIX}
    CMAKE_CACHE_ARGS
      -DCMAKE_INSTALL_PREFIX:STRING=${SB_INSTALL_PREFIX}
      -DCMAKE_BUILD_TYPE:STRING=Release
      -DTIFF_BUILD_DIR:STRING=${TIFF_SB_SRC}/libtiff
      DEPENDS ${proj}_build
      CMAKE_COMMAND
    )

  else()
    ExternalProject_Add(${proj}
      PREFIX ${proj}
      URL "http://download.osgeo.org/libtiff/tiff-4.0.3.tar.gz"
      URL_MD5 051c1068e6a0627f461948c365290410
      BINARY_DIR ${TIFF_SB_BUILD_DIR}
      INSTALL_DIR ${SB_INSTALL_PREFIX}
      CONFIGURE_COMMAND
        # use 'env' because CTest launcher doesn't perform shell interpretation
        # env ${LDLIBVAR}=${SB_INSTALL_PREFIX}/lib 
        ${TIFF_SB_BUILD_DIR}/configure
        --prefix=${SB_INSTALL_PREFIX}
        --enable-static=no
        ${TIFF_SB_CONFIG}
      BUILD_COMMAND $(MAKE)
      INSTALL_COMMAND $(MAKE) install
      DEPENDS ${${proj}_DEPENDENCIES}
      )
    
    ExternalProject_Add_Step(${proj} copy_source
      COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${TIFF_SB_SRC} ${TIFF_SB_BUILD_DIR}
      DEPENDEES patch update
      DEPENDERS configure
    )
    
  endif()
  
  set(${proj}_INCLUDE_DIR ${SB_INSTALL_PREFIX}/include)
  if(WIN32)
    set(${proj}_LIBRARY ${SB_INSTALL_PREFIX}/lib/libtiff_i.lib)
  elseif(UNIX)
    set(${proj}_LIBRARY ${SB_INSTALL_PREFIX}/lib/libtiff${CMAKE_SHARED_LIBRARY_SUFFIX})
  endif()
  
endif()
endif()
