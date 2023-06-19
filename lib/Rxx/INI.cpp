#include "INI.h"
#include "Str.h"
#include "File.h"

#include <sstream>


namespace Rcf
{
	namespace INI
	{
		using namespace Rut::StrX;
		using namespace Rut::FileX;

		INI_File::INI_File()
		{

		}

		INI_File::INI_File(const std::wstring & wsINI)
		{
			Parse(wsINI);
		}

		void INI_File::Parse(const std::wstring& wsINI)
		{
			std::wifstream wifs_ini = OpenFileUTF8Stream(wsINI);

			std::size_t pos = -1;
			std::wstring node_name;
			for (std::wstring line; std::getline(wifs_ini, line);)
			{
				if (line.empty()) { continue; }

				switch (line[0])
				{
				case L'#':case L';':case L'/': // Comment Char
					break;

				case L'[': // [Node]
				{
					pos = line.find_first_of(L']');
					if (pos == std::wstring::npos) { throw std::runtime_error("INI_File:Parse: Get Node Error!"); }
					node_name = Trim(line.substr(1, pos - 1));
				}
				break;

				default:// Key = Value
				{
					pos = line.find_first_of(L'=');
					if ((pos == std::wstring::npos) || (pos == 0)) { throw std::runtime_error("INI_File::Parse: Get Key Error!"); }
					m_mpNodes[node_name][Trim(line.substr(0, pos))] = Trim(line.substr(pos + 1));
				}
				break;
				}
			}
		}

		void INI_File::Save(const std::wstring& wsFile)
		{
			std::wofstream wofs_ini = CreateFileUTF8Stream(wsFile);
			wofs_ini << Dump();
		}

		std::wstring INI_File::Dump()
		{
			std::wstringstream ss;
			for (auto& node : m_mpNodes)
			{
				ss << L"[" << node.first << L"]" << L'\n';
				for (auto& key : node.second) { ss << key.first << L"=" << std::wstring(key.second) << L'\n'; }
				ss << L'\n';
			}
			return ss.str();
		}


		NodesMap::iterator INI_File::At(const std::wstring& wsNode)
		{
			return m_mpNodes.find(wsNode);
		}

		NodesMap::iterator INI_File::End()
		{
			return m_mpNodes.end();
		}

		KeysMap& INI_File::Get(const std::wstring& wsNode)
		{
			const auto& ite_node = At(wsNode);
			if (ite_node == End()) { throw std::runtime_error("INI_File::Get: INI File No Find Node"); }
			return ite_node->second;
		}

		Value& INI_File::Get(const std::wstring& wsNode, const std::wstring& wsName)
		{
			auto& keys = Get(wsNode);
			const auto& ite_keys = keys.find(wsName);
			if (ite_keys == keys.end()) { throw std::runtime_error("INI_File::Get: INI File No Find Key"); }
			return ite_keys->second;
		}

		KeysMap& INI_File::operator[] (const std::wstring& wsNode)
		{
			return Get(wsNode);
		}

		void INI_File::Add(const std::wstring& wsNode, const std::wstring& wsName, const Value& vValue)
		{
			m_mpNodes[wsNode][wsName] = vValue;
		}

		bool INI_File::Has(const std::wstring& wsNode)
		{
			return At(wsNode) != End() ? true : false;
		}

		bool INI_File::Has(const std::wstring& wsNode, const std::wstring& wsName)
		{
			auto ite_node = At(wsNode);
			if (ite_node != End())
			{
				auto& keys = ite_node->second;
				auto ite_keys = keys.find(wsName);
				return ite_keys != keys.end() ? true : false;
			}
			return false;
		}
	}
}