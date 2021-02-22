
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define  MAXLEN  50 //定义栈结构的最大长度

typedef struct
{
   char  name[10];  //姓名
   int   age;      //年龄
}Data;

typedef struct stack
{
    Data  data[MAXLEN];  //数据元素
    int   top ;          //栈顶   top为0时表示栈空，top为MAXLEN-1表示栈满。
}Student;


//初始化顺序栈
Student  *StInit()
{
    Student  *p;
    
    if(p=(Student *)malloc(sizeof(Student)))
    {
        p->top = 0; //设置栈顶为0;
        return p;  //返回指向栈的指针
    }

    return NULL;
}

//判断空栈
int StIsEmpty(Student *s)
{    
    int t;
    t = s->top==0?1:0;

    return t;
}

//判断栈满
int  StzIsFull(Student *s)
{
    int t;
    t = s->top == MAXLEN - 1?1:0;

    return t;
}

//清空栈
void  StClear(Student *s)
{
    s->top == 0;
}

//释放空间
void StFree(Student *s)
{
    if(s)
      free(s);
}

//入栈
int PushSt(Student *s, Data data)
{
    if(s->top >= MAXLEN)
    {
        printf("栈溢出!\n");
        return 0;
    }
    s->data[++s->top] = data;  //将元素入栈

    return 1;
}

//出栈
Data PopSt(Student *s)
{
    if(s->top==0)
    {
        printf("栈为空！\n");
        exit(0);
    }

    return (s->data[s->top--]);
}

//读栈顶数据
Data PeekSt(Student *s)
{
     if(s->top==0)
    {
        printf("栈为空！\n");
        exit(0);
    }

    return (s->data[s->top]);
}

int main(void)
{
    Student *s;
    Data d1,d2;

    s = StInit();
    printf("入栈操作:\n");
    printf("输入姓名  年龄进行入栈:\n");

    do{
        scanf("%s%d",d1.name,&d1.age);
        if(strcmp(d1.name,"0")==0)
            break;  //若输入0，则退出
        else
        {
            PushSt(s,d1);
        }
    }while(1);
    printf("\n");
    do{
        printf("出栈操作：按任意键进行出栈操作：\n");
        getchar();   //输入任意字符
        d2 = PopSt(s);
        printf("出栈数据是(%s, %d)\n",d2.name,d2.age);
    } while(1);   

    StFree(s);

    return 0;
            
}
//在这里主函数首先初始化栈结构，然后循环进行入栈操作，添加数据结点，当输入值全部为0 时则退出结点添加的进程。接下来，用户每按一次键，则进行一次出栈操作，显示结点数
//据 。当为空栈时，退出程序。