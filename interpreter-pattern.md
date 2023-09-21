## interpreter Pattern (인터프리터 패턴)

인터프리터 패턴(interpreter pattern)은 한 언어에서 문들을 평가하는 방법을 규정하는 디자인 패턴이다.

## 예

위 정의를 다시말하면, 언어를 의미 있는 어떤 것으로 해석하는 것이라고 생각된다. 게임 개발을 하다보면 특정 조건에 대해서 어떤 일을 수행하는 일을 데이터로 정의하는 경우가 있다. 예를 들면, "complateQuest(3)", "hasSkill(1003)" 등의 조건이 있을 때, 아이템을 사용가능하다던지, 퀘스트를 진행할 수 있다던지 데이터로 정의를 할 수 있다. 이러한 조건들을 파싱할 때 이 interpreter Pattern을 사용할 수 있다. 아래 예제는 함수안에 int 변수가 하나 들어가고, return 도 int로 되는 조건식만 가능한 것을 보여준다.

```c++

class Player {
public:
    std::unordered_set<int>     completedquest;
    std::unordered_set<int>     skill;
};

class Expression {
public:
    virtual bool check(string expression) = 0;
    virtual bool evaluate(Player& player, std::string parameter) = 0;
};

class ComplateQuestExpression : public Expression {
    virtual bool check(string expression) override {
        return expression == "complateQuest";
    }

    virtual bool evaluate(Player& player, std::string parameter) override {
        return player.completedquest.end() != player.completedquest.find(atoi(parameter.c_str()));
    }
};

class HasSkillExpression : public Expression {
    virtual bool check(string expression) override {
        return expression == "hasSkill";
    }

    virtual bool evaluate(Player& player, std::string parameter) override {
        return player.skill.end() != player.skill.find(atoi(parameter.c_str()));
    }
};

class RootExpression : public Expression {
public:
    RootExpression() {
        expressions.push_back(new ComplateQuestExpression());
        expressions.push_back(new HasSkillExpression());
    }
    virtual bool check(string expression) override { return true; }
    bool evaluate(Player& player, std::string condition) {
        Expression* currentExpression = nullptr;
        string currentString;
        bool isParameter = false;

        for (int index = 0; index < condition.size(); ++index) {
            char character = condition[index];
            if (character == '(') {
                for (auto* expression : expressions) {
                    if (expression->check(currentString)) {
                        currentExpression = expression;
                        currentString.clear();
                        break;
                    }
                }
            }
            else if (character == ')') {
                if (currentExpression != nullptr) {
                    return currentExpression->evaluate(player, currentString.c_str());
                }
            }
            else {
                currentString += character;
            }
        }

        return false;
    }

    vector<Expression*> expressions;
};

int main() {
    Player player;
    player.completedquest.insert(103);
    player.skill.insert(104);

    RootExpression expression;
    bool a1 = expression.evaluate(player, "complateQuest(103)");
    bool a2 = expression.evaluate(player, "hasSkill(104)");
    bool a3 = expression.evaluate(player, "complateQuest(0)");
    bool a4 = expression.evaluate(player, "hasSkill(0)");

    return 0;
}

```

## 결론

위 예제는 "문자열 ( 문자열 )" 의 규칙을 갖고 있는 문장을 해석하여, 특정 플레이어의 조건을 검사한다. 문장을 해석하여, 플레이어의 조건을 판단하는 의미있는 것을 만든 것이다. 계산기나, && || 와 같은 논리 연산자 등등을 사용하는 문장에서 이 인터프리터가 많이 사용될 것 같다.