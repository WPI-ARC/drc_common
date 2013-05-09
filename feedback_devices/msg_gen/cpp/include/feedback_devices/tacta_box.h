/* Auto-generated by genmsg_cpp for file /home/nick/Dropbox/ROS_Workspace/drc_common/feedback_devices/msg/tacta_box.msg */
#ifndef FEEDBACK_DEVICES_MESSAGE_TACTA_BOX_H
#define FEEDBACK_DEVICES_MESSAGE_TACTA_BOX_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"

namespace feedback_devices
{
template <class ContainerAllocator>
struct tacta_box_ {
  typedef tacta_box_<ContainerAllocator> Type;

  tacta_box_()
  : header()
  , active()
  , freq()
  , amp_max()
  , amp_min()
  {
    active.assign(0);
    freq.assign(0);
    amp_max.assign(0);
    amp_min.assign(0);
  }

  tacta_box_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , active()
  , freq()
  , amp_max()
  , amp_min()
  {
    active.assign(0);
    freq.assign(0);
    amp_max.assign(0);
    amp_min.assign(0);
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef boost::array<uint8_t, 16>  _active_type;
  boost::array<uint8_t, 16>  active;

  typedef boost::array<uint8_t, 16>  _freq_type;
  boost::array<uint8_t, 16>  freq;

  typedef boost::array<uint8_t, 16>  _amp_max_type;
  boost::array<uint8_t, 16>  amp_max;

  typedef boost::array<uint8_t, 16>  _amp_min_type;
  boost::array<uint8_t, 16>  amp_min;

  enum { FREQ_ON = 255 };
  enum { FREQ_1HZ = 1 };
  enum { FREQ_2HZ = 2 };
  enum { FREQ_3HZ = 3 };
  enum { FREQ_4HZ = 4 };
  enum { FREQ_5HZ = 5 };
  enum { FREQ_OFF = 0 };
  enum { AMP_OFF = 0 };
  enum { AMP_WEAK = 64 };
  enum { AMP_MED = 127 };
  enum { AMP_STRONG = 190 };
  enum { AMP_FULL = 255 };
  enum { INACTIVE = 0 };
  enum { ACTIVE = 1 };

  typedef boost::shared_ptr< ::feedback_devices::tacta_box_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::feedback_devices::tacta_box_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct tacta_box
typedef  ::feedback_devices::tacta_box_<std::allocator<void> > tacta_box;

typedef boost::shared_ptr< ::feedback_devices::tacta_box> tacta_boxPtr;
typedef boost::shared_ptr< ::feedback_devices::tacta_box const> tacta_boxConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::feedback_devices::tacta_box_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::feedback_devices::tacta_box_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace feedback_devices

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::feedback_devices::tacta_box_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::feedback_devices::tacta_box_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::feedback_devices::tacta_box_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ebbee57de72c42873b6e95e495e7ccbe";
  }

  static const char* value(const  ::feedback_devices::tacta_box_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xebbee57de72c4287ULL;
  static const uint64_t static_value2 = 0x3b6e95e495e7ccbeULL;
};

template<class ContainerAllocator>
struct DataType< ::feedback_devices::tacta_box_<ContainerAllocator> > {
  static const char* value() 
  {
    return "feedback_devices/tacta_box";
  }

  static const char* value(const  ::feedback_devices::tacta_box_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::feedback_devices::tacta_box_<ContainerAllocator> > {
  static const char* value() 
  {
    return "uint8 FREQ_ON=255\n\
uint8 FREQ_1HZ=1\n\
uint8 FREQ_2HZ=2\n\
uint8 FREQ_3HZ=3\n\
uint8 FREQ_4HZ=4\n\
uint8 FREQ_5HZ=5\n\
uint8 FREQ_OFF=0\n\
\n\
uint8 AMP_OFF=0\n\
uint8 AMP_WEAK=64\n\
uint8 AMP_MED=127\n\
uint8 AMP_STRONG=190\n\
uint8 AMP_FULL=255\n\
\n\
uint8 INACTIVE=0\n\
uint8 ACTIVE=1\n\
\n\
Header header\n\
\n\
uint8[16] active\n\
uint8[16] freq\n\
uint8[16] amp_max\n\
uint8[16] amp_min\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
";
  }

  static const char* value(const  ::feedback_devices::tacta_box_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::feedback_devices::tacta_box_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::feedback_devices::tacta_box_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::feedback_devices::tacta_box_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.active);
    stream.next(m.freq);
    stream.next(m.amp_max);
    stream.next(m.amp_min);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct tacta_box_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::feedback_devices::tacta_box_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::feedback_devices::tacta_box_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "active[]" << std::endl;
    for (size_t i = 0; i < v.active.size(); ++i)
    {
      s << indent << "  active[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.active[i]);
    }
    s << indent << "freq[]" << std::endl;
    for (size_t i = 0; i < v.freq.size(); ++i)
    {
      s << indent << "  freq[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.freq[i]);
    }
    s << indent << "amp_max[]" << std::endl;
    for (size_t i = 0; i < v.amp_max.size(); ++i)
    {
      s << indent << "  amp_max[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.amp_max[i]);
    }
    s << indent << "amp_min[]" << std::endl;
    for (size_t i = 0; i < v.amp_min.size(); ++i)
    {
      s << indent << "  amp_min[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.amp_min[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // FEEDBACK_DEVICES_MESSAGE_TACTA_BOX_H

