/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red-blackree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:13:01 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/04 11:04:18 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <unistd.h>

#define LEFT    0
#define RIGHT   1
#define COUNT   10
#define BLACK   0
#define RED     1

typedef struct s_tree{

	struct s_tree *parent;
	struct s_tree *left;
	struct s_tree *right;
	int data;
	bool color;
} tree;


tree *CreateNode(int data)
{
	tree *node;

	node = new tree;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->data = data;
	node->color = RED;
	return node;
}

void print2DUtil(tree *root, int space)
{
   
	if (root == NULL)
		return;
 
  
	space += COUNT;
 
	print2DUtil(root->right, space);
 
	std::cout<<std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout<<" ";
	std::cout<<root->data << " " ;
	std::cout << root->color<<"\n";
	print2DUtil(root->left, space);
}

void print2D(tree *root)
{
	print2DUtil(root, 0);
}

void leftRotation(tree **root,tree *t)
{
	tree *tmp;

	tmp = t->right;
	t->right = tmp->left;
	if (tmp->left)
		tmp->left->parent = t;
	if (t->parent)
	{   
		tmp->parent = t->parent;
		if (t->parent->left == t)
			t->parent->left = tmp;
		else
			t->parent->right = tmp;
	}
	else
	{
		tmp->parent = NULL;
		*root = tmp;
	}
	t->parent = tmp;
	tmp->left = t;
}

void	rightRotation(tree **root,tree *t)
{
	tree *tmp;

	tmp = t->left;
	t->left = tmp->right;
	if (tmp->right)
		tmp->right->parent = t;
	if (t->parent)
	{
		tmp->parent = t->parent;
		if (t->parent->left == t)
			t->parent->left = tmp;
		else
			t->parent->right = tmp;
	}
	else
	{
		tmp->parent = NULL;
		*root = tmp;
	}
	t->parent = tmp;
	tmp->right = t;

}

void addToTree(tree **root,tree *node)
{
	tree *tmp;

	tmp = *root;
	if (!tmp)
	{
		node->color = BLACK;
		(*root) = node;
		return ;
	}

	while (tmp)
	{
		if (node->data < tmp->data)
		{
		   
			if (tmp->left == NULL)
			{
				node->parent = tmp;
				tmp->left = node;
				break;
			}
			else 
				tmp = tmp->left;
		}
		else
		{
			if (tmp->right == NULL)
			{
				node->parent = tmp;
				tmp->right = node;
				break;
			}
			else
				tmp = tmp->right;
		}
	}  
}

void	insert(tree **root,tree *node)
{
	addToTree(root,node);

	// if (node->data == 6)
	// {
	// 	rightRotation(root,node->parent->parent);
	// 	std::cout << "root now " << (*root)->data << std::endl;
	// 	if ((*root)->parent)
	// 		std::cout << "root parent " << (*root)->parent->data << std::endl;
	// 	if ((*root)->left)
	// 		std::cout << "Left child parent " << (*root)->left->parent->data << std::endl;
	// 	if ((*root)->right)
	// 		std::cout << "right child parent " << (*root)->right->parent->data << std::endl;
	// 	//  std::cout << "left left child parent " << (*root)->left->left->parent->data << std::endl;
	// 	//  std::cout << "left right  child parent " << (*root)->left->right->parent->data << std::endl;

	// }

	//sleep(1);
	tree *u; // uncle 
	tree *p; // parent
	tree *n; // node

	bool dir; // direction of the node acording to the grandPa

	n = node;
	while (n && n != *root)
	{
		p = n->parent;

		// parent color is black , No violation of the rules 
		if (p->color == BLACK)
			return;
		if (p == *root && p->color == RED)
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
					n = p;
					leftRotation(root,p);
				}
				else
				{
					p->color = BLACK;
					p->parent->color = RED;
					rightRotation(root,p->parent);
				}
	
			}
			else
			{
				if (n == p->parent->right->left)
				{
					n = p;
					rightRotation(root,p);
				}
				else
				{
					p->color = BLACK;
					p->parent->color = RED;
					leftRotation(root,p->parent);
				}
			}
		}
		// moving to the Grandparent node and re-checking 
	}
	if ((*root)->color == RED)
		(*root)->color = BLACK;
};

int main()
{
	tree *root;

	root = new tree;
	root = NULL;

	insert(&root,CreateNode(11));
	insert(&root,CreateNode(2));
	insert(&root,CreateNode(14));
	 insert(&root,CreateNode(15));
	insert(&root,CreateNode(8));
	
	insert(&root,CreateNode(4));
	insert(&root,CreateNode(100));
	//rightRotation(&(root->left));
	//leftRotation(&root);
  	print2D(root);

}