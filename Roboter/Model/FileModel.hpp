#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class NoTemplateFileError : public std::exception
{
  private:
  std::string mErrorMessage;

  public:
  NoTemplateFileError(const std::string& error_message);
  const char* what() const noexcept override;
};

class FileModel
{
  private:
  std::string mCsvFilePath;
  std::string mCsvFileColumn[2];

  public:
  FileModel(std::string csv_file_path = "");
  std::string GetCsvFilePath();
  std::string GetTemplateFilePath(std::string template_file_name);
  std::string GetTemplateFileContent(std::string template_file_name);
  std::string RewritePartOfFile(std::string template_file_name, std::vector<std::string> replace_word);
  void UpdateFile(std::map<std::string, int> restaurant_data);
  std::map<std::string, int> PutFileDataIntoMap(std::map<std::string, int> restaurant_data);
};