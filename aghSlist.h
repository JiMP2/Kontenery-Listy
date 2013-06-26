//
//  aghSlist.h
//  Kontenery - Listy
//
//  Created by Wojtek on 5/29/13.
//  Copyright (c) 2013 Wojtek. All rights reserved.
//
#ifndef Kontenery___Listy_aghSlist_h
#define Kontenery___Listy_aghSlist_h

#include "aghContainer.h"
#include "aghNode.h"
#include "aghException.h"

template <class T>
class aghSlist : public aghContainer<T> {    
protected:
    //\brief Pointer to first element of list.
    aghNode<T> * firstElement;
    //\brief Number of elements in list.
    unsigned int elementsCount;
    
public:
    //\brief Default constructor of class.
    aghSlist(unsigned int _size = 0);
    
    //\ Default copying constructor of class.
    aghSlist(const aghContainer<T>& _source);
    //\ Destructor of class.
    ~aghSlist();
    
     //\brief Method returns element from given position.
     //\_position - Index of element.
     //\return value of element at given position.
    T& at (unsigned int _index) const;
    
    //\brief Method returns size of container.
    //\return size of container.
    unsigned int size (void) const;
    
    //\brief Method appends new element to end of container.
    //\_element - Element value.
    //\return true if operation successful
    bool insert (unsigned int _index, const T& _value);
    
    //\brief Method removes element at given position. Virual method.
    //\return true if operation successful.
    bool remove (unsigned int _index);
    
    //\brief Overload of operator=.
    //\_right Operand of overloaded operator.
    aghSlist<T>& operator=(const aghContainer<T>& _right);
    
};


template <class T>
aghSlist<T>::aghSlist(unsigned int _size):firstElement(NULL), elementsCount(_size)
{
    if (_size > 0)
    {
        aghNode<T> * temp;
        
        for (unsigned int i = 0; i < _size; i++)
        {
            temp = firstElement;
            firstElement = new aghNode<T>;
            firstElement->setNext(temp);
        }
    }
}

template <class T>
aghSlist<T>::aghSlist(const aghContainer<T>& _source)
{//to dodałem
     aghNode<T>* temp;
     elementsCount = _source.size();
     if(elementsCount){
          for(unsigned int i = 0; i < elementsCount; i++){
               temp = firstElement;
               firstElement = new aghNode<T>(_source[i], temp);
          }
     }else{
          firstElement = NULL;
     }
}

template <class T>
aghSlist<T>::~aghSlist()
{
    this->clear();
    elementsCount = 0;
    firstElement = NULL;
}


template <class T>
T& aghSlist<T>::at (unsigned int _index) const
{
     if(_index >= elementsCount)
     {
          throw aghException(0, "Index out of range", __FILE__, __LINE__);
     }
     else
     {
          return (*firstElement)[_index]->getValue();
     }  
}

template <class T>
unsigned int aghSlist<T>::size (void) const
{
    return elementsCount;
}

template <class T>
bool aghSlist<T>::insert (unsigned int _index, const T& _value)
{
    if(_index > elementsCount)
    {
        return false;
    }
    else
    {
        aghNode<T> * prev;
        if (_index != 0)
        {
            prev = (*firstElement)[_index - 1];
            prev->setNext(new aghNode<T>(_value, prev->getNext()));
        }
        else
        {
            prev = (*firstElement)[_index];
            firstElement = new aghNode<T>(_value, prev);
        }
        elementsCount++;
        return true;
    }
}

template <class T>
bool aghSlist<T>::remove (unsigned int _index)
{
    if(_index >= elementsCount)
    {
        return false;
    }
    else
    {
        if (_index != 0)
        {
            aghNode<T> * prev = (*firstElement)[_index - 1];
            aghNode<T> * deleted = prev->getNext();
            
            prev->setNext(deleted->getNext());
        
            delete deleted;
        }
        else
        {
            aghNode<T> * deleted = (*firstElement)[_index];
            firstElement = deleted->getNext();
            delete deleted;
        }
        elementsCount--;
        return true;
    }
}

template <class T>
aghSlist<T>& aghSlist<T>::operator=(const aghContainer<T>& _right)
{
    if (this != &_right)
    {
        this->clear();
        
        for(int i = 0; i < _right.size(); i++)
        {
            this->append(_right[i]);
        }
    }
    return *this;
}

#endif
