#ifndef _NGX_EXCEPT_HPP
#define _NGX_EXCEPT_HPP

#include <string>
#include <exception>
#include <boost/exception/all.hpp>
#include <boost/utility/string_ref.hpp>

#include "Nginx.hpp"

class Exception final : public virtual std::exception,
						public virtual boost::exception
{
public:
	typedef boost::string_ref string_ref_type;
private:
	ngx_int_t m_code = NGX_ERROR;
	std::string m_msg;
public:
	NgxException(ngx_int_t, string_ref_type msg):
				m_code(x), m_msg(msg)
	{}
	NgxException(ngx_int_t = NGX_ERROR):
		NgxException(x, "")
	{}
	NgxException(string_ref_type msg):
		NgxException(NGX_ERROR, msg)
	{}
	virtual ~NgxException() noexcept
	{}

public:
	ngx_int_t code() const
	{
		return m_code;
	}
	virtual const char* what() const noexcept override
	{
		return m_msg.c_str();
	}

public:
	static void raise(ngx_int_t rc = NGX_ERROR, string_ref_type msg = "")
	{
		throw NgxException(rc, msg);
	}
	static void require(bool cond, ngx_int_t e = NGX_ERROR)
	{
		if(!cond)
		{
			raise(e);
		}
	}
	static void require(ngx_int_t rc, ngx_int_t x = NGX_OK)
	{
		require(rc == x, rc);
	}
	template<typename T>
	static void require(T* p, ngx_int_t e = NGX_ERROR)
	{
		require(p!= nullptr, e);
	}
public:
	static void fail(bool cond, ngx_int_t e = NGX_ERROR)
	{
		if(cond)
		{
			raise(e);
		}
	}
};

#endif
