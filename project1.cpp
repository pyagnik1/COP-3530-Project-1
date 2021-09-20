#include <iostream>
#include <string.h>

using namespace std;

class gatorInfo
{

    int gatorID;
    string gatorName;

    gatorInfo *right;
    gatorInfo *left;

    gatorInfo() : gatorID(0), left(nullptr), right(nullptr) {}
    gatorInfo(int x) : gatorID(x), left(nullptr), right(nullptr) {}
    gatorInfo(int x, gatorInfo *left, gatorInfo *right) : gatorID(x), left(left), right(right) {}
};

gatorInfo *insert(gatorInfo *root, char *gatorID, int gatorName);

void printInorder(gatorInfo *root);

gatorInfo *removeID(gatorInfo *root, int gatorID);

gatorInfo *removeInorder(gatorInfo *root, int NthgatorID);

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
            /* code */

            printInorder(root);
        }

        if (strcmp(comand, "remove") == 0)
        {
            /* code */
            scanf("%d", &id);
            root = removeID(root, id);
        }

        if (strcmp(comand, "removeInorder") == 0)
        {
            /* code */

            int NthgatorID;

            scanf("%d", &NthgatorID);

            root = removeInorder(root, NthgatorID);
        }
    }
}

gatorInfo *insert(gatorInfo *root, char *gatorID, int gatorName)
{

    gatorInfo *temp = root;

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
