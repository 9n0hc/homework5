/* Circular Queue�� �����ϰ� ����ϴ� C ���α׷�. */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

/* QueueType�̶�� ����ü ����. 
ť�� ��Ҹ� �����ϴ� �迭�� queue�� front, rear �� ���� �ε��� ����.
front�� ���� ť�� ù ��° ��Ұ� �ִ� ��ġ, rear�� ���� ť�� ������ ��Ұ� �ִ� ��ġ ��Ÿ��. */
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

/* ����ڷκ��� �Է��� �޾� �� �Լ� ȣ��.
���α׷��� ����� �� QueueType ����ü ����. */
int main(void)
{
    printf("[----- [������] [2022041043] -----]");
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

/* QueueType ����ü�� ���� �Ҵ��ϰ� �ʱ�ȭ�Ͽ� ��ȯ. */
QueueType *createQueue()
{
    QueueType *cQ;
    cQ = (QueueType *)malloc(sizeof(QueueType));
    cQ->front = 0;
    cQ->rear = 0;
    return cQ;
}

/* QueueType ����ü�� ���� �Ҵ� ����. */
int freeQueue(QueueType *cQ)
{
    if (cQ == NULL) return 1;
    free(cQ);
    return 1;
}

/* ����ڷκ��� �ϳ��� ��Ҹ� �Է� �޾� ��ȯ. */
element getElement()
{
    element item;
    printf("Input element = ");
    scanf(" %c", &item);
    return item;
}

/* ť�� ����ִ��� Ȯ���ϰ�, ����ִٸ� �޽����� ����ϰ� 1�� ��ȯ. */
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

/* ť�� ���� á���� Ȯ���ϰ�, ���� á�ٸ� �޽����� ����ϰ� 1�� ��ȯ. */
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

/* ť�� ���ο� ��Ҹ� �߰�.
ť�� ���� ���ִ� ��� ���� �޽��� ���. */
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

/* ť���� ��Ҹ� �����ϰ�, ������ ����� ���� item �����Ϳ� ����.
ť�� ����ִ� ��� ���� �޽��� ���. */
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

/* ť�� ���� ���.
ť�� ����ִ� ��� �ƹ��͵� ������� ����. */
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

/* ť�� ���� ������ ���.
���������ε� ���. */
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