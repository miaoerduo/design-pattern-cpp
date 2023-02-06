#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <algorithm>

class Subject;

class Observer {
public:
    Observer() = default;
    virtual void Update(Subject &subject) = 0;
};

class Subject {
public:
    Subject() = default;
    virtual ~Subject() = default;
    void RegisterObserver(std::shared_ptr<Observer> observer) {
        std::lock_guard<std::mutex> lock(this->mutex_);
        auto it = std::find(this->observer_list_.begin(), this->observer_list_.end(), observer);
        if (it == this->observer_list_.end()) {
            this->observer_list_.push_back(std::move(observer));
        }
    }
    void RemoveObserver(std::shared_ptr<Observer> observer) {
        std::lock_guard<std::mutex> lock(this->mutex_);
        auto new_end = std::remove(this->observer_list_.begin(), this->observer_list_.end(), observer);
        this->observer_list_.resize(new_end - this->observer_list_.begin());
    }
    void NotifyObservers() {
        std::lock_guard<std::mutex> lock(this->mutex_);
        for (auto &&observer : this->observer_list_) {
            observer->Update(*this);
        }
    }

    // you can define any kind of status, here it's int
    virtual int GetStatus() = 0;
    virtual void SetStatus(int status) = 0;

private:
    std::vector<std::shared_ptr<Observer>> observer_list_;
    std::mutex mutex_;
};

class ConcreteSubject : public Subject {
public:
    ConcreteSubject() = default;
    virtual ~ConcreteSubject() = default;
    virtual int GetStatus() override {
        std::lock_guard<std::mutex> lock(this->mutex_);
        return this->status_;
    }
    virtual void SetStatus(int status) override {
        std::lock_guard<std::mutex> lock(this->mutex_);
        this->status_ = status;
        this->NotifyObservers();
    }
private:
    int status_;
    std::mutex mutex_;
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(std::string name): name_(std::move(name)) {}
    virtual ~ConcreteObserver() = default;
    virtual void Update(Subject &subject) override {
        std::cout << this->name_ << " update " << subject.GetStatus() << std::endl;
    }
private:
    std::string name_;
};

int main() {
    auto ob1 = std::make_shared<ConcreteObserver>("ob1");
    auto ob2 = std::make_shared<ConcreteObserver>("ob2");

    auto subject = std::make_shared<ConcreteSubject>();

    subject->RegisterObserver(ob1);
    subject->RegisterObserver(ob2);

    subject->SetStatus(100); // both ob1 and ob2 will update

    subject->RemoveObserver(ob1);
    subject->SetStatus(200); // only ob2 will update
}