; Auto-generated. Do not edit!


(cl:in-package feedback_devices-msg)


;//! \htmlinclude tacta_belt.msg.html

(cl:defclass <tacta_belt> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (motors
    :reader motors
    :initarg :motors
    :type cl:fixnum
    :initform 0)
   (values
    :reader values
    :initarg :values
    :type (cl:vector cl:float)
   :initform (cl:make-array 16 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass tacta_belt (<tacta_belt>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <tacta_belt>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'tacta_belt)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name feedback_devices-msg:<tacta_belt> is deprecated: use feedback_devices-msg:tacta_belt instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <tacta_belt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:header-val is deprecated.  Use feedback_devices-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'motors-val :lambda-list '(m))
(cl:defmethod motors-val ((m <tacta_belt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:motors-val is deprecated.  Use feedback_devices-msg:motors instead.")
  (motors m))

(cl:ensure-generic-function 'values-val :lambda-list '(m))
(cl:defmethod values-val ((m <tacta_belt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:values-val is deprecated.  Use feedback_devices-msg:values instead.")
  (values m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <tacta_belt>) ostream)
  "Serializes a message object of type '<tacta_belt>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motors)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'values))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <tacta_belt>) istream)
  "Deserializes a message object of type '<tacta_belt>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motors)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'values) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'values)))
    (cl:dotimes (i 16)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<tacta_belt>)))
  "Returns string type for a message object of type '<tacta_belt>"
  "feedback_devices/tacta_belt")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'tacta_belt)))
  "Returns string type for a message object of type 'tacta_belt"
  "feedback_devices/tacta_belt")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<tacta_belt>)))
  "Returns md5sum for a message object of type '<tacta_belt>"
  "6594452e6e5a30284436e89b1d1531a8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'tacta_belt)))
  "Returns md5sum for a message object of type 'tacta_belt"
  "6594452e6e5a30284436e89b1d1531a8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<tacta_belt>)))
  "Returns full string definition for message of type '<tacta_belt>"
  (cl:format cl:nil "Header header~%~%uint8 motors~%float32[16] values~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'tacta_belt)))
  "Returns full string definition for message of type 'tacta_belt"
  (cl:format cl:nil "Header header~%~%uint8 motors~%float32[16] values~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <tacta_belt>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'values) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <tacta_belt>))
  "Converts a ROS message object to a list"
  (cl:list 'tacta_belt
    (cl:cons ':header (header msg))
    (cl:cons ':motors (motors msg))
    (cl:cons ':values (values msg))
))
