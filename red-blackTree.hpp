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
		void    insert(int data);
		void	Delete(int data);
		// int for the moment 
		void	printTree();
		node*	search(int data);
		node*	predecessor(int data);
		node*	successor(int data);

	private :
		node*   createNode(int data);

		void    addToTree(node *n);
		void	rebalance(node *n);
		void	leftRotation(node *p);
		void	rightRotation(node *p);
		node*	removeNode(node *n);

		void	printTreeUtil(node *root,int space);

		node *root;

};