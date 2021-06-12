#ifndef IPACKET_EVENT_SENDER_HPP
#define IPACKET_EVENT_SENDER_HPP

#include "../ReadDataModel.hpp"
#include "../pch.hpp"

class IPacketEventSender
{
   public:
	virtual ~IPacketEventSender( ) { }
	virtual void Start( )                                      = 0;
	virtual void Stop( )                                       = 0;
	virtual void Send (const std::vector<unsigned char>& data) = 0;
};

#endif  // IPACKET_EVENT_SENDER_HPP