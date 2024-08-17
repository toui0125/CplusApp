#include "Controller.hpp"

Controller::Controller()
{
  mDataModel_p = new DataModel("Roboko");
  mFileModel_p = new FileModel();
  mDataModel_p->msRestaurantData = mFileModel_p->PutFileDataIntoMap(mDataModel_p->msRestaurantData);
  mView_p = new View();
}

void Controller::SayHello()
{
  while(true)
  {
    std::string robot_name = mDataModel_p->GetRobotName();
    mReplaceWord = {robot_name, robot_name};
    std::string template_file_content = mFileModel_p->RewritePartOfFile("hello.txt", mReplaceWord);
    std::string user_name = mView_p->PrintMessage(template_file_content);
    if (!user_name.empty())
    {
      mDataModel_p->SetUserName(user_name);
      break;
    }
  }
}

bool Controller::RecommendRestaurant()
{
  std::string recommend_restaurant = mDataModel_p->GetMostPupularRestaurant();
  if (recommend_restaurant.empty())
  {
    return false;
  }
  std::vector<std::string> already_recommended_restaurants = {recommend_restaurant};

  while(true)
  {
    mReplaceWord = {recommend_restaurant, recommend_restaurant};
    std::string template_file_content = mFileModel_p->RewritePartOfFile("greeting.txt", mReplaceWord);
    std::string is_yes = mView_p->PrintMessage(template_file_content);

    for (char& c : is_yes)
    {
      c = std::tolower(c);
    }
    if (is_yes == "y" || is_yes == "yes")
    {
      return true;
    }
    if (is_yes == "n" || is_yes == "no")
    {
      recommend_restaurant = mDataModel_p->GetMostPupularRestaurant(already_recommended_restaurants);
      if (recommend_restaurant.empty())
      {
        return false;
      }
      already_recommended_restaurants.push_back(recommend_restaurant);
    }
  }
}

void Controller::AskUserFavoriteRestaurant()
{
  while(true)
  {
    std::string user_name = mDataModel_p->GetUserName();
    mReplaceWord = {user_name, user_name};
    std::string template_file_content = mFileModel_p->RewritePartOfFile("which_restaurant.txt", mReplaceWord);
    std::string user_favorite_restaurant = mView_p->PrintMessage(template_file_content);

    if (!user_favorite_restaurant.empty())
    {
      std::map<std::string, int> restaurant_data = mDataModel_p->IncrementCounter(user_favorite_restaurant);
      mFileModel_p->UpdateFile(restaurant_data);
      break;
    }
  }
}

void Controller::SayThankYou()
{
  std::string robot_name = mDataModel_p->GetRobotName();
  std::string user_name = mDataModel_p->GetUserName();
  mReplaceWord = {robot_name, user_name, robot_name, user_name};
  std::string template_file_content = mFileModel_p->RewritePartOfFile("good_by.txt", mReplaceWord);
  mView_p->PrintThankYouMessage(template_file_content);
}