#include <stdio.h>
#include <malloc.h>

struct node
{
    int data;
    struct node  *link;
};

/*int empty(struct node *head)*/
/* 该函数判断链表是否为空，如果为空则返回整数值1 */
int empty(struct node *head)
{
     int k = 0;
     
     // 确定链表是否为空
     if(head == NULL)
        k = 1;
    
    return k;
}
// 函数empty检测表头节点，如果链表为空，函数返回1，否则返回0。

/* void  print_list(struct node *head)  */
/* 该函数从链表头部开始，输出每个节点中的数据值，直至链表结尾*/
void  print_list(struct node *head)
{
    struct  node  *next;

    //输出链表
    if(empty(head))
        printf("Empty list！\n");
    else
    {
        printf("List Values:\n");
        next = head;

        while(next->link != NULL)
        {
            printf("%d \n",next->data);
            next = next->link;
        }
        printf("%d \n", next->data);
    }
       
}

/* void insert(struct node **ptr_to_head, struct node *nw)*/
/* 该函数在链表中插入一个新节点*/
void insert(struct node **ptr_to_head, struct node *nw)
{
    struct node **next;

    //检查是否为空链表
    if(empty(*ptr_to_head))
    {
        *ptr_to_head = nw;
    }
    else  //遍历链表，找到正确的插入位置
    {
        next = ptr_to_head;
        while(((*next)->data < nw->data) && ((*next)->link != NULL) )
        next = &(*next)->link;

        //检查插入值是否已存在
        if((*next)->data == nw->data)
            printf("Node already in list.\n");
        else
        {
            if((*next)->data < nw->data)  //检查是否在尾节点之后插入
                 (*next)->link = nw ;
            else
            {
                nw->link = *next;
                *next = nw;
            }
        }
    }
    
}
/*void remove(struct node **prt_to_head, int old)*/
/*该函数从链表中删除一个节点*/
/*该函数从链表的表头开始，逐一查找数据值为old的节点。如果没有找到该节点，则打印相关信息。如果找到了，便删除该节点，并释放内存 */
void remover(struct node **prt_to_head, int old)
{
    struct node *next,*last,*hold,*head;

    //检查是否为空链表
    head = *prt_to_head;

    if(empty(head)) 
        printf("Empty list.\n");
    else
    {
        //检查是否删除第一个节点
        if(head->data == old)
         {
             //删除第一个节点
             hold = head;
             *prt_to_head = head->link;
             free(hold);
         }
         else
         {
             //遍历链表寻找值为old的节点
             next = head->link;
             last = head;

             while((next->data < old) && (next->link != NULL))
             {
                 last = next;
                 next = next->link;
             }
             //如果找到该节点，则删除节点
             if(next->data == old)
             {
                 if(next->link!=NULL)
                {
                    hold = next;
                   last->link = next->link;
                   free(hold);

                } 
                else
                 {
                     last->link = NULL;
                     hold = next;
                     free(hold);
                 }
             }
             else
                printf("Value %d not in list.\n",old);
         }

    }  
}

int main(void)
{
    int k=0, old, value;
    struct node *head,*next, *previous,*nw,**ptr_to_head = &head;

    //生成一个拥有5个节点的链表，并打印该链表
    head = (struct node*)malloc(sizeof(struct node));
    next = head;

    for(k=1;k<=5;k++)
    {
        next->data = k * 5;
        next->link = (struct node*)malloc(sizeof(struct node));
        previous = next;
        next = next->link;
    }
    previous->link = NULL;
    print_list(head);

    // 允许用户在链表中插入或删除节点
    while(k != 2)
    {
        printf("Enter 0 to delete node,1 to add node, 2 to quit.\n");
        scanf("%d",&k);
        if(k==0)
        {
            printf("Enter data value to delete:\n");
            scanf("%d",&old);
            remover(ptr_to_head,old);
            print_list(head);
        }
        else
        {
            if(k == 1)
            {
                printf("Enter data value to add:\n");
                scanf("%d",&value);
                nw = (struct node*)malloc(sizeof(struct node));
                nw->data = value;
                nw->link = NULL;
                insert(ptr_to_head,nw);
                print_list(head);
            }

        }

        return 0;
    }    
    
}
