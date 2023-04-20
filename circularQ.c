/* Circular Queue를 구현하고 사용하는 C 프로그램. */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

/* QueueType이라는 구조체 정의. 
큐의 요소를 저장하는 배열인 queue와 front, rear 두 개의 인덱스 가짐.
front는 현재 큐의 첫 번째 요소가 있는 위치, rear는 현재 큐의 마지막 요소가 있는 위치 나타냄. */
typedef char element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType; 

QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void dequeue(QueueType *cQ, element *item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

/* 사용자로부터 입력을 받아 각 함수 호출.
프로그램이 종료될 때 QueueType 구조체 해제. */
int main(void)
{
    printf("[----- [이은총] [2022041043] -----]");
    QueueType *cQ = createQueue();
    element data;

    char command;

    do {
        printf("\n-----------------------------------------------------\n");
        printf("                     Circular Q                   \n");
        printf("------------------------------------------------------\n");
        printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
        printf("------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'i':
        case 'I':
            data = getElement();
            enQueue(cQ, data);
            break;
        case 'd':
        case 'D':
            dequeue(cQ, &data);
            printf("deleted item = %c\n", data);
            break;
        case 'p':
        case 'P':
            printQ(cQ);
            break;
        case 'b':
        case 'B':
            debugQ(cQ);
            break;
        case 'q':
        case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    freeQueue(cQ);

    return 0;
}

/* QueueType 구조체를 동적 할당하고 초기화하여 반환. */
QueueType *createQueue()
{
    QueueType *cQ;
    cQ = (QueueType *)malloc(sizeof(QueueType));
    cQ->front = 0;
    cQ->rear = 0;
    return cQ;
}

/* QueueType 구조체를 동적 할당 해제. */
int freeQueue(QueueType *cQ)
{
    if (cQ == NULL) return 1;
    free(cQ);
    return 1;
}

/* 사용자로부터 하나의 요소를 입력 받아 반환. */
element getElement()
{
    element item;
    printf("Input element = ");
    scanf(" %c", &item);
    return item;
}

/* 큐가 비어있는지 확인하고, 비어있다면 메시지를 출력하고 1을 반환. */
int isEmpty(QueueType *cQ)
{
    if (cQ->front == cQ->rear) {
        printf("Circular Queue is empty!");
        return 1;
    }
    else {
        return 0;
    }
}

/* 큐가 가득 찼는지 확인하고, 가득 찼다면 메시지를 출력하고 1을 반환. */
int isFull(QueueType *cQ)
{
    if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front) {
        printf("Circular Queue is full!");
        return 1;
    }
    else {
        return 0;
    }
}

/* 큐에 새로운 요소를 추가.
큐가 가득 차있는 경우 에러 메시지 출력. */
void enQueue(QueueType *cQ, element item)
{
    if (isFull(cQ)) {
        printf(" Circular Queue is full!");
        return;
    }
    else {
        cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
        cQ->queue[cQ->rear]=item;
    }
}

/* 큐에서 요소를 제거하고, 삭제된 요소의 값을 item 포인터에 저장.
큐가 비어있는 경우 에러 메시지 출력. */
void dequeue(QueueType *cQ, element *item)
{
    if (isEmpty(cQ)) {
        printf("Circular Queue is empty!");
        return;
    }
    else {
        cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
        *item = cQ->queue[cQ->front];
    }
}

/* 큐의 내용 출력.
큐가 비어있는 경우 아무것도 출력하지 않음. */
void printQ(QueueType *cQ)
{
    int i, first, last;

    if (isEmpty(cQ)) {
        return;
    }
    else {
        first = (cQ->front + 1) % MAX_QUEUE_SIZE;
        last = (cQ->rear + 1) % MAX_QUEUE_SIZE;
        printf("Circular Queue : [");

        i = first;
        while (i != last) {
            printf("%3c", cQ->queue[i]);
            i = (i + 1) % MAX_QUEUE_SIZE;
        }
        printf(" ]\n");
    }
}

/* 큐의 내부 정보를 출력.
디버깅용으로도 사용. */
void debugQ(QueueType *cQ)
{
    printf("\n---DEBUG\n");
    for (int i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        if (i == cQ->front) {
            printf("  [%d] = front\n", i);
            continue;
        }
        printf("  [%d] = %c\n", i, cQ->queue[i]);

        if (i == cQ->rear) {
            printf("  [%d] = rear\n", i);
            break;
        }
    }
    printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}