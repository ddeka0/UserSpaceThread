/**
 * @file main.cpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */

#include <bits/stdc++.h>
#include "task_system.hpp"
#include "config.hpp"
#include "logger.hpp"
#include <chrono>

thread_local ThreadCtx* currContext[N];
long long StackSize = 0x400000;

void func() {

    Log("TID before yield = ",THIS_THREAD_ID);
    
    u_yield();

    Log("TID After yield = ",THIS_THREAD_ID);

    Log("Hello from func!");
}

int main(int argc,char *argv[]) {

    task_system ts;

    ts.submit(func);

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));   

}