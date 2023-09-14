## Builder Pattern (빌더 패턴)
복합 객체의 생성 과정과 표현 방법을 분리하여 동일한 생성 절차에서 서로 다른 표현 결과를 만들 수 있게 하는 패턴이다. (wiki)

즉, 생성 과정을 통일하지만, 빌더를 추상화 및 상속하여 다른 객체를 만드는 방법이다. 구성 요소는 아래와 같다.
1. Director: 객체 생성을 관장한다.
2. Builder: 빌더 인터페이스
3. ConcreteBuilder: 어떤 객체를 만들 것인지 구체적인 내용이 들어가 있는 객체이다.
4. Product: Director 가 Builder를 통해 만들어진 결과물이다. 

커피 자판기를 생각해보자. 생성 과정은 "돈을 넣고 버튼을 누른다" 이지만, 어떤 버튼이냐에 따라서 커피가 달라진다. 이를 대입해보면,
1. Director: 자판기
2. Builder: 버튼 자체
3. Concrete Builder: 아메리카노 버튼, 라떼 버튼 등등이 해당된다.
4. Product: 커피


## 예

어떤 DB든 간편하게 연결할 수 있도록 만들어 보자. 어떤 DB의 어떤 버전을 쓰느냐에 따라서 설정이나 연결 방법에 차이가 있기 때문에, 각종 프레임워크에서는 DB 와 연결할 때 이러한 빌더 패턴같은 것을 만들어서 객체를 내보낸다. 

```c++


// Product Interface
class DBConnector {
public:
    DBConnector(const std::string& dialect) : dialect(dialect) {}
    virtual void connect(const std::string& url) = 0;

protected:
    std::string dialect;
};

// Product 
class OracleDBConnector : public DBConnector {
public:

    OracleDBConnector(const std::string& dialect) : DBConnector(dialect) {}
    virtual void connect(const std::string& url) override {
        std::cout << "oracle db 에 연결 : " << url << " " << dialect << std::endl;
    }
};

// Product 
class MySqlDBConnector : public DBConnector {
public:
    MySqlDBConnector(const std::string& dialect) : DBConnector(dialect) {}
    virtual void connect(const std::string& url) override {
        std::cout << "mysql db 에 연결 : " << url << " " << dialect << std::endl;
    }
};

// Builder Interface
class DBConnectorBuilder {
    virtual DBConnector* generate(const char* dialect) = 0;
};

// Builder
class OracleDBConnectorBuilder : public DBConnectorBuilder {
public:
    virtual DBConnector* generate(const char* dialect) {
        return new OracleDBConnector(dialect);
    }
};

// Builder
class MySqlDBConnectorBuilder : public DBConnectorBuilder {
public:
    virtual DBConnector* generate(const char* dialect) {
        return new MySqlDBConnector(dialect);
    }
};


class DBConnectorGenerator {
public:
    DBConnector* buildOracle_5() {
        return OracleDBConnectorBuilder().generate("oracel5");
    }

    DBConnector* buildOracle_6() {
        return OracleDBConnectorBuilder().generate("oracel5");
    }

    DBConnector* buildMySql_5_2() {
        return MySqlDBConnectorBuilder().generate("mysql5.2");
    }

    DBConnector* buildMySql_8_1() {
        return MySqlDBConnectorBuilder().generate("mysql8.1");
    }
};

int main() {
    DBConnector* connector = DBConnectorGenerator().buildMySql_8_1();
    connector->connect("127.0.0.1:8000");
    return 0;
}

```

## 결론

위의 예시로 DB의 종류와 버전에 따른 빌더를 만들어 보았다. 빌더의 장점은 만드는 사람 입장에서는 매우 편하다는 것이다. 여러 설정 값들을 일일이 설정하거나 올바르지 못한 설정값으로 인해 객체를 정상적으로 사용하지 못할 때 이 빌더 패턴이 유용할 것 같다. 단점은 빌더들이 늘어나 복잡성이 늘어난다는 것이 있을 것 같다.