#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <queue>

using namespace std;

static const int IMBALANCE_THRESHHOLD = 1;

class gatorInfo
{
    // The class is based on Prof. Aman Trees-3.pdf
    public:
    int gatorID;
    string gatorName;
    int height;
    gatorInfo *right;
    gatorInfo *left;
};

gatorInfo* insert(gatorInfo* root, string gatorName, int gatorID);
gatorInfo* newGatorInfo(string gatorName,int gatorID);
int height(gatorInfo* root);
int max(int x,int y);
int balance(gatorInfo* root);
gatorInfo* rotateRight(gatorInfo* root);
gatorInfo* rotateLeft(gatorInfo* root);
gatorInfo* balanceTree(gatorInfo* root, int gatorID);
//redefine remove function
gatorInfo* removeGatorID(gatorInfo* root, int gatorID);
gatorInfo* findMin(gatorInfo* node);
void search(gatorInfo* root, int gatorID, gatorInfo* parent);
int searchGatorName(gatorInfo* root, string gatorName);
void printInorder(gatorInfo* root);
void printPreorder(gatorInfo* root);
void printPostorder(gatorInfo* root);
//redefine level and n remove 
void levele(gatorInfo* node);
void NthInorder(gatorInfo* node, int n);




int main(){

	gatorInfo* root = NULL;

	root = insert(root,"Brandon",45674567);
	root = insert(root,"Brian" ,35455565);
	root = insert(root,"Briana", 87878787);
	root = insert(root,"Bella" ,95462138);
	printPreorder(root);

	cout<<"\n";

	printPreorder(root);

	search(root, 007, NULL);

	

	int val2 = searchGatorName(root, "Brandon");

	if(val2 == 0){
		cout<<"unsuccessful\n";
	}
	if(val2 == 1){
		cout<<"successful in main val2\n";
	}


	int level = max(height(root->right),height(root->left));

	levele(root);

	NthInorder(root,2);

	printPreorder(root);
		

		//buid cin menue

	
	
}









gatorInfo* insert(gatorInfo* root, string gatorName, int gatorID){


	if(root == NULL){
		return newGatorInfo(gatorName, gatorID);
	}

	if(gatorID > root->gatorID){

		root->right = insert (root->right,gatorName,gatorID);
	}

	if(gatorID < root->gatorID){
		root->left = insert (root->left, gatorName, gatorID);
	}

	if(gatorID == root->gatorID){
		cout<<"cant be duplicate \n";
		return root;
	}

	root->height = max(height(root->right),height(root->left)) + 1;

	root = balanceTree(root,gatorID);

	return root;
}



//I made a saprete balanceTree function so I can reuse it in remove function
gatorInfo* balanceTree(gatorInfo* root, int gatorID){
	int balanceFactor = balance(root);

		/*
	-->Left Right case
		--> fix: 1.Rotate left
				-->root->val = 1, root->left->val = 2 
		
			3	<- balance = 2								3 <- balance = 2
		/																/
		1	<- balance = -1		--> 			2 <- balance = 1
		\														/
			2												1
		-->2. rotate righ
			-->root->val = 2
						3 <- balance = 2
					/
				2	<- balance = 1		-->			2 <- balance = 1 - 1 = 0
			/														/		\
		1														1				3
		
	*/
	if(balanceFactor > 1 && gatorID > root->left->gatorID ){
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	/*
	-->Left Left case
		--> fix: Rotate right
				-->root->left->val = 2
						3 <-balance =2
					/
				2	<-balance =1			-->				2 <- balance = 1- 1 = 0
			/															/		\
		1															1				3
	*/

	if(balanceFactor > 1 && gatorID < root->left->gatorID){
		return rotateRight(root);
	}

	/*
	-->Right Left case
		--> fix: 1. Rotae right
			-->root->right->val = 3
		
			1	<- balance = -2								1 <- balance = -2
				\																\
					3 <- balance = 1		--> 				2	<- balance = -1
				/																		\				
			2																				3
		-->2. Rotate left	
			-->root->val = 2, root->right->val = 3
		1	<-balance = -2
			\
				2		<- balance = -1			--> 				2 <- balance = 1 - 1 = 0
					\																/		\
						3														1				3
	*/

	if(balanceFactor < -1 && gatorID < root->right->gatorID){
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	/*
	--> Right Right case
		--> fix: Rotate 1 to left
		1 <- balance = -2
			\
				2	<- balance = -1			-->			2 <- balance = 1 - 1 = 0
					\													/		\
						3											1				3
	*/

	if(balanceFactor < -1 && gatorID > root->right->gatorID){
		return rotateLeft(root);
	}

	return root;
}









gatorInfo* newGatorInfo(string gatorName,int gatorID){

		gatorInfo* node = new class gatorInfo;

		node->gatorName = gatorName;

		node->gatorID = gatorID;

		node->left = NULL;

		node->right = NULL;

		return node;
	}




//the psudo code comes from weisse book page 154
int height(gatorInfo* root){
	return root == NULL ? 0: root->height;
}




int max(int x,int y){
	return (x>y) ? x:y;
}




int balance(gatorInfo* root){
	if(root == NULL){
		return 0;
	}

	return height(root->left) - height(root->right);
}







gatorInfo* rotateRight(gatorInfo* root){

	
	gatorInfo* newParent = root->left;

	gatorInfo* grandChild = newParent->right;

	/*
	Pre rotation-->
		root->val = 3, newParent->val = 2, grandChild = NULL
						root->	3
									/
	newParent	->	2	
							/		\					
						1			NULL	<- grandChild			
	*/

	newParent->right = root;

	root->left = grandChild;

	/*
		Post rotation
		newParent->val = 2, newParent->right->val = 3
					newParent->	2
										/		\
									1				3 <-root
												/
											NULL <-grandChild
	*/

	newParent->height = max(height(newParent->right),height(newParent->left)) +1;

	root->height = max(height(root->right),height(root->left)) + 1;
	
	return newParent;
}








gatorInfo* rotateLeft(gatorInfo* root){



	gatorInfo* newParent = root->right;

	gatorInfo* grandChild = newParent->left;

		/*
			Pre rotation
							root->	1
												\
							newParent->	2			
												/		\					
			grandChild->		NULL	   3				
		*/

	newParent->left = root;

	root->right = grandChild;

	/*
		Post rotation
		newParent->		2
								/		\
			root->	1				3
								\
								NULL <- grandChild
	*/

	newParent->height = max(height(newParent->right),height(newParent->left)) +1;

	root->height = max(height(root->right),height(root->left)) + 1;

	return newParent;


}


/*
*/
gatorInfo* removeGatorID(gatorInfo* root, int gatorID){

		if (root == NULL){
      return root;
		}
 
    
  	if ( gatorID < root->gatorID ){
     root->left = removeGatorID(root->left, gatorID);
		}
 
  
    if( gatorID > root->gatorID ){
     root->right = removeGatorID(root->right, gatorID);
		}

      
    if( (root->left == NULL) && (root->right != NULL) )
      {
        gatorInfo *temp = root->right;
 
            
      	if (temp == NULL)
        {
          temp = root;
          root = NULL;
        }
        else{ 
       	 *root = *temp; 
      		free(temp);
				}
      }

			if( (root->left != NULL) && (root->right == NULL) )
      {
        gatorInfo *temp = root->left;
 
            
      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else {
      	*root = *temp; 
      	free(temp);
			}
    }

		if((root->right == NULL) && (root->left != NULL)){
			gatorInfo* temp = root->left;

			if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else {
        *root = *temp; 
        free(temp);
			}

		}
				
    if(root->right != NULL && root->left != NULL)
    {
            
      gatorInfo* temp = findMin(root->right);
 
            
      root->gatorID = temp->gatorID;
 
           
      root->right = removeGatorID(root->right,temp->gatorID);
    }
    
		root->height = max(height(root->right),height(root->left)) + 1;

		root = balanceTree(root, gatorID);

	
		return root;
	}




gatorInfo* findMin(gatorInfo* node)
{
    gatorInfo* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}


void search(gatorInfo* root, int gatorID, gatorInfo* parent)
{
	
    
    if (root == nullptr)
    {
      cout << "unsuccessful\n";
      return;
    }
 
    
    if (root->gatorID == gatorID)
    {
      cout << "successful\n";
 
      return;
		}
 
    if (gatorID < root->gatorID) {
      return search(root->left, gatorID, root);
    }
 
    return search(root->right, gatorID, root);
}


int searchGatorName(gatorInfo* root, string gatorName){

		if(gatorName == root->gatorName){
			cout<<"successful\n";
			return 1;
		}

		searchGatorName(root->right, gatorName);

		searchGatorName(root->left, gatorName);

		return 0;
	}

void printInorder(gatorInfo* root){
	if(root != NULL && root->gatorID != 0){

		printInorder(root->left);
		cout<<root->gatorName << " "<<root->gatorID<<"\n";
		printInorder(root->right);
	}
}

void printPreorder(gatorInfo* root){
	if(root != NULL && root->gatorID != 0){

		cout<<root->gatorName << " "<<root->gatorID<<"\n";

		printPreorder(root->left);

		printPreorder(root->right);
	}
}

void printPostorder(gatorInfo* root){

	if(root != NULL && root->gatorID != 0){

		printPostorder(root->left);

		printPostorder(root->right);

		cout<<root->gatorName << " "<<root->gatorID<<"\n";
		
	}
}


void levele(gatorInfo* root)
{
    if (!root)
        return;
 
    // queue to hold tree node with level
    queue<pair<gatorInfo*, int> > q;
 
    q.push({root, 1}); // let root node be at level 1
 
    pair<gatorInfo*, int> p;
 
    // Do level Order Traversal of tree
    while (!q.empty()) {
        p = q.front();
        q.pop();
 
 
        if (p.first->left)
            q.push({ p.first->left, p.second + 1 });
        if (p.first->right)
            q.push({ p.first->right, p.second + 1 });
    }
		cout << p.second << "\n";
}


void NthInorder(gatorInfo* node, int n)
{
    static int count = 0;
    if (node == NULL)
        return;
 
    if (count <= n) {
 
        /* first recur on left child */
        NthInorder(node->left, n);
        count++;
 
        // when count = n then print element
        if (count == n)
            removeGatorID(node, node->gatorID);
 
        /* now recur on right child */
        NthInorder(node->right, n);
    }
}