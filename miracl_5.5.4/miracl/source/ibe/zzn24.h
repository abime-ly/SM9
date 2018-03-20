/*
 *    MIRACL  C++ Header file ZZn24.h
 *
 *    AUTHOR  : M. Scott
 *
 *    NOTE:   : Must be used in conjunction with ZZn8.cpp zzn4.cpp zzn2.cpp big.cpp zzn.cpp
 *            : This is designed as a "towering extension", so a ZZn24 consists
 *            : of three ZZn8. 
 *
 *    PURPOSE : Definition of class ZZn24  (Arithmetic over n^24)
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 *    Copyright (c) 2010 Shamus Software Ltd.
 */

#ifndef ZZn24_H
#define ZZn24_H

#include "zzn8.h"

class ZZn24
{
    ZZn8 a,b,c;
	BOOL unitary; // "unitary" property measns that fast squaring can be used, and inversions are just conjugates
	BOOL miller;  // "miller" property means that arithmetic on this instance can ignore multiplications
	              // or divisions by constants - as instance will eventually be raised to (p-1).
public:
    ZZn24()   {miller=unitary=FALSE;}
    ZZn24(int w) {a=(ZZn8)w; b.clear(); c.clear(); miller=FALSE; if (w==1) unitary=TRUE; else unitary=FALSE;}
    ZZn24(const ZZn24& w) {a=w.a; b=w.b; c=w.c; miller=w.miller; unitary=w.unitary;}
    ZZn24(const ZZn8 &x) {a=x; b.clear(); c.clear(); miller=unitary=FALSE;}
    ZZn24(const ZZn8 &x,const ZZn8& y,const ZZn8& z) {a=x; b=y; c=z; miller=unitary=FALSE;}
    ZZn24(const ZZn &x) {a=(ZZn8)x; b.clear(); c.clear(); miller=unitary=FALSE;}
    ZZn24(const Big &x) {a=(ZZn8)x; b.clear(); c.clear(); miller=unitary=FALSE;}
    
    void set(const ZZn8 &x,const ZZn8 &y,const ZZn8 &z) {a=x; b=y; c=z; unitary=FALSE;}
    void set(const ZZn8 &x) {a=x; b.clear(); c.clear();unitary=FALSE;}
    void set(const ZZn8 &x,const ZZn8 &y) {a=x; b=y; c.clear();unitary=FALSE; }
    void set1(const ZZn8 &x) {a.clear(); b=x; c.clear();unitary=FALSE;}
    void set2(const ZZn8 &x) {a.clear(); b.clear(); c=x; unitary=FALSE;}
    void set(const Big &x) {a=(ZZn8)x; b.clear(); c.clear();unitary=FALSE;}

    void get(ZZn8 &,ZZn8 &,ZZn8 &) ;
    void get(ZZn8 &) ;
    void get1(ZZn8 &) ;
    void get2(ZZn8 &) ;
    
    void clear() {a.clear(); b.clear(); c.clear();}
    void mark_as_unitary() {miller=FALSE; unitary=TRUE;}
	void mark_as_miller()  {miller=TRUE;}
	void mark_as_regular() {miller=unitary=FALSE;}

    BOOL is_unitary() {return unitary;}

	ZZn24& conj() {a.conj(); b.conj(); b=-b; c.conj(); return *this;}

    BOOL iszero()  const {if (a.iszero() && b.iszero() && c.iszero()) return TRUE; return FALSE; }
    BOOL isunity() const {if (a.isunity() && b.iszero() && c.iszero()) return TRUE; return FALSE; }
 //   BOOL isminusone() const {if (a.isminusone() && b.iszero()) return TRUE; return FALSE; }

    ZZn24& powq(const ZZn2&);
    ZZn24& operator=(int i) {a=i; b.clear(); c.clear(); if (i==1) unitary=TRUE; else unitary=FALSE; return *this;}
    ZZn24& operator=(const ZZn8& x) {a=x; b.clear(); c.clear(); unitary=FALSE; return *this; }
    ZZn24& operator=(const ZZn24& x) {a=x.a; b=x.b; c=x.c; miller=x.miller; unitary=x.unitary; return *this; }
    ZZn24& operator+=(const ZZn8& x) {a+=x; unitary=FALSE; return *this; }
    ZZn24& operator+=(const ZZn24& x) {a+=x.a; b+=x.b; c+=x.c; unitary=FALSE; return *this; }
    ZZn24& operator-=(const ZZn8& x) {a-=x; unitary=FALSE; return *this; }
    ZZn24& operator-=(const ZZn24& x) {a-=x.a; b-=x.b; c-=x.c; unitary=FALSE; return *this; }
    ZZn24& operator*=(const ZZn24&); 
    ZZn24& operator*=(const ZZn8& x) {a*=x; b*=x; c*=x; unitary=FALSE; return *this; }
    ZZn24& operator*=(int x) {a*=x; b*=x; c*=x; unitary=FALSE; return *this;}
    ZZn24& operator/=(const ZZn24&); 
    ZZn24& operator/=(const ZZn8&);

    friend ZZn24 operator+(const ZZn24&,const ZZn24&);
    friend ZZn24 operator+(const ZZn24&,const ZZn8&);
    friend ZZn24 operator-(const ZZn24&,const ZZn24&);
    friend ZZn24 operator-(const ZZn24&,const ZZn8&);
    friend ZZn24 operator-(const ZZn24&);

    friend ZZn24 operator*(const ZZn24&,const ZZn24&);
    friend ZZn24 operator*(const ZZn24&,const ZZn8&);
    friend ZZn24 operator*(const ZZn8&,const ZZn24&);

    friend ZZn24 operator*(int,const ZZn24&);
    friend ZZn24 operator*(const ZZn24&,int);

    friend ZZn24 operator/(const ZZn24&,const ZZn24&);
    friend ZZn24 operator/(const ZZn24&,const ZZn8&);

    friend ZZn24 tx(const ZZn24&);
    friend ZZn24 pow(const ZZn24&,const Big&);
	friend ZZn24 pow(int,const ZZn24*,const Big*);
//    friend ZZn6 pow(int,const ZZn6*,const Big*);
  
    friend ZZn24 inverse(const ZZn24&);
	friend ZZn24 conj(const ZZn24&);
#ifndef MR_NO_RAND
    friend ZZn24 randn24(void);        // random ZZn24
#endif
    friend BOOL operator==(const ZZn24& x,const ZZn24& y)
    {if (x.a==y.a && x.b==y.b && x.c==y.c) return TRUE; else return FALSE; }

    friend BOOL operator!=(const ZZn24& x,const ZZn24& y)
    {if (x.a!=y.a || x.b!=y.b || x.c!=y.c) return TRUE; else return FALSE; }

#ifndef MR_NO_STANDARD_IO
    friend ostream& operator<<(ostream&,const ZZn24&);
#endif

    ~ZZn24()  {}
};
#ifndef MR_NO_RAND
extern ZZn24 randn24(void);   
#endif
#endif

