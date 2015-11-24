#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>
#include <algorithm>

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


inline unsigned hash(unsigned x){
    return x;
}

//http://stackoverflow.com/a/107657
inline unsigned hash(const std::string& x){
	unsigned v = 0;
	for(unsigned char i : x){
		v = v * 101 + (unsigned)i;
	}
}

template<typename K, typename V>
class HashMap{
	std::vector< Pair<K, V> >* data;
	unsigned items, buckets;
public:
	HashMap(unsigned i){
		buckets = i;
		data = new std::vector< Pair<K, V> >[buckets];
		items = 0;
	}
	~HashMap(){delete[] data;}
	HashMap(const HashMap& other){
		buckets = other.buckets;
		items = other.buckets;
		data = new std::vector< Pair<K, V> >[buckets];
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < other.data[i].size(); j++){
				data[i].push_back(other.data[i][j]);
			}
		}
	}
	inline void operator=(const HashMap& other){
		delete[] data;
		buckets = other.buckets;
		items = other.buckets;
		data = new std::vector< Pair<K, V> >[buckets];
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < other.data[i].size(); j++){
				data[i].push_back(other.data[i][j]);
			}
		}
	}
	inline unsigned numItems(){return items;}
	inline unsigned numBuckets(){return buckets;}
	inline std::vector<Pair<K, V> >& getBucket(const K& key){return data[hash(key) % buckets];}
	inline Pair<K, V>* find(const K& key){
		std::vector<Pair<K, V> >& bucket = getBucket(key);
		for(unsigned i = 0; i < bucket.size(); i++){
			if(bucket[i].key == key){
				return &bucket[i];
			}
		}
		return nullptr;
	}
	inline Pair<K, V>* operator [](const K& key){return find(key);}
	inline void resize(){
		unsigned new_buckets = items * 2;
		std::vector< Pair<K, V> >* temp = new std::vector<Pair<K, V> >[new_buckets]; 
		for(unsigned i = 0; i < buckets; i++){
			for(auto k : data[i]){
				temp[hash(k.key)%new_buckets].push_back(k);
			}
		}
		delete[] data;
		data = temp;
		buckets = new_buckets;
	}
	inline bool remove(const K& key){
		std::vector<Pair<K, V> >& bucket = getBucket(key);
		for(unsigned i = 0; i < bucket.size(); i++){
			if(bucket[i].key == key){
				bucket.erase(bucket.begin() + i);
				items--;
				if(items < (buckets >> 3)) resize();
				return true;
			}
		}
		return false;
	}
	inline bool add(const Pair<K, V>& item){
		std::vector<Pair<K, V> >& bucket = getBucket(item.key);
		for(unsigned i = 0; i < bucket.size(); i++){
			if(bucket[i].key == item.key){
				return false;
			}
		}
		bucket.push_back(item);
		items++;
		if(items > buckets) resize();
		return true;
	}
	inline void getPairs(std::vector< Pair<K, V>* >& list){
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < data[i].size(); j++){
				list.push_back(&data[i][j]);
			}
		}
	}
	inline void getValues(std::vector<V*>& list){
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < data[i].size(); j++){
				list.push_back(&data[i][j].value);
			}
		}
	}
	inline void getKeys(std::vector<K*>& list){
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < data[i].size(); j++){
				list.push_back(&data[i][j].key);
			}
		}
	}
#ifdef DEBUG
	inline void print(){
		for(unsigned i = 0; i < buckets; i++){
			std::cout << "Bucket: " << i << std::endl;
			for(auto j : data[i]){
				std::cout << "	" << j.key << " : " << j.value << std::endl;
			}
		}
	}
#endif
};

#endif
