#ifndef CLIENT_SENDER_MODEL_HPP
#define CLIENT_SENDER_MODEL_HPP

#include "../InternalLib/NetCode/Headers/UDP_IP4/ClientUdpIp4Send.hpp"
#include "pch.hpp"

class ClientSenderModel
{
   public:
	Core::Ref<ClientUdpIp4Send> udpIp4Sender;
	// Core::Ref<ClientUdpIp6Send> udpIp6Sender;
	// .... more
};

#endif  // CLIENT_SENDER_MODEL_HPP