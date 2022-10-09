#include "red-blackTree.hpp"

int main()
{
    RBtree t;
    node *tmp;


    t.insert(11);
    t.insert(2);
    t.insert(14);
    t.insert(15);
    t.insert(1);
    t.insert(7);
    t.insert(5);
    t.insert(8);
    t.insert(13);
    t.insert(99);
    t.insert(6);
    // tmp = t.predecessor(11);
    // if (!tmp)
    //     std::cout << "Errror " << std::endl;
    // else
    //     std::cout << "Successor :" <<  tmp->data << std::endl;
    t.Delete(8);
    t.Delete(6);
    t.printTree();
    //t.freeTree(t.getRoot());
 
}