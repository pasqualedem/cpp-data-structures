#ifndef _SET_
#define _SET_

template <class T>
class Set {
	public:
		typedef T value_type;
		
		virtual void create() = 0;
		virtual bool empty() = 0;
		virtual bool member(const value_type &) const = 0;
		virtual void erase (const value_type &) = 0;
		virtual void add (const value_type &) = 0;
		
		virtual value_type read() const = 0;
		
		int size() {
			return _size;
		}
		
	protected:
		int _size;
	
};




#endif
