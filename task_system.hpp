/**
 * @file task_system.hpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 *  Defines the thread pool mechanism and API
 * @version 0.1
 * @date 2021-02-14
 * 
 */
#pragma once
#include <vector>
#include "notification_queue.hpp"
#include "user_thread_api.hpp"
#include "logger.hpp"
#include "config.hpp"
#include <mutex>

template<typename F>
concept Invocable = std::is_invocable_v<F>;

/**
 * @brief 
 * task_system is the class for thread pool
 */
class task_system {
    private:
    const unsigned              _count{N};
    std::vector<std::thread>    _threads;
    notification_queue          _q;
    std::mutex                  _m;

    void run(unsigned i);

    public:
        task_system();
        ~task_system();
        void destruct();

        template<Invocable F>
        void submit(F &&f) {
            char* stack = new char[StackSize];
            
            if (stack == nullptr) {
                Log("Function is not submitted!");
                return;
            }
                

            *(uint64_t *)&stack[StackSize -  8] = (uint64_t)u_stop;
            *(uint64_t *)&stack[StackSize - 16] = (uint64_t)f;

            ThreadCtx* newUThread = new ThreadCtx();
            newUThread->setRsp((uint64_t)&stack[StackSize - 16]);
            newUThread->setState(uState::READY);

            _q.push(newUThread);
        }
};