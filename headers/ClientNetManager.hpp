#ifndef CLIENT_NET_MANAGER_HPP
#define CLIENT_NET_MANAGER_HPP

#include "../InternalLib/MessageInterface/src/MessageInterface.hpp"
#include "../InternalLib/MessageInterface/src/MovePacket.hpp"
#include "../InternalLib/MessageInterface/src/Packet.hpp"
#include "../InternalLib/MessageInterface/src/PingPacket.hpp"
#include "../InternalLib/MessageInterface/src/SayPacket.hpp"
#include "../InternalLib/NetCode/Headers/CreateSocket.hpp"
#include "../InternalLib/NetCode/Headers/CreateUdpAbstractFactory.hpp"
#include "../InternalLib/NetCode/Headers/ICreateSocket.hpp"
#include "../InternalLib/NetCode/Headers/UDP_IP4/ClientUdpIp4Send.hpp"
#include "../InternalLib/NetCode/Headers/UdpAdrAbstractFactory.hpp"
#include "../headers/ClientReceiveModel.hpp"
#include "../headers/ClientSenderModel.hpp"
#include "../headers/MsgReader/MsgReaderAbstractFactory.hpp"
#include "../headers/MsgReader/MsgReaderFactory.hpp"
#include "../headers/MsgSender/MsgSendAbstractFactory.hpp"
#include "../headers/MsgSender/MsgSendFactory.hpp"
#include "ClientReceiveModel.hpp"
#include "ClientSenderModel.hpp"
#include "IClientNetManager.hpp"

class ClientNetManager : public IClientNetManager
{
	ClientReceiveModel receiveModel;
	ClientSenderModel  senderModel;
	int                m_ClientSocketNum {0};

	Core::Scope<ICreateSocket> clientSocket = Core::CreateScope<CreateSocket>( );

	Core::Scope<UdpAdrAbstractFactory> m_UdpAdrFactory = Core::CreateScope<CreateUdpAbstractFactory>( );
	Core::Scope<IUDP_IP4_Address>      m_UdpIp4Address;

	Core::Ref<MsgReaderAbstractFactory> m_MsgReaderFactory = Core::CreateRef<MsgReaderFactory>( );
	Core::Ref<ClientUdpIp4Receive>      m_ClientReceive;
	Core::Scope<PacketEventReader>      m_Reader;

	Core::Ref<ClientUdpIp4Send>       m_ClientSend;
	Core::Ref<MsgSendAbstractFactory> m_MsgSendFactory;
	Core::Scope<PacketEventSender>    m_Sender;

	void CreateSender( );
	void CreateReceiver( );

   public:
	~ClientNetManager( );

	Core::Ref<ReadDataModel> Recv( );
	void                     Connect (const std::string_view& Ip, const int& Port);
	void                     Send (const std::vector<unsigned char>& Data);
};
#endif  // CLIENT_NET_MANAGER_HPP