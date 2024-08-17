#include <map>
#include <string>
#include <vector>

class DataModel
{
  private:
  std::string mName;
  std::string mUserName;

  public:
  std::map<std::string, int> msRestaurantData = {};

  DataModel(std::string name);
  std::string GetRobotName();
  void SetUserName(std::string user_name);
  std::string GetMostPupularRestaurant(std::vector<std::string> already_recomennded_restaurants = {});
  std::string GetUserName();
  std::map<std::string, int> IncrementCounter(std::string user_favorite_restaurant);
};