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



== Might as well make it like C++ vectors for consistancy ==
-- From http://www.cplusplus.com/reference/vector/vector/ --
Member functions
(constructor)
Construct vector (public member function )
(destructor)
Vector destructor (public member function )
operator=
Assign content (public member function )

Iterators:
[ ] - begin - Return iterator to beginning (public member function )
[ ] - end - Return iterator to end (public member function )
[ ] - rbegin - Return reverse iterator to reverse beginning (public member function )
[ ] - rend - Return reverse iterator to reverse end (public member function )
[ ] - cbegin - Return const_iterator to beginning (public member function )
[ ] - cend  - Return const_iterator to end (public member function )
[ ] - crbegin - Return const_reverse_iterator to reverse beginning (public member function )
[ ] - crend  - Return const_reverse_iterator to reverse end (public member function )

Capacity:
[ ] - size - Return size (public member function )
[ ] - max_size - Return maximum size (public member function )
[ ] - resize - Change size (public member function )
[ ] - capacity - Return size of allocated storage capacity (public member function )
[ ] - empty - Test whether vector is empty (public member function )
[ ] - reserve - Request a change in capacity (public member function )
[ ] - shrink_to_fit  - Shrink to fit (public member function )

Element access:
[ ] - operator[] - Access element (public member function )
[ ] - at - Access element (public member function )
[ ] - front - Access first element (public member function )
[ ] - back - Access last element (public member function )
[ ] - data  - Access data (public member function )

Modifiers:
[ ] - assign - Assign vector content (public member function )
[ ] - push_back - Add element at the end (public member function )
[ ] - pop_back - Delete last element (public member function )
[ ] - insert - Insert elements (public member function )
[ ] - erase - Erase elements (public member function )
[ ] - swap - Swap content (public member function )
[ ] - clear - Clear content (public member function )
[ ] - emplace  - Construct and insert element (public member function )
[ ] - emplace_back  - Construct and insert element at the end (public member function )

Allocator:
[ ] - get_allocator - Get allocator (public member function )

Non-member function overloads
relational operators - Relational operators for vector (function template )
[ ] - swap - Exchange contents of vectors (function template )

Template specializations
[ ] - vector<bool> - Vector of bool (class template specialization )

** End C++ Vector 
=========================================================================================




*/

/* Preprocessing */
#include <stdio.h>
#include <stdlib.h>

#include "fullVector.h"

void _dynamicArray(dynamicArray * init, int startSize, int resiz){
  //Initalize all variables to a default
  (*init).resizer = resiz;
  (*init).currentCount = 0;
  (*init).totalSize = startSize;
  (*init).entries = malloc(sizeof(void* ) * (*init).totalSize);
}

void addTo_dynamicArray(dynamicArray* addTo, void *entry){
  //Sanity check to see if resize is needed
  if ((*addTo).totalSize == (*addTo).currentCount){
    resize_dynamicArray(addTo);
  }
  //Increment to next in array
  (*addTo).entries[addTo->currentCount++] = entry;
}

static void resize_dynamicArray (dynamicArray* toResize){
  
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

void * getIndex_dynamicArray (dynamicArray* arrayGet, int index){
  //Sanity check - make sure its in range
  if (index < 0 || index > arrayGet->totalSize){
    return (*arrayGet).entries[index];
  }
  return NULL;
}

/*set index*/
/*Params - type (*, int) - array to get, index, entry value*/
void setIndex_dynamicArray (dynamicArray* arraySet, int indexSet, void* newEntry){
  //Sanity check - make sure its in range
  if (indexSet < 0 || indexSet > arraySet->totalSize){
    (*arraySet).entries[indexSet] = newEntry;    
  }
  // Needs better error handling - Catch range error w/o requiring a return
  // else {
  //    return 1;
  // }  
}

int getTotalSize_dynamicArray (dynamicArray* getTotalSize){
  return getTotalSize->totalSize;
}



