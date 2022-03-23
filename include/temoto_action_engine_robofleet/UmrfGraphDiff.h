#pragma once

// the plugin parent class
#include <robofleet_client/ROSMsgHandlers.hpp>

// get the msg type
#include <temoto_action_engine/UmrfGraphDiff.h>

#include <temoto_action_engine_robofleet/temoto_action_engine_generated.h>

// message dependencies


/** Conversion Functions **/
temoto_action_engine::UmrfGraphDiff FbtoRos(const fb::temoto_action_engine::UmrfGraphDiff* src);

std::vector<temoto_action_engine::UmrfGraphDiff> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff>>* src);

flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff>>> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const std::vector<temoto_action_engine::UmrfGraphDiff>& msg);

flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const temoto_action_engine::UmrfGraphDiff& msg);

namespace temoto_action_engine_robofleet {

  /** Publish Handler **/
  class UmrfGraphDiffPublishHandler : public robofleet_client::ROSPublishHandler
  {
  public:

    // advertises the topic
    virtual void initialize(ros::NodeHandle& nh,
                            const std::string client_topic,
                            const bool latched);
    
    // decodes raw data into the flatbuffer type,
    // then converts to the ROS type, then publishes to the topic
    virtual void publish(const QByteArray& data);

  private:
    typedef temoto_action_engine::UmrfGraphDiff MsgType;
    typedef fb::temoto_action_engine::UmrfGraphDiff FbMsgType;

    // converts from raw data to flatbuffer type
    const FbMsgType* decode(const QByteArray& data);
  };
  
  
  /** Subscribe Handler **/
  class UmrfGraphDiffSubscribeHandler : public robofleet_client::ROSSubscribeHandler
  {
  public:
    // sets up subscriber, message scheduler function, and metadata function
    virtual void initialize(ros::NodeHandle& nh,
                            MessageScheduler& scheduler,
                            const std::string client_topic,
                            const std::string rbf_topic,
                            const double priority,
                            const double rate_limit,
                            const bool no_drop);

    virtual void initialize(ros::NodeHandle& nh,
                            WsServer& server,
                            const std::string client_topic,
                            const std::string rbf_topic);
    
  private:
    typedef temoto_action_engine::UmrfGraphDiff MsgType;
    typedef boost::shared_ptr<MsgType> MsgTypeConstPtr;

    // produces a buffer with metadata
    QByteArray encodeWithMetadata(const MsgType& msg);
    
    // encodes the message
    void callback(const MsgTypeConstPtr& msg);
  };
}