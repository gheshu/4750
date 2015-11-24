#ifndef HASHMAP_H
#define HASHMAP_H

#include <list>
#include <vector>
#include <algorithm>
#include "hash.h"

#ifdef DEBUG
#include <iostream>
#endif

template<typename K, typename V>
struct Pair{
	V value;
	K key;
	Pair(const K& k, const V& v) : value(v), key(k){};
	inline bool operator < (const Pair<K, V>& other){return key < other.key;}
	inline bool operator == (const Pair<K, V>& other){return key == other.key;}
};

template<typename K, typename V>
class HashMap{
	std::list< Pair<K, V> >* data;
	unsigned items, buckets;
public:
	HashMap(unsigned i){
		buckets = std::max(i, (unsigned)4);
		data = new std::list< Pair<K, V> >[buckets];
		items = 0;
	}
	~HashMap(){delete[] data;}
	HashMap(const HashMap& other){
		buckets = other.buckets;
		items = other.buckets;
		data = new std::list< Pair<K, V> >[buckets];
		for(unsigned i = 0; i < buckets; i++){
			for(const auto& j : other.data[i])
				data[i].push_back(j);
		}
	}
	inline void operator=(const HashMap& other){
		delete[] data;
		buckets = other.buckets;
		items = other.buckets;
		data = new std::list< Pair<K, V> >[buckets];
		for(unsigned i = 0; i < buckets; i++){
			for(const auto& j : other.data[i])
				data[i].push_back(j);
		}
	}
	inline unsigned numItems(){return items;}
	inline unsigned numBuckets(){return buckets;}
	inline std::list<Pair<K, V> >& getBucket(const K& key){return data[hash(key) % buckets];}
	inline Pair<K, V>* find(const K& key){
		std::list<Pair<K, V> >& bucket = getBucket(key);
		for(auto& i : bucket){
			if(i.key == key)
				return &i;
		}
		return nullptr;
	}
	inline Pair<K, V>* operator [](const K& key){return find(key);}
	inline void resize(unsigned i){
		unsigned new_buckets = i;
		std::list< Pair<K, V> >* temp = new std::list<Pair<K, V> >[new_buckets]; 
		for(unsigned i = 0; i < buckets; i++){
			for(const auto& j : data[i])
				temp[hash(j.key)%new_buckets].push_back(j);
		}
		delete[] data;
		data = temp;
		buckets = new_buckets;
	}
	inline bool remove(const K& key){
		std::list<Pair<K, V> >& bucket = getBucket(key);
		for(auto i = begin(bucket); i != end(bucket);){
			if(i->key == key){
				bucket.erase(i);
				items--;
				if(items < (buckets >> 2)) resize(items);
				return true;
			}
			++i;
		}
		return false;
	}
	inline bool add(const Pair<K, V>& item){
		std::list<Pair<K, V> >& bucket = getBucket(item.key);
		if(!(bucket.empty() || std::find(begin(bucket), end(bucket), item) == end(bucket)))
			return false;
		bucket.push_back(item);
		items++;
		if(items > (buckets << 1)) resize(buckets * 3);
		return true;
	}
	inline void getPairs(std::vector<Pair<K, V>*>& list){
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(auto& j : data[i])
				list.push_back(&j);
		}
	}
	inline void getValues(std::vector<V*>& list){
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(auto& j : data[i])
				list.push_back(&j.value);
		}
	}
	inline void getKeys(std::vector<K*>& list){
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(auto& j : data[i])
				list.push_back(&j.key);
		}
	}
	inline unsigned collisions(){
		unsigned c = 0;
		for(unsigned i = 0; i < buckets; i++){
			c += (data[i].size() > 1) ? data[i].size() : 0;
		}
		return c;
	}
#ifdef DEBUG
	inline void print(){
		for(unsigned i = 0; i < buckets; i++){
			std::cout << "Bucket: " << i << std::endl;
			for(const auto& j : data[i]){
				std::cout << "	" << j.key << " : " << j.value << std::endl;
			}
		}
	}
#endif
};

#endif
