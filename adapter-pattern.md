## Adapter Pattern (어댑터 패턴)

어댑터 패턴(Adapter pattern)은 클래스의 인터페이스를 사용자가 기대하는 다른 인터페이스로 변환하는 패턴으로, 호환성이 없는 인터페이스 때문에 함께 동작할 수 없는 클래스들이 함께 작동하도록 해준다. (wiki)

어댑터 패턴(Adapter Pattern)은 패턴은 서로 다른 두 인터페이스 사이에서 상호 작용할 수 있도록 도와줍니다 (chatgpt)

## 예
어댑터 패턴은 아래와 같은 상황에서 사용 됩니다.
1. 이미 존재하는 클래스의 인터페이스를 변경하고자 할 때
2. 호환되지 않는 인터페이스를 가진 두 클래스를 함께 사용해야 할 때

1번을 예로 콘센트를 예를 들어보자.
```java
// 콘센트
class PowerSocket {
  int volt, shape;
  
  void plugIn ( volt, shape ) {
    if( this.volt != volt || this.shape == shape ) {
      explode();
      return;
    }
    if( volt != 220 && volt != 110 ) {
      explode();
      return;
    }

    // 전기가 흘러라
  }

  bool is220() {return volt == 220};
  bool is110() {return volt == 110};
}

class IPowerAdapter {
  PowerSocket _powerSocket;
  IPowerAdapter(self._powerSocket);

  bool plugIn();
}

class SquarePowerAdapter_220 : IPowerAdapter{
  bool plugIn() override {
    if(_powerSocket.is220() {
      _powerSocket.plugIn(220, Square)
      return true;
    }

    return false;
  }
}

class CirclePowerSocketAdapter_110 : IPowerAdapter{
  bool plugIn() override {
     if(_powerSocket.is110() {
      _powerSocket.plugIn(110, Circle)
      return true;
    }
    return false;
  }
}

void client () {
  PowerSocket _powerSocket;
  SquarePowerAdapter_220 adapter (_powerSocket);
  adapter.plugIn();
}

```

위 예제는 콘센트(PowerSocket)에 잘못된 전압의 파워가 들어가게되면 폭발한다. 이처럼 사용자가 잘못사용할 수 있는 객체나 너무 범용적인 객체라면, 어댑터 패턴으로 한번 감싸서 호출함으로써 올바른 사용을 하게 하고 편리하게 사용할 수 있도록 도와줄 수 있을 것 같다.

-----

2번을 예로 지도 라이브러리를 이용해서 애플리케이션을 만든다고 가정해봅시다.

```java
class GoogleMap {
  bool displayMap(location, zoom, AndroidSetting, IosSetting);
}

class NaverMap {
  int drawMap(zoom, location, MapSetting);
}

// 위 두 클래스 GoogleMap,  NaverMap 는 호환되지 않는 인터페이스를 갖고 있습니다.

class IMapAapter {
  TResult renderMap(location, zoom, NaverMapSetting);
}

class GoogleMapAdapter : IMapAapter{
  TResult renderMap(location, zoom, Setting) {
    bool result = GoogleMap.displayMap(location, zoom, SettingToAndroidSetting, SettingToIosSetting);
    return TResult(result);
  }
}

class NaverMapAdapter : IMapAapter{
  TResult renderMap(location, zoom, Setting) {
    int result = NaverMap.drawMap(zoom, location, SettingToNaverMapSetting);
    return TResult(result);
  }
}

void App() {
  IMapAdapter map = new GoogleMapAdapter;
  map.renderMap(location, zoom, Setting(...));
}
```

위 예제에서 만일 API 사용량에 따라서, GoogleMap 과 NaverMap을 왔다갔다 해야한다면 IMapAdapter 를 받는 변수에 GoogleMapAdapter과 NaverMapAdapter 만 갈아끼우면 유지보수가 쉽게 될 것이다. 만일 Adapter를 사용하지 않았다면, App() 함수 내에서 관리해야할 것이다.

## 결론

알게 모르게 많이 쓰고 있는 패턴인 것 같다. 자료구조 구현을 보면 Stack, Queue 이런 자료구조들이 내부에서는 vector( array ) 등으로 사용되고 있는 것을 볼 수 있다. 이 또한 어댑터 패턴의 예로 볼 수 있다. 결론은 불편한 인터페이스를 갖고 있는 객체를 이용해야하거나, 호환되지 않는 두 객체를 묶고 싶을 때 사용될 수 있는 패턴으로 이해하면 될 것 같다.
