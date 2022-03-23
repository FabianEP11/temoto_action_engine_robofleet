#include <temoto_action_engine_robofleet/BroadcastStopUmrfGraph.h>
#include <QByteArray>

temoto_action_engine::BroadcastStopUmrfGraph FbtoRos(const fb::temoto_action_engine::BroadcastStopUmrfGraph* src)
{
  temoto_action_engine::BroadcastStopUmrfGraph msg;
		msg.umrf_graph_name=::FbtoRos(src->umrf_graph_name());
		msg.targets=::FbtoRos<std::string,flatbuffers::String>(src->targets());

  return msg;
}

temoto_action_engine::BroadcastStopUmrfGraph FbtoRos(const fb::temoto_action_engine::BroadcastStopUmrfGraph& src_ref)
{
  const fb::temoto_action_engine::BroadcastStopUmrfGraph* src = &src_ref;
  temoto_action_engine::BroadcastStopUmrfGraph msg;
		msg.umrf_graph_name=::FbtoRos(src->umrf_graph_name());
		msg.targets=::FbtoRos<std::string,flatbuffers::String>(src->targets());

  return msg;
}

std::vector<temoto_action_engine::BroadcastStopUmrfGraph> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStopUmrfGraph>>* src)
{
  std::vector<temoto_action_engine::BroadcastStopUmrfGraph> dst;
  dst.reserve(src->size());
  typedef flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStopUmrfGraph>> fvec;
  for (fvec::const_iterator it = src->begin(); it != src->end(); ++it)
  {
    dst.push_back(FbtoRos(*it));
  }

  return dst;
  
}

flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStopUmrfGraph>>> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const std::vector<temoto_action_engine::BroadcastStopUmrfGraph>& src)
{
  std::vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStopUmrfGraph>> dst(src.size());
  std::transform(
      src.begin(), src.end(), dst.begin(), [&fbb](const temoto_action_engine::BroadcastStopUmrfGraph& item) {
        return RostoFb(fbb, item);
      });
  return fbb.CreateVector(dst).o;
}

flatbuffers::Offset<fb::temoto_action_engine::BroadcastStopUmrfGraph> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const temoto_action_engine::BroadcastStopUmrfGraph& msg)
{
  return fb::temoto_action_engine::CreateBroadcastStopUmrfGraph(fbb, 0,
				::RostoFb(fbb, msg.umrf_graph_name),
				::RostoFb<std::string,flatbuffers::String>(fbb, msg.targets)).o;
}

namespace temoto_action_engine_robofleet {
    
  void BroadcastStopUmrfGraphPublishHandler::initialize(ros::NodeHandle& nh,
                                                 const std::string client_topic,
                                                 const bool latched)
  {
    pub_ = nh.advertise<MsgType>(client_topic,
                                 10,
                                 latched);
  }

  const BroadcastStopUmrfGraphPublishHandler::FbMsgType*
  BroadcastStopUmrfGraphPublishHandler::decode(const QByteArray& data)
  {
    const FbMsgType* root = 
      flatbuffers::GetRoot<FbMsgType>(data.data());

    return root;
  }
  
  void BroadcastStopUmrfGraphPublishHandler::publish(const QByteArray& data)
  {
    const FbMsgType* fb = decode(data);
    const MsgType msg = FbtoRos(fb);
    
    pub_.publish(msg);
  }

  PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::BroadcastStopUmrfGraphPublishHandler, robofleet_client::ROSPublishHandler)
  


  void BroadcastStopUmrfGraphSubscribeHandler::initialize(ros::NodeHandle& nh,
                                              MessageScheduler& scheduler,
                                              const std::string client_topic,
                                              const std::string rbf_topic,
                                              const double priority,
                                              const double rate_limit,
                                              const bool no_drop)
  {
    robofleet_client::ROSSubscribeHandler::initialize(nh,
                                                      scheduler,
                                                      client_topic,
                                                      rbf_topic,
                                                      priority,
                                                      rate_limit,
                                                      no_drop);

    encode_metadata_function_ = [rbf_topic](flatbuffers::FlatBufferBuilder& fbb)
      {
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::BroadcastStopUmrfGraph", rbf_topic.c_str());
      };

    sub_ = nh.subscribe(client_topic, 10, &BroadcastStopUmrfGraphSubscribeHandler::callback, this);
  }


  void BroadcastStopUmrfGraphSubscribeHandler::initialize(ros::NodeHandle& nh,
                                              WsServer& server,
                                              const std::string client_topic,
                                              const std::string rbf_topic)
  {
    robofleet_client::ROSSubscribeHandler::initialize(nh,
                                                      server,
                                                      client_topic,
                                                      rbf_topic);

    encode_metadata_function_ = [rbf_topic](flatbuffers::FlatBufferBuilder& fbb)
      {
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::BroadcastStopUmrfGraph", rbf_topic.c_str());
      };

    sub_ = nh.subscribe(client_topic, 10, &BroadcastStopUmrfGraphSubscribeHandler::callback, this);
  }

  
  QByteArray BroadcastStopUmrfGraphSubscribeHandler::encodeWithMetadata(const MsgType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // encode the metadata
    const MetaDataOffset metadata = encode_metadata_function_(fbb);

    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateBroadcastStopUmrfGraph(fbb,
                                              metadata,
				::RostoFb(fbb, msg.umrf_graph_name),
				::RostoFb<std::string,flatbuffers::String>(fbb, msg.targets)).o;

    // encode the rest of the type
    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }
  

  void BroadcastStopUmrfGraphSubscribeHandler::callback(const MsgTypeConstPtr& msg)
  {
    const QByteArray data = encodeWithMetadata(*msg);
    schedule_function_(data);
  }
} // namespace temoto_action_engine_robofleet

PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::BroadcastStopUmrfGraphSubscribeHandler, robofleet_client::ROSSubscribeHandler)