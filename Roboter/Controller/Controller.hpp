#include "../Model/DataModel.hpp"
#include "../Model/FileModel.hpp"
#include "../View/View.hpp"

class Controller
{
  private:
  DataModel* mDataModel_p;
  FileModel* mFileModel_p;
  View* mView_p;
  std::vector <std::string> mReplaceWord = {};

  public:
  Controller();
  void SayHello();
  bool RecommendRestaurant();
  void AskUserFavoriteRestaurant();
  void SayThankYou();
};