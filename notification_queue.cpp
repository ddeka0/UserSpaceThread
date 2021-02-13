/**
 * @file notification_queue.cpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */
#include "notification_queue.hpp"
#include "logger.hpp"

/** done()
 * @brief 
 * Thread safe queue, where user threads are kept
 */
void notification_queue::done() {
    {
        lock_t lock{_mutex};
        _done = true;
    }
    _ready.notify_all();
}

/**
 * @brief  pop(ThreadCtx** x)
 * 
 * @param x 
 * @return true 
 * @return false 
 */
bool notification_queue::pop(ThreadCtx** x) {
    lock_t lock{_mutex};
    _ready.wait(lock,[this]() {
        Log("Sleeping ....TID = ",THIS_THREAD_ID);
        return !_q.empty() || _done;
    });
    if(_q.empty() || _done) {
        return false;
    }
    *x = std::move(_q.front());
    _q.pop_front();
    return true;
}

/**
 * @brief 
 * 
 * @return std::size_t 
 */
std::size_t notification_queue::get_size() {
    lock_t lock{_mutex};
    return _q.size();
}