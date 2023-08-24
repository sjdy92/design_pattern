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
        print("레지스터에서 메모리를 갖고 옵니다.");
    }
};

class DecodeState : public State {
    void process() {
        print("명령어를 해석합니다.");
    }
};

class ExecutionState : public State {
    void process() {
        print("명령어를 실행합니다.");
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