FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/feedback_devices/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/feedback_devices/msg/__init__.py"
  "../src/feedback_devices/msg/_tacta_box.py"
  "../src/feedback_devices/msg/_tacta_hydra.py"
  "../src/feedback_devices/msg/_BrakeState.py"
  "../src/feedback_devices/msg/_tacta_wrist.py"
  "../src/feedback_devices/msg/_BrakeForce.py"
  "../src/feedback_devices/msg/_tacta_pr2_grippers.py"
  "../src/feedback_devices/msg/_tacta_belt.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
