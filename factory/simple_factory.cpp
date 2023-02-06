#include <iostream>
#include <memory>

class AbstractProduct {
public:
    AbstractProduct() = default;
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
    Factory() = default;
    std::shared_ptr<AbstractProduct> CreateProduct(const std::string &type) {
        if (type == "A") {
            return std::make_shared<ProductA>();
        }
        if (type == "B") {
            return std::make_shared<ProductB>();
        }
        return  nullptr;
    }
};

int main() {
    Factory factory;
    auto product_a = factory.CreateProduct("A");
    auto product_b = factory.CreateProduct("B");
    auto product_not_exist = factory.CreateProduct("not_exist");
    std::cout << "product_a " << product_a->GetName() << std::endl;
    std::cout << "product_b " << product_b->GetName() << std::endl;
    std::cout << "product_not_exist " << product_not_exist << std::endl;
}