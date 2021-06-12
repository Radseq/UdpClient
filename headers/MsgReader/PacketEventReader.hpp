#ifndef PACKET_EVENT_READER_HPP
#define PACKET_EVENT_READER_HPP

#include <mutex>

#include "../../InternalLib/MessageInterface/src/Packet.hpp"
#include "../../InternalLib/NetCode/Headers/UDP_IP4/ClientUdpIp4Receive.hpp"
#include "../ClientReceiveModel.hpp"
#include "IPacketEventReader.hpp"

class PacketEventReader : public IPacketEventReader
{
	bool                         m_Working {false};
	int*                         m_MsgReturnedCode = new int (-1);
	std::mutex                   m_Mutex;
	std::unique_ptr<std::thread> m_SenderThread;

	const ClientReceiveModel& m_Receive;
	Core::Ref<ReadDataModel>  readData = Core::CreateRef<ReadDataModel>( );

	float m_Tickrate {1000 / 128};
	using FpMilliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;

	void ReadMsg( );
	void ProcessShedule( );

   public:
	PacketEventReader (const ClientReceiveModel& Receive)
		: m_Receive (Receive)
	{
	}

	~PacketEventReader( ) { Stop( ); };

	void                     Start( ) override;
	void                     Stop( ) override;
	Core::Ref<ReadDataModel> Read( ) override;
};

#endif  // PACKET_EVENT_READER_HPP