/**
 * @file threadCtx.hpp
 * @author d.deka (https://ddeka0.github.io/)
 * @brief 
 * @version 0.1
 * @date 2021-02-14
 * 
 */
#pragma once
#include "u_util.hpp"

/**
 * @brief 
 * 
 */
class ThreadCtx {
public:
    void setRsp(uint64_t rsp);
    void setState(uState state);
    uState getState();
    RegisterContext* getRegCtxPtr();
    RegisterContext m_rctx;
    uState m_state = uState::INVALID;
};