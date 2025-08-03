// c code for every functions like preoreder, inorder, postorder traversal,height of binary tree,search ing in binary tree etc,sizeof binary tree, etc.,to find maximum and minimum value in binary tree, etc.,
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
    int data;
    struct node *left;
    struct node *right;
};
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void insert(struct node** root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
    } else if (data < (*root)->data) {
        insert(&((*root)->left), data);
    } else {
        insert(&((*root)->right), data);
    }
}
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void preorder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(struct node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
int height(struct node* root) {
    if (root == NULL) {
        return -1; // Height of an empty tree is -1
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
int search(struct node* root, int data) {
    if (root == NULL) {
        return 0; // Not found
    }
    if (root->data == data) {
        return 1; // Found
    } else if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}
int findMin(struct node* root) {
    if (root == NULL) {
        return -1; // Tree is empty
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}
int findMax(struct node* root) {
    if (root == NULL) {
        return -1; // Tree is empty
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}
int size(struct node* root) {
    if (root == NULL) {
        return 0; // Size of an empty tree is 0
    }
    return 1 + size(root->left) + size(root->right);
}
int width(struct node* root) {
    if (root == NULL) {
        return 0; // Width of an empty tree is 0
    }
    int leftWidth = width(root->left);
    int rightWidth = width(root->right);
    return 1 + (leftWidth > rightWidth ? leftWidth : rightWidth);
}
int depth(struct node* root, int data) {
    if (root == NULL) {
        return -1; // Data not found
    }
    if (root->data == data) {
        return 0; // Found at root
    }
    int leftDepth = depth(root->left, data);
    if (leftDepth != -1) {
        return leftDepth + 1; // Found in left subtree
    }
    int rightDepth = depth(root->right, data);
    if (rightDepth != -1) {
        return rightDepth + 1; // Found in right subtree
    }
    return -1; // Data not found
}
int diameter(struct node* root) {
    if (root == NULL) {
        return 0; // Diameter of an empty tree is 0
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);
    return (leftHeight + rightHeight + 1 > leftDiameter && leftHeight + rightHeight + 1 > rightDiameter) ? 
           leftHeight + rightHeight + 1 : 
           (leftDiameter > rightDiameter ? leftDiameter : rightDiameter);
}
void freeTree(struct node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main(){
    struct node* root = NULL;
    int choice, data;
    do{
        printf("\n\nBinary Search Tree Operations\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Height of Tree\n");
        printf("6. Search\n");
        printf("7. Find Minimum Value\n");
        printf("8. Find Maximum Value\n");
        printf("9. Size of Tree\n");
        printf("10. Width of Tree\n");
        printf("11. Depth of Node\n");
        printf("12. Diameter of Tree\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                insert(&root, data);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Height of Tree: %d\n", height(root));
                break;
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &data);
                if (search(root, data)) {
                    printf("Value %d found in the tree.\n", data);
                } else {
                    printf("Value %d not found in the tree.\n", data);
                }
                break;
            case 7:
                printf("Minimum Value: %d\n", findMin(root));
                break;
            case 8:
                printf("Maximum Value: %d\n", findMax(root));
                break;
            case 9:
                printf("Size of Tree: %d\n", size(root));
                break;
            case 10:
                printf("Width of Tree: %d\n", width(root));
                break;  
            case 11:
                printf("Enter value to find depth: ");
                scanf("%d", &data);
                int depthValue = depth(root, data);
                if (depthValue != -1) {
                    printf("Depth of node with value %d: %d\n", data, depthValue);
                } else {
                    printf("Node with value %d not found in the tree.\n", data);
                }
                break;
            case 12:
                printf("Diameter of Tree: %d\n", diameter(root));
                break;
            case 13:
                freeTree(root);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    while (choice != 13);
    return 0;
}