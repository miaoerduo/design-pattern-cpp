#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

// Adaptee --> Adapter --> Target

// Target: Set
class Target {
public:
    Target() = default;
    virtual ~Target() = default;
    virtual void Insert(int data) = 0;
    virtual bool Has(int data) = 0;
    virtual void Erase(int data) = 0;
};

// Adaptee: Array
using Array = std::vector<int>;

// Adapter: from Array to Set
class Adapter: public Target {
public:
    Adapter() = default;
    virtual ~Adapter() = default;
    virtual void Insert(int data) {
        if (!this->Has(data)) {
            this->array_.push_back(data);
        }
    }
    virtual bool Has(int data) {
        return std::find(this->array_.begin(), this->array_.end(), data) != this->array_.end();
    }
    virtual void Erase(int data) {
        auto it = std::remove(this->array_.begin(), this->array_.end(), data);
        this->array_.resize(it - this->array_.begin());
    }
private:
    Array array_;
};

int main() {
    std::shared_ptr<Target> target = std::make_shared<Adapter>();

    target->Insert(10);
    target->Insert(20);
    std::cout << target->Has(10) << std::endl;
    std::cout << target->Has(20) << std::endl;
    std::cout << target->Has(30) << std::endl;

    target->Erase(10);
    std::cout << target->Has(10) << std::endl;
    std::cout << target->Has(20) << std::endl;
    std::cout << target->Has(30) << std::endl;
}