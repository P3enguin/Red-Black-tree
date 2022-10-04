#include <iostream>
#include <string>
#include <unistd.h>

# define RED   1
# define BLACK 0
# define LEFT  0
# define RIGHT 1
# define COUNT 10

typedef struct s_tree node;

struct s_tree{

	node *parent;
	node *left;
	node *right;
	int data;
	bool color;
}; 


class RBtree 
{
	public :
		RBtree();
		node*   createNode(int data);
		void    addToTree(node *n);
		void    insert(int data); // int for the moment 
		void	leftRotation(node *p);
		void	rightRotation(node *p);
		void	printTree();
		void	printTreeUtil(node *root,int space);
	private :
		node *root;

};