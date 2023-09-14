#include <string>
#include <iostream>


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
