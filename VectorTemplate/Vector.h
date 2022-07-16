#include <iostream>
#include <algorithm>
#pragma once

template <typename T>
class Vector;

template <typename T>
std::istream& operator >> (std::istream& is, Vector<T>& original);

template <typename T>
std::ostream& operator << (std::ostream& os, const Vector<T>& original);

template <typename T>
bool operator == (const Vector<T> left, const Vector<T> right);

template <typename T>
class Vector
{
    unsigned int size = 0;
    unsigned int capacity = 10;
    T* data = nullptr;

public:
    Vector();
    Vector(unsigned int capacity);
    ~Vector();

private:
    void EnsureCapacity();

public:
    unsigned int GetSize() const;
    unsigned int GetCapacity() const;
    void PushBack(T value);
    void PushFront(T value);
    void Clear();
    bool IsEmpty() const;
    void Print() const;
    void Insert(T value, int index);
    void RemoveByIndex(int index);
    void RemoveByValue(T value);
    void PopFront();
    void PopBack();
    void TrimToSize();
    int IndexOf(T value);
    int LastIndexOf(T value);
    void Reverse();
    void SortAsc();
    void SortDesc();
    void Shuffle();
    void RandomFill(int size);
    bool Equals(Vector& origin);
    T GetElementAt(int index);
    Vector(const Vector& original);
    Vector& operator = (const Vector& original);
    T operator[](int index);
    template <typename T>
    friend bool operator == <>(const Vector<T> left, const Vector<T> right);
    friend std::istream& operator >> <>(std::istream& is, Vector& original);
    friend std::ostream& operator << <>(std::ostream& os, const Vector& original);
};

template <typename T>
Vector<T>::Vector() : Vector(10) {}

template <typename T>
Vector<T>::Vector(unsigned int capacity)
{
    if (capacity < 10)
    {
        capacity = 10;
    }
    this->capacity = capacity;
    data = new T [capacity];
}

template <typename T>
Vector<T>:: ~Vector()
{
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
}

template <typename T>
void Vector<T>::EnsureCapacity()
{
    if (size == capacity)
    {
        capacity *= 2;
        T* temp = new T[capacity];
        for (unsigned int i = 0; i < size; i++)
            temp[i] = data[i];
        delete[] data;
        data = temp;
    }
}

template <typename T>
void Vector<T>::PushBack(T value)
{
    EnsureCapacity();
    data[size++] = value;
}

template <typename T>
void Vector<T>::PushFront(T value)
{
    EnsureCapacity();
    for (unsigned int i = size; i > 0; i--)
        data[i] = data[i - 1];
    data[0] = value;
    size++;
}

template <typename T>
void Vector<T>::Clear()
{
    size = 0;
}

template <typename T>
bool Vector<T>::IsEmpty() const
{
    return size == 0;
}

template <typename T>
void Vector<T>::Print() const
{
    if (IsEmpty())
    {
        std::cout << "Vector is empty.\n";
        return;
    }
    for (unsigned int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << "\n";
}

template <typename T>
unsigned int Vector<T>::GetSize() const
{
    return size;
}

template <typename T>
unsigned int Vector<T>::GetCapacity() const
{
    return capacity;
}

template <typename T>
void Vector<T>::Insert(T value, int index)
{
    if (index < 0 || index > size)
        throw "Incorrect index!";
    EnsureCapacity();
    for (unsigned int i = size + 1; i >= index; i--)
        data[i + 1] = data[i];
    data[index] = value;
    size++;
}

template <typename T>
void Vector<T>::RemoveByIndex(int index)
{
    if (index < 0 || index >= size)
        throw "Incorrect index!";

    for (unsigned int i = index; i <= size - 1; i++)
        data[i] = data[i + 1];

    size--;
}

template <typename T>
void Vector<T>::RemoveByValue(T value)
{
    for (unsigned int i = 0; i < size; i++)
    {
        if (data[i] == value) {
            RemoveByIndex(i);
            i = -1;
        }
    }
}

template <typename T>
void Vector<T>::PopFront()
{
    for (unsigned int i = 0; i < size; i++)
        data[i] = data[i + 1];
    size--;
}

template <typename T>
void Vector<T>::PopBack()
{
    size--;
}

template <typename T>
void Vector<T>::TrimToSize()
{
    if (size != capacity)
    {
        capacity = size;
        T* temp = new T[capacity];
        for (unsigned int i = 0; i < size; i++)
            temp[i] = data[i];
        delete[] data;
        data = temp;
    }
}

template <typename T>
int Vector<T>::IndexOf(T value)
{
    for (unsigned int i = 0; i < size; i++) {
        if (data[i] == value)
            return i;
    }
    return -1;
}

template <typename T>
int Vector<T>::LastIndexOf(T value)
{
    for (int i = size - 1; i >= 0; i--) {
        if (data[i] == value)
            return i;
    }
    return -1;
}

template <typename T>
void Vector<T>::Reverse()
{
    std::reverse(data, data + size);
}

template <typename T>
void Vector<T>::SortAsc()
{
    std::sort(data, data + size);
}

template <typename T>
void Vector<T>::SortDesc()
{
    SortAsc();
    std::reverse(data, data + size);
}

template <typename T>
void Vector<T>::Shuffle()
{
    std::random_shuffle(data, data + size);
}

template <typename T>
void Vector<T>::RandomFill(int size)
{
     this->size = size;
    this->capacity = size;
    EnsureCapacity();
    for (unsigned int i = 0; i < size; i++)
        data[i] = rand() % 90 + 10;
}

template <typename T>
bool Vector<T>::Equals(Vector& origin)
{
    if (size != origin.size)
        return false;
    for (unsigned int i = 0; i < size; i++) {
        if (data[i] != origin.data[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
T Vector<T>::GetElementAt(int index)
{
    if (index < 0 || index >= size)
        throw "Incorrect index!";
    return data[index];
}

template <typename T>
Vector<T>::Vector(const Vector& original)
{
    size = original.size;
    capacity = original.capacity;
    data = new T[size];
    for (unsigned int i = 0; i < size; i++)
        data[i] = original.data[i];
}

template <typename T>
bool operator == (const Vector<T> left, const Vector<T> right)
{
    if (left.size != right.size)
        return false;
    for (unsigned int i = 0; i < left.size; i++) {
        if (left.data[i] != right.data[i])
            return false;
    }
    return true;
}

template <typename T>
Vector<T>& Vector<T>::operator = (const Vector& original)
{
    if (this == &original)
        return *this;
    delete[] data;
    size = original.size;
    capacity = original.capacity;
    data = new T[size];
    for (unsigned int i = 0; i < size; i++)
        data[i] = original.data[i];
    return *this;
}

template <typename T>
T Vector<T>::operator[](int index)
{
    if (index < 0 || index >= size)
        throw "Incorrect index!";
    return data[index];
}

template <typename T>
std::istream& operator >> (std::istream& is, Vector<T>& original)
{
    std::cout << "Please, enter the size of array: ";
    is >> original.size;
    std::cout << "Please, enter the capacity of array: ";
    is >> original.capacity;
    for (unsigned int i = 0; i < original.size; i++) {
        std::cout << "Please enter value for element " << i << " of array: ";
        is >> original.data[i];
    }
    return is;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Vector<T>& original)
{
    for (unsigned int i = 0; i < original.size; i++)
        os << original.data[i] << " ";
    return os;
}

