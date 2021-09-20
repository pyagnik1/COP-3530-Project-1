#include <iostream>
#include <string.h>

using namespace std;

class gatorInfo
{

    int gatorID;
    char* gatorName;

    gatorInfo *right;
    gatorInfo *left;

};

gatorInfo *insert(gatorInfo *root, char *gatorID, int gatorName);

void printInorder(gatorInfo *root);

gatorInfo *removeID(gatorInfo *root, int gatorID);

gatorInfo *removeInorder(gatorInfo *root, int NthgatorID);

void searchGatorName(gatorInfo *root, char *gatorName);

void searchGatorID(gatorInfo *root, int gatorID);

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

gatorInfo* newGatorInfo(char* gatorName,int gatorID){

    gatorInfo* node = new gatorInfo();
    node->gatorName = gatorName;

    node->gatorID = gatorID;

    node->left = NULL;

    node->right = NULL;

    return node;

}

gatorInfo *insert(gatorInfo *root, char *gatorName, int gatorID)
{

    //Do normal BST insertion first->
    if(root == NULL){
        return (newGatorInfo(gatorName,gatorID));

    }
    gatorInfo *temp = root;

    if(gatorID < temp->gatorID){

        temp->left = insert(temp->left,gatorName,gatorID);
    }

    if(gatorID > temp->gatorID){

        temp->right = insert(temp->right,gatorName,gatorID);
    }

    


    return temp;
}







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
