#ifndef THREAD_RAII_HPP
#define THREAD_RAII_HPP

#include <thread>

#include "pch.hpp"

class ThreadRaii
{
	std::thread& threadRaii;

   public:
	ThreadRaii (std::thread& th)
		: threadRaii (th)
	{
	}

	~ThreadRaii( )
	{
		if (threadRaii.joinable( )) { threadRaii.join( ); }
	}

	// copy constructor
	ThreadRaii (const ThreadRaii& thr);

	// copy-assignment operator
	ThreadRaii& operator= (const ThreadRaii& thr);
};

#endif  // THREAD_RAII_HPP