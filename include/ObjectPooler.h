#pragma once
#include <queue>

template<typename T>
class ObjectPooler
{
public:

	//Contructores
	ObjectPooler();
	ObjectPooler(const size_t N);
	~ObjectPooler();
	//Metodos

	T* get_one();
	void add_one();
	void add_one(T* object);

private:

	std::queue<T*> m_queue;


};



//Contructores
template<typename T>
ObjectPooler<T>::ObjectPooler()
{
	this->m_queue = std::queue<T*>();
	for (size_t i = 0; i < 1; i++)
	{
		m_queue.push(new T());

	}

};

template<typename T>
ObjectPooler<T>::ObjectPooler(const size_t N)
{
	
	this->m_queue = std::queue<T*>();
	for (size_t i = 0; i < N; i++)
	{
		m_queue.push(new T());

	}

}

template<typename T>
ObjectPooler<T>::~ObjectPooler()
{
	/*while (!m_queue.empty()) {
		T* ptr = m_queue.front();
		m_queue.pop();
		delete ptr;
	}*/
};

template<typename T>
T* ObjectPooler<T>::get_one()
{
	if(this->m_queue.empty())
	{
		this->add_one();

	}

	T* aux = m_queue.front();
	m_queue.pop();

	return aux;
};

template<typename T>
void ObjectPooler<T>::add_one()
{
	m_queue.push(new T());
};

template<typename T>
void ObjectPooler<T>::add_one(T* object)
{
	m_queue.push(object);
};

