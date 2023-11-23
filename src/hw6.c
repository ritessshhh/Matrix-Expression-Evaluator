#include "hw6.h"

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[])
{
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows * num_cols * sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat)
{
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows * mat->num_cols; i++)
    {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows * mat->num_cols - 1)
            printf(" ");
    }
    printf("\n");
}

/**
 * @brief Inserts a bst node in the root
 *
 * @param mat Matrix to integrate in the node
 * @param root To find the position to insert
 * @return bst_sf* New free root
 */
bst_sf *insert_bst_sf(matrix_sf *mat, bst_sf *root)
{
    if (root == NULL)
    {
        bst_sf *newRoot = (bst_sf *)malloc(sizeof(bst_sf));
        if (newRoot == NULL)
        {
            return NULL;
        }
        newRoot->mat = mat;
        newRoot->left_child = NULL;
        newRoot->right_child = NULL;
        return newRoot;
    }

    if (mat->name < root->mat->name)
    {
        root->left_child = insert_bst_sf(mat, root->left_child);
    }
    else if (mat->name > root->mat->name)
    {
        root->right_child = insert_bst_sf(mat, root->right_child);
    }
    return root;
}

/**
 * @brief Finds a specified node
 *
 * @param name Name of the node
 * @param root Root to find in
 * @return matrix_sf* Returns specified node
 */
matrix_sf *find_bst_sf(char name, bst_sf *root)
{
    if (root == NULL || root->mat->name == name)
    {
        return (root == NULL) ? NULL : root->mat;
    }

    if (name < root->mat->name)
        return find_bst_sf(name, root->left_child);
    else if (name > root->mat->name)
        return find_bst_sf(name, root->right_child);
}

/**
 * @brief Frees all the nodes in the tree
 *
 * @param root Root to start freeing
 */
void free_bst_sf(bst_sf *root)
{
    if (root == NULL)
    {
        return;
    }

    // Recursively free left and right children
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    // Next, free the 'matrix_sf' structure itself
    free(root->mat);

    // Finally, free the BST node
    free(root);
}

/**
 * @brief Adds two matrix
 *
 * @param mat1 Matrix one
 * @param mat2 Matrix two
 * @return matrix_sf* new matrix after adding
 */
matrix_sf *add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    if (mat1->num_rows == mat2->num_rows && mat1->num_cols == mat2->num_cols)
    {

        int rows = mat1->num_rows;
        int cols = mat1->num_cols;

        matrix_sf *m = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
        m->num_rows = rows;
        m->num_cols = cols;

        for (int i = 0; i < rows * cols; i++)
        {
            m->values[i] = mat1->values[i] + mat2->values[i];
        }

        return m;
    }
    else
        return NULL;
}

/**
 * @brief Multiplies two matrix
 *
 * @param mat1 Matrix one
 * @param mat2 Matrix two
 * @return matrix_sf* new matrix after multiplying
 */
matrix_sf *mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    if (mat1->num_cols == mat2->num_rows)
    {

        int rows = mat1->num_rows;
        int cols = mat2->num_cols;

        matrix_sf *m = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
        m->num_rows = rows;
        m->num_cols = cols;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                m->values[i * cols + j] = 0;

                for (int k = 0; k < mat1->num_cols; k++)
                {
                    m->values[i * m->num_cols + j] += mat1->values[i * mat1->num_cols + k] * mat2->values[k * mat2->num_cols + j];
                }
            }
        }

        return m;
    }
    else
        return NULL;
}

/**
 * @brief Returns a trnspose matrix
 *
 * @param mat Matrix to transpose
 * @return matrix_sf* Transposed matrix
 */
matrix_sf *transpose_mat_sf(const matrix_sf *mat)
{
    int rows = mat->num_rows;
    int cols = mat->num_cols;

    matrix_sf *m = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    m->num_rows = cols;
    m->num_cols = rows;

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            m->values[i * rows + j] = mat->values[j * cols + i];
        }
    }

    return m;
}

/**
 * @brief Create a matrix sf object
 *
 * @param name Name of the new matrix
 * @param expr Expression to make the new matrix with
 * @return matrix_sf* New matrix
 */
matrix_sf *create_matrix_sf(char name, const char *expr)
{
    int rows, cols;
    sscanf(expr, "%u %u", &rows, &cols);

    matrix_sf *mat = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    if (!mat)
    {
        // Handle memory allocation failure
        return NULL;
    }

    mat->name = name;
    mat->num_rows = rows;
    mat->num_cols = cols;

    const char *current = strchr(expr, '[') + 1;
    char *token;
    char buffer[strlen(current) + 1];
    strcpy(buffer, current);

    int counter = 0;
    token = strtok(buffer, " ;]");
    while (token != NULL && counter < rows * cols)
    {
        mat->values[counter++] = atoi(token);
        token = strtok(NULL, " ;]");
    }

    return mat;
}

// InfixToPostfix methods....
/**
 * @brief Stack structure
 *
 */
struct stack
{
    char *operators;
    int count;
};

/**
 * @brief Push elements in stack
 *
 * @param Stack Stack to push in
 * @param c Element to push in
 */
void push(struct stack *Stack, char c)
{
    Stack->operators[Stack->count] = c;
    Stack->count++;
}

/**
 * @brief Pop element from the stack
 *
 * @param Stack Stack to pop
 * @return char Element popped
 */
char pop(struct stack *Stack)
{
    if (Stack->count > 0)
    {
        char temp = Stack->operators[Stack->count - 1];
        Stack->count--;
        return temp;
    }
    return '\0'; // Return a sentinel value when the stack is empty
}

/**
 * @brief Peek at the top element
 *
 * @param Stack Stack to peek
 * @return char peeked element
 */
char peek(struct stack *Stack)
{
    if (Stack->count > 0)
    {
        return Stack->operators[Stack->count - 1];
    }
    return '\0'; // Return a sentinel value when the stack is empty
}

/**
 * @brief Check operator
 *
 * @param c Operator
 * @return int Returns 1 if found else 0
 */
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '\'') ? 1 : 0;
}

/**
 * @brief Check precedence of the operator
 *
 * @param c To check precedence
 * @return int Returns precedence level
 */
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '\'')
        return 3;
    else
        return 0;
}

/**
 * @brief Convert infix expression to postfix
 *
 * @param infix infix expression
 * @return char* Returns postfix expression
 */
char *infix2postfix_sf(char *infix)
{
    char *postfix = malloc(sizeof(char) * (strlen(infix) + 1));
    struct stack *Stack = malloc(sizeof(struct stack));
    Stack->operators = malloc(sizeof(char) * strlen(infix));
    Stack->count = 0;
    int i, j;

    for (i = 0, j = 0; i < strlen(infix); i++)
    {
        if (isalnum(infix[i]))
        {
            postfix[j] = infix[i];
            j++;
        }
        else if (infix[i] == '(')
        {
            push(Stack, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (peek(Stack) != '(')
            {
                postfix[j++] = pop(Stack);
            }
            pop(Stack); // Pop the '('
        }
        else if (isOperator(infix[i]))
        {
            while (Stack->count > 0 &&
                   precedence(peek(Stack)) >= precedence(infix[i]))
            {
                postfix[j++] = pop(Stack);
            }
            push(Stack, infix[i]);
        }
    }

    while (Stack->count > 0)
    {
        if (peek(Stack) == '(')
        {
            return "Invalid Expression";
        }
        postfix[j++] = pop(Stack);
    }
    postfix[j] = '\0';

    free(Stack->operators);
    free(Stack);

    return postfix;
}

/**
 * @brief Stack with different elements
 *
 */
struct stack2
{
    matrix_sf *operators[100];
    int count;
};

/**
 * @brief Pushes elements in stack
 *
 * @param Stack Stack to push in
 * @param c Element to push
 */
void push2(struct stack2 *Stack, matrix_sf *c)
{
    if (Stack->count >= 100)
        return;
    else
    {
        Stack->operators[Stack->count] = c;
        Stack->count++;
    }
}

/**
 * @brief Pops the top element in stack
 *
 * @param Stack Stack to pop
 * @return matrix_sf* Return popped element
 */
matrix_sf *pop2(struct stack2 *Stack)
{
    if (Stack->count > 0)
    {
        matrix_sf *temp = Stack->operators[Stack->count - 1];
        Stack->operators[Stack->count - 1] = NULL;
        Stack->count--;
        return temp;
    }
    return NULL; // Return a sentinel value when the stack is empty
}

/**
 * @brief Evaluates the expressions
 *
 * @param name name of the new matrix
 * @param expr expression to evaluate
 * @param root root to find new elements
 * @return matrix_sf*
 */
matrix_sf *evaluate_expr_sf(char name, char *expr, bst_sf *root)
{
    char *postfix = infix2postfix_sf(expr);

    struct stack2 *Stack = malloc(sizeof(struct stack2));
    if (!Stack)
        return NULL; // Check for malloc failure
    Stack->count = 0;

    for (int i = 0; postfix[i] != '\0'; i++) // Changed to postfix[i] != '\0'
    {
        if (isalpha(postfix[i]))
            push2(Stack, find_bst_sf(postfix[i], root));

        else
        {
            // Ensure operations on Stack are safe
            if (Stack->count < 2 && (postfix[i] == '+' || postfix[i] == '*'))
            {
                // Handle error: not enough operands
                while (Stack->count > 0)
                {
                    matrix_sf *temp = pop2(Stack);
                    if (temp && !isalpha(temp->name))
                        free(temp);
                }
                free(Stack);
                free(postfix);
                return NULL; // Indicate failure
            }

            matrix_sf *mat1 = NULL, *mat2 = NULL;
            if (postfix[i] == '\'')
            {
                mat1 = pop2(Stack);
                push2(Stack, transpose_mat_sf(mat1));
            }
            else
            {
                mat2 = pop2(Stack);
                mat1 = pop2(Stack);
                if (postfix[i] == '+')
                    push2(Stack, add_mats_sf(mat1, mat2));
                else if (postfix[i] == '*')
                    push2(Stack, mult_mats_sf(mat1, mat2));
            }

            // Free temporary matrices if needed
            if (mat1 && !isalpha(mat1->name))
                free(mat1);
            if (mat2 && !isalpha(mat2->name))
                free(mat2);
        }
    }

    matrix_sf *newMatrix = pop2(Stack);
    newMatrix->name = name;
    free(Stack);
    free(postfix); // Free the postfix string

    return newMatrix;
}

/**
 * @brief Checks line for [
 *
 * @param c expression to check
 * @return int 1 if found else 0
 */
int checkLine(char *c)
{
    for (int i = 0; i < strlen(c); i++)
    {
        if (c[i] == '[')
            return 1;
    }
    return 0;
}

/**
 * @brief Evaluate script from the files
 *
 * @param filename file name
 * @return matrix_sf* final matrix formed
 */
matrix_sf *execute_script_sf(char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    char name;
    char *expr;
    matrix_sf *final;

    bst_sf *root = NULL;

    while (getline(&line, &len, file) != -1)
    {
        if (strlen(line) != 0)
        {
            name = line[0];
            expr = strchr(line, '=') + 1;

            if (checkLine(line))
                root = insert_bst_sf(create_matrix_sf(name, expr), root);
            else
            {
                final = evaluate_expr_sf(name, expr, root);
                root = insert_bst_sf(final, root);
            }
        }
    }

    final = copy_matrix(final->num_rows, final->num_cols, final->values);

    fclose(file);
    free_bst_sf(root);
    free(line);
    return final;
}