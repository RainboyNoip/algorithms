//过滤器
namespace Stream {
namespace provider{

template<typename T,typename Predicate>
class filter : public StreamProviderProxy<T> {

public:
    filter(StreamProviderPtr<T> source , Predicate&& predicate)
        : StreamProviderProxy<T>(this),
        source_(std::move(source)),
        predicate_(std::move(predicate))
    {}


    bool advance_impl() {
        while(source_->advance()){
            current_ = source_ -> get();
            if( predicate_(*current_))
                return true;

        }
        current_.reset();
        return false;
    }

    std::shared_ptr<T> get_impl() {
        return current_;
    }

private:
    StreamProviderPtr<T> source_;
    Predicate predicate_;
    std::shared_ptr<T> current_;
};

}// namespace provider
} // end namespace Stream
