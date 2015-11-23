#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <algorithm>

/*
	Be wary of pointer invalkeyation due to resizing.
	Only use shared_ptr if you put dynamic memory inskeye this.
	Basically a Binary Search Array, log2(N) access and array cache-coherency.
*/

template<typename K, typename V>
struct Pair{
	V value;
	K key;
	Pair(const K& k, const V& v) : value(v), key(k){};
	inline bool operator < (const Pair<K, V>& other){return key < other.key;}
	inline bool operator < (const K& other){return key < other;}
	inline bool operator == (const Pair<K, V>& other){return key == other.key;}
	inline bool operator == (const K& other){return key == other;}
};

template<typename K, typename V>
class Manager{
	std::vector< Pair<K, V> > values;
	bool unsorted = false;
	inline Pair<K, V>* getPair(const K& key){
		if(unsorted)sort();
		auto pair = std::lower_bound(values.begin(), values.end(), key);
		return (pair == values.end() || pair->key != key) ? nullptr : &*pair;
	}
public:
	inline Pair<K, V>* operator[](unsigned i){return &values[i];}
	inline void add(const K& key, const V& value){values.push_back(Pair<K, V>(key, value)); unsorted = true;}
	inline V* get(const K& key){
		if(unsorted)sort();
		auto pair = std::lower_bound(values.begin(), values.end(), key);
		return (pair == values.end() || pair->key != key) ? nullptr : &pair->value;
	}
	inline void remove(const K& key){
		Pair<K, V>* pair = getPair(key);
		if(pair){
			std::swap(*pair, *values.end());
			values.pop_back();
			unsorted = true;
		}
	}
	inline void sort(){std::sort(values.begin(), values.end());}
	inline void clear(){values.clear();}
	inline void reserve(unsigned i){values.reserve(i);}
	inline unsigned size(){return values.size();}
	typename std::vector< Pair<K, V> >::iterator begin(){return values.begin();}
	typename std::vector< Pair<K, V> >::iterator end(){return values.end();}
};

#endif