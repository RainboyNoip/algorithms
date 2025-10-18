/**
 * 抄自 : https://github.com/arun11299/cpp-subprocess
 * @desc 提供类似于 python Popen的功能,需要c++17
 *
 * 使用手册:
 *  
 *  构造
 *      Popen("ls -l")
 *      Popen("ls","-l")
 *
 * 代码架构设计:
 *  
 *  Buffer
 *  exception
 *    1. CalledProcessError
 *    2. OSError
 *  utils
 *    1. split
 *    2. join
 *    3. set_clo_on_exec
 *    4. pip_cloexec 创建管道
 *    5. wirte_n
 *    6. read_almost_n 尽可能读取
 *    7. wait_child_exit
 *  arguments
 *      bufsize
 *      derfer_swap
 *      close_dfs
 *      string_arg
 *      excutable
 *      cwd
 *      environment
 *      input
 *      output
 *      error
 *  ArgumentDeducer
 *  Child
 *  Streams
 *  Communication
 */
#pragma once


#ifndef __SUB_PROCESS_HPP
#define __SUB_PROCESS_HPP

#include <string_view>
#include <string>
#include <map>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace rainboy {


namespace details {
    class Streams; //抽象与子进程的交互
                   
    class Streams {

    };

} // end namespace details

class Popen;

class Popen {
    private:
        int __child_pid_ = -1; // 子进程id
        bool __defer_process_start_ = false; //延迟执行
        bool __close_fds_ = false; //关闭文件描述符标记
        std::string __exe_name_; //程序名
        std::string __cwd_; //current workd directory
        std::map<std::string,std::string> __env_;
        std::string __args_;
        std::vector<std::string> __vargs_;
        std::vector<char *> __cargs_; // ?

        details::Streams __stream_;


    public:
        template<typename... Args>
        Popen(std::string_view cmd_args,Args&& ... args)
        {
            //TODO
        }

        int pid() const noexcept { return __child_pid_;}

        //发送信息
        int send(std::string_view msg);

        //创建交互
        void
            communicate(std::string_view msg);

    private:

        //初始化 命令参数
        template<typename F,typename ... Args>
        void init_args(F&& farg,Args&& ... args);

        //移动/填充 c 参数
        void populate_c_argv();
        
        //执行 子进程
        void execute_process() /*throw*/;

};

} // end namespace rainboy


#endif
