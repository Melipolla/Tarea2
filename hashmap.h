#ifndef hashmap_h
#define hashmap_h

typedef struct Pair Pair;
typedef struct HashMap HashMap;

Pair * createPair( char * key,  void * value);

long hash( char * key, long capacity);

int is_equal(void* key1, void* key2);

void enlarge(HashMap * map);

void insertMap(HashMap * map, char * key, void * value);

HashMap * createMap(long capacity);

void eraseMap(HashMap * map,  char * key);

Pair * searchMap(HashMap * map,  char * key);

Pair * firstMap(HashMap * map);

Pair * nextMap(HashMap * map);

#endif