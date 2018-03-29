/*************************************************************************
	> File Name: quick_sort_non_recursive.c
	> Author: luoyi
	> Mail: 596890983@qq.com
	> Created Time: 2018年02月28日 星期三 14时52分56秒
 ************************************************************************/

#include<stdio.h>
#include "any_stack.h"

#define swap(a, b) { \
    *(a) = (*(a))^(*(b)); \
    *(b) = (*(b))^(*(a)); \
    *(a) = (*(a))^(*(b)); \
}
/*
void __quick_sort(int *data, int left, int right) {
    //status == 0
    if(left >= right) return; 
    //status == 1
    int l = left, r = right, target = data[l];
    while(l < r) {
        while(l < r && data[r] >= target) r--;
        if(l < r) swap(data + l, data + r);
        while(l < r && data[l] <= target) l++;
        if(l < r) swap(data + l, data + r);
    }
    data[l] = target;
    quick_sort(data, left, l - 1); // status == 2
    quick_sort(data, l + 1, right); // status == 3
    return; // status == 4
}*/

typedef struct quick_sort_node {
    int left, right, status, l, r;
} quick_sort_node;
 
quick_sort_node *getnewNode(int l, int r) {
    quick_sort_node *p = (quick_sort_node *)malloc(sizeof(quick_sort_node));
    p->left = p->l = l;
    p->right = p->r = r;
    p->status = 0;
    return p;
}

void quick_sort(int *data, int left, int right) {
    Stack *s = init_stack(right - left + 1, quick_sort_node);
    quick_sort_node *p = getnewNode(left, right);
    push_stack(s, p);
    while(!empty_stack(s)) {
        quick_sort_node *top = top_stack(s, quick_sort_node);
        switch(top->status) {
            case 0: {
                if(top->left >= top->right) {
                    top->status = 4;
                } else {
                    top->status = 1;
                }
                break;
            }
            case 1: {
                top->l = top->left, top->r = top->right; 
                int target = data[top->l];
                while(top->l < top->r) {
                    while(top->l < top->r && data[top->r] >= target) 
                        top->r--;
                    if(top->l < top->r) swap(data + top->l, data + top->r);
                    while(top->l < top->r && data[top->l] <= target) 
                        top->l++;
                    if(top->l < top->r) swap(data + top->l, data + top->r);
                }
                data[top->l] = target;
                top->status = 2;
                break;
            }
            case 2: {
                p->left = top->left;
                p->right = top->l - 1;
                push_stack(s, p);
                top->status = 3;
                break;
            }
            case 3: {
                p->left = top->l + 1;
                p->right = top->right;
                push_stack(s, p);
                top->status = 4;
                break;
            }
            case 4: {
                pop_stack(s);
            }
        }
    }
    free(p);
    clear_stack(s);
    return;
}

int main() {/*
    FILE *fin = fopen("input", "r");
    FILE *fout = fopen("result", "w");
    int n;
    fscanf(fin, "%d", &n);
    int *data = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < 100; i++) {
        fscanf(fin, "%d", data + i);
    }
    quick_sort(data, 0, n - 1);
    for(int i = 0; i < 100; i++) {
        fprintf(fout, "%d\n", data[i]);
    }
    return 0;*/
    int *data = (int *)malloc(sizeof(int) * 5);
    for(int i = 0; i < 5; i++) scanf("%d", data + i);
    quick_sort(data, 0, 4);
    for(int i = 0; i < 5; i++) printf("%d ", data[i]);
    return 0;
}
