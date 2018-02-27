#include "DataBase.h"

using namespace std;

USING_NS_CC;

unique_ptr<DataBase> DataBase::_dataBase;

const unique_ptr<DataBase>& DataBase::getInstace()
{
    if (_dataBase == nullptr)
    {
        unique_ptr<DataBase> dataBase(new DataBase());
        _dataBase = move(dataBase);
    }
    
    return _dataBase;
}

bool DataBase::getBoolForKey(const std::string &key)
{
    return UserDefault::getInstance()->getBoolForKey(key.c_str());
}

void DataBase::setBoolForKey(const std::string &key, bool val)
{
    UserDefault::getInstance()->setBoolForKey(key.c_str(), val);
}
