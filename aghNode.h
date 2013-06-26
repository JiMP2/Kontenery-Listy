//
//  aghNode.h
//
//  Created by Wojtek on 5/29/13.
//  Copyright (c) 2013 Wojtek. All rights reserved.
//
#ifndef AGHNODE_H
#define AGHNODE_H

template <class U>
class aghNode {
     private:
          //\brief Value of node element.
          U value; 
          
          //\brief Pointer to next element.    
          aghNode<U> * next;
          
          //\brief Pointer to previous element. NULL by default in aghSlist.
          aghNode<U> * prev;
             
     public:
          //\brief Default class constructor.
          aghNode (U _value = 0, aghNode<U> * _next = NULL, aghNode<U> * _prev = NULL);
          
          //\brief Class copying constructor.
          aghNode (const aghNode<U>& _source);
          
          //\brief "Getter" method for value.
          //\return Method returns value of current element.
          U& getValue (void);
          
          //\brief "Setter" method for value.
          void setValue (U _value);
          
          //\brief "Getter" method for next element.
          //\return Method returns pointer to next element.
          aghNode<U>* getNext (void) const;
          
          //\brief "Setter" method for value.
          void setNext (aghNode<U>* _next);
          
          //\brief "Getter" method for previous element.
          //\return Method returns pointer to previous element.
          aghNode<U>* getPrev (void) const;
          
          //\brief "Setter" method for value.
          //\return Method returns value of current element.
          void setPrev (aghNode<U>* _prev);
          
          //|brief Overload of [] operator. Finds the n-th element in list.
          //\return Pointer to n-th element.
          aghNode<U> * operator[](unsigned int n);
          
          //\brief Overload of << operator.
          //\return Reference to ostream.
          friend ostream& operator<<(ostream& _output, aghNode<U> const& _right)
          {
              _output << _right.value << "\t";
              return _output;
          }
};

template <class U>
aghNode<U>::aghNode (U _value, aghNode<U> * _next, aghNode<U> * _prev):value(_value),next(_next), prev(_prev)
{}

template <class U>
aghNode<U>::aghNode (const aghNode<U>& _source):value(_source.value),next(_source.next), prev(_source.prev)
{}

template <class U>
U& aghNode<U>::getValue (void)
{
    return value;
}

template <class U>
void aghNode<U>::setValue (U _value)
{
    value = _value;
}

template <class U>
aghNode<U>* aghNode<U>::getNext (void) const
{
    return next;
}

template <class U>
void aghNode<U>::setNext (aghNode<U>* _next)
{
    next = _next;
}

template <class U>
aghNode<U>* aghNode<U>::getPrev (void) const
{
    return prev;
}

template <class U>
void aghNode<U>::setPrev (aghNode<U>* _prev)
{
    prev = _prev;
}

template <class U>
aghNode<U>* aghNode<U>::operator[](unsigned int n)
{
    aghNode<U> * temp = this;
    
    for (unsigned int i = 0; i < n; i++)
        temp = temp->next;
    
    return temp;
}

#endif
