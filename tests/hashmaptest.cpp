#include "../hashmap.h"
#include <iostream>
#include <iomanip>
#include "time.h"
#include <random>
using namespace std;
int main(){
	srand(time(NULL));
	HashMap<unsigned, unsigned> hm(0);
	float avg_load = 0.0f, avg_col = 0.0f;
	unsigned resizes = 0;
	//unsigned a[]={0,1,2,3,4,5,6,7,8,9,10,10,9,8,7,6,5,4,3,2,1,0};
	//unsigned b[]={3,1,4,1,5,9,2,8,6,5,7,8,9,10,15,200,32,18,19,20,21,22};
	#define STATISTICS \
	float new_load = (size == 0) ? 0.0f : (float)hm.numItems()/(float)size;	\
	float new_col = (hm.numItems() == 0) ? 0.0f : (float)hm.collisions() / (float)hm.numItems();	\
	avg_load += new_load;	\
	avg_col += 	new_col;\
	if(hm.numItems() > 0) resizes++;	\
	cout << "load: " << setw(10) << new_load << " collisions per item: " << setw(10) << new_col << endl;
	unsigned size = hm.numBuckets();
	for(unsigned i = 0; i < 1000000; i++){
		unsigned j = rand();
		if(rand()%2)
			hm.add({j, j});
		else
			hm.remove(j);
		if(size != hm.numBuckets()){
			size = hm.numBuckets();
			STATISTICS
		}
	}
	//hm.print();
	std::vector<unsigned*> keys;
	hm.getKeys(keys);
	std::vector<unsigned*> values;
	hm.getValues(values);
	/*
	for(unsigned i = 0; i < 20; i++)
		cout << *keys[i] << " ";
	cout << endl;
	for(unsigned i = 0; i < 20; i++)
		cout << *values[i] << " ";
	cout << endl;
	for(unsigned i = 0; i < keys.size(); i++){
		auto j = hm[*keys[i]];
		cout << j->key << " : " << j->value << endl;
	}
	*/
	STATISTICS
	cout << "avg_load: " << setw(10) << avg_load / resizes << " avg_col: " << setw(10) << avg_col / resizes << endl;
	//hm.print();
	HashMap<unsigned, unsigned> hm2(hm);
	//hm2.print();
	HashMap<unsigned, unsigned> hm3(5);
	hm3 = hm2;
	//hm3.print();
	
	return 0;
}