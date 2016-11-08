#pragma once
#include <cassert>

template<typename T>
class StrongPtr
{
public:
    StrongPtr(T* object = nullptr) : _object(object)
    {
        retain();
    }
    
    ~StrongPtr()
    {
        release();
    }
    
    //copy constructor
    StrongPtr(const StrongPtr<T>& other) : _object(other._object)
    {
        retain();
    }
    
    //assignment operator
    StrongPtr<T>& operator=(const StrongPtr &other)
    {
        if (_object == other._object)
            return *this;
        
        release();
        _object = other._object;
        retain();
        
        return *this;
    }
    
    bool operator==(const StrongPtr<T>& other) const
    {
        return _object == other._object;
    }
    
    T* get()
    {
        return _object;
    }
    
    void reset(T *object = nullptr)
    {
        if (_object == object)
            return;
        
        release();
        _object = object;
        retain();
    }
    
    T* operator->()
    {
        assert(_object);
        return _object;
    }
    
    StrongPtr(StrongPtr<T>&& other) = delete;
    StrongPtr<T>& operator=(StrongPtr&& other) = delete;
    
private:
    void retain()
    {
        if (_object)
            _object->retain();
    }
    
    void release()
    {
        if (_object)
            _object->release();
        _object = nullptr;
    }
    
private:
    T* _object = nullptr;
};
