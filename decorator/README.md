## 데코레이터 패턴 (Decorator pattern) 

데코레이터 패턴(Decorator pattern)이란 주어진 상황 및 용도에 따라 어떤 객체에 책임을 덧붙이는 패턴으로, 기능 확장이 필요할 때 서브클래싱 대신 쓸 수 있는 유연한 대안이 될 수 있다. (wiki)

데코레이터 패턴(Decorator Pattern)은 객체 지향 프로그래밍에서 사용되는 디자인 패턴 중 하나입니다. 이 패턴은 기존 객체의 동작을 변경하지 않고, 기능을 추가하거나 확장할 수 있는 유연한 방법을 제공합니다. 데코레이터 패턴은 객체 간의 계층 구조를 만들어 사용하며, 각 객체는 동일한 인터페이스를 공유합니다. (chatgpt)

![image](https://github.com/sjdy92/design_pattern/assets/11484867/63da1531-39e3-4a3d-a03f-0d37bfeb3877)

## 정의
1. 기능 확장이 필요할 때 서브클래싱 대신 사용한다.
2. 객체에 기존 동작을 변경하지 않고, 기능을 추가하거나 확장할 수 있는 유연한 방법을 제공한다.
3. 상황 및 용도에 따라 책임을 덧붙인다.

 게임에서 궁수가 활을 쏘아 적을 무찌르는데, 화살과 샷의 속성들을 스테이지가 깰 때마다 추가로 붙일 수 있다고 생각해보자. 불화살 샷, 불화살이고 연속으로 3번 쏘는 샷, 불화살이고 연속으로 3번 나가면서 튕겨지는 화살을 쏘는 샷. 이것을 BowSkill 클래스를 두고 서브클래싱으로 만든다면, 여러가지 조합으로 인해서 많은 경우의 클래스를 만들어야 할 것이다. 혹은 화살과 샷의 속성을 클래스의 멤버로 만든다면, 새로운 기능을 추가할 때 기존의 속성들과 조합하는 로직을 새로 써야할 것이다. 이 대안으로 Decorator Pattern을 사용해 볼 수 있다.

 ![image](https://github.com/sjdy92/design_pattern/assets/11484867/f48ad526-1be7-46a7-931c-f8b59c3c5d31)


```java
interface Skill {
  public void execute();
}

class BowSkill extends Skill {
  public void execute() {
    print("화살을 쏘았다!");
  }
}

class SkillDecorator extends Skill {
  private Skill component;
  
  SkillDecorator(Skill component) {
    this.component = component;
  }
  
  public void execute() {
    component.execute();
  }
}

class FireSkillDecorator {
  FireSkillDecorator(Skill component) {
    super(component);
  }

  public void execute() {
    super.execute();
    print("불!");
  }
}

class ReflectSkillDecorator {
  ReflectSkillDecorator(Skill component) {
    super(component);
  }

  public void execute() {
    super.execute();
    print("반사되는!");
  }
}
```

위 UML과 코드를 보면서 시나리오를 작성해보자. 

1. 궁수로 선택하고 불화살 능력을 선택하였다.
```java
// 궁수로 선택했으니, BowSkill을 데코레이터 패턴의 실제 객체로 사용한다.
Skill bowSkill = new BowSkill();
// 불화살 능력을 선택을 했으므로, 불 속성의 Decorator를 입혀준다.
bowSkill = new FireSkillDecorator(bowSkill);
bowSkill.execute();
```
=> 불!화살을 쏘았다! 가 출력된다.

2. 한 스테이지가 끝나고 추가로 반사 능력을 붙였다.
```java
bowSkill = new ReflectSkillDecorator(bowSkill);
bowSkill.execute();
```
=> 반사되는!불!화살을 쏘았다! 가 출력된다.


## 결론
위의 예제와 같이 데코레이터 패턴을 사용하면 코드의 유연성과 확장성이 높아집니다. 예를 들면 화살의 속성이 추가되었을 때, 혹은 활이 아닌 검을 사용한다고 했을 때, 이들의 조합으로 경우의 수를 처리할 수 있게됩니다. 
