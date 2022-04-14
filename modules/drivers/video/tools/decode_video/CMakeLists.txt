cmake_minimum_required(VERSION 3.16)

project(modules_drivers_video_tools_decode_video)
message("${Green} [info] modules_drivers_video_tools_decode_video cmakelist ${ColourReset}")

add_library(modules_drivers_video_tools_decode_video_frame_processor  SHARED
  frame_processor.cc
)
set_target_properties(modules_drivers_video_tools_decode_video_frame_processor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_video_tools_decode_video_frame_processor
  modules::drivers::video::tools::decode_video::h265_decoder
  modules::common::util::util
  ${absl}
)
add_library(modules::drivers::video::tools::decode_video::frame_processor  ALIAS   modules_drivers_video_tools_decode_video_frame_processor)

add_library(modules_drivers_video_tools_decode_video_h265_decoder  SHARED
  h265_decoder.cc
)
set_target_properties(modules_drivers_video_tools_decode_video_h265_decoder  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_video_tools_decode_video_h265_decoder
  cyber::common::log
  ${ffmpeg}
)
add_library(modules::drivers::video::tools::decode_video::h265_decoder  ALIAS   modules_drivers_video_tools_decode_video_h265_decoder)

add_executable(video2jpg
  video2jpg.cc
)
target_link_libraries(video2jpg
  modules::drivers::video::tools::decode_video::frame_processor
  ${gflags_LIBRARIES}
  ${ffmpeg}
)
