#pragma once

template <class T>
class Singleton
{
protected:
	static T * Instance;
public:
	Singleton();
	static T *getInstance();
	virtual ~Singleton();
};

template<class T>
T *Singleton<T>::Instance = nullptr;

template<class T>
Singleton<T>::Singleton()
{
	Instance = static_cast<T *>(this);
}

template<class T>
T * Singleton<T>::getInstance()
{
	return Instance;
}

template<class T>
Singleton<T>::~Singleton()
{
	Instance = nullptr;
}
