// AVLSet.hpp


#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include "Set.hpp"



template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    ~AVLSet() noexcept override;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const noexcept;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;



private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.

    struct Node
    {
        ElementType key;
        Node* left;
        Node* right;

    };
    void deleteElements(Node* n);
    void copyElements(Node*& copyOne, Node* copyTwo);
    void preorderTraversal(Node* node, VisitFunction visited) const;
    void postorderTraversal(Node* node, VisitFunction visited) const;
    void inorderTraversal(Node* node, VisitFunction visited) const;


    Node* root;
    int treeHeight;
    int sz;

};


template <typename ElementType>
void AVLSet<ElementType>::copyElements(Node*& copyOne, Node* copyTwo)
{
    if (copyTwo != nullptr)
    {
        copyOne = new Node();
        copyOne->key = copyTwo->key;
        if (copyOne->left == nullptr && copyOne->right == nullptr)
        {
            return;
        }
        else
        {
            copyElements(copyOne->left,copyTwo->left);
            copyElements(copyOne->right,copyTwo->right);
            copyOne = nullptr;
        }
    }
    else
    {
        copyOne = nullptr;

    }



}

template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{

    sz = 0;
    treeHeight = -1;
    root = nullptr;
}


template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{

    deleteElements(root);
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
    copyElements(root,s.root);
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
    sz = 0;
    treeHeight = -1;
    root = nullptr;

    Node *temp = root;
    root = s.root;
    s.root = temp;

    
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    if (this != &s)
    {
        sz = s.sz;
        root = nullptr;

        deleteElements(root);
        copyElements(root,s.root);
    }
    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    Node *tempRoot = root;
    root = s.root;
    s.root = tempRoot;

    int tempH = treeHeight;
    treeHeight = s.treeHeight;
    s.treeHeight = tempH;

    int tempSize = sz;
    sz = s.sz;
    s.sz = tempSize;
   
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{

    Node* current = root;
    Node* temp = nullptr;
    bool addRight;

    if (current != nullptr)
    {
           while (current != nullptr)
        {
            temp = current;

            if (element == current->key)
            {
                return;
            }

            if (element < current->key)
            {
                addRight = false;
                current = current->left;

            }
            else if (element > current->key)
            {
                current = current->right;
                addRight = true;
            }

        }
        if (!(addRight))
        {
            temp->left = new Node{element, nullptr,nullptr};
            
        }
        else
        {
            temp->right = new Node{element,nullptr,nullptr};
        }
    }

    else
    {
         root = new Node{element,nullptr,nullptr};

    }
    sz++;

}

template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
    Node* current = root;
    Node* temp = current;

    while (temp!= nullptr)
    {
        if (element == temp->key)
        {
            return true;
        }

        if (element < temp->key)
        {
            temp = temp->left;  
        }
    
        else
        {
            temp = temp->right;
        }
     
    }
    return false;
 
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return sz;
}


template <typename ElementType>
int AVLSet<ElementType>::height() const noexcept
{
    return treeHeight;

}


template <typename ElementType>
void AVLSet<ElementType>::preorderTraversal(Node* node, VisitFunction visited) const
{
    if (node != nullptr)
    {
        visited(node->key);
        preorderTraversal(node->left,visited);
        preorderTraversal(node->right,visited);

    }


}

template <typename ElementType>
void AVLSet<ElementType>::inorderTraversal(Node* node, VisitFunction visited) const
{
    if (node != nullptr)
    {
        inorderTraversal(node->left,visited);
        visited(node->key);
        inorderTraversal(node->right,visited);


    }

}


template <typename ElementType>
void AVLSet<ElementType>::postorderTraversal(Node* node, VisitFunction visited) const
{
    if (node != nullptr)
    {
        postorderTraversal(node->left,visited);
        postorderTraversal(node->right,visited);
        visited(node->key);

    }

}

template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
        preorderTraversal(root,visit);


}


template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    inorderTraversal(root,visit);
}


template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    postorderTraversal(root,visit);
}

template <typename ElementType>
void AVLSet<ElementType>::deleteElements(Node* n)
{
    if (n == nullptr)
    {
        return;
    }
    if (n->left != nullptr)
    {
        deleteElements(n->left);
    }
    if (n->right != nullptr)
    {
        deleteElements(n->right);
    }
    if ( n != nullptr)
    {
        delete n;
    }

}



#endif

