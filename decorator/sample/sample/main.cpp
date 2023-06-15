#include <iostream>
#include <memory.h>

class Skill {
public:
    virtual void execute() = 0;
};

class BowSkill : public Skill {
public:
    virtual void execute() override {
        std::cout << "화살을 쏘았다!" << std::endl;
    }
};

class SkillDecorator : public Skill {
public:
    SkillDecorator(std::shared_ptr<Skill>& component)
        : component(component) {}

    void execute() {
        component->execute();
    }
private:
    std::shared_ptr<Skill> component;
};

class FireSkillDecorator : public SkillDecorator {
public:
    FireSkillDecorator(std::shared_ptr<Skill>& component)
        : SkillDecorator(component) {}

    void execute() {
        std::cout << "불!";
        __super::execute();
    }
};

class ReflectSkillDecorator : public SkillDecorator {
public:
    ReflectSkillDecorator(std::shared_ptr<Skill>& component)
        : SkillDecorator(component) {}

    void execute() {
        std::cout << "반사되는!";
        __super::execute();
    }
};

int main() {

    std::shared_ptr<Skill> bowSkill = std::make_shared<BowSkill>();

    int stage = 0;
    while (true) {
        int i;
        std::cin >> i;
        if (i == 0) {
            break;
        }
        else if (i == 1) {
            bowSkill = std::make_shared<FireSkillDecorator>(bowSkill);
        }
        else if (i == 2) {
            bowSkill = std::make_shared<ReflectSkillDecorator>(bowSkill);
        }

        std::cout << "스테이지:" << ++stage << std::endl;
        bowSkill->execute();
        std::cout << "=========" << std::endl;
    }
    return 0;
}