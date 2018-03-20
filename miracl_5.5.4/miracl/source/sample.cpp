/*
 *   Example program
 *
 *   Requires: flash.cpp 
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <iostream>
#include "flash.h"

using namespace std;

/*
#ifndef MR_NOFULLWIDTH
Miracl precision(-35,0);
#else
Miracl precision(-35,MAXBASE);
#endif
*/

Miracl precision=8;


int main()
{ /* Brents example program */
    Flash x;
    cout << pi() << endl;
    x=exp(pi()*sqrt((Flash)(char *)"163/9"));
    cout << x << endl;
    cout << pow(x,3) << endl;
    return 0;
}

