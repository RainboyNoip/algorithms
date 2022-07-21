/**
* 表格对象，可以进行表格的输出
* Author:Rainboy
*
*/

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>

#include "color.hpp"

// =========== table 
// 实现的功能
// add_row {"string",long long,double}
// Itertor cloumn(), row
// center, align left ,right ,
// change bg_color,fg_color
// change_value
// copy ctor
namespace Tools {
    using namespace std;

    class cell {
    public:
        template<typename U>
        explicit cell(U&& a){
            stringstream ss;
            ss << a;
            __c__ = ss.str();
        }

        int lenght() const{
            return __c__.length();
        }

        friend std::ostream& operator<<(std::ostream &o,const cell & c) {
            o << c.__c__;
            return o;
        }
    private:
        string __c__;
    };

    class Table {
    public:
        Table() = default;
        template<typename... Args>
        Table(Args... args){
             add_row(std::forward<Args>(args)...);
        }

        template<typename... Args>
        std::enable_if_t<sizeof...(Args)>
        add_row(Args... args){
            table_.emplace_back();
            ((table_.back().emplace_back(std::forward<Args>(args))),...);
        }

        //template<typename T,typename  U = std::vector<T> >
        template<typename T>
        void copy_row(std::vector<T>& vec){
            table_.push_back({});
            for (const auto& e : vec) {
                table_.back().emplace_back(e);
            }
        }

        friend std::ostream& operator<<(std::ostream& __o,const Table &t) {
            t.print(__o);
            return __o;
        }

        void print(std::ostream& __o = std::cerr) const{
            auto rows_cnt = table_.size();
            auto cols_cnt = rows_cnt == 0 ? : table_.front().size();
            std::vector<int> cols_length;

            //todo 保证每一行一样长
            
            for(int j = 0;j<cols_cnt ;j++){
                cols_length.push_back(0);
                for(int i = 0;i<rows_cnt;i++){
                    cols_length.back() = std::max( cols_length.back(),table_[i][j].lenght());
                }
                cols_length.back() += padding_left.length();
                cols_length.back() += padding_right.length();
            }
            auto print_row_table_border = [&](){
                for (const auto& e : cols_length) {
                    __o << conner;
                    for(int i=1;i<=e;++i) __o << row_ch;
                }
                __o << conner <<'\n';
            };
            auto print_row_table_cell = [&](int line){
                for(int i=0;i<table_[line].size();++i){
                    auto& cell_  = table_[line][i];
                    int space_size = cols_length[i]  - cell_.lenght();
                    int left = space_size >> 1;
                    int right = space_size - left;
                    __o <<  col_ch;
                    for(int i=1;i<=left;++i) __o << ' ' ;
                    __o << cell_ ;
                    for(int i=1;i<=right;++i) __o << ' ' ;
                }
                __o <<  col_ch << '\n';
            };

            for(int i=1;i<=rows_cnt;++i){
                print_row_table_border();
                print_row_table_cell(i-1);
            }
            print_row_table_border();
        }
        using rowType = std::vector<cell>;
        std::vector<rowType> table_;

        char conner{'+'};
        char row_ch{'-'};
        char col_ch{'|'};
        std::string padding_left{" "};
        std::string padding_right{" "};
    };



} // end namespace Tools

