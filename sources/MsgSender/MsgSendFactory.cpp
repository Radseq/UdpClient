#include "../../headers/MsgSender/MsgSendFactory.hpp"

Core::Scope<PacketEventSender> MsgSendFactory::CreatePacketEventSender (const ClientSenderModel& Sender)
{
	return Core::CreateScope<PacketEventSender> (Sender);
}