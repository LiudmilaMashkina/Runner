#pragma once

#include <base/CCUserDefault.h>

class DataBase // Singleton
{
public:
    
    bool getBoolForKey(const std::string& key);
    void setBoolForKey(const std::string& key, bool val);
    
    static const std::unique_ptr<DataBase>& getInstace();
    
private:
    DataBase() {}
    
    static std::unique_ptr<DataBase> _dataBase;
};
