#ifndef ICLIENT_NET_MANAGER_HPP
#define ICLIENT_NET_MANAGER_HPP

#include "ReadDataModel.hpp"
#include "pch.hpp"

class IClientNetManager
{
   public:
	virtual ~IClientNetManager( ) { }

	virtual Core::Ref<ReadDataModel> Recv( )                                               = 0;
	virtual void                     Connect (const std::string_view& Ip, const int& Port) = 0;
	virtual void                     Send (const std::vector<unsigned char>& Data)         = 0;
};
#endif  // ICLIENT_NET_MANAGER_HPP