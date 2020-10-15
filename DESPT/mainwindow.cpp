#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLineEdit"
#include <stdlib.h>
#include <time.h>
#include <QString>
#include <QChar>
#include <QDebug>
#include <iostream>
using namespace std;
QString k;
QString global_miwen;        //存放密文数据
QString global_mingwen;      //存放明文数据
int global_sixteen[1000];   //用来存放明文数据ASCII码整除16后的数值
int index;       //控制global_sixteen的下标

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

struct node
{
    int c[80];        //存放去掉奇偶校验位后，重排的56比特子密钥左半部分（28比特）
    int d[80];        //存放去掉奇偶校验位后，重排的56比特子密钥右半部分（28比特）
    int cd[80];       //存放去掉奇偶校验位后，重排的56比特子密钥（56比特）
    int k_n[80];       //存放16轮子密钥
    int l[80];       //存放明文左半部分
    int r[80];       //存放明文右半部分
    node()         //初始化
    {
        memset(c, 0, sizeof(c));
        memset(d, 0, sizeof(d));
        memset(k_n, 0, sizeof(k_n));
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
    }
};

const QChar mikey[18] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };


//IP初始置换表    前面第一位补一个0，因为数组索引从0开始。
const int pc_ip[80] = { 0,
58, 50, 42, 34, 26, 18, 10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9, 1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5,
63, 55, 47, 39, 31, 23, 15, 7 };

//IP初始逆置换表
const int pc_reverse_ip[80] = { 0,
40, 8, 48, 16, 56, 24, 64, 32,
39, 7, 47, 15, 55, 23, 63, 31,
38, 6, 46, 14, 54, 22, 62, 30,
37, 5, 45, 13, 53, 21, 61, 29,
36, 4, 44, 12, 52, 20, 60, 28,
35, 3, 43, 11, 51, 19, 59, 27,
34, 2, 42, 10, 50, 18, 58, 26,
33, 1, 41, 9, 49, 17, 57, 25 };

//置换选择1(PC-1)
const int pc_1[60] = { 0,
57, 49, 41, 33, 25, 17, 9,
1, 58, 50, 42, 34, 26, 18,
10, 2, 59, 51, 43, 35, 27,
19, 11, 3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23,15,
7, 62, 54, 46, 38, 30, 22,
14, 6, 61, 53, 45, 37, 29,
21, 13, 5, 28, 20, 12, 4 };

//置换选择2(PC-2)
const int pc_2[60] = { 0,
14, 17, 11, 24, 1, 5,
3, 28, 15, 6, 21, 10,
23, 19, 12, 4, 26, 8,
16, 7, 27, 20, 13, 2,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32 };

//E盒选择拓展运算
const int pc_e[80] = { 0,
32, 1, 2, 3, 4, 5,
4, 5, 6, 7, 8, 9,
8, 9, 10, 11, 12, 13,
12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32, 1 };

//P盒置换表
const int pc_p[80] = { 0,
16, 7, 20, 21,
29, 12, 28, 17,
1, 15, 23, 26,
5, 18, 31, 10,
2, 8, 24, 14,
32, 27, 3, 9,
19, 13, 30, 6,
22, 11, 4, 25 };


//S盒选择压缩运算
 const int s_box[8][4][16] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,

    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 10, 5, 14, 9,

    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,

    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,

    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,

    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,

    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,

    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };

//F轮函数实现E盒扩展
int f(int r[80], int kn[80])
{
    int x = 0;
    int e[80] = { 0 };
    int h = 0, l = 0, idx = 0;
    //E盒扩展得到48比特输出数据e(Ri);
    for (int i = 1; i <= 48; i++)
        e[i] = r[pc_e[i]];
    //与子密钥异或运算得到k^(Ri);
    for (int i = 1; i <= 48; i++)
        r[i] = e[i] ^ kn[i];
    //S盒压缩将48位分为8组，每组6位，得到S(k^(Ri));
    for (int i = 1; i <= 48; i += 6)
    {
        h = r[i] * 2 + r[i + 5] * 1;    //算出六比特的第1和第6比特组成十进制，获取S盒的行号
        l = r[i + 1] * 8 + r[i + 2] * 4 + r[i + 3] * 2 + r[i + 4] * 1; //2,3,4,5比特的列号
        e[++idx] = (s_box[x][h][l] >> 3) & 1;          //得到S盒中对应的二进制数值
        e[++idx] = (s_box[x][h][l] >> 2) & 1;
        e[++idx] = (s_box[x][h][l] >> 1) & 1;
        e[++idx] = s_box[x][h][l] & 1;
        x++;       //控制S盒的下标，S0-S7即S[X]
    }
    //P盒置换
    for (int i = 1; i <= 32; i++)
        r[i] = e[pc_p[i]];
    return 0;
}

void jiami_or_jiemi(QString m, int choice)
{

    /*
    转二进制
    功能：将16个16进制转换成16个二进制并存到two数组
    k密钥转换成二进制并存到two_k数组
    */

    QChar *b=new QChar[m.length()];    //把QString类型明文转为char类型使用，存放在m1中
    char m1[m.length()];
    b=m.data();
    for(int i=0;i<m.length();i++)
        m1[i]=b[i].toLatin1();

    int two[66] = { 0 }, num, idx = 0, two_k[66] = { 0 }, two_kup[66] = { 0 };

    for (int i = 0; i < 16; i++) //将16个16进制转换成16个4位二进制:变成64位
    {
        if (m1[i] >= '0' && m1[i] <= '9')
            num = m1[i]-'0';
        else
            num = m1[i] - 'A' + 10;
        two[++idx] = (num >> 3) & 1;
        two[++idx] = (num >> 2) & 1;
        two[++idx] = (num >> 1) & 1;
        two[++idx] = num & 1;
    }

    idx = 0;
    QChar *b2=new QChar[m.length()];    //把QString类型密钥转为char类型使用，存放在k1中
    char k1[m.length()];
    b2=k.data();
    for(int i=0;i<m.length();i++)
        k1[i]=b2[i].toLatin1();

    for (int i = 0; i < 16; i++) //k密钥转2进制
    {
        if (k1[i] >= '0' &&k1[i] <= '9')
            num = k1[i]-'0';
        else
            num = k1[i] - 'A' + 10;
        two_k[++idx] = (num >> 3) & 1;
        two_k[++idx] = (num >> 2) & 1;
        two_k[++idx] = (num >> 1) & 1;
        two_k[++idx] = num & 1;
    }

    //生成子密钥///
    /*
    求16个子密钥
    功能：由密钥生成16轮加密所用的子密钥
    */
    //用pc_1得到k+(将密钥用pc_1置换)
    for (int i = 1; i <= 56; i++)
        two_kup[i] = two_k[pc_1[i]];
    //左右分组
    node c_and_d[20];
    for (int i = 1; i <= 28; i++)   //得到c[0];
        c_and_d[0].c[i] = two_kup[i];
    for (int i = 1, j = 29; j <= 56; i++, j++)  //得到d[0];
        c_and_d[0].d[i] = two_kup[j];

    //16轮生成每轮子密钥
    for (int i = 1; i <= 16; i++) //得到c[1]-c[15],d[1]-d[15],CnDn;
    {
        ///把移一位和移两位的用一个if语句分开
        //如果为第1、2、9、16轮，则d循环左移1位
        if (i == 1 || i == 2 || i == 9 || i == 16)
        {
            for (int j = 1; j <= 27; j++)
                c_and_d[i].c[j] = c_and_d[i - 1].c[j + 1];
            c_and_d[i].c[28] = c_and_d[i - 1].c[1];
            for (int j = 1; j <= 27; j++)
                c_and_d[i].d[j] = c_and_d[i - 1].d[j + 1];
            c_and_d[i].d[28] = c_and_d[i - 1].d[1];
        }
        //如果是其他轮次，则d循环左移2位
        else
        {
            for (int j = 1; j <= 26; j++)
                c_and_d[i].c[j] = c_and_d[i - 1].c[j + 2];
            c_and_d[i].c[27] = c_and_d[i - 1].c[1];
            c_and_d[i].c[28] = c_and_d[i - 1].c[2];
            for (int j = 1; j <= 26; j++)
                c_and_d[i].d[j] = c_and_d[i - 1].d[j + 2];
            c_and_d[i].d[27] = c_and_d[i - 1].d[1];
            c_and_d[i].d[28] = c_and_d[i - 1].d[2];
        }
        for (int j = 1; j <= 28; j++)
            c_and_d[i].cd[j] = c_and_d[i].c[j];
        for (int j = 29, t = 1; t <= 28; j++, t++)
            c_and_d[i].cd[j] = c_and_d[i].d[t];
    }

    //PC_2置换后打印16轮子密钥
    node k_16[20];
    for (int i = 1; i <= 16; i++) //得到k1-kn;
        for (int j = 1; j <= 48; j++)
            k_16[i].k_n[j] = c_and_d[i].cd[pc_2[j]];


    //明文加密///
    /*
    DES算法主函数
    功能：实现DES算法的16轮加密
    */
    int ip[80] = { 0 };
    //初始变换ip
    for (int i = 1; i <= 64; i++)
        ip[i] = two[pc_ip[i]];

    //初始化得到 l[0],r[0]
    node l_r[20];
    for (int i = 1; i <= 32; i++) //得到l（左半部分）;
        l_r[0].l[i] = ip[i];
    for (int i = 1, j = 33; j <= 64; i++, j++) //得到r（右半部分）;
        l_r[0].r[i] = ip[j];

    //choice=0时是加密操作，choice=1时是解密操作
    //进行16轮运算
    if (choice == 0)
    {
        for (int i = 1; i <= 16; i++) //计算L1-L16，R1-R16;
        {
            for (int j = 1; j <= 32; j++)
                //64比特数据右半部分赋给下一轮的左半部分
                l_r[i].l[j] = l_r[i - 1].r[j];
            //F函数包含E盒扩展、异或、S盒压缩、P盒置换
            f(l_r[i - 1].r, k_16[i].k_n);
            //左右两部分结合，两者进行最终按位异或得到r[i]
            for (int j = 1; j <= 32; j++)
                l_r[i].r[j] = l_r[i - 1].l[j] ^ l_r[i - 1].r[j];
        }
    }
    else
    {
        for (int i = 1; i <= 16; i++) //计算L1-L16，R1-R16;
        {
            for (int j = 1; j <= 32; j++)
                l_r[i].l[j] = l_r[i - 1].r[j];
            f(l_r[i - 1].r, k_16[16 - i + 1].k_n);
            //^异或运算符
            for (int j = 1; j <= 32; j++)
                l_r[i].r[j] = l_r[i - 1].l[j] ^ l_r[i - 1].r[j];
        }
    }

    int R32L32[80] = { 0 }; //得到R32L32;
    //执行完F轮函数后左右半部分合在一起（交换左、右32比特）
    for (int i = 1; i <= 32; i++)
        R32L32[i] = l_r[16].r[i];
    for (int i = 33, j = 1; j <= 32; j++, i++)
        R32L32[i] = l_r[16].l[j];

    int ans[80] = { 0 }; //得到最终变换,64比特密文;
    //进行ip逆置换
    for (int i = 1; i <= 64; i++)
        ans[i] = R32L32[pc_reverse_ip[i]];

    //choice=0时是加密操作，choice=1时是解密操作
    int ten_num;

    if (choice == 0)
    {
       // global_miwen="";
        //字节转换成字符输出密文
        for (int i = 1; i <= 64; i += 4)
        {
            ten_num = ans[i] * 8 + ans[i + 1] * 4 + ans[i + 2] * 2 + ans[i + 3] * 1;
            if (ten_num >= 10)
                global_miwen+=((ten_num - 10) + 'A');
            else
                global_miwen+=(ten_num + '0');
        }
    }
    else
    {
        int change[1000];
        int pos = 0;
        for (int i = 1; i <= 64; i += 4)
        {
            ten_num = ans[i] * 8 + ans[i + 1] * 4 + ans[i + 2] * 2 + ans[i + 3] * 1;
            change[++pos] = ten_num;
        }
        int jieans = 0;
        for (int i = 1; i <= 16; i += 1,index+=1)
        {
            jieans += change[i];
            jieans += 16*global_sixteen[index];
            global_mingwen+=jieans;
            jieans = 0;
        }
    }
}




void MainWindow::on_pushButton_clicked()
{
    k = "";
    srand((int)time(0));

    //把QString数据转换为char,存放在mingwen数组中
    QString mingwen_1;
    mingwen_1=ui->txtmingwen->toPlainText().trimmed();

    QChar *b3=new QChar[mingwen_1.length()];
    char mingwen[mingwen_1.length()];
    b3=mingwen_1.data();
    for(int i=0;i<mingwen_1.length();i++)
        mingwen[i]=b3[i].toLatin1();

    int num;
    for (int i = 1; i <= 16; i++)
        num = rand() % 16, k += mikey[num];
    ui->miyao->setText(k);

    int len = sizeof(mingwen);
    int idx = 0;

    QChar sixteen[2000], H[1000];
    int now = 0;

    //sixteen文本对应的16进制数，global_sixteen是文本ASCII码整除16，用于数据转换
    memset(global_sixteen,0,sizeof(global_sixteen));
    for (int i = 0; i < len; i++) //文本转16进制
    {
        int k=2;
        while (--k)
        {
            if (mingwen[i] % 16 >= 10)
                H[++idx] = (mingwen[i] % 16 - 10) + 'A';
            else
                H[++idx] = (mingwen[i] % 16) + '0';
            //mingwen[i] /=16;
            global_sixteen[i+1]=mingwen[i]/16;
        }
        //倒序存入
        for (int j = idx; j >= 1; j--)
            sixteen[++now] = H[j];
        idx = 0;
    }

    //不够16位补0；
    while (now % 16)
    {
        ++now;
        sixteen[now] = '0';
    }

    int sum = 0;
    QString m = "";

    index=1;
    for (int i = 1; i <= now; i++)  //每64位加密一次；
    {
        sum++;
        m += sixteen[i];
        if (sum == 16)
        {
            sum = 0;
            jiami_or_jiemi(m, 0);
            m = "";
        }
     }
    ui->miwen->setText(global_miwen);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString out_miyao;
    QString out_miwen;
    out_miyao.clear();
    out_miwen.clear();
    out_miyao=ui->input_miyao->text().trimmed();
    QString global_mingwen_1;   //临时存放明文数据，按键事件结束就清空
    if(QString::compare(out_miyao,k)==0)    //判断密钥正确
    {
        out_miwen=ui->input_miwen->toPlainText().trimmed();
        int len = out_miwen.length();

        QChar *b4=new QChar[len]; //将SQtring类型转换为char类型
        char out_global_miwen[len];
        b4=out_miwen.data();
        for(int i=0;i<len;i++)
            out_global_miwen[i]=b4[i].toLatin1();

        int sum = 0;
        QString m1 = "";
        for (int i = 0; i < len; i++) //每64位解密一次；
            {
                 sum++;
                 m1 += out_global_miwen[i];
                 if (sum == 16)
                     {
                          sum = 0;
                          jiami_or_jiemi(m1, 1);
                          m1 = "";
                      }
               }
        global_mingwen_1=global_mingwen;
        ui->output_mingwen->setText(global_mingwen_1);
        global_mingwen_1.clear();
        out_miwen.clear();
        out_miyao.clear();
        index=0;
    }
    else     //密钥错误
    {
        ui->output_mingwen->setText("密钥错误");
        global_mingwen_1.clear();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    global_mingwen.clear();
    global_miwen.clear();
}
