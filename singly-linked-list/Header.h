#pragma once
#include <iostream>

using namespace std;

class ArrayException : public std::exception
{
private:
	std::string m_error;
public:
	ArrayException(std::string error) : m_error(error) {}
	// ���������� std::string � �������� ����������� ������ C-style
	const char* what() const noexcept { return m_error.c_str(); } // C++11 � �������
};

template <typename T>
class List
{
	int *index; //������ ��������
	T *data;//������ ������
	int head, free; //��������� �� ������ � �� ������ ���������
	int size; //������ ������
	int capacity; //������ �������
	int viewed = 0; //���������� ������������ �����

public:
	List();
	List(int N);
	List(const List<T> & L);
	~List();

	int getSize();                    
	void clear();                       
	bool isEmpty();                     
	bool contains(T value);       //����� ������� ��������� ��������      
	T get(int index);            
	bool replace(T value, int index);   //��������� �������� � �������� �������
	int indexOf(T value);               
	bool add(T value);                  
	bool add_pos(T value, int index);       
	bool remove(T value);               
	bool removeAt(int ind);                           
	int getViewedCount();
	void print();

	class Iterator {
		List<T>* arr; //��������� �� ������
		int cur; //��������� �� ������� ������� ������������������
	public:
		Iterator()
		{
			arr = NULL;
			cur = 0;
		}
		Iterator(List<T>*ar, int ind)
		{
			arr = ar;
			cur = ind;
		}
		Iterator(const Iterator&iter)
		{
			arr = iter.arr;
			cur = iter.cur;
		}
		T& operator *() //������ � ������ �������� ��������
		{
			if (cur != -1)
			{
				return arr->data[cur];
			}
			else throw ArrayException("Invalid index");
		}

		Iterator& operator++()
		{
			if (cur >= 0 && cur < arr->size)
			{
				cur = arr->index[cur];
				return *this;
			}
			else throw ArrayException("Invalid index");
		}

		bool operator ==(const Iterator& iter)
		{
			if (arr == iter.arr && cur == iter.cur)
				return true;
			else return false;
		}

		bool operator !=(const Iterator& iter)
		{
			if (arr != iter.arr || cur != iter.cur)
				return true;
			else return false;
		}
	};

	friend class Iterator;

	Iterator begin() //��������� ��������� begin( )
	{
		Iterator iter(this, head);
		return iter;
	}

	Iterator end() //��������� ��������� end( )
	{
		Iterator iter(this, free);
		return iter;
	}
};

template <typename T>
List<T>::List()
{
	size = 0;
	capacity = 10;
	index = new int[capacity];
	data = new T[capacity];
	head = -1;
	free = 0;
	int i;
	for (i = 0; i < capacity - 1; i++)
	{
		index[i] = i + 1;
	}
	index[i] = -1;
}

template <typename T>
List<T>::List(int N)
{
	size = 0;
	capacity = N;
	index = new int[capacity];
	data = new T[capacity];
	head = -1;
	free = 0;
	int i;
	for (i = 0; i < capacity - 1; i++)
	{
		index[i] = i + 1;
	}
	index[i] = -1;
}

template <typename T>
List<T>::List(const List<T> & L)
{
	size = L.size;
	capacity = L.capacity;
	delete[] index;
	delete[] data;
	index = new int[capacity];
	data = new T[capacity];
	head = L.head;
	free = L.free;
	for (int i = 0; i < capacity; i++)
	{
		index[i] = L.index[i];
		data[i] = L.data[i];
	}
}

template <typename T>
List<T>::~List()
{
	delete[] index;
	delete[] data;
}

template <typename T>
int List<T>::getSize()
{
	return size;
}

template <typename T>
void List<T>::clear()
{
	size = 0;
	capacity = 10;
	delete[] index;
	delete[] data;
	index = new int[capacity];
	data = new T[capacity];
	head = -1;
	free = 0;
	int i;
	for (i = 0; i < capacity - 1; i++)
	{
		index[i] = i + 1;
	}
	index[i] = -1;
}

template <typename T>
bool List<T>::isEmpty()
{
	if (size == 0)
		return true;
	else return false;
}

template <typename T>
bool List<T>::add(T value)
{
	viewed = 0;
	if (free != -1)
		data[free] = value;
	else return false;

	int i = head, temp_free = free, prev = 0;
	while (i != -1) //������� ��������� �������
	{
		viewed++;
		prev = i;
		i = index[i];
	}
	if (size == 0)
		head = free;
	free = index[free]; // �������� ������ ������ ��������� ����� �� ����� �����
	index[prev] = temp_free; // �������� ������ ���������� �� ����� �����������
	index[temp_free] = -1; //������� �������� � �����, ������� �� �� ���� �� ���������
	size++;

	return true;
}

template <typename T>
bool List<T>::add_pos(T value, int ind)
{
	viewed = 0;
	if (ind > size)
		return false;
	if (free != -1)
		data[free] = value;
	else return false;

	int i, j = head, prev = head, next, oldfree = free;
	for (i = 0; i < ind; i++)
	{
		viewed++;
		prev = j;
		j = index[j];
	}

	if (ind == head)//���� ��������� � ������
	{
		next = head;
		head = free;
	}
	else
	{
		next = index[prev]; //������ ��������, ������� ����� � ������� ind
		index[prev] = free; //������ ����������� ��������� �� �����
	}
	free = index[free]; //����������� ������ ������ ��������� �� ��������� �������
	index[oldfree] = next;//����������� ������ ��������� �� �������, �������� � ������� ind

	size++;
	return true;
}

template <typename T>
void List<T>::print()
{
	int i = head;
	while(i!=-1)
	{
		cout << data[i] << " ";
		i = index[i];
	}
	cout << endl;
}

template <typename T>
bool List<T>::removeAt(int ind)
{
	viewed = 0;
	int i, j = head, prev = head;
	int next;
	if (size <= ind)
		return false;

	for (i = 0; i < ind; i++)
	{
		viewed++;
		prev = j;
		j = index[j];
	}

	if (j == head)//���� ������� ������
	{
		head = index[j];//���������� ������ �� ��������� �������
	}
	//������ �������
	index[prev] = index[j]; //��� ����������� ��������� ����� ��������� ����������
	index[j] = -1;

	if (free == -1)//���� ������ �������� � ��� ��������� �����
		free = j;
	else
	{
		i = free;
		while (i != -1)
		{
			prev = i;
			i = index[i];
		}
		index[prev] = j;
	}

	size--;
	return true;
}

template <typename T>
bool List<T>::remove(T value)
{
	viewed = 0;
	int i, j = head, prev = head;
	int next;
	bool flag = false;
	for (i = 0; i < size; i++)
	{
		viewed++;
		if (data[j] == value)
		{
			flag = true;
			break;
		}
		prev = j;
		j = index[j];
	}

	if (!flag)
		return false;
	
	if (j == head)//���� ������� ������
	{
		head = index[j];//���������� ������ �� ��������� �������
	}
	//������ �������
	index[prev] = index[j]; //��� ����������� ��������� ����� ��������� ����������
	index[j] = -1;

	if (free == -1)//���� ������ �������� � ��� ��������� �����
		free = j;
	else
	{
		i = free;
		while (i != -1)
		{
			viewed++;
			prev = i;
			i = index[i];
		}
		index[prev] = j;
	}

	size--;
	return true;	
}

template <typename T>
bool List<T>::contains(T value)
{
	viewed = 0;
	int j = head;
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		viewed++;
		if (data[j] == value)
		{
			flag = true;
			return true;
		}
		else
			j = index[j];
	}
	return flag;
}

template <typename T>
T List<T>::get(int ind)
{
	viewed = 0;
	int j = head;
	if (ind >= size)
		throw ArrayException("Invalid index");
	else
	{
		for (int i = 0; i < ind; i++)
		{
			viewed++;
			j = index[j];
		}
	}
	return data[j];
}

template <typename T>
bool List<T>::replace(T value, int ind)
{
	viewed = 0;
	if (ind >= size)
		return false;
	else
	{
		int j = head;
		for (int i = 0; i < ind; i++)
		{
			viewed++;
			j = index[j];
		}
		data[j] = value;
	}
	return true;
}

template <typename T>
int List<T>::indexOf(T value)
{
	viewed = 0;
	int j = head;
	for (int i = 0; i < size; i++)
	{
		viewed++;
		if (data[j] == value)
		{
			return i;
		}
		j = index[j];
	}
	throw ArrayException("Nonexistent element");
}

template <typename T>
int List<T>::getViewedCount()
{
	return viewed;
}