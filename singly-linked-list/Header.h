#pragma once
#include <iostream>

using namespace std;

class ArrayException : public std::exception
{
private:
	std::string m_error;
public:
	ArrayException(std::string error) : m_error(error) {}
	// Возвращаем std::string в качестве константной строки C-style
	const char* what() const noexcept { return m_error.c_str(); } // C++11 и позднее
};

template <typename T>
class List
{
	int *index; //массив индексов
	T *data;//массив данных
	int head, free; //указатели на голову и на первфй свободный
	int size; //размер списка
	int capacity; //размер массива
	int viewed = 0; //количество просмотрнных узлов

public:
	List();
	List(int N);
	List(const List<T> & L);
	~List();

	int getSize();                    
	void clear();                       
	bool isEmpty();                     
	bool contains(T value);       //опрос наличия заданного значения      
	T get(int index);            
	bool replace(T value, int index);   //изменение значения с заданным номером
	int indexOf(T value);               
	bool add(T value);                  
	bool add_pos(T value, int index);       
	bool remove(T value);               
	bool removeAt(int ind);                           
	int getViewedCount();
	void print();

	class Iterator {
		List<T>* arr; //указатель на список
		int cur; //Указатель на текущий элемент последовательности
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
		T& operator *() //доступ к данным текущего элемента
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

	Iterator begin() //получение итератора begin( )
	{
		Iterator iter(this, head);
		return iter;
	}

	Iterator end() //получение итератора end( )
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
	while (i != -1) //находим последний элемент
	{
		viewed++;
		prev = i;
		i = index[i];
	}
	if (size == 0)
		head = free;
	free = index[free]; // сдвигаем голову списка свободных место на новое место
	index[prev] = temp_free; // сдвигаем индекс последнего на новый добавленный
	index[temp_free] = -1; //элемент добавлен в конец, поэтому ни на кого не ссылается
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

	if (ind == head)//есди добавляем в голову
	{
		next = head;
		head = free;
	}
	else
	{
		next = index[prev]; //индекс элемента, который стоит в позиции ind
		index[prev] = free; //индекс предыдущего указывает на новый
	}
	free = index[free]; //передвигаем голову списка свободных на следующий элемент
	index[oldfree] = next;//добавленный элемен указывает на элемент, стоявший в позиции ind

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

	if (j == head)//если удаляем голову
	{
		head = index[j];//перемещаем голову на следующий элемент
	}
	//меняем индексы
	index[prev] = index[j]; //для предыдущего следующим будет следующий удаляемого
	index[j] = -1;

	if (free == -1)//если список заполнен и нет свободных ячеек
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
	
	if (j == head)//если удаляем голову
	{
		head = index[j];//перемещаем голову на следующий элемент
	}
	//меняем индексы
	index[prev] = index[j]; //для предыдущего следующим будет следующий удаляемого
	index[j] = -1;

	if (free == -1)//если список заполнен и нет свободных ячеек
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