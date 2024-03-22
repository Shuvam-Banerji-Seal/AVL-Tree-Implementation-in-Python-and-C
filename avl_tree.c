#include <stdio.h>
#include <stdlib.h>

// Define structure for AVL Tree Node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Function to get height of a node
int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get balance factor of a node
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to perform right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// Function to perform left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// Function to update height and balance of a node
void updateHeightAndBalance(Node* node) {
    if (node != NULL) {
        node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    }
}

// Function to insert a node into the AVL tree
Node* insert(Node* root, int data) {
    // Perform standard BST insertion
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root; // Duplicate keys not allowed

    // Update height and balance of the current node
    updateHeightAndBalance(root);

    // Check balance factor and perform rotations if necessary
    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the node with minimum value in a tree rooted with given node
Node* findMinNode(Node* root) {
    Node* current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
Node* deleteNode(Node* root, int data) {
    // Perform standard BST delete
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = findMinNode(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height and balance of the current node
    updateHeightAndBalance(root);

    // Check balance factor and perform rotations if necessary
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to print the tree in BFS manner with balance factors
void printBFSWithBF(Node* root) {
    if (root == NULL)
        return;

    // Create a queue for level order traversal
    Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int currentLevelNodes = rear - front;
        while (currentLevelNodes--) {
            Node* current = queue[front++];
            int balanceFactor = getHeight(current->left) - getHeight(current->right);
            printf("%d(%d) ", current->data, balanceFactor);

            if (current->left != NULL)
                queue[rear++] = current->left;
            if (current->right != NULL)
                queue[rear++] = current->right;
        }
        printf("\n");
    }
}

int main() {
    Node* root = NULL;

    // Menu-based system
    while (1) {
        printf("\nAVL Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print Tree with Balance Factors\n");
                printf("4. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int data;
                printf("Enter a value to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Inserted: %d\n", data);
                printBFSWithBF(root);
                break;
            }
            case 2: {
                int data;
                printf("Enter a value to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                printf("Deleted: %d\n", data);
                printBFSWithBF(root);
                break;
            }
            case 3:
                printf("AVL Tree with Balance Factors:\n");
                printBFSWithBF(root);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

       
