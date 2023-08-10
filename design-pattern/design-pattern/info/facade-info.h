#pragma once
#include <iostream>
#include <string>
#include <vector>

class Excel {
public:
    class Row {
    public:
        Row(int index) :_index(index) {}
        int _index;
    };

    class Sheet {
    public:
        Sheet(std::string str) :_sheetName(str) {
            for (int index = 0; index < 10; ++index) {
                _rows.push_back(Row(index));
            }
        }

        std::vector<Row>& getRows() { return _rows; }
        std::vector<Row> _rows;
        std::string _sheetName;
    };

    Sheet* getSheet(std::string str) {
        return new Sheet(str);
    }

    Excel(std::string str) :_fileName(str) {}
    std::string _fileName;
};

class ThirdParty_ExcelLibrary {
public:
    static Excel* load(std::string str) {
        return new Excel(str);
    }
};

class StaticInfo {
public:
    virtual bool load(Excel::Row row) = 0;
    int _index;
};

class CharacterInfo : public StaticInfo {
public:
    static std::string GetSheetName() { return "CharacterInfo"; }
    virtual bool load(Excel::Row row) {
        _index = row._index;
        return true;
    }
};

class SkillInfo : public StaticInfo {
public:
    static std::string GetSheetName() { return "SkillInfo"; }
    virtual bool load(Excel::Row row) {
        _index = row._index;
        return true;
    }
};
