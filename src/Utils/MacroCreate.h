#pragma once

#define CC_CREATE_FUNC(class_name) \
static class_name* create() \
{ \
    class_name *res = new class_name(); \
    if (res && res->init()) \
    { \
        res->autorelease(); \
        return res; \
    } \
    else \
    { \
        delete res; \
        return nullptr; \
    } \
}

#define CC_CREATE_FUNC_1(class_name, t, v) \
static class_name* create(t v) \
{ \
    class_name *res = new class_name(); \
    if (res && res->init(v)) \
    { \
        res->autorelease(); \
        return res; \
    } \
    else \
    { \
        delete res; \
        return nullptr; \
    } \
}

#define CC_CREATE_FUNC_2(class_name, t1, v1, t2, v2) \
static class_name* create(t1 v1, t2 v2) \
{ \
    class_name *res = new class_name(); \
    if (res && res->init(v1, v2)) \
    { \
        res->autorelease(); \
        return res; \
    } \
    else \
    { \
        delete res; \
        return nullptr; \
    } \
}

#define CC_CREATE_FUNC_3(class_name, t1, v1, t2, v2, t3, v3) \
static class_name* create(t1 v1, t2 v2, t3 v3) \
{ \
    class_name *res = new class_name(); \
    if (res && res->init(v1, v2, v3)) \
    { \
        res->autorelease(); \
        return res; \
    } \
    else \
    { \
        delete res; \
        return nullptr; \
    } \
}

#define CC_CREATE_FUNC_4(class_name, t1, v1, t2, v2, t3, v3, t4, v4) \
static class_name* create(t1 v1, t2 v2, t3 v3, t4 v4) \
{ \
    class_name *res = new class_name(); \
    if (res && res->init(v1, v2, v3, v4)) \
    { \
        res->autorelease(); \
        return res; \
    } \
    else \
    { \
        delete res; \
        return nullptr; \
    } \
}

#define CC_CREATE_FUNC_5(class_name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) \
static class_name* create(t1 v1, t2 v2, t3 v3, t4 v4, t5 v5) \
{ \
    class_name *res = new class_name(); \
    if (res && res->init(v1, v2, v3, v4, v5)) \
    { \
        res->autorelease(); \
        return res; \
    } \
    else \
    { \
        delete res; \
        return nullptr; \
    } \
}