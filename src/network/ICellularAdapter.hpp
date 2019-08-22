/******************************************************************************
*	@file	ICellularAdapter
*
*	@author		Jensen Miller
*	@date		Jul 13, 2018
*	@copyright	LooUQ Inc 2018
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

#ifndef IOTQC_ICELLULADAPTER_H
#define IOTQC_ICELLULADATER_H

#include <stdlib.h>
#include "NetworkAdapter.hpp"

namespace iotq
{
	namespace network
	{
		namespace cellular
		{
			class ICellularAdapter;

			/// The version of network IP addressing.
			typedef enum {
				NOIPSUPPORT,	///< Not a valid IP option
				IPV4,		///< IP version 4
				IPV4V6		///< IP version 4 with 6 support
			} wwan_network_IPkind;

			/// The authentication option.
			typedef enum {
				NONE,		///< No authentication used
				PAP,		///< PAP authentication
				CHAP,		///< CHAP authentication
				PAPorCHAP	///< Use either PAP or CHAP
			} authentication_type;

			/// The data service provided by wwan connection
			typedef enum {
				GSM = 0,
				LTE_CAT_M1 = 8,
				LTE_CAT_NB1 = 9
			} wwan_data_class;

			/**
			 *	@typedef A structure detailing a cellular apn context.
			 */
			typedef struct
			{
				//property string AccessPointName;
				const char* AccessPointName = "";

				//property authentication_type AuthenticationType;
				authentication_type AuthenticationType = NONE;

				//property string Password;
				const char* Password = "";

				//property wwan_network_IPkind ContextType;
				wwan_network_IPkind ContextType = NOIPSUPPORT;

				//property string ProviderId;
				const char* ProviderId = "";

				//property string UserName;
				const char* UserName = "";

				//property byte PdpIndex;
				uint8_t PdpIndex = 0;
			} cellular_apn_context;

			typedef struct
			{
				wwan_data_class WwanDataClass = LTE_CAT_M1;
				cellular_apn_context CellularApnContext;
				const char* ProfileName = "";
				ICellularAdapter * CellularAdapter = nullptr;
				INetworkAdapter * NetworkAdapter = nullptr;
			} wwan_connection_profile;


			struct connection_session
			{
				connection_session(ICellularAdapter * cellularAdapter) : m_cellularAdapter(cellularAdapter) {}
				connection_session() : m_isConnected(false) {}
				wwan_connection_profile ConnectionProfile;
				void Close() {}
				bool IsConnected() { return m_isConnected; }

			protected:
				friend ICellularAdapter;
				void SetCellularAdapter(ICellularAdapter * cellularAdapter) { m_cellularAdapter = cellularAdapter; }

			private:
				///	The cellular adapter that created this session
				ICellularAdapter * m_cellularAdapter = nullptr;

				/// Whether the connection session is connected. True upon instantiation
				///		given that it is connected upon creation.
				bool m_isConnected = true;
			};
			

			class ICellularAdapter
			{
			public:
				virtual connection_session	AquireConnection(int pdpIndex, const cellular_apn_context &pdpContext) = 0;
				virtual const connection_session&	GetDefaultSession() = 0;
				virtual const char* GetImei() = 0;
				virtual const char* GetIccid() = 0;
			};
		}
	}
}
#endif // !IOTQC_ICELLULADAPTER_H
