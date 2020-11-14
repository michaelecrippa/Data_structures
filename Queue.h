#include <iostream>
template <typename T> struct Node {
	T data;
	Node* next;
	Node* prev;

	Node<T>();

	T getData() const;
	void setData(const T* data);

	Node<T>* getNext() const;
	void setNext(const Node<T>* next);

	Node<T>* getPrevious() const;
	void setPrevious(const Node<T>* prev);

	void print() const;
};

template <typename T> class Queue {
	Node<T>* head;
	Node<T>* tail;
	size_t size;

	void erase();
	void copyFrom(const Queue<T>& other);

	bool isEmpty() const;
public:
	Queue();
	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);
	~Queue();


	void push(const T& element); //pushFront 
	T pop(); //popBack
	T peak() const; //show next element to be removed 

	size_t getSize() const;
	void print() const;
	void reverse();

};

template <typename T> void Queue<T>::erase() {
	if (isEmpty()) return;
	while (head != tail) { //more than 1 element
		head = head->getNext();
		delete head->getPrevious();
	}
	delete head; //1 element left to delete
	head = tail = nullptr;
}
template <typename T> void Queue<T>::copyFrom(const Queue<T>& other) {
	short diff = size - other.size;
	//other is larger
	if (diff < 0)
		for (short i = diff; i < 0; i++)
			this->pushBack((T)0); //add some "fictive" elements 
	//other is smaller or equal
	else
		for (short i = 0; i < diff; i++)
			this->popBack();
	//copy data from the other list
	Node<T>* cursor = head;
	Node<T>* otherCursor = other.head;
	while (cursor != nullptr) {
		cursor->setData(&otherCursor->data);
		cursor = cursor->getNext();
		otherCursor = otherCursor->getNext();
	}
}

template <typename T> Queue<T>::Queue() {
	head = tail = nullptr;
	size = 0;
}
template <typename T> Queue<T>::Queue(const Queue<T>& other) {
	copyFrom(other);
}
template <typename T> Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this != &other)
		copyFrom();
	return *this;
}
template <typename T> Queue<T>::~Queue() {
	erase();
}

template <typename T> void Queue<T>::push(const T& element) {
	Node<T>* add;
	add->setData(&element);
	if (isEmpty()) {
		head = tail = add;
	}
	else
	{
		add->setNext(head);
		head->setPrevious(add);
		head = add;
	}
	size++;
}
template <typename T> T  Queue<T>::pop() {
	if (isEmpty())
		throw std::length_error("");
	T data = tail->getData();
	if (size > 1) {
		tail = tail->getPrevious();
		delete tail->getNext();
		tail->setNext(nullptr);
	}
	else {
		delete tail;
		head = tail = nullptr;
	}
	size--;
	return data;
}
template <typename T> T Queue<T>::peak() const{
	if (isEmpty()) throw std::length_error("");
	return tail->getData();
}

template <typename T> bool Queue<T>::isEmpty() const {
	return head == nullptr;
}
template <typename T> void Queue<T>::print() const {
	if (isEmpty()) return;
	std::cout << "Head ->";
	Node<T>* iter = head;
	while (iter !=nullptr)
	{
		std::cout << iter->getData() << " ";
		iter = iter->getNext();
	}
}
template <typename T> size_t Queue<T>::getSize() const {
	return size;
}
template <typename T> void Queue<T>::reverse() {
	if (isEmpty()) return;
	Node<T>* helper;
	helper = head;
	head = tail;
	tail = helper;
		
}