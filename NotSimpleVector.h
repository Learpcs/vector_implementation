#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class NotSimpleVector
{
public:
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
	class NotSimpleIterator
	{
	    public:
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
public: using iterator = NotSimpleIterator;
};
