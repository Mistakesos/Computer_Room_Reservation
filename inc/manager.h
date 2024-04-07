#ifndef MANAGER_H
#define MANAGER_H
#include<vector>
#include"teacher.h"
#include"student.h"
#include"identity.h"
#include"computerRoom.h"

//管理员类设计
class Manager :public Identity
{
public:

    //默认构造
    Manager();

    //有参构造
    Manager(std::string name, std::string passwd);

    //菜单界面
    virtual void operMenu();

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    //初始化容器
    void initVector();

    //检测重复 参数1：检测学号/职工号   参数2：检测类型
    bool checkRepeat(int id, int type);

    //学生容器
    std::vector<Student> vStu;

    //教师容器
    std::vector<Teacher> vTea;

    //机房信息
    std::vector<ComputerRoom> vCom;

};

#endif  //MANAGER_H