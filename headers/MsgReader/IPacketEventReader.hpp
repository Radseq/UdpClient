#ifndef IPACKET_EVENT_READER_HPP
#define IPACKET_EVENT_READER_HPP

#include "../ReadDataModel.hpp"
#include "../pch.hpp"

class IPacketEventReader
{
   public:
	virtual ~IPacketEventReader( ) { }
	virtual void                     Start( ) = 0;
	virtual void                     Stop( )  = 0;
	virtual Core::Ref<ReadDataModel> Read( )  = 0;
};

#endif  // IPACKET_EVENT_READER_HPP