#ifndef READ_DATA_MODEL_HPP
#define READ_DATA_MODEL_HPP

#include "../InternalLib/MessageInterface/src/Packet.hpp"
#include "pch.hpp"

class ReadDataModel
{
   public:
	bool                valid {false};
	Core::Ref<Packet> packet = Core::CreateRef<Packet>( );
	// uint32_t                   sizeReceivedMsg {0};
	// std::vector<unsigned char> msgReceiveArray;
};

#endif  // READ_DATA_MODEL_HPP