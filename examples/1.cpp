#include "../tools/color.hpp"
using namespace Tools;
int main(){
    //Msg << " hello world" << '\n';
    //Alert << " hello world" << '\n';
    //Alert << " hello world" << '\n';
    auto t = Info<std::string>("hello world") ;
    std::cout << t << std::endl;
    std::cout <<
        Info<std::string>("hello world") 
        << std::endl;
    return 0;
}
