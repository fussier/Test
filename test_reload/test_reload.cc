#include <iostream>
#include <thread>
#include <string>
#include "instance.h"

Instance a;

void func()
{
    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        a.init();  
    }
}

int main(int argc, char* argv[])
{
    std::thread t_reload(func);
    a.init();

    while(1) {    
        std::cout << *(a.get_instance()->pstr) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    t_reload.join();

    return 0;
}
