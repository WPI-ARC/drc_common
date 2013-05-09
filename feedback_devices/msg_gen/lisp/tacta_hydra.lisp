; Auto-generated. Do not edit!


(cl:in-package feedback_devices-msg)


;//! \htmlinclude tacta_hydra.msg.html

(cl:defclass <tacta_hydra> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (freq
    :reader freq
    :initarg :freq
    :type (cl:vector cl:integer)
   :initform (cl:make-array 2 :element-type 'cl:integer :initial-element 0))
   (amp
    :reader amp
    :initarg :amp
    :type (cl:vector cl:integer)
   :initform (cl:make-array 2 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass tacta_hydra (<tacta_hydra>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <tacta_hydra>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'tacta_hydra)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name feedback_devices-msg:<tacta_hydra> is deprecated: use feedback_devices-msg:tacta_hydra instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <tacta_hydra>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:header-val is deprecated.  Use feedback_devices-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'freq-val :lambda-list '(m))
(cl:defmethod freq-val ((m <tacta_hydra>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:freq-val is deprecated.  Use feedback_devices-msg:freq instead.")
  (freq m))

(cl:ensure-generic-function 'amp-val :lambda-list '(m))
(cl:defmethod amp-val ((m <tacta_hydra>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:amp-val is deprecated.  Use feedback_devices-msg:amp instead.")
  (amp m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<tacta_hydra>)))
    "Constants for message type '<tacta_hydra>"
  '((:LEFT . 0)
    (:RIGHT . 1)
    (:FREQ_ON . 255)
    (:FREQ_CRUSH . 1)
    (:FREQ_SLIP . 5)
    (:FREQ_OFF . 0))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'tacta_hydra)))
    "Constants for message type 'tacta_hydra"
  '((:LEFT . 0)
    (:RIGHT . 1)
    (:FREQ_ON . 255)
    (:FREQ_CRUSH . 1)
    (:FREQ_SLIP . 5)
    (:FREQ_OFF . 0))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <tacta_hydra>) ostream)
  "Serializes a message object of type '<tacta_hydra>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'freq))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'amp))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <tacta_hydra>) istream)
  "Deserializes a message object of type '<tacta_hydra>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'freq) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'freq)))
    (cl:dotimes (i 2)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'amp) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'amp)))
    (cl:dotimes (i 2)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<tacta_hydra>)))
  "Returns string type for a message object of type '<tacta_hydra>"
  "feedback_devices/tacta_hydra")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'tacta_hydra)))
  "Returns string type for a message object of type 'tacta_hydra"
  "feedback_devices/tacta_hydra")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<tacta_hydra>)))
  "Returns md5sum for a message object of type '<tacta_hydra>"
  "705d4d3a802020d08354e99414158546")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'tacta_hydra)))
  "Returns md5sum for a message object of type 'tacta_hydra"
  "705d4d3a802020d08354e99414158546")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<tacta_hydra>)))
  "Returns full string definition for message of type '<tacta_hydra>"
  (cl:format cl:nil "~%uint8 LEFT=0~%uint8 RIGHT=1~%~%uint8 FREQ_ON=255~%uint8 FREQ_CRUSH=1~%uint8 FREQ_SLIP=5~%uint8 FREQ_OFF=0~%~%Header header~%~%int32[2] freq~%int32[2] amp~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'tacta_hydra)))
  "Returns full string definition for message of type 'tacta_hydra"
  (cl:format cl:nil "~%uint8 LEFT=0~%uint8 RIGHT=1~%~%uint8 FREQ_ON=255~%uint8 FREQ_CRUSH=1~%uint8 FREQ_SLIP=5~%uint8 FREQ_OFF=0~%~%Header header~%~%int32[2] freq~%int32[2] amp~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <tacta_hydra>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'freq) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'amp) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <tacta_hydra>))
  "Converts a ROS message object to a list"
  (cl:list 'tacta_hydra
    (cl:cons ':header (header msg))
    (cl:cons ':freq (freq msg))
    (cl:cons ':amp (amp msg))
))
