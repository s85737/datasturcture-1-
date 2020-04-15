#include <stdio.h>
#include <stdlib.h>
 
typedef int element;
 
typedef struct ListNode {
    element data;
    struct ListNode* link;
    
} ListNode;
 
ListNode *insert_first(ListNode* head, int value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    printf("\nnew node의 주소 : %p\n", p);
    
    p->data = value;
    p->link = head;
    head = p;
    
    printf("head의 주소 %p\n", head);
    printf("head의 데이터 %d\n", head->data);
    printf("head의 링크값 %p\n", head->link);
    
    return head;
    
}
//insert_last 구현 제일끝에 어떤 값을 ,노드를 입력하고 마치는 함수 제출
 
ListNode *insert_last(ListNode* head, int value){
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    ListNode* temp = head; //임시 값에 head 저장
    printf("\nnew node의 주소 : %p\n", p);
    
 
        p->data = value;
        p->link = NULL; //해당 list의 마지막값 이므로 link에는 NULL 저장
 
        // 마지막 노드 탐색
        while(temp->link != NULL)
        temp = temp->link ;
 
        temp->link = p; // 마지막 노드의 link에 새 노드 주소 저장
 
    
    printf("new node의 데이터 : %d\n", p->data);
    
    return head;
}
 
 
ListNode *insert(ListNode* head, ListNode* pre, element value)
{
    printf("pre의 데이터 : %d\n", pre->data);
    printf("pre의 링크값 : %p\n", pre->link);
    
    ListNode *p = (ListNode*)malloc(sizeof(ListNode));
    printf("\nnew node의 주소 : %p\n", p);
    
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    
    printf("new node의 데이터 : %d\n", p->data);
    printf("new node의 링크값 : %p\n", p->link);
    
    return head;
    
}
 
 
void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}
 
int main(int argc, const char * argv[]) {
    ListNode* head = NULL; // 링크드 리스트 생성
    
    for(int i = 0; i < 3; i++)
    {
        head = insert_first(head, i);
        print_list(head);
    }
    
    ListNode* pre = head;
    head = insert(head, pre, 50);
    print_list(head);
    
    head = insert_last(head, 22);
    print_list(head);
    
    return 0;
}
