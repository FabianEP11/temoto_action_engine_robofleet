#include <temoto_action_engine_robofleet/BroadcastStartUmrfGraph.h>
#include <QByteArray>

temoto_action_engine::BroadcastStartUmrfGraph FbtoRos(const fb::temoto_action_engine::BroadcastStartUmrfGraph* src)
{
  temoto_action_engine::BroadcastStartUmrfGraph msg;
		msg.umrf_graph_name=::FbtoRos(src->umrf_graph_name());
		msg.name_match_required=src->name_match_required();
		msg.targets=::FbtoRos<std::string,flatbuffers::String>(src->targets());
		msg.umrf_graph_json=::FbtoRos(src->umrf_graph_json());
		msg.umrf_graph_diffs=::FbtoRos(src->umrf_graph_diffs());

  return msg;
}

temoto_action_engine::BroadcastStartUmrfGraph FbtoRos(const fb::temoto_action_engine::BroadcastStartUmrfGraph& src_ref)
{
  const fb::temoto_action_engine::BroadcastStartUmrfGraph* src = &src_ref;
  temoto_action_engine::BroadcastStartUmrfGraph msg;
		msg.umrf_graph_name=::FbtoRos(src->umrf_graph_name());
		msg.name_match_required=src->name_match_required();
		msg.targets=::FbtoRos<std::string,flatbuffers::String>(src->targets());
		msg.umrf_graph_json=::FbtoRos(src->umrf_graph_json());
		msg.umrf_graph_diffs=::FbtoRos(src->umrf_graph_diffs());

  return msg;
}

std::vector<temoto_action_engine::BroadcastStartUmrfGraph> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStartUmrfGraph>>* src)
{
  std::vector<temoto_action_engine::BroadcastStartUmrfGraph> dst;
  dst.reserve(src->size());
  typedef flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStartUmrfGraph>> fvec;
  for (fvec::const_iterator it = src->begin(); it != src->end(); ++it)
  {
    dst.push_back(FbtoRos(*it));
  }

  return dst;
  
}

flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStartUmrfGraph>>> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const std::vector<temoto_action_engine::BroadcastStartUmrfGraph>& src)
{
  std::vector<flatbuffers::Offset<fb::temoto_action_engine::BroadcastStartUmrfGraph>> dst(src.size());
  std::transform(
      src.begin(), src.end(), dst.begin(), [&fbb](const temoto_action_engine::BroadcastStartUmrfGraph& item) {
        return RostoFb(fbb, item);
      });
  return fbb.CreateVector(dst).o;
}

flatbuffers::Offset<fb::temoto_action_engine::BroadcastStartUmrfGraph> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const temoto_action_engine::BroadcastStartUmrfGraph& msg)
{
  return fb::temoto_action_engine::CreateBroadcastStartUmrfGraph(fbb, 0,
				::RostoFb(fbb, msg.umrf_graph_name),
				msg.name_match_required,
				::RostoFb<std::string,flatbuffers::String>(fbb, msg.targets),
				::RostoFb(fbb, msg.umrf_graph_json),
				::RostoFb(fbb, msg.umrf_graph_diffs)).o;
}

namespace temoto_action_engine_robofleet {
    
  void BroadcastStartUmrfGraphPublishHandler::initialize(ros::NodeHandle& nh,
                                                 const std::string client_topic,
                                                 const bool latched)
  {
    pub_ = nh.advertise<MsgType>(client_topic,
                                 10,
                                 latched);
  }

  const BroadcastStartUmrfGraphPublishHandler::FbMsgType*
  BroadcastStartUmrfGraphPublishHandler::decode(const QByteArray& data)
  {
    const FbMsgType* root = 
      flatbuffers::GetRoot<FbMsgType>(data.data());

    return root;
  }
  
  void BroadcastStartUmrfGraphPublishHandler::publish(const QByteArray& data)
  {
    const FbMsgType* fb = decode(data);
    const MsgType msg = FbtoRos(fb);
    
    pub_.publish(msg);
  }

  PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::BroadcastStartUmrfGraphPublishHandler, robofleet_client::ROSPublishHandler)
  


  void BroadcastStartUmrfGraphSubscribeHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::BroadcastStartUmrfGraph", rbf_topic.c_str());
      };

    sub_ = nh.subscribe(client_topic, 10, &BroadcastStartUmrfGraphSubscribeHandler::callback, this);
  }


  void BroadcastStartUmrfGraphSubscribeHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::BroadcastStartUmrfGraph", rbf_topic.c_str());
      };

    sub_ = nh.subscribe(client_topic, 10, &BroadcastStartUmrfGraphSubscribeHandler::callback, this);
  }

  
  QByteArray BroadcastStartUmrfGraphSubscribeHandler::encodeWithMetadata(const MsgType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // encode the metadata
    const MetaDataOffset metadata = encode_metadata_function_(fbb);

    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateBroadcastStartUmrfGraph(fbb,
                                              metadata,
				::RostoFb(fbb, msg.umrf_graph_name),
				msg.name_match_required,
				::RostoFb<std::string,flatbuffers::String>(fbb, msg.targets),
				::RostoFb(fbb, msg.umrf_graph_json),
				::RostoFb(fbb, msg.umrf_graph_diffs)).o;

    // encode the rest of the type
    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }
  

  void BroadcastStartUmrfGraphSubscribeHandler::callback(const MsgTypeConstPtr& msg)
  {
    const QByteArray data = encodeWithMetadata(*msg);
    schedule_function_(data);
  }
} // namespace temoto_action_engine_robofleet

PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::BroadcastStartUmrfGraphSubscribeHandler, robofleet_client::ROSSubscribeHandler)