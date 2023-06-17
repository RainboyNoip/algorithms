#include <iostream>
#include "draw_tree.hpp"

Draw_Tree mydr;

int main(){
    //init font
    // base64_decode(font_b_base64,font_a);
    //load font
    std::ifstream font("CamingoCode-Bold.ttf",std::ios::binary);
    if( !font ){
        std::cout << "cannot open font file" << "\n";
        return 1;
    }
    char t;
    while( font ) {
        font.read(&t, 1);
        font_a.push_back(t);
    }
    font.close();
    
    mydr.set_default_font();
    std::cout << font_a.size() << "\n";

    // mydr.draw_text("hello", 100,100);
    mydr.draw_one_node(100, 100, 'A');
    mydr.write_png("test.png");
    return 0;
}
