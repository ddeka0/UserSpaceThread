/**
 * @file threadCtx.cpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * 
 * @version 0.1
 * @date 2021-02-14
 */
#include "threadCtx.hpp"
#include "logger.hpp"

/** setRsp(uint64_t rsp)
 * @brief 
 *  Set the stack pointer of this thread
 * @param rsp 
 *  
 */
void ThreadCtx::setRsp(uint64_t rsp) {
    Log("rsp set = ",rsp);
    this->m_rctx.rsp = rsp;
}

/** setState(uState state)
 * @brief 
 *  Change the state of this thread
 * @param state 
 * 
 */
void ThreadCtx::setState(uState state) {
    this->m_state = state;
}

/** getState()
 * @brief  
 *  Returns the current state
 * @return uState 
 *  Returns the current state
 */
uState ThreadCtx::getState() {
    return this->m_state;
}

/** getRegCtxPtr()
 * @brief 
 *  Returns the pointer to register context
 * @return RegisterContext* 
 */
RegisterContext* ThreadCtx::getRegCtxPtr() {
    return &m_rctx;
}
