#ifndef MSG_SEND_ABSTRACT_FACTORY_HPP
#define MSG_SEND_ABSTRACT_FACTORY_HPP

#include "../ClientSenderModel.hpp"
#include "../pch.hpp"
#include "PacketEventSender.hpp"

class MsgSendAbstractFactory
{
   public:
	virtual ~MsgSendAbstractFactory( ) { }

	virtual Core::Scope<PacketEventSender> CreatePacketEventSender (const ClientSenderModel& Sender) = 0;
};

#endif  // MSG_SEND_ABSTRACT_FACTORY_HPP