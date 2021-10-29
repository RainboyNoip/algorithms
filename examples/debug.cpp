#include "../noicpputils.hpp"
int main(){
    int x=1,y=2,z=3;  
    tdbg(x,y,z);

    std::string str{"hello world"};
    gbg_one(str);
    tgbg_one(str);
    return 0;
}
