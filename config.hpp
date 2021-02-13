/**
 * @file config.hpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */
#pragma once
#include "threadCtx.hpp"

#define N   2
/**
 * @brief 
 *  Context Switch API
 */
extern "C" void ContextSwitch(RegisterContext* curr,RegisterContext* next);

/**
 * @brief 
 * Each non user space thread has this variable to know 
 * the current running thread context (user space or non user space)
 */
extern thread_local ThreadCtx* currContext[N];

/**
 * @brief 
 * Limits the size of the user thread stack
 */
extern long long StackSize;