/**
 *  使用方法
 *  R>10 创建一个Range(1,10)
 *  R<10 创建一个Range(10,1)
 *  R0>10 创建一个Range(0,10)
 *  R0<10 创建一个Range(10,0)
 *  R1>10 创建一个Range(1,10)
 *  R1<10 创建一个Range(10,1)
 *  Range(2,10) 创建一个Range(2,10)
 *  Range(2,10,2) 创建一个[2,4,6,8,10]
 *  int n = 10;
 *
 *  ra = Range ra 是Range的缩写
 *
 *  还有一个FOR宏
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

using ra = Range;

//Range工厂类 
template<int start_>
struct RangeFactory {
    Range operator()(int end) {
        return Range(start_,end,1);
    }

    // start_->end
    Range operator>(int end) const{
        return Range(start_,end,1);
    }

    // n->start_
    Range operator<(int begin) const{
        return Range(begin,start_,-1);
    }
};

constexpr RangeFactory<1> R;
constexpr RangeFactory<0> R0;
constexpr RangeFactory<1> R1;

