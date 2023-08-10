// command.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <memory>
#include <queue>
#include <windows.h>

class Chef;



class OrderCommand {
public:
    virtual void execute() = 0;
};

class MakePasterOrderCommand : public OrderCommand {
public:
    MakePasterOrderCommand(std::shared_ptr<Chef>& chef) {
        _chef = chef;
    }

    virtual void execute() override;

private:
    std::shared_ptr<Chef> _chef;
};


class InvokerMasterChef {
public:
    void add(std::shared_ptr<OrderCommand>& order) {
        orderQueue.push(order);
    }

    void invokeByTimer() {
        orderQueue.front()->execute();
        orderQueue.pop();
    }

private:
    std::queue<std::shared_ptr<OrderCommand>> orderQueue;
};

class Chef {
public:
    void makePasta() {
        ++pasterCount;
        std::cout << pasterCount << "번째 파스타 만들어야지 ㅜ " << std::endl;
    }

private:
    int pasterCount = 0;
};

class Customer {
public:
    std::shared_ptr<OrderCommand> makeOrder(std::shared_ptr<Chef>& chef) {
        return std::make_shared<MakePasterOrderCommand>(chef);
    }
};

void MakePasterOrderCommand::execute()
{
    _chef->makePasta();
}

//int main() {
//    InvokerMasterChef masterChef;
//    std::shared_ptr<Chef> chef = std::make_shared<Chef>();
//
//    for (int index = 0; index < 100; ++index) {
//        Customer customer;
//        std::shared_ptr<OrderCommand> order = customer.makeOrder(chef);
//        masterChef.add(order);
//    }
//
//    while (true) {
//        Sleep(1000);
//        masterChef.invokeByTimer();
//    }
//
//    return 0;
//}