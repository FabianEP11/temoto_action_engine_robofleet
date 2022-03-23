#include <temoto_action_engine_robofleet/StartUmrfGraph.h>
#include <QByteArray>

temoto_action_engine::StartUmrfGraphResponse FbtoRos(const fb::temoto_action_engine::StartUmrfGraphResponse* src)
{
  temoto_action_engine::StartUmrfGraphResponse msg;
		msg.success=src->success();

  return msg;
}

std::vector<temoto_action_engine::StartUmrfGraphResponse> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StartUmrfGraphResponse>>* src)
{
  std::vector<temoto_action_engine::StartUmrfGraphResponse> dst;
  dst.reserve(src->size());
  typedef flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StartUmrfGraphResponse>> fvec;
  for (fvec::const_iterator it = src->begin(); it != src->end(); ++it)
  {
    dst.push_back(FbtoRos(*it));
  }

  return dst;
}

temoto_action_engine::StartUmrfGraphRequest FbtoRos(const fb::temoto_action_engine::StartUmrfGraphRequest* src)
{
  temoto_action_engine::StartUmrfGraphRequest msg;
		msg.umrf_graph_name=::FbtoRos(src->umrf_graph_name());
		msg.umrf_graph_json=::FbtoRos(src->umrf_graph_json());
		msg.name_match_required=src->name_match_required();

  return msg;
}

std::vector<temoto_action_engine::StartUmrfGraphRequest> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StartUmrfGraphRequest>>* src)
{
  std::vector<temoto_action_engine::StartUmrfGraphRequest> dst;
  dst.reserve(src->size());
  typedef flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::StartUmrfGraphRequest>> fvec;
  for (fvec::const_iterator it = src->begin(); it != src->end(); ++it)
  {
    dst.push_back(FbtoRos(*it));
  }

  return dst;
}

namespace temoto_action_engine_robofleet {

  void StartUmrfGraphSrvInHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::StartUmrfGraph", rbf_topic.c_str());
      };

    server_ = nh.advertiseService(client_service, &StartUmrfGraphSrvInHandler::callback, this);
  }

  void StartUmrfGraphSrvInHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::StartUmrfGraph", rbf_topic.c_str());
      };

    server_ = nh.advertiseService(client_service, &StartUmrfGraphSrvInHandler::callback, this);
  }

  
  QByteArray StartUmrfGraphSrvInHandler::encodeRequestWithMetadata(const RequestType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // encode the metadata
    const MetaDataOffset metadata = encode_metadata_function_(fbb);

    // encode the rest of the type
    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateStartUmrfGraphRequest(fbb,
                                              metadata,
				::RostoFb(fbb, msg.umrf_graph_name),
				::RostoFb(fbb, msg.umrf_graph_json),
				msg.name_match_required).o;

    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }
  
  QByteArray StartUmrfGraphSrvInHandler::encodeRequest(const RequestType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // not including metadata
    const MetaDataOffset metadata = 0;

    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateStartUmrfGraphRequest(fbb,
                                                  metadata,
				::RostoFb(fbb, msg.umrf_graph_name),
				::RostoFb(fbb, msg.umrf_graph_json),
				msg.name_match_required).o;

    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }

  bool StartUmrfGraphSrvInHandler::callback(RequestType& req, ResponseType& res)
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

  PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::StartUmrfGraphSrvInHandler, robofleet_client::ROSSrvInHandler)



  void StartUmrfGraphSrvOutHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::StartUmrfGraph", rbf_topic.c_str());
      };

    client_ = nh.serviceClient<SrvType>(client_service);
  }

  void StartUmrfGraphSrvOutHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::StartUmrfGraph", rbf_topic.c_str());
      };

    client_ = nh.serviceClient<SrvType>(client_service);
  }

  const StartUmrfGraphSrvOutHandler::FbRequestType*
  StartUmrfGraphSrvOutHandler::decodeRequest(const QByteArray& data)
  {
    const FbRequestType* root = 
      flatbuffers::GetRoot<FbRequestType>(data.data());

    return root;
  }

  QByteArray StartUmrfGraphSrvOutHandler::encodeResponseWithMetadata(const ResponseType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // encode the metadata
    const MetaDataOffset metadata = encode_metadata_function_(fbb);

    // encode the rest of the type
    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateStartUmrfGraphResponse(fbb,
                                              metadata,
				msg.success).o;

    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }
  
  void StartUmrfGraphSrvOutHandler::sendRequest(const QByteArray& data)
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

  PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::StartUmrfGraphSrvOutHandler, robofleet_client::ROSSrvOutHandler)
} // namespace temoto_action_engine_robofleet