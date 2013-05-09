; Auto-generated. Do not edit!


(cl:in-package feedback_devices-msg)


;//! \htmlinclude tacta_pr2_grippers.msg.html

(cl:defclass <tacta_pr2_grippers> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (rh_rf_freq
    :reader rh_rf_freq
    :initarg :rh_rf_freq
    :type cl:integer
    :initform 0)
   (rh_lf_freq
    :reader rh_lf_freq
    :initarg :rh_lf_freq
    :type cl:integer
    :initform 0)
   (rh_rf_amp
    :reader rh_rf_amp
    :initarg :rh_rf_amp
    :type cl:integer
    :initform 0)
   (rh_lf_amp
    :reader rh_lf_amp
    :initarg :rh_lf_amp
    :type cl:integer
    :initform 0)
   (lh_rf_freq
    :reader lh_rf_freq
    :initarg :lh_rf_freq
    :type cl:integer
    :initform 0)
   (lh_lf_freq
    :reader lh_lf_freq
    :initarg :lh_lf_freq
    :type cl:integer
    :initform 0)
   (lh_rf_amp
    :reader lh_rf_amp
    :initarg :lh_rf_amp
    :type cl:integer
    :initform 0)
   (lh_lf_amp
    :reader lh_lf_amp
    :initarg :lh_lf_amp
    :type cl:integer
    :initform 0)
   (rh_grip_quality
    :reader rh_grip_quality
    :initarg :rh_grip_quality
    :type (cl:vector cl:integer)
   :initform (cl:make-array 6 :element-type 'cl:integer :initial-element 0))
   (lh_grip_quality
    :reader lh_grip_quality
    :initarg :lh_grip_quality
    :type (cl:vector cl:integer)
   :initform (cl:make-array 6 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass tacta_pr2_grippers (<tacta_pr2_grippers>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <tacta_pr2_grippers>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'tacta_pr2_grippers)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name feedback_devices-msg:<tacta_pr2_grippers> is deprecated: use feedback_devices-msg:tacta_pr2_grippers instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:header-val is deprecated.  Use feedback_devices-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'rh_rf_freq-val :lambda-list '(m))
(cl:defmethod rh_rf_freq-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:rh_rf_freq-val is deprecated.  Use feedback_devices-msg:rh_rf_freq instead.")
  (rh_rf_freq m))

(cl:ensure-generic-function 'rh_lf_freq-val :lambda-list '(m))
(cl:defmethod rh_lf_freq-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:rh_lf_freq-val is deprecated.  Use feedback_devices-msg:rh_lf_freq instead.")
  (rh_lf_freq m))

(cl:ensure-generic-function 'rh_rf_amp-val :lambda-list '(m))
(cl:defmethod rh_rf_amp-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:rh_rf_amp-val is deprecated.  Use feedback_devices-msg:rh_rf_amp instead.")
  (rh_rf_amp m))

(cl:ensure-generic-function 'rh_lf_amp-val :lambda-list '(m))
(cl:defmethod rh_lf_amp-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:rh_lf_amp-val is deprecated.  Use feedback_devices-msg:rh_lf_amp instead.")
  (rh_lf_amp m))

(cl:ensure-generic-function 'lh_rf_freq-val :lambda-list '(m))
(cl:defmethod lh_rf_freq-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:lh_rf_freq-val is deprecated.  Use feedback_devices-msg:lh_rf_freq instead.")
  (lh_rf_freq m))

(cl:ensure-generic-function 'lh_lf_freq-val :lambda-list '(m))
(cl:defmethod lh_lf_freq-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:lh_lf_freq-val is deprecated.  Use feedback_devices-msg:lh_lf_freq instead.")
  (lh_lf_freq m))

(cl:ensure-generic-function 'lh_rf_amp-val :lambda-list '(m))
(cl:defmethod lh_rf_amp-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:lh_rf_amp-val is deprecated.  Use feedback_devices-msg:lh_rf_amp instead.")
  (lh_rf_amp m))

(cl:ensure-generic-function 'lh_lf_amp-val :lambda-list '(m))
(cl:defmethod lh_lf_amp-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:lh_lf_amp-val is deprecated.  Use feedback_devices-msg:lh_lf_amp instead.")
  (lh_lf_amp m))

(cl:ensure-generic-function 'rh_grip_quality-val :lambda-list '(m))
(cl:defmethod rh_grip_quality-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:rh_grip_quality-val is deprecated.  Use feedback_devices-msg:rh_grip_quality instead.")
  (rh_grip_quality m))

(cl:ensure-generic-function 'lh_grip_quality-val :lambda-list '(m))
(cl:defmethod lh_grip_quality-val ((m <tacta_pr2_grippers>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:lh_grip_quality-val is deprecated.  Use feedback_devices-msg:lh_grip_quality instead.")
  (lh_grip_quality m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <tacta_pr2_grippers>) ostream)
  "Serializes a message object of type '<tacta_pr2_grippers>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'rh_rf_freq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rh_lf_freq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rh_rf_amp)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rh_lf_amp)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'lh_rf_freq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'lh_lf_freq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'lh_rf_amp)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'lh_lf_amp)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'rh_grip_quality))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'lh_grip_quality))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <tacta_pr2_grippers>) istream)
  "Deserializes a message object of type '<tacta_pr2_grippers>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rh_rf_freq) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rh_lf_freq) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rh_rf_amp) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rh_lf_amp) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lh_rf_freq) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lh_lf_freq) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lh_rf_amp) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lh_lf_amp) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:setf (cl:slot-value msg 'rh_grip_quality) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'rh_grip_quality)))
    (cl:dotimes (i 6)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'lh_grip_quality) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'lh_grip_quality)))
    (cl:dotimes (i 6)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<tacta_pr2_grippers>)))
  "Returns string type for a message object of type '<tacta_pr2_grippers>"
  "feedback_devices/tacta_pr2_grippers")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'tacta_pr2_grippers)))
  "Returns string type for a message object of type 'tacta_pr2_grippers"
  "feedback_devices/tacta_pr2_grippers")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<tacta_pr2_grippers>)))
  "Returns md5sum for a message object of type '<tacta_pr2_grippers>"
  "6f511160451a24188f64b49198493eca")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'tacta_pr2_grippers)))
  "Returns md5sum for a message object of type 'tacta_pr2_grippers"
  "6f511160451a24188f64b49198493eca")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<tacta_pr2_grippers>)))
  "Returns full string definition for message of type '<tacta_pr2_grippers>"
  (cl:format cl:nil "Header header~%~%#uint8 RH_RF=0~%#uint8 RH_LF=1~%#uint8 LH_RF=3~%#uint8 LH_LF=4~%~%#int32[4] freq~%#int32[4] min_amp~%#int32[4] max_amp~%~%int32 rh_rf_freq~%int32 rh_lf_freq~%int32 rh_rf_amp~%int32 rh_lf_amp~%~%int32 lh_rf_freq~%int32 lh_lf_freq~%int32 lh_rf_amp~%int32 lh_lf_amp~%~%int32[6] rh_grip_quality~%int32[6] lh_grip_quality~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'tacta_pr2_grippers)))
  "Returns full string definition for message of type 'tacta_pr2_grippers"
  (cl:format cl:nil "Header header~%~%#uint8 RH_RF=0~%#uint8 RH_LF=1~%#uint8 LH_RF=3~%#uint8 LH_LF=4~%~%#int32[4] freq~%#int32[4] min_amp~%#int32[4] max_amp~%~%int32 rh_rf_freq~%int32 rh_lf_freq~%int32 rh_rf_amp~%int32 rh_lf_amp~%~%int32 lh_rf_freq~%int32 lh_lf_freq~%int32 lh_rf_amp~%int32 lh_lf_amp~%~%int32[6] rh_grip_quality~%int32[6] lh_grip_quality~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <tacta_pr2_grippers>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     4
     4
     4
     4
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'rh_grip_quality) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'lh_grip_quality) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <tacta_pr2_grippers>))
  "Converts a ROS message object to a list"
  (cl:list 'tacta_pr2_grippers
    (cl:cons ':header (header msg))
    (cl:cons ':rh_rf_freq (rh_rf_freq msg))
    (cl:cons ':rh_lf_freq (rh_lf_freq msg))
    (cl:cons ':rh_rf_amp (rh_rf_amp msg))
    (cl:cons ':rh_lf_amp (rh_lf_amp msg))
    (cl:cons ':lh_rf_freq (lh_rf_freq msg))
    (cl:cons ':lh_lf_freq (lh_lf_freq msg))
    (cl:cons ':lh_rf_amp (lh_rf_amp msg))
    (cl:cons ':lh_lf_amp (lh_lf_amp msg))
    (cl:cons ':rh_grip_quality (rh_grip_quality msg))
    (cl:cons ':lh_grip_quality (lh_grip_quality msg))
))
