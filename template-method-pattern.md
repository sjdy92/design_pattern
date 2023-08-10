## Template-Method Pattern (템플릿 메소드 패턴)

동작 상의 알고리즘의 프로그램 뼈대를 정의하는 행위 디자인 패턴이다.[1] 알고리즘의 구조를 변경하지 않고 알고리즘의 특정 단계들을 다시 정의할 수 있게 해준다 (wiki)

알고리즘의 구조를 정의하는데 사용되며, 알고리즘의 일부 단계를 서브클래스에서 구현할 수 있도록 하는 패턴입니다. 템플릿 메소드 패턴의 주요 목적은 공통된 알고리즘 구조를 한 곳에서 관리하면서, 각 단계를 서브클래스에서 변경할 수 있도록 하는 것입니다. 이로써 코드의 재사용성과 유지보수성을 향상시킬 수 있습니다.(chat gpt)

## 예

계산기를 예로 들어 템플릿 메소드 패턴을 구현하면 아래와 같다.

```java
abstract class CalculatorTemplate {
    int caculate(int num1, int num2) {
        input(num1, num2);
        int result = doOperation(num1, num2);
        display(result);
        return result;
    }

    // 추상 메소드: 서브클래스에서 구현해야 할 메소드들
    abstract void input(int num1, int num2);
    abstract int doOperation(int num1, int num2);
    abstract void display(int result);
}

class AdditionCalculator extends CalculatorTemplate {
    void input(int num1, int num2) {
        System.out.println("Adding " + num1 + " and " + num2);
    }

    int doOperation(int num1, int num2) {
        return num1 + num2;
    }

    void display(int result) {
        System.out.println("Result: " + result);
    }
}

class SubtractionCalculator extends CalculatorTemplate {
    void input(int num1, int num2) {
        System.out.println("Subtracting " + num2 + " from " + num1);
    }

    int doOperation(int num1, int num2) {
        return num1 - num2;
    }

    void display(int result) {
        System.out.println("Result: " + result);
    }
}

void main(String[] args) {
    string operand1;
    string operand2;
    CalculatorTemplate calculator;
    while(true)
    {
        char input = input()
        if('0' < input && input < '9')
        {
            if(nullptr == calculator)
                operand1.add(input);
            else 
                operand2.add(input);
        }
        else if('+')
        {
            calculator = new AdditionCalculator();
        } 
        else if('-')
        {
            calculator = new SubtractionCalculator();
        }
        else if('=')
        {
            calculator.calculate(int(operand1), int(operand2));
            operand1.clear();
            operand2.clear();
        }
    }
}
```

더하기, 빼기, 곱하기, 나누기, 루트, 제곱 등등의 계산기 알고리즘이 있는데, 이를 템플릿으로 묶어 calculate를 함수를 호출하면 각각의 알고리즘을 수행한다. 

## 결론

이 패턴은 사실 너무 많은 곳에서 활용되고 있는 패턴 같다. 객체 지향 프로그래밍을 배웠다면 animal 을 상속받아 dog, cat, duck 등 을 구현하고 울음 소리를 오버라이드 해서 표현되는 예제를 많이 봤을 텐데 그 또한 템플릿 메소드 패턴이라고 생각이 된다. 그만큼 이 패턴은 쓰임새가 많은 것 같다.