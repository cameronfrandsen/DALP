set(lib_name Proto)
set(${lib_name}_srcs
  BaseMsg.proto
  EncryptedMsg.proto
  FinishMsg.proto
  FinishRsp.proto
  FlightPathMsg.proto
  FlightPathRsp.proto
  HitTargetMsg.proto
  HitTargetRsp.proto
  PingMsg.proto
  PingRsp.proto
  ReadyMsg.proto
  ReadyRsp.proto
  ReadyRspRsp.proto
  StringMsg.proto
  Target.proto
  ZConfigMsg.proto
  ZConfigRsp.proto
  )
source_group("proto" FILES ${${lib_name}_srcs})
list(APPEND ${lib_name}_proto_srcs ${${lib_name}_srcs})
xpFindPkg(PKGS protobuf)
PROTOBUF_GENERATE_CPP(${lib_name}_cpp ${lib_name}_hpp ${${lib_name}_proto_srcs})
source_group(protoc FILE ${${lib_name}_cpp} ${${lib_name}_hpp})
if(MSVC)
  set_source_files_properties(${${lib_name}_cpp} ${${lib_name}_hpp} PROPERTIES COMPILE_FLAGS "/wd4267 /wd4244 /wd4800")
elseif(CMAKE_COMPILER_IS_GNUXX AND (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0))
  set(noMisIndent "-Wno-misleading-indentation")
  check_cxx_compiler_flag("${noMisIndent}" has_noMisIndent)
  if(has_noMisIndent)
    set_source_files_properties(${${lib_name}_cpp} ${${lib_name}_hpp} PROPERTIES COMPILE_FLAGS "${noMisIndent}")
  endif()
endif()
add_library(${lib_name} STATIC ${${lib_name}_cpp} ${${lib_name}_hpp} ${${lib_name}_proto_srcs})
target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../)
xpTargetExtern(${lib_name} PUBLIC protobuf)
set_property(TARGET ${lib_name} PROPERTY FOLDER ${folder})
xpSourceListAppend("${${lib_name}_proto_srcs}")
xpSourceListAppend(${${lib_name}_srcs})
