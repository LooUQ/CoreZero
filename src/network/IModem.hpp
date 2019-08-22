/******************************************************************************
*	@file		IModem.h
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

#ifndef IOTQC_IMODEM_H
#define IOTQC_IMODEM_H


namespace iotq
{
	namespace devices
	{
		struct IModem
		{
			//property string ManufacturerId;
			virtual const char* GetManufacturerId() = 0;

			//property string ModelId;
			virtual const char* GetModelId() = 0;

			//property string FirmwareVersion;
			virtual const char* GetFirmwareVersion() = 0;

			//property string SerialNumber;
			virtual const char* GetSerialNumber() = 0;
		};
	}
}

#endif // !IOTQC_IMODEM_H
