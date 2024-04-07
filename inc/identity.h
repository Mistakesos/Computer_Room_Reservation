#ifndef IDENTITY_H
#define IDENTITY_H
#include<iostream>
#include<string>
//身份抽象基类
class Identity
{
public:

    //操作菜单  纯虚函数
    virtual void operMenu() = 0;

    //用户名
    std::string m_Name;
    //密码
    std::string m_PassWd;
};




#endif  //IDENTITY_H