#include <temoto_action_engine_robofleet/UmrfGraphDiff.h>
#include <QByteArray>

temoto_action_engine::UmrfGraphDiff FbtoRos(const fb::temoto_action_engine::UmrfGraphDiff* src)
{
  temoto_action_engine::UmrfGraphDiff msg;
		msg.operation=::FbtoRos(src->operation());
		msg.umrf_json=::FbtoRos(src->umrf_json());

  return msg;
}

temoto_action_engine::UmrfGraphDiff FbtoRos(const fb::temoto_action_engine::UmrfGraphDiff& src_ref)
{
  const fb::temoto_action_engine::UmrfGraphDiff* src = &src_ref;
  temoto_action_engine::UmrfGraphDiff msg;
		msg.operation=::FbtoRos(src->operation());
		msg.umrf_json=::FbtoRos(src->umrf_json());

  return msg;
}

std::vector<temoto_action_engine::UmrfGraphDiff> FbtoRos(const flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff>>* src)
{
  std::vector<temoto_action_engine::UmrfGraphDiff> dst;
  dst.reserve(src->size());
  typedef flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff>> fvec;
  for (fvec::const_iterator it = src->begin(); it != src->end(); ++it)
  {
    dst.push_back(FbtoRos(*it));
  }

  return dst;
  
}

flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff>>> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const std::vector<temoto_action_engine::UmrfGraphDiff>& src)
{
  std::vector<flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff>> dst(src.size());
  std::transform(
      src.begin(), src.end(), dst.begin(), [&fbb](const temoto_action_engine::UmrfGraphDiff& item) {
        return RostoFb(fbb, item);
      });
  return fbb.CreateVector(dst).o;
}

flatbuffers::Offset<fb::temoto_action_engine::UmrfGraphDiff> RostoFb(flatbuffers::FlatBufferBuilder& fbb, const temoto_action_engine::UmrfGraphDiff& msg)
{
  return fb::temoto_action_engine::CreateUmrfGraphDiff(fbb, 0,
				::RostoFb(fbb, msg.operation),
				::RostoFb(fbb, msg.umrf_json)).o;
}

namespace temoto_action_engine_robofleet {
    
  void UmrfGraphDiffPublishHandler::initialize(ros::NodeHandle& nh,
                                                 const std::string client_topic,
                                                 const bool latched)
  {
    pub_ = nh.advertise<MsgType>(client_topic,
                                 10,
                                 latched);
  }

  const UmrfGraphDiffPublishHandler::FbMsgType*
  UmrfGraphDiffPublishHandler::decode(const QByteArray& data)
  {
    const FbMsgType* root = 
      flatbuffers::GetRoot<FbMsgType>(data.data());

    return root;
  }
  
  void UmrfGraphDiffPublishHandler::publish(const QByteArray& data)
  {
    const FbMsgType* fb = decode(data);
    const MsgType msg = FbtoRos(fb);
    
    pub_.publish(msg);
  }

  PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::UmrfGraphDiffPublishHandler, robofleet_client::ROSPublishHandler)
  


  void UmrfGraphDiffSubscribeHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::UmrfGraphDiff", rbf_topic.c_str());
      };

    sub_ = nh.subscribe(client_topic, 10, &UmrfGraphDiffSubscribeHandler::callback, this);
  }


  void UmrfGraphDiffSubscribeHandler::initialize(ros::NodeHandle& nh,
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
        return fb::CreateMsgMetadataDirect(fbb, "temoto_action_engine::UmrfGraphDiff", rbf_topic.c_str());
      };

    sub_ = nh.subscribe(client_topic, 10, &UmrfGraphDiffSubscribeHandler::callback, this);
  }

  
  QByteArray UmrfGraphDiffSubscribeHandler::encodeWithMetadata(const MsgType& msg)
  {
    flatbuffers::FlatBufferBuilder fbb;

    // encode the metadata
    const MetaDataOffset metadata = encode_metadata_function_(fbb);

    const flatbuffers::uoffset_t root_offset =
          fb::temoto_action_engine::CreateUmrfGraphDiff(fbb,
                                              metadata,
				::RostoFb(fbb, msg.operation),
				::RostoFb(fbb, msg.umrf_json)).o;

    // encode the rest of the type
    fbb.Finish(flatbuffers::Offset<void>(root_offset));
    const QByteArray data{reinterpret_cast<const char*>(fbb.GetBufferPointer()),
                          static_cast<int>(fbb.GetSize())};

    return data;
  }
  

  void UmrfGraphDiffSubscribeHandler::callback(const MsgTypeConstPtr& msg)
  {
    const QByteArray data = encodeWithMetadata(*msg);
    schedule_function_(data);
  }
} // namespace temoto_action_engine_robofleet

PLUGINLIB_EXPORT_CLASS(temoto_action_engine_robofleet::UmrfGraphDiffSubscribeHandler, robofleet_client::ROSSubscribeHandler)