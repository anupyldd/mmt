#pragma once

#include <filesystem>
#include <memory>
#include <vector>
#include <string>

namespace miniz_cpp { class zip_file; struct zip_info; }

namespace mmt
{
	namespace util
	{
		struct ZipInfo
		{
			std::unique_ptr<miniz_cpp::zip_info> info;
		};

		class Zip
		{
		public:
			void Load(const std::filesystem::path& path);
			void Save(const std::filesystem::path& path);
			void Save(std::vector<unsigned char>& bytes);
			void Reset();

			std::ostream& Open(const std::string& name);
			void Extract(const std::string& member, const std::filesystem::path& path);
			void Extract(const std::vector<std::string>& members, const std::filesystem::path& path);
			void ExtractAll(const std::filesystem::path& path);
			std::string Read(const std::string& name);
			void Write(const std::string& name);
			void WriteStr(const std::string& arc, const std::string& bytes);

			bool HasFile(const std::string& name) const;
			miniz_cpp::zip_info GetInfo(const std::string& name);
			std::vector<miniz_cpp::zip_info> InfoList();
			std::vector<std::string> NameList();
			void PrintDir() const;

		private:
			std::shared_ptr<miniz_cpp::zip_file> file;
		};
	}
}