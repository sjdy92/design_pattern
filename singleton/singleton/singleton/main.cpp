#include <memory>
#include <iostream>
#include <string>

class Logger {
private:
    static std::unique_ptr<Logger> instance;

    Logger() {
        // private �����ڷ� �ܺο����� �ν��Ͻ� ���� ����
    }

public:
    static Logger* getInstance() {
        if (instance == nullptr) {
            instance.reset(new Logger());
        }

        return instance.get();
    }

    void write(std::string message) {
        // ���Ͽ� �α� �ۼ�
        std::cout << message << std::endl;
    }
};

std::unique_ptr<Logger> Logger::instance;

class Inventory {
public:
    void consumeItem(int key) {
        Logger::getInstance()->write(std::string ("�������� ���Ǿ����ϴ�. itemkey:").append(std::to_string(key)));
    }
};

int main() {

    Inventory inven;
    inven.consumeItem(1);
    inven.consumeItem(2);

    return 0;
}