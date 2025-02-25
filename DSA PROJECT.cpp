#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct wd
{
	char word[100],meaning[100];
};
struct spdict
{
	struct wd w;
	struct spdict *left,*right;
};
struct spdict *newdict(struct wd w)
{
	struct spdict *node=(struct spdict*)malloc(sizeof(struct spdict));
	strcpy(node->w.word,w.word);
	strcpy(node->w.meaning,w.meaning);
	node->left=NULL;
	node->right=NULL;
	return node;
}
struct spdict *rightrotate(struct spdict *a)
{
	struct spdict *b=a->left;
	a->left=b->right;
	b->right=a;
	return b;
}
struct spdict *leftrotate(struct spdict *a)
{
	struct spdict *b=a->right;
	a->right=b->left;
	b->left=a;
	return b;
}
int compare(char a[],char b[])
{
	int i,j,c;
    for(i=0,j=0 ; a[i]!='\0' && b[j]!='\0' ; i++,j++)
	{
       if(a[i]>b[j])
		{
        	c=1;
        	break;
    	}
    	else if(b[j]>a[i])
		{
        	c=-1;
    		break;
        }
		else
        	c=0;
    }
    if(c==1)
       return 1;
    else if(c==-1)
        return -1;
    else
        return 0;
}
struct spdict *splay(struct spdict *root,struct wd w)
{
	if(root==NULL||compare(root->w.word,w.word)==0)
	{
		return root;
	}
	if(compare(root->w.word,w.word)==1)
	{
		if(root->left==NULL)
		{
			return root;
		}
		if(compare(root->left->w.word,w.word)==1)
		{
			root->left->left = splay(root->left->left,w);
			root = rightrotate(root);
		}
		else if(compare(root->left->w.word,w.word)==-1)
		{
			root->left->right = splay(root->left->right,w);
			if (root->left->right != NULL)
			{
				root->left = leftrotate(root->left);		
			}
		}
		return (root->left == NULL)? root: rightrotate(root);
	}
	else
	{
		if (root->right == NULL)
		{
			return root;
		}
		if(compare(root->right->w.word,w.word)==1)
		{
			root->right->left = splay(root->right->left,w);
			if (root->right->left != NULL)
			{
				root->right = rightrotate(root->right);
			}		
		}
		else if(compare(root->right->w.word,w.word)==-1)
		{
			root->right->right = splay(root->right->right,w);
            root = leftrotate(root);	
		}
		return (root->right == NULL)? root: leftrotate(root);
	}
}
struct spdict *accept(struct spdict *root,struct wd w)
{
	if (root == NULL)
	{
		printf("Word Inserted\n");
		return newdict(w);
	}
	root = splay(root, w);
	if(compare(root->w.word,w.word)==0)
	{
		printf("Word already present\n");
		return root;
	}
	struct spdict *newnode= newdict(w);
	if(compare(root->w.word,w.word)==1)
	{
		newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
	}
	else 
	{
		newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
	}
	printf("Word Inserted\n");
	return newnode;
}
struct spdict *search(struct spdict *root)
{
	spdict *t;
	wd p;
	printf("Enter word who's meaning is to be known: ");
	scanf("%s",&p.word);
	t=splay(root,p);
	printf("Word:%s  Meaning:%s\n",t->w.word,t->w.meaning);
	return t;
}
struct spdict *remove(struct spdict *root)
{
	wd p;
	printf("Enter word to be deleted: ");
	scanf("%s",&p.word);
	struct spdict *t;
	if(root==NULL)
	{
		printf("Dictionary Empty\n");
		return NULL;
	}
	root=splay(root,p);
	if(strcmp(p.word,root->w.word)==0)
	{
		if(!root->left)
		{
			t=root;
			root=root->right;
		}
		else
		{
			t=root;
			root=splay(root->left,p);
			root->right=t->right;
		}
		free(t);
		printf("Word deleted\n");
		return root;
	}
	else if(strcmp(root->w.word,p.word)==-1);
	{
		printf("Word not Found\n");
		return root;
	}
}
void prdisplay(struct spdict *root)
{
	if(root!=NULL)
	{
		printf("Word:%s  Meaning:%s\n",root->w.word,root->w.meaning);
		prdisplay(root->left);
		prdisplay(root->right);
	}
}
int main()
{
	int c;
	struct spdict *root=NULL;
	wd a;
	while(c!=5)
	{
		printf("\n1.Insert\n2.Display\n3.Delete\n4.Search\n5.Exit\n");
		printf("Enter Choice: ");
		scanf("%d",&c);
		if(c==1)
		{
			printf("Enter Word: ");
			scanf("%s",&a.word);
			printf("Enter Meaning: ");
			scanf("%s",&a.meaning);
			root=accept(root,a);
		}
		else if(c==2)
		{
			if(root==0)
			{
				printf("Dictionary Empty");
			}
			else
			{
				printf("Dictionary displayed in pre order:\n");
				prdisplay(root);
			}
		}
		else if(c==3)
		{
			root=remove(root);	
		}	
		else if(c==4)
		{
			root=search(root);	
		}
		else if(c==5)
		{
			exit(0);
		}
	}
}


