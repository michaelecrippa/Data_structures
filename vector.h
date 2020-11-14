#include "baseStructureInterface.h"

template <typename T>
class vector : public structuresInterface<T> {
private:
	size_t size;
	size_t capacity;
	T* container;

	void erase();
	void copyFrom(const vector<T>& other);

	void resize();
	void shrink_to_fit();

	bool isEmpty() const;
	bool outOfRange(size_t index) const;

	T getAt(size_t index);
public:
	vector();
	vector(size_t capacity);
	vector(const vector& other);
	vector<T>& operator=(const vector<T>& other);
	~vector();

	void addAt(const T& element, size_t index);
	T removeAt(size_t index);

	void push(const T& element);
	T pop();

	void pushBack(const T& element);
	T popBack();

	T peak() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	size_t getSize() const;
	void print() const;
};

template <typename T> bool vector<T>::isEmpty() const {
	return this == nullptr;
}
template <typename T> bool vector<T>::outOfRange(size_t index) const{
	return index >= capacity;
}

template <typename T> void vector<T>::erase() {
	if (this->isEmpty()) return;
	delete[] container;
	container = nullptr;
	size = 0;
	capacity = 0;
}
template <typename T> void vector<T>::copyFrom(const vector<T>& other) {
	if (other.isEmpty()) {
		erase();
		return;
	}
	this->size = other.size;
	this->capacity = other.capacity;
	delete[] this->container;
	container = new T[capacity];
	for (size_t i = 0; i < size; i++)
		container[i] = other.container[i];
}
template <typename T> void vector<T>::resize() {
	this->capacity << 1; // shift left 1 postion to get new capacity
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}
template <typename T> void vector<T>::shrink_to_fit() {
	this->capacity >> 1 // shift right 1 postiotion to get new capacity;
	T* helper = new T[capacity];
	for (size_t i = 0; i < this->size; i++)
		helper[i] = container[i];
	delete[] container;
	container = helper;
}

template <typename T> vector<T>::vector() {
	this->size = 0;
	this->capacity = 4;
	this->container = new T[this->capacity];
}
template <typename T> vector<T>::vector(size_t capacity) {
	this->size = 0;
	this->capacity = capacity;
	this->container = new T[this->capacity];
}// create dynamic array with capacity closest bigger power of two to requested capacity
template <typename T> vector<T>::vector(const vector<T>& other) {
	copyFrom(other);
}
template <typename T> vector<T>& vector<T>::operator=(const vector<T>& other) {
	if (this != &other)
	{
		erase();
		copyFrom(other);
	}
	return *this;
}
template <typename T> vector<T>::~vector() {
	if (!this->isEmpty()) erase();
}

template <typename T> size_t vector<T>::getSize() const {
	return size;
}
template <typename T> void vector<T>::print() const {
	if (this->isEmpty())
		throw "Empty vector!";
	for (size_t i = 0; i < size; i++)
		std::cout << container[i] << ' ';
}
template  <typename T> T vector<T>::getAt(size_t index) {
	if (!outOfRange(index))
		return container[index];
	throw std::out_of_range("");
}
template <typename T> void vector<T>::addAt(const T& element, size_t index) {
	if (outOfRange(index))
		throw std::out_of_range("exception");
	if (size == capacity)
		resize();
	container[index] = element;
	size++;
}
template <typename T> T vector<T>::removeAt(size_t index) {
	if (outOfRange(index))
		throw std::out_of_range("exception");
	size--;
	if (size < capacity / 2 && capacity > 8)
		this->shrink_to_fit();
	return container[index];
}
template <typename T> T& vector<T>::operator[](size_t index) {
	if (outOfRange(index))
		throw std::out_of_range("");
	T* ptr = container[index];
	return ptr;
}
template <typename T> const T& vector<T>::operator[](size_t index) const {
	if (outOfRange(index))
		throw std::out_of_range("");
	return container[index];
}

template <typename T> void vector<T>::push(const T& element) {
	if (size == capacity)
		resize();
	for (size_t i = size - 1; i > 0; i--)
		container[i] = container[i - 1]; //pusha all elements one position right
	container[0] = element;
	size++;
}
template <typename T> void vector<T>::pushBack(const T& element) {
	this->addAt(element, this->size);
}
template <typename T> T vector<T>::pop() {
	if (isEmpty()) throw std::out_of_range("");
	T el = container[0];
	for (size_t i = size - 1; i > 0; i++)
		container[i - 1] = container[i]; //push all elements one position left
	size--;
	return el;
}
template <typename T> T vector<T>::popBack() {
	return this->removeAt(this->size - 1);
}
template <typename T> T vector<T>::peak() const {
	if (isEmpty())
		throw std::length_error("exc");
	return container[0];
}
