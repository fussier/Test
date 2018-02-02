#include <string>
#include <chrono>

typedef struct st {
    st() 
    : pstr(nullptr)
    , timestamp(0)
    {}
    std::string* pstr;
    long timestamp;
} stIns;

class Instance
{
    public:
        Instance();
        virtual ~Instance();

        stIns* get_instance();
        void init();
        void fini();
        
    private:

        stIns* a_;
        stIns* b_;

        inline void init_st(stIns* ins);
        inline void fini_st(stIns* ins);
};