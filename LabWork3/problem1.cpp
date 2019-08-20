#include <iostream>
using namespace std;
int level = 0;
int leafnodes[100];
int subpaths[100];
int s = 0;
int i = 0;
struct uniNode
{
	int nodeValue;
	struct uniNode *left;
	struct uniNode *right;
	struct uniNode *parent;
	char color;
	int height;
};
uniNode *rootBST,*rootRBT,*rootAVL;

void search(uniNode *tree,int a);
void create(uniNode *tree);
void printAllPaths(uniNode *tree);
void printInOrder(uniNode *tree); //for all three trees

int storeHeight(uniNode *tree); //for BST and RBT

void rightRotate(uniNode **rootPassed,uniNode *tree); //for RBT and AVL
void leftRotate(uniNode **rootPassed,uniNode *tree);  //for RBT and AVL

void checkColor(uniNode *tree); //for RBT
void insertRBT(uniNode *tree,int value);
void printTreeRBT(uniNode *tree);

void insertBST(uniNode *tree,int value); //for BST

void printTree(uniNode *tree); //for BST and AVL

void createAVLInOrder(uniNode *tree); //for AVL
uniNode *rightRotateAVL(uniNode *y) ;
uniNode *leftRotateAVL(uniNode *x) ;
uniNode *insertAVL(uniNode *tree,int value);
int balanceTree(uniNode *tree);



void create(uniNode *tree)
{
	if(tree->left)
		create(tree->left);
	
	if(tree->right)
		create(tree->right);
	if(!tree->left && !tree->right)
	{
		leafnodes[i] = tree->nodeValue;
		i++;
	}
}
void search(uniNode *tree,int a)
{
	if(tree->nodeValue == a)  //
		{
			subpaths[s]=tree->nodeValue;
			s++;
		}
	else if(tree->nodeValue > a)
	{
		subpaths[s]=tree->nodeValue;
			s++;
		search(tree->left,a);
	}
	else
	{
		subpaths[s]=tree->nodeValue;
			s++;
		search(tree->right,a);
	}

}
void printAllPaths(uniNode *tree)
{
	for(int j = 0; j< i ; j++)
	{
		int value = leafnodes[j];
		search(tree,value);
		cout<<j+1<<". path is"<<endl;
		for(int l = 0;l<s;l++)
		{
			cout<<"\t";
			for(int k = l;k<s;k++)
			{
				if(k != s-1)
					cout<<subpaths[k]<<"->";
				else
					cout<<subpaths[k];
			}
			cout<<endl;
		}
		cout<<endl;
		for(int l = 0;l<s;l++)
		{
			subpaths[l] = 0;
		}
		s = 0;
	}
	for(int j = 0;j<i;j++)
	{
		leafnodes[j] = 0;
	}
	i = 0; 
	
}
void printInOrder(uniNode *tree)
{
	if(tree)
	{
		printInOrder(tree->left);
		cout<<tree->nodeValue<<" ";
		printInOrder(tree->right);
	}
}

int storeHeight(uniNode *tree)
{
	if(!tree)
		return 0;
	else if(!tree->left && !tree->right) //leafnode
		tree->height = 1;
	else
	{
		if(storeHeight(tree->left)>=storeHeight(tree->right))
	    	tree->height = storeHeight(tree->left)+1;
	    else
	    	tree->height = storeHeight(tree->right)+1;	}
	return tree->height;
}

void rightRotate(uniNode **rootPassed,uniNode *tree)
{
	uniNode *treeL = tree->left; 
  
    tree->left = treeL->right; 
  
    if (tree->left != NULL) 
        tree->left->parent = tree; 
  
    treeL->parent = tree->parent; 
  
    if (tree->parent == NULL) 
        *rootPassed = treeL; 
  
    else if (tree == tree->parent->left) 
        tree->parent->left = treeL; 
  
    else
        tree->parent->right = treeL; 
  
    treeL->right = tree; 
    tree->parent = treeL; 
    treeL = NULL;
    delete treeL;
}
void leftRotate(uniNode **rootPassed,uniNode *tree)
{
    uniNode *treeR = tree->right; 
    tree->right = treeR->left; 
    if (tree->right != NULL) 
        tree->right->parent = tree; 
  
    treeR->parent = tree->parent;
  
    if (tree->parent == NULL)
    	*rootPassed = treeR; 
    else if (tree == tree->parent->left) 
        tree->parent->left = treeR; 
    else
        tree->parent->right = treeR; 
  
    treeR->left = tree; 
    tree->parent = treeR; 
    treeR = NULL;
    delete treeR;
}

void checkColor(uniNode *tree)
{
	uniNode *p = NULL;
	uniNode *gp = NULL ;
	if(tree == rootRBT)
		tree->color = 'B';
	else if(tree != rootRBT && tree->parent->color != 'B')
	{	
		uniNode *p = tree->parent;
		uniNode *gp = p->parent;
		uniNode *u = new uniNode;
		if(p == gp->left)
			u = gp->right; //pehle new uniNode likhna zruri hai ??
		else
			u = gp->left;
		if(u && u->color == 'R')
		{
			u->color = 'B';
			p->color = 'B';
			gp->color = 'R';
			checkColor(gp);
		}
		else
		{
			if(tree == p->left && p == gp->left)
			{
				rightRotate(&rootRBT, gp);
				char colortemp = p->color;
				p->color = gp->color;
				gp->color = colortemp;
				checkColor(gp);
			}
			else if(tree == p->right && p == gp->left)
			{
				leftRotate(&rootRBT,p);
				tree = p;
				p = tree->parent;
				rightRotate(&rootRBT,gp);
				char colortemp = p->color;
				p->color = gp->color;
				gp->color = colortemp;
				checkColor(gp);
			}
			else if(tree == p->right && p == gp->right)
			{
				leftRotate(&rootRBT,gp);
				char colortemp = p->color;
				p->color = gp->color;
				gp->color = colortemp;
				checkColor(gp);
			}
			else if(tree == p->left && p == gp->right)
			{
				rightRotate(&rootRBT,p);
				tree = p;
				p = tree->parent;
				leftRotate(&rootRBT,gp);
				char colortemp = p->color;
				p->color = gp->color;
				gp->color = colortemp;
				checkColor(gp);
			}
		}
	}
}
void insertRBT(uniNode *tree,int value)
{
	if(!rootRBT)
	{
		rootRBT = new uniNode;
		rootRBT->nodeValue = value;
		rootRBT->color = 'B'; //zrurat hai kya?
		cout<<"Inserted successfully in Red Black Tree!"<<endl;
	}	
	else
	{
		if(value == tree->nodeValue)
			cout<<"Element already present in the Red Black Tree"<<endl;
		else if(value < tree->nodeValue)
		{
		    if (tree->left != NULL)
			    insertRBT(tree->left,value);
			else
			{
				tree->left = new uniNode;
	            tree->left->nodeValue = value;
	            tree->left->parent = tree;
	            tree->left->color = 'R';
	            checkColor(tree->left);
	            cout<<"Inserted successfully in Red Black Tree!"<<endl;
			}	           	
		}
		else
		{
			if (tree->right != NULL)
			    insertRBT(tree->right,value);
			else
			{
				tree->right = new uniNode;
	            tree->right->nodeValue = value;
	            tree->right->parent = tree;
	            tree->right->color = 'R';
	            checkColor(tree->right);
	            cout<<"Inserted successfully in Red Black Tree!"<<endl;
			}
		}
	}
}
void printTreeRBT(uniNode *tree)
{
	if(tree)
	{
		for(int j = 0 ;j<level;j++)
			cout<<"\t";	
		level++;
		
		if(tree->right && !tree->left)
			cout<< tree->nodeValue <<"[" <<tree->right->height<<"]["<<tree->color<<"]"<<endl;

		else if(tree->left && !tree->right)
			cout<< tree->nodeValue <<"[" <<tree->left->height<<"]["<<tree->color<<"]"<<endl;

		else if(tree->left && tree->right)
		{
			if(tree->left->height > tree->right->height )
				cout<< tree->nodeValue <<"[" << (tree->left->height - tree->right->height) <<"]["<<tree->color<<"]"<<endl;
			else if(tree->left->height < tree->right->height )
				cout<< tree->nodeValue <<"[" << (tree->right->height - tree->left->height) <<"]["<<tree->color<<"]"<<endl;
			else
				cout<< tree->nodeValue <<"[" << (tree->right->height - tree->left->height) <<"]["<<tree->color<<"]"<<endl;
		}
		else
			cout<< tree->nodeValue <<"["<<tree->color<<"]"<<endl;
		printTreeRBT(tree->left);	
		printTreeRBT(tree->right);	
		level--;
	}
}

void insertBST(uniNode *tree,int value)
{
	if(!rootBST)
	{
		rootBST = new uniNode;
		rootBST->nodeValue = value;
		cout<<"Inserted successfully in Binary Search Tree!"<<endl;
	}	
	else
	{
		if(value == tree->nodeValue)
			cout<<"Element already present in the Binary Search Tree"<<endl;
		else if(value < tree->nodeValue)
		{
		    if (tree->left != NULL)
			    insertBST(tree->left,value);
			else
			{
				tree->left = new uniNode;
	            tree->left->nodeValue = value;
	            //tree->left->parent = tree;
	            cout<<"Inserted successfully in Binary Search Tree!"<<endl;
			}	           	
		}
		else
		{
			if (tree->right != NULL)
			    insertBST(tree->right,value);
			else
			{
				tree->right = new uniNode;
	            tree->right->nodeValue = value;
	            //tree->right->parent = tree;
	            cout<<"Inserted successfully in Binary Search Tree!"<<endl;
			}
		}
	}
}
void printTree(uniNode *tree)
{
	if(tree)
	{
		for(int j = 0 ;j<level;j++)
			cout<<"\t";	
		level++;
		
		if(tree->right && !tree->left)
			cout<< tree->nodeValue <<"[" <<tree->right->height<<"]"<<endl;

		else if(tree->left && !tree->right)
			cout<< tree->nodeValue <<"[" <<tree->left->height<<"]"<<endl;

		else if(tree->left && tree->right)
		{
			if(tree->left->height >= tree->right->height )
				cout<< tree->nodeValue <<"[" << (tree->left->height - tree->right->height) <<"]"<<endl;
			else
				cout<< tree->nodeValue <<"[" << (tree->right->height - tree->left->height) <<"]"<<endl;
		}
		else
			cout<< tree->nodeValue <<endl;
		printTree(tree->left);	
		printTree(tree->right);	
		level--;
	}
}

int balanceTree(uniNode *tree)
{
	int bf;
	if(tree->right && !tree->left)
		bf = -tree->right->height;
	else if(tree->left && !tree->right)
		bf = tree->left->height;
	else if(tree->left && tree->right)
		bf = (tree->left->height - tree->right->height);
	else
		bf = 0;
	return bf;
}
uniNode *rightRotateAVL(uniNode *y)  
{  
    uniNode *x = y->left;  
    uniNode *T2 = x->right;  
 
    x->right = y;  
    y->left = T2;  
   	storeHeight(rootAVL);  
    return x;  
} 
uniNode *leftRotateAVL(uniNode *x)  
{  
    uniNode *y = x->right;  
    uniNode *T2 = y->left;  
   
    y->left = x;  
    x->right = T2;  
  	storeHeight(rootAVL);
    return y;  
} 
uniNode* insertAVL(uniNode *tree,int value)
{
	if (tree == NULL)  
	{
		uniNode *node = new uniNode;
		node->nodeValue = value;
        return node;  
	}
  
    if (value < tree->nodeValue)  
    {
        tree->left = insertAVL(tree->left, value);  
        //tree->left->parent = tree;
    }
    else 
    {
        tree->right = insertAVL(tree->right, value);
        //tree->right->parent = tree; 
    }
     
    storeHeight(rootAVL);
   	int a = balanceTree(tree);

    if(tree->left)
    {
    	if (a > 1 && value < tree->left->nodeValue)  
        return rightRotateAVL(tree);   
	    if (a > 1 && value > tree->left->nodeValue)  
	    {  
	        tree->left = leftRotateAVL(tree->left);  
	        return rightRotateAVL(tree);  
	    }
    }
    if(tree->right)
    {
    	
    	if (a < -1 && value > tree->right->nodeValue)  
        return leftRotateAVL(tree);   
      
	    if (a < -1 && value < tree->right->nodeValue)  
	    {  
	        tree->right = rightRotateAVL(tree->right);  
	        return leftRotateAVL(tree);  
	    }
    }
      
    return tree;
}

void createAVLInOrder(uniNode *tree)
{
	if(tree)
	{
		createAVLInOrder(tree->left);
		rootAVL = insertAVL(rootAVL,tree->nodeValue);
		createAVLInOrder(tree->right);
	}
}

int main()
{
	cout<<"1 - Insert in Binary Search Tree and Red Black Tree"<<endl;
	cout<<"2 - Create AVL tree from InOrder traversal of Binary Search Tree"<<endl;
	cout<<"3 - Print inorder traversal of all trees"<<endl;
	cout<<"5 - Print all the trees"<<endl;
	cout<<"6 - exit"<<endl;
	while (1)
    {
        cout<<"Enter choice : ";
        int ch;
        cin>>ch;
        switch (ch)
        {
            case 1:
            	int value;
				cout<<"Enter the value to be stored"<<endl;
				cin>>value;
            	insertBST(rootBST,value);
            	cout<<endl;
            	insertRBT(rootRBT,value);
                break;
            case 2:
            	rootAVL = NULL;
            	createAVLInOrder(rootBST);
            	 cout<<"Created successfully  AVL Tree!"<<endl;
            	break;
            case 3:
            	if(rootBST)
            	{
            		cout<<"InOrder in BST is : ";
            		printInOrder(rootBST);
            	}
            	else
					cout<<"Binary Search Tree is Empty";
				if(rootRBT)
            	{
            		cout<<"\nInOrder in RBT is : ";
					printInOrder(rootRBT);
            	}
            	else
					cout<<"\nRed Black Tree is Empty";
				if(rootAVL)
            	{
            		cout<<"\nInOrder in AVL is : ";
					printInOrder(rootAVL);
					cout<<endl;
            	}
            	else
					cout<<"\nAVL Tree is Empty"<<endl;
				break;
            case 4:
            	cout<<"\nBST:"<<endl;
            	create(rootBST);
              	printAllPaths(rootBST);
              	cout<<"\nRBT:"<<endl;
              	create(rootRBT);
              	printAllPaths(rootRBT);
              	cout<<"\nAVL:"<<endl;
              	create(rootAVL);
              	printAllPaths(rootAVL);
            	break;
            case 5:
            	storeHeight(rootBST);
            	storeHeight(rootRBT);
            	storeHeight(rootAVL);
            	if(rootBST)
            	{
            		cout<<"\nBST:"<<endl;
              		printTree(rootBST);
            	}
               	else
					cout<<"Binary Search Tree is Empty";
				if(rootRBT)
				{
					cout<<"\nRBT:"<<endl;
					printTreeRBT(rootRBT);
				}
            	else
					cout<<"Red Black Tree is Empty"<<endl;
				if(rootAVL)
				{
					cout<<"\nAVL:"<<endl;
					printTree(rootAVL);
				}
            	else
					cout<<"AVL Tree is Empty"<<endl;
            	break;
            case 6:
                exit(0);
            default:
                cout<<"Wrong choice menu"<<endl;
        }
    }
	return 0;
}