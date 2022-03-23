#pragma once

// the plugin parent class
#include <robofleet_client/ROSSrvHandlers.hpp>

// get the srv type
#include <temoto_action_engine/StartUmrfGraph.h>

#include <temoto_action_engine_robofleet/temoto_action_engine_generated.h>

// message dependencies


/** Request Conversion Functions **/
temoto_action_engine::StartUmrfGraphResponse FbtoRos(const fb::temoto_action_engine::StartUmrfGraphResponse* src);

std::vector<temoto_action_engine::StartUmrfGraphResponse> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StartUmrfGraphResponse>>* src);

temoto_action_engine::StartUmrfGraphRequest FbtoRos(const fb::temoto_action_engine::StartUmrfGraphRequest* src);

std::vector<temoto_action_engine::StartUmrfGraphRequest> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StartUmrfGraphRequest>>* src);

namespace temoto_action_engine_robofleet {
  
  /** Request Handler **/
  class StartUmrfGraphSrvInHandler : public robofleet_client::ROSSrvInHandler
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
    typedef temoto_action_engine::StartUmrfGraphRequest RequestType;
    typedef temoto_action_engine::StartUmrfGraphResponse ResponseType;
    typedef fb::temoto_action_engine::StartUmrfGraphRequest FbRequestType;
    typedef fb::temoto_action_engine::StartUmrfGraphResponse FbResponseType;

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
  class StartUmrfGraphSrvOutHandler : public robofleet_client::ROSSrvOutHandler
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
    typedef temoto_action_engine::StartUmrfGraph SrvType;
    typedef temoto_action_engine::StartUmrfGraphRequest RequestType;
    typedef temoto_action_engine::StartUmrfGraphResponse ResponseType;
    typedef fb::temoto_action_engine::StartUmrfGraphRequest FbRequestType;
    typedef fb::temoto_action_engine::StartUmrfGraphResponse FbResponseType;

    // converts from raw data to flatbuffer type
    const FbRequestType* decodeRequest(const QByteArray& data);

    // produces a buffer with metadata
    QByteArray encodeResponseWithMetadata(const ResponseType& msg);
  };
}