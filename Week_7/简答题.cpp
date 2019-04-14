1. 派生类继承了基类的大部分的成员函数和所有的数据成员，
但是无法继承构造函数，拷贝构造函数，复制构造函数，析构函数，与其他类或函数的友元关系也无法继承

2. 
(1)ph->head被解释为PublicCorporation的head函数，输出为
"PublicCorporation's head\n"

(2)ph->head被解释为Corporation的head函数，输出为
"Corporation's head\n"

3.
/*
------Section 1------
in B's default constructor
in A's default constructor
in C's default constructor
------Section 2------
in C's copy constructor
In func1
------Section 3------
In func2
------Sextion 4------
*/
4. A* p

