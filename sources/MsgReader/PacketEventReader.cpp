#include "../../headers/MsgReader/PacketEventReader.hpp"

void PacketEventReader::Start( )
{
	m_Working = true;

	m_SenderThread.reset (new std::thread (&PacketEventReader::ProcessShedule, this));  // start the thread
}

void PacketEventReader::Stop( )
{
	std::cout << "End Reader thread"
			  << "\n";
	m_Working = false;        // inform the thread of termination
	m_SenderThread->join( );  // wait for thread termination
	m_SenderThread.reset (NULL);
}

void PacketEventReader::ProcessShedule( )
{
	while (m_Working)
	{
		std::this_thread::sleep_for (FpMilliseconds (m_Tickrate));
		ReadMsg( );
	}
}

Core::Ref<ReadDataModel> PacketEventReader::Read( )
{
	std::lock_guard<std::mutex> guard (m_Mutex);
	return readData;
}

void PacketEventReader::ReadMsg( )
{
	std::lock_guard<std::mutex> guard (m_Mutex);
	readData         = Core::CreateRef<ReadDataModel>( );
	readData->packet = Core::CreateRef<Packet>( );

	assert (m_Receive.udpIp4Receive);
	readData->packet = m_Receive.udpIp4Receive->Receive<Packet> (m_MsgReturnedCode);
	assert (*m_MsgReturnedCode > 0);

	if (readData->packet) readData->valid = true;
}