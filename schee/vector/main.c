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


Testing a vector
==============================================
Just a pretty basic main to test out the construction of a dynamic array

basicVector.c - Working

fulLVector.h/.c - Needs quite a bit more work

To Do:
=======
- Write some propper tests for this thing...

*/

/* Preprocessing */
#include <stdio.h>
#include <stdlib.h>

#include "fullVector.h"

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
