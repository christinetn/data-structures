// DoublyLinkedList.hpp


#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "EmptyException.hpp"
#include "IteratorException.hpp"



template <typename ValueType>
class DoublyLinkedList
{
    // The forward declarations of these classes allows us to establish
    // that they exist, but delay displaying all of the details until
    // later in the file.
    //
    // (This is generally a good style, with the most important details
    // appearing earlier in the class declaration.  That's the same
    // reason why we're implementing the bodies of the member functions
    // outside of the class declaration.)
public:
    class Iterator;
    class ConstIterator;


private:
    struct Node;


public:
    // Initializes this list to be empty.
    DoublyLinkedList() noexcept;

    // Initializes this list as a copy of an existing one.
    DoublyLinkedList(const DoublyLinkedList& list);

    // Initializes this list from an expiring one.
    DoublyLinkedList(DoublyLinkedList&& list) noexcept;


    // Destroys the contents of this list.
    virtual ~DoublyLinkedList() noexcept;


    // Replaces the contents of this list with a copy of the contents
    // of an existing one.
    DoublyLinkedList& operator=(const DoublyLinkedList& list);

    // Replaces the contents of this list with the contents of an
    // expiring one.
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;


    // addToStart() adds a value to the start of the list, meaning that
    // it will now be the first value, with all subsequent elements still
    // being in the list (after the new value) in the same order.
    void addToStart(const ValueType& value);

    // addToEnd() adds a value to the end of the list, meaning that
    // it will now be the last value, with all subsequent elements still
    // being in the list (before the new value) in the same order.
    void addToEnd(const ValueType& value);


    // removeFromStart() removes a value from the start of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the first one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromStart();

    // removeFromEnd() removes a value from the end of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the last one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromEnd();


    // first() returns the value at the start of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& first() const;
    ValueType& first();


    // last() returns the value at the end of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& last() const;
    ValueType& last();


    // isEmpty() returns true if the list has no values in it, false
    // otherwise.
    bool isEmpty() const noexcept;


    // size() returns the number of values in the list.
    unsigned int size() const noexcept;



    // There are two kinds of iterators supported: Iterators and
    // ConstIterators.  They have similar characteristics; they both
    // allow you to see what values are in the list and move back and
    // forth between them.  The difference is that ConstIterators allow
    // you to see the elements but not modify them, while Iterators also
    // support modification of the list (both by modifying the elements
    // directly, and also by inserting or removing values at arbitrary
    // locations).
    //
    // At any given time, an iterator refers to a value in the list.
    // There are also two additional places it can refer: "past start"
    // and "past end", which are the positions directly before the
    // first value and directly after the last one, respectively.
    // Except with respect to those boundaries, they can be moved
    // both forward and backward.
    //
    // Note, too, that the reason we have a ConstIterator class instead
    // of just saying "const Iterator" is because a "const Iterator"
    // is something different: It's an Iterator object that you can't
    // modify (i.e., you can't move it around).  What a ConstIterator
    // holds constant isn't the iterator; it's the list that's protected
    // by it.


    // iterator() creates a new Iterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    Iterator iterator();


    // constIterator() creates a new ConstIterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    ConstIterator constIterator() const;


public:
    // The IteratorBase class is the base class for our two kinds of
    // iterators.  Because there are so many similarities between them,
    // we write those similarities in a base class, then inherit from
    // that base class to specify only the differences.
    class IteratorBase
    {
    public:
        // Initializes a newly-constructed IteratorBase to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        IteratorBase(const DoublyLinkedList& list) noexcept;


        // moveToNext() moves this iterator forward to the next value in
        // the list.  If the iterator is refrering to the last value, it
        // moves to the "past end" position.  If it is already at the
        // "past end" position, an IteratorException will be thrown.
        void moveToNext();


        // moveToPrevious() moves this iterator backward to the previous
        // value in the list.  If the iterator is refrering to the first
        // value, it moves to the "past start" position.  If it is already
        // at the "past start" position, an IteratorException will be thrown.
        void moveToPrevious();


        // isPastStart() returns true if this iterator is in the "past
        // start" position, false otherwise.
        bool isPastStart() const noexcept;


        // isPastEnd() returns true if this iterator is in the "past end"
        // position, false otherwise.
        bool isPastEnd() const noexcept;
    
    protected:
        // You may want protected member variables and member functions,
        // which will be accessible to the derived classes.
        unsigned int posValue;
        Node* pos;
        const DoublyLinkedList& dlptr;

    };


    class ConstIterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed ConstIterator to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        ConstIterator(const DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        const ValueType& value() const;

    private:
        // You may want private member variables and member functions.
        const DoublyLinkedList& dlptr;
    };


    class Iterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed Iterator to operate on the
        // given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        Iterator(DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        ValueType& value() const;


        // insertBefore() inserts a new value into the list before
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past start" position, an IteratorException
        // is thrown.
        void insertBefore(const ValueType& value);


        // insertAfter() inserts a new value into the list after
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past end" position, an IteratorException
        // is thrown.
        void insertAfter(const ValueType& value);


        // remove() removes the value to which this iterator refers,
        // moving the iterator to refer to either the value after it
        // (if moveToNextAfterward is true) or before it (if
        // moveToNextAfterward is false).  If the iterator is in the
        // "past start" or "past end" position, an IteratorException
        // is thrown.
        void remove(bool moveToNextAfterward = true);

    private:
        // You may want private member variables and member functions.
        DoublyLinkedList& dlptr;

    };


private:
    // A structure that contains the vital parts of a Node in a
    // doubly-linked list, the value and two pointers: one pointing
    // to the previous node (or nullptr if there isn't one) and
    // one pointing to the next node (or nullptr if there isn't
    // one).
    struct Node
    {
        ValueType value;
        Node* prev;
        Node* next;
    };


    // You can feel free to add private member variables and member
    // functions here; there's a pretty good chance you'll need some.
    unsigned int dlsize;
    Node* head;
    Node* tail;
};



template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList() noexcept
    :dlsize{0},head{nullptr}, tail{nullptr}
{
}



template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& list)
    : dlsize{0},head{nullptr},tail{nullptr}
{
    
    
    if (list.head == nullptr)
    {
        head = nullptr;
        dlsize = 0;
        tail = nullptr;
    }

    else
    {
        Node* newNode = new Node{list.head->value,nullptr,list.head->next};
        head = newNode;
        Node* temp = head;
        Node* current = list.head->next;
        dlsize ++;

        while(current != nullptr)
        {
            Node* newNodeB = new Node{current->value,temp,temp->next};
            current = current->next;
            temp->next = newNodeB;
            temp = temp->next;
            dlsize++;
        }
        tail = temp;
        tail->next = nullptr;

    }
    
    
}



template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& list) noexcept
    :dlsize{0}, head{nullptr}, tail{nullptr}
{
    head = list.head;
    tail = list.tail;

    list.head = nullptr;
    list.tail = nullptr;

    int tempSize = list.dlsize;
    list.dlsize = dlsize;
    dlsize = tempSize;

}


template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList() noexcept
{
    Node* temp = head;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }

    
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(const DoublyLinkedList& list)
{
    if (this != &list)
    {
        DoublyLinkedList<ValueType> copy_list(list);

        dlsize = list.dlsize;


        Node* tempH = copy_list.head;
        copy_list.head = head;
        head = tempH;

        Node* tempT= copy_list.tail;
        copy_list.tail = tail;
        tail = tempT;

      
    }
    return *this;
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
    if (this != &list)
    {
        Node* h = head;
        Node* t = tail;

        head = list.head;
        tail = list.tail;

        list.head = h;
        list.tail = t;

        int tempSize = list.dlsize;
        list.dlsize = dlsize;
        dlsize = tempSize;
    }
    return *this;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToStart(const ValueType& value)
{

    if (dlsize == 0)
    {
        Node* newNode = new Node{value,nullptr,nullptr};
        head = newNode;
        tail = newNode;
    }

    else
    {
        Node* newNode = new Node{value,nullptr,nullptr};
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    dlsize++;

    


}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToEnd(const ValueType& value)
{
     if (dlsize == 0)
    {
        Node* newNode = new Node{value,nullptr,nullptr};
        head = newNode;
        tail = newNode;
    }

    else
    {
        Node* newNode = new Node{value,nullptr,nullptr};
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    dlsize++;

}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromStart()
{

    if (dlsize == 0)
    {
        throw EmptyException{};
    }
    //if theres not one node
    else if (head != tail)
    {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
    else{
        delete head;
        head = nullptr;
        tail = nullptr;

    }
    dlsize --;
    

}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
    if (dlsize == 0)
    {
        throw EmptyException();
    }
    //if theres one node
    else if (head != tail)
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
    else{
        head = nullptr;
        delete tail;
        tail = nullptr;

    }
    dlsize --;
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::first() const
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

    if (dlsize == 0)
    {
        throw EmptyException();
    }
    return head->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::first()
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.


   if (dlsize == 0)
    {
        throw EmptyException();
    }
    return head->value;
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::last() const
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

    //return (new Node)->value;
    if (dlsize == 0)
    {
        throw EmptyException();
    }
    return tail->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::last()
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

    if (dlsize == 0)
    {
        throw EmptyException();
    }
    return tail->value;
}


template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
    return dlsize;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::isEmpty() const noexcept
{
    
    
    if (dlsize == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
    return Iterator{*this};
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
    return ConstIterator{*this};
}

// Initializes a newly-constructed Iterator to operate on the
        // given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".

template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
    : dlptr{list}
{
    
    pos = list.head;
    if (list.dlsize != 0)
    {
        posValue = 1;
    }

  
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
    
    
    if (isPastEnd())
    {
        throw IteratorException{};
    }
    
    if (posValue < dlptr.dlsize)
    {
        pos = pos->next;
      
    }
    
    posValue ++;
    
    
    

}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
    if (isPastStart())
    {
        throw IteratorException{};
    }

    if (posValue > 1 && posValue <= dlptr.dlsize)
    {
        pos = pos->prev;
    }
    posValue --;



}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastStart() const noexcept
{
    
    if (posValue >= 1 && dlptr.dlsize > 0)
    {
         return false;
    }

    return true;
    
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastEnd() const noexcept
{


    if (posValue <= dlptr.dlsize && dlptr.dlsize > 0)
    {
        return false;
    }
    return true;
    

}


template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
    : IteratorBase{list}, dlptr{list}
{
}

template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::ConstIterator::value() const
{
    // Note that this is an awful thing I'm doing here, but I needed
    // something that would make this code compile.  You're definitely
    // going to want to replace this with something else before you
    // ever call this member function and expect it to work.  This
    // version *will* leak memory and *will* return an undefined value.

    if (IteratorBase::isPastStart() || IteratorBase::isPastEnd())
    {
        throw IteratorException{};
    }

    return IteratorBase::pos->value;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
    : IteratorBase{list}, dlptr{list}
{
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::Iterator::value() const
{
    

    if (IteratorBase::isPastStart() || IteratorBase::isPastEnd())
    {
        throw IteratorException{};
    }

    return IteratorBase::pos->value;
}



template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
    Node* newNode = new Node{value,nullptr,nullptr};
    if (IteratorBase::isPastStart())
    {
        throw IteratorException{};
    }


    if (IteratorBase::posValue == 1)
    {
        dlptr.addToStart(value);
    }
    else
    {
        newNode->prev = IteratorBase::pos->prev;
        IteratorBase::pos->prev = newNode;
        newNode->next = IteratorBase::pos;
        if (newNode->prev != nullptr)
        {
            newNode->prev->next = newNode;
        }

    }
    dlptr.dlsize ++;

}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
    Node* newNode = new Node{value,nullptr,nullptr};
    if (IteratorBase::isPastEnd())
    {
        throw IteratorException{};
    }

    
    if (IteratorBase::posValue == dlptr.dlsize)
    {
        dlptr.addToEnd(value);
    }
    else
    {
        newNode->next = IteratorBase::pos->next;
        IteratorBase::pos->next = newNode;
        newNode->prev = IteratorBase::pos;

        if (newNode->next != nullptr)
        {
       
            newNode->next->prev = newNode;
        }
    

    }
    dlptr.dlsize ++;
}



template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
    if (IteratorBase::isPastStart() || IteratorBase::isPastEnd())
    {
        throw IteratorException{};
    }

    if (IteratorBase::posValue == 1)
    {
        dlptr.removeFromStart();
    }
    else if (IteratorBase::posValue == dlptr.dlsize)
    {
        dlptr.removeFromEnd();
    }
    else //remove from middle 
    { 
        
        if (moveToNextAfterward)
        {
            IteratorBase::pos->prev->next = IteratorBase::pos->next;
            Node* temp = IteratorBase::pos;
            IteratorBase::pos = IteratorBase::pos->next;
            delete temp;
        }
        else{
            IteratorBase::pos->prev->next = IteratorBase::pos->next;
            Node* temp = IteratorBase::pos;
            IteratorBase::pos = IteratorBase::pos->prev;
            delete temp;

        }

        dlptr.dlsize --;
        
    }

}



#endif

