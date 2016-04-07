//
//  main.c
//  iOS-单链表操作
//
//  Created by 康蕤 刘 on 16/4/7.
//  Copyright © 2016年 康蕤 刘. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int Element;

//  定义节点结构
struct None{
    Element data;  //数据域
    struct None *next;  //指针域
}None;

typedef struct None LNone;

///  创建单链表
LNone * createLinkList();   //不带头字节的链表
LNone * createLinkList(){
    
    LNone *head = NULL;  // 头
    LNone *tail = NULL;  // 尾
    LNone *temp = NULL;  // 临时节点，指向当前创建的元素
    
    int data;
    scanf("%d",&data);  // 在控制台输入数据，用来放在链表中,输入0时结束插入
    
    while (data) {
        temp = (LNone *)malloc(sizeof(LNone));   //temp 初始化
        if (!temp) {
            printf("初始化失败");
        }else{
            temp->data = data;
            temp->next = NULL;
        }
        if (head == NULL) {
            head = temp;
            tail = temp;
        }else{
            tail->next = temp;
            tail = temp;
        }
        
        scanf("%d",&data);
    }
    
    return head;
}

/// 控制台输出单链表
void printLinkList(LNone *head);
void printLinkList(LNone *head){
    LNone *p = head;
    while (p) {
        printf("%d\t",p->data);
        p = p->next;
    }
}

/// 获取列表长度
int length(LNone *head);
int length(LNone *head){
    int len = 0;
    LNone *p = head;
    while (p) {
        len++;
        p = p->next;
    }
    
    return len;
}

/// 返回第pos个节点的元素
int getElenment(LNone *head,int pos);
int getElenment(LNone *head,int pos){
    int data = 0;
    LNone *p = head;
    //判断pos是否超出了链表长度
    if (pos > length(head) || pos <= 0) {
        return data;
    }
    
    for (int i = 0; i < pos - 1; i ++) {
        //循环pos - 1次
        p = p->next;
    }
    data = p->data;
    
    return data;
}

/// 输入单列表的节点 修改节点的值
int modifyElement(LNone *head,int pos,Element newElement);
int modifyElement(LNone *head,int pos,Element newElement){
    int success = 0;
    
    LNone *p = head;
    //判断pos是否超出了链表长度
    if (pos > length(head) || pos <= 0) {
        return success;
    }
    
    for (int i = 0; i < pos - 1; i++) {
        p = p->next;
    }
    
    if (p) {
        p->data = newElement;
        success = 1;
    }
    
    return success;
}

///  向单链表的表首插入一个元素
int insertElementToHead(LNone **head,Element e);
int insertElementToHead(LNone **head,Element e){
    int success = 0;
    LNone *tmp = NULL;
    
    if (e) {
        tmp = (LNone *)malloc(sizeof(struct None));
        if (tmp) {
            tmp->data = e;
            tmp->next = NULL;
        }
    }else{
        printf("初始化失败");
        return success;
    }
    tmp->next = *head;
    *head = tmp;
    success = 1;
    
    return success;
}

///  向单链表的表尾插入一个元素
int insertElementToEnd(LNone *head,Element e);
int insertElementToEnd(LNone *head,Element e){
    int success = 0;
    LNone *tmp = NULL;
    LNone *p = head;
    
    if (e) {
        tmp = (LNone *)malloc(sizeof(LNone));
        tmp->data = e;
        tmp->next = NULL;
    }else{
        printf("oops:zero is invalid");
        return success;
    }
    
    while (p&&p->next) {
        p = p->next;
    }
    p->next = tmp;
    success = 1;
    
    return success;
}

///  向pos未知插入元素
int insertElementToPos(LNone *head,Element e,int pos);
int insertElementToPos(LNone *head,Element e,int pos)
{
    int success = 0;
    LNone *tmp = NULL;
    LNone *p = head;
    
    if (e) {
        tmp = (LNone *)malloc(sizeof(LNone));
        tmp->data = e;
        tmp->next = NULL;
    }else{
        printf("初始化失败");
        return success;
    }
    
    if (pos <= 0 || pos>length(head)) {
        return success;
    }
    
    for (int i = 0; i < pos - 1; i++) {
        p = p->next;
    }
    tmp->next = p->next;
    p->next = tmp;
    success = 1;
    
    return success;
}

int insertOrderLinkList(LNone *head,Element x);
int insertOrderLinkList(LNone *head,Element x)
{
    int sussecc = 0;
    int loc = 1;
    LNone *p = head;
    while (p)
    {
        if (p->data < x)
        {
            p = p->next;
            loc++;
        }
        else
        {
            break;
        }
    }
    
    sussecc = insertElementToPos(head, x, loc);
    
    return sussecc;
}

/// 删除头节点
int deleteHeadNode(LNone **head);
int deleteHeadNode(LNone **head){
    int data = 0;
    LNone *p = *head;
    data = p->data;
    *head = p->next;
    
    return data;
}

/// 删除结尾的节点
int deleteEndNode(LNone *head);
int deleteEndNode(LNone *head){
    int data = 0;
    LNone *p = head;
    LNone *q = NULL;
    if (length(head) < 2) {
        return data;
    }
    while (p->next && p->next->next) {
        p = p->next;
    }
    q = p->next;
    p->next = NULL;
    data = q->data;
    free(q);
    return data;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    LNone *head;
    head = createLinkList();
    printLinkList(head);
    printf("链表长度 = %d\n",length(head));
    
    // 1、返回pos节点中的元素。
    printf("返回pos节点的元素:%d\n",getElenment(head,2));
    //  2、修改pos节点中得元素。
    printf("pos节点的元素修改是否成功:%d\n",modifyElement(head,2,20));
    printLinkList(head);
    
    
    // 3、向单链表的表头插入一个元素。
    printf("\n");
    insertElementToHead(&head, 90);
    printLinkList(head);
    
    // 4、向单链表的末尾添加一个元素。
    printf("\n");
    insertElementToEnd(head, 80);
    printLinkList(head);
    
    //5、
    printf("\n");
    insertElementToPos(head, 100, 1);
    printLinkList(head);
    
    //6、
    printf("\n");
    insertElementToEnd(head, 120);
    printLinkList(head);
    
    //7、
    printf("\n");
    deleteHeadNode(&head);
    printLinkList(head);
    
    //8、
    printf("\n");
    deleteEndNode(head);
    printLinkList(head);
    
    printf("\n");
    return 0;
    
}
