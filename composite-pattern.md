## Composite-Pattern (컴포지트 패턴)

컴포지트 패턴(Composite pattern)이란 객체들의 관계를 트리 구조로 구성하여 부분-전체 계층을 표현하는 패턴으로, 사용자가 단일 객체와 복합 객체 모두 동일하게 다루도록 한다. (wiki)

## 구성요소

1. Component : 요소 => 재사용이 가능한 각각의 독립된 모듈이라고 생각하면 된다.
2. Composite : 복합물 => 컴포넌트를 상속받고 있고, 컴포넌트들을 갖고있다. 때문에 복합물이라고 표현하는 듯하다.
3. Leaf : 단일 객체 => 복합체를 구성하는 클래스고, 행동들을 정의합니다.

## 예

파일 구조를 예로 들겠습니다. 파일 구조에 구성 요소(component)로는 이미지, 텍스트, 실행 파일, 폴더 등이 있습니다. 이 중 "이미지, 텍스트, 실행 파일" 는 단일 객체(Leaf)이고, 폴더는 다른 컴포넌트를 갖는 Composite 입니다. 코드로 예를 들면 아래와 갖습니다.

```java
class Component {
    string name;
    virtual string extension() = 0;
    virtual void print(int depth) {
        for (int index = 0; index < depth; ++index) {
            std::cout << "  ";
        }
        std::cout << name << "." << extension();
    }
}

class Folder : public Component {
    virtual string extension() {return ""};

    addComponent(Component component);
    virtual void print(int depth) override{
        super::print();
        ++depth;
        for(Component c : components) {
            c.print(depth);
        }
    }
    Array<Component> components;
}

class ExeFile : public Component {
    virtual string extension() {return "exe"};
}

class TextFile : public Component {
    virtual string extension() {return "txt"};
}

class ImageFile : public Component {
    virtual string extension() {return "png"};
}

int main () {
    Folder folder1("sub-dir");
    Folder folder2("root");
    ExeFile exe("hello");
    TextFile txt("composite");
    ImageFile img("pattern");

    folder1.addComponent(exe);
    folder1.addComponent(txt);
    folder2.addComponent(folder1);
    folder2.addComponent(img);
    folder2.print();

    return 0;
}

```

위의 결과는 아래와 같을 것이다.
root
    - sub-dir
        - hello.exe
        - composite.txt
    - pattern.png


## 결론
1. 트리 구조의 형태가 되어야 한다면, 이 컴포지트 패턴을 떠올려서 적용 가능한지 검토해보면 좋을 것 같다.
2. 컴포지트 패턴을 사용하면 재귀, 다형성을 활용이 가능하다.
3. 컴포넌트만 상속하여 "행동"들을 확장이 가능하다.
