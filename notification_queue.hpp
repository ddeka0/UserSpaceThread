/**
 * @file notification_queue.hpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */
#pragma once
#include <thread>
#include <concepts>
#include "threadCtx.hpp"
#include <stdio.h>
#include <deque>
#include <condition_variable>

/**
 * @brief 
 * Thread safe queue, where user threads are kept
 */

class notification_queue {
private:
	std::deque<ThreadCtx*> 				_q;
	bool                                _done{false};
	std::mutex                          _mutex;
	std::condition_variable             _ready;
	using lock_t = std::unique_lock<std::mutex>;
	
public:
	void done();
	bool pop(ThreadCtx** x);
	// Test purpose ...
	std::size_t get_size();

	template<typename F>
	void push(F&& f) {
		{
			lock_t lock{_mutex};
			_q.emplace_back(std::forward<F>(f));
		}
		_ready.notify_one();
	}
};