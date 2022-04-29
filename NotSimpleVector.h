#pragma once
#include <memory>
#include <iterator>

template <typename T>
class NotSimpleIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type*;

	NotSimpleIterator(T* p);

	NotSimpleIterator& operator++();
	NotSimpleIterator operator++(int);
	value_type operator*();
	bool operator==(const NotSimpleIterator& rhs) const;
	bool operator!=(const NotSimpleIterator& rhs) const;

private:
	T* ptr;
	using value_type = T;
};

template <typename T, typename Alloc = std::allocator<T>>
class NotSimpleVector
{
public:
	using iterator = NotSimpleIterator<T>;
	NotSimpleVector();

	size_t size() const noexcept;
	size_t capacity() const noexcept;
	void push_back(const T& a);
	void pop_back();
	void insert();
	T& operator[](size_t index);
	iterator begin();
	iterator end();

private:
	T* arr;
	Alloc alloc;
	size_t sz;
	size_t cp;
};


template<typename T>
NotSimpleVector<T>::NotSimpleVector() : sz(0), cp(2), arr(std::allocator_traits<Alloc>::allocate(alloc, 2)) {}

template<typename T>
size_t NotSimpleVector<T>::size() const noexcept { return sz; }
template<typename T>
size_t NotSimpleVector<T>::capacity() const noexcept { return cp; }

template<typename T>
void NotSimpleVector<T>::push_back(const T& a)
{
	if (sz == cp)
	{
		T* new_arr = std::allocator_traits<Alloc>::allocate(alloc, 2 * cp);
		for (int i = 0; i < sz; ++i)
		{
			std::allocator_traits<Alloc>::construct(alloc, new_arr + i, arr[i]);
			std::allocator_traits<Alloc>::destroy(alloc, arr + i);
		}
		std::allocator_traits<Alloc>::deallocate(alloc, arr, sz);
		arr = new_arr;
	}
	std::allocator_traits<Alloc>::construct(alloc, arr + sz, a);
	++sz;
}
template<typename T>
void NotSimpleVector<T>::pop_back() { --sz; }

template<typename T>
void NotSimpleVector<T>::insert()
{
	++sz;


}

template <typename T>
T& NotSimpleVector<T>::operator[](size_t index) { return arr[index]; }
template <typename T>
NotSimpleIterator<T> NotSimpleVector<T>::begin() { return NotSimpleIterator<T>(arr); }
template <typename T>
NotSimpleIterator<T> NotSimpleVector<T>::end() { return NotSimpleIterator<T>(arr + sz); }

template <typename T>
NotSimpleIterator<T>::NotSimpleIterator(T* p) { ptr = p; }
template <typename T>
NotSimpleIterator<T>& NotSimpleIterator<T>::operator++()
{ 
	++ptr; 
	return *this; 
}

template <typename T>
NotSimpleIterator<T> NotSimpleIterator<T>::operator++(int)
{
	NotSimpleIterator<T> cpy = *this;
	++(*this);
	return cpy;
}

template <typename T>
T& NotSimpleIterator<T>::operator*() { return *ptr; }
template <typename T>
bool NotSimpleIterator<T>::operator==(const NotSimpleIterator<T>& rhs) const { return this->ptr == rhs.ptr; }
template <typename T>
bool NotSimpleIterator<T>::operator!=(const NotSimpleIterator<T>& rhs) const { return !(*this == rhs); }
