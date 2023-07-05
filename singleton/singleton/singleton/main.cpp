#include <memory>
#include <iostream>
#include <string>

class Logger {
private:
    static std::unique_ptr<Logger> instance;

    Logger() {
        // private 생성자로 외부에서의 인스턴스 생성 방지
    }

public:
    static Logger* getInstance() {
        if (instance == nullptr) {
            instance.reset(new Logger());
        }

        return instance.get();
    }

    void write(std::string message) {
        // 파일에 로그 작성
        std::cout << message << std::endl;
    }
};

std::unique_ptr<Logger> Logger::instance;

class Inventory {
public:
    void consumeItem(int key) {
        Logger::getInstance()->write(std::string ("아이템이 사용되었습니다. itemkey:").append(std::to_string(key)));
    }
};

int main() {

    Inventory inven;
    inven.consumeItem(1);
    inven.consumeItem(2);

    return 0;
}