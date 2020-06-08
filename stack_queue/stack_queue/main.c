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
    stackNode* linkedTop;
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
    start2 = clock();
    for(int i=0; i<count; i++){
        arrayPush(arrayStack, i);
    }
//    printArrayStack(arrayStack);
    end2 = clock();
    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    result =0;
    
    start2 = clock();
    for(int i=0; i<count; i++){
        result += arrayPop(arrayStack);
    }
    printf("%d번 pop한 결과는 : %0.0lf\n", count, result);
    end2 = clock();
    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
    
    
//     printf("\nDoubly Linked List Queue\n\n");
//    start = clock();
//    for(int i=0; i<count; i++){
//        linkedEnqueue(linkedQueue, i);
//    }
////    printLinkedQueue(linkedQueue);
//    end = clock();
//    duration = (double)(end - start) / CLOCKS_PER_SEC;
//    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
//
//    result =0;
//
//    start2 = clock();
//    for(int i=0; i<count; i++){
//        result += linkedDequeue(linkedQueue);
//    }
//    printf("%d번 dequeue한 결과는 : %0.0lf\n", count, result);
//    end2 = clock();
//    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
//    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
//
//     printf("\nRound Array Queue\n\n");
//    start = clock();
//    for(int i=0; i<count; i++){
//        arrayEnqueue(arrayQueue, i);
//    }
////    printArrayQueue(arrayQueue);
//    end = clock();
//    duration = (double)(end - start) / CLOCKS_PER_SEC;
//    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
//
//    result =0;
//
//    start2 = clock();
//    for(int i=0; i<count; i++){
//        result += arrayDequeue(arrayQueue);
//    }
//    printf("%d번 dequeue한 결과는 : %0.0lf\n", count, result);
//    end2 = clock();
//    duration = (double)(end2 - start2) / CLOCKS_PER_SEC;
//    printf("\n수행시간은 %lf초 입니다.\n\n", duration);
//
//
    
    
    
    return 0;
}


//linked list 함수

// linked list를 처음에 생성하는 함수

stackNode* createLinkedStack(){
    return NULL;
}

//linked list stack이 비어있는지 확인하는 함수

int linkedStackEmpty(stackNode* top){
    if(top == NULL) return 1;
    else return 0;
}


//linked list stack 에서 pop하는 함수

element linkedPop(stackNode** top){
    element outputData;
    stackNode** temp;
    
    if(linkedStackEmpty(*top)){
        fprintf(stderr ,"\n\n stack empty error!\n");
        exit(-1);
    }
    
    temp = *top;
    outputData = (*top) -> data;
    *top = (*top) -> link;
    free(temp);
    
    return outputData;
}

////linked list stack 에서 Peek하는 함수
//
//element linkedPeek(stackNode** top){
//    element output;
//
//    if(LinkedstackEmpty(*top)){
//        printf("\n\n stack is empty\n");
//        exit(1);
//    }else{
//        return((*top) -> data);
//    }
//
//    return output;
//}

//linked list stack에서 push 하는 함수

void linkedPush(stackNode** top, element inputData){
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
    if(!temp){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    temp -> data = inputData;
    temp -> link = *top;
    *top = temp;
    
    
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
    
    stack -> size = 5;
    stack -> top = -1;
    stack -> data = malloc(stack -> size * sizeof(element));
    if (!stack->data){
        return NULL;
    }
    
    return stack;
    
}

//array stack이 꽉 차있는지 확인하는 함수

int arrayStackFull(stackArray* stack){
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
    }else{
        return stack->data[(stack->top)--];
    }
    
}

//array stack을 Push하는 함수

void arrayPush(stackArray* stack, element input){
    
    if(arrayStackFull(stack)){
        stack -> size *= 2;
        stack -> data = (element*)realloc(stack -> data, stack -> size * sizeof(element)); // size 만큼 메모리 재할당
    }
    stack -> data[++(stack->top)] = input;
    
    
}


void printArrayStack(stackArray* stack){
    
    
    if(arrayStackEmpty(stack)){
        fprintf(stderr ,"stack is empty!\n");
        return;
    }
    
    printf("\nDynamic Array STACK [top- ");
    for(int i = stack->top; i>-1; i-- ){
        printf("%d ", stack->data[i]);
    }
    
    printf("]\n");
    
}


// Linked queue 함수



linkedQueueSub* createLinkedQueue(linkedQueueSub* queue){
    
    queueNode* temp;
    queue = malloc(sizeof(linkedQueueSub));
    temp = malloc(sizeof(queueNode));
    
    if(!queue || !temp){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    queue -> rear = NULL;
    queue -> front = NULL;
    
    return queue;
    
}


int linkedQueueEmpty(linkedQueueSub* queue){
    if(queue -> front == NULL) return 1;
    else return 0;
    
}

void linkedEnqueue(linkedQueueSub* queue, element data){
    queueNode* newNode = malloc(sizeof(queueNode));
    
    if(!newNode){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    newNode -> data = data;
    newNode -> lLink = NULL;
    if(queue -> rear != NULL){
        newNode -> rLink = queue -> rear;
        queue -> rear -> lLink = newNode;
        queue -> rear = newNode;
    }else if(queue -> rear == NULL && queue -> front == NULL){
        newNode -> rLink = NULL;
        queue -> front = newNode;
        queue -> rear = newNode;
    }
    else{
        fprintf(stderr ,"enqueue error!\n");
        exit(-1);
    }
    
    
    
}

int linkedDequeue(linkedQueueSub* queue){
    
    queueNode* temp = queue -> front;
    int data = 0;
    if(linkedQueueEmpty(queue)){
        fprintf(stderr ,"queue empty error!\n");
        exit(-1);
    }
    
    if(queue -> front == queue -> rear){
        data = queue -> front -> data;
        queue -> front = NULL;
        queue -> rear = NULL;
        free(temp);
    }
    else{
        data = queue -> front -> data;
        queue -> front = queue -> front -> lLink;
        queue -> front -> rLink = NULL;
        if (queue -> front == NULL){
            queue -> rear = NULL;
        }
        free(temp);
    }
    return data;
    
}


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



queueArray* createArrayQueue(int size){
    queueArray* queue = malloc(sizeof(queueArray));
    if(!queue){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    queue -> size = size;
    queue -> rear = -1;
    queue -> front = -1;
    queue -> data = malloc(queue -> size * sizeof(element));
    if(!(queue -> data)){
        fprintf(stderr,"\n malloc error! \n");
        exit(-1);
    }
    
    return queue;
    
}

int arrayQueueEmpty(queueArray* queue){
    // front와 rear 자리가 같으면 큐가 비어있음 X
    // front의 자리가 -1이면 비어있음.
    if(queue -> front == -1) return 1;
    else return 0;
}


int arrayQueueFull(queueArray* queue){
    // rear + 1 자리에 front 가 있는지 확인 있으면 큐가 가득차있음.
    if((queue -> rear+1) % queue -> size == queue -> front) return 1;
    else return 0;
}

//enqueue 함수
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


/**
 if else 문 check
 */


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

