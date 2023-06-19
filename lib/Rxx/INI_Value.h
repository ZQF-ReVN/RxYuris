#pragma once
#include <string>

//Ria's Configuration File Library X 
namespace Rcf
{
	namespace INI
	{
		class Value
		{
		private:
			std::wstring m_wsValue;

		public:
			Value();

			Value(const int iValue);
			Value(const uint32_t uiValue);
			Value(const float fValue);
			Value(const double dValue);
			Value(const bool bValue);
			Value(const wchar_t* wValue);
			Value(const std::wstring& wsValue);

			operator const int();
			operator const uint32_t();
			operator const float();
			operator const double();
			operator const bool();
			operator const wchar_t*();
			operator const std::string() const;
			operator const std::wstring() const;
			operator std::wstring& ();

			bool Empty();
		};
	}
}