#include "Zip.h"

#include "zip/zip_file.hpp"

#include <exception>
#include <format>

namespace mmt
{
	namespace util
	{
		void Zip::Load(const std::filesystem::path& path)
		{
			if (file) throw std::runtime_error(std::format("Zip file at [{}] is already open", path.string()));
			file = std::make_shared<miniz_cpp::zip_file>(path.string());
		}
		void Zip::Save(const std::filesystem::path& path)
		{
			if (file) file->save(path.string());
		}
		void Zip::Save(std::vector<unsigned char>& bytes)
		{
			if (file) file->save(bytes);
		}
		void Zip::Reset()
		{
			file->reset();
		}
		std::ostream& Zip::Open(const std::string& name)
		{
			if (!file)throw std::runtime_error(std::format("Failed to open file [{}]: zip is not loaded", name));
			return file->open(name);
		}
		void Zip::Extract(const std::string& member, const std::filesystem::path& path)
		{
			if (file) file->extract(member, path.string());
		}
		void Zip::Extract(const std::vector<std::string>& members, const std::filesystem::path& path)
		{
			if (file) file->extractall(path.string(), members);
		}
		void Zip::ExtractAll(const std::filesystem::path& path)
		{
			if (file) file->extractall(path.string());
		}
		std::string Zip::Read(const std::string& name)
		{
			return file ? file->read(name) : std::string();
		}
		void Zip::Write(const std::string& name)
		{
			if (file) file->write(name);
		}
		void Zip::WriteStr(const std::string& arc, const std::string& bytes)
		{
			if (file) file->writestr(arc, bytes);
		}
		bool Zip::HasFile(const std::string& name) const
		{
			return file ? file->has_file(name) : false;
		}
		miniz_cpp::zip_info Zip::GetInfo(const std::string& name)
		{
			return file ? file->getinfo(name) : miniz_cpp::zip_info{};
		}
		std::vector<miniz_cpp::zip_info> Zip::InfoList()
		{
			return file ? file->infolist() : std::vector<miniz_cpp::zip_info>();
		}
		std::vector<std::string> Zip::NameList()
		{
			return file ? file->namelist() : std::vector<std::string>();
		}
		void Zip::PrintDir() const
		{
			if (file) file->printdir();
		}
	}
}