#include <iostream>

// ÄÜ¼¾Æ®
class PowerSocket {

public:
    PowerSocket(int volt, int shape) 
        :_volt(volt), _shape(shape)
    {}

    void plugIn(int volt, int shape) {
        if (shape != _shape || volt != _volt) {
            explode();
            return;
        }

        if (volt != 220 && volt != 110) {
            explode();
            return;
        }
        else if (volt == 220) {
            if (shape != 12345) {
                explode();
                return;
            }
        }
        else {
            if (shape != 654321) {
                explode();
                return;
            }
        }

        // Àü±â°¡ Èê·¯¶ó
        std::cout << "Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´Âî¸´!." << _volt << "," << _shape << std::endl;
    }

    virtual bool is220() { return false; }

private:
    void explode() {
        std::cout << "Æø¹ß Çß½À¤¤µð¤¿." << std::endl;
        delete this;
    }

    int _volt;
    int _shape;
};

class PowerSocket220 : public PowerSocket {
public:
    PowerSocket220() : PowerSocket(220, 12345) {}
    virtual bool is220() override { return true; }
};

class IPowerAdapter {
public:
    IPowerAdapter(PowerSocket* powerSocket) {
        _powerSocket = powerSocket;
    }
    virtual bool plugIn() = 0;

protected:
    PowerSocket* _powerSocket;
};

class SquarePowerAdapter_220 : public IPowerAdapter {
public:
    SquarePowerAdapter_220(PowerSocket* powerSocket) 
        :IPowerAdapter(powerSocket){}

    virtual bool plugIn() override {
        if (_powerSocket != nullptr 
            && _powerSocket->is220()) {
            _powerSocket->plugIn(220, 12345);
            return true;
        }
        return false;
    }
};

class CirclePowerSocketAdapter_110 : public IPowerAdapter {
public:
    CirclePowerSocketAdapter_110(PowerSocket* powerSocket)
        :IPowerAdapter(powerSocket) {}

    virtual bool plugIn() override {
        if (_powerSocket != nullptr
            && !_powerSocket->is220()) {
            _powerSocket->plugIn(110, 654321);
            return true;
        }
        return false;
    }
};
//
//int main() {
//    PowerSocket* _powerSocket = new PowerSocket220();
//    IPowerAdapter* adapter = new SquarePowerAdapter_220(_powerSocket);
//    adapter->plugIn();
//    adapter = new CirclePowerSocketAdapter_110(_powerSocket);
//    adapter->plugIn();
//    _powerSocket->plugIn(2, 3);
//
//    adapter = new SquarePowerAdapter_220(_powerSocket);
//    adapter->plugIn();
//
//    return 0;
//};