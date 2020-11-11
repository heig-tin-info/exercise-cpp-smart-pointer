#include <exception>

struct Box
{
	int length, width, height;
};

template <class T>
class UniquePtr
{
	T *ptr = nullptr;

public:
	UniquePtr(T *ptr) : ptr{ptr} {}
	UniquePtr(const UniquePtr &obj) = delete;
	UniquePtr &operator=(const UniquePtr &obj) = delete;
	UniquePtr(UniquePtr &&dyingObj)
	{
		this->ptr = dyingObj.ptr;
		dyingObj.ptr = nullptr;
	}
	void operator=(UniquePtr &&dyingObj)
	{
		__cleanup__();
		this->ptr = dyingObj.ptr;
		dyingObj.ptr = nullptr;
	}
	T *operator->() { return this->ptr; }
	T &operator*() { return *(this->ptr); }

	~UniquePtr() { __cleanup__(); }

private:
	void __cleanup__()
	{
		if (ptr != nullptr)
			delete ptr;
	}
};

int main()
{
	UniquePtr<Box> box(new Box);
	return 0;
}