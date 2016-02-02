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
        
        Copyright 2014 Tyler McKay Hall
        	tyler.m.hall@gmail.com
			  www.hive.technology

	This software is not intended for redistribution. All credit
should be given and permission requested for republication and 
modificaiton. Permission will be given to those who reasonably
request. More information can be found at www.hive.technology/copywright

	Please contact, any questions will be gladly answered.



==============================================


*/

/* Preprocessing */
#include <stdio.h>

int somefunction(float f);
int (*pSomeFunction)(float a);


/* function main begins program execution */
int main(int argc, char const *argv[])
{
	/* code */
	int (*pSomeFunction)(float a);
    pSomeFunction = somefunction;
    
    int x;
    x = pSomeFunction(23.23);
    printf("Output: %d\n", x);
  
	return 0; /* indicate that program ended successfully */
} /* End Main */

int somefunction(float f){
    return 8;
}

