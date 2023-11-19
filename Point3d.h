//
// Created by PortLate on 2023/11/11.
//

#include <iostream>

#ifndef INSIDE_THE_C___OBJECT_MODEL_POINT3D_H
#define INSIDE_THE_C___OBJECT_MODEL_POINT3D_H


class Point3d {
public:
    Point3d(float x = 0.0 , float y = 0.0, float z = 0.0):_x(x),_y(y),_z(z){}

    float x(){return _x;}
    float y(){return _y;}
    float z(){return _z;}

    void x(float xval){_x = xval;}
    void y(float yval){_y = yval;}
    void z(float zval){_z = zval;}

private:
    float _x;
    float _y;
    float _z;
};

/**
 * @class 简单对象模型
 */
class Point{
public:
    Point(float xval);

    // 一个虚函数形式的析构函数可以在多态中，实现更好的内存管理
    virtual ~Point();

    float x() const;
    static int PointCount();

protected:
    virtual std::ostream&
        print(std::ostream &os) const;
    float _x;
    static int _point_count;
};

/**
 * @class 表格驱动对象模型
 * 将member相关的信息抽离出来
 * 放在data member table 和 member function table
 * 类对象本身则内含指向这两个表格的指针
 */


#endif //INSIDE_THE_C___OBJECT_MODEL_POINT3D_H
