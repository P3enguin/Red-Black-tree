#include "red-blackTree.hpp"

/* 
Red-Black tree Properties :
	- each node is either black or red
	- Every path from a node to its leafs (NULL) should contain the same number of black nodes 
	- the root is always black
	- the leafs are considered black (NULL)
	- there should be no two consecutive red nodes
	- New insertions are always red
*/

RBtree::RBtree()
{
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

node*	RBtree::search(int data)
{
	node *t;

	t = this->root;
	while (t)
	{
		if (t->data == data)
			return t;
		else if (t->data  < data)
			t = t->right;
		else if (t->data > data)
			t = t->left;
	}
	return NULL;
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

	node *u;  // uncle 
	node *p;  // parent of the current node
	bool dir; // direction of the node acording to the grandPa

	while (n && n != this->root)
	{
		p = n->parent;

		// parent color is black , No violation of the rules 
		if (p->color == BLACK)
			return;

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
			// We move the node to the grandParent since Its red Now and we re-check
			n = p->parent;
		}
		else
		{
			/* 
				now uncle is black we have two cases :
			 		- the node is `inner` child of It grandparent 
					- the node is `outter` child of It grandparent
			*/
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

	}
	if ((this->root)->color == RED)
		(this->root)->color = BLACK;
}

node *	RBtree::predecessor(int data)
{
	node *t,*pred;

	// /* Predeccessor  of a node is the node with the greatest key 
	// 	smaller than the key of the current n in Its left subtree

	// 	- if the node doesnt have a left subtree , the successor is
	// 		one of Its ancestor 
	t = this->root;
	pred = NULL;
	while (t)
	{
		if (t->data < data)
		{
			pred = t;
			t = t->right;
		}
		else if (t->data > data)
			t = t->left;
		else if (t->data == data)
		{
			if (t->left)
			{
				t = t->left;
				while (t)
				{
					if (t->right)
						t = t->right;
					else if (t->left)
						t = t->left;
					else
						return t;
				}
			}
			else
				break;
		}
	}
	
	return pred;
}

node*	RBtree::successor(int data)
{
	node *t,*succ;

	/* Successor of a node is the node with the smallest key 
		greater than the key of the current n in Its right subtree

		- if the node doesnt have a right subtree , the successor is
			one of Its ancestor 

	*/
	t = this->root;
	succ = NULL;
	while (t)
	{
		if (t->data < data)
			t = t->right;
		else if (t->data > data)
		{
			succ = t;
			t = t->left;
		}
		else if (t->data == data)
		{
			if (t->right)
			{
				t = t->right;
				while (t)
				{
					if (t->left)
						t = t->left;
					else if (t->right)
						t = t->right;
					else
						return t;
				}
			}
			else
				break;
		}
	}
	return succ;
}


void	RBtree::rebalance(node *n,node *u)
{
	/* 
		n : the node to be deleted 
		u : the node that will replace the deleted node
		s : sibling of the node
		c : close nephew 
		d : distant nephew
	*/

	node *tmp = n; /* saving the deleted node pointer to free at the end */
	node *p = n->parent;

	/* Node being replaced by Its one child */
	if (u)
	{
		u->color = BLACK;
        if (p)
        {
            if (p->left == n)
                p->left = u;
            else
                p->right = u;
        }
		u->parent = p;
	}
	/* node is leaf and black */
	else if (!u && n->color == BLACK)
	{
        
		bool dir;
		node *s,*d,*c;
	
		while (p != NULL)
		{
			if (p->left == n)
			{
				s = p->right;
				d = s->right;
				c = s->left;
				dir = LEFT;
			}
			else
			{
				s = p->left;
				d = s->left;
				c = s->right;
				dir = RIGHT;
			}
			/* case 4 :parent is red and s+c+d black */
			if (p->color == RED && 
				(s->color == BLACK && ( (d && c && 
					d->color == BLACK && c->color == BLACK)
					|| (!d && !c))))
			{
				
				p->color = BLACK;
				s->color = RED;
				break ;
			}
			/* case 2 : p+s+c+d all black */
			else if (p->color == BLACK && 
				(s->color == BLACK && ((d && c && 
					d->color  == BLACK && c->color == BLACK)
					|| (!d && !c))))
			{
				s->color = RED;
				n = p;
				p = p->parent;
				continue;
			}
			/* case 3 : sibling is red */
			else if (s->color == RED)
			{	
				
				p->color = RED;
				s->color = BLACK;
				if (dir == LEFT)
					leftRotation(p);
				else
					rightRotation(p);
				continue;
			}
			else if (s->color == BLACK)
			{
			/* case 5 : s is black & d is black */
				if (!d || (d && d->color == BLACK /*&&
					c && c->color == RED*/))
				{
					// might be an error here 	
					c->color = BLACK;
					s->color = RED;
					if (dir == RIGHT)
						leftRotation(s);
					else
						rightRotation(s);
					continue;
				}
			/* case 6 : s is black & d is RED */
				else if (d && d->color == RED)
				{
					s->color = p->color;
					d->color =  p->color = BLACK;
					if (dir == RIGHT)
						rightRotation(p);
					else
						leftRotation(p);
					break ;
				}
			}
		}
	}
	/* 	deleting the node and setting */
	/*	it parent to NULL + red leaf case */
	if (tmp->parent)
	{
		if (tmp->parent->left == tmp)
			tmp->parent->left = NULL;
		else if (tmp->parent->right == tmp)
			tmp->parent->right = NULL;
		delete tmp;
		tmp = NULL;
	}
    
	return ;
}

/* basic  binary tree deletion */ 
void	RBtree::removeNode(node *n)
{
	node *t;
	
	/*	node is a leaf	*/
	if (!n->left && !n->right)
    {
        if (n == this->root)
        {
            delete n;
            n = NULL;
            this->root = NULL;
            return ;
        }
	    rebalance(n,NULL);
    }

	/*	node has only one child */
	else if (!n->left || !n->right)
	{	
		if (n->left)
			t = n->left;
		else
			t = n->right;
        if (n == this->root)
        {       
            t->parent = NULL;
            delete n;
            n = NULL;
            this->root = t;
            return ;
        }
		rebalance(n,t);
	}

	/* node has two childs */
	else if (n->left && n->right)
	{
		t = predecessor(n->data);
		if (!t)
		 	t = successor(n->data);
		n->data = t->data;
		rebalance(t,NULL);
	}
}

void	RBtree::Delete(int data)
{
	node *tmp;
	bool dir;
	

	/* there are many cases in deletion 
		first we have to find the element we want to delete 
		then we perform a binary search deletion .
	*/
	tmp = this->root;
	while (tmp)
	{
		if (tmp->data == data)
		{
			removeNode(tmp);
			return;
		}
		else if (tmp->data > data)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
}

void	RBtree::freeTree(node *root)
{
	if (root)
	{
		if (root->left)
			freeTree(root->left);
		if (root->right)
			freeTree(root->right);
		delete root;
	}
	return ;
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

node*	RBtree::getRoot()
{
	return this->root;
}