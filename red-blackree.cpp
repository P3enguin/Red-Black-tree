/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red-blackree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <ybensell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:13:01 by ybensell          #+#    #+#             */
/*   Updated: 2022/10/03 10:22:43 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

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
    std::cout<<root->data<<"\n";
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
        if (t->parent->left == t)
			t->parent->left = tmp;
        else
            t->parent->right = tmp;
    }
    else
        *root = tmp;
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
        if (t->parent->left == t)
            t->parent->left = tmp;
        else
            t->parent->right = tmp;
    }
    else
        *root = tmp;
    t->parent = tmp;
    tmp->right = t;
}

void checkInsertion(tree **root,tree *node,tree *p,bool dir)
{


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
    bool dir;
    while (tmp)
    {
        if (node->data < tmp->data)
        {
           
            if (tmp->left == NULL)
            {
                node->parent = tmp;
                tmp->left = node;
				checkInsertion(root,node,tmp,dir);
                break;
            }
            else 
            {
                dir = LEFT;
                tmp = tmp->left;
            }
        }
        else
        {
            if (tmp->right == NULL)
            {
                node->parent = tmp;
                tmp->right = node;
				checkInsertion(root,node,tmp,dir);
                break;
            }
            else
            {
				dir = RIGHT;
				tmp = tmp->right;
            }
        }
    }  
}


int main()
{
    tree *root;

    root = new tree;
    root = NULL;

    addToTree(&root,CreateNode(5));
    addToTree(&root,CreateNode(7));
    addToTree(&root,CreateNode(8));

    addToTree(&root,CreateNode(9));
    // addToTree(&root,CreateNode(7));
    // addToTree(&root,CreateNode(1));
    // addToTree(&root,CreateNode(0));
    //rightRotation(&(root->left));
    //leftRotation(&root);
  	 print2D(root);

}