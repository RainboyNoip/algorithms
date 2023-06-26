#ifdef LOG_TRACE
//使用方法见 https://blog.roj.ac.cn/学习笔记/tinyasync/first.html

#include <cstdio>
#include <cstdarg>

#include <string>
#include <string_view>
#include <vector>
#include <map>

#define LOG_CAT_(a, b) a##b
#define LOG_CAT(a, b) LOG_CAT_(a, b)
#define LOG_GUARD(...) log_prefix_guad LOG_CAT(log_prefix_guad_, __LINE__)(__VA_ARGS__)
#define LOG_LOG(...) \
    do                     \
    {                      \
        log(__VA_ARGS__);  \
        printf("\n");      \
    } while (0)
#define LOG_LOG_NNL(...) log(__VA_ARGS__)



    inline std::vector<std::string> log_prefix;

    struct log_prefix_guad
    {
        std::size_t l;

        log_prefix_guad(char const *fmt, ...) : l(0)
        {

            char buf[1000];
            va_list args;
            va_start(args, fmt);
            vsnprintf(buf, 1000, fmt, args);
            va_end(args);

            buf[1000 - 1] = 0;

            l = log_prefix.size();

            log_prefix.emplace_back(buf);
        }

        ~log_prefix_guad()
        {
            printf(">>>>>>>>>");
            printf("l=%d,",l);
            printf("\n");
            printf("size %d,",log_prefix.size());
            if (l < log_prefix.size())
            {
                log_prefix.resize(l);
            }
        }
    };

    inline void log(char const *fmt, ...)
    {
        for (auto &p : log_prefix)
        {
            printf("%s", p.c_str());
        }
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }

#else

#define LOG_LOG(...) \
    do                     \
    {                      \
    } while (0)


    struct log_prefix_guad
    {
        log_prefix_guad(std::string_view)
        {
        }
    };

    inline void log(char const *fmt, ...)
    {
    }


#define LOG_GUARD(...) \
    do                       \
    {                        \
    } while (0)
#define LOG_LOG(...) \
    do                     \
    {                      \
    } while (0)
#define LOG_LOG_NNL(...) \
    ldo {}                     \
    while (0)

#endif // LOG_TRACE
