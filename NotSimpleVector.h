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
	T& operator*();
	bool operator==(const NotSimpleIterator& rhs) const;
	bool operator!=(const NotSimpleIterator& rhs) const;

private:
	T* ptr;
};

template <typename T, typename Alloc = std::allocator<T>>
class NotSimpleVector
{
public:
	using iterator = NotSimpleIterator<T>;
	NotSimpleVector();
	NotSimpleVector(const NotSimpleVector<T, Alloc>& a);
	NotSimpleVector(NotSimpleVector<T, Alloc>&& a);

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


template<typename T, typename Alloc>
NotSimpleVector<T, Alloc>::NotSimpleVector() : sz(0), cp(2), arr(std::allocator_traits<Alloc>::allocate(alloc, 2)) {}
template<typename T, typename Alloc>
NotSimpleVector<T, Alloc>::NotSimpleVector(const NotSimpleVector<T, Alloc>& a) : sz(a.size()), cp(a.capacity()), arr(std::allocator_traits<Alloc>::allocate(alloc, a.capacity())) 
{
	for(size_t i = 0; i < a.size(); ++i)
	{
		std::allocator_traits<Alloc>::construct(alloc, arr + i, a[i]);
	}

}

template<typename T, typename Alloc>
size_t NotSimpleVector<T, Alloc>::size() const noexcept { return sz; }
template<typename T, typename Alloc>
size_t NotSimpleVector<T, Alloc>::capacity() const noexcept { return cp; }

template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::push_back(const T& a)
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
template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::pop_back() { --sz; }

template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::insert()
{
	++sz;
}

template<typename T, typename Alloc>
T& NotSimpleVector<T, Alloc>::operator[](size_t index) { return arr[index]; }
template<typename T, typename Alloc>
NotSimpleIterator<T> NotSimpleVector<T, Alloc>::begin() { return NotSimpleIterator<T>(arr); }
template<typename T, typename Alloc>
NotSimpleIterator<T> NotSimpleVector<T, Alloc>::end() { return NotSimpleIterator<T>(arr + sz); }

template<typename T>
NotSimpleIterator<T>::NotSimpleIterator(T* p) { ptr = p; }
template<typename T>
NotSimpleIterator<T>& NotSimpleIterator<T>::operator++()
{ 
	++ptr; 
	return *this; 
}

template<typename T>
NotSimpleIterator<T> NotSimpleIterator<T>::operator++(int)
{
	NotSimpleIterator<T> cpy = *this;
	++(*this);
	return cpy;
}

template<typename T>
T& NotSimpleIterator<T>::operator*() { return *ptr; }
template<typename T>
bool NotSimpleIterator<T>::operator==(const NotSimpleIterator<T>& rhs) const { return this->ptr == rhs.ptr; }
template<typename T>
bool NotSimpleIterator<T>::operator!=(const NotSimpleIterator<T>& rhs) const { return !(*this == rhs); }
