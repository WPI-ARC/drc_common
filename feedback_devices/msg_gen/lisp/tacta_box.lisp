; Auto-generated. Do not edit!


(cl:in-package feedback_devices-msg)


;//! \htmlinclude tacta_box.msg.html

(cl:defclass <tacta_box> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (active
    :reader active
    :initarg :active
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 16 :element-type 'cl:fixnum :initial-element 0))
   (freq
    :reader freq
    :initarg :freq
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 16 :element-type 'cl:fixnum :initial-element 0))
   (amp_max
    :reader amp_max
    :initarg :amp_max
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 16 :element-type 'cl:fixnum :initial-element 0))
   (amp_min
    :reader amp_min
    :initarg :amp_min
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 16 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass tacta_box (<tacta_box>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <tacta_box>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'tacta_box)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name feedback_devices-msg:<tacta_box> is deprecated: use feedback_devices-msg:tacta_box instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <tacta_box>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:header-val is deprecated.  Use feedback_devices-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'active-val :lambda-list '(m))
(cl:defmethod active-val ((m <tacta_box>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:active-val is deprecated.  Use feedback_devices-msg:active instead.")
  (active m))

(cl:ensure-generic-function 'freq-val :lambda-list '(m))
(cl:defmethod freq-val ((m <tacta_box>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:freq-val is deprecated.  Use feedback_devices-msg:freq instead.")
  (freq m))

(cl:ensure-generic-function 'amp_max-val :lambda-list '(m))
(cl:defmethod amp_max-val ((m <tacta_box>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:amp_max-val is deprecated.  Use feedback_devices-msg:amp_max instead.")
  (amp_max m))

(cl:ensure-generic-function 'amp_min-val :lambda-list '(m))
(cl:defmethod amp_min-val ((m <tacta_box>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:amp_min-val is deprecated.  Use feedback_devices-msg:amp_min instead.")
  (amp_min m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<tacta_box>)))
    "Constants for message type '<tacta_box>"
  '((:FREQ_ON . 255)
    (:FREQ_1HZ . 1)
    (:FREQ_2HZ . 2)
    (:FREQ_3HZ . 3)
    (:FREQ_4HZ . 4)
    (:FREQ_5HZ . 5)
    (:FREQ_OFF . 0)
    (:AMP_OFF . 0)
    (:AMP_WEAK . 64)
    (:AMP_MED . 127)
    (:AMP_STRONG . 190)
    (:AMP_FULL . 255)
    (:INACTIVE . 0)
    (:ACTIVE . 1))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'tacta_box)))
    "Constants for message type 'tacta_box"
  '((:FREQ_ON . 255)
    (:FREQ_1HZ . 1)
    (:FREQ_2HZ . 2)
    (:FREQ_3HZ . 3)
    (:FREQ_4HZ . 4)
    (:FREQ_5HZ . 5)
    (:FREQ_OFF . 0)
    (:AMP_OFF . 0)
    (:AMP_WEAK . 64)
    (:AMP_MED . 127)
    (:AMP_STRONG . 190)
    (:AMP_FULL . 255)
    (:INACTIVE . 0)
    (:ACTIVE . 1))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <tacta_box>) ostream)
  "Serializes a message object of type '<tacta_box>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'active))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'freq))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'amp_max))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'amp_min))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <tacta_box>) istream)
  "Deserializes a message object of type '<tacta_box>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'active) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'active)))
    (cl:dotimes (i 16)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  (cl:setf (cl:slot-value msg 'freq) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'freq)))
    (cl:dotimes (i 16)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  (cl:setf (cl:slot-value msg 'amp_max) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'amp_max)))
    (cl:dotimes (i 16)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  (cl:setf (cl:slot-value msg 'amp_min) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'amp_min)))
    (cl:dotimes (i 16)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<tacta_box>)))
  "Returns string type for a message object of type '<tacta_box>"
  "feedback_devices/tacta_box")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'tacta_box)))
  "Returns string type for a message object of type 'tacta_box"
  "feedback_devices/tacta_box")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<tacta_box>)))
  "Returns md5sum for a message object of type '<tacta_box>"
  "ebbee57de72c42873b6e95e495e7ccbe")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'tacta_box)))
  "Returns md5sum for a message object of type 'tacta_box"
  "ebbee57de72c42873b6e95e495e7ccbe")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<tacta_box>)))
  "Returns full string definition for message of type '<tacta_box>"
  (cl:format cl:nil "uint8 FREQ_ON=255~%uint8 FREQ_1HZ=1~%uint8 FREQ_2HZ=2~%uint8 FREQ_3HZ=3~%uint8 FREQ_4HZ=4~%uint8 FREQ_5HZ=5~%uint8 FREQ_OFF=0~%~%uint8 AMP_OFF=0~%uint8 AMP_WEAK=64~%uint8 AMP_MED=127~%uint8 AMP_STRONG=190~%uint8 AMP_FULL=255~%~%uint8 INACTIVE=0~%uint8 ACTIVE=1~%~%Header header~%~%uint8[16] active~%uint8[16] freq~%uint8[16] amp_max~%uint8[16] amp_min~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'tacta_box)))
  "Returns full string definition for message of type 'tacta_box"
  (cl:format cl:nil "uint8 FREQ_ON=255~%uint8 FREQ_1HZ=1~%uint8 FREQ_2HZ=2~%uint8 FREQ_3HZ=3~%uint8 FREQ_4HZ=4~%uint8 FREQ_5HZ=5~%uint8 FREQ_OFF=0~%~%uint8 AMP_OFF=0~%uint8 AMP_WEAK=64~%uint8 AMP_MED=127~%uint8 AMP_STRONG=190~%uint8 AMP_FULL=255~%~%uint8 INACTIVE=0~%uint8 ACTIVE=1~%~%Header header~%~%uint8[16] active~%uint8[16] freq~%uint8[16] amp_max~%uint8[16] amp_min~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <tacta_box>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'active) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'freq) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'amp_max) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'amp_min) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <tacta_box>))
  "Converts a ROS message object to a list"
  (cl:list 'tacta_box
    (cl:cons ':header (header msg))
    (cl:cons ':active (active msg))
    (cl:cons ':freq (freq msg))
    (cl:cons ':amp_max (amp_max msg))
    (cl:cons ':amp_min (amp_min msg))
))
