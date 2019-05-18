1. 如果派生类所继承的多个基类有相同的基类，而派生类对象需要调用这个祖先类的接口方法或者是成员对象，就会容易出现二义性，即产生重复继承问题
D类继承B，C类，而B，C类均继承A类，则D类继承A类两次，D类对象将包含A类的所有成员对象两份，一份属于B，一份属于C
解决方法：将A类定义为B和C类的虚基类