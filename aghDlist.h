/**
* \file aghDlist.h
* \author Filip Pasternak
* \date 31.05.2013
* \brief Definition of class template aghDlist which extends aghContainer class template.
*/
// -------------------------------------------------------------------------
#ifndef AGHDLIST_H
#define AGHDLIST_H

#include <iostream>
#include "aghContainer.h"
#include "aghNode.h"
#include "aghException.h"

using namespace std;

/**
* \class template aghVector
* \author Filip Pasternak
* \date 31.05.2013
* \brief Definition of class template aghDlist which extends aghContainer class template.
*/
template <class T>
class aghDlist : public aghContainer<T>{
     private:
          aghNode<T>* firstElement;   ///< Pointer to the first element of the list.
          unsigned int elementsCount; ///< Ammount of elements in the list.
     
     public:
          //\brief The class constructor.
          //
          //\param _size - number of elements to store
          aghDlist(unsigned int _size = 0);
          
          //\brief The class copying constructor.
          //
          //\param _source - source object
          aghDlist(const aghContainer<T>& _source);
          
          //\brief The class destructor.
          virtual ~aghDlist();
     
          //\brief Method to return value of given element.
          //
          //\param _index - index of chosen element
          //\return value of the element on given position
          T& at(unsigned int _index) const;
          
          //\brief Method to check ammount of elements in the list.
          //
          //return Ammount of the elements.
          unsigned int size(void) const;
          
          //\brief Method to insert new element to the list.
          //
          //\param _index - position where we want to put new element
          //\param _value - value to set for new element
          //\return TRUE if finished successfully ( FALSE otherwaise )
          bool insert(unsigned int _index, T const& _value);
          
          //\brief Method to remove element from the list.
          //
          //\param _index - position from where we want remove element
          //\return TRUE if finished successfully ( FALSE otherwaise )
          bool remove(unsigned int _id);
          
          //\brief Overload of operator=
          //
          //\param - source aghVector<T> object
          //\return reference to 'this' object
          aghDlist<T>& operator=(const aghContainer<T>& _right);
};

template <typename T>
aghDlist<T>::aghDlist(unsigned int _size){
     firstElement = NULL;
     elementsCount = _size;
     aghNode<T>* temp;
     
     if(_size > 0){          
          for(unsigned int i = 0; i < _size; i++){
               temp = firstElement;
               firstElement = new aghNode<T>(0, temp, NULL);
               if(i != 0) temp->setPrev(firstElement);
          }
     }
}

template <typename T>
aghDlist<T>::aghDlist(const aghContainer<T>& _source){
     aghNode<T>* temp;
     elementsCount = _source.size();
     if(elementsCount){
          for(unsigned int i = 0; i < elementsCount; i++){
               temp = firstElement;
               firstElement = new aghNode<T>(_source[i], temp, NULL);
               if(i != 0) temp->setPrev(firstElement);
          }
     }else{
          firstElement = NULL;
     }
}

template <typename T>
aghDlist<T>::~aghDlist(){
     this->clear();
     elementsCount = 0;
     firstElement = NULL;
}

template <typename T>
T& aghDlist<T>::at(unsigned int _index)const{
     if(_index >= elementsCount){
          throw aghException(0, "Index out of range", __FILE__, __LINE__);
     }else{
          return (*firstElement)[_index]->getValue();
     }  
}

template <typename T>
unsigned int aghDlist<T>::size(void)const{
     return elementsCount;
}

template <typename T>
bool aghDlist<T>::insert(unsigned int _index, T const& _value){
     aghNode<T>* temp;
     aghNode<T>* newElement;
     if(_index > elementsCount){
          return false;
     }else{
          newElement = new aghNode<T>(_value);

          if(_index != 0){
               temp = (*firstElement)[_index-1];
               newElement->setNext(temp->getNext());
               newElement->setPrev(temp);
               temp->setNext(newElement);
                    
               if(newElement->getNext()){
                    newElement->getNext()->setPrev(newElement);
               }
          }else{
               newElement->setNext(firstElement);
               newElement->setPrev(NULL);
               if(firstElement) firstElement->setPrev(newElement);
               firstElement = newElement;
          }
     elementsCount++;
     return true;
     } 
}

template <typename T>
bool aghDlist<T>::remove(unsigned int _index){
     aghNode<T>* toRemove;
     if(_index < elementsCount){
          toRemove = (*firstElement)[_index];
          if(_index != elementsCount-1){
               toRemove->getNext()->setPrev(toRemove->getPrev());
          }
          if(_index != 0){
               toRemove->getPrev()->setNext(toRemove->getNext());
          }
          if(_index == 0){
               firstElement = toRemove->getNext();
          }
          
          delete toRemove;
          elementsCount--;
          return true;
     }else{
          return false;
     }
}
template<class T>
aghDlist<T>& aghDlist<T>::operator=(const aghContainer<T>& _right){
     if(this != &_right){
          this->clear();
          for(unsigned int i = 0; i < _right.size(); i++){
               this->append(_right[i]);
          }
     }
     return *this;
}
#endif
