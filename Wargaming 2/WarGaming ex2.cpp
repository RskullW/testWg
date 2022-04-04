#include <iostream>

const int _MAX_SIZE_BUFFER = 5;

template <class value_type> struct node
{
	value_type data;
	node* next;
};

#pragma region ALL_CLASSES
// Interface (basic class)
template <class value_type> class Container
{
public:
	// Default Constructor
	Container() = default;
	// Adding a new element
	virtual void push(value_type) = 0;
	// Extracting and reading the first element
	virtual value_type pop() = 0;
	// Clearing the buffer
	virtual void clear() = 0;
	// Checking for buffer fullness: 1 - FULL, 0 - BUFFER IS NOT FULL
	bool full() const { return (sizeBuffer == _MAX_SIZE_BUFFER) ? 1 : 0; }
	// Checking for buffer emptiness: 1 - EMPTY, 0 - AVAILABILITY
	bool isEmpty() const { return (sizeBuffer == 0) ? 1 : 0; }
	// Getter sizeBuffer
	uint32_t getSize() const { return sizeBuffer; }
	// Destructor
	virtual ~Container() = default;
protected:
	uint32_t sizeBuffer = 0;
	value_type* data;
	node<value_type>* head;
};
// Vector implementation 
template <class value_type> class Vector final :
	public Container<value_type>
{
public:
	// Default Constructor
	Vector();
	// Adding a new element
	void push(const value_type);
	// Extracting and reading the first element
	value_type pop();
	// Clearing the buffer
	void clear();
	// Destructor
	~Vector();
};
// List implementation 
template <class value_type> class List final :
	public Container<value_type>
{
public:
	// Default Constructor
	List();
	// Adding a new element
	void push(const value_type);
	// Extracting and reading the first element
	value_type pop();
	// Clearing the buffer
	void clear();
	// Destructor
	~List();
};

template <class value_type, template<typename> class Container = Vector > class userBuffer
{
public:
	userBuffer() = default;
	void push(value_type dataFromTheUser)
	{
		m_Container.push(dataFromTheUser);
	}
	void clear()
	{
		m_Container.clear();
	}
	bool full()
	{
		return m_Container.full();
	}
	bool isEmpty()
	{
		return m_Container.isEmpty();
	}
	uint32_t getSize()
	{
		return m_Container.getSize();
	}
	value_type pop()
	{
		return m_Container.pop();
	}
private:
	Container<value_type> m_Container;
};
#pragma endregion ALL_CLASSES

#pragma region VECTOR_METHOD_IMPLEMENTAION

template <class value_type> Vector<value_type>::Vector()
{
	Container<value_type>::data = new value_type[_MAX_SIZE_BUFFER];
	Container<value_type>::sizeBuffer = 0;
}

template <class value_type> void Vector<value_type>::push(const value_type dataFromTheUser)
{
	if (Container<value_type>::sizeBuffer == _MAX_SIZE_BUFFER)
	{
		throw std::exception("Buffer full!\n");
	}

	Container<value_type>::data[Container<value_type>::sizeBuffer++] = dataFromTheUser;
}

template <class value_type> value_type Vector<value_type>::pop()
{
	if (Container<value_type>::sizeBuffer == 0)
	{
		throw std::exception("Buffer empty!\n");
	}

	value_type tempData = Container<value_type>::data[0];

	for (uint32_t i = 0; i < Container<value_type>::sizeBuffer - 1; ++i)
	{
		Container<value_type>::data[i] = Container<value_type>::data[i + 1];
	}

	Container<value_type>::data[--Container<value_type>::sizeBuffer] = 0;

	return tempData;

}

template <class value_type> void Vector<value_type>::clear()
{
	delete Container<value_type>::data;
	Container<value_type>::data = new value_type[_MAX_SIZE_BUFFER];
	this->sizeBuffer = 0;
}

template <class value_type> Vector<value_type>::~Vector()
{
	delete Container<value_type>::data;
}

#pragma endregion VECTOR_METHOD_IMPLEMENTATION

#pragma region LIST_METHOD_IMPLEMENTATION

template <class value_type> List<value_type>::List()
{
	Container<value_type>::head = NULL;
	Container<value_type>::sizeBuffer = 0;
}

template <class value_type> void List<value_type>::push(const value_type dataFromTheUser)
{
	if (Container<value_type>::sizeBuffer == _MAX_SIZE_BUFFER)
	{
		throw std::exception("Buffer full!\n");
	}

	if (Container<value_type>::sizeBuffer == 0)
	{
		Container<value_type>::head = new node<value_type>;
		Container<value_type>::head->data = dataFromTheUser;
		Container<value_type>::head->next = NULL;
	}

	else
	{
		node<value_type>* temp = Container<value_type>::head;

		while (temp)
		{
			if (temp->next == NULL)
			{
				temp->next = new node<value_type>;
				temp->next->data = dataFromTheUser;
				temp->next->next = NULL;
				break;
			}

			temp = temp->next;
		}
	}

	Container<value_type>::sizeBuffer++;
}

template <class value_type> value_type List<value_type>::pop()
{
	if (Container<value_type>::sizeBuffer == 0)
	{
		throw std::exception("Buffer empty!\n");
	}


	node<value_type>* temp = Container<value_type>::head;
	value_type tempData = temp->data;
	Container<value_type>::head = Container<value_type>::head->next;
	--Container<value_type>::sizeBuffer;

	delete temp;

	return tempData;
}

template <class value_type> void List<value_type>::clear()
{
	while (Container<value_type>::sizeBuffer--)
	{
		node<value_type>* temp = Container<value_type>::head;
		Container<value_type>::head = Container<value_type>::head->next;

		delete temp;
	}

	Container<value_type>::head = NULL;
	Container<value_type>::sizeBuffer = 0;
}

template <class value_type> List<value_type>::~List()
{
	while (Container<value_type>::sizeBuffer--)
	{
		node<value_type>* temp = Container<value_type>::head;
		Container<value_type>::head = Container<value_type>::head->next;

		delete temp;
	}
}

#pragma endregion LIST_METHOD_IMPLEMENTATION

int main()
{
	uint32_t i = 1;
	userBuffer<uint32_t, List> foo;
	try
	{
		// Checking for emptiness
		std::cout << "1 - empty, 0 - availablity: " << foo.isEmpty() << "\n---";
		// Checking for fullness and adding five data
		while (!foo.full())
		{
			foo.push(i);
			std::cout << "\nData = " << i++ << " || 1 - full, 0 - buffer is not full: ";
			std::cout << foo.full();
		}

		std::cout << "\n---";
		// Checking for emptiness and delete five data
		while (!foo.isEmpty())
		{
			std::cout << "\nData = " << foo.pop() << " || 1 - empty, 0 - buffer is not empty: ";
			std::cout << foo.isEmpty();
		}

		std::cout << "\n---\n";
		// Checking to delete a file in an empty buffer. Waiting: going to the exception
		std::cout << foo.pop();

	}

	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}


	return 0;
}