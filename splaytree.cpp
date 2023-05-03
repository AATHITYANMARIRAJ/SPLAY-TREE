#include <bits/stdc++.h>
using namespace std;

//Tree Node
class node{
 public:
 	int key;
 	node *left;
 	node *right;

};
typedef struct node node;
//allocating a new node with the given key and NULL left and right pointers.
node *TreeNode(int key){
	node *Node=new node();
	Node->key=key;
	Node->left=Node->right=NULL;
	return (Node);
}

//A utility function for right-rotating a y-rooted subtree
node* rightrotate(node *x ){
	node* y=x->left; 
	x->left=y->right;
	y->right=x;
    return y;
}

//A utility function for left-rotating a y-rooted subtree
node *leftrotate(node *x){ //18
	node* y=x->right; //20;
	x->right=y->left;
	y->left=x;
	return y;
}

//If the key is present in the tree, this function moves it to the root
//If the key is not present , it returns the last item acceseed by root
//This function modifies the tree and returns the modified root

node* splay(node *root,int key)
{
	if(root==NULL || root->key==key){
		return root;
	}
	
	//key is in the left sub-tree
	if(root->key>key){
		if(root->left==NULL){
			return root;
		}
		//ZIG-ZIG ROTATION
		if(root->left->key>key){
			//FIRST RECURSIVELY BRING THE KEY VALUE AS THE ROOT OF LEFT-LEFT
			root->left->left=splay(root->left->left,key);
			
			//Do the first rotation for the root
			root=rightrotate(root);
		}
		
		//ZIG-ZAG ROTATION
		else if(root->left->key<key){
			//FIRST RECURSIVELY BRING THE KEY VALUE AS THE ROOT OF LEFT-RIGHT
			root->left->right=splay(root->left->right,key);
			
			//Do the first rotation followed by the second rotation
			if(root->right!=NULL){
				root->left=leftrotate(root->left);
			}
		}
		return(root->left==NULL)? root : rightrotate(root);
	}
	
	//If key is present in the right sub-tree
	else{
		if(root->right==NULL){
			return root;
		}
		//ZAG-ZAG(right-right)
		else if(root->right->key<key){
			//First recursively bring the key as the root of right-right
			root->right->right=splay(root->right->right,key);
			
			//do the first recursive rotation followed by the next
			root=leftrotate(root);
		}
		
		//ZAG-ZIG(right-left)
		else if(root->right->key>key){
			//First recursively rotate and bring the key as the root of right-left
			root->right->left=splay(root->right->left,key);
			
			if(root->right->left!=NULL){
				root->right=rightrotate(root->right);
			}
		}
	  //Do second rotation for root
	  	return(root->right==NULL)? root : leftrotate(root);
	}
}
node *bstSearch(struct node *root,int key){
		return splay(root,key);
}
	
void preOrder(struct node *root)
	{
		if(root!=NULL)
		{
			printf("%d\n",root->key);
			preOrder(root->left);
			preOrder(root->right);
		}
	}
node* insert(node *root,int key){
	if(root==NULL){
		return TreeNode(key);
	}
	
	//splay the last inserted node to root
	root=splay(root,key);
	
	//If key is aldready present,the return
	if(root->key==key) return root;
	
	//Insert the new node at the root
	node* new_node=TreeNode(key);
	
	if(key<root->key){
		new_node->right=root;
		new_node->left=root->left;
		root->left=NULL;
		
	}
	else{
		new_node->left=root;
		new_node->right=root->right;
		root->right=NULL;
	}
	return new_node;
}
node *delete_key(node *root,int key){
	node* temp;
	if(!root){
	   return NULL;
    }
	//SPLAY THE GIVEN KEY
	root=splay(root,key);
    
	//If key is not present then return root	
	if(key!=root->key){
		return root;
	} 
	
	//IF KEY IS PRESENT
	//IF LEFT CHILD DOES NOT EXIST
	//MAKE root->right as root
	if(!root->left){
		temp=root;
		root=root->right;
	} 
	
	//If key is present 
	//If left child exists
	else{
		temp=root;
		
		 /*Note: Since key == root->key,
        so after Splay(key, root->lchild),
        the tree we get will have no right child tree
        and maximum node in left subtree will get splayed*/
        
        //New root
        root=splay(root->left,key);
        
        //Make right child of previous root as
        // new root's right child
        root->right=temp->right;
	}
	//free the previous root node
	//node containing the key
	free(temp);
	return root;
}



int main(){
	node* root;
	int choice;
	do{
	       cout << "1. Insert a key" << endl;
            cout << "2. display" << endl;
            cout<< "3.delete"<<endl;
            cout<<"0.exit"<<endl;
            cout << "Enter your choice: ";
            cin >> choice;
	switch(choice){
	     case 1:	
			int element;
			cout<<"Enter the element\n";
			cin>>element;
			root=insert(root,element);
			cout<<"element inserted successfully\n";
		    break;
	    case 2:
			cout<<"The pre-order display of the elements are\n";
			preOrder(root);
		    break;
	    case 3:
			int del_element;
			printf("enter the key to be deleted\n");
			cin>>del_element;
			root=delete_key(root,del_element);
			cout<<del_element<<"is deleted successfully\n";
			break;
	    case 0:
	    	cout << "Exiting..." << endl;
             break;
	  
	}
	}while(choice!=0);
	return 0;
}