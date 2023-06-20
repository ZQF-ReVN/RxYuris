#pragma once
#include <string>

#include "../Rxx/Mem.h"


namespace YurisLibrary
{
	namespace YSCOM
	{
		class YSCOM_Loader
		{
		private:
			uint32_t m_uiScriptCount;
			Rut::MemX::AutoMem m_amBin;

		public:
			YSCOM_Loader();

			void Compile(uint32_t uiVersion);
			void Extract(uint32_t uiXorKey);
		};
	}
}