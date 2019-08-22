/******************************************************************************
*	Author: Jensen Miller
*	Date:	May 14, 2018
*	Company:	LooUQ Inc
*
*	Description:	A messaging queue derived from a basic queue. Meant to
*		support basic messaging logic.
*
*	License:
*		The GNU Licence(GNU)
*
*	This file is part of the iotq library.
*
*	IotQc is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	IotQc is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with iotq.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
#pragma once

#ifndef IOTQC_MESSAGING_QUEUE_H
#define IOTQC_MESSAGING_QUEUE_H

#include <string.h>

#include "Queue.h"

namespace iotq
{
	namespace utilities
	{
		template<class M>
		void FindMessage(M& message, const char* lookingFor)
		{
			strstr(message.c_str(), lookingFor);
		}
	}

	namespace containers
	{
		/**
		 *	@class MessagingQueue MessagingQueue.h "src/containers/MessagingQueue.h"
		 *	@brief A container to queue messages.
		 *	@details This queue inherits a generic templated queue.
		 */
		template<class T, size_t N=8>
		class MessagingQueue : private CQueue<T,N>
		{
		public:
			MessagingQueue();
			virtual	~MessagingQueue();

		public:
			void	PushMessage(const T& message);
			void	PopMessage();
			T&		AcknowledgeMessage();
			
			bool	IsEmpty();
			bool	IsFull();
			size_t	GetSize();
			size_t	GetCapacity();
		private:
			TArray<bool, N> m_PendingMessages;
			size_t m_Position = 0;
		};

		template<class T, size_t N>
		MessagingQueue<T, N>::MessagingQueue()
		{
			m_PendingMessages.Fill(false);
		}

		template<class T, size_t N>
		MessagingQueue<T, N>::~MessagingQueue()
		{}

		template<class T, size_t N>
		void MessagingQueue<T, N>::PushMessage(const T& message)
		{
			if (CQueue<T, N>::Full() || m_PendingMessages[m_Position])
				return;
			m_PendingMessages[m_Position] = true;
			CQueue<T, N>::Push(message);
			++m_Position %= N;
		}

		template<class T, size_t N>
		void MessagingQueue<T, N>::PopMessage()
		{
			CQueue<T, N>::Pop();
		}

		template<class T, size_t N>
		inline T & MessagingQueue<T, N>::AcknowledgeMessage()
		{
			if (m_PendingMessages[index])
			{
				m_PendingMessages[index] = false;
			}
		}

		template<class T, size_t N>
		inline bool MessagingQueue<T, N>::IsEmpty()
		{
			return false;
		}

		template<class T, size_t N>
		inline bool MessagingQueue<T, N>::IsFull()
		{
			return false;
		}

		template<class T, size_t N>
		inline size_t MessagingQueue<T, N>::GetSize()
		{
			return size_t();
		}

		template<class T, size_t N>
		inline size_t MessagingQueue<T, N>::GetCapacity()
		{
			return size_t();
		}
	}
}

#endif // !IOTQC_MESSAGING_QUEUE_H
