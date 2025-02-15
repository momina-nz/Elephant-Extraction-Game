#include <stdio.h>
#include <stdlib.h>

// Define a Node struct to represent a position in the grid
struct Node
{
    int r, c;           // Row and column indices
    struct Node *next;  // Pointer to the next Node in the linked list
};

// Define a Stack struct to implement a stack using linked list
struct Stack
{
    struct Node *head;  // Pointer to the top of the stack
};

// Define a struct for the Elephant containing its memory stack
struct Elephant
{
    struct Stack memory;  // Stack to remember visited positions
};

// Function to create a new Node with given row and column indices
struct Node *createNode(int row, int col)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->r = row;
    newNode->c = col;
    newNode->next = NULL;
    return newNode;
}

// Function to push a new Node onto the stack
void push(struct Stack *stk, int row, int col)
{
    struct Node *newNode = createNode(row, col);
    newNode->next = stk->head;
    stk->head = newNode;
}

// Function to pop the top Node from the stack
void pop(struct Stack *stk)
{
    if (stk->head != NULL)
    {
        struct Node *temp = stk->head;
        stk->head = stk->head->next;
        free(temp);
    }
}

// Function to get the row and column indices of the top Node in the stack
void top(struct Stack *stk, int *row_ptr, int *col_ptr)
{
    if (stk->head != NULL)
    {
        *row_ptr = stk->head->r;
        *col_ptr = stk->head->c;
    }
}

// Function to add bait at a specified position in the grid
void addBait(int **grid, int row, int col, int amt)
{
    grid[row][col] += amt;
}

// Function to eat bait at a specified position in the grid and return the consumed amount
int eatBait(int **grid, int row, int col)
{
    // Eat melons at the selected position
    return grid[row][col]; // Return consumed melons
}

// Function to move the elephant to the adjacent intersection with the most watermelons
void move(struct Elephant *ele_ptr, int **grid)
{
    int row, col, hasMoved = 0;
    top(&ele_ptr->memory, &row, &col);

    // Move to the adjacent intersection with the most watermelons
    int maxMelons = grid[row][col];
    int nextRow = row, nextCol = col;

    if (grid[row][col] == 0)
    {
        if (row > 1 && grid[row - 1][col] > maxMelons) //Check lower intersection
        {
            maxMelons = grid[row - 1][col];
            nextRow = row - 1, hasMoved = 1;
            push(&ele_ptr->memory, nextRow, nextCol);
        }

        if (row < 500 && grid[row + 1][col] > maxMelons) //Check upper intersection
        {
            maxMelons = grid[row + 1][col];
            nextRow = row + 1, hasMoved = 1;
            push(&ele_ptr->memory, nextRow, nextCol);
        }

        if (col > 1 && grid[row][col - 1] > maxMelons) //Check left intersection
        {
            maxMelons = grid[row][col - 1];
            nextCol = col - 1, hasMoved = 1;
            push(&ele_ptr->memory, nextRow, nextCol);
        }

        if (col < 500 && grid[row][col + 1] > maxMelons) //Check right intersection
        {
            maxMelons = grid[row][col + 1];
            nextCol = col + 1, hasMoved = 1;
            push(&ele_ptr->memory, nextRow, nextCol);
        }

        // If no bait was consumed and the elephant has moved before, update its position
        if (ele_ptr->memory.head->next != NULL && hasMoved == 0)
        {
            pop(&ele_ptr->memory);             // Remove current position
            top(&ele_ptr->memory, &row, &col); // Get previous position
        }
    }
}

// Function to let the elephant eat bait at its current position
int eat(struct Elephant *ele_ptr, int **grid)
{
    int row, col;
    top(&ele_ptr->memory, &row, &col);
    int consumed = eatBait(grid, row, col);

    // If bait was consumed, update grid
    if (consumed > 0)
    {
        grid[row][col] = 0;
    }
    return consumed;
}

// Function to make progress for all elephants in one hour
int progress_hour(struct Elephant *ele_arr, int num_ele, int **grid)
{
    // First, move all elephants
    for (int i = 0; i < num_ele; i++)
    {
        move(&ele_arr[i], grid);
    }

    // Then, let all elephants eat
    int totalConsumed = 0;
    for (int i = 0; i < num_ele; i++)
    {
        int consumed = eat(&ele_arr[i], grid);
        totalConsumed += consumed;
    }

    return totalConsumed;
}

int main()
{
    int N;
    while (scanf("%d", &N) != EOF) // Loop until end of input
    {
        // Allocate memory for the array of elephants and the grid
        struct Elephant *elephants = (struct Elephant *)malloc(N * sizeof(struct Elephant));
        int **grid = (int **)malloc(501 * sizeof(int *));

        // Allocate memory for each row of the grid
        for (int i = 0; i <= 500; i++)
        {
            grid[i] = (int *)calloc(501, sizeof(int));
        }

        // Initialize elephants' starting positions and memory stacks
        for (int i = 0; i < N; i++)
        {
            int row, col;
            scanf("%d %d", &row, &col);
            elephants[i].memory.head = NULL; // Initialize the stack's head to NULL
            push(&elephants[i].memory, row, col);
        }

        char command[5];
        // Process commands until QUIT command is encountered
        while (scanf("%s", command) != EOF)
        {
            if (command[0] == 'B')
            {
                int row, col, amt;
                scanf("%d %d %d", &row, &col, &amt);
                addBait(grid, row, col, amt);
            }
            else if (command[0] == 'H')
            {
                // Progress one hour and print total consumed bait
                int consumed = progress_hour(elephants, N, grid);
                printf("%d\n", consumed);
            }
            else
            {
                break; // QUIT command
            }
        }

        // Print final positions of all elephants
        for (int i = 0; i < N; i++)
        {
            int row, col;
            top(&elephants[i].memory, &row, &col);
            printf("%d %d\n", row, col);
        }

        // Free allocated memory
        for (int i = 0; i <= 500; i++)
        {
            free(grid[i]);
        }
        free(grid);
        free(elephants);
    }

    return 0;
}