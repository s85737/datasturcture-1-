//
//  main.c
//  stack_queue
//
//  Created by 최제현 on 2020/06/05.
//  Copyright © 2020 5468107최제현. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int element;

typedef struct queueNode{
    element data;
    struct queueNode* rLink;
    struct queueNode* lLink;
}queueNode;

//doubly linked list Queue 보조 구조체
typedef struct linkedQueueSub{
    struct queueNode* front;
    struct queueNode* rear;
}linkedQueueSub;

typedef struct queueArray{
    element *data;
    int front;
    int rear;
    int size;
}queueArray;

typedef struct stackNode{
    element data;
    struct stackNode* link;
} stackNode;

typedef struct stackArray{
    element *data;
    int top;
    int size;
}stackArray;



stackNode* createLinkedStack();
int linkedStackEmpty(stackNode* top);
element linkedPop(stackNode** top);
//element linkedPeek();
void linkedPush(stackNode** top, element inputData);
void printLinkedStack(stackNode** top);
stackArray* createArrayStack();
int arrayStackFull(stackArray* stack);
int arrayStackEmpty(stackArray* stack);
int arrayPop(stackArray* stack);
void arrayPush(stackArray* stack, element input);
void printArrayStack(stackArray* stack);
linkedQueueSub* createLinkedQueue(linkedQueueSub* queue);
int linkedQueueEmpty(linkedQueueSub* queue);
void linkedEnqueue(linkedQueueSub* queue, element data);
int linkedDequeue(linkedQueueSub* queue);
void printLinkedQueue(linkedQueueSub* queue);
queueArray* createArrayQueue(int size);
int arrayQueueEmpty(queueArray* queue);
int arrayQueueFull(queueArray* queue);
void arrayEnqueue(queueArray* queue, element data);
int arrayDequeue(queueArray* queue);
void printArrayQueue(queueArray* queue);


int main(int argc, const char * argv[]) {
    stackNode* linkedTop; //linked list stack 보조 구조체
    stackArray* arrayStack;
    linkedQueueSub* linkedQueue;
    queueArray* arrayQueue;
    int count;
    clock_t start, end, start2, end2;
    double duration;
    double value = 0;
    double result = 0;
    srand((unsigned int)time(NULL));
    
    printf("수행횟수 : ");
    scanf("%d", &count);
    linkedTop = createLinkedStack();
    arrayStack = createArrayStack();
    linkedQueue = createLinkedQueue(linkedQueue);
    arrayQueue = createArrayQueue(count);
    
    
    printf("\nLinked List Stack\n\n");
    printf("\nPush 수행:\n\n");
    start = clock();
    for(int i=0; i<count; i++){
        linkedPush(&linkedTop, i);
    }
    //    printLinkedStack(&linkedTop);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    //stack 은 FILO 이기 때문에 pop을 하게되면 가장 최근에 push 했던 값이 나오기 때문에 pop을 100번 반복.
    
    start = clock();
    for(int i=0; i<count; i++){
        result += linkedPop(&linkedTop);
    }
    printf("%d번 pop한 결과는 : %0.0lf\n", count, result);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    
    printf("\nDynamic Array Stack\n\n");
    printf("\nPush 수행:\n\n");
    start2 = clock();
    for(int i=0; i<count; i++){
        arrayPush(arrayStack, i);
    }
    //    printArrayStack(arrayStack);
    end2 = clock();
    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    //result 초기화
    result =0;
    
    start2 = clock();
    for(int i=0; i<count; i++){
        result += arrayPop(arrayStack);
    }
    printf("%d번 pop한 결과는 : %0.0lf\n", count, result);
    end2 = clock();
    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
//    
    
    printf("\nDoubly Linked List Queue\n\n");
    printf("\nEnqueue 수행:\n\n");
    start = clock();
    for(int i=0; i<count; i++){
        linkedEnqueue(linkedQueue, i);
    }
    //    printLinkedQueue(linkedQueue);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);

    result =0;

    //Queue는 FIFO 이기 때문에 dequeue을 하게되면 가장 처음에 enqueue 했던 값이 나오기 때문에 dequeue을 100번 반복.

    start2 = clock();
    for(int i=0; i<count; i++){
        result += linkedDequeue(linkedQueue);
    }
    printf("%d번 dequeue한 결과는 : %0.0lf\n", count, result);
    end2 = clock();
    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);

    printf("\nRound Array Queue\n\n");
    printf("\nEnqueue 수행:\n\n");
    start = clock();
    for(int i=0; i<count; i++){
        arrayEnqueue(arrayQueue, i);
    }
    //    printArrayQueue(arrayQueue);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);

    result =0;

    start2 = clock();
    for(int i=0; i<count; i++){
        result += arrayDequeue(arrayQueue);
    }
    printf("%d번 dequeue한 결과는 : %0.0lf\n", count, result);
    end2 = clock();
    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    
    
    
    
    return 0;
}


//linked list 함수

// linked list를 처음에 생성하는 함수

stackNode* createLinkedStack(){
    return NULL; //data가 없을때 top = NULL
}

//linked list stack이 비어있는지 확인하는 함수

int linkedStackEmpty(stackNode* top){
    if(top == NULL) return 1; //data가 없을때 top은 NULL 이므로
    else return 0;
}




/*
 linked list stack 에서 pop하는 함수
 @params 구조체 선언을 할 때 따로 보조구조체인 top을 선언하지 않고, main 함수에서 선언
 하였기 떄문에 -> top -> Node 를 역참조 하려면 이중포인터를 사용해야한다.
 */

element linkedPop(stackNode** top){
    element data;
    stackNode** temp; //pop 후 남은 Node를 삭제하기 위해 선언
    
    if(linkedStackEmpty(*top)){
        //스택이 비어있을때 오류 출력
        fprintf(stderr ,"\n\n stack empty error!\n");
        exit(-1);
    }
    
    temp = *top;
    data = (*top) -> data;
    //pop 하기전 head에 연결된 node가 top 이었으므로, 그 다음 Node를 top으로 변경
    *top = (*top) -> link;
    free(temp);
    
    return data;
}


//linked list stack에서 push 하는 함수

void linkedPush(stackNode** top, element data){
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
    if(!newNode){
        //메모리 할당이 제대로 되지 않았을 때 오류출력
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    newNode -> data = data;
    newNode -> link = *top; //새로 생성된 노드의 다음노드에 top 에 붙여줌
    *top = newNode; // 새로운 노드가 push 되었으므로 top 변경
    
    
}



//linked list의 모든 스택을 출력하는 함수

void printLinkedStack(stackNode** top){
    
    stackNode* stack = *top;
    if(linkedStackEmpty(*top)){
        fprintf(stderr ,"stack is empty!\n");
        return;
    }
    printf("\nLinked STACK [top- ");
    while(stack){
        printf("%d ", stack -> data);
        stack = stack->link;
    }
    printf("]\n");
    
}


//Array stack 함수

//array stack을 처음에 생성하는 함수

stackArray* createArrayStack(){
    
    stackArray* stack = malloc(sizeof(stackArray));
    
    if(!stack){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    stack -> size = 5; //초기 배열의 크기 5로 지정
    stack -> top = -1; //Data가 없을 때 top 은 -1
    stack -> data = malloc(stack -> size * sizeof(element));
    if (!stack->data){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    return stack;
    
}

//array stack이 꽉 차있는지 확인하는 함수

int arrayStackFull(stackArray* stack){
    
    //top은 0부터 시작하므로 최대크기일때 4, data배열의 최대크기는 1부터 카운트 되므로 보정
    return(stack -> top == (sizeof(stack->data)-1));
}

//array stack이 비어있는지 확인하는 함수

int arrayStackEmpty(stackArray* stack){
    if(stack -> top == -1) return 1;
    else return 0;
}

//array stack 을 pop하는 함수

int arrayPop(stackArray* stack){
    
    if(arrayStackEmpty(stack)){
        fprintf(stderr, "stack empty error!\n");
        exit(-1);
    }
    
        return stack->data[(stack->top)--]; //pop한 data를 return 해주고 top 1감소
    
}

//array stack을 Push하는 함수

void arrayPush(stackArray* stack, element data){
    
    if(arrayStackFull(stack)){
        stack -> size *= 2; //구조체 size 멤버 조정
        stack -> data = (element*)realloc(stack -> data, stack -> size * sizeof(element)); // size 만큼 메모리 재할당
    }
    stack -> data[++(stack->top)] = data; //push 되었으므로 top이 가리키는 index를 1 올리고, 입력된 data 저장
    
    
}

//array stack을 출력하는 함수

void printArrayStack(stackArray* stack){
    
    
    if(arrayStackEmpty(stack)){
        fprintf(stderr ,"stack is empty!\n");
        return;
    }
    
    printf("\nDynamic Array STACK [top- ");
    for(int i = stack->top; i>-1; i-- ){ // linked list와 편하게 비교하기 위해 역순출력
        printf("%d ", stack->data[i]);
    }
    
    printf("]\n");
    
}


// Linked queue 함수


// doubly linked list 를 생성하는 함수
linkedQueueSub* createLinkedQueue(linkedQueueSub* queue){
    
    queueNode* temp;
    queue = malloc(sizeof(linkedQueueSub)); //보조 구조체 메모리할당
    temp = malloc(sizeof(queueNode)); //보조 구조체와 연결된 노드 메모리 할당
    
    if(!queue || !temp){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    queue -> rear = NULL; //data가 비어있음을 보여주기위해 NULL로 저장
    queue -> front = NULL;
    
    return queue;
    
}


//doubly linked list Queue가 비었는지 확인하는 함수
int linkedQueueEmpty(linkedQueueSub* queue){
    // front가 NULL일때 queue가 비어있음
    if(queue -> front == NULL) return 1;
    else return 0;
    
}

//doubly linked list Queue에 새 노드를 추가하는 함수
void linkedEnqueue(linkedQueueSub* queue, element data){
    queueNode* newNode = malloc(sizeof(queueNode));
    
    if(!newNode){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    newNode -> data = data;
    newNode -> lLink = NULL; //newnode는 head쪽에 저장되기 때문에 왼쪽에 node가 없음
    if(queue -> rear != NULL){// 다른 data가 있을 때
        //queue 는 FIFO 이므로, 새로운 노드가 삽입되었을 때 rear(head)쪽에 삽입
        newNode -> rLink = queue -> rear; //오른쪽 링크에 기존 rear이 가리키던 노드 삽입
        queue -> rear -> lLink = newNode; //기존 노드에 newnode 주소 삽입
        queue -> rear = newNode; //rear에 newnode 주소 저장
        //다른 data가 없을 때
    }else if(queue -> rear == NULL && queue -> front == NULL){
        newNode -> rLink = NULL; //양쪽에 노드가 없으므로 양쪽 다 NULL 삽입
        queue -> front = newNode; //front와 rear 모두 newnode 의 주소삽입
        queue -> rear = newNode;
    }
    else{//예외처리 : free 되지않은 주소가 남아있을때 오류출력
        fprintf(stderr ,"enqueue error!\n");
        exit(-1);
    }
    
    
    
}

int linkedDequeue(linkedQueueSub* queue){
    
    queueNode* temp = queue -> front; //노드를 깔끔하게 삭제하기 위해 temp 선언
    
    int data = 0;
    if(linkedQueueEmpty(queue)){
        fprintf(stderr ,"queue empty error!\n");
        exit(-1);
    }
    
    if(queue -> front == queue -> rear){ //dequeue 후 data가 남아있지 않을 때
        data = queue -> front -> data; // front에 저장된 노드의 data 저장
        queue -> front = NULL; //front와 rear 초기화
        queue -> rear = NULL;
        free(temp); // temp 노드 삭제
    }
    else{ //
        data = queue -> front -> data;
        queue -> front = queue -> front -> lLink; // 기존 노드의 뒷순위 노드를 front 에 저장
        queue -> front -> rLink = NULL; // 맨 첫순위 노드이므로 오른쪽에 NULL저장
        //예외처리 : front가 NULL일때 rear도 NULL로 저장
        if (queue -> front == NULL){
            queue -> rear = NULL;
        }
        free(temp);
    }
    return data;
    
}

// doubly linked list 출력 함수
void printLinkedQueue(linkedQueueSub* queue){
    
    queueNode* node = queue -> rear;
    if(linkedQueueEmpty(queue)){
        fprintf(stderr ,"queue is empty!\n");
        return;
    }
    printf("\nLinked Queue [ rear");
    while(node){
        printf("%<-|%d|->", node -> data);
        node = node -> rLink;
    }
    
    printf("front ]\n");
    
}


// Array queue 함수


// round array queue 생성함수
queueArray* createArrayQueue(int size){
    queueArray* queue = malloc(sizeof(queueArray));
    if(!queue){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    queue -> size = size; //round array size에 매개변수 저장
    queue -> rear = -1; // 큐가 비었음을 나타내는 -1값 front와 rear에 저장
    queue -> front = -1;
    queue -> data = malloc(queue -> size * sizeof(element));
    if(!(queue -> data)){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    return queue;
    
}

//round array queue가 비어있는지 확인
int arrayQueueEmpty(queueArray* queue){
    // front와 rear 자리가 같으면 큐가 비어있다고 봤을 때는 예외상황이 생김.
    // front의 자리가 -1이면 비어있음.
    if(queue -> front == -1) return 1;
    else return 0;
}

//round array queue가 가득 차있는지 확인
int arrayQueueFull(queueArray* queue){
    // rear + 1 자리에 front 가 있는지 확인 있으면 큐가 가득차있음.
    if((queue -> rear+1) % queue -> size == queue -> front) return 1;
    else return 0;
}

//round array queue enqueue 함수
void arrayEnqueue(queueArray* queue, element data){
    
    if(arrayQueueFull(queue)){
        fprintf(stderr ,"ArrayQueue is Full!\n");
        exit(-1);
    }
    
    // 원형큐로 활용하기 위하여 rear가 size보다 크면 다시 0부터 삽입
    queue -> rear = (queue -> rear + 1) % queue -> size;
    queue -> data[queue->rear] = data;
    if(queue -> front == -1){
        //input data가 첫 data일 경우 front를 rear과 같게 해준다.
        queue -> front = queue -> rear;
        
    }
}


//round array queue dequeue 함수
int arrayDequeue(queueArray* queue){
    
    int data =0;
    
    if(arrayQueueEmpty(queue)){
        fprintf(stderr ,"ArrayQueue is empty!\n");
        exit(-1);
    }
    
    data = queue -> data[queue -> front];
    // queue 비어있음을 표시하기 위해 front 와 rear 를 -1로 초기화
    if (queue -> front == queue -> rear){
        queue -> front = -1;
        queue -> rear = -1;
    }else{
        //원형큐로 활영하기 위하여 front가 size보다 크면 다시 0부터 삽입
        queue -> front = (queue -> front +1) % queue -> size;
    }
    return data;
    
}

void printArrayQueue(queueArray* queue){
    
    if(arrayQueueEmpty(queue)){
        fprintf(stderr ,"queue is empty!\n");
        return;
    }
    printf("\nRound Array STACK [rear-");
    
    
    int i = (queue -> rear) % queue -> size;
    
    do{
        //예외처리 : data가 1개만 있을때는 front와 rear가 같으므로 조건문에서 걸러져 출력되지 못한다.
        if (i == queue ->front){
            printf(" %d",queue -> data[i]);
            break;
        }
        printf(" %d", queue->data[i]);
        i--;
        //예외처리 : 역순으로 출력하는 중 i가 0이하가 되는것을 방지
        if(i < 0) i = queue -> size-1;
    }while(i != queue -> rear);
    
    printf(" -front]\n");
    
}

