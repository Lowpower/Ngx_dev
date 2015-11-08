#ifndef _NGX_WRAPPER_HPP
#define _NGX_WRAPPER_HPP

#include "Nginx.hpp"
#include <boost/type_traits.hpp>


template<typename T>

class NgxWrapper
{
	public:
		typedef typename boost::remove_pointer<T>::type wrapper_type;
		typedef wrapper_type* point_type;
		typedef wrapper_type& reference_type;
	private:
		pointer_type m_ptr = nullptr;
	
	protected:
		NgxWrapper(point_type p):p_ptr(p)
		{}
		NgxWrapper(reference_type x):m_ptr(&x)
		{}
		~NgxWrapper() = default;

	public:
		pointer_type get() const
		{
			return m_ptr;
		}
		operator bool () const
		{
			return get();
		}
		pointer_type operator->() const
		{
			return get();
		}
		operator pointer_type () const
		{
			return get();
		}
};

#endif
