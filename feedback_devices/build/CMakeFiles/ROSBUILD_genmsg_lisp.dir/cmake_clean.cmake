FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/feedback_devices/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/tacta_box.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_tacta_box.lisp"
  "../msg_gen/lisp/tacta_hydra.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_tacta_hydra.lisp"
  "../msg_gen/lisp/BrakeState.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_BrakeState.lisp"
  "../msg_gen/lisp/tacta_wrist.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_tacta_wrist.lisp"
  "../msg_gen/lisp/BrakeForce.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_BrakeForce.lisp"
  "../msg_gen/lisp/tacta_pr2_grippers.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_tacta_pr2_grippers.lisp"
  "../msg_gen/lisp/tacta_belt.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_tacta_belt.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
