// Copyright (c) 2018 LooUQ Inc. All rights reserved.

// Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "Thread.h"

#if defined(ARDUINO)
#include <Arduino.h>
#include <core_cmFunc.h>

uint32_t g_PendingThreads = 0;

struct _thread
{
	unsigned tid;
	iotq::utilities::VoidFunctor<>* callable;
} *g_LocalThread;

thread_local _thread* th_ThisThread = nullptr;

void PendSV_Configure(unsigned priority)
{
	unsigned system_priority;
	__disable_irq();

	system_priority = NVIC_GetPendingIRQ(IRQn::PendSV_IRQn);
	system_priority &= ~(0x3 << 22);
	system_priority |= (priority << 22);
	NVIC_SetPriority(IRQn_Type::PendSV_IRQn, system_priority);

	__DSB();
	__ISB();
	__enable_irq();

	return;
}

void PendSV_Set()
{
	__DSB();
	__ISB();
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void PendSV_Clear()
{
	SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk;
}

void PendSV_Handler(void)
{
	// DO...
	if (g_LocalThread)
	{		
		th_ThisThread = g_LocalThread, g_LocalThread = nullptr;
		(*(th_ThisThread->callable))();
		g_PendingThreads &= ~(1ul << th_ThisThread->tid);
		th_ThisThread = nullptr;
	}

	// Clear PendSV on return
	return PendSV_Clear();
}

namespace iotq
{
	namespace threading
	{
		Thread::Thread(utilities::VoidFunctor<>* callable)
			: m_tid(0x1)
		{			
			g_LocalThread = new _thread{ m_tid, callable };
			g_PendingThreads |= (1ul << m_tid);
			PendSV_Set();
		}

		Thread::Thread(void(*voidFunction)(void))
			: m_tid(0x1)
		{
			g_LocalThread = new _thread{ m_tid, new utilities::VoidFunctor<>(voidFunction) };
			PendSV_Set();
		}



		Thread::~Thread()
		{
			g_PendingThreads &= ~(1ul << m_tid);
		}


		void Thread::Join()
		{			
			while (g_PendingThreads & (1ul << m_tid))
				;
		}



		void Thread::Detach()
		{
			g_PendingThreads &= ~(1ul << m_tid);
			m_IsDetached = true;
		}


		void this_thread::yield()
		{

		}



		void this_thread::sleep_for(unsigned long milli_s)
		{
			delay(milli_s);
		}
	}
}

#else

#include <thread>
#include <chrono>

namespace iotq
{
	namespace threading
	{
		Thread::Thread(void(*voidFunction)(void))
		{
		}

		Thread::~Thread()
		{

		}


		void Thread::Join()
		{
		}


		void Thread::Detach()
		{
		}



		void this_thread::yield() noexcept
		{
			std::this_thread::yield();
		}



		void this_thread::sleep_for(unsigned long milli_s)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(milli_s));
		}
	}
}

#endif