set(lib_name TCP)
set(${lib_name}_srcs
  EncryptHelpers.cpp
  EncryptHelpers.hpp
  Handler.cpp
  Handler.hpp
  TCPClient.cpp
  TCPClient.hpp
  TCPConnection.cpp
  TCPConnection.hpp
  TCPServer.cpp
  TCPServer.hpp
  TCPTools.cpp
  TCPTools.hpp
  )
source_group("" FILES ${${lib_name}_srcs})
add_library(${lib_name} ${${lib_name}_srcs})
target_link_libraries(${lib_name} PUBLIC acq Msg Proto json registry logger)
target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
xpTargetExtern(${lib_name} PUBLIC openssl PRIVATE protobuf)
set_property(TARGET ${lib_name} PROPERTY FOLDER ${folder})
add_subdirectory(Test)
xpSourceListAppend("${${lib_name}_srcs}")
