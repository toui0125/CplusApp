#include "View.hpp"

std::string View::PrintMessage(std::string template_file_content)
{
  std::string user_input = "";
  std::cout << template_file_content << std::endl;
  std::cin >> user_input;
  
  return user_input;
}

void View::PrintThankYouMessage(std::string template_file_content)
{
  std::cout << template_file_content << std::endl;
}