#include "Mem_Auto.h"

using namespace Rut::FileX;


namespace Rut
{
	namespace MemX
	{
		AutoMem::AutoMem() : m_pData(nullptr), m_szData(0)
		{

		}

		AutoMem::AutoMem(const AutoMem& buffer)
		{
			if (buffer.m_pData != nullptr)
			{
				this->m_szData = buffer.m_szData;
				this->m_pData = new uint8_t[buffer.m_szData];
				memcpy(m_pData, buffer.m_pData, m_szData);
			}
			else
			{
				this->m_pData = nullptr;
				this->m_szData = 0;
			}
		}

		AutoMem::AutoMem(AutoMem&& buffer) noexcept
		{
			this->m_pData = buffer.m_pData;
			this->m_szData = buffer.m_szData;

			buffer.m_pData = nullptr;
			buffer.m_szData = 0;
		}

		AutoMem::AutoMem(const std::wstring& wsFile) : m_pData(nullptr), m_szData(0)
		{
			LoadFileViaSize(wsFile);
		}

		AutoMem::AutoMem(const std::wstring& wsFile, size_t szFile) : m_pData(nullptr), m_szData(0)
		{
			LoadFileViaSize(wsFile, szFile);
		}

		AutoMem::~AutoMem()
		{
			m_szData = 0;
			if (m_pData) { delete[] m_pData; }
			m_pData = nullptr;
		}

		uint8_t* AutoMem::ReSize(size_t szRes)
		{
			if (!m_szData)
			{
				m_pData = new uint8_t[szRes];
				m_szData = szRes;
			}

			if (szRes > m_szData)
			{
				delete[] m_pData;
				m_pData = new uint8_t[szRes];
				m_szData = szRes;
			}

			return m_pData;
		}

		uint8_t* AutoMem::LoadFileViaSize(const std::wstring& wsFile, size_t szFile)
		{
			std::ifstream ifs = OpenFileBinaryStream(wsFile);
			if (szFile == -1) { szFile = static_cast<size_t>(GetFileSize(ifs)); }

			ifs.read((char*)ReSize(szFile), szFile);
			return m_pData;
		}

		void AutoMem::SaveDataToFile(const std::wstring& wsFile)
		{
			std::ofstream ofs = CreateFileBinaryStream(wsFile);
			ofs.write((char*)m_pData, m_szData);
			ofs.flush();
		}
	}
}