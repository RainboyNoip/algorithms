//@desc 根据迭代器生成的Provider
namespace Stream {
namespace provider{

template<typename T,typename Itr>
class Iterator : public StreamProviderProxy<T> {

public:
    Iterator(Itr begin,Itr end)
        : StreamProviderProxy<T>(this),
        current_(begin),end_(end)
    {}

    std::shared_ptr<T> get_impl() {
        return std::make_shared<T>(std::move(*current_));
    }

    bool advance_impl()
    {
        if( first_ ){
            first_ = false;
            return current_ != end_;
        }
        ++current_;
        return current_ !=end_;
    }

private:
    bool first_ = true;
    Itr current_ ;
    Itr end_;

};


}// namespace provider
} // end namespace Stream

