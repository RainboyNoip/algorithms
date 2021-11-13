#include "../noicpputils.hpp"
int main(){
    int x=1,y=2,z=3;  
    tdbg(x,y,z);

    std::string str{"hello world"};
    dbg_one(str);
    tdbg_one(str);
    return 0;
}
