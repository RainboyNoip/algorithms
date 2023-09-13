// 提供一些碎片化的函数/代码
/*
-- upd_min(a,b) if a > b, a =b;
-- upd_max(a,b) if a < b, a=b;
-- is_in_range(a,l,r) if a in [l,r]

-- max_val(begin,end)
-- max_pos(begin,end)
*/
#pragma once

template<typename... T>
auto maximum(T&&... args) {
    return std::max({std::forward<T>(args)...});
}

template<typename T1,typename T2>
void upd_max(T1 & t,const T2& t2){
    if(t < t2)
        t = t2;
}

template<typename T1,typename T2>
void upd_min(T1 & t,const T2& t2){
    if(t > t2)
        t = t2;
}

//用最大的那个值更新T1
template<typename T1,typename T2,typename... T3>
void upd_max(T1 & t,const T2& t2, const T3 &... t3) {
    if(t < t2)
        t = t2;
    upd_max(t,t3...);
}

template<typename T>
inline bool is_in_range(T&& a,T && l, T&& r) {
    return a >= l && a <= r;
}


// [iter l ,Iter r] ,之间的最大的位置
template<typename Iter,
    typename = std::void_t<decltype(*std::declval<Iter>(),++std::declval<Iter&>())> >
inline auto max_pos(Iter l,Iter r) {
    Iter pos = l;
    for( ; l != r; ++ l) {
        if( *pos < *l) pos = l;
    }
    return pos;
}


// [iter l ,Iter r] ,之间的最大的值
template<typename Iter,
    typename = std::void_t<decltype(*std::declval<Iter>(),++std::declval<Iter&>())> >
inline auto max_val(Iter l,Iter r) {
    return *max_pos(l,r);
}
