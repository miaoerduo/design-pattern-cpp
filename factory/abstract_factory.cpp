#include <iostream>
#include <memory>

class AbstractProduct {
public:
    virtual ~AbstractProduct() = default;
    virtual std::string GetName() = 0;
};

class ProductA1 : public AbstractProduct {
public:
    ProductA1(): name_("A1") {}
    virtual ~ProductA1() = default;
    virtual std::string GetName() override {
        return this->name_;
    }
private:
    std::string name_;
};

class ProductA2 : public AbstractProduct {
public:
    ProductA2(): name_("A2") {}
    virtual ~ProductA2() = default;
    virtual std::string GetName() override {
        return this->name_;
    }
private:
    std::string name_;
};

class ProductB1 : public AbstractProduct {
public:
    ProductB1(): name_("B1") {}
    virtual ~ProductB1() = default;
    virtual std::string GetName() override {
        return this->name_;
    }
private:
    std::string name_;
};

class ProductB2 : public AbstractProduct {
public:
    ProductB2(): name_("B2") {}
    virtual ~ProductB2() = default;
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
    virtual std::shared_ptr<AbstractProduct> CreateProductV1() = 0;
    virtual std::shared_ptr<AbstractProduct> CreateProductV2() = 0;
};

class FactoryA : public Factory {
public:
    FactoryA() = default;
    virtual ~FactoryA() = default;
    virtual std::shared_ptr<AbstractProduct> CreateProductV1() override {
        return std::make_shared<ProductA1>();
    }
    virtual std::shared_ptr<AbstractProduct> CreateProductV2() override {
        return std::make_shared<ProductA2>();
    }
};

class FactoryB : public Factory {
public:
    FactoryB() = default;
    virtual ~FactoryB() = default;
    virtual std::shared_ptr<AbstractProduct> CreateProductV1() override {
        return std::make_shared<ProductB1>();
    }
    virtual std::shared_ptr<AbstractProduct> CreateProductV2() override {
        return std::make_shared<ProductB2>();
    }
};

int main() {
    Factory *factory = new FactoryA();
    auto product_a1 = factory->CreateProductV1();
    auto product_a2 = factory->CreateProductV2();
    delete factory;
    factory = new FactoryB();
    auto product_b1 = factory->CreateProductV1();
    auto product_b2 = factory->CreateProductV2();
    delete factory;

    std::cout << "product_a1 " << product_a1->GetName() << std::endl;
    std::cout << "product_a2 " << product_a2->GetName() << std::endl;
    std::cout << "product_b1 " << product_b1->GetName() << std::endl;
    std::cout << "product_b2 " << product_b2->GetName() << std::endl;
}