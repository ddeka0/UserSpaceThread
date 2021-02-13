/**
 * @file u_util.hpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */
#pragma once

#include <stdint.h> 

#define KTHREAD     0
#define UTHREAD     1

#define THIS_THREAD_ID std::this_thread::get_id()

/**
 * @brief 
 * 
 */
class RegisterContext {
public:
    uint64_t rsp = 0;
    uint64_t r15 = 0;
    uint64_t r14 = 0;
    uint64_t r13 = 0;
    uint64_t r12 = 0;
    uint64_t rbx = 0;
    uint64_t rbp = 0;
};

/**
 * @brief 
 * 
 */
enum class uState : unsigned char {
    INVALID,
    READY,
    RUNNING,
    COMPLETE
};