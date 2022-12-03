#include "YSTList.h"

YstList::YstList(std::wstring wsYstListFile) :
	m_pYstList(nullptr)
{
	m_wsYstListFile = wsYstListFile;

	wchar_t currentDir[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(0xFF, currentDir);
	m_wsCurrentDir = currentDir;

	if (GetScriptInfo())
	{
		GetMakeDirInfo();
	}
}

YstList::~YstList()
{
	if (m_pYstList)
	{
		delete[] m_pYstList;
	}
}

bool YstList::GetScriptInfo()
{
	size_t scriptCount = 0;
	std::ifstream ifsYstList(m_wsYstListFile, std::ios::binary);
	if (ifsYstList.is_open())
	{
		size_t szFile = Tools::GetFileSize(ifsYstList);
		if (!szFile)
		{
			return false;
		}

		char* m_pYstList = new char[szFile];
		if (!m_pYstList)
		{
			return false;
		}

		ifsYstList.read(m_pYstList, szFile);

		if (*(unsigned int*)(((YSTListHeader*)m_pYstList)->aSignature) == 0x4C545359)
		{
			scriptCount = ((YSTListHeader*)m_pYstList)->iScriptCount;
		}

		ScriptInfo si = { 0 };
		ScriptInfo* pInfoStart = (ScriptInfo*)(m_pYstList + sizeof(YSTListHeader));
		for (size_t iteYst = 0; iteYst < scriptCount; iteYst++)
		{
			si.iIndex = pInfoStart->iIndex;
			si.iPathLength = pInfoStart->iPathLength;
			si.lpPath = (char*)&pInfoStart->iPathLength + 0x4;
			pInfoStart = (ScriptInfo*)((char*)pInfoStart + si.iPathLength);
			si.iLowDateTime = pInfoStart->iLowDateTime;
			si.iHighDateTime = pInfoStart->iHighDateTime;
			si.iVariableCount = pInfoStart->iVariableCount;
			si.iLabelCount = pInfoStart->iLabelCount;
			si.iTextCount = pInfoStart->iTextCount;

			m_vecScriptInfoList.push_back(si);
			pInfoStart = (ScriptInfo*)((char*)pInfoStart + sizeof(ScriptInfo) - 0x4);
		}
		pInfoStart = nullptr;

		ifsYstList.close();
		return true;
	}

	return false;
}

void YstList::GetMakeDirInfo()
{
	ScriptPath dirInfo;
	std::string scriptFullPath;
	wchar_t fileName[13] = { 0 };

	for (ScriptInfo& iteScriptInfo : m_vecScriptInfoList)
	{
		wsprintfW(fileName, L"yst%05d.ybn", iteScriptInfo.iIndex);
		iteScriptInfo.lpPath[iteScriptInfo.iPathLength] = L'\0';
		scriptFullPath = iteScriptInfo.lpPath;

		dirInfo.wsYbn = fileName;
		dirInfo.wsPath = Tools::StrToWStr(scriptFullPath, 932);
		dirInfo.iTextCount = iteScriptInfo.iTextCount;

		m_vecScriptPathList.push_back(dirInfo);
	}
}

void YstList::TextCount()
{
	std::wofstream oTextCout(L"TextCount.txt");
	auto cvtUTF8 = std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::codecvt_mode(std::consume_header | std::generate_header | std::little_endian)>);
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

void YstList::MakeDir()
{
	std::wofstream oMakeDir(L"MakeDir.txt");
	auto cvtUTF8 = std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::codecvt_mode(std::consume_header | std::generate_header | std::little_endian)>);
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

void YstList::RestoreDir()
{
	CreateDirectoryW(L"ysbin_RestoreDir", NULL);
	for (ScriptPath& iteDirInfo : m_vecScriptPathList)
	{
		CopyFileW((L"ysbin_MakeDir\\" + iteDirInfo.wsPath + L".ybn").c_str(), (L"ysbin_RestoreDir\\" + iteDirInfo.wsYbn).c_str(), FALSE);
	}
}