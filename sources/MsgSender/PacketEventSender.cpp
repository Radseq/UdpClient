#include "../../headers/MsgSender/PacketEventSender.hpp"

void PacketEventSender::Start( )
{
	m_Working = true;

	m_SenderThread.reset (new std::thread (&PacketEventSender::ProcessShedule, this));  // start the thread }
}

void PacketEventSender::Stop( )
{
	std::cout << "End Sender thread"
			  << "\n";
	m_Working = false;        // inform the thread of termination
	m_SenderThread->join( );  // wait for thread termination
	m_SenderThread.reset (NULL);
	ClearSend( );
}

void PacketEventSender::SendMsg( )
{
	for (const auto& msg : msgTypeWithData)
	{
		const size_t vectorDataSize = msg.second.size( ) - 1;

		std::copy_n (std::make_move_iterator (msg.second.begin( )), vectorDataSize, msgPacket.data.begin( ));
	}

	// msgPacket.size = 0;

	assert (m_ClientSend.udpIp4Sender);
	auto resultValue = m_ClientSend.udpIp4Sender->Send<Packet> (&msgPacket);
	assert (resultValue > 0);

	// what if new collection of  msgTypeWithData will be set before send???? (look at tickrate, every ~8 ms is send
	// specyfic collection what if collection wont send ???) todo solve hmm udp dont care that data was send or no, if
	// so, use TCP...

	ClearSend( );
}

void PacketEventSender::ProcessShedule( )
{
	while (m_Working)
	{
		if (msgTypeWithData.size( ) > 0) SendMsg( );
		std::this_thread::sleep_for (FpMilliseconds (m_Tickrate));
	}
}

void PacketEventSender::Send (const std::vector<unsigned char>& data)
{
	MsgInterface::MsgType msgType = static_cast<MsgInterface::MsgType> (data.at (0));

	if (!ReplacedExistsPackage (msgType, data)) { AddToMsgTypeDataPair (msgType, data); }
}

bool PacketEventSender::ReplacedExistsPackage (const MsgInterface::MsgType& msgType, const vecMsg& data)
{
	// pos 0: packet 1
	// pos 1: packet 2
	// pos 2: packet 1 -- this will be never of pos 0, so replace.

	for (auto&& msg : msgTypeWithData)
	{
		if (msg.first == msgType)
		{
			msg.second = data;
			return true;
		}
	}

	return false;
}

void PacketEventSender::AddToMsgTypeDataPair (const MsgInterface::MsgType& msgType, const vecMsg& data)
{
	m_SizeOfMsgToSend += data.size( );

	if (m_SizeOfMsgToSend <= MsgInterface::MAX_MSG_SIZE) msgTypeWithData.push_back ({msgType, data});
}
void PacketEventSender::ClearSend( )
{
	msgTypeWithData.clear( );
	m_SizeOfMsgToSend = 0;

	msgPacket.data.fill ('\0');
}