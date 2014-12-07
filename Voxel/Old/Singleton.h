#ifndef SINGLETON_H
#define SINGLETON_H

template <class T> 
class Singleton
{
public:
	static T& GetInstance()
	{
		if(p == 0)
			p = new T;
		return *p; 
	}
protected:
	static T* p;
};
template <class T>
T* Singleton<T>::p = 0;

#endif