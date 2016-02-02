
#ifndef FULLVECTOR_H
#define FULLVECTOR_H

typedef  struct dynamicArray
{
  void **entries;
  int currentCount;
  int totalSize;
  int resizer;

} dynamicArray;


/*Initalize the dynamic array*/
/*Params - type (*) - array to initalize, initial size*/
void _dynamicArray(dynamicArray*, int, int);

/*Initalize the dynamic array*/
/*Params - type (*) - array to add to, entry to add*/
void addTo_dynamicArray(dynamicArray*, void *);

/*resize the array - NOT to be used manually, will be called by nessisary functions*/
/*Params - type (*) - array to resize*/
static void resize_dynamicArray (dynamicArray *);

/*get index*/
/*Params - type (*, int) - array to get, index*/
void* getIndex_dynamicArray (dynamicArray *, int);

/*set index*/
/*Params - type (*, int) - array to get, index, entry value*/
void setIndex_dynamicArray (dynamicArray *, int, void *);

#endif