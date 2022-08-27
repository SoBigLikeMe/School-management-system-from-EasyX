#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#pragma comment(lib,"winmm.lib")
void menu();
void help();
void increase();
void search();
void _delete();
void modify();
void Welcome();
void click();
void GoMenu();

int n = 0, t = 1, a = 1;    //n为总人数，t控制循环,a控制窗口和音效只执行一次

struct STU {
    char num[100];    //学号
    char name[100];   //姓名
    char sex[10];   //性别
    char age[10];    //年龄
    char score[10];   //C语言成绩
}stu[100];

int main() {
    while (a) {
        Welcome();
        a -= 1;
    }
    initgraph(1280, 800);
    menu();
    click();
}

//欢迎音效
void Welcome() {
    HWND hnd = GetHWnd();//窗口句柄
    SetWindowText(hnd, "学生管理系统");
    MessageBox(NULL, "欢迎来到学生管理系统", "提示", MB_OKCANCEL);
    mciSendString("open ../source/music/Welcome.mp3", 0, 0, 0);//打开音乐
    mciSendString("play ../source/music/Welcome.mp3", 0, 0, 0);//播放音乐
}

void help() {
    IMAGE img;//定义图像对象
    loadimage(&img, "../source/picture/help.jpg");//加载图片
    putimage(0, 0, &img);
    outtextxy(250, 250, TEXT("该学生管理系统十分简陋，并且有许多非常“难以发现”的BUG"));
    outtextxy(250, 350, TEXT("系统包括四大功能包括：增，删，查，改"));
    GoMenu();
}

//回到菜单
void GoMenu() {
    settextstyle(30, 0, "楷体");//设置字体样式
    outtextxy(0, 770, TEXT("回到菜单"));
    while (1) {
        if (MouseHit()) {//判断鼠标是否有信息
            MOUSEMSG msg = GetMouseMsg();//获取一个鼠标消息。如果没有，就等待
            if (msg.uMsg == WM_LBUTTONDOWN) {//当前鼠标消息
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    if (msg.x > 0 && msg.x < 130 && msg.y>750 && msg.y < 800) {
                        main();
                    }
                }
            }
        }
    }
}

//菜单生成
void menu() {
    cleardevice();
    IMAGE img;//定义图像对象
    loadimage(&img, "../source/picture/menu.jpeg");//加载图片
    settextstyle(100, 0, "楷体");
    setbkmode(TRANSPARENT);//设置背景透明,防止文字被遮挡
    putimage(0, 0, &img);//生成图片
    outtextxy(350, 10, TEXT("学生管理系统"));
    settextstyle(30, 0, "楷体");
    outtextxy(250, 250, TEXT("      1、使用帮助             2、增加学生信息         "));
    outtextxy(250, 350, TEXT("      3、查询学生信息         4、删除学生信息         "));
    outtextxy(250, 450, TEXT("      5、修改学生信息         6、退出系统          "));
}

//菜单选择
void click() {
    while (1) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (msg.x > 338 && msg.x < 512 && msg.y>249 && msg.y < 277) {//1
                    help();
                }
                if (msg.x > 696 && msg.x < 926 && msg.y>251 && msg.y < 277) {//2
                    increase();
                }
                if (msg.x > 339 && msg.x < 567 && msg.y>349 && msg.y < 379) {//3
                    search();
                }
                if (msg.x > 700 && msg.x < 925 && msg.y>350 && msg.y < 377) {//4
                    _delete();
                }
                if (msg.x > 338 && msg.x < 564 && msg.y>450 && msg.y < 477) {//5
                    modify();
                }
                if (msg.x > 699 && msg.x < 924 && msg.y>451 && msg.y < 479) {//6
                    closegraph();
                }
            }
        }
    }
}

//添加学生
void increase()    //增加学生信息
{
    setbkcolor(WHITE);//设置背景颜色

    char str[10];
    char s[10];
    InputBox(str, 8, TEXT("输入添加添加学生人数"), 0, 0, 500, 200, 0);//生成添加学生人数的窗口,并获取添加人数

    cleardevice();//清屏
    settextcolor(BLACK);//设置文字颜色

    int flag, i = n, j;
    int m = atoi(str);

    if (m > 0)
    {
        do
        {
            flag = 1;
            while (flag != 0)
            {
                flag = 0;
                InputBox(str, 9, TEXT("输入添加学生的学号"));
                strcpy_s(stu[i].num, str);

                //学号查重
                for (j = 0; j < i; j++)
                {
                    if (strcmp(stu[i].num, stu[j].num) == 0)
                    {
                        MessageBox(NULL, "输入学号重复,请重新添加", "提示", MB_OKCANCEL);
                        increase();
                        flag = 1;
                        break;
                    }
                }
            }
            InputBox(str, 9, TEXT("输入添加学生学生姓名"));
            strcpy_s(stu[i].name, str);
            InputBox(str, 9, TEXT("输入添加学生学生性别"));
            strcpy_s(stu[i].sex, str);
            InputBox(str, 9, TEXT("输入添加学生学生年龄"));
            strcpy_s(stu[i].age, str);
            InputBox(str, 9, TEXT("输入添加学生学生C语言成绩"));
            strcpy_s(stu[i].score, str);
            i++;
        } while (i < m + n);
        n += m;
    }

    IMAGE img;
    loadimage(&img, "../source/picture/increase.jpg");
    putimage(0, 0, &img);
    outtextxy(410, 380, TEXT("已添加学生:"));
    sprintf_s(s, "%d", i);//转换int型为char型,因为outtextxy只能输出char类型
    outtextxy(580, 380, s);
    GoMenu();
}

//查找学生
void search()    //查询学生信息
{
    IMAGE img;
    int flag = 0, i, all = 0;
    char s1[100];
    cleardevice();
    loadimage(&img, "../source/picture/sreach.jpg");
    putimage(0, 0, &img);
    setbkcolor(WHITE);
    settextstyle(100, 0, "楷体");
    outtextxy(380, 10, TEXT("学生管理系统"));
    settextstyle(80, 0, "楷体");
    outtextxy(467, 296, TEXT("按学号查询"));
    settextstyle(30, 0, "楷体");
    outtextxy(0, 770, TEXT("回到菜单"));

    while (1) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (msg.x > 0 && msg.x < 130 && msg.y>750 && msg.y < 800) {
                    main();
                }
                if (msg.x > 467 && msg.x < 822 && msg.y>296 && msg.y < 365) {
                    InputBox(s1, 9, TEXT("请输入查询学生的学号"), 0, 0, 500, 200, 0);
                    for (i = 0; i < n; i++)
                    {
                        if (strcmp(stu[i].num, s1) == 0)
                        {
                            flag = 1;
                            cleardevice();
                            loadimage(&img, "../source/picture/search.jpg");
                            putimage(0, 0, &img);
                            settextstyle(30, 0, "楷体");
                            outtextxy(200, 300, TEXT("姓名"));
                            outtextxy(400, 300, TEXT("性别"));
                            outtextxy(600, 300, TEXT("年龄"));
                            outtextxy(800, 300, TEXT("学号"));
                            outtextxy(1000, 300, TEXT("C语言成绩"));
                            outtextxy(200, 450, stu[i].name);
                            outtextxy(400, 450, stu[i].sex);
                            outtextxy(600, 450, stu[i].age);
                            outtextxy(800, 450, stu[i].num);
                            outtextxy(1000, 450, stu[i].score);
                            GoMenu();
                        }
                    }if (flag == 0) {
                        MessageBox(NULL, "请输入正确学号或查无此人", "提示", MB_OKCANCEL);
                        main();
                    }
                }
            }
        }
    }
}

//删除信息
void _delete()   //删除信息
{
    int flag, i, j;
    char str[100];
    InputBox(str, 9, TEXT("请输入删除学生的学号"), 0, 0, 500, 200);
    flag = 0;
    for (i = 0; i < n; i++)
    {
        if (strcmp(stu[i].num, str) == 0)
        {
            flag = 1;
            for (j = i; j < n - 1; j++)
            {
                stu[j] = stu[j + 1];
            }
        }
        else {
            MessageBox(NULL, "查无此人", "提示", MB_OKCANCEL);
        }
    }
    if (flag == 1)
    {
        MessageBox(NULL, "删除成功", "提示", MB_OKCANCEL);
        menu();
        n--;
    }
    menu();
}

void modify()    //修改学生信息
{
    int flag = 0;
    char s1[100];
    InputBox(s1, 9, TEXT("输入需要更改信息的学号"), 0, 0, 500, 200, 0);
    cleardevice();
    IMAGE img;
    loadimage(&img, "../source/picture/modify.jpg");
    putimage(0, 0, &img);
    outtextxy(250, 250, TEXT("      1、更改姓名             2、更改性别         "));
    outtextxy(250, 350, TEXT("      3、更改年龄             4、更改C语言成绩         "));
    settextstyle(30, 0, "楷体");
    outtextxy(0, 770, TEXT("回到菜单"));

    for (int i = 0; i < n; i++)
    {
        if (strcmp(s1, stu[i].num) == 0)
        {
            flag = 1;
            while (1) {
                if (MouseHit()) {
                    MOUSEMSG msg = GetMouseMsg();
                    if (msg.uMsg == WM_LBUTTONDOWN) {
                        if (msg.x > 338 && msg.x < 512 && msg.y>249 && msg.y < 277) {//1
                            InputBox(s1, 9, TEXT("输入更改后的姓名"), 0, 0, 500, 200, 0);
                            strcpy_s(stu[i].name, s1);
                            MessageBox(NULL, "更改完成", "提示", MB_OKCANCEL);
                            main();
                        }
                        if (msg.x > 696 && msg.x < 926 && msg.y>251 && msg.y < 277) {//2
                            InputBox(s1, 9, TEXT("输入更改后的性别"), 0, 0, 500, 200, 0);
                            strcpy_s(stu[i].sex, s1);
                            MessageBox(NULL, "更改完成", "提示", MB_OKCANCEL);
                            main();
                        }
                        if (msg.x > 339 && msg.x < 567 && msg.y>349 && msg.y < 379) {//3
                            InputBox(s1, 9, TEXT("输入更改后的年龄"), 0, 0, 500, 200, 0);
                            strcpy_s(stu[i].age, s1);
                            MessageBox(NULL, "更改完成", "提示", MB_OKCANCEL);
                            main();
                        }
                        if (msg.x > 700 && msg.x < 925 && msg.y>350 && msg.y < 377) {//4
                            InputBox(s1, 9, TEXT("输入更改后的C语言成绩"), 0, 0, 500, 200, 0);
                            strcpy_s(stu[i].score, s1);
                            MessageBox(NULL, "更改完成", "提示", MB_OKCANCEL);
                            main();
                        }
                        if (msg.x > 0 && msg.x < 130 && msg.y>750 && msg.y < 800) {
                            GoMenu();
                        }
                    }
                }
            }
        }
    }
    if (flag == 0)
    {
        MessageBox(NULL, "学号输入有误", "提示", MB_OKCANCEL);
        menu();
    }
}
