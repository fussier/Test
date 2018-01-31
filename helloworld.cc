#include <iostream>
#include <list>
#include <string>

typedef struct retry_elem_s {
    retry_elem_s(std::string* param_msg)
        : num_retry(0)
        , msg(param_msg)
    {}

    int num_retry;
    std::string* msg;
} stRetryElem_t;

std::list<stRetryElem_t*> list_retry_;

int main(int argc, char* argv[])
{
    for(int i = 0; i < 10; ++i) {
        stRetryElem_t* st_retry = new stRetryElem_t(&std::to_string(i));
        list_retry_.push_back(st_retry);
    }

    while(true) {
    for (std::list<stRetryElem_t*>::iterator iter = list_retry_.begin(); iter != list_retry_.end(); ) {
        if ((*iter) == nullptr || ((*iter)->msg) == nullptr) continue;

        Job job;
        ret = job.exec((*iter)->msg);

        if (ATHENA_SUCCESS == ret) {
            delete (*iter)->msg;
            (*iter)->msg = nullptr;

            delete (*iter);
            (*iter) = nullptr;
            
            iter = list_retry_.erase(iter);
        } else {
            (*iter)->num_retry++;

            if ((*iter)->num_retry > 3) {
                delete (*iter)->msg;
                (*iter)->msg = nullptr;

                delete (*iter);
                (*iter) = nullptr;

                iter = list_retry_.erase(iter);
            } else {
                ++iter;
            }
        }
    }
    }

    return 0;
}
