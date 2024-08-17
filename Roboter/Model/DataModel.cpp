#include "DataModel.hpp"

DataModel::DataModel(std::string name)
{
  this->mName = name;
}

std::string DataModel::GetRobotName()
{
  return this->mName;
}

void DataModel::SetUserName(std::string user_name)
{
  user_name[0] = std::toupper(user_name[0]);
  this->mUserName = user_name;
}

std::string DataModel::GetMostPupularRestaurant(std::vector<std::string> already_recomennded_restaurants)
{
  if (msRestaurantData.empty())
  {
    return "";
  }

  std::vector<std::pair<std::string, int>> sorted_restaurant_data(msRestaurantData.begin(), msRestaurantData.end());
  std::sort
  (
    sorted_restaurant_data.begin(), sorted_restaurant_data.end(), [](const auto& former, const auto& latter)
    {
      return latter.second < former.second;
    }
  );
  for (const auto& restaurant : sorted_restaurant_data)
  {
    if (std::find(
        already_recomennded_restaurants.begin(), already_recomennded_restaurants.end(), restaurant.first
       ) != already_recomennded_restaurants.end())
    {
      continue;
    }
    return restaurant.first;
  }

  return "";
}

std::string DataModel::GetUserName()
{
  return mUserName;
}

std::map<std::string, int> DataModel::IncrementCounter(std::string user_favorite_restaurant)
{
  user_favorite_restaurant[0] = std::toupper(user_favorite_restaurant[0]);
  for (std::size_t i = 1; i < user_favorite_restaurant.length(); i++)
  {
    user_favorite_restaurant[i] = std::tolower(user_favorite_restaurant[i]);
  }

  if (msRestaurantData.find(user_favorite_restaurant) != msRestaurantData.end())
  {
    msRestaurantData[user_favorite_restaurant] += 1;
  }
  else
  {
    msRestaurantData[user_favorite_restaurant] = 1;
  }

  return msRestaurantData;
}