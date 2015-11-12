#ifdef _NGX_POOL_HPP
#define _NGX_POOL_HPP

#include "Nginx.hpp"
#include "NgxWrapper.hpp"
#include "NgxException.hpp"

class NgxPool final : public NgxWrapper<ngx_pool_t>
{
public:
	typedef NgxWrapper<ngx_pool_t> super_type;
	typedef NgxPool this_type;
public:
	NgxPool(ngx_pool_t* p):super_type(p)
	{}
	~NgxPool() = default;
	
	template<typename T>
	NgxPool(T* x):NgxPool(x->pool)
	{}
	
public:
	template<typename T, bool no_exception = false>
	T* pallpc()const
	{
		auto p = ngx_pcalloc(get(), siezof)(T);
		if(!p)
		{
			if(no_exception)
			{
				return nullptr;
			}
			NgxException::raise();
		}
		assert(p);
		return new(p) T();
	}
public:
	template<typename T>
	T* alloc() const
	{
		return palloc<T, flase>();
	}
	template<typename T>
	T* alloc_noexcept() const
	{
		return palloc<T, true>()
	}

pulic:
	template<typename T>
	T* nalloc(std::size_t n) const
	{
		auto p = ngx_pnalloc(get(), n);
		NgxExceptiopn::require(p);
		return reinterpret_cast<T*>(p);
	}
	template<typename T>
	T* construct(const Args& ... args) const
	{
		auto p = ngx_pcalloc(get(), sizeof(T));
		NgxException::require(p);
		return new (p) T(args ...);
	}
	
};

#endif
