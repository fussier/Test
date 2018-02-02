#include "instance.h"

Instance::Instance() 
{
    a_ = new stIns();
    b_ = new stIns();
}

Instance::~Instance()
{
    delete a_;
    delete b_;
}

void Instance::init()
{
    if (nullptr == a_) {
        init_st(a_);
    } 

    if (nullptr == b_) {
        init_st(b_);
    }
    
    if (a_->timestamp > b_->timestamp) {
        fini_st(b_);
        init_st(b_);
    } else {
        fini_st(a_);
        init_st(a_);
    }
}

void Instance::fini()
{
    if (a_) {
        fini_st(a_);
    }

    if (b_) {
        fini_st(b_);
    }
}

stIns* Instance::get_instance()
{
    if (b_ == nullptr) {
        return a_;
    }

    return a_->timestamp > b_->timestamp ? a_ : b_;
}

inline void Instance::init_st(stIns* ins) {
    std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
    time_t time_stamp = std::chrono::system_clock::to_time_t(timestamp);

    ins->pstr = new std::string(std::to_string(time_stamp));
    ins->timestamp = time_stamp;
}

inline void Instance::fini_st(stIns* ins) {
    if (ins->pstr) {
        delete ins->pstr;
        ins->pstr = nullptr;
    }
}