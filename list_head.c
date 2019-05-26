#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_head{
    struct list_head * prev;
    struct list_head * next;
};

#define MALLOC(type) (type *)malloc(sizeof(type)) 

//初始化链表
#define LIST_HEAD_INIT(name)   { &(name), &(name)}
//声明并初始化链表
#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

//计算链表节点的起始地址
#define list_entry(ptr,type,member)\
    ((type *) ( (char*)(ptr) - (unsigned long)(&((type*)0)->member)))
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head);pos = pos->next)
//根据给定的前驱和后继,将节点插入链表
static inline void 
list_add(struct list_head *new,
        struct list_head *prev,
        struct list_head * next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}
//在表头插入节点
static inline void
list_add_head(struct list_head *new,
            struct list_head *head)
{
    list_add(new, head, head->next);
}
//在表尾插入节点
static inline void
list_add_tail(struct list_head *new,
            struct list_head *head)
{
    list_add(new, head->prev, head);
}

struct student{
    char name[20];
    unsigned long number;
    struct list_head list;
};

int main(){
    
    struct student * tmp = NULL;
    struct list_head head = LIST_HEAD_INIT(head);

    
    for (int i = 1; i < 7;i++){
        tmp = MALLOC(struct student);
        scanf("%s %lu",tmp->name,&tmp->number);
        list_add_tail(&(tmp->list), &head);
    }
   
    struct list_head * pos = NULL;
    
    list_for_each(pos, &head){
        struct student * p = list_entry(pos, struct student, list);
        printf("%s %lu\n", p->name, p->number);
    }
    return 0;
}