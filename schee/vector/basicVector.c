/* 
 ___  ___  ___  ___      ___ _______
|\  \|\  \|\  \|\  \    /  /|\  ___ \
\ \  \\\  \ \  \ \  \  /  / | \   __/|
 \ \   __  \ \  \ \  \/  / / \ \  \_|/
  \ \  \ \  \ \  \ \    / /   \ \  \_|\ \ ___
   \ \__\ \__\ \__\ \__/ /     \ \_______\\__\
 ___\|__|\|__|\|__|\|__|/_____  \|_______\|__|
|\___   ___\\  ___ \ |\   ____\|\  \|\  \
\|___ \  \_\ \   __/|\ \  \___|\ \  \\\  \
     \ \  \ \ \  \_|/_\ \  \    \ \   __  \
      \ \  \ \ \  \_|\ \ \  \____\ \  \ \  \
       \ \__\ \ \_______\ \_______\ \__\ \__\
        \|__|  \|_______|\|_______|\|__|\|__|                
        
        Copyright © 2015 - Hive.Tech - Tyler McKay Hall
            tyler@hive.technology
             www.hive.technology

  This software is not intended for redistribution, as such it is not fully
  documented or gaurenteed. All rights reserved for use and publication. Permission 
  will be given to those who reasonably request. 

    ** More information can be found at www.hive.technology/copywright ** 

  Please contact, any questions will be gladly answered. Thank you for your understanding.


Building a vector
==============================================
Attempt at building a vector arry in C from scratch.

== Requirements ==
- Should emulate the basics of vector in C++
- Keep generic for all data types
    + Keep pointers to pointers = Read the content from that pointer
- Handle large amounts of arrays
- Resizing options + Should be able to add/or multiply to grow/shrink
    + That way options can be kept for differnt use cases

== Required Functions ==
[x] - Initalize
[x] - Expand - Grow to a new size
[x] - Add items - Depending on data type? Double at first?
[ ] - Delete items - Delete/shift


== For Later ==
[ ] - Shrink - If less than half full, shrink by 1/4
[ ] - Handle other data types other than just stirngs

*/

/* Preprocessing */
#include <stdio.h>
#include <stdlib.h>

/* Declarations */

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


/* functionmain begins program execution */
int main(int argc, char const *argv[])
{
	/* code */

  //Make New Dynamic Array
  struct dynamicArray test;

  _dynamicArray(&test, 6, 2);
  printf("Max size: %d\n", test.totalSize);
  printf("Multiplier: %d\n", test.resizer);

  addTo_dynamicArray(&test, "one");
  addTo_dynamicArray(&test, "two");
  addTo_dynamicArray(&test, "three");
  addTo_dynamicArray(&test, "four");
  addTo_dynamicArray(&test, "five");
  addTo_dynamicArray(&test, "six");
  addTo_dynamicArray(&test, "seven");

  printf("%s\n%s\n%s\n", (char*)test.entries[0], (char*)test.entries[1], (char*)test.entries[2]);
  printf("%s\n%s\n%s\n", (char*)test.entries[3], (char*)test.entries[4], (char*)test.entries[5]);
  printf("%s\n", (char*)test.entries[6]);

	return 0; /* indicate that program ended successfully */
} /* End Main */


void _dynamicArray(dynamicArray * init, int startSize, int resiz){
  //Initalize all variables to a default
  (*init).resizer = resiz;
  (*init).currentCount = 0;
  (*init).totalSize = startSize;
  (*init).entries = malloc(sizeof(void *) * (*init).totalSize);
}

void addTo_dynamicArray(dynamicArray* addTo, void *entry){
  //Sanity check to see if resize is needed
  if ((*addTo).totalSize == (*addTo).currentCount){
    resize_dynamicArray(addTo);
  }
  //Increment to next in array
  (*addTo).entries[addTo->currentCount++] = entry;
}

static void resize_dynamicArray (dynamicArray * toResize){
  
  int pushSize = toResize->totalSize + toResize->resizer;
  //printf("Resize: %d\n", pushSize);

  //Temporary Pointer with the resized memory
  void **tempPoint = realloc(toResize->entries, sizeof(void*) * (toResize->totalSize + toResize->resizer));
  
  //Check to see if pointer allocation is set
  if (tempPoint != NULL){
    (*toResize).entries = tempPoint;
    (*toResize).totalSize = pushSize;
  }
}

void * getIndex_dynamicArray (dynamicArray * arrayGet, int index){
  //Sanity check - make sure its in range
  if (index < 0 || index > arrayGet->totalSize){
    return (*arrayGet).entries[index];
  }
  return NULL;
}





