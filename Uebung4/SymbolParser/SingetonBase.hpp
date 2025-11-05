/*****************************************************************//**
 * \file   SingetonBase.hpp
 * \brief  
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef SINGLETON_BASE_HPP
#define SINGLETON_BASE_HPP

#include "Object.h"
#include <memory>

template <typename T> class SingletonBase : public Object {
public:
	static T& GetInstance() {
		if (mInstance == nullptr) { mInstance = std::unique_ptr<T>{ new T{} }; };
		return *mInstance;
	}
protected:
	SingletonBase() = default;
	virtual ~SingletonBase() = default;

private:
	SingletonBase(SingletonBase const& s) = delete;
	SingletonBase& operator = (SingletonBase const& s) = delete;
	static std::unique_ptr<T> mInstance;
};

template <typename T> std::unique_ptr<T> SingletonBase<T>::mInstance = nullptr;

#endif // !SINGLETON_BASE_HPP
