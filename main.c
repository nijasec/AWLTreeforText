// C program to insert a node in AVL tree 
#include<stdio.h> 
#include<stdlib.h> 

struct Node* deleteNode(struct Node* root, char* key) ;
// An AVL tree node 
struct Node 
{ 
	char *data; 
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 

//searching for data
int iterativeSearch(struct Node* root, char *data) 
{ 
    // Traverse untill root reaches to dead end 
    while (root != NULL) { 
        // pass right subtree as new tree 
        if (strcmp(data,root->data)>0) 
            root = root->right; 
  
        // pass left subtree as new tree 
        else if (strcmp(data ,root->data)<0) 
            root = root->left; 
        else
            return 1; // if the key is found return 1 
    } 
    return 0; 
}

// A utility function to get maximum of two integers 
int max(int a, int b); 

// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

 
/* Helper function that allocates a new node with the given key and 
	NULL left and right pointers. */
struct Node* newNode(char *data,int len) 
{ 
	struct Node* node = (struct Node*) 
						malloc(sizeof(struct Node)); 
				node->data=(char*)malloc(len);
				
			memset(node->data,0,len);
			memcpy(node->data,data,len);
	
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, char *data,int len) 
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) 
		return(newNode(data,len)); 

	if (strcmp(data,node->data)<0) 
		node->left = insert(node->left, data,len); 
	else if (strcmp(data,node->data)>0) 
		node->right = insert(node->right, data,len); 
	else // Equal keys are not allowed in BST 
		return node; 

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && strcmp(data,node->left->data)<0) 
		return rightRotate(node); 

	// Right Right Case 
	if (balance < -1 && strcmp(data,node->right->data)>0) 
		return leftRotate(node); 

	// Left Right Case 
	if (balance > 1 && strcmp(data,node->left->data)>0) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && strcmp(data,node->right->data)<0) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the (unchanged) node pointer */
	return node; 
} 
void trim(char *src)
{
    int i, len;
    len = strlen(src);

    for(i = 0; i < len; i++) {
        if(src[i] == ' ') {
            continue;
        }
        if(src[i] == '\n') {
			src[i]=0;
            return;
			
        }
        //printf("%c", src[i]); // prints: host=1.2.3.4
    }
}

// A utility function to do inorder traversal of BST 
void inorder(struct Node *root) 
{ 
	if (root != NULL) 
	{ 
		inorder(root->left); 
		printf("%s \n", root->data); 
		inorder(root->right); 
	} 
} 
// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(struct Node *root) 
{ 
	if(root != NULL) 
	{ 
		
		printf("%s\n", root->data); 
		 preOrder(root->left);
		preOrder(root->right); 
	} 
} 

/* Drier program to test above function*/
int main() 
{ 
struct Node *root = NULL; 
int i=0,r;
char line[1000];
/* Constructing tree given in the above figure */
memset(line,0,sizeof(line));
	FILE *fp;
	fp=fopen("test.txt","r");
	//fp=fopen("testbst.txt","r");
	if(fp!=NULL)
	{
		

		
		
		do{
		
		r=fgets(line,sizeof(line),fp);
		//printf("%s",line);
		if(line[0]=='#')
			continue;
			trim(line);
		//if(root == NULL)
		if(*(line+(strlen(line)-1))=='\n')
				*(line+(strlen(line)-1))=0;
		root = insert(root, line,strlen(line)); 	
		//else
			//insert(root, line,strlen(line)); 
		
	//	number++;	
		//if(number>30)
			//break;
			
		}while(r!=NULL);
		
	}
	if(fp!=NULL)
	fclose(fp);
	memset(line,0,sizeof(line));
//root = insert(root, 20); 
//root = insert(root, 30); 
//root = insert(root, 40); 
//root = insert(root, 50); 
//root = insert(root, 25); 

/* The constructed AVL Tree would be 
			30 
		/ \ 
		20 40 
		/ \	 \ 
	10 25 50 
*/

printf("inorder traversal of the constructed AVL"
		" tree is \n"); 
inorder(root); 
char q;
char d[100];
int k;
		while(q!='q'){
			
			printf("\nenter q:-Quit d:-Delete s:-Search p:-printinorder =");
			scanf("%c",&q);
			switch(q)
			{
				case 's':
				printf("Enter text to search:");
				scanf("%s",line);
				if(iterativeSearch(root,line))
				{
					printf("Found!");
				}
				else
					printf("Not found :(");
				break;
				case 'd':
					printf("\nEnter data to delete:");
					scanf("%s",line);
					if(deleteNode(root,line)==NULL)
						printf("can not delete");
					else
						printf("deleted");
								
				break;
				case 'p':
				
				
				
				preOrder(root);
				break;
				
			}
			
		}

return 0; 
} 
/* Given a non-empty binary search tree, return the 
   node with minimum key value found in that tree. 
   Note that the entire tree does not need to be 
   searched. */
struct Node * minValueNode(struct Node* node) 
{ 
    struct Node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
// Recursive function to delete a node with given key 
// from subtree with given root. It returns root of 
// the modified subtree. 
struct Node* deleteNode(struct Node* root, char  *key) 
{ 
    // STEP 1: PERFORM STANDARD BST DELETE 
  
    if (root == NULL) 
        return root; 
  
    // If the key to be deleted is smaller than the 
    // root's key, then it lies in left subtree 
    if (strcmp(key,root->data)<0) 
        root->left = deleteNode(root->left, key); 
  
    // If the key to be deleted is greater than the 
    // root's key, then it lies in right subtree 
    else if(strcmp(key,root->data)>0) 
        root->right = deleteNode(root->right, key); 
  
    // if key is same as root's key, then This is 
    // the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            struct Node *temp = root->left ? root->left : 
                                             root->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
             *root = *temp; // Copy the contents of 
                            // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            struct Node* temp = minValueNode(root->right); 
  
            // Copy the inorder successor's data to this node 
            
			memcpy(root->data,temp->data,strlen(temp->data));
            // Delete the inorder successor 
            root->right = deleteNode(root->right, temp->data); 
        } 
    } 
  
    // If the tree had only one node then return 
    if (root == NULL) 
      return root; 
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    int balance = getBalance(root); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0) 
    { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root; 
}