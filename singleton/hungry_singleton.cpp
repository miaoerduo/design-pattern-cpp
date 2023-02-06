#include <iostream>

class HungrySingleton {
public:
    HungrySingleton(HungrySingleton const&) = delete;
    HungrySingleton& operator=(HungrySingleton const&) = delete;

    static HungrySingleton& GetInstance() {
        static HungrySingleton instance;
        return instance;
    }
private:
    HungrySingleton() {}
};

// __init__ is used to init HungrySingleton
static int __init__ = [](){
    HungrySingleton::GetInstance();
    return 1;
}();

int main() {
    auto& ins1 = HungrySingleton::GetInstance();
    auto& ins2 = HungrySingleton::GetInstance();
    std::cout << "ins1 addr " << &ins1 << std::endl;
    std::cout << "ins2 addr " << &ins2 << std::endl;
    std::cout << "is same " << (&ins1 == &ins2) << std::endl;
}