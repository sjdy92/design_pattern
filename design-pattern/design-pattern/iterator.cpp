#include <iostream>
#include <vector>


template<class T>
class Iterator {
public:
    virtual bool valid() = 0;
    virtual Iterator<T>* next() = 0;
    virtual T * current() = 0;
};

template<class T>
class ArrayIterator : public Iterator<T> {
public:
    ArrayIterator(T arr [], size_t count)
        : _count(count)
        , _currentIndex(0)
        , _ptr(count == 0 ? nullptr : arr) {}

    virtual bool valid() override {
        return _currentIndex < _count;
    }

    virtual Iterator<T>* next() override {
        ++_currentIndex;
        return this;
    }

    virtual T* current() override {
        return &_ptr[_currentIndex];
    }

private:
    size_t  _count;
    size_t  _currentIndex;
    T* _ptr;
};

template <class T>
class ArrayIteratorCreator {
public:
    virtual ArrayIterator<T>* iterator() = 0;
};

class Skill {
public:
    int key;
};

class SkillList : public ArrayIteratorCreator<Skill> {
public:
    static const int count = 100;
    virtual ArrayIterator<Skill>* iterator() override {
        return new ArrayIterator<Skill>(skills, count);
    }

    void init() {
        for (int index = 0; index < count; ++index) {
            skills[index].key = index;
        }
    }

    Skill skills[count];
};

//int main() {
//    SkillList list;
//    list.init();
//
//    for (Iterator<Skill>* iterator = list.iterator(); iterator->valid(); iterator->next())
//    {
//        Skill* skill = iterator->current();
//        std::cout << skill->key << std::endl;
//    }
//
//    return 0;
//}
