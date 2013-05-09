
(cl:in-package :asdf)

(defsystem "feedback_devices-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "tacta_box" :depends-on ("_package_tacta_box"))
    (:file "_package_tacta_box" :depends-on ("_package"))
    (:file "tacta_hydra" :depends-on ("_package_tacta_hydra"))
    (:file "_package_tacta_hydra" :depends-on ("_package"))
    (:file "BrakeState" :depends-on ("_package_BrakeState"))
    (:file "_package_BrakeState" :depends-on ("_package"))
    (:file "tacta_wrist" :depends-on ("_package_tacta_wrist"))
    (:file "_package_tacta_wrist" :depends-on ("_package"))
    (:file "BrakeForce" :depends-on ("_package_BrakeForce"))
    (:file "_package_BrakeForce" :depends-on ("_package"))
    (:file "tacta_pr2_grippers" :depends-on ("_package_tacta_pr2_grippers"))
    (:file "_package_tacta_pr2_grippers" :depends-on ("_package"))
    (:file "tacta_belt" :depends-on ("_package_tacta_belt"))
    (:file "_package_tacta_belt" :depends-on ("_package"))
  ))