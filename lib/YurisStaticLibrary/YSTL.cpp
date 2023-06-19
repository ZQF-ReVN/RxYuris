#include "YSTL.h"
#include "../Rxx/Str.h"
#include "../Rxx/File.h"

#include <Windows.h>
#include <shlobj_core.h>
#include <shlwapi.h>
#include <fstream>


namespace YurisLibrary
{

	using namespace YSTL_Struct;
	using namespace Rut::StrX;
	using namespace Rut::FileX;

	YSTL::YSTL(std::wstring wsYSTL) :
		m_Header{ 0 },
		m_wsYSTL(wsYSTL)
	{
		m_ifsYSTL.open(m_wsYSTL, std::ios::binary);
		InitIndex();
	}

	YSTL::~YSTL()
	{
		if (m_ifsYSTL.is_open())
		{
			m_ifsYSTL.close();
		}
	}

	bool YSTL::InitIndex()
	{
		if (!m_ifsYSTL.is_open()) return false;

		char* pIndex = nullptr;
		m_ifsYSTL.read(reinterpret_cast<char*>(&m_Header), sizeof(m_Header));
		pIndex = new char[static_cast<size_t>(GetFileSize(m_ifsYSTL)) - sizeof(m_Header)];
		m_ifsYSTL.read(pIndex, GetFileSize(m_ifsYSTL) - sizeof(m_Header));

		char* pEntry = pIndex;
		YSTL_Struct::YSTLEntry_V5 Entry = { 0 };
		for (size_t iteEntry = 0; iteEntry < m_Header.uiEntryCount; iteEntry++)
		{
			Entry.uiSequence = *(unsigned int*)(pEntry + 0);
			Entry.szRelativePath = *(unsigned int*)(pEntry + 0x4);

			memcpy(Entry.aRelativePath, pEntry + 0x8, Entry.szRelativePath);
			Entry.aRelativePath[Entry.szRelativePath] = '\0';
			pEntry += Entry.szRelativePath + 0x8;

			memcpy(&Entry.uiHighDateTime, pEntry, sizeof(Entry) - sizeof(Entry.aRelativePath) - 8);
			pEntry += 20;

			m_vecEntry.emplace_back(Entry);
		}
		pEntry = nullptr;

		delete[] pIndex;
		pIndex = nullptr;

		return true;
	}

	bool YSTL::PrintIndexToFile()
	{
		std::wofstream woText(L"YSTList_Info.txt");
		woText.imbue(GetCVT_UTF8());
		if (!woText.is_open()) return false;

		std::string mPath;
		std::wstring wPath;
		wchar_t aYSTB[13] = { 0 };
		for (auto& iteEntry : m_vecEntry)
		{
			swprintf_s(aYSTB, L"yst%05d.ybn", iteEntry.uiSequence);
			woText << L"YSTB File   :" << aYSTB << L'\n';

			mPath = iteEntry.aRelativePath;
			StrToWStr(mPath, wPath, 932);
			woText << L"RelativePath:" << wPath << L'\n';

			woText << L"TextCount   :" << iteEntry.uiTextCount << L"\n\n";
		}

		woText.flush();
		woText.close();
		return true;
	}

	bool YSTL::MakeStructure()
	{
		std::wstring cur_dir = GetCurrentDirW() + L"\\Make\\";

		std::string rel_path;
		std::wstring full_path;
		std::wstring full_dir;
		wchar_t aYSTB[13] = { 0 };
		for (auto& iteEntry : m_vecEntry)
		{
			//Get Full Path
			rel_path = FormatSlash(iteEntry.aRelativePath, '\\');
			full_path = cur_dir + StrToWStr(rel_path, 932);

			//Crete Dir
			full_dir = PathRemoveFileName(full_path);
			SHCreateDirectoryExW(NULL, full_dir.c_str(), NULL);

			//Get YSTB File Name
			swprintf_s(aYSTB, L"yst%05d.ybn", iteEntry.uiSequence);

			//Copy File
			CopyFileW(aYSTB, full_path.c_str(), FALSE);
		}

		return true;
	}

	bool YSTL::BackStructure()
	{
		return true;
	}

}
