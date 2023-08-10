#include <iostream>
#include <string>
#include <vector>
#include "info/facade-info.h"

class DataLoaderFacade {
public:
    template<class T, typename = std::enable_if<std::is_base_of<StaticInfo, T>::value>>
    static bool loadExcel(std::vector<T*>& outInfos) {
        Excel* file = ThirdParty_ExcelLibrary::load("Data");
        if (!file)
            return false;

        Excel::Sheet* sheet = file->getSheet(T::GetSheetName());
        if (!sheet)
            return false;

        std::vector<T*> infos;
        for (Excel::Row row : sheet->getRows()) {
            T* info = new T();
            bool result = info->load(row); // 내부에서 컬럼 별로 데이터를 읽는다.
            if (!result) {
                std::cout << "로드 실패" << T::GetSheetName();
                return false;
            }

            infos.push_back(info);
        }

        outInfos = infos;
        return true;
    }
};

class DataManager {
public:
    bool LoadGameData() {
        
        #define LOAD_DATA(T, infos) {bool result = DataLoaderFacade::loadExcel<T>(infos); if(!result) return false;}

        LOAD_DATA(SkillInfo,        _skillInfos);
        LOAD_DATA(CharacterInfo,    _characterInfos);
        // .... 다른 데이터 모두.. 
        return true;
    }

    void print() {
        for (auto x : _characterInfos) {
            std::cout << x->GetSheetName() << x->_index << std::endl;
        }

        for (auto x : _skillInfos) {
            std::cout << x->GetSheetName() << x->_index << std::endl;
        }
    }

    std::vector<CharacterInfo*> _characterInfos;
    std::vector<SkillInfo*> _skillInfos;
};

//int main() {
//    DataManager d;
//    d.LoadGameData();
//    d.print();
//    return 0;
//}
