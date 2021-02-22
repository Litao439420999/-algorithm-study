
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAD_INFO  "学号\t姓名\t语文\t数学\t英语\t专业课\t总分\t平均分\n"
#define HEAD_INFO2 "学号\t姓名\t语文\t数学\t英语\t专业课\n" 
// 定义学生信息数据结构 
struct student{
  // 学号 
  int    num;
  // 姓名 
  char  name[20];
  // 语文 
  int   chinese;
  // 数学
  int   math;
  // 英语
  int   english;
  // 专业课
  int   profession; 
  // 总分
  int    total;
  // 平均分
  double   average; 
};
// 定义链表结点结构类型
struct node
{
  struct student  stu;
  struct node    *next;
};

/*
  定义各种功能函数
*/
// 显示功能菜单
void showMenu();  
// 录入信息 
void addStudent(struct node *head);
// 删除信息  
void deleteStudent(struct node *head); 
// 查询信息 
void queryStudent(struct node *head); 
// 修改信息
void modifyStudent(struct node *head);
// 成绩排序
void sortStudent(struct node *head);
// 显示所有
void showStudent(struct node *head);
// 保存信息
void saveStudent(struct node *head); 
// 退出
void exitProgram(struct node *head); 
// 定义链表基本操作函数 
struct node *createStudentNode(struct student *stu);
struct node *insertStudentNode(struct node *head, struct student *stu);
struct node *createStudentList(); 
void         freeStudentList(struct node* head); 
struct node *queryStudentListByNum(struct node* head, int num);
struct node *queryStudentListByName(struct node* head, char *name);
int      deleteStudentListByNum(struct node* head, int num);
int      getStudentListLength(struct node* head); 
struct node *sortStudentListByTotal(struct node *head);
struct node *sortStudentListByAverage(struct node *head);
void         printStudentListInfo(struct node* head);
void         saveStudentListToFile(struct node* head);
void         error(const char* err);

int main() {
  // 创建学生成绩空链表保存信息 
  struct node* list = createStudentList(); 
  // 显示功能主菜单 
  showMenu();    
  char a[10];  
  while (1) {
    printf("\n请输出0-8,回车结束！\n");
    if (fgets(a, 10, stdin) != NULL) {  
      switch (a[0]) {
      case '0':  
        exitProgram(list);
        break;
      case '1':  
        addStudent(list);
        break;
      case '2':  
        deleteStudent(list);
        break;
      case '3':    
        queryStudent(list);
        break;
      case '4':  
        modifyStudent(list);
        break;
      case '5':  
        sortStudent(list);
        break;
      case '6':  
        showStudent(list);
        break;
      case '7':
        saveStudent(list);
        break;
      case '8':
        showMenu();
        break;
      default:
        printf("请重新输入正确的功能数字0-8!\n");
      }
    }
  }
  return 0;
}
// 创建学生成绩结点
struct node *createStudentNode(struct student *stu)
{
  struct node* p = (struct node*)calloc(1,sizeof(struct node));
  if(stu != NULL)
  {
    struct student *s = &(p->stu);
    if(p != NULL)
    {
      s->num = stu->num;
      strcpy(s->name, stu->name);
      s->chinese = stu->chinese;
      s->math = stu->math;
      s->english = stu->english;
      s->profession = stu->profession;
      // 计算成绩
      s->total = s->chinese + s->math + \
             s->english + s->profession;
      s->average = s->total*1.0/4; 
      p->next = NULL;
    }
  }
  return p;
} 
// 表尾增加学生成绩 
struct node *insertStudentNode(struct node *head, struct student *stu)
{
  struct node *node = NULL;
  if(head != NULL)
  {
    node =  createStudentNode(stu);
    struct student *s = &(node->stu);
    if(node != NULL)
    {
      struct node* p = head;
      // 循环找到链表最后的结点
      while(p->next != NULL)
        p = p->next;
      p->next = node;
    }
  }
  return node;
}
// 创建带头结点的学生成绩空链表
struct node *createStudentList()
{
  // 创建头结点
  return createStudentNode(NULL);
}
// 释放学生成绩链表内存空间
void freeStudentList(struct node* head)
{
  struct node* p = head;
  while(p != NULL)
  {
    head = p->next;
    free(p);
    p = head;
  }
}
// 根据学号查找学生成绩 
struct node *queryStudentListByNum(struct node* head, int num)
{
  
  struct node *p = NULL;
  if(head != NULL)
  {
    p = head->next;
    while(p != NULL)
    {
      if(p->stu.num == num)
        break;
      p = p->next;
    }
  }
  return p;
} 
// 根据姓名查找学生成绩 
struct node *queryStudentListByName(struct node* head, char *name)
{
  
  struct node *p = NULL;
  if(head != NULL)
  {
    p = head->next;
    while(p != NULL)
    {
      if(strcmp(p->stu.name, name) == 0)
        break;
      p = p->next;
    }
  }
  return p;
} 
// 根据学号删除学生成绩 
int deleteStudentListByNum(struct node* head, int num)
{
  // p保存当前结点，pre保存前一个结点 
  struct node *p = NULL, *pre = NULL;
  // 返回结果0或1
  int status = 0; 
  if(head != NULL)
  {
    pre = head;
    p = head->next;
    while(p != NULL)
    {
      if(p->stu.num == num)
      {
        pre->next = p->next;
        free(p);
        status = 1;        
        break;
      }
      pre = p;
      p = p->next;
    }
  }
  return status;
} 

// 获取学生成绩链表的长度 
int getStudentListLength(struct node* head)
{
  int n = 0;
  struct node *p = NULL;
  if(head != NULL)
  {
    p = head->next;
    while(p != NULL)
    {
      n++;
      p = p->next;
    }
  }
  return n;
}
// 按总分从高到低排序学生成绩
struct node *sortStudentListByTotal(struct node *head)
{
  if(head != NULL)
  {
    struct node *p1, *p2, *max; 
    struct student s;
    
    p1 = head;
    // 简单选择排序
    // 直接交换信息，不改变结点 
    while((p1=p1->next) != NULL)
    {
      max = p1;
      p2 = p1;
      while((p2=p2->next) != NULL)
      {
        if((p2->stu).total > (max->stu).total)
          max = p2;
      }
      
      if(max != p1)
      {
        s = p1->stu;
        p1->stu = max->stu;
        max->stu = s;
      }    
    } 
  }
  return head;
}
 
// 按平均分从小到大排序学生成绩
struct node *sortStudentListByAverage(struct node *head)
{
  if(head != NULL)
  {
    struct node *p1, *p2, *min; 
    struct student s;
    
    p1 = head;
    // 简单选择排序
    // 直接交换信息，不改变结点 
    while((p1=p1->next) != NULL)
    {
      min = p1;
      p2 = p1;
      while((p2=p2->next) != NULL)
      {
        if((p2->stu).average < (min->stu).average)
          min = p2;
      }
      
      if(min != p1)
      {
        s = p1->stu;
        p1->stu = min->stu;
        min->stu = s;
      }    
    } 
  }
  return head;
}

// 打印出链表所有结点保存的图书信息
void printStudentListInfo(struct node* head)
{
  struct node* p = head->next;
  printf(HEAD_INFO);
  struct student *s;
  while(p != NULL)
  {
    s = &(p->stu);
    printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.2lf\n", s->num, s->name, \
        s->chinese, s->math, s->english, s->profession, \
        s->total, s->average);
    p = p->next;
  }
}

// 文件保存学生成绩链表所有信息
void saveStudentListToFile(struct node* head)
{
  if(head != NULL)
  {
    struct node *p = head->next;
    FILE* fp = fopen("students.txt", "w+");
    if(fp != NULL)
    {
      struct student *s;
      while(p != NULL)
      {
        s = &(p->stu);
        fprintf(fp,"%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.2lf\n", s->num, s->name, \
             s->chinese, s->math, s->english, s->profession,     \
               s->total, s->average);
        p = p->next;
      }
      fclose(fp); 
    }else { 
      error("打开students文件失败，请检查!\n");
    }  
  }
} 
// 屏幕显示各类出错信息，并退出程序
void error(const char* err)
{
  printf(err);
  exit(-1);
} 

void showMenu() 
{
  
  printf("\t*************欢迎使用学生成绩管理系统*************\t\n");
  printf("\t*  1:录入成绩                        2:删除成绩  *\t\n");
  printf("\t*  3:查询成绩                        4:修改成绩  *\t\n");
  printf("\t*  5:成绩排序                        6:显示所有  *\t\n");
  printf("\t*  7:保存成绩                        8:显示菜单  *\t\n");
  printf("\t*  0:退出系统                                    *\t\n");
  printf("\t**************************************************\t\n");
}
// 录入信息 
void addStudent(struct node *head) {
  printf("请您按提示依次输入图书信息（以空格分隔）：\n");
  printf(HEAD_INFO2);
  char a[1024];
  struct student stu;
  if (fgets(a, 1024, stdin) != NULL &&         \
      sscanf(a, "%d%s%d%d%d%d", &stu.num, \
      stu.name, &stu.chinese, &stu.math,   \
      &stu.english, &stu.profession) >= 6) {
    if (queryStudentListByNum(head, stu.num) != NULL)
      printf("该学生成绩信息已经存在，无法增加!\n");
    else {
      insertStudentNode(head, &stu);
      printf("学生【%d\t%s】的信息添加成功！\n", stu.num, stu.name);
    }
  }
  else {
    printf("输入格式有误，请重新输入!\n");
  }
}
// 删除信息  
void deleteStudent(struct node *head)
{
  printf("请输入要删除的学生学号：");
  char a[1024];
  int num;
  if (fgets(a, 1024, stdin) != NULL && \
       sscanf(a, "%d", &num) != EOF) {
    if (deleteStudentListByNum(head, num))
    {
      printf("学号%d对应的学生信息删除成功!\n", num);
      
    }else
    {
      printf("学号%d对应的学生信息不存在!\n", num);
    }
  }
  else {
        printf("输入格式有误，请重新输入!\n");
  }
}
// 查询信息 
void queryStudent(struct node *head)
{
  printf("请选择查询方式：1.学号查询  2.姓名查询 \n");
  char a[1024];  
  if (fgets(a, 1024, stdin) != NULL) 
  {
    if(a[0] == '1')
    {
      printf("请输入学生学号：");
      int num;
      if (fgets(a, 1024, stdin) != NULL && \
         sscanf(a, "%d", &num) != EOF) {
         struct node *p = queryStudentListByNum(head, num);
         if(p == NULL)
         {
           printf("未查到学号%d对应的学生信息!\n", num);
        }else
        {
          struct student *s = &(p->stu);
          printf(HEAD_INFO); 
          printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.2lf\n", s->num, s->name, \
                s->chinese, s->math, s->english, s->profession, \
                    s->total, s->average);  
        }  
       }else
       {
           printf("输入格式有误，请重新输入！\n");
      }
      
    }else if(a[0] == '2')
    {
      printf("请输入学生姓名：");
      char  name[20];
      if (fgets(a, 1024, stdin) != NULL && \
         sscanf(a, "%s", name) != EOF) {
         struct node *p = queryStudentListByName(head, name);
         if(p == NULL)
         {
           printf("未查到姓名%s对应的学生信息!\n", name);
        }else
        {
          struct student *s = &(p->stu);
          printf(HEAD_INFO); 
          printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.2lf\n", s->num, s->name, \
                s->chinese, s->math, s->english, s->profession, \
                    s->total, s->average);  
        }  
       }else
       {
           printf("输入格式有误，请重新输入！\n");
      }
      
    }else
    {
      printf("输入格式有误，请重新输入！\n");
    }
  }
}
// 修改信息
void modifyStudent(struct node *head)
{
  printf("请输入要修改的学生学号：");
  char a[1024];
  int num;
  if (fgets(a, 1024, stdin) != NULL &&  \
      sscanf(a, "%d", &num) != EOF)
  {    
    struct node *p = queryStudentListByNum(head, num);
    if (p == NULL)
    {
      printf("学号%d对应的学生信息不存在!\n", num);
    }else 
    {
      struct student *s = &(p->stu);
      printf("学号%d对应的学生信息如下：\n", num);
      printf(HEAD_INFO);
      printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.2lf\n", s->num, s->name, \
          s->chinese, s->math, s->english, s->profession, \
            s->total, s->average);  
      
      printf("请依次输入修改后信息,不变的信息请同样输入:\n");
      printf("姓名\t语文\t数学\t英语\t专业课\n");
          struct student stu;
      if (fgets(a, 1024, stdin) != NULL &&         \
          sscanf(a, "%s%d%d%d%d", stu.name, &stu.chinese, \
              &stu.math, &stu.english, &stu.profession) >= 5) 
      {
        strcpy(s->name, stu.name);
        s->chinese = stu.chinese;
        s->math = stu.math;
        s->english = stu.english;
        s->profession = stu.profession;
        // 计算成绩
        s->total = stu.chinese + stu.math + \
             stu.english + stu.profession;
          s->average = s->total*1.0/4; 
          printf("修改成功，修改后信息如下：\n");
          printf(HEAD_INFO);
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%.2lf\n", s->num, s->name, \
          s->chinese, s->math, s->english, s->profession, \
            s->total, s->average);  
      }else
      {
        printf("输入格式有误，请重新输入!\n");
      }
      }
    }else 
  {
    printf("输入格式有误，请重新输入!\n");
  }
}
// 成绩排序
void sortStudent(struct node *head)
{
  printf("请选择排序方式：1.总分从高到低排序  2.平均分从低到高排序 \n");
  char a[1024];  
  if (fgets(a, 1024, stdin) != NULL) 
  {
    if(a[0] == '1')
    {
      sortStudentListByTotal(head);
      printStudentListInfo(head);
      
    }else if(a[0] == '2')
    {
      sortStudentListByAverage(head);
      printStudentListInfo(head);
    }else
    {
      printf("输入格式有误，请重新输入！\n");
    }
  }else 
  {
    printf("输入格式有误，请重新输入！\n");
  } 
}
// 显示所有
void showStudent(struct node *head)
{
  printStudentListInfo(head);
  printf("当前系统总共有%d条学生成绩记录！\n", getStudentListLength(head));
}
// 保存信息
void saveStudent(struct node *head)
{
  saveStudentListToFile(head);
  printf("保存成功，信息存放在students.txt文件!\n");
}
// 退出
void exitProgram(struct node *head)
{
  freeStudentList(head);
  printf("ByeBye....~~\n");
  exit(0); 
}