#include <iostream>
#include <string.h>

using namespace std;

class gatorInfo
{
    // The class is based on Prof. Aman Trees-3.pdf
    public:
    int gatorID;
    char *gatorName;
    int height;
    gatorInfo *right;
    gatorInfo *left;
};

gatorInfo *insert(gatorInfo *root, char *gatorID, int gatorName);

void printInorder(gatorInfo *root);

gatorInfo *removeID(gatorInfo *root, int gatorID);

gatorInfo *removeInorder(gatorInfo *root, int NthgatorID);

void searchGatorName(gatorInfo *root, char *gatorName);

void searchGatorID(gatorInfo *root, int gatorID);

int maxOf(int x, int y);

int height(gatorInfo *root);

gatorInfo *rotateLeft(gatorInfo *node);

gatorInfo *rotateRight(gatorInfo *node);

int balance(gatorInfo* root);

int main()
{
    cout << "Hello World!\n";

    gatorInfo *root = NULL;

    int inputSize;

    scanf("%d", &inputSize);

    char *comand;

    char *name;

    int id;

    for (int i = 0; i < inputSize; i++)
    {

        scanf("%s", comand);

        if (strcmp(comand, "insert") == 0)
        {
            scanf("%s %d", name, id);

            root = insert(root, name, id);
        }

        if (strcmp(comand, "printInorder") == 0)
        {

            printInorder(root);
        }

        if (strcmp(comand, "remove") == 0)
        {

            scanf("%d", &id);
            root = removeID(root, id);
        }

        if (strcmp(comand, "removeInorder") == 0)
        {
            int NthgatorID;

            scanf("%d", &NthgatorID);

            root = removeInorder(root, NthgatorID);
        }

        if (strcmp(comand, "search") == 0)
        {

            char *input;

            int in;

            // I need to check if the next phrase is a string or int
            //Google it before testing
            scanf("%s", input);

            searchGatorID(root, in);
        }
    }
}

int maxOf(int x, int y)
{
    return (x > y) ? x : y;
}

int height(gatorInfo *root)
{

    // this implemantation is refrenced from Prof. Aman Trees-1.pdf slide #18
    if (root == NULL)
    {
        return 0;
    }

    return root->height;
}

int balance(gatorInfo* root){

    //This implementation is refrenced from Prof. Aman Trees-3.pdf slide # 33

    //psudo code-> Balance Factor of x = Height (left subtree of x) -Height (right subtree of x)

    if(root == NULL){

        return 0;
    }

    return height(root->left) - height(root->right);
}

gatorInfo *rotateLeft(gatorInfo *node)
{

    //Example from Prof. Resch AVL Trees Suplemental.pdf slide #9 -->
    //tree = 6,7,2,1,4,3

    gatorInfo *newParent = node->right; // based on example we save refrence to 3

    gatorInfo *grandChild = newParent->left; // based on example we save refrence to 4
    //above statement is same as grandchild = node->right->left

    newParent->left = node;

    node->right = grandChild;

    //I have also implimented update height function
    //This implemantation is refrenced from Prof. Aman Trees-1.pdf slide #18

    newParent->height = maxOf(height(newParent->left), height(newParent->right)) + 1;

    node->height = maxOf(height(node->right), height(node->left)) + 1;

    return newParent;
}

gatorInfo *rotateRight(gatorInfo *node)
{

    //Example from Prof. Resch AVL Trees Suplemental.pdf slide #9 -->
    //tree = 6,7,2,1,4,3

    gatorInfo *newParent = node->left;
    gatorInfo *grandChild = newParent->right; //this is the same as grandchild = node->left->right;

    newParent->right = node;
    node->left = grandChild;

    //I have also implimented update height function
    //This implemantation is refrenced from Prof. Aman Trees-1.pdf slide #18

    newParent->height = maxOf(height(newParent->left), height(newParent->right)) + 1;
    node->height = maxOf(height(node->right), height(node->left)) + 1;

    return newParent;
}

gatorInfo *newGatorInfo(char *gatorName, int gatorID)
{

    gatorInfo *node = new gatorInfo();
    node->gatorName = gatorName;

    node->gatorID = gatorID;

    node->left = NULL;

    node->right = NULL;

    return node;
}

gatorInfo *insert(gatorInfo *root, char *gatorName, int gatorID)
{

    //Do normal BST insertion first->
    //psudo code for this implementation is taken from Prof. Resch BST slide 6
    if (root == NULL)
    {
        return (newGatorInfo(gatorName, gatorID));
    }
    gatorInfo *temp = root;

    if (gatorID < temp->gatorID)
    {

        temp->left = insert(temp->left, gatorName, gatorID);
    }

    if (gatorID > temp->gatorID)
    {

        temp->right = insert(temp->right, gatorName, gatorID);
    }

    //same keys are not allowed
    if (gatorID == temp->gatorID)
    {
        return temp;
    }

    // End of normal BST

    //This implemantation is refrenced from Prof. Aman Trees-1.pdf slide #18
    temp->height = maxOf(height(temp->left),height(temp->right)) + 1;

    int balance = balance(temp);

    
    return temp;
}
//http://www.uoitc.edu.iq/images/documents/informatics-institute/Competitive_exam/DataStructures.pdf

void printInorder(gatorInfo *root)
{
}

gatorInfo *removeID(gatorInfo *root, int gatorID)
{
    gatorInfo *temp = root;

    return temp;
}

gatorInfo *removeInorder(gatorInfo *root, int NthgatorID)
{
    gatorInfo *temp = root;

    return temp;
}

void searchGatorName(gatorInfo *root, char *gatorName)
{
}

void searchGatorID(gatorInfo *root, int gatorID)
{
}