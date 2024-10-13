#include <iostream>
//
//int main() {
//    using namespace std;
//    cout << "О сколько нам открытий чудных" << endl
//    << "Готовят просвещенья дух" << endl
//    << "И опыт, сын ошибок трудных," << endl
//    << "И гений, парадоксов друг." << endl;
//    return 0;
//}

int main(){
  std::cout << "О сколько нам открытий чудных\n"
    "Готовят просвещенья дух\n"
    "И опыт, сын ошибок трудных,\n"
    "И гений, парадоксов друг.\n" 
    << std::endl;
  const char* line = "Привет"" Мир!";
  std::cout << line << std::endl;
  return (0);

}
