#include "YSTL.h"
#include "..\TDA\FileX.h"
#include "..\TDA\CVTString.h"

#include <Windows.h>
#include <shlobj_core.h>
#include <shlwapi.h>
#include <fstream>

using namespace YSTL_Struct;
using namespace TDA;

YSTList::YSTList(std::wstring wsYSTL) :
	m_Header{ 0 },
	m_wsYSTL(wsYSTL)
{
	m_ifsYSTL.open(m_wsYSTL, std::ios::binary);
	InitIndex();
}

YSTList::~YSTList()
{
	if (m_ifsYSTL.is_open())
	{
		m_ifsYSTL.close();
	}
}

bool YSTList::InitIndex()
{
	if (!m_ifsYSTL.is_open()) return false;

	char* pIndex = nullptr;
	m_ifsYSTL.read(reinterpret_cast<char*>(&m_Header), sizeof(m_Header));
	pIndex = new char[static_cast<size_t>(FileX::GetFileSize(m_ifsYSTL)) - sizeof(m_Header)];
	m_ifsYSTL.read(pIndex, FileX::GetFileSize(m_ifsYSTL) - sizeof(m_Header));

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

bool YSTList::PrintIndexToFile()
{
	std::wofstream woText(L"YSTList_Info.txt");
	woText.imbue(CVTString::GetCVT_UTF8());
	if (!woText.is_open()) return false;

	std::string mPath;
	std::wstring wPath;
	wchar_t aYSTB[13] = { 0 };
	for (auto& iteEntry : m_vecEntry)
	{
		swprintf_s(aYSTB, L"yst%05d.ybn", iteEntry.uiSequence);
		woText << L"YSTB File   :" << aYSTB << L'\n';

		mPath = iteEntry.aRelativePath;
		CVTString::StrToWStr(mPath, wPath, 932);
		woText << L"RelativePath:" << wPath << L'\n';

		woText << L"TextCount   :" << iteEntry.uiTextCount << L"\n\n";
	}

	woText.flush();
	woText.close();
	return true;
}

bool YSTList::MakeDirStructure()
{
	std::wstring makeDir;
	FileX::GetWokrDir(makeDir, L"\\Make\\");

	std::string relaPath;
	std::wstring fullPath;
	std::wstring fullDir;
	wchar_t aYSTB[13] = { 0 };
	for (auto& iteEntry : m_vecEntry)
	{
		//Get Full Path
		FileX::BackSlash(relaPath, iteEntry.aRelativePath);
		CVTString::StrToWStr(relaPath, fullPath, 932);
		fullPath.insert(0, makeDir);

		//Crete Dir
		FileX::PathRemoveFileName(fullPath, fullDir);
		SHCreateDirectoryExW(NULL, fullDir.c_str(), NULL);
		
		//Get YSTB File Name
		swprintf_s(aYSTB, L"yst%05d.ybn", iteEntry.uiSequence);

		//Copy File
		CopyFileW(aYSTB, fullPath.c_str(), FALSE);
	}

	return true;
}

bool YSTList::RestoreStructure()
{
	std::wstring makeDir;
	FileX::GetWokrDir(makeDir, L"\\Make\\");

	std::wstring restoreDir;
	FileX::GetWokrDir(restoreDir, L"\\Restore\\");





	return true;
}
