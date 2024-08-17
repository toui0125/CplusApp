#include "FileModel.hpp"

NoTemplateFileError::NoTemplateFileError(const std::string& error_message)
{
  mErrorMessage = error_message;
}

const char* NoTemplateFileError::what() const noexcept
{
  return (this->mErrorMessage).c_str();
}

FileModel::FileModel(std::string csv_file_path)
{
  if (csv_file_path.empty())
  {
    this->mCsvFilePath = this->GetCsvFilePath();
  }
  std::ofstream csv_file(this->mCsvFilePath, std::ios::app);
  csv_file.close();
  this->mCsvFileColumn[0] = "RESTAURANT_NAME";
  this->mCsvFileColumn[1] = "POPULAR_COUNT";
}

std::string FileModel::GetCsvFilePath()
{
  std::string csv_file_path = "";

  #ifdef CSV_FILE_PATH
    csv_file_path = CSV_FILE_PATH;
  #endif

  if (csv_file_path.empty())
  {
    csv_file_path = "restaurant_ranking.csv";
  }

  return csv_file_path;
}

std::string FileModel::GetTemplateFilePath(std::string template_file_name)
{
  std::string template_dir_path = "";

  #ifdef TEMPLATE_DIR_PATH
    template_dir_path = TEMPLATE_DIR_PATH;
  #endif

  if (template_dir_path.empty())
  {
    std::filesystem::path current_dir_path = std::filesystem::current_path();

    template_dir_path = current_dir_path.string() + "/Roboter/Template/";
  }

  std::string template_file_path = template_dir_path + template_file_name;

  return template_file_path;
}

std::string FileModel::GetTemplateFileContent(std::string template_file_name)
{
  std::string template_file_path = this->GetTemplateFilePath(template_file_name);
  std::ifstream template_file(template_file_path);

  try
  {
    if (!template_file)
    {
      throw NoTemplateFileError("Cannot open " + template_file_path);
    }
  }
  catch(const NoTemplateFileError& e)
  {
    std::cout << e.what() << std::endl;
    exit (1);
  }

  std::string template_file_all_content = "";
  std::string template_file_content;
  while (std::getline(template_file, template_file_content))
  {
    template_file_all_content += template_file_content + '\n';
  }

  template_file.close();

  std::string splitter(60, '=');
  template_file_all_content = splitter + '\n' + template_file_all_content + splitter;

  return template_file_all_content;
}

std::string FileModel::RewritePartOfFile(std::string template_file_name, std::vector<std::string> replace_word)
{
  std::string template_file_content = this->GetTemplateFileContent(template_file_name);

  for (std::string word : replace_word)
  {
    template_file_content.replace(template_file_content.find("$replace"), 8, word);
  }

  return template_file_content;
}

void FileModel::UpdateFile(std::map<std::string, int> restaurant_data)
{
  std::ofstream csv_file(this->mCsvFilePath, std::ios::app);

  csv_file << mCsvFileColumn[0] << "," << mCsvFileColumn[1] << std::endl;

  for(const auto& restautrant : restaurant_data)
  {
    csv_file << restautrant.first << "," << restautrant.second << std::endl;
  }

  csv_file.close();
}

std::map<std::string, int> FileModel::PutFileDataIntoMap(std::map<std::string, int> restaurant_data)
{
  std::ifstream csv_file(this->mCsvFilePath);

  std::string csv_file_row;
  std::string restaurant_name;
  std::string popular_count_str;

  std::getline(csv_file, csv_file_row);
  while(std::getline(csv_file, csv_file_row))
  {
    std::istringstream csv_file_line(csv_file_row);
    std::getline(csv_file_line, restaurant_name, ',');
    std::getline(csv_file_line, popular_count_str);

    restaurant_data[restaurant_name] = std::stoi(popular_count_str);
  }

  return restaurant_data;
}