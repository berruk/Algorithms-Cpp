/*
*
*   Custom List Library  
*     @author: github/berruk
*
*
*/


#include <iostream>

#ifndef CPPLIST_H
#define CPPLIST_H


/*
* Node struct for linkedlist
*/
template <typename T>
struct Node{

  T val;
  Node<T>* next;

  void operator =(T&);
  void operator =(Node<T>&);

};

/*
 * List class 
 * Implemented with a Linked List data structure.
 *
*/ 
template <typename T>
class List{

    protected:

        Node<T>* head;
        Node<T>* tail;
        size_t lsize;

    public:

        List();
        //List(size_t);
        ~List();


        //:::Capacity:::

        size_t size() const;
        bool is_empty() const;

        //:::Element access:::
        
        T& operator[] (int);
        T& front() const; 
        T& back() const;
        T* data();
        int get_index(T);
        void print();

        //:::Modifiers:::

        bool push_back(const T&);
        T pop_back();
        bool insert(int, const T&);
        bool swap(List<T>&);
        bool clear();
        

   

};

/*
 *  Assignment operator
 *  @param reference of value 
 */
template <typename T>
void Node<T>::operator = (T& value) { 
    
    val = value;

}

/*
 *   Assignment operator
 *  @param reference of node 
 */
template <typename T>
void Node<T>::operator = (Node<T>& ref) { 
    
    val = ref.val;

}


template <typename T>
void List<T>::print(){
    
    Node<T> *temp = head;
    
    std::cout << "List: ";

    for(int i; i<lsize; i++){

        std::cout << temp->val << std::endl;
        temp = temp->next;

    }

}

template <typename T>
List<T>::List(){
    
    head = NULL;
    tail = NULL;
    lsize = 0;

}


template <typename T>
List<T>::~List(){
    
    clear();

}


template<typename T>
bool List<T>::push_back(const T& value){

	Node<T> *temp = new Node<T>();
	temp->val = value;
	temp->next = NULL;
	lsize++;

	if(!head){ //First element
		head = temp;
		tail = temp;
	}
    else{ 
        tail->next = temp;
		tail = temp;
	}

	return true;
}



template<typename T>
T List<T>::pop_back(){ //return reference? leak

    T return_val = head->val;

    if (head == NULL)
        return 0;
 
    if (head->next == NULL){

        delete head;
        head = NULL;
        return return_val;
    
    }
 
    Node<T>* second_last = head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;
 
    return_val = second_last->next->val;

    delete (second_last->next);
    second_last->next = NULL;
    
    lsize--;

    return return_val;
  
}


/*
 *   Inserts data to a certain index
 *  @param index, reference of value 
 */
template<typename T>
bool List<T>::insert(int index,const T& value) 
{

    Node<T> *temp = new Node<T>();
	temp->val = value;
	temp->next = NULL;
	lsize++;
    

    if(index == 0){

        temp->next = head;
        head = temp;

        return true;

    }

    Node<T>* prev;
    prev = head;

    while(index > 1){

        prev = prev->next;
        index--;

    } 
    
    temp->next = prev->next; 
    prev->next = temp; 

    return true;

}


/*
 *   Clears the contents of the List
 */
template<typename T>
bool List<T>::clear(){

    Node<T>* temp;

	while(head!=NULL){

		temp = head;
		head = head->next;
		delete temp;
	}

	lsize = 0;
	tail = NULL;

    return true;
 
}

/*
 *   Swaps contents of two Lists
 *  @param List reference
 */
template<typename T>
bool List<T>::swap(List<T>& berry){

    Node<T>* blue;
    blue = berry.head;
    berry.head = head;
    head = blue;

    return true;  

}

template <typename T>
size_t List<T>::size() const{

  return lsize;

}

template <typename T>
bool List<T>::is_empty() const{

  return lsize == 0;

}

template <typename T>
T& List<T>::operator[](int index)
{
    Node<T>* prev;
    prev = head;

    while(index > 1){

        prev = prev->next;
        index--;

    } 
    
    return prev->val;
}

template <typename T>
T& List<T>::back() const{

  return tail->val;

}

template <typename T>
T& List<T>::front() const{

    return head->val;

}

template <typename T>
T* List<T>::data(){

    return head;

} 


/*
 *   Returns index to value if exists
 *   @param 
 *   val: to be found
 */
template <typename T>
int List<T>::get_index(T val){

    Node<T>* temp = head;

    for(int i=0; i<lsize; i++){

            if(temp->next->val == val)
                return i;

            temp = temp->next;
        }
    
    return -1;

}


/*

    :::: ::::
    *reverse
    *remove
    *remove_if
    *unique
    *emplace
    *iterator

    
*/


#endif