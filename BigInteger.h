// square.h
#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct BigInteger {
    int length;
    node* list;
    char sign;
} BigInteger;

node* createnode(int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}

node* createlist(char* s);
BigInteger createBigInteger(); 
BigInteger initialize(char* s);
node* reverse(node* head);
int length(node* ptr);
BigInteger add(BigInteger a, BigInteger b);
BigInteger sub(BigInteger a, BigInteger b);
BigInteger multiply(BigInteger a, BigInteger b);
int cmplist(node* a,node* b);
void dump(struct BigInteger c);
struct BigInteger div1(struct BigInteger a , struct BigInteger b );
struct node *duplicate(struct node *head);
struct BigInteger division(struct BigInteger a , struct BigInteger b , int sign , int choice);
int compare(struct BigInteger h1 , struct BigInteger h2);
int compare_sub(struct node *h1 , struct node *h2);
void div_add(struct node *p1 ,struct node *p2 ,struct node *p3 , int *l);
void div_sub(struct node *p1 ,struct node *p2 ,struct node *p3 );
void display(BigInteger n1);
void tnct(struct BigInteger tmp);
void revsign(struct node *head);
struct BigInteger mod(struct BigInteger a , struct BigInteger b);
struct BigInteger addminus(struct BigInteger a, struct BigInteger b,int sign);
#endif
