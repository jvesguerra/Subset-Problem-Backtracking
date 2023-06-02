#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define N 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// Function to create an empty stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

// Function to push an element onto the stack
void push(Stack* stack, int element) {
    stack->top++;
    stack->data[stack->top] = element;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    int element = stack->data[stack->top];
    stack->top--;
    return element;
}

// Function to get the top element of the stack
int top(Stack* stack) {
    return stack->data[stack->top];
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to print a partition
void printPartition(int set[], int subset1[], int size1, int subset2[], int size2) {
    printf("{ ");
    for (int i = 0; i < size1; i++) {
        printf("%d ", set[subset1[i]]);
    }
    printf("} { ");
    for (int i = 0; i < size2; i++) {
        printf("%d ", set[subset2[i]]);
    }
    printf("}\n");
}

// Function to check if a partition is valid (i.e., sums of subsets are equal)
bool isPartitionValid(int set[], int subset1[], int size1, int subset2[], int size2) {
    int sum1 = 0;
    int sum2 = 0;

    // Calculate the sum of elements in subset1
    for (int i = 0; i < size1; i++) {
        sum1 += set[subset1[i]];
    }

    // Calculate the sum of elements in subset2
    for (int i = 0; i < size2; i++) {
        sum2 += set[subset2[i]];
    }

    // Check if the sums are equal
    return sum1 == sum2;
}

// Utility function for finding partitions recursively
void findPartitionsUtil(int set[], int n, int index, int start, int move, int nopts[], Stack* option[][N+2]) {
    // Base case: reached the end of the set
    if (index == n) {
        // Check if both subsets are non-empty and have equal sums
        if (isEmpty(option[start][0]) || isEmpty(option[start][1]))
            return;
        if (isPartitionValid(set, option[start][0]->data, option[start][0]->top + 1, option[start][1]->data, option[start][1]->top + 1)) {
            // Print the valid partition
            printPartition(set, option[start][0]->data, option[start][0]->top + 1, option[start][1]->data, option[start][1]->top + 1);
        }
        return;
    }

    // Determine the current top of stack
    int topStack = nopts[move];

    // Include the current element in subset1 and recursively find partitions
    push(option[start][0], index);
    nopts[move + 1] = topStack + 1;
    findPartitionsUtil(set, n, index + 1, start, move + 1, nopts, option);
    pop(option[start][0]);

    // Include the current element in subset2 and recursively find partitions
    push(option[start][1], index);
    nopts[move + 1] = topStack + 2;
    findPartitionsUtil(set, n, index + 1, start, move + 1, nopts, option);
    pop(option[start][1]);

    // Reset the top of stack after recursive calls
    nopts[move] = topStack;
}

int main() {
    int set[] = {3, 7, 1, 2, 4, 5, 8};
    int size = sizeof(set) / sizeof(set[0]);

    printf("Partitionings (%d solutions):\n", size);

    int start, move;
    int nopts[N+2]; // array of top of stacks
    Stack* option[N+2][N+2]; // array of stacks of options

    // Initialize the first elements of the option array
    option[0][0] = createStack();
    option[0][1] = createStack();

    move = start = 0;
    nopts[start] = 1;

    // Utility function for finding partitions recursively
    findPartitionsUtil(set, size, 0, start, move, nopts, option);

    // Free the memory allocated for the stacks
    for (int i = 0; i < size; i++) {
        free(option[i][0]);
        free(option[i][1]);
    }

    return 0;
}
