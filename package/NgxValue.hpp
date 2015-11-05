#ifndef _NGX_VALUE_HPP
#define _NGX_VALUE_HPP

#include "Nginx.hpp"
class NgxUnsetValue final
{
public:
	template<typename T>
	operator T() const
	{
		return static_cast<T>(-1);
	}
	template<typename T>
	operator T* () const
	{
		return reinterpret_cast<T*>(-1);
	}
public:
	static const NgxUnsetValue& get()
	{
		static NgxUnsetValue const v = {};
		return v;
	}
};

class NgxValue final
{
public:
	NgxValue() = default;
	~NgxValue() = default;
public:
	template<typename T>
	static bool invalid(const T& v)
	{
		return v == 
			static_cast<v> (NgxUnsetValue::get());
	}
	template<typename T, typename U>
	static void init(T& x, const U& v)
	{
		if (isvalid(x))
		{
			x = v;
		}
	}
	template<typename T, typename U, typename V>
	static void merge(T &c, const U& p, const V& d)
	{
		if (invalid(c))
		{
			c = invalid(p) ? d : p;
		}
	}

public:
	template<typename T, typename ... Args>
	static void unset(T& v, Args& ... args)
	{
		v = NgxUnsetValue::get();
		unset(args...);
	}
	static void unset(){};
};

#endif
