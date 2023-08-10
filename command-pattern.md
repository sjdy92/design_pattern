## Command Pattern (커맨드 패턴)

커맨드 패턴은 특정 동작을 캡슐화하여 객체로 표현하고, 이 동작을 나중에 실행할 수 있도록 하는 것을 목적으로 하며, 동작을 로깅/취소할 수 있다. (wiki)

A 객체가 다른 객체 B의 함수를 실행하려면, 객체 B를 참조하고 있어야 하는 의존성이 생긴다. 커맨드 패턴을 활용하면 이런 의존성을 제거할 수 있고, 객체 A와 무관하게 확장할 수 있어 유연성을 갖고 있다.

## 구성 요소

![image](https://github.com/sjdy92/design_pattern/assets/11484867/876d8532-f558-4542-9c37-0218d3dbb507)

요청할 특정 동작 (A)

* Command: 특정 동작을 캡슐화한 객체에 대한 인터페이스.
* ConcreteCommand: 특정 동작을 캡슐화한 객체.
* Receiver: 실제로 특정 동작을 할 객체.
* Invoker: 커맨드 객체를 실행할 객체
* Client: 커맨드 객체를 생성하고, 수신자와 커맨드를 연결하여 Invoker에게 전달한다.

주방을 운영한다고 가정해봅시다. 주방장과 파스타 만드는 직원, 스테이크 만드는 직원 이렇게 세 사람이 주방을 이룹니다. 이를 커맨드 패턴으로 맵핑한다면 아래와 같습니다.

* Command: 주문서
* ConcreteCommand: 주문서에 적힌 내용
* Receiver: 파스타 만드는 직원, 스테이크 만드는 직원
* Invoker: 주방장
* Client: 손님

여기에서 특정 동작은 "파스타와 스테이크 만들기" 입니다.
1. 손님(Client)이 주방 직원(Receiver)에게 파스타와 스테이크를 만들도록 하는 것이 목표입니다.
2. 손님은 주문서를 적습니다. (Client가 ConcreteCommand를 만듭니다.) 
3. 주문서가 주방장에게 갑니다.. ( ConcreteCommand 를 Invoker 에게 밀어넣는다. )
4. 주방장은 직원들에게 주문을 내립니다. "봉골레 파스타 하나! 티본 스테이크 하나!" ( Invoker -> ConcreteCommand::execute )
5. 파스타 만드는 직원은 파스타를 만들고, 스테이크 만드는 직원은 스테이크를 만듭니다. ( Receiver 가 실제 동작을 수행함. )

```java
class OrderCommand {
  void execute();
}

class MakePasterOrderCommand {
  Chef chef;
  MakePasterOrderCommand(this.chef);

  void execute() {
    chef->makePasta();
  }
}

class InvokerMasterChef {
  void invoke( OrderCommand order) {
    order.execute();
  }
}

class Chef {
  void makePaster() {
    // 파스타 만들자 ~
  }
}

class Customer {
  OrderCommand makeOrder(Chef chef) {
    return new MakePasterOrderCommand(chef);
  }
}

void main() {
  Chef chef;
  Customer customer;
  customer.makeOrder(chef);
  OrderCommand* command = new MakePasterOrderCommand( Chef );
  InvokerMasterChef.invoke( command );
}

```

비유가 조금 어색할 수 있지만, 여기서 중요한 사실은 직원들은 이 명령이 누구에게로부터 요청 왔는지 알 필요 없고, 손님은 누가 이 음식들을 만드는지 알 필요가 없다는 점이다.
커맨드 패턴을 사용하지 않는다면 객체 Customer 가 객체 Chef 를 참조하여 makePaster() 를 호출해야 한다. 하지만, 커맨드 패턴을 사용함으로써 객체 Customer는 MakePasterOrder 라는 주문서를 작성하고 주방장에게 넘겨준 것으로 Chef가 makePasta() 를 실행하도록 하면서 Customer 와 Chef 와의 의존성이 감소한다.

## 결론

커맨드 패턴을 사용하면 아래와 같은 장점이 있습니다. 
1. 원하는 특정 동작을 캡슐화하고 이를 요청하는 객체와 결합도를 낮출 수 있어서, 이 "특정 동작" 의 확장성과 유연성을 갖게 합니다.
2. "특정 동작"들에 대한 로그를 쌓거나 취소를 할 수 있습니다.
3. 그리고 invoker의 구현에 따라 이를 비동기적으로 처리할 수 있습니다.
4. 위의 장점에 따라 유지 보수성이 높아집니다.

