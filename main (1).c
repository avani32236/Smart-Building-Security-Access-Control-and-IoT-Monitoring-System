#include"header.h"
BST *Parent;
int main()
{
  BST *root=0,*r;
  int op,num;
  while(1){
  printf("Enter Your choice\n");
  printf("1)insert 2)inorder 3)postorder 4)preorder 5)search 6)delete 7)exit\n");
  scanf("%d",&op);
  
  switch(op){
   case 1: printf("enter num to insert\n");
   			scanf("%d",&num);
   			insertNode(&root,num);break;
   case 2: inOrder(root);break;
   case 3: postOrder(root);break;
   case 4: preOrder(root);break;
  
   case 5:  printf("enter num to search\n");
   			scanf("%d",&num);
   			r=searchNode(root,num);
   			if(r==0) printf("Num not Found\n");
   			else printf("NUM found\n");break;
  case 6:   printf("enter num to delete\n");
   			scanf("%d",&num);		
   			deleteNode(&root,num);break;
  case 7: exit(0);
  default: printf("Unknwon choice\n");
  }
 }

}
void deleteNode(BST **ptr,int n)
{
  if(*ptr){
      BST *del=searchNode(*ptr,n);
      BST *p=Parent;
      if(del){
       //////////delete  a leaf node 
    abc:
       if(del->left==0 && del->right==0)
       {
         if(del == p->left)
            p->left=0;
         else if( del == p->right)
          p->right=0;   
       
        free(del);
        return ;
       }
      //////////// delete a node having one child left
      if(del->left!=0 && del->right==0)
      {
      	if(del == p->left)
      	  p->left= del->left;
      	else if( del == p->right)
      	  p->right= del->left;  

        free(del);
        return;
	  }
		//////////// delete a node having one child right
      if(del->left==0 && del->right!=0)
      {
      	if(del == p->left)
      	  p->left= del->right;
      	else if( del == p->right)
      	  p->right= del->right;  

        free(del);
        return;
	  }
	  /////////////////delete a node having two childs
	  if(del->left!=0 && del->right!=0)
	  {
	     BST *min=del->right;
	     p=del;
	     while(min->left)
	     {
	        p=min;
	        min=min->left;
	     }
		 del->num=min->num;
		 del=min;
		 goto abc;
	  }  
     }
     else
     	printf("Num not found\n");
  }
  else
    printf("No records\n");

}
BST* searchNode(BST *ptr,int n)
{
  if(ptr)
  {
     if(ptr->num == n)
      return ptr;
     else if( n < ptr->num){
        Parent=ptr;
       searchNode(ptr->left,n);
     }
     else if( n > ptr->num){
       Parent=ptr;
       searchNode(ptr->right,n);
     } 
     else
      return 0;
  }
  else
    return 0;
}


void insertNode(BST **ptr,int n)
{
       if(*ptr==0){
       *ptr=calloc(1,sizeof(BST));
		(*ptr)->num=n;
       }
       else if( n < (*ptr)->num)
         insertNode(&((*ptr)->left),n);
	   else if( n >  (*ptr)->num)
	     insertNode(&((*ptr)->right),n);
	   else
           printf("Duplicate not allowed\n");
}

void inOrder(BST *ptr)
{
   if(ptr){
	 inOrder(ptr->left);   
     printf("%d ",ptr->num);
     inOrder(ptr->right);
   }
}

void preOrder(BST *ptr)
{
   if(ptr){
     printf("%d ",ptr->num);
	 preOrder(ptr->left);   
     preOrder(ptr->right);
   }
}
void postOrder(BST *ptr)
{
   if(ptr){
     postOrder(ptr->left);   
     postOrder(ptr->right);
   	 printf("%d ",ptr->num);
   }
}
















