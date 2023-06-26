/**
 *  使用方法
 *  Rf>10 创建一个Range(1,10)
 *  Rf<10 创建一个Range(10,1)
 *  Rf0>10 创建一个Range(0,10)
 *  Rf0<10 创建一个Range(10,0)
 *  Rf1>10 创建一个Range(1,10)
 *  Rf1<10 创建一个Range(10,1)
 *  int n = 10;
 *  FOR(i, Range(1, n)) {
 *      std::cout << "Iteration: " << i << std::endl;
 *      // 在此处编写要执行的代码
 *  }
 *
 */
    
    
    
    
    
class Range {
public:
    Range(int start, int end,int step) : start_(start), end_(end) ,step_(step){}
    Range(int start, int end) : Range(start,end,start < end ? 1 : -1) {}
    Range(int end):Range(1,end) {}

    struct END { int end_;};

    class Iterator {
    public:
        Iterator(int value,int step) 
            : value_(value) ,step_(step)
        {}

        int operator*() const {
            return value_;
        }

        void operator++() {
            value_+=step_;
        }

        bool operator!=(const Iterator& other) const {
            return value_ != other.value_;
        }

        bool operator!=(const END& other) const {
            if( step_ > 0 && value_ > other.end_) //没有超过end
                return 0; //就是不相等
            if( step_ < 0 && value_ < other.end_) //没有超过end
                return 0; //就是不相等
            return 1;
        }

    private:
        int value_;
        int step_;
    };


    Iterator begin() const {
        return Iterator(start_,step_);
    }

    END end() const {
        return {end_};
    }
private:
    int start_;
    int end_;
    int step_;
};

using R = Range;

//Range工厂类 
template<int start_>
struct RangeFactory {
    Range operator()(int end) {
        return Range(start_,end,1);
    }

    // start_->end
    Range operator>(int end) {
        return Range(start_,end,1);
    }

    // n->start_
    Range operator<(int begin) {
        return Range(begin,start_,-1);
    }
};

constexpr RangeFactory<1> Rf;
constexpr RangeFactory<0> Rf0;
constexpr RangeFactory<1> Rf1;

#ifndef FOR
#define FOR(i, range) \
    for (auto i : range)
#else
    static_assert(0,"Macro FOR already defined!");
#endif

