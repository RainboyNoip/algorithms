/*
 *   rainboyNoip/algorithms, some helpful cpp utils for noi/acm user
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
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <tuple>
#include <memory_resource>

//最大数据等级1
#ifndef MAXLevel1 
#define MAXLevel1 7
#endif

//最大数据等级2
#ifndef MAXLevel2
#define MAXLevel2 7
#endif

namespace rainboy {


//typedef std::integral_constant<size_t, 1000005> MAXN; // 最多点的数量
//typedef std::integral_constant<size_t, 1000005> MAXE; // 最多边的数量

// 加上 std::cin std::cout
//[（acm）C++加速输入的几种方法_hebtu666-CSDN博客](https://blog.csdn.net/hebtu666/article/details/107269428)
struct quick_io {
    quick_io(){
	    std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
};

//计算 题目的数量级
constexpr std::size_t __convDataLeveL(unsigned int l){
    std::size_t L = 1;
    for(int i=1;i<=l;++i) L *= 10;
    return L + 5;
}

template<unsigned int level = 7>
struct DataLevelImpl
{
    static constexpr std::size_t value = __convDataLeveL(level);
};

template<unsigned int level = 7>
constexpr auto & DataLevel = DataLevelImpl<level>::value;

//所有算法类的基类
template<unsigned int level1, unsigned int level2>
class __Base {
public:
    //算法数据等级
    constexpr static std::size_t m_DataLevel = DataLevel<level1>;
    constexpr static std::size_t m_DataLevel2 = DataLevel<level2>;
};

template<unsigned int level1>
class __Base<level1,0> {
    constexpr static std::size_t m_DataLevel = DataLevel<level1>;
};


} //namespace rainboy
