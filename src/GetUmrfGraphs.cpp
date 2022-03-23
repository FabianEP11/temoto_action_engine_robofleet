#include <temoto_action_engine_robofleet/GetUmrfGraphs.h>
#include <QByteArray>

temoto_action_engine::GetUmrfGraphsResponse FbtoRos(const fb::temoto_action_engine::GetUmrfGraphsResponse* src)
{
  temoto_action_engine::GetUmrfGraphsResponse msg;
		msg.umrf_graph_jsons=::FbtoRos<std::string,flatbuffers::String>(src->umrf_graph_jsons());

  return msg;
}

std::vector<temoto_action_engine::GetUmrfGraphsResponse> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::GetUmrfGraphsResponse>>* src)
{
  std::vector<temoto_action_engine::GetUmrfGraphsResponse> dst;
  dst.reserve(src->size());
  typedef flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::GetUmrfGraphsResponse>> fvec;
  for (fvec::const_iterator it = src->begin(); it != src->end(); ++it)
  {
    dst.push_back(FbtoRos(*it));
  }

  return dst;
}

temoto_action_engine::GetUmrfGraphsRequest FbtoRos(const fb::temoto_action_engine::GetUmrfGraphsRequest* src)
{
  temoto_action_engine::GetUmrfGraphsRequest msg;
		msg.requested_graphs=::FbtoRos<std::string,flatbuffers::String>(src->requested_graphs());

  return msg;
}

std::vector<temoto_action_engine::GetUmrfGraphsRequest> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::GetUmrfGraphsRequest>>* src)
{
  std::vector<temoto_action_engine::GetUmrfGraphsRequest> dst;
  dst.reserve(src->size());
  typedef flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::GetUmrfGraphsRequest>> fvec;
  for (fvec::const_iterator it = src->begin(); it != src->end(); ++it)
  {
    dst.push_back(FbtoRos(*it));
  }

  return dst;
}

namespace temoto_action_engine_robofleet {

  void GetUmrfGraphsSrvInHandler::initialize(ros::NodeHandle& nh,
                                          MessageScheduler& scheduler,
                                          const std::string client_service,
                                          const std::string rbf_topic,
                                          const ros::Duration timeout)
  {
    robofleet_client::ROSSrvInHandler::initialize(nh,
                                                  scheduler,
                                                  client_service,
                                                  rbf_topic,
                                                  timeout);

    encode_metadata_function_ = [rbf_topic](flatbuffers::FlatBufferBuilder& fbb)
      {
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::GetUmrfGraphs", rbf_topic.c_str());
      };

    server_ = nh.advertiseService(client_service, &GetUmrfGraphsSrvInHandler::callback, this);
  }

  void GetUmrfGraphsSrvInHandler::initialize(ros::NodeHandle& nh,
                                          WsServer& server,
                                          const std::string client_service,
                                          const std::string rbf_topic,
                                          const ros::Duration timeout)
  {
    robofleet_client::ROSSrvInHandler::initialize(nh,
                                                  server,
                                                  client_service,
                                                  rbf_topic,
                                                  timeout);

    encode_metadata_function_ = [rbf_topic](flatbuffers::FlatBufferBuilder& fbb)
      {
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::GetUmrfGraphs", rbf_topic.c_str());
      };

    server_ = nh.advertiseService(client_service, &GetUmrfGraphsSrvInHandler::callback, this);
  }

  
  QByteArray GetUmrfGraphsSrvInHandler::encodeRequestWithMetadata(const RequestType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // encode the metadata
    const MetaDataOffset metadata = encode_metadata_function_(fbb);

    // encode the rest of the type
    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateGetUmrfGraphsRequest(fbb,
                                              metadata,
				::RostoFb<std::string,flatbuffers::String>(fbb, msg.requested_graphs)).o;

    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }
  
  QByteArray GetUmrfGraphsSrvInHandler::encodeRequest(const RequestType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // not including metadata
    const MetaDataOffset metadata = 0;

    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateGetUmrfGraphsRequest(fbb,
                                                  metadata,
				::RostoFb<std::string,flatbuffers::String>(fbb, msg.requested_graphs)).o;

    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }

  bool GetUmrfGraphsSrvInHandler::callback(RequestType& req, ResponseType& res)
  {
    // encode request and schedule for transmission
    const QByteArray data = encodeRequestWithMetadata(req);
    schedule_function_(data);

    // wait until we get a response
    // awaitResponse will return false if we timed out
    if (!awaitReponse())
    {
      return false;
    }

    // decode response
    const FbResponseType* fb = decodeResponse(response_data_);
    res = FbtoRos(fb);

    return true;
  }

  PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::GetUmrfGraphsSrvInHandler, robofleet_client::ROSSrvInHandler)



  void GetUmrfGraphsSrvOutHandler::initialize(ros::NodeHandle& nh,
                                           MessageScheduler& scheduler,
                                           const std::string client_service,
                                           const std::string rbf_topic)
  {
    robofleet_client::ROSSrvOutHandler::initialize(nh,
                                                   scheduler,
                                                   client_service,
                                                   rbf_topic);

    encode_metadata_function_ = [rbf_topic](flatbuffers::FlatBufferBuilder& fbb)
      {
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::GetUmrfGraphs", rbf_topic.c_str());
      };

    client_ = nh.serviceClient<SrvType>(client_service);
  }

  void GetUmrfGraphsSrvOutHandler::initialize(ros::NodeHandle& nh,
                                           WsServer& server,
                                           const std::string client_service,
                                           const std::string rbf_topic)
  {
    robofleet_client::ROSSrvOutHandler::initialize(nh,
                                                   server,
                                                   client_service,
                                                   rbf_topic);

    encode_metadata_function_ = [rbf_topic](flatbuffers::FlatBufferBuilder& fbb)
      {
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::GetUmrfGraphs", rbf_topic.c_str());
      };

    client_ = nh.serviceClient<SrvType>(client_service);
  }

  const GetUmrfGraphsSrvOutHandler::FbRequestType*
  GetUmrfGraphsSrvOutHandler::decodeRequest(const QByteArray& data)
  {
    const FbRequestType* root = 
      flatbuffers::GetRoot<FbRequestType>(data.data());

    return root;
  }

  QByteArray GetUmrfGraphsSrvOutHandler::encodeResponseWithMetadata(const ResponseType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // encode the metadata
    const MetaDataOffset metadata = encode_metadata_function_(fbb);

    // encode the rest of the type
    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateGetUmrfGraphsResponse(fbb,
                                              metadata,
				::RostoFb<std::string,flatbuffers::String>(fbb, msg.umrf_graph_jsons)).o;

    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }
  
  void GetUmrfGraphsSrvOutHandler::sendRequest(const QByteArray& data)
  {
    // decode the request
    const FbRequestType* fb = decodeRequest(data);
    SrvType srv;
    srv.request = FbtoRos(fb);

    ros::AsyncSpinner spinner(1);
    spinner.start();
    
    // send on to the final recipient
    client_.call(srv);

    spinner.stop();

    // encode the response
    const QByteArray response_data = encodeResponseWithMetadata(srv.response);

    // send the response back
    schedule_function_(response_data);
  }

  PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::GetUmrfGraphsSrvOutHandler, robofleet_client::ROSSrvOutHandler)
} // namespace temoto_action_engine_robofleet