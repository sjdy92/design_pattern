## Iterator-Pattern (반복자 패턴)

반복자 패턴(iterator pattern)은 객체 지향 프로그래밍에서 반복자를 사용하여 컨테이너를 가로지르며 컨테이너의 요소들에 접근하는 디자인 패턴이다. (wiki)

핵심은 클래스 내부 컨테이너와의 결합도를 낮추면서도, 컨테이너의 요소들에게 접근할 수 있는 것이다.


## 예
```java
interface Iterator<T> {
    bool hasNext();
    Iterator<T> next();
    T current();
}

class ArrayIterator<T> : public Iterator<T> {
    ArrayIterator<T>(this.array, this.currentIndex = 0) 

    bool hasNext() override {
        return index + 1 < array.size()
    }

    Iterator<T> next() override {
        ++currentIndex;
        return ArrayIterator<T>(this);
    }

    T current() override {
        return array[currentIndex];
    }

    int currentIndex;
    Array<T> array;
}

class ArrayIteratorCreator<T> {
    ArrayIterator<T> iterator();
}

class Skill {
    int key;
}

class SkillList implements ArrayIteratorCreator<T> {
    public ArrayIterator<Skill> iterator() override {
        return new ArrayIterator<Skill>(skills);
    }

    void AddSkill(Skill s) {
        skills.add(s);
    }

    Array<Skill> skills;
}

int main () {
    SkillList list;
    list.AddSkill(Skill(0));
    list.AddSkill(Skill(1));
    list.AddSkill(Skill(2));

    for(ArrayIterator<Skill> iterator = list.iterator(); iterator.hasNext(); iterator.next())
    {
        SKill skill = iterator.current();
        print(skill.key);
    }
    
    return 0;
}

```

## 결론
1. iterator 를 사용하면 내부 클래스의 컨테이너에 직접 접근하지 않아도 된다. 
2. 많은 언어에서 자료구조 내부를 감추고 iterator 로 접근할 수 있도록 구현되어 있다. ex) (c++)vector.begin(), (java)ArrayList.iterator() 등..
