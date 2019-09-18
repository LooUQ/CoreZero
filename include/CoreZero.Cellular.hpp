#ifndef COREZERO_CELLULAR_H_
#define COREZERO_CELLULAR_H_


namespace CoreZero
{
	namespace Cellular
	{
		namespace LTE
		{
			/// 3GPP-LTE-IoT
			typedef enum
			{
				eMTC,
				NB_IoT,
				EC_GSM_IoT
			} IoT_Network;
		}
		
		namespace Gen5 {}
	}
}

#endif	// !COREZERO_CELLULAR_H_