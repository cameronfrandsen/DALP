cmake_minimum_required(VERSION 3.15.0)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  message(STATUS "Building DALP")
  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE PATH
    "Locaction for installation"
    FORCE)
  if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
    set(CMAKE_BUILD_TYPE "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
      "Choose the type to build, options are: Debug Release" FORCE)
  endif()
  project(DALP)
  set(externprolite_REV 20.05.4)
  find_package(externprolite REQUIRED)
  xpSetFlags()
  set(CMAKE_CXX_STANDARD 14)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()
set(folder ${PROJECT_NAME})
set_property(GLOBAL PROPERTY FOLDER Shared)
##################################
add_subdirectory(Shared)
add_subdirectory(Referee)
add_subdirectory(DroneSimulator)
###########################################
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  include(FindGit)
  if(NOT GIT_FOUND)
    message(FATAL_ERROR "Could not find git")
  endif()
  if(NOT EXISTS ${CMAKE_SOURCE_DIR}/.git)
    message(FATAL_ERROR "Must be a git repo")
  endif()
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REV
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  if(UNIX)
    set(CPACK_GENERATOR STGZ)
  elseif(WIN32)
    set(CPACK_GENERATOR TXZ)
  endif()
  set(CPACK_PACKAGE_NAME "DALP")
  set(CPACK_PACKAGE_VENDOR "Cameron Frandsen")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PACKAGE_NAME} Revision ${GIT_REV}")
  #set(CPACK_PACKAGE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/License.txt)
  set(CPACK_PACKAGE_FIlE_NAME "DALP-${GIT_REV}")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "DALP")
  set(CPACK_PACKAGE_VERSION ${GIT_REV})
  include(CPack)
endif()
###########################################
set(random_srcs
  Findexternprolite.cmake
  )
###########################################
xpSourceListAppend(${random_srcs})