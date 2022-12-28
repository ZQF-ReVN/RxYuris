#include "YSTList.h"
#include <Windows.h>
#include <shlobj_core.h>
#include <fstream>
#include "..\Tools\FileX.h"
#include "..\Tools\CVTString.h"
using namespace CUS_Struct;
using namespace ORG_Struct;

YSTList::YSTList(std::wstring wsYSTListFile) :
	m_pYSTList(nullptr)
{
	m_wsYSTListFile = wsYSTListFile;

	wchar_t currentDir[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(0xFF, currentDir);
	m_wsCurrentDir = currentDir;

	if (GetScriptInfo())
	{
		GetMakeDirInfo();
	}
}

YSTList::~YSTList()
{
	if (m_pYSTList)
	{
		delete[] m_pYSTList;
	}
}

bool YSTList::GetScriptInfo()
{
	size_t scriptCount = 0;
	std::streamsize szFile = 0;

	std::ifstream iYstList(m_wsYSTListFile, std::ios::binary);
	if (iYstList.is_open())
	{
		szFile = FileX::GetFileSize(iYstList);
		if (!szFile)
		{
			iYstList.close();
			return false;
		}

		m_pYSTList = new char[static_cast<size_t>(szFile)];
		if (!m_pYSTList)
		{
			iYstList.close();
			return false;
		}

		iYstList.read(m_pYSTList, szFile);

		if (*(unsigned int*)(((YSTListHeader_V5*)m_pYSTList)->aSignature) == 0x4C545359)
		{
			scriptCount = ((YSTListHeader_V5*)m_pYSTList)->iScriptCount;
		}

		ScriptInfo_V5 si = { 0 };
		ScriptInfo_V5* pInfoStart = (ScriptInfo_V5*)(m_pYSTList + sizeof(YSTListHeader_V5));
		for (size_t iteYst = 0; iteYst < scriptCount; iteYst++)
		{
			si.iIndex = pInfoStart->iIndex;
			si.iPathLength = pInfoStart->iPathLength;
			si.lpPath = (char*)&pInfoStart->iPathLength + 0x4;
			pInfoStart = (ScriptInfo_V5*)((char*)pInfoStart + si.iPathLength);
			si.iLowDateTime = pInfoStart->iLowDateTime;
			si.iHighDateTime = pInfoStart->iHighDateTime;
			si.iVariableCount = pInfoStart->iVariableCount;
			si.iLabelCount = pInfoStart->iLabelCount;
			si.iTextCount = pInfoStart->iTextCount;

			m_vecScriptInfoList.push_back(si);
			pInfoStart = (ScriptInfo_V5*)((char*)pInfoStart + sizeof(ScriptInfo_V5) - 0x4);
		}
		pInfoStart = nullptr;

		iYstList.close();
		return true;
	}

	return false;
}

void YSTList::GetMakeDirInfo()
{
	ScriptPath dirInfo;
	std::string scriptFullPath;
	wchar_t fileName[13] = { 0 };

	for (ScriptInfo_V5& iteScriptInfo : m_vecScriptInfoList)
	{
		wsprintfW(fileName, L"yst%05d.ybn", iteScriptInfo.iIndex);
		iteScriptInfo.lpPath[iteScriptInfo.iPathLength] = L'\0';
		scriptFullPath = iteScriptInfo.lpPath;

		dirInfo.wsYbn = fileName;
		CVTString::StrToWStr(scriptFullPath, dirInfo.wsPath, 932);
		dirInfo.iTextCount = iteScriptInfo.iTextCount;

		m_vecScriptPathList.push_back(dirInfo);
	}
}

void YSTList::TextCount()
{
	std::locale cvtUTF8 = CVTString::GetCVT();

	std::wofstream oTextCout(L"TextCount.txt");
	oTextCout.imbue(cvtUTF8);

	if (oTextCout.is_open())
	{
		for (ScriptPath& iteDirInfo : m_vecScriptPathList)
		{
			if (iteDirInfo.iTextCount)
			{
				oTextCout << iteDirInfo.wsPath << L'\n' << iteDirInfo.wsYbn << L"\n" << L"TextCount:" << iteDirInfo.iTextCount << '\n' << std::endl;
			}
		}

		oTextCout.flush();
		oTextCout.close();
	}

}

void YSTList::MakeDir()
{
	std::locale cvtUTF8 = CVTString::GetCVT();

	std::wofstream oMakeDir(L"MakeDir.txt");
	oMakeDir.imbue(cvtUTF8);
	if (oMakeDir.is_open())
	{
		std::wstring currentDir = m_wsCurrentDir + L"\\ysbin_MakeDir\\";
		for (ScriptPath& iteScriptPath : m_vecScriptPathList)
		{
			SHCreateDirectoryExW(NULL, (currentDir + iteScriptPath.wsPath.substr(0, iteScriptPath.wsPath.rfind(L'\\'))).c_str(), NULL);
			CopyFileW(iteScriptPath.wsYbn.c_str(), (currentDir + iteScriptPath.wsPath + L".ybn").c_str(), FALSE);
			oMakeDir << iteScriptPath.wsYbn << L'\n';
			oMakeDir << iteScriptPath.wsPath << L'\n' << L'\n';
		}

		oMakeDir.flush();
		oMakeDir.close();
	}
}

void YSTList::RestoreDir()
{
	CreateDirectoryW(L"ysbin_RestoreDir", NULL);
	for (ScriptPath& iteDirInfo : m_vecScriptPathList)
	{
		CopyFileW((L"ysbin_MakeDir\\" + iteDirInfo.wsPath + L".ybn").c_str(), (L"ysbin_RestoreDir\\" + iteDirInfo.wsYbn).c_str(), FALSE);
	}
}