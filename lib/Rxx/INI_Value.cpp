#include "INI_Value.h"
#include "Str.h"


namespace Rcf
{
	namespace INI
	{
		Value::Value()
		{

		}

		Value::Value(const int iValue)
		{
			m_wsValue = std::to_wstring(iValue);
		}

		Value::Value(const uint32_t uiValue)
		{
			m_wsValue = std::to_wstring(uiValue);
		}

		Value::Value(const float fValue) 
		{ 
			m_wsValue = std::to_wstring(fValue);
		}

		Value::Value(const double dValue) 
		{ 
			m_wsValue = std::to_wstring(dValue);
		}

		Value::Value(const bool bValue) 
		{ 
			m_wsValue = bValue ? L"true" : L"false";
		}

		Value::Value(const wchar_t* wValue)
		{ 
			m_wsValue = wValue;
		}

		Value::Value(const std::wstring& wsValue)
		{
			m_wsValue = wsValue; 
		}

		Value::operator const int() 
		{
			return std::stoi(m_wsValue, nullptr, 0);
		}

		Value::operator const uint32_t()
		{
			return std::stoi(m_wsValue, nullptr, 16);
		}

		Value::operator const float() 
		{
			return std::stof(m_wsValue);
		}

		Value::operator const double() 
		{
			return std::stod(m_wsValue);
		}

		Value::operator const bool() 
		{
			return _wcsicmp(m_wsValue.c_str(), L"true") == 0;
		}

		Value::operator const wchar_t*() 
		{
			return m_wsValue.c_str();
		}

		Value::operator const std::string() const
		{
			return Rut::StrX::WStrToStr(m_wsValue, 0);
		}

		Value::operator const std::wstring() const
		{
			return m_wsValue;
		}

		Value::operator std::wstring& () 
		{
			return m_wsValue;
		}

		bool Value::Empty() 
		{
			return m_wsValue.empty();
		}
	}
}