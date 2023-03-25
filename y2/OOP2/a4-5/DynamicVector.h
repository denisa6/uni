#pragma once

template <typename T>

class DynamicVector {
private:
	int capacity;
	int size;
	T* elements;
public:
	/// <summary>
	/// Contructor for a dynamic vector
	/// </summary>
	/// <param name="capacity">The initial capacity of the vector</param>
	DynamicVector(int capacity = 5);

	/// <summary>
	/// Copy constructor for a DynamicVector
	/// </summary>
	/// <param name="vector">The DynamicVector to be copies</param>
	DynamicVector(const DynamicVector& vector);
	~DynamicVector();

	/// <summary>
	/// Assignment constructor for a DynamicVector
	DynamicVector& operator=(const DynamicVector& vector);
	T& operator[](int position);

	/// <summary>
	/// Adds an element to the current DynamicVector
	/// </summary>
	/// <param name="elem">The element to be added</param>
	void add(const T& elem);

	int getSize() const;

	void setSize(int size) { this->size = size; }

private:
	/// <summary>
	/// Resize current DynamicVector, multipling its capacity by a real factor
	void resize(double factor = 2);
public:
	class iterator {
	private:
		T* pointer;
	public:
		iterator(T* pointer) { this->pointer = pointer; }
		iterator operator++() { this->pointer++; return *this; }
		iterator operator++(int) { iterator i = *this; this->pointer++; return i; }
		T& operator*() { return *this->pointer; }
		bool operator!=(const iterator& it) { return this->pointer != it.pointer; }
	};

	iterator begin()
	{
		return iterator{ this->elements };
	}

	iterator end()
	{
		return iterator{ this->elements + this->size };
	}
};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& vector)
{
	this->capacity = vector.capacity;
	this->size = vector.size;
	this->elements = new T[this->capacity];

	for (int i = 0; i < this->size; i++)
		this->elements[i] = vector.elements[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& vector)
{
	if (this == &vector)
		return *this;

	this->capacity = vector.capacity;
	this->size = vector.size;

	delete[] this->elements;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = vector.elements[i];

	return *this;
}

template <typename T>
void DynamicVector<T>::add(const T& element)
{
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size++] = element;
}

template <typename T>
void DynamicVector<T>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);
	T* vector = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		vector[i] = this->elements[i];

	delete[] this->elements;
	this->elements = vector;
}

template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
T& DynamicVector<T>::operator[](int position)
{
	return this->elements[position];
}

template <typename T>
DynamicVector<T>& operator+(DynamicVector<T>& v, const T elem)
{
	v.add(elem);
	return v;
}

template <typename T>
DynamicVector<T>& operator+(const T elem, DynamicVector<T>& v)
{
	v.add(elem);
	return v;
}