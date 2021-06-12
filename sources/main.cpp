
#include <string.h>

#include "../headers/pch.hpp"

#define SERWER_PORT 8888
#define SERWER_IP   "127.0.0.1"

#include "../headers/ClientNetManager.hpp"
#include "../headers/IClientNetManager.hpp"

int main( )
{
	IClientNetManager* clientNetCode;

	ClientNetManager clientNet { };
	clientNetCode = &clientNet;

	clientNetCode->Connect (SERWER_IP, SERWER_PORT);

	MovePacket mp;
	mp.entity = 1;
	mp.x      = 1.3;
	mp.y      = 2.4;
	mp.z      = 5.2;

	SayPacket sp;
	sp.entity = 1;
	std::fill (std::begin (sp.text), std::end (sp.text), 0);  // clear array from trash
	strcpy (sp.text, "Hello!");

	SayPacket sp2;
	sp2.entity = 1;
	std::fill (std::begin (sp2.text), std::end (sp2.text), 0);  // clear array from trash
	strcpy (sp2.text, "Hello There!");
	/*
		std::cout << "Client Send:" << std::endl;

		std::cout << "mp.entity:" << mp.entity << std::endl;
		std::cout << "mp.type:" << PrintMsgType (mp.type) << std::endl;
		std::cout << "mp.x:" << mp.x << std::endl;
		std::cout << "mp.y:" << mp.y << std::endl;
		std::cout << "mp.z:" << mp.z << std::endl;*/

	// sender->Start( );
	// reader->Start( );
	/*
	Packet packet;
	packet.data     = MsgInterface::VarToBytes (mp);
	packet.dataSize = sizeof (packet.data);
	packet.flag     = 1;
	packet.packetId = 1;
	auto a          = MsgInterface::VarToBytes (packet);

	Packet sadweasd;

	MsgInterface::BytesToVar (a, sadweasd);

	MovePacket sad;
	MsgInterface::BytesToVar (packet.data, sad);*/

	/*
		sender->Send (MsgInterface::VarToBytes (sp));
		sender->Send (MsgInterface::VarToBytes (mp));
		sender->Send (MsgInterface::VarToBytes (sp2));
	*/

	using FpMilliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;

	PingPacket pp;
	pp.ping = 0;

	while (1)
	{
		std::this_thread::sleep_for (FpMilliseconds (1000 / 128));
		pp.ping += 1;

		clientNetCode->Send (MsgInterface::VarToBytes (pp));

		Core::Ref<ReadDataModel> readMsgData = clientNetCode->Recv( );

		if (readMsgData && readMsgData->valid)
		{
			std::vector<unsigned char> vectorMessage;

			for (size_t i = 0; i <= readMsgData->packet->data.size( ); ++i)
			{
				MsgInterface::MsgType msgType = static_cast<MsgInterface::MsgType> (readMsgData->packet->data.at (0));
				size_t                sizeOfPackage = MsgInterface::GetSizeOfPackageByMsgType (msgType);

				for (size_t y = 0; y < sizeOfPackage; ++y)
				{
					vectorMessage.push_back (readMsgData->packet->data.at (y));
				}
				break;  // for now, untill i write correct get message impl.
			}
			PingPacket receiveMovePacage;

			MsgInterface::BytesToVar (vectorMessage, receiveMovePacage);

			// DONT LOOK AT THIS SHIT, ITS TEST ONLY....

			std::cout << "Server Send: " << std::endl;
			std::cout << "ping: " << receiveMovePacage.ping << std::endl;
		}

		readMsgData.reset( );
	}
	// sender->Stop( );
	// reader->Stop( );
}
