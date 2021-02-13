/**
 * @file user_thread_api.hpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */

#pragma once

#include <iostream>
#include "threadCtx.hpp"

bool u_yield();
bool u_yield_to(ThreadCtx* next);
void u_stop();