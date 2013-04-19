Whether or not to cause translations, boolean, default = true  
"/gui/valve_interact/cause_translations"

Whether or not to cause rotations, boolean, default = true
"/gui/valve_interact/cause_rotations"

Max amount of rotation in degrees, integar, default = 10
"/gui/valve_interact/max_rotation_deg"

Max amount to cause translation in millimeters, integer, default = 25
"/gui/valve_interact/max_translation_mm"

Number of test iterations, integer, default = 100
"/gui/valve_interact/test_iterations"

DTW max amount of translation to call something good in mm, integer, default = 5
"/gui/valve_interact/DTW_max_good_translation_err_mm"

DTW max amount of rotation to call something good in degrees, integer, default = 10
"/gui/valve_interact/DTW_max_good_rotational_err_deg"

DTW what to call a good position, string, default = "KG-EX"
"/gui/valve_interact/DTW_good_id"

DTW what to call a bad position, string, default = "KB-EX"
"/gui/valve_interact/DTW_bad_id"

Whether or not to align the valve to the pointcloud before sending to the robot, boolean, default = false
"/gui/valve_interact/use_valve_icp"

Whether or not to send the alignment to the robot, boolean, default = true
"/gui/valve_interact/send_2_robot"

Whether or not to print debug messages, boolean, default = true
"/gui/valve_interact/print_debug"

Time to delay after updating the interactive marker server, ie, do you see it before it sends, integer, default = 0
"/gui/valve_interact/test_display_delay_sec", 0);
