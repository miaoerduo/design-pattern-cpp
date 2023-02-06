#include <iostream>
#include <memory>

class AbstractProduct {
public:
    virtual ~AbstractProduct() = default;
    virtual std::string GetName() = 0;
};

class ProductA : public AbstractProduct {
public:
    ProductA(): name_("A") {}
    virtual ~ProductA() = default;
    virtual std::string GetName() override {
        return this->name_;
    }
private:
    std::string name_;
};

class ProductB : public AbstractProduct {
public:
    ProductB(): name_("B") {}
    virtual ~ProductB() = default;
    virtual std::string GetName() override {
        return this->name_;
    }
private:
    std::string name_;
};

class Factory {
public:
    Factory() {}
    virtual ~Factory() = default;
    virtual std::shared_ptr<AbstractProduct> CreateProduct() = 0;
};

class FactoryA : public Factory {
public:
    FactoryA() = default;
    virtual ~FactoryA() = default;
    virtual std::shared_ptr<AbstractProduct> CreateProduct() override {
        return std::make_shared<ProductA>();
    }
};

class FactoryB : public Factory {
public:
    FactoryB() = default;
    virtual ~FactoryB() = default;
    virtual std::shared_ptr<AbstractProduct> CreateProduct() override {
        return std::make_shared<ProductB>();
    }
};

int main() {
    Factory *factory = new FactoryA();
    auto product_a = factory->CreateProduct();
    delete factory;
    factory = new FactoryB();
    auto product_b = factory->CreateProduct();
    delete factory;

    std::cout << "product_a " << product_a->GetName() << std::endl;
    std::cout << "product_b " << product_b->GetName() << std::endl;
}