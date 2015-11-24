#ifndef HASH_H
#define HASH_H

#include <climits>
#include <string>

inline unsigned hash(int x){
	return (unsigned)((x & INT_MAX) * 0xFB);
}
inline unsigned hash(unsigned x){
    return x * 0xFB;
}
inline unsigned hash(char x){
	return (unsigned)((x & CHAR_MAX) * 0xFB);
}
inline unsigned hash(unsigned char x){
	return (unsigned)(x * 0xFB);
}
inline unsigned hash(short x){
	return (unsigned)((x & SHRT_MAX) * 0xFB);
}
inline unsigned hash(unsigned short x){
	return (unsigned)(x * 0xFB);
}

//http://stackoverflow.com/a/107657
inline unsigned hash(const std::string& x){
	unsigned v = 0;
	for(unsigned char i : x){
		v = v * 101 + (unsigned)i;
	}
	return v;
}

#endif