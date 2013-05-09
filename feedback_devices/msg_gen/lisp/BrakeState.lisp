; Auto-generated. Do not edit!


(cl:in-package feedback_devices-msg)


;//! \htmlinclude BrakeState.msg.html

(cl:defclass <BrakeState> (roslisp-msg-protocol:ros-message)
  ((braking
    :reader braking
    :initarg :braking
    :type cl:float
    :initform 0.0))
)

(cl:defclass BrakeState (<BrakeState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BrakeState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BrakeState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name feedback_devices-msg:<BrakeState> is deprecated: use feedback_devices-msg:BrakeState instead.")))

(cl:ensure-generic-function 'braking-val :lambda-list '(m))
(cl:defmethod braking-val ((m <BrakeState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader feedback_devices-msg:braking-val is deprecated.  Use feedback_devices-msg:braking instead.")
  (braking m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BrakeState>) ostream)
  "Serializes a message object of type '<BrakeState>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'braking))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BrakeState>) istream)
  "Deserializes a message object of type '<BrakeState>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'braking) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BrakeState>)))
  "Returns string type for a message object of type '<BrakeState>"
  "feedback_devices/BrakeState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BrakeState)))
  "Returns string type for a message object of type 'BrakeState"
  "feedback_devices/BrakeState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BrakeState>)))
  "Returns md5sum for a message object of type '<BrakeState>"
  "e26225f002321acda041fe30fccdfc59")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BrakeState)))
  "Returns md5sum for a message object of type 'BrakeState"
  "e26225f002321acda041fe30fccdfc59")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BrakeState>)))
  "Returns full string definition for message of type '<BrakeState>"
  (cl:format cl:nil "float32 braking~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BrakeState)))
  "Returns full string definition for message of type 'BrakeState"
  (cl:format cl:nil "float32 braking~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BrakeState>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BrakeState>))
  "Converts a ROS message object to a list"
  (cl:list 'BrakeState
    (cl:cons ':braking (braking msg))
))
