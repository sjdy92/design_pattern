## 팩토리 패턴 (Factory Pattern)

팩토리 패턴(Factory Pattern)은 소프트웨어 디자인 패턴 중 하나로, 객체 생성을 처리하는 방법을 추상화하는 패턴입니다. 이 패턴은 객체를 생성하는 코드를 클라이언트로부터 분리시키고, 객체의 구체적인 클래스에 대한 의존성을 줄여줍니다. (chatgpt)

![image](https://github.com/sjdy92/design_pattern/assets/11484867/aa3b4bc2-c573-4825-9183-293a50ab80fa)

## 정의
다시 말하면 팩토리 패턴에 객체를 곧바로 생성하지 않고 특정 메서드나 클래스에게 위임하여 객체 생성에 대한 의존성을 줄여준다. 근데 왜 객체를 생성하면 안되는 것일까? 예시를 들어서 확인해보자.

```java
// 1번 예시
interface Shape { 
  void draw();
}

class Rectangle : Shape {}
class Square : Shape {}

void main() {
  int width, height;
  // width, height 입력

  Shape shape;
  if (width == height) {
    shape = new Square();
    shape.fillColor(BLACK);
  } else {
    shape = new Rectangle();
  }
  
  shape.draw();
}
```

위의 코드는 width와 hegiht 가 같다면 까만색 정사각형을, 다르다면 직사각형으로 만들어준다. 이를 **팩토리 메서드**로 구현한다면 아래와 같이 구현할 수 있다.

```java
// 2번 예시
class IShapeFactory {
  Shape createShape(int width, int height);
}

class ShapeFactory {
  Shape createShape(int width, int height) {
    if (width == height) {
      Shape square = new Square();
      square.fillColor(BLACK);
      return square;
    } else {
      return new Rectangle();
    }
  }
}

void main() {
    int width, height;
    // width, height 입력
    IShapeFactory factory = new ShapeFactory();
    Shape shape = factory.createShape(width, height);
    shape.draw();
}
```
1번과 2번 예시의 차이점은 생성하는 부분을 따로 함수로 뺀 것 밖에 없다. 하지만 이로 인해서 main 함수에서는 width와 height 만 갖고 팩토리 메서드를 호출하면 어떤 객체가 나오는지 알필요가 없어졌다. 이것은 객체를 요청하는 클라이언트가 객체 생성에 대한 의존성이 떨어졌다는 것을 의미한다. main 함수 뿐만 아니라 다른 함수에서 Square, Rectangle에 대한 생성을 요구한다면 혹은 생성시 필요한 작업들이 생긴다면, 이 createShape 함수는 더 큰 의미를 갖게 될 것이다. 또 하나의 예시를 들어보자.

```java
interface UIObject {
  void render();
}
interface Button : UIObject {}
interface CheckBox : UIObject {}
class WindowsButton : UIObject {}
class MacButton : UIObject {}
class WindowsCheckBox : UIObject {}
class MacCheckBox : UIObject {}
  
void main() {
    // 버튼 하나와 체크박스 하나를 생성해서 rendering 하자.
    Button button;
    CheckBox checkBox;
    if (isPlatformWindows()) {
      button = new WindowsButton();
    } else (isPlatformMac()) {
      button = new MacButton();
    }
    if (isPlatformWindows()) {
      checkBox = new WindowsCheckBox();
    } else (isPlatformMac()) {
      checkBox = new MacCheckBox();
    }
    button.render();
    checkBox.render();
}
```

이번에도 플랫폼 별로 다른 버튼과 체크박스로 인해서 생성 코드가 길어졌다. 이를 추상 팩토리 클래스를 사용해서 만들어보자.

```java
interface Button {}
interface Checkbox {}

// 윈도우용 버튼 클래스
class WindowsButton implements Button {
    public void render() {
        System.out.println("Rendering a Windows button.");
    }
}

// 윈도우용 체크박스 클래스
class WindowsCheckbox implements Checkbox {
    public void render() {
        System.out.println("Rendering a Windows checkbox.");
    }
}

// 맥용 버튼 클래스
class MacButton implements Button {
    public void render() {
        System.out.println("Rendering a Mac button.");
    }
}

// 맥용 체크박스 클래스
class MacCheckbox implements Checkbox {
    public void render() {
        System.out.println("Rendering a Mac checkbox.");
    }
}

// 추상 팩토리 인터페이스
class GUIFactory {
    Button createButton();
    Checkbox createCheckbox();

    static GUIFactory getInstance() {
      if (isPlatformWindows()) {
        return new WindowsFactory();
      } else if (isPlatformMac()) {
        return new MacFactory();
      } else {
        throw
      }
    }
}

// 윈도우용 팩토리 클래스
class WindowsFactory implements GUIFactory {
    public Button createButton() {
        return new WindowsButton();
    }

    public Checkbox createCheckbox() {
        return new WindowsCheckbox();
    }
}

// 맥용 팩토리 클래스
class MacFactory implements GUIFactory {
    public Button createButton() {
        return new MacButton();
    }

    public Checkbox createCheckbox() {
        return new MacCheckbox();
    }
}

void main() {
    Button button = GUIFactory.getInstance().createButton();
    CheckBox checkBox = GUIFactory.getInstance().createCheckbox();
    button.render();
    checkBox.render();
}
```

위의 예시를 보면 버튼과 체크박스를 만드려는 클라이언트는 어떤 플랫폼인지 신경쓰지 않고 만들 수 있게 되었다. 이처럼 서브클래스의 객체를 생성할 때 서로 다른 작업을 요하거나, 생성하는 로직이 복잡해질 수 있다면 팩토리 패턴으로 객체 생성 로직과 생성 요청 로직을 분리하여 팩토리 패턴의 장점들을 얻을 수 있다.


## 결론

이렇게 팩토리 패턴으로 객체 생성 로직을 분리하면 다음과 같은 이점이 있다.

1. 객체 생성 추상화: 객체 생성에 대한 로직을 분리하여, 객체 생성의 추상화를 할 수 있다. 이는 객체 생성 로직 내부에서 어떠한 작업이 일어나도 요청하는 클라이언트는 신경쓸 필요가 없다는 것을 의미한다.
2. 유연성과 확장성: 객체 생성 로직을 팩토리 내부에 캡슐화할 수 있고, 중앙 관리되기 때문에 생성 로직의 변경이나 기능 추가에 대해 유연성과 확장성을 갖을 수 있다. 


하지만 단점으로 팩토리 클래스가 늘어나게 되면 이에 따른 복잡성이 동반되므로 팩토리 패턴의 장단점을 따져서 도입하는 것이 좋을 것 같다.



