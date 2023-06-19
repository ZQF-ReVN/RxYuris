#pragma once
#include <cstdint>
#include <string>

#include "File.h"

//Ria's Utility Library X
namespace Rut
{
	namespace MemX
	{
		class AutoMem
		{
		private:
			size_t m_szData;
			uint8_t* m_pData;

		public:
			AutoMem();
			AutoMem(const AutoMem& buffer);
			AutoMem(AutoMem&& buffer) noexcept;
			AutoMem(const std::wstring& wsFile);
			AutoMem(const std::wstring& wsFile, size_t szFile);
			~AutoMem();

			template <typename T_Ptr>
			operator T_Ptr* () { return (T_Ptr*)m_pData; }

			template <typename T_Type>
			operator T_Type () { return (T_Type)m_szData; }

			template <typename T_Size>
			AutoMem& operator[] (T_Size tSize) { ReSize(tSize); return *this; }

			uint8_t* ReSize(size_t szRes);
			size_t GetSize() { return m_szData; }
			uint8_t* GetPtr() { return m_pData; }

			uint8_t* LoadFileViaSize(const std::wstring& wsFile, size_t szFile = -1);
			void     SaveDataToFile(const std::wstring& wsFile);
		};
	}
}