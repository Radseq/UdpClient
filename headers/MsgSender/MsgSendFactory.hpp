#ifndef MSG_SEND_FACTORY_HPP
#define MSG_SEND_FACTORY_HPP

#include "MsgSendAbstractFactory.hpp"

class MsgSendFactory : public MsgSendAbstractFactory
{
   public:
	Core::Scope<PacketEventSender> CreatePacketEventSender (const ClientSenderModel& Sender) override;
};

#endif  // MSG_SEND_FACTORY_HPP