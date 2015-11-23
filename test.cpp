#include "hashmap.h"
#include <iostream>

using namespace std;

int main(){
	HashMap<unsigned, int> hm(3);
	int v[] = {1, 1, 2, 1, 3, 5, 76, 72, 432, 2 , 1};
	unsigned k[] = {0, 1, 1, 3, 2, 5, 6, 7, 8765, 322, 111};
	hm.print();
	for(int i = 0; i < 11; i++){
		if(hm.add(Pair<unsigned, int>(k[i], v[i]))){
			cout << k[i] << " : " << v[i] << " added\n";
		}
	}
	hm.print();
	for(int i = 0; i < 10; i++){
		if(hm.remove(k[i]))
			cout << k[i] << " removed\n";
	}
	std::vector< Pair<unsigned, int>* > list;
	hm.getPairs(list);
	cout << "Num items: " << hm.numItems() << endl;
	cout << "Num Buckets: " << hm.numBuckets() << endl;
	cout << "Load: " << hm.loadAmt() << endl;
	cout << "Iterator list size: " << list.size() << endl;
	for(auto i : list){
		cout << i->key << " : " << i->value << endl;
	}
	hm.print();

	return 0;
}