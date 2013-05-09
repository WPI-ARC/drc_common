FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/feedback_devices/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/feedback_devices/tacta_box.h"
  "../msg_gen/cpp/include/feedback_devices/tacta_hydra.h"
  "../msg_gen/cpp/include/feedback_devices/BrakeState.h"
  "../msg_gen/cpp/include/feedback_devices/tacta_wrist.h"
  "../msg_gen/cpp/include/feedback_devices/BrakeForce.h"
  "../msg_gen/cpp/include/feedback_devices/tacta_pr2_grippers.h"
  "../msg_gen/cpp/include/feedback_devices/tacta_belt.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
