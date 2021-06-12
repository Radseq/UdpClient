#ifndef MSG_READER_ABSTRACT_FACTORY_HPP
#define MSG_READER_ABSTRACT_FACTORY_HPP

#include "../ClientReceiveModel.hpp"
#include "../pch.hpp"
#include "PacketEventReader.hpp"

class MsgReaderAbstractFactory
{
   public:
	virtual ~MsgReaderAbstractFactory( ) { }

	virtual Core::Scope<PacketEventReader> CreatePacketEventReader (const ClientReceiveModel& Receive) = 0;
};

#endif  // MSG_SEND_ABSTRACT_FACTORY_HPP