#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <algorithm>

template<typename S>
class IDType{
public:
	S item;
	unsigned id;
	IDType(const S& i, unsigned _id) : item(i), id(_id){};
	inline bool operator < (const IDType<S>& other){ return id < other.id;}
};

template<typename T>
class Manager{
	std::vector< IDType<T> > items;
	inline IDType<T>* getIDType(unsigned i){
		auto item = std::lower_bound(items.begin(), items.end(), i);
		return (item == items.end() || item->id != i) ? nullptr : item;
	}
public:
	inline IDType<T>& operator[](unsigned i){return items[i];}
	inline void add(const T& item, unsigned id){items.push_back(IDType<T>(item, id));sort();}
	inline T* get(unsigned i){
		auto item = std::lower_bound(items.begin(), items.end(), i);
		return (item == items.end() || item->id != i) ? nullptr : &item->item;
	}
	inline void remove(unsigned i){
		IDType<T>* iditem = getIDType(i);
		if(iditem){
			std::swap(*iditem, *items.end());
			items.pop_back();
		}
		sort();
	}
	inline void sort(){std::sort(items.begin(), items.end());}
	inline void clear(){items.clear();}
	inline void reserve(unsigned i){items.reserve(i);}
	inline unsigned size(){return items.size();}
	typename std::vector< IDType<T> >::iterator begin(){return items.begin();}
	typename std::vector< IDType<T> >::iterator end(){return items.end();}
};

#endif