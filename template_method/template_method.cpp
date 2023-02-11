#include <iostream>

class AbstractClass {
public:
    AbstractClass() = default;
    virtual ~AbstractClass() = default;
    void Run() {
        this->PreProcess();
        this->Process();
        this->PostProcess();
    }
    virtual void PreProcess() {
        std::cout << "start" << std::endl;
    }
    virtual void Process() = 0;
    virtual void PostProcess() {
        std::cout << "end" << std::endl;
    }
};

class ConcreteClass : public AbstractClass {
public:
    ConcreteClass() = default;
    virtual ~ConcreteClass() = default;
    virtual void PreProcess() override {
        std::cout << "start ConcreteClass" << std::endl;
    }
    virtual void Process() override {
        std::cout << "Processing" << std::endl;
    }
};

int main() {
    ConcreteClass c;
    c.Run();
}
