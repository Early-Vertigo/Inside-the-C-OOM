## 1.1 C++对象模型
    C++对象模型是从简单对象模型派生而来的，并对内存空间和存取时间做了优化。

    在此模型中，非静态的数据成员被配置于每一个类对象内，静态数据成员则被存放在个别的类成员之外。

    静态和非静态的函数成员也被放在个别的类成员之外。

    虚函数则以两个步骤支持：
        1.每一个类产生出一堆指向虚函数的指针，放在表格之中。这个表格被称为虚函数表(virtual table, vtbl)。
        2.每一个类对象被安插一个指针，指向相关的虚函数表。
          通常这个指针被称为虚指针(vptr)。
          vptr的设定(setting)和重置(resetting)都由每一个类的构造函数、析构函数、拷贝赋值运算符自动完成(见第五章)。
          每一个类所关联的type_info对象(用以支持runtime type identification, RTTI)也经由virtual table被指出来，通常放在表格的第一个slot。

### C++对象模型的特点
    C++对象模型的优点在于空间和存取时间的效率。
    主要缺点是：如果应用程序代码本身未曾改变，但所涉及到的类对象的非静态数据成员有所修改(可能是添加、移除、更改)，那么应用程序代码同样得重新编译。
    该缺点，双表格模型(将数据成员放在一个表格，将函数成员放在一个表格，类对象通过两个指针访问表格进而访问成员)提供了较大的弹性。
    因为双表格模型多提供了一层间接性，不过双表格模型的缺点则是付出了空间和执行效率的代价。

### 加上继承
    C++支持单一继承:
        class Library_materials {...};
        class Book : public Library_materials {...};
        class Rental_book : public Book {...};
    C++也支持多重继承：
        class iostream: public istream, public ostream {...};
    甚至，继承关系也可以指定为虚拟(virtual,也就是共享的意思)
        class istream : virtual public ios {...};
        class ostream : virtual public ios {...};
    在虚拟继承的情况下，基类不管在继承串链中被派生多少次，永远只会存在一个实例。
    例如iostream之中就只有virtual ios base class的一个实例。

    一个派生类如何在本质上塑造其基类的实例？
    
    考虑到”间接性“的级数变化：因为继承的深度而增加。
        解决方法：在派生类内复制一个指针，指向继承串链中的每一个基类，可以获得一个固定的存取时间，但代价是额外的空间存放该指针。
    
### 对象模型如何影响程序
    不同的模型，会导致”现有的程序代码必须修改”以及“必须加入新的程序代码”两个结果。
    见例子virtual function foo.h

## 1.2 关键词所带来的差异
    本节主要讲述了struct和class的区别、使用时的选择、一些共通或者可利用的特性

    例1.在C语言中，把单一元素的数组放在一个struct的尾端，于是每个结构体对象可以拥有可变大小的数组：
        struct mumble{
            // jibber jabber
            char pc[1];
        };
        // 然后从文件或标准输入装置中取得一个字符串
        // 然后为结构体本身和该字符串配置足够的内存
        struct mumble *pmumb1 = (struct mumble*) malloc (sizeof(struct mumble) + strlen(string) + 1);
        strcpy(&mumble.pc, string);
    该方法在C++中不一定可以成功运行，以为C++中对象虚函数的存在使得所谓将可变数组放在结构体尾部的做法，变得不一定有效。
    如果想要实现类似的效果，那么最好将该可变部分抽离出变为一个独立的struct声明。

## 1.3 对象的差异
    C++程序设计模型支持的三种程序设计范式：
        1.程序模型(procedural model)
        2.抽象数据类型模型(abstract data type model, ADT)
        3.面向对象模型(object-oriented model)
    
    在OO设计模式中，只有通过pointer或者reference的间接处理，才支持OO程序设计所需的多态性质。
    在ADT设计模式中，处理的是一个拥有固定而单一类型的实例，其在编译时期就已经完全定义好了。

    在C++中，多态只存在于public class体系中。
    C++以下列方式支持多态：
        1.经由一组隐式的转化操作。比如把一个派生类指针转化为一个指向其public base type的指针：
            shape *ps = new circle(); // 
        2.经由virtual function机制：
            ps->rotate();
        3.经由dynamic_cast和typeid运算符：
            if(circle *pc = dynamic_cast<circle*>(ps))... // 不是很理解这个做法嘞
    
    多态的主要作用是经由一个共同的接口来影响类型的封装，这个接口通常被定义在一个抽象的base class中。
    这个共享接口是以virtual function机制引发的，其可以在执行期根据对象的真正类型解析出到底是哪一个函数实例被调用。
    
    类对象的内存大小？或者说，需要多少内存才可以表现一个类对象？
        其非静态的数据成员的总和大小；
        加上任何由于alignment(内存对齐)的需求而填补上去的空间(可能存在于成员之间，也可能存在于集合体边界)；
        加上为了支持虚函数而由内部产生的任何额外负担(overhead)，如虚指针。