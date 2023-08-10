#include <iostream>
#include <string>

class CalculatorTemplate {
public:
    int caculate(int num1, int num2) {
        input(num1, num2);
        int result = doOperation(num1, num2);
        display(result);
        return result;
    }

private:
    // 추상 메소드: 서브클래스에서 구현해야 할 메소드들
    virtual void input(int num1, int num2) = 0;
    virtual int doOperation(int num1, int num2) = 0;
    virtual void display(int result) = 0;
};

class AdditionCalculator : public CalculatorTemplate {
private:
    virtual void input(int num1, int num2) {
        std::cout << num1 << " + " << num2 << " ";
    }

    virtual int doOperation(int num1, int num2) {
        return num1 + num2;
    }

    virtual void display(int result) {
        std::cout << " Result: " << result;
    }
};

class SubtractionCalculator : public CalculatorTemplate {
private:
    virtual void input(int num1, int num2) {
        std::cout << num1 << " - " << num2 << " ";
    }

    virtual int doOperation(int num1, int num2) {
        return num1 - num2;
    }

    virtual void display(int result) {
        std::cout << " Result: " << result;
    }
};

int main() {
    int operand1;
    int operand2;
    CalculatorTemplate* calculator = nullptr;
    while (true)
    {
        std::string input;
        std::cin >> input;
        
        try {
            int result = std::stoi(input);
            if (nullptr == calculator)
                operand1 = result;
            else
                operand2 = result;
        }
        catch (const std::invalid_argument& e) {
            if ('+' == input[0])
            {
                calculator = new AdditionCalculator();
            }
            else if ('-' == input[0])
            {
                calculator = new SubtractionCalculator();
            }
            else if ('=' == input[0])
            {
                calculator->caculate(operand1, operand2);
                calculator = nullptr;
            }
        }
    }
    return 0;
}