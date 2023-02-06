#include <iostream>

class LazySingleton {
public:
    LazySingleton(LazySingleton const&) = delete;
    LazySingleton& operator=(LazySingleton const&) = delete;

    static LazySingleton& GetInstance() {
        static LazySingleton instance;
        return instance;
    }
private:
    LazySingleton() {}
};

int main() {
    auto& ins1 = LazySingleton::GetInstance();
    auto& ins2 = LazySingleton::GetInstance();
    std::cout << "ins1 addr " << &ins1 << std::endl;
    std::cout << "ins2 addr " << &ins2 << std::endl;
    std::cout << "is same " << (&ins1 == &ins2) << std::endl;
}