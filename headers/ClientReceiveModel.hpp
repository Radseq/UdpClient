#ifndef CLIENT_RECEIVE_MODEL_HPP
#define CLIENT_RECEIVE_MODEL_HPP

#include "../InternalLib/NetCode/Headers/UDP_IP4/ClientUdpIp4Receive.hpp"
#include "pch.hpp"

class ClientReceiveModel
{
   public:
	Core::Ref<ClientUdpIp4Receive> udpIp4Receive;
	// Core::Ref<ClientUdpIp6Receive> udpIp6Receive;
	// .... more
};

#endif  // CLIENT_RECEIVE_MODEL_HPP