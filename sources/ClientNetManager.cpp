#include "../headers/ClientNetManager.hpp"

Core::Ref<ReadDataModel> ClientNetManager::Recv( ) { return m_Reader->Read( ); }

void ClientNetManager::Connect (const std::string_view& Ip, const int& Port)
{
	m_UdpIp4Address = m_UdpAdrFactory->CreateUdpIp4( );
	m_UdpIp4Address->Create (Ip, Port);

	clientSocket->Create( );
	m_ClientSocketNum = clientSocket->GetId( );

	CreateSender( );
	CreateReceiver( );
}

void ClientNetManager::Send (const std::vector<unsigned char>& Data) { m_Sender->Send (Data); }

ClientNetManager::~ClientNetManager( )
{
	m_Reader->Stop( );
	m_Sender->Stop( );
}

void ClientNetManager::CreateSender( )
{
	m_MsgSendFactory         = Core::CreateRef<MsgSendFactory>( );
	m_ClientSend             = Core::CreateScope<ClientUdpIp4Send> (m_UdpIp4Address, m_ClientSocketNum);
	senderModel.udpIp4Sender = m_ClientSend;
	m_Sender                 = m_MsgSendFactory->CreatePacketEventSender (senderModel);
	m_Sender->Start( );
}

void ClientNetManager::CreateReceiver( )
{
	m_ClientReceive            = Core::CreateRef<ClientUdpIp4Receive> (m_ClientSocketNum);
	m_MsgReaderFactory         = Core::CreateRef<MsgReaderFactory>( );
	receiveModel.udpIp4Receive = m_ClientReceive;
	m_Reader                   = m_MsgReaderFactory->CreatePacketEventReader (receiveModel);
	m_Reader->Start( );
}