#include <iostream>
#include <memory>
#include <unordered_map>

// Command
class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    virtual void Execute() = 0;
};

// Light: Receiver and Command
class Light {
public:
    void On() {
        std::cout << "Light On" << std::endl;
    }
    void Off() {
        std::cout << "Light Off" << std::endl;
    }
};

class LightOnCommand : public Command {
public:
    LightOnCommand(std::shared_ptr<Light> light): light_(light) {}
    virtual ~LightOnCommand() = default;
    virtual void Execute() override {
        this->light_->On();
    }
private:
    std::shared_ptr<Light> light_ = nullptr;
};

class LightOffCommand : public Command {
public:
    LightOffCommand(std::shared_ptr<Light> light): light_(light) {}
    virtual ~LightOffCommand() = default;
    virtual void Execute() override {
        this->light_->Off();
    }
private:
    std::shared_ptr<Light> light_ = nullptr;
};

// Stereo: Receiver and Command
class Stereo {
public:
    void SetCD() {
        std::cout << "Stereo SetCD" << std::endl;
    }
    void Play() {
        std::cout << "Stereo Play" << std::endl;
    }
    void Stop() {
        std::cout << "Stereo Stop" << std::endl;
    }
};

class StereoOnCommand : public Command {
public:
    StereoOnCommand(std::shared_ptr<Stereo> stereo): stereo_(stereo) {}
    virtual ~StereoOnCommand() = default;
    virtual void Execute() override {
        this->stereo_->SetCD();
        this->stereo_->Play();
    }
private:
    std::shared_ptr<Stereo> stereo_ = nullptr;
};

class StereoOffCommand : public Command {
public:
    StereoOffCommand(std::shared_ptr<Stereo> stereo): stereo_(stereo) {}
    virtual ~StereoOffCommand() = default;
    virtual void Execute() override {
        this->stereo_->Stop();
    }
private:
    std::shared_ptr<Stereo> stereo_ = nullptr;
};

// Invoker
class Invoker {
public:
    void SetCommand(int slot, std::shared_ptr<Command> command) {
        this->command_map_[slot] = command;
    }
    void Do(int slot) {
        auto it = this->command_map_.find(slot);
        if (it != this->command_map_.end()) {
            it->second->Execute();
        }
    }
private:
    std::unordered_map<int, std::shared_ptr<Command>> command_map_;
};

int main() {
    auto light = std::make_shared<Light>();
    auto lightOnCommand = std::make_shared<LightOnCommand>(light);
    auto lightOFFCommand = std::make_shared<LightOffCommand>(light);

    auto stereo = std::make_shared<Stereo>();
    auto stereoOnCommand = std::make_shared<StereoOnCommand>(stereo);
    auto stereoOFFCommand = std::make_shared<StereoOffCommand>(stereo);

    Invoker invoker;
    invoker.SetCommand(0, lightOnCommand);
    invoker.SetCommand(1, lightOFFCommand);
    invoker.SetCommand(2, stereoOnCommand);
    invoker.SetCommand(3, stereoOFFCommand);

    invoker.Do(0); // turn on light
    invoker.Do(2); // turn on stereo
    invoker.Do(1); // turn off light
    invoker.Do(3); // turn off stereo
}