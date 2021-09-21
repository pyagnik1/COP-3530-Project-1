#include <iostream>
#include <string.h>
#include <stdio.h>

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
void preOrder(gatorInfo* root);





int main(){

	gatorInfo* root = NULL;

	root = insert(root,"Brandon",45674567);
	root = insert(root,"Brian" ,35455565);
	root = insert(root,"Briana", 87878787);
	root = insert(root,"Bella" ,95462138);
	


	preOrder(root);

	cout<<"\n";
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

void preOrder(gatorInfo* root){
	if(root == NULL){
		return;
	}

	preOrder(root->left);

	cout<<root->gatorName << "\n";

	preOrder(root->right);
}