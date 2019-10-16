/******************************************************************************
*	Cellular definitions.
*
*	\file	cellular_def.hpp
*	\author	Jensen Miller
*
*	Copyright (c) 2018 LooUQ Incorporated.
*
*	License: The GNU License
*
*	This file is part of the CoreZero library.
*
*	CoreZero is free software: you can redistribute it and/or modify it under
*	the terms of the GNU General Public License as published by the
*	Free Software Foundation, either version 3 of the License, or (at
*	your option) any later version.
*
*	CoreZero is distributed in the hope that it will be useful, but WITHOUT
*	ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR
*	PURPOSE.  See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public
*	License along with CoreZero.
*	If not, see <http://www.gnu.org/licenses/>.
*
******************************************************************************/
#ifndef COREZERO_CELLULARDEF_H_
#define COREZERO_CELLULARDEF_H_


namespace corezero
{
	namespace cellular
	{
		namespace LTE
		{
			/// 3GPP low power, wide area (LPWA) standards (1)
			enum class IotNetwork
			{
				eMTC,	///< Enhanced machine-type communications
				NBIot,	///< Narrow band
				EcGsmIot
			};
		}
		
		namespace NR_5G
		{
			///	5G New radio technologies (2)			
			enum class IoTNetwork
			{
				eMBB,	///< Enhanced mobile broadband
				URLLC	///< ultra-reliable, low-latency communication
//				mMTC	///< massive machine-type communication (not targeted yet)
			};
		}
	}
}


/*	Appendix
-----------------------------------------------------------------------------------------------------------------------

references:
	(1)	https://www.3gpp.org/news-events/3gpp-news/1805-iot_r14
	(2) https://www.qualcomm.com/news/onq/2017/06/15/lte-iot-starting-connect-massive-iot-today-thanks-emtc-and-nb-iot
*/

#endif	// !COREZERO_CELLULARDEF_H_