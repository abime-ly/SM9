/*
 *    MIRACL  C++ Header file ecn3.h
 *
 *    AUTHOR  : M. Scott
 *  
 *    PURPOSE : Definition of class ECn3 (Arithmetic on an Elliptic Curve,
 *               mod n^3)
 *
 *    NOTE    : Must be used in conjunction with zzn.cpp, big.cpp and 
 *              zzn3.cpp
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 *    Copyright (c) 2006 Shamus Software Ltd.
 */

#ifndef ECN3_H
#define ECN3_H

#include "zzn3.h"

//#define MR_ECN3_PROJECTIVE

class ECn3
{
    ZZn3 x,y;
#ifdef MR_ECN3_PROJECTIVE
#ifndef MR_AFFINE_ONLY
	ZZn3 z;
#endif
#endif
	int marker;
public:
    ECn3()     {marker=MR_EPOINT_INFINITY;}
    ECn3(const ECn3& b) 
	{
		x=b.x; y=b.y; 
#ifdef MR_ECN3_PROJECTIVE
#ifndef MR_AFFINE_ONLY
		z=b.z;
#endif
#endif
		marker=b.marker; 
	}

    ECn3& operator=(const ECn3& b) 
    {
		x=b.x; y=b.y; 
#ifdef MR_ECN3_PROJECTIVE
#ifndef MR_AFFINE_ONLY
		z=b.z;
#endif
#endif
		marker=b.marker; 
		return *this; 
	}
    
    int add(const ECn3&,ZZn3&,ZZn3 *ex1=NULL,ZZn3 *ex2=NULL );

    ECn3& operator+=(const ECn3&); 
    ECn3& operator-=(const ECn3&); 
    ECn3& operator*=(const Big&); 
   
    void clear() 
	{
		x=y=0; 
#ifdef MR_ECN3_PROJECTIVE
#ifndef MR_AFFINE_ONLY
		z=0;
#endif
#endif
	marker=MR_EPOINT_INFINITY;
	}

    BOOL iszero() {if (marker==MR_EPOINT_INFINITY) return TRUE; return FALSE;}

    void get(ZZn3&,ZZn3&);
    void get(ZZn3&);
#ifdef MR_ECN3_PROJECTIVE
#ifndef MR_AFFINE_ONLY
	void getZ(ZZn3&);
	void get(ZZn3&,ZZn3&,ZZn3&);

	void set(const ZZn3&,const ZZn3&,const ZZn3&);
#endif
#endif
    BOOL set(const ZZn3&,const ZZn3&); // set on the curve - returns FALSE if no such point
    BOOL set(const ZZn3&);      // sets x coordinate on curve, and finds y coordinate

	void norm(void);    
    friend ECn3 operator-(const ECn3&);
    friend ECn3 operator+(const ECn3&,const ECn3&);
    friend ECn3 operator-(const ECn3&,const ECn3&);

	friend ECn3 mul(int,ECn3*,const Big*);
	friend ECn3 mul(const ECn3&,const Big&,const ECn3&,const Big&);

    friend BOOL operator==(ECn3& a,ECn3 &b) 
    {
#ifdef MR_ECN3_PROJECTIVE
		a.norm(); b.norm(); 
#endif
		return (a.x==b.x && a.y==b.y && a.marker==b.marker); 
	}
    friend BOOL operator!=(ECn3& a,ECn3 &b) 
    {
#ifdef MR_ECN3_PROJECTIVE
		a.norm(); b.norm(); 
#endif
		return (a.x!=b.x || a.y!=b.y || a.marker!=b.marker); 
	}

    friend ECn3 operator*(const Big &,const ECn3&);
#ifndef MR_NO_STANDARD_IO
    friend ostream& operator<<(ostream&,ECn3&);
#endif

    ~ECn3() {}
};

#endif

