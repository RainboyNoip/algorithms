#pragma once
//#include <algo/base.hpp>
#include <iostream>
#include <ostream>

namespace Tools {

//[bash:tip_colors_and_formatting - FLOZz' MISC](https://misc.flogisoft.com/bash/tip_colors_and_formatting)
//[c++ - How do I output coloured text to a Linux terminal? - Stack Overflow](https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal)
enum ColorCode {
    //效果
    RST        = 0, //重置
    BLOD       = 1,
    DIM        = 2,
    UNDERLINE  = 4, 
    BLINK      = 5,
    INVERT     = 7,
    HIDDEN     = 8,

    //前景色
    FG_RED     = 31,
    FG_GREEN   = 32,
    FG_BLUE    = 34,
    FG_DEFAULT = 39,

    //背景色
    BG_RED     = 41,
    BG_GREEN   = 42,
    BG_BLUE    = 44,
    BG_DEFAULT = 49

};

class FontModifier {
public:
    FontModifier(ColorCode __c): code(__c) {}
    friend std::ostream& operator<<(std::ostream& os,const FontModifier& mod){
            return os << "\033[" << mod.code << "m";
        }
private:
    ColorCode code;
};


const FontModifier rst        = RST        ;
const FontModifier blod       = BLOD       ;
const FontModifier dim        = DIM        ;
const FontModifier underline  = UNDERLINE  ;
const FontModifier blink      = BLINK      ;
const FontModifier invert     = INVERT     ;
const FontModifier hidden     = HIDDEN     ;

const FontModifier fg_red     = FG_RED     ;
const FontModifier fg_green   = FG_GREEN   ;
const FontModifier fg_blue    = FG_BLUE    ;
const FontModifier fg_default = FG_DEFAULT ;

const FontModifier bg_red     = BG_RED     ;
const FontModifier bg_green   = BG_GREEN   ;
const FontModifier bg_blue    = BG_BLUE    ;
const FontModifier bg_default = BG_DEFAULT ;

enum _NOTIFY_ {
    info,
    alert,
    msg
};
template<
    _NOTIFY_ tag
    ,typename T
    //,std::enable_if_t<std::is_reference_v<T>, int> = 0
    >
struct NotifyWrapper {
    explicit NotifyWrapper(T t)
        :V{t}
    {}

    T V;

    friend std::ostream& operator<<(std::ostream& o,NotifyWrapper& some) {
        if constexpr ( tag == info){
            o << bg_green << fg_blue << some.V << rst ;
        }
        else if constexpr ( tag == alert ) {
            o << bg_red << some.V << rst;
        }
        else if constexpr ( tag == msg) {
            o << fg_blue << some.V << rst;
        }
        return o;
    }

    friend std::ostream& operator<<(std::ostream& o,NotifyWrapper&& some) {
        return o << some;
    }
};

template<_NOTIFY_ tag = info>
struct Notify {
    template<typename T>
    friend const Notify<tag>& operator<<(const Notify<tag>& notify,T&& some) {
        auto& o  = std::cout;
        if constexpr ( tag == info){
            o << bg_green << fg_blue << some << rst << rst;
        }
        else if constexpr ( tag == alert ) {
            o << bg_red << some << rst;
        }
        else if constexpr ( tag == msg) {
            o << fg_blue << some << rst;
        }
        return notify;
    }
};

template<typename T>
using Info = NotifyWrapper<info,T>;
//struct Info : public NotifyWrapper<info, T>  { using NotifyWrapper<info, T>::NotifyWrapper;};

template<typename T>
using Alert = NotifyWrapper<alert,T>;

template<typename T>
using Msg= NotifyWrapper<msg,T>;



//constexpr  auto Info  = Notify<info>();
//constexpr  auto Msg   = Notify<msg>();
//constexpr  auto Alert = Notify<alert>();

} //namespace Tools
