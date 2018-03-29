/*************************************************************************
	> File Name: binary_non_recursive.c
	> Author: luoyi
	> Mail: 596890983@qq.com
	> Created Time: 2018年02月28日 星期三 10时26分50秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include "any_stack.h"

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node, *Trie;

Node *getNewNode(int data) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *init_binary_tree() {
    Node *root = getNewNode(1);
    root->lchild = getNewNode(3);
    root->rchild = getNewNode(6);
    root->lchild->rchild = getNewNode(9);
    root->rchild->rchild = getNewNode(11);
    root->rchild->lchild = getNewNode(14);
    root->lchild->rchild->lchild = getNewNode(17);
    return root;
}

void __preorder(Node *root) {
    //status == 0
    if(!root) return ; // status == 100
    printf("%d ", root->data); // status == 1
    __preorder(root->lchild); //status == 2
    __preorder(root->rchild); //status == 3
    return; //status == 100
}

typedef struct orderArgs {
    Node *root;
    int status;
} orderArgs;

orderArgs *getNewArgs(Node *root) {
    orderArgs *p = (orderArgs *)malloc(sizeof(orderArgs) * 1);
    p->root = root;
    p->status = 0;
    return p;
}

void pre_order(Node *root) {
    Stack *s = init_stack(100, orderArgs);
    orderArgs *temp_args = getNewArgs(root);
    push_stack(s, temp_args);
    while(!empty_stack(s)) {
        orderArgs *p_args = top_stack(s, orderArgs);
        switch(p_args->status) {
            case 0 : {
                if(p_args->root == NULL) {
                    p_args->status = 100;
                }
                else {
                    p_args->status = 1;
                }
                break;
            }
            case 1 : {
                printf("%d\n", p_args->root->data);
                p_args->status = 2;
                break;
            }
            case 2 : {
                temp_args->root = p_args->root->lchild;
                temp_args->status = 0;
                push_stack(s, temp_args);//模拟递归过程
                p_args->status = 3;
                break;
            }
            case 3 : {
                temp_args->root = p_args->root->rchild;
                temp_args->status = 0;
                push_stack(s, temp_args);//模拟递归过程
                p_args->status = 100;
                break;
            }
            case 100 : {
                pop_stack(s);
            }
        }
    }
    free(temp_args);
    clear_stack(s);
    return;
}

void __midorder(Node *root) {
    //status == 0
    if(!root) return; // status = 100
    __midorder(root->lchild); // status == 1
    printf("%d ", root->data); // status == 2
    __midorder(root->rchild);  // status == 3
    return; // status == 100
}

void mid_order(Node *root) {
    Stack *s = init_stack(100, orderArgs);
    orderArgs *temp_args = getNewArgs(root);
    push_stack(s, temp_args);
    while(!empty_stack(s)) {
        orderArgs *p_args = top_stack(s, orderArgs);
        switch(p_args->status) {
            case 0 : {
                if(p_args->root == NULL) {
                    p_args->status = 100;
                }
                else {
                    p_args->status = 1;
                }
                break;
            }
            case 1 : {
                temp_args->root = p_args->root->lchild;
                temp_args->status = 0;
                push_stack(s, temp_args);//模拟递归过程
                p_args->status = 2;
                break;
            }
            case 2 : {
                printf("%d\n", p_args->root->data);
                p_args->status = 3;
                break;
            }
            case 3 : {
                temp_args->root = p_args->root->rchild;
                temp_args->status = 0;
                push_stack(s, temp_args);//模拟递归过程
                p_args->status = 100;
                break;
            }
            case 100 : {
                pop_stack(s);
            }
        }
    }
    free(temp_args);
    clear_stack(s);
    return;
}
/*
void __postorder(Node *root) {
    //status == 0
    if(!root) return; // status = 100
    __postorder(root->lchild); // status == 1
    __postorder(root->rchild);  // status == 2
    printf("%d ", root->data); // status == 3
    return; // status == 100
}

void post_order(Node *root) {
    Stack *s = init_stack(100, PreOrderArgs);
    PreOrderArgs *temp_args = getNewArgs(root);
    push_stack(s, temp_args);
    while(!empty_stack(s)) {
        PreOrderArgs *p_args = top_stack(s, PreOrderArgs);
        switch(p_args->status) {
            case 0 : {
                if(p_args->root == NULL) {
                    p_args->status = 100;
                }
                else {
                    p_args->status = 1;
                }
                break;
            }
            case 1 : {
                temp_args->root = p_args->root->lchild;
                temp_args->status = 0;
                push_stack(s, temp_args);//模拟递归过程
                p_args->status = 2;
                break;
            }
            case 2 : {
                temp_args->root = p_args->root->rchild;
                temp_args->status = 0;
                push_stack(s, temp_args);//模拟递归过程
                p_args->status = 3;
                break;
            }
            case 3 : {
                printf("%d\n", p_args->root->data);
                p_args->status = 100;
                break;
            }
            case 100 : {
                free(temp_args);
                pop_stack(s);
            }
        }
    }
    clear_stack(s);
    return;
}
*/

int main() {
    Node *root = init_binary_tree();
    pre_order(root);
    mid_order(root);/*
    post_order(root);*/
    return 0;
}
