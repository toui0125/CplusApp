#include "Roboter/Controller/Controller.hpp"

int main()
{
  Controller* my_controller_p = new Controller();
  my_controller_p->SayHello();
  bool is_recommend_restaurant_exist = my_controller_p->RecommendRestaurant();
  if (is_recommend_restaurant_exist == false)
  {
    my_controller_p->AskUserFavoriteRestaurant();
  }
  my_controller_p->SayThankYou();

  return 0;
}

// コンパイルコマンド
/* g++ -std=c++17 Main.cpp Roboter/Controller/Controller.cpp Roboter/Model/DataModel.cpp Roboter/Model/FileModel.cpp Roboter/View/View.cpp -o compiled */