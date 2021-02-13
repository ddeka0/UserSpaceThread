/**
 * @file user_thread.cpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */
#include "user_thread_api.hpp"
#include "threadCtx.hpp"
#include "logger.hpp"
#include "config.hpp"
#include <thread>
#include <unordered_map>

/** u_yield_to(ThreadCtx* nextThread)
 * @brief 
 *  Current pthread yields control to a user space thread
 * @param nextThread 
 *  next thread context to load from
 * @return true 
 *  Context Switch is done properly
 * @return false 
 *  Error while context switch
 */
bool u_yield_to(ThreadCtx* nextThread) {
	PrintF
    
    currContext[KTHREAD]->setState(uState::READY);
    auto currRegCtx = currContext[KTHREAD]->getRegCtxPtr();
    nextThread->setState(uState::RUNNING);

    auto nextRegCtx = nextThread->getRegCtxPtr();

    currContext[UTHREAD] = nextThread;

    Log("Calling ContextSwitch");

	ContextSwitch(currRegCtx,nextRegCtx);
    
    Log("TID = ",THIS_THREAD_ID);

	return true;
}

/** u_yield()
 * @brief 
 * An user thread is going to yield to a pthread
 * @return true 
 * @return false 
 */
bool u_yield() {
	PrintF

    currContext[UTHREAD]->setState(uState::READY);
    auto currRegCtx = currContext[UTHREAD]->getRegCtxPtr();

    currContext[KTHREAD]->setState(uState::RUNNING);

    auto nextRegCtx = currContext[KTHREAD]->getRegCtxPtr();


    Log("Calling ContextSwitch");

	ContextSwitch(currRegCtx,nextRegCtx);

    Log("TID = ",THIS_THREAD_ID);

	return true;
}

/** u_stop()
 * @brief 
 * Marks the end of this user space thread and yield to a pthread
 */
void u_stop() {
    PrintF;

    currContext[UTHREAD]->setState(uState::COMPLETE);

    auto currRegCtx = currContext[UTHREAD]->getRegCtxPtr();

    currContext[KTHREAD]->setState(uState::RUNNING);

    auto nextRegCtx = currContext[KTHREAD]->getRegCtxPtr();


    Log("Calling ContextSwitch");

	ContextSwitch(currRegCtx,nextRegCtx);

    Log("TID = ",THIS_THREAD_ID);

}
