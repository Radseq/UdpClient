#ifndef MSG_READER_FACTORY_HPP
#define MSG_READER_FACTORY_HPP

#include "MsgReaderAbstractFactory.hpp"

class MsgReaderFactory : public MsgReaderAbstractFactory
{
   public:
	Core::Scope<PacketEventReader> CreatePacketEventReader (const ClientReceiveModel& Receive) override;
};

#endif  // MSG_READER_FACTORY_HPP