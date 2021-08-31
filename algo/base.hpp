/*
 *   noiCppUtils, some helpful cpp utils for noi/acm user
 *    Copyright (C) 2020-2021  Rainboy
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/* 
 * 常用宏
 * */

#pragma once

#include <iostream>

#define __MY_SELF__NAMESPACE__ rainboy

namespace __MY_SELF__NAMESPACE__ {


#define log(...) { \
    fprintf(stderr,"In [ %s ],At line [ %d ]\n",__func__,__LINE__); \
    fprintf(stderr,__VAR_ARGS__); \
    fprintf(stderr,"\n"); \
}

// 加上 std::cin std::cout
//[（acm）C++加速输入的几种方法_hebtu666-CSDN博客](https://blog.csdn.net/hebtu666/article/details/107269428)
struct quick_io {
    quick_io(){
	    std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
};



} //namespace __MY_SELF__NAMESPACE__
