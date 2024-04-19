#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find the index of value in inOrder array
int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to construct binary search tree from inOrder and postOrder arrays
struct TreeNode* buildTree(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    struct TreeNode* root = newNode(postOrder[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd) {
        return root;
    }

    int inIndex = findIndex(inOrder, inStart, inEnd, root->data);

    root->right = buildTree(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    root->left = buildTree(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return root;
}

// Function to traverse the tree in breadth-first-search (DFS) traversal
void breadthFirstSearch(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a queue for BFS
    struct TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* temp = queue[front++];
        printf("%d ", temp->data);

        if (temp->left != NULL) {
            queue[rear++] = temp->left;
        }
        if (temp->right != NULL) {
            queue[rear++] = temp->right;
        }
    }
}

// Function to construct binary search tree and return root
struct TreeNode* bst_construct(int inOrder[], int postOrder[], int size) {
    int postIndex = size - 1;
    return buildTree(inOrder, postOrder, 0, size - 1, &postIndex);
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int size = sizeof(inOrder) / sizeof(inOrder[0]);

    struct TreeNode* root = bst_construct(inOrder, postOrder, size);

    printf("Breadth First Search Traversal: ");
    breadthFirstSearch(root);

    return 0;
}
