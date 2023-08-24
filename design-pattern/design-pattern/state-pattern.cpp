#include <windows.h>
#include <vector>
#include <iostream>

class State {
public:
    virtual void process() = 0;
protected:
    void print(const char* str) {
        std::cout << str << std::endl;
    }
};

class FetchState : public State {
    virtual void process() override {
        print("�������Ϳ��� �޸𸮸� ���� �ɴϴ�.");
    }
};

class DecodeState : public State {
    void process() {
        print("��ɾ �ؼ��մϴ�.");
    }
};

class ExecutionState : public State {
    void process() {
        print("��ɾ �����մϴ�.");
    }
};

class CPUContext {
public:
    void changeState(State* state) {
        cpuState = state;
    }

    void process() {
        cpuState->process();
    }
private:
    State* cpuState;
};

int main() {
    CPUContext cpu;
    State* states [] = {new FetchState(), new DecodeState(), new ExecutionState()};
    int index = 0;
    while (true)
    {
        Sleep(1000);
        cpu.changeState(states[index]);
        cpu.process();
        index = (index + 1) % (sizeof(states) / sizeof(State*));
    }

    return 0;
}