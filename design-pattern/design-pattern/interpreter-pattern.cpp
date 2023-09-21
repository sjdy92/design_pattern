#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

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