#include "red-blackTree.hpp"

RBtree::RBtree()
{
    this->root = new node;
    this->root = NULL; 
}

node* RBtree::createNode(int data)
{
    node *n;

	n = new node;
	n->parent = NULL;
	n->left = NULL;
	n->right = NULL;
	n->data = data;
	n->color = RED;
	return n;

}

void RBtree::addToTree(node *n)
{
	node *tmp;

	tmp = root;
	if (!tmp)
	{
		n->color = BLACK;
		this->root = n;
		return ;
	}

	while (tmp)
	{
		if (n->data < tmp->data)
		{
		   
			if (tmp->left == NULL)
			{
				n->parent = tmp;
				tmp->left = n;
				break;
			}
			else 
				tmp = tmp->left;
		}
		else
		{
			if (tmp->right == NULL)
			{
				n->parent = tmp;
				tmp->right = n;
				break;
			}
			else
				tmp = tmp->right;
		}
	}  

}

void RBtree::leftRotation(node *p)
{
	node *tmp;

	tmp = p->right;
	p->right = tmp->left;
	if (tmp->left)
		tmp->left->parent = p;
	if (p->parent)
	{   
		tmp->parent = p->parent;
		if (p->parent->left == p)
			p->parent->left = tmp;
		else
			p->parent->right = tmp;
	}
	else
	{
		tmp->parent = NULL;
		this->root = tmp;
	}
	p->parent = tmp;
	tmp->left = p;
}

void	RBtree::rightRotation(node *p)
{
	node *tmp;

	tmp = p->left;
	p->left = tmp->right;
	if (tmp->right)
		tmp->right->parent = p;
	if (p->parent)
	{
		tmp->parent = p->parent;
		if (p->parent->left == p)
			p->parent->left = tmp;
		else
			p->parent->right = tmp;
	}
	else
	{
		tmp->parent = NULL;
		this->root = tmp;
	}
	p->parent = tmp;
	tmp->right = p;
}

void RBtree::insert(int data)
{
	node *n = createNode(data);
    addToTree(n);

	node *u; // uncle 
	node *p; // parent
	bool dir; // direction of the node acording to the grandPa

	while (n && n != this->root)
	{
		p = n->parent;

		// parent color is black , No violation of the rules 
		if (p->color == BLACK)
			return;
		if (p == this->root && p->color == RED)
		{
			p->color = BLACK;
			return ;
		}
		// now parent is red , we check the uncle of the node
		if (p->parent->left == p)
		{
			u = p->parent->right;
			dir = LEFT;
		}
		else
		{
			u = p->parent->left;
			dir = RIGHT;
		}

		// if the uncle is red , we just re-color 
		if (u && u->color == RED)
		{
			u->color = BLACK;
			p->color = BLACK;
			p->parent->color = RED;
			n = p->parent;
		}
		else
		{
			// now uncle is black we have to cases :
			// - the node is `inner` child of It grandparent 
			// - the node is `outter` child of It grandparent

			if (dir == LEFT)
			{
				if (n == p->parent->left->right)
				{
					// left-right rotation
					n = p;
					leftRotation(p);
				}
				else
				{
					p->color = BLACK;
					p->parent->color = RED;
					rightRotation(p->parent);
				}
	
			}
			else
			{
				if (n == p->parent->right->left)
				{
					// right-left rotation 
					n = p;
					rightRotation(p);
				}
				else
				{
					p->color = BLACK;
					p->parent->color = RED;
					leftRotation(p->parent);
				}
			}
		}
		// moving to the Grandparent node and re-checking 
	}
	if ((this->root)->color == RED)
		(this->root)->color = BLACK;
}


void RBtree::printTreeUtil(node *root, int space)
{
   
	if (root == NULL)
		return;
  
	space += COUNT;
 
	printTreeUtil(root->right, space);
 
	std::cout<<std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout<<" ";
	std::cout<<root->data << " " ;
	std::cout << root->color<<"\n";
	printTreeUtil(root->left, space);
}


void RBtree::printTree()
{
	printTreeUtil(this->root, 0);
}