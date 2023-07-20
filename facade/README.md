## Facade Pattern (퍼사드 패턴)

퍼사드는 클래스 라이브러리 같은 어떤 소프트웨어의 다른 커다란 코드 부분에 대한 간략화된 인터페이스를 제공하는 객체이다.

1. 퍼사드는 소프트웨어 라이브러리를 쉽게 사용할 수 있게 해준다. 또한 퍼사드는 소프트웨어 라이브러리를 쉽게 이해할 수 있게 해 준다. 퍼사드는 공통적인 작업에 대해 간편한 메소드들을 제공해준다.
2. 퍼사드는 라이브러리를 사용하는 코드들을 좀 더 읽기 쉽게 해준다.
3. 퍼사드는 라이브러리 바깥쪽의 코드가 라이브러리의 안쪽 코드에 의존하는 일을 감소시켜 준다. 대부분의 바깥쪽의 코드가 퍼사드를 이용하기 때문에 시스템을 개발하는 데 있어 유연성이 향상된다.
4. 퍼사드는 좋게 작성되지 않은 API의 집합을 하나의 좋게 작성된 API로 감싸준다.
5. 래퍼(wrapper)가 특정 인터페이스를 준수해야 하며, 폴리모픽 기능을 지원해야 할 경우에는 어댑터 패턴을 쓴다. 단지 쉽고 단순한 인터페이스를 이용하고 싶을 경우에는 퍼사드를 쓴다.


## 정의 해석

요약하면, 복잡한 인터페이스를 가진 것을 쉽게 표현해주는 객체다. 

예를 들어 엑셀 형태의 게임 데이터를 로드하는 로직을 만든다고 가정해보자. 
1. Excel 파일을 연다.
2. 특정 Sheet 를 찾는다.
3. 컬럼들을 모두 읽은 후 특정 객체에 담는다.
4. 모든 Row에 대해서 3번을 반복한다.
이를 코드로 표현하면

```c++
bool DataManager::LoadGameData () {
  ExcelFile* file = ExcelLibrary->Load("Data");
  if(!file)
    return false;

  /// SkillInfo 
  ExcelSheet* sheet = file->getSheet("SkillInfo");
  if(!sheet)
      return false;

  Array<SkillInfo> skillInfos;
  for( row : sheet->GetRows() ) {
    SkillInfo* info = new SkillInfo();
    bool result = info->load(row); // 내부에서 컬럼 별로 데이터를 읽는다.
    if(!result) {
      LOG_ERROR("로드 실패 SkillInfo");
      return false;
    }

    skillInfos.add(info);
  }
  _skillInfos = skillInfos;

  /// CharacterInfo 
  sheet = file->getSheet("CharacterInfo");
  if(!sheet)
      return false;

  Array<CharacterInfo> characterInfos;
  for( row : sheet->GetRows() ) {
    CharacterInfo* info = new CharacterInfo();
    bool result = info->load(row); // 내부에서 컬럼 별로 데이터를 읽는다.
    if(!result) {
      LOG_ERROR("로드 실패 CharacterInfo");
      return false;
    }

    characterInfos.add(info);
  }
  _characterInfos = characterInfos;

  // .... 다른 데이터 모두.. 
}
```

이것을 퍼사드 패턴으로 바꿔보자.

```c++

class DataLoaderFacade<T> {
  static bool load<T extends StaticInfo>(Array<T>& outInfos) {
    Excel* file = ExcelLibrary->Load("Data");
    if(!file)
      return false;

    ExcelSheet* sheet = file->getSheet(T::GetSheetName());
    if(!sheet)
      return false;

    Array<T> infos;
    for( row : sheet->GetRows() ) {
      T* info = new T();
      bool result = info->load(row); // 내부에서 컬럼 별로 데이터를 읽는다.
      if(!result) {
        LOG_ERROR("로드 실패 %s", T::GetSheetName());
        return false;
      }

      infos.add(info);
    }
    outInfos = infos;
    return true;
  }
}

bool DataManager::LoadGameData () {
  #define LOAD_DATA(T, infos) {bool result = DataLoaderFacade.load<T>(infos); if(!result) return false;}

  LOAD_DATA(SkillInfo,         _skillInfos);
  LOAD_DATA(CharacterInfo,     _characterInfos);
  // .... 다른 데이터 모두.. 
}

```

퍼사드 패턴으로 엑셀에서 게임 데이터를 읽는 복작한 로직들을 한 메서드로 표현할 수 있었다. 이로써 얻게되는 장점은 아래와 같다.

1. 로드하고 읽어오는 복잡한 로직을 퍼사드 내부로 감추었다. (위 정의 1, 2, 4 번 내용)
2. DataManager::LoadGameData 의 함수에서 어떤 데이터들을 로드하는지 보기가 간결해졌다.  (위 정의 1, 4 번 내용)
3. Excel 라이브러리에 대해서 DataManager는 알 필요가 없다.  (위 정의 3 번 내용)
4. DataManager 는 게임 데이터를 어디서 읽어오는지 관계가 없어졌다. 추후 Excel 에서 Xml 혹의 Binary, Json 등으로 바꿔도 DataManager는 변하지 않는다. (위 정의 3, 5 번 내용)
5. 에러 처리나, 로그 처리 등이 한 곳으로 몰려서 관리가 편해졌다.

## 결론

아마 이 패턴은 개발하면서 한번쯤은 사용해보았을 것이다. 서드파티를 이용하는 로직, OS 에 접근하는 로직들을 감추기 위해, 혹은 너무 복잡한 내부 구현들을 반복해서 써야하거나, 의존 관계가 여러 곳에 얽히게 될 때 퍼사드 패턴을 사용하면 유용할 것 같다.
   
