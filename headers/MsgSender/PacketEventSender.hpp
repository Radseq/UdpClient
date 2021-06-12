#ifndef PACKET_EVENT_SENDER_HPP
#define PACKET_EVENT_SENDER_HPP

#include "../../InternalLib/MessageInterface/src/Packet.hpp"
#include "../../InternalLib/NetCode/Headers/UDP_IP4/ClientUdpIp4Send.hpp"
#include "../ClientSenderModel.hpp"
#include "IPacketEventSender.hpp"

typedef std::vector<unsigned char> vecMsg;

class PacketEventSender : public IPacketEventSender
{
	// Message type with vector of bytes (unsigned char), used to determine packages that already listed for sending
	std::vector<std::pair<MsgInterface::MsgType, vecMsg>> msgTypeWithData;

	using FpMilliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;
	float m_Tickrate {1000 / 128};

	bool   m_Working {false};
	size_t m_SizeOfMsgToSend {0};

	std::unique_ptr<std::thread> m_SenderThread;
	const ClientSenderModel&     m_ClientSend;
	Packet                       msgPacket;

	void SendMsg( );
	void ProcessShedule( );

	bool ReplacedExistsPackage (const MsgInterface::MsgType& msgType, const vecMsg& data);
	void AddToMsgTypeDataPair (const MsgInterface::MsgType& msgType, const vecMsg& data);
	void ClearSend( );

   public:
	PacketEventSender (const ClientSenderModel& ClientSend)
		: m_ClientSend (ClientSend) { };

	~PacketEventSender( ) { Stop( ); };

	void Start( ) override;
	void Stop( ) override;

	void Send (const vecMsg& data) override;
};

#endif  // PACKET_EVENT_SENDER_HPP