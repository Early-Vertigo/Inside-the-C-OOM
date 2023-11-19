//
// Created by PortLate on 2023/11/11.
//

#ifndef INSIDE_THE_C___OBJECT_MODEL_VIRTUAL_FUNCTION_FOO_H
#define INSIDE_THE_C___OBJECT_MODEL_VIRTUAL_FUNCTION_FOO_H
/*
 * X有两个虚函数
 * 1.析构函数；2.foo
 * virtual table中，vtbl[0]是指向X的type_info obejct
 * vtbl[1]指向X::~X();
 * vtbl[2]指向X::foo();
 */
class X{
    // 构造函数
    X(){}
    // 虚函数形式的析构函数
    ~X(){}
    virtual X foo(){
        X xx;
        X *px = new X;
        // foo()是一个virtual function
        xx.foo();
        px->foo();

        delete px;
        return xx;
    };
};
/*
上述函数有可能在内部转换为：
 void foobar(X &_result){
    // 构造_result
    // _result用来代替local xx ...
    _result.X::X(); // 调用

    // 扩展X *px = new x;
    px = _new(sizeof(X));
    if(px != 0) px->X::X();

    // 扩展xx.foo()但不使用virtual机制
    // 以 _result取代xx
    foo(&_result);

    // 使用virtual 机制扩展px->foo()
    (*px->vtbl[2]) (px)

    // 扩展delete px
    if(px != 0){
        (*px->vtbl[1])(px);
        _delete(px);
    }

    // 无需使用named return statement
    // 无需摧毁local object xx
    return;
}
 */

#endif //INSIDE_THE_C___OBJECT_MODEL_VIRTUAL_FUNCTION_FOO_H
