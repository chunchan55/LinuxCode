#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

int main()
{

    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
          pool.enqueue([i] {
            std::cout << "hello " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world " << i << std::endl;
            return i*i;
        })
      );
    }

    for(auto && result: results)    //通过future.get()获取返回值
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}

---------------------

本文来自 沉默的影魔 的CSDN 博客 ，全文地址请点击：https://blog.csdn.net/gcola007/article/details/78750220?utm_source=copy 