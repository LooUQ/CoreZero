#pragma once


namespace iotq
{
	namespace TCTobjects
	{		
		class CTString
		{
		//
		//	Constructor
		//
		public:
			template<unsigned int N>
			constexpr CTString(const char(&staticString)[N])
				: m_pString(staticString)
				, m_Length(N - 1)
			{}
		//
		//	Methods
		//
		public:
			constexpr const char* c_str() const
			{ return m_pString; }
			constexpr unsigned int GetLength() const
			{ return m_Length; }

		//
		//	Attributes
		//
		private:
			/// Length of the string (not including null-terminator)
			unsigned int m_Length;

			/// Pointer to the static string
			const char * m_pString;
		};
	}
}