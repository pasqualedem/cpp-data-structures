#ifndef _BINTREE_
#define _BINTREE_

template <class T,class N>
class Bintree {
	public:
		typedef T value_type;
		typedef N node;
		
		virtual void create() = 0;
		virtual bool empty() const = 0;
		virtual node root() const = 0;
		virtual node parent(node) const = 0;
		virtual node lchild(node) const = 0;
		virtual node rchild(node) const = 0;
		virtual bool lempty(node) const = 0;
		virtual bool rempty(node) const= 0;
	//	virtual void build (Bintree &) = 0;
		virtual void delete_sub(node) = 0;
		virtual value_type read(node) const = 0;
		virtual void write(const value_type&, node) = 0;
		virtual node insert_root () = 0;
		virtual node insert_lchild(node) = 0;
		virtual node insert_rchild(node) = 0;
		
		bool leaf (node u) {
			return (lempty(u) && rempty(u));
		}
		
    	virtual void print(std::ostream&) const;
		virtual int subSize(node, int i = 0) const;
		int node_depth(node) const;
		int height() const;
		int sub_height (node u) const ;
		
	private:
    	virtual void printSubTree(const node,std::ostream&) const;
		
		
};

template <class T, class N>
void Bintree<T,N>::print(std::ostream& out) const{
	if (!empty())
		printSubTree(root(),out);
	else 
		out << "{}";
}

template <class T, class N>
int Bintree<T,N>::subSize(node u, int i) const{
	i++;
	if (!lempty(u))
		i = subSize(lchild(u),i);
	if (!rempty(u))
		i = subSize(rchild(u),i);
	return i;
}

template <class T, class N>
void Bintree<T,N>::printSubTree(const node n,std::ostream& out) const{
	out << "{" << read(n);
	if (!lempty(n)) {
		out << ", ";
		printSubTree(lchild(n),out);
	}
	else out << " , NIL";
	if (!rempty(n)){
		out << ", ";
		printSubTree(rchild(n),out); 
	}
	else out << " , NIL";
	out << " }";
}

template<class T, class N>
std::ostream& operator<<(std::ostream& out, const Bintree<T, N> & t) {
    t.print(out);
    return out;
}

template<class T, class N>
int Bintree<T,N>::node_depth(node u ) const {
	int d = 0;
	while(u->pn != 0x0) {
		u = u->pn;
		d++;
	}
	return d;
}

template<class T, class N>
int Bintree<T,N>::height() const {
	if(empty())
		return 0;
	else
		return sub_height(root());
	
}

template<class T, class N>
int Bintree<T,N>::sub_height(node u) const {
	if(!lempty(u) && !rempty(u)) {
		int l = sub_height(lchild(u));
		int r = sub_height(rchild(u));
		if(l>r)
			return l+1;
		else
			return r+1;
	}
	else if (!lempty(u))
		return sub_height(lchild(u))+1;
	else if (!rempty(u))
		return sub_height(rchild(u))+1;
	return 1;
}

template <class T, class N>
void mutation (Bintree<T,N> & b ,Bintree<T,N>  & t , typename Bintree<T,N>::node u, typename Bintree<T,N>::node v) {
	T tmp;
	tmp = b.read(u);
	b.write(t.read(v),u);
	t.write(tmp,v);
	if(!b.lempty(u) && !t.lempty(v)) 
		mutation(b,t, b.lchild(u),t.lchild(v));
	else if (!b.lempty(u) && t.lempty(v)) {
		t.insert_lchild(v);
		mutation(b,t, b.lchild(u),t.lchild(v));
		b.delete_sub(b.lchild(u));
	}
	else if (b.lempty(u) && !t.lempty(v)) {
		b.insert_lchild(u);
		mutation(b,t, b.lchild(u),t.lchild(v));
		t.delete_sub(t.lchild(v));
	}	
	
	if(!b.rempty(u) && !t.rempty(v)) 
		mutation(b,t, b.rchild(u),t.rchild(v));
	else if (!b.rempty(u) && t.rempty(v)) {
		t.insert_rchild(v);
		mutation(b,t, b.rchild(u),t.rchild(v));
		b.delete_sub(b.rchild(u));
	}
	else if (b.rempty(u) && !t.rempty(v)) {
		b.insert_rchild(u);
		mutation(b,t, b.rchild(u),t.rchild(v));
		t.delete_sub(t.rchild(v));
	}
	
} 

#endif
