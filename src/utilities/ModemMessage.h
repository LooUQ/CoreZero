/******************************************************************************
*	@file
*
*	@author		Jensen Miller
*	@date		
*	@copyright  LooUQ Inc 2018
*
*	@details
*
*	License:
*		The GNU Licence(GNU)
*
*	This file is part of the iotq library.
*
*	IotQc is free software: you can redistribute it and/or modify it under
*	the terms of the GNU General Public License as published by the
*	Free Software Foundation, either version 3 of the License, or (at
*	your option) any later version.
*
*	IotQc is distributed in the hope that it will be useful, but WITHOUT
*	ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR
*	PURPOSE.  See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public
*	License along with iotq.
*	If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#pragma once

#ifndef IOTQC_MODEMMESSAGE_H
#define IOTQC_MODEMMESSAGE_H

#include "../containers/Vector.h"


namespace iotq
{
	namespace devices
	{
		namespace modems
		{
			class ModemMessage
			{
			public:
				typedef const char * ExpectedMessage;
				//
				//	Constructors
				//
			public:
				ModemMessage();
				virtual	~ModemMessage();


				//
				//	Methods
				//
			public:
				void TokenizeBy(const char* delimiter_s);
				void Detokenize(char subCh);
				bool LookFor(const char* subToken);
				void Reserve(size_t reservelen);
				void InvalidateMessage();
				const char* operator[](size_t line);
				const char* c_str()const;
				size_t		length() { return m_MessageSize; }
				char* data() { return m_FullMessage; }


				//
				//	Getters and Setters
				//
			public:
				const char* GetActualExpression();
				const char* GetNextExpression();
				const char* GetLastToken();
				size_t GetNumOfTokens();
				size_t GetFullMessage(char* message[]);
				void SetFullMessage(char* message[], size_t msgSz);


				//
				//	Attributes
				//
			private:
				/// A pointer to the full message
				char* m_FullMessage = nullptr;

				/// The size of the entire message
				size_t m_MessageSize = NULL;

				/// The partitioned expression found in the actual message
				size_t m_ActualExpression = 0;

				/// A vector of all tokens
				containers::Vector<const char*> m_Tokens;

				bool m_Tokenized = false;
			};


		}
	}
}


#endif // !IOTQC_MODEMMESSAGE_H

