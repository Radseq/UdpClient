#include "../../headers/MsgReader/MsgReaderFactory.hpp"

Core::Scope<PacketEventReader> MsgReaderFactory::CreatePacketEventReader (const ClientReceiveModel& Receive)
{
	return Core::CreateScope<PacketEventReader> (Receive);
}