// HashSet.hpp

#ifndef HASHSET_HPP
#define HASHSET_HPP
 
#include <functional>
#include "Set.hpp"
 
 
 
template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
   // The default capacity of the HashSet before anything has been
   // added to it.
   static constexpr unsigned int DEFAULT_CAPACITY = 10;
 
   // A HashFunction is a function that takes a reference to a const
   // ElementType and returns an unsigned int.
   using HashFunction = std::function<unsigned int(const ElementType&)>;
 
public:
   // Initializes a HashSet to be empty, so that it will use the given
   // hash function whenever it needs to hash an element.
   explicit HashSet(HashFunction hashFunction);
 
   // Cleans up the HashSet so that it leaks no memory.
   ~HashSet() noexcept override;
 
   // Initializes a new HashSet to be a copy of an existing one.
   HashSet(const HashSet& s);
 
   // Initializes a new HashSet whose contents are moved from an
   // expiring one.
   HashSet(HashSet&& s) noexcept;
 
   // Assigns an existing HashSet into another.
   HashSet& operator=(const HashSet& s);
 
   // Assigns an expiring HashSet into another.
   HashSet& operator=(HashSet&& s) noexcept;
 
 
   // isImplemented() should be modified to return true if you've
   // decided to implement a HashSet, false otherwise.
   bool isImplemented() const noexcept override;
 
 
   // add() adds an element to the set.  If the element is already in the set,
   // this function has no effect.  This function triggers a resizing of the
   // array when the ratio of size to capacity would exceed 0.8, in which case
   // the new capacity should be determined by this formula:
   //
   //     capacity * 2 + 1
   //
   // In the case where the array is resized, this function runs in linear
   // time (with respect to the number of elements, assuming a good hash
   // function); otherwise, it runs in constant time (again, assuming a good
   // hash function).  The amortized running time is also constant.
   void add(const ElementType& element) override;
 
 
   // contains() returns true if the given element is already in the set,
   // false otherwise.  This function runs in constant time (with respect
   // to the number of elements, assuming a good hash function).
   bool contains(const ElementType& element) const override;
 
 
   // size() returns the number of elements in the set.
   unsigned int size() const noexcept override;
 
 
   // elementsAtIndex() returns the number of elements that hashed to a
   // particular index in the array.  If the index is out of the boundaries
   // of the array, this function returns 0.
   unsigned int elementsAtIndex(unsigned int index) const;
 
 
   // isElementAtIndex() returns true if the given element hashed to a
   // particular index in the array, false otherwise.  If the index is
   // out of the boundaries of the array, this functions returns false.
   bool isElementAtIndex(const ElementType& element, unsigned int index) const;
   void initializeTable();
   void rehash(const ElementType& element);
 
 
private:
 
 struct Node
   {
       ElementType element;
       Node* next = nullptr;
      
   };
   HashFunction hashFunction;
 
   unsigned int cap;
   unsigned int sz;
   Node** setHash;
 
 
    // You'll no doubt want to add member variables and "helper" member
   // functions here.
};
 
 
 
namespace impl_
{
   template <typename ElementType>
   unsigned int HashSet__undefinedHashFunction(const ElementType& element)
   {
       return 0;
   }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
   : hashFunction{hashFunction},cap{DEFAULT_CAPACITY},sz{0}
{

   setHash = new Node*[cap];
   initializeTable();

}


template <typename ElementType>
void HashSet<ElementType>::initializeTable()
{
   for (unsigned int i=0; i < cap; i++)
    {
        setHash[i] = nullptr;
    }
 
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{

     for (int i = 0 ; i<cap; i++)
    {
       Node *current = setHash[i];
       Node *prev = nullptr;
       while (current != nullptr)
       {
           prev = current->next;
           delete current;
           current = prev;
       }
   }
   delete[] setHash;

}



template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
   : hashFunction{s.hashFunction},cap{s.cap},sz{s.sz}
{


   setHash = new Node*[cap];
   int i = 0;
   Node* current = nullptr;
   Node* temp = current;
   while (i < cap)
   {
       temp = s.setHash[i];
       setHash[i] = nullptr;
 
       while (temp != nullptr)
       {
           setHash[i] = nullptr;
 
           setHash[i] = new Node{temp->element, setHash[i]};
           temp= current->next;
       }
       i++;
   }
 
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
   : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>},cap{s.cap},sz{s.sz}
{
 
   s.cap = 0;
   s.sz = 0;
   setHash = s.setHash;
   s.setHash = nullptr;
  
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        int a = 0;

        while (a < cap)
        {
            Node *current = setHash[a];
            Node *prev = nullptr;
            while (current != nullptr)
            {
                prev = current->next;
                delete current;
                current = prev;
            }
            a++;
        }

        cap = s.cap;
        sz = s.sz;
        setHash= new Node*[cap];

        for (int i = 0; i < cap; i++)
        {
            setHash[i] = nullptr;
            Node* curr = s.setHash[i];

            while (curr != nullptr)
            {
                setHash[i] = new Node{curr->element, setHash[i]};
                curr = curr->next;
            }      
        }

    }
   return *this;
}



template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
   unsigned int temp = sz;
   sz = s.sz;
   s.sz = temp;
 
   unsigned int tempTwo = cap;
   cap = s.cap;
   s.cap = tempTwo;
 
   Node** tempThird= setHash;
   setHash = s.setHash;
   s.setHash = tempThird;
 
   return *this;
}



template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
   return true;
}


template <typename ElementType>
void HashSet<ElementType>::rehash(const ElementType& element)
{
            int newCap = ((cap*2)+1);
            Node** newTable = new Node*[newCap];

            for (int i = 0; i< newCap; i++)
            {
                newTable[i] = nullptr;
            }

            int a = 0;
            while (a<cap)
                {
                    Node* prevElement = setHash[a];

                    while(prevElement != nullptr)
                    {
                        int newkeyIndex = hashFunction(prevElement->element) % newCap;
                        newTable[newkeyIndex] = new Node{prevElement->element,newTable[newkeyIndex]};
                        prevElement = prevElement->next;
                    }
                    a++;
                }

            setHash = newTable;
            cap = newCap;

}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    if (contains(element) == false)
    {
        int keyIndex = hashFunction(element) % cap;
        Node* curr = setHash[keyIndex];
        if (curr != nullptr)
        {
            setHash[keyIndex] = new Node{element, setHash[keyIndex]};
        }
        else
        {
            setHash[keyIndex] = new Node{element, nullptr};
        }

        if ((double(sz) / cap) > 0.8)
        {
                rehash(element);
        }

        sz++;
    }
}



template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
   int keyIndex = hashFunction(element) % cap;
   Node *current = setHash[keyIndex];
 
   while (current != nullptr)
   {
       if (current->element == element)
       {
           return true;
       }
       current = current->next;
   }
   return false;
}


 
template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
   return sz;
}
 


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
   if (index <= cap)
   {
       int val = 0;
       Node* current = nullptr;
       Node* temp = current;
       temp = setHash[index];
       while (temp != nullptr)
       {
           temp = temp->next;
           val++;
       }
       return val;
   }
  
   else
   {
       return 0;
   }
 
}



template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{

 if (index <= cap)
   {
       Node* current = nullptr;
       Node* temp = current;
       temp = setHash[index];
       while (temp != nullptr)
       {
           if (temp->element == element)
           {
               return true;
           }
           temp = temp->next;
       }
 
       return false;
   }
 
   else
   {
       return false;
 
   }
}
 


#endif // HASHSET_HPP


