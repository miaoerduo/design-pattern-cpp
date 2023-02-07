#include <iostream>
#include <memory>
#include <string>

class Component {
public:
    Component() = default;
    virtual ~Component() = default;
    virtual std::string MethodA() = 0;
    virtual std::string MethodB() = 0;
};

class Decorator : public Component {
public:
    Decorator(std::shared_ptr<Component> component): Component() {}
    virtual ~Decorator() = default;
    virtual std::string MethodA() = 0;
    virtual std::string MethodB() = 0;
};

class ConcreteComponent : public Component {
public:
    ConcreteComponent(const std::string& name): Component(), name_(name) {}
    virtual ~ConcreteComponent() = default;
    virtual std::string MethodA() override {
        return this->name_ + "-MethodA";
    }
    virtual std::string MethodB() override {
        return this->name_ + "-MethodB";
    }

private:
    std::string name_;
};

class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(std::shared_ptr<Component> component): Decorator(component), component_(std::move(component)) {}
    virtual ~ConcreteDecoratorA() = default;
    virtual std::string MethodA() override {
            return "[" + this->component_->MethodA() + "]";
    }
    virtual std::string MethodB() override {
        return "[" + this->component_->MethodB() + "]";
    }
private:
    std::shared_ptr<Component> component_ = nullptr;
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(std::shared_ptr<Component> component): Decorator(component), component_(std::move(component)) {}
    virtual ~ConcreteDecoratorB() = default;
    virtual std::string MethodA() override {
        return "-->" + this->component_->MethodA() + "<--";
    }
    virtual std::string MethodB() override {
        return "-->" + this->component_->MethodB() + "<--";
    }
private:
    std::shared_ptr<Component> component_ = nullptr;
};

int main() {
    std::shared_ptr<Component> component = std::make_shared<ConcreteComponent>("component");
    // decorator
    component = std::make_shared<ConcreteDecoratorA>(component);
    component = std::make_shared<ConcreteDecoratorA>(component);
    component = std::make_shared<ConcreteDecoratorB>(component);

    std::cout << component->MethodA() << std::endl;
    std::cout << component->MethodB() << std::endl;
}