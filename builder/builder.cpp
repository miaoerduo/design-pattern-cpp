#include <iostream>
#include <memory>

class Product {
public:
    Product() = default;
    ~Product() = default;

    void MakeA(const std::string &data) { this->part_a_ = data; }
    void MakeB(const std::string &data) { this->part_b_ = data; }
    void MakeC(const std::string &data) { this->part_c_ = data; }

    std::string Get() {
        return this->part_a_ + " " + this->part_b_ + " " + this->part_c_;
    }

private:
    std::string part_a_;
    std::string part_b_;
    std::string part_c_;
};

class Builder {
public:
    Builder() = default;
    virtual ~Builder() = default;

    virtual void SetPartA(const std::string &data) = 0;
    virtual void SetPartB(const std::string &data) = 0;
    virtual void SetPartC(const std::string &data) = 0;

    virtual std::shared_ptr<Product> GetProduct() = 0;
};

class Director {
public:
    Director() = default;

    void SetBuilder(std::shared_ptr<Builder> builder) {
        this->builder_ = std::move(builder);
    }

    bool Construct() {
        if (this->builder_ == nullptr) {
            return false;
        }
        this->builder_->SetPartA("Head");
        this->builder_->SetPartB("Body");
        this->builder_->SetPartC("Tail");
        return true;
    }

    std::shared_ptr<Product> GetProduct() {
        return this->builder_->GetProduct();
    }
private:
    std::shared_ptr<Builder> builder_ = nullptr;
};

class ConcreteBuilderA : public Builder {
public:
    ConcreteBuilderA() = default;
    virtual ~ConcreteBuilderA() = default;

    virtual void SetPartA(const std::string &data) {
        this->part_a_ = data + "-A";
    }
    virtual void SetPartB(const std::string &data) {
        this->part_b_ = data + "-A";
    }
    virtual void SetPartC(const std::string &data) {
        this->part_c_ = data + "-A";
    }

    virtual std::shared_ptr<Product> GetProduct() {
        auto product = std::make_shared<Product>();
        product->MakeA(this->part_a_);
        product->MakeB(this->part_b_);
        product->MakeC(this->part_c_);
        return product;
    }

private:
    std::string part_a_;
    std::string part_b_;
    std::string part_c_;
};

class ConcreteBuilderB : public Builder {
public:
    ConcreteBuilderB() = default;
    virtual ~ConcreteBuilderB() = default;

    virtual void SetPartA(const std::string &data) {
        this->part_a_ = data + "-B";
    }
    virtual void SetPartB(const std::string &data) {
        this->part_b_ = data + "-B";
    }
    virtual void SetPartC(const std::string &data) {
        this->part_c_ = data + "-B";
    }

    virtual std::shared_ptr<Product> GetProduct() {
        auto product = std::make_shared<Product>();
        product->MakeA(this->part_a_);
        product->MakeB(this->part_b_);
        product->MakeC(this->part_c_);
        return product;
    }

private:
    std::string part_a_;
    std::string part_b_;
    std::string part_c_;
};


int main() {
    Director director;
    director.SetBuilder(std::make_shared<ConcreteBuilderA>());
    director.Construct();
    auto product_a = director.GetProduct();

    director.SetBuilder(std::make_shared<ConcreteBuilderB>());
    director.Construct();
    auto product_b = director.GetProduct();

    std::cout << product_a->Get() << std::endl;
    std::cout << product_b->Get() << std::endl;
}