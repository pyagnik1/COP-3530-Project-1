#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <algorithm>

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
gatorInfo* removeGatorID(gatorInfo* root, int gatorID);
gatorInfo* findMin(gatorInfo* node);
void searchGatorID(gatorInfo* root,int gatorID);
void searchGatorName(gatorInfo* root, string gatorName);
void printInorder(gatorInfo* root);
void printPreorder(gatorInfo* root);
void printPostorder(gatorInfo* root);

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}



int main(){

	int iter = 0;

	cin>>iter;

	gatorInfo* root = NULL;

	for(int i =0; i<iter; i++){

		string comand;
		cin>>comand;

		if(comand == "search"){

			string valToSearch;

			cin>>valToSearch;

			// removes double quotes from string
			valToSearch.erase(remove(valToSearch.begin(),valToSearch.end(),'\"'),valToSearch.end());

			if(isNumber(valToSearch)){
				//convert string to int
				stringstream ss; 
				int gatorID = 0;
				ss << valToSearch;
				ss >> gatorID;

				searchGatorID(root,gatorID);

			}

			else{
				searchGatorName(root,valToSearch);
			}

		}

		if(comand == "insert"){

			string gatorName;
			int gatorID = 0;

			cin>> gatorName;
			cin>> gatorID;

			gatorName.erase(remove(gatorName.begin(),gatorName.end(),'\"'),gatorName.end());

			root = insert(root,gatorName,gatorID);

			
		}

		if(comand == "remove"){
			int gatorID =0;
			cin>> gatorID;

			root = removeGatorID(root,gatorID);
		}

		if(comand == "printInorder"){
			printInorder(root);
			cout<<"\n";
		}

		if(comand == "printPostorder"){
			printPostorder(root);
			cout<<"\n";
		}

		if(comand == "printPreorder"){
			printPreorder(root);
			cout<<"\n";
		}

	}

	
}








//The inspiration to create a seprate balance function came from weiss book page # 155
gatorInfo* insert(gatorInfo* root, string gatorName, int gatorID){


	if(root == NULL){
		cout<<"successful\n";
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



//Since balance function is used multiple times I created a saprete functino, psudo code come from slack project discussion
int balance(gatorInfo* root){
	if(root == NULL){
		return 0;
	}

	return height(root->left) - height(root->right);
}






//The variable names for rotateRight and rotateLeft function were inspired by Prof. Resch slides

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


// Psudo code used for remove functino comes weiss book page # 157
gatorInfo* removeGatorID(gatorInfo* root, int gatorID){

 
 if(root == NULL){
	 cout<<"\nsuccessful\n";
	 return root;
 }

 if(gatorID < root->gatorID){
	 root->left = removeGatorID(root->left, gatorID);

 }

 if(gatorID > root->gatorID){
	 root->right = removeGatorID(root->right, gatorID);
 }

 else{
	 if(root->left == NULL){
		 gatorInfo* newChild = new class gatorInfo;
		 newChild = root->right;
		 delete root;
	 }

	 if(root->right == NULL){
		 gatorInfo* newChild = new class gatorInfo;
		 newChild = root->left;
		 delete root;
	 }


	 if(root->right != NULL && root->left != NULL){
		 gatorInfo* newChild = new class gatorInfo;

		 newChild = findMin(root->right);
		 root->right = removeGatorID(root->right, gatorID);
	 }
 }

	root->height = max(height(root->right),height(root->left)) + 1;

	root = balanceTree(root, gatorID);

	
	return root;
}



// Psudo code for findMin comes from CLRS book page # 291
gatorInfo* findMin(gatorInfo* root)
{
    while(root->left != NULL){
			root = root->left;
		}

		return root;
}


// Used the CLRS to learn the how to recursively find an item in the Trees
//The psudo code is on page # 288
void searchGatorID(gatorInfo* root,int gatorID){
	if(root->gatorID == gatorID){
		cout<<"successful\n";
		
	}
	if(gatorID < root->gatorID){
		searchGatorID(root->left, gatorID);
	}

	if(gatorID > root->gatorID){
		searchGatorID(root->right,gatorID);
	}

	if(root == NULL){
		cout<<"unsuccessful\n";
	}
}

void searchGatorName(gatorInfo* root, string gatorName){

	if(gatorName == root->gatorName){
		cout<<"successful\n";
		
	}

	searchGatorName(root->right, gatorName);

	searchGatorName(root->left, gatorName);

	if(root == NULL){
		cout<<"unsuccessful\n";
	}
}


//I used psudo code from Prof. Resch module 3 slides set 2 slide # 3
void printInorder(gatorInfo* root){
	if(root != NULL && root->gatorID != 0){

		printInorder(root->left);
		cout<<root->gatorName << " , ";
		printInorder(root->right);
	}
}

void printPreorder(gatorInfo* root){
	if(root != NULL && root->gatorID != 0){

		cout<<root->gatorName << " , ";

		printPreorder(root->left);

		printPreorder(root->right);
	}
}

void printPostorder(gatorInfo* root){


	if(root != NULL && root->gatorID != 0){

		printPostorder(root->left);

		printPostorder(root->right);

		cout<<root->gatorName;
		
	}
	
} 

