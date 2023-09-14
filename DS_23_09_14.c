#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* data;
    struct StackNode* next;
}StackNode;

typedef struct Stack {
    StackNode* top;
}Stack;

// 스택 초기화
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// 스택이 비어있는지 확인
int is_empty(Stack* stack) {
    return (stack->top == NULL);
}

// 스택 푸시
void push(Stack* stack, TreeNode* data) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

// 스택 팝
TreeNode* pop(Stack* stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "stack is empty.\n");
        exit(1);
    }
    StackNode* top_node = stack->top;
    TreeNode* data = top_node->data;
    stack->top = top_node->next;
    free(top_node);
    return data;
}

// 스택 메모리 해제
void free_stack(Stack* stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}

// 중위 순회
void inorder_iter(TreeNode* root) {
    Stack* stack = create_stack();
    while (!is_empty(stack) || root != NULL) {
        if (root != NULL) {
            push(stack, root);
            root = root->left;
        }
        else {
            root = pop(stack);
            printf("%d ", root->data);
            root = root->right;
        }
    }
    free_stack(stack);
}

// 전위 순회
void preorder_iter(TreeNode* root) {
    Stack* stack = create_stack();
    push(stack, root);
    while (!is_empty(stack)) {
        root = pop(stack);
        printf("%d ", root->data);
        if (root->right != NULL) {
            push(stack, root->right);
        }
        if (root->left != NULL) {
            push(stack, root->left);
        }
    }
    free_stack(stack);
}

// 후위 순회
void postorder_iter(TreeNode* root) {
    Stack* stack = create_stack();
    Stack* output = create_stack();

    push(stack, root);
    while (!is_empty(stack)) {
        root = pop(stack);
        push(output, root);
        if (root->left != NULL) {
            push(stack, root->left);
        }
        if (root->right != NULL) {
            push(stack, root->right);
        }
    }
    while (!is_empty(output)) {
        root = pop(output);
        printf("%d ", root->data);
    }

    free_stack(stack);
    free_stack(output);
}

// 트리 메모리 해제
void free_tree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(int argc, char* argv[]) {
    TreeNode* n1, * n2, * n3, * n4, * n5, * n6, * n7, * n8, * n9, * n10, * n11;

    n1 = (TreeNode*)malloc(sizeof(TreeNode));
    n2 = (TreeNode*)malloc(sizeof(TreeNode));
    n3 = (TreeNode*)malloc(sizeof(TreeNode));
    n4 = (TreeNode*)malloc(sizeof(TreeNode));
    n5 = (TreeNode*)malloc(sizeof(TreeNode));
    n6 = (TreeNode*)malloc(sizeof(TreeNode));
    n7 = (TreeNode*)malloc(sizeof(TreeNode));
    n8 = (TreeNode*)malloc(sizeof(TreeNode));
    n9 = (TreeNode*)malloc(sizeof(TreeNode));
    n10 = (TreeNode*)malloc(sizeof(TreeNode));
    n11 = (TreeNode*)malloc(sizeof(TreeNode));

    n1->data = 1;
    n1->left = n2;
    n1->right = n7;

    n2->data = 2;
    n2->left = n3;
    n2->right = n6;

    n3->data = 3;
    n3->left = n4;
    n3->right = n5;

    n4->data = 4;
    n4->left = NULL;
    n4->right = NULL;

    n5->data = 5;
    n5->left = NULL;
    n5->right = NULL;

    n6->data = 6;
    n6->left = NULL;
    n6->right = NULL;

    n7->data = 7;
    n7->left = n8;
    n7->right = n9;

    n8->data = 8;
    n8->left = NULL;
    n8->right = NULL;

    n9->data = 9;
    n9->left = n10;
    n9->right = n11;

    n10->data = 10;
    n10->left = NULL;
    n10->right = NULL;

    n11->data = 11;
    n11->left = NULL;
    n11->right = NULL;

    printf("<Traversal with Stack>\n");
    printf("1.전위순회\n");
    preorder_iter(n1);
    printf("\n");

    printf("2. 중위순회\n");
    inorder_iter(n1);
    printf("\n");

    printf("3. 후위 순회\n");
    postorder_iter(n1);
    printf("\n");

    free_tree(n1);

    return 0;
}