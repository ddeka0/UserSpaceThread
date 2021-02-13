/**
 * @file task_system.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */

#include "config.hpp"
#include "task_system.hpp"

/**
 * @brief 
 *  Each Thread loop to get user space thread request in a queue
 * @param i 
 *  i = Thread Number
 */

void task_system::run(unsigned i) {

    currContext[KTHREAD] = new ThreadCtx();
    currContext[KTHREAD]->setState(uState::RUNNING);
    currContext[UTHREAD] = nullptr;

    while(true) {
        ThreadCtx * ctx = nullptr;
        if(!_q.pop(&ctx)) break;
        if(ctx == nullptr) {
            Log("ctx is nullptr");
        }else if(ctx->getState() != uState::COMPLETE) {
            u_yield_to(ctx);
            if(ctx->getState() != uState::COMPLETE) {
                // push tp queue again
                _q.push(ctx);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));   
            }else {
                Log("rsp = ",(uint64_t)(ctx->getRegCtxPtr()->rsp));
                auto stackbase = (char*)(ctx->getRegCtxPtr()->rsp) - StackSize;
                // delete stackbase;

                delete ctx;
            }
        }
    }

    delete currContext[KTHREAD];
}

/**
 * @brief Construct a new task system::task system object
 * 
 */
task_system::task_system() {
    for(unsigned n = 0;n != this->_count ;++n) {
        _threads.emplace_back([&,n]() {
            run(n);
            Log("work done!");
        });
    }
}

/**
 * @brief Destroy the task system object
 * 
 */
task_system::~task_system() {
    destruct();
}

/**
 * @brief 
 * 
 */
void task_system::destruct() {
    this->_q.done();      // wake up the threads
    for(auto& e : this->_threads) {
        if(e.joinable()) {
            e.join();
        }
    }
}

