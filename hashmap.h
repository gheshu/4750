#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>
#include <algorithm>

template<typename K, typename V>
struct Pair{
	V value;
	K key;
	Pair(const K& k, const V& v) : value(v), key(k){};
	inline bool operator < (const Pair<K, V>& other){return key < other.key;}
	inline bool operator == (const Pair<K, V>& other){return key == other.key;}
};

//http://stackoverflow.com/a/12996028
inline unsigned hash(unsigned x){
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}
//http://stackoverflow.com/a/107657
inline unsigned hash(const std::string& x){
	unsigned v = 0;
	for(unsigned char i : x){
		v = v * 101 + (unsigned)i;
	}
	return v;
}

template<typename K, typename V>
class HashMap{
	std::vector< Pair<K, V> >* data;
	unsigned items, buckets;
	float load;
	HashMap(unsigned i){
		buckets = i;
		data = new std::vector< Pair<K, V> >[buckets];
		items = 0;
	}
	~HashMap(){delete[] data;}
	inline std::vector<Pair<K, V> >& getBucket(const K& key){return data[hash(key) % buckets];}
	inline Pair<K, V>* find(const K& key){
		auto bucket = getBucket(key);
		auto i = std::find(bucket.begin(), bucket.end(), key);
		if(i == bucket.end()) return nullptr;
		return &*i;
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
		auto bucket = getBucket(key);
		auto i = std::find(bucket.begin(); bucket.end(), key);
		if(i == bucket.end()) return false;
		bucket.erase(i);
		items--;
		load = (float)items / (float)data.capacity();
		if(load < 0.1f) resize();
		return true;
	}
	inline bool add(const Pair<K, V>& item){
		auto bucket = getBucket(key);
		auto i = std::find(bucket.begin(), bucket.end(), item.key);
		if(i != bucket.end()) return false;
		bucket.push_back(item);
		items++;
		load = (float)items / (float)data.capacity();
		if(load > 1.0f) resize();
		return true;
	}
};

#endif