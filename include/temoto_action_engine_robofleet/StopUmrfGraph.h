#pragma once

// the plugin parent class
#include <robofleet_client/ROSSrvHandlers.hpp>

// get the srv type
#include <temoto_action_engine/StopUmrfGraph.h>

#include <temoto_action_engine_robofleet/temoto_action_engine_generated.h>

// message dependencies


/** Request Conversion Functions **/
temoto_action_engine::StopUmrfGraphResponse FbtoRos(const fb::temoto_action_engine::StopUmrfGraphResponse* src);

std::vector<temoto_action_engine::StopUmrfGraphResponse> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StopUmrfGraphResponse>>* src);

temoto_action_engine::StopUmrfGraphRequest FbtoRos(const fb::temoto_action_engine::StopUmrfGraphRequest* src);

std::vector<temoto_action_engine::StopUmrfGraphRequest> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StopUmrfGraphRequest>>* src);

namespace temoto_action_engine_robofleet {
  
  /** Request Handler **/
  class StopUmrfGraphSrvInHandler : public robofleet_client::ROSSrvInHandler
  {
  public:
    // sets up subscriber, message scheduler function, and metadata function
    virtual void initialize(ros::NodeHandle& nh,
                            MessageScheduler& scheduler,
                            const std::string client_service,
                            const std::string rbf_topic,
                            const ros::Duration timeout);
    
    virtual void initialize(ros::NodeHandle& nh,
                            WsServer& scheduler,
                            const std::string client_service,
                            const std::string rbf_topic,
                            const ros::Duration timeout);
  private:
    typedef temoto_action_engine::StopUmrfGraphRequest RequestType;
    typedef temoto_action_engine::StopUmrfGraphResponse ResponseType;
    typedef fb::temoto_action_engine::StopUmrfGraphRequest FbRequestType;
    typedef fb::temoto_action_engine::StopUmrfGraphResponse FbResponseType;

    // produces a buffer with metadata
    QByteArray encodeRequestWithMetadata(const RequestType& msg);

    // converts from flatbuffer type to raw data
    QByteArray encodeRequest(const RequestType& msg);

    // converts from raw data to flatbuffer type
    const FbResponseType* decodeResponse(const QByteArray& data);
    
    // encodes the message
    bool callback(RequestType& req, ResponseType& res);
  };

    /** Response Handler **/
  class StopUmrfGraphSrvOutHandler : public robofleet_client::ROSSrvOutHandler
  {
  public:
    // sets up subscriber, message scheduler function, and metadata function
    virtual void initialize(ros::NodeHandle& nh,
                            MessageScheduler& scheduler,
                            const std::string client_service,
                            const std::string rbf_topic);
    
    virtual void initialize(ros::NodeHandle& nh,
                            WsServer& server,
                            const std::string client_service,
                            const std::string rbf_topic);

    virtual void sendRequest(const QByteArray& data);

  private:
    typedef temoto_action_engine::StopUmrfGraph SrvType;
    typedef temoto_action_engine::StopUmrfGraphRequest RequestType;
    typedef temoto_action_engine::StopUmrfGraphResponse ResponseType;
    typedef fb::temoto_action_engine::StopUmrfGraphRequest FbRequestType;
    typedef fb::temoto_action_engine::StopUmrfGraphResponse FbResponseType;

    // converts from raw data to flatbuffer type
    const FbRequestType* decodeRequest(const QByteArray& data);

    // produces a buffer with metadata
    QByteArray encodeResponseWithMetadata(const ResponseType& msg);
  };
}