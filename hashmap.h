#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>
#include <algorithm>

#include <iostream>

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
	bool lock = false;
public:
	HashMap(unsigned i){
		lock = true;
		buckets = i;
		data = new std::vector< Pair<K, V> >[buckets];
		items = 0;
		lock = false;
	}
	~HashMap(){delete[] data;}
	HashMap(const HashMap& other){
		lock = true;
		buckets = other.buckets;
		items = other.buckets;
		load = (float) items / (float) buckets;
		data = new std::vector< Pair<K, V> >[buckets];
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < other.data[i].size(); j++){
				data[i].push_back(other.data[i][j]);
			}
		}
		lock = false;
	}
	void operator=(const HashMap& other){
		while(lock);
		lock = true;
		delete[] data;
		buckets = other.buckets;
		items = other.buckets;
		load = (float) items / (float) buckets;
		data = new std::vector< Pair<K, V> >[buckets];
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < other.data[i].size(); j++){
				data[i].push_back(other.data[i][j]);
			}
		}
		lock = false;
	}
	inline unsigned numItems(){return items;}
	inline unsigned numBuckets(){return buckets;}
	inline float loadAmt(){return load;}
	inline std::vector<Pair<K, V> >& getBucket(const K& key){return data[hash(key) % buckets];}
	inline Pair<K, V>* find(const K& key){
		while(lock);
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
		while(lock);
		lock = true;
		std::vector<Pair<K, V> >& bucket = getBucket(key);
		for(unsigned i = 0; i < bucket.size(); i++){
			if(bucket[i].key == key){
				bucket.erase(bucket.begin() + i);
				items--;
				load = (float)items / (float)buckets;
				if(load < 0.1f) resize();
				lock = false;
				return true;
			}
		}
		lock = false;
		return false;
	}
	inline bool add(const Pair<K, V>& item){
		while(lock);
		lock = true;
		std::vector<Pair<K, V> >& bucket = getBucket(item.key);
		for(unsigned i = 0; i < bucket.size(); i++){
			if(bucket[i].key == item.key){
				lock = false;
				return false;
			}
		}
		bucket.push_back(item);
		items++;
		load = (float)items / (float)buckets;
		if(load > 1.0f) resize();
		lock = false;
		return true;
	}
	inline void getPairs(std::vector< Pair<K, V>* >& list){
		while(lock);
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < data[i].size(); j++){
				list.push_back(&data[i][j]);
			}
		}
	}
	inline void getValues(std::vector<V*>& list){
		while(lock);
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < data[i].size(); j++){
				list.push_back(&data[i][j].value);
			}
		}
	}
	inline void getKeys(std::vector<K*>& list){
		while(lock);
		list.clear();
		list.reserve(items);
		for(unsigned i = 0; i < buckets; i++){
			for(unsigned j = 0; j < data[i].size(); j++){
				list.push_back(&data[i][j].key);
			}
		}
	}
	inline void print(){
		for(unsigned i = 0; i < buckets; i++){
			std::cout << "Bucket: " << i << std::endl;
			for(auto j : data[i]){
				std::cout << "	" << j.key << " : " << j.value << std::endl;
			}
		}
	}
};

#endif