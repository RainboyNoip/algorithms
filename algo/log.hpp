#pragma once
#include <algo/base.hpp>
#include <iostream>

namespace __MY_SELF__NAMESPACE__ {

//[bash:tip_colors_and_formatting - FLOZz' MISC](https://misc.flogisoft.com/bash/tip_colors_and_formatting)
//[c++ - How do I output coloured text to a Linux terminal? - Stack Overflow](https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal)
enum Code {
    RST        = 0,
    BLOD       = 1,
    DIM        = 2,
    UNDERLINE  = 4,
    BLINK      = 5,
    INVERT     = 7,
    HIDDEN     = 8,

    FG_RED     = 31,
    FG_GREEN   = 32,
    FG_BLUE    = 34,
    FG_DEFAULT = 39,

    BG_RED     = 41,
    BG_GREEN   = 42,
    BG_BLUE    = 44,
    BG_DEFAULT = 49

};

class Modifier {
public:
    Modifier(Code __c): code(__c) {}
    friend std::ostream& 
        operator<<(std::ostream& os,const Modifier& mod){
            return os << "\033[" << mod.code << "m";
        }
private:
    Code code;
};


const Modifier rst        = RST        ;
const Modifier blod       = BLOD       ;
const Modifier dim        = DIM        ;
const Modifier underline  = UNDERLINE  ;
const Modifier blink      = BLINK      ;
const Modifier invert     = INVERT     ;
const Modifier hidden     = HIDDEN     ;

const Modifier fg_red     = FG_RED     ;
const Modifier fg_green   = FG_GREEN   ;
const Modifier fg_blue    = FG_BLUE    ;
const Modifier fg_default = FG_DEFAULT ;

const Modifier bg_red     = BG_RED     ;
const Modifier bg_green   = BG_GREEN   ;
const Modifier bg_blue    = BG_BLUE    ;
const Modifier bg_default = BG_DEFAULT ;

} //namespace __MY_SELF__NAMESPACE__
