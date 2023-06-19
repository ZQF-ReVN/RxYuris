#pragma once
#include <fstream>

#include "Str.h"


namespace Rut
{
	namespace FileX
	{
		template <typename T_FileName>
		std::streamsize GetFileSize(const T_FileName& tFile)
		{
			std::ifstream ifs(tFile, std::ios::binary);
			if (!ifs) { throw std::runtime_error("GetFileSize: Open File Error!"); }

			ifs.seekg(0, std::ios::end);
			return ifs.tellg();
		}

		template <typename T_Stream>
		std::streamsize GetFileSize(T_Stream& tStream)
		{
			std::streamsize file_size = 0;
			std::streampos file_pos = tStream.tellg();

			tStream.seekg(0, std::ios::end);
			file_size = tStream.tellg();
			tStream.seekg(file_pos, std::ios::beg);

			return file_size;
		}

		template <typename T_FileName>
		std::ofstream  CreateFileBinaryStream(const T_FileName& tFile)
		{
			std::ofstream ofs(tFile, std::ios::binary);
			if (!ofs) { throw std::runtime_error("CreateFileBinaryStream: Create File Error!"); }
			return ofs;
		}

		template <typename T_FileName>
		std::ofstream  CreateFileANSIStream(const T_FileName& tFile)
		{
			std::ofstream ofs(tFile);
			if (!ofs) { throw std::runtime_error("CreateFileANSIStream: Create File Error!"); }
			return ofs;
		}

		template <typename T_FileName>
		std::wofstream CreateFileUTF8Stream(const T_FileName& tFile)
		{
			std::wofstream ofs(tFile);
			ofs.imbue(StrX::GetCVT_UTF8());
			if (!ofs) { throw std::runtime_error("CreateFileUTF8Stream: Create File Error!"); }
			return ofs;
		}

		template <typename T_FileName>
		std::ifstream  OpenFileBinaryStream(const T_FileName& tFile)
		{
			std::ifstream ifs(tFile, std::ios::binary);
			if (!ifs) { throw std::runtime_error("OpenFileBinaryStream: Open File Error!"); }
			return ifs;
		}

		template <typename T_FileName>
		std::ifstream  OpenFileANSIStream(const T_FileName& tFile)
		{
			std::ifstream ifs(tFile);
			if (!ifs) { throw std::runtime_error("OpenFileANSIStream: Open File Error!"); }
			return ifs;
		}

		template <typename T_FileName>
		std::wifstream OpenFileUTF8Stream(const T_FileName& tFile)
		{
			std::wifstream ifs(tFile);
			ifs.imbue(StrX::GetCVT_UTF8());
			if (!ifs) { throw std::runtime_error("OpenFileUTF8Stream: Open File Error!"); }
			return ifs;
		}
	}
}