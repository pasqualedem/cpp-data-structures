#ifndef _LINEARLISTORD_H
#define _LINEARLISTORD_H

#include "Linear_list.h"


template< class T, class P >
class Linear_list_ord : public Linear_list<T,P> {
public:
	typedef typename Linear_list<T,P>::value_type value_type;
	typedef typename Linear_list<T,P>::position position;
	virtual void insert (const value_type &) = 0;
protected:
	using Linear_list<T, P>::_length;
};

#endif // _LISTALIN_H
