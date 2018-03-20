/*
 *    MIRACL  C++ Header file ZZn12a.h
 *
 *    AUTHOR  : M. Scott
 *
 *    NOTE:   : Must be used in conjunction with zzn4.cpp zzn2.cpp big.cpp and zzn.cpp
 *            : This is designed as a "towering extension", so a ZZn12 consists
 *            : of three ZZn4. 
 *
 *    PURPOSE : Definition of class zzn12  (Arithmetic over n^12)
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 *    Note: This code assumes that 
 *          p=5 mod 8
 *          OR p=3 mod 8
 *          OR p=7 mod 8, p=2,3 mod 5
 *
 * Irreducible poly is X^3+n, where n=sqrt(w+sqrt(m)), m= {-1,-2} and w= {0,1,2}
 *          if p=5 mod 8, n=sqrt(-2)
 *          if p=3 mod 8, n=1+sqrt(-1)
 *          if p=7 mod 8, p=2,3 mod 5, n=2+sqrt(-1)
 *
 *    Copyright (c) 2009 Shamus Software Ltd.
 */

#ifndef ZZN12A_H
#define ZZN12A_H

#include "zzn4.h"

class ZZn12
{
    ZZn4 a,b,c;
	BOOL unitary; // "unitary property means that fast squaring can be used, and inversions are just conjugates
	BOOL miller;  // "miller" property means that arithmetic on this instance can ignore multiplications
	              // or divisions by constants - as instance will eventually be raised to (p-1).
public:
    ZZn12()   {miller=unitary=FALSE;}
    ZZn12(int w) {a=(ZZn4)w; b.clear(); c.clear(); miller=FALSE; if (w==1) unitary=TRUE; else unitary=FALSE;}
    ZZn12(const ZZn12& w) {a=w.a; b=w.b; c=w.c; miller=w.miller; unitary=w.unitary;}
    ZZn12(const ZZn4 &x) {a=x; b.clear(); c.clear(); miller=unitary=FALSE;}
    ZZn12(const ZZn4 &x,const ZZn4& y,const ZZn4& z) {a=x; b=y; c=z; miller=unitary=FALSE;}
    ZZn12(const ZZn &x) {a=(ZZn4)x; b.clear(); c.clear(); miller=unitary=FALSE;}
    ZZn12(const Big &x) {a=(ZZn4)x; b.clear(); c.clear(); miller=unitary=FALSE;}
    
    void set(const ZZn4 &x,const ZZn4 &y,const ZZn4 &z) {a=x; b=y; c=z; unitary=FALSE;}
    void set(const ZZn4 &x) {a=x; b.clear(); c.clear();unitary=FALSE;}
    void set(const ZZn4 &x,const ZZn4 &y) {a=x; b=y; c.clear();unitary=FALSE; }
    void set1(const ZZn4 &x) {a.clear(); b=x; c.clear();unitary=FALSE;}
    void set2(const ZZn4 &x) {a.clear(); b.clear(); c=x; unitary=FALSE;}
    void set(const Big &x) {a=(ZZn4)x; b.clear(); c.clear();unitary=FALSE;}

    void get(ZZn4 &,ZZn4 &,ZZn4 &) ;
    void get(ZZn4 &) ;
    void get1(ZZn4 &) ;
    void get2(ZZn4 &) ;
    
    void clear() {a.clear(); b.clear(); c.clear();}
    void mark_as_unitary() {miller=FALSE; unitary=TRUE;}
	void mark_as_miller()  {miller=TRUE;}
	void mark_as_regular() {miller=unitary=FALSE;}
    BOOL is_unitary() {return unitary;}


	ZZn12& conj() {a.conj(); b.conj(); b=-b; c.conj(); return *this;}

    BOOL iszero()  const {if (a.iszero() && b.iszero() && c.iszero()) return TRUE; return FALSE; }
    BOOL isunity() const {if (a.isunity() && b.iszero() && c.iszero()) return TRUE; return FALSE; }
 //   BOOL isminusone() const {if (a.isminusone() && b.iszero()) return TRUE; return FALSE; }

    ZZn12& powq(const ZZn2&);
    ZZn12& operator=(int i) {a=i; b.clear(); c.clear(); if (i==1) unitary=TRUE; else unitary=FALSE; return *this;}
    ZZn12& operator=(const ZZn4& x) {a=x; b.clear(); c.clear(); unitary=FALSE; return *this; }
    ZZn12& operator=(const ZZn12& x) {a=x.a; b=x.b; c=x.c; miller=x.miller; unitary=x.unitary; return *this; }
    ZZn12& operator+=(const ZZn4& x) {a+=x; unitary=FALSE; return *this; }
    ZZn12& operator+=(const ZZn12& x) {a+=x.a; b+=x.b; c+=x.c; unitary=FALSE; return *this; }
    ZZn12& operator-=(const ZZn4& x) {a-=x; unitary=FALSE; return *this; }
    ZZn12& operator-=(const ZZn12& x) {a-=x.a; b-=x.b; c-=x.c; unitary=FALSE; return *this; }
    ZZn12& operator*=(const ZZn12&); 
    ZZn12& operator*=(const ZZn4& x) {a*=x; b*=x; c*=x; unitary=FALSE; return *this; }
    ZZn12& operator*=(int x) {a*=x; b*=x; c*=x; unitary=FALSE; return *this;}
    ZZn12& operator/=(const ZZn12&); 
    ZZn12& operator/=(const ZZn4&);

    friend ZZn12 operator+(const ZZn12&,const ZZn12&);
    friend ZZn12 operator+(const ZZn12&,const ZZn4&);
    friend ZZn12 operator-(const ZZn12&,const ZZn12&);
    friend ZZn12 operator-(const ZZn12&,const ZZn4&);
    friend ZZn12 operator-(const ZZn12&);

    friend ZZn12 operator*(const ZZn12&,const ZZn12&);
    friend ZZn12 operator*(const ZZn12&,const ZZn4&);
    friend ZZn12 operator*(const ZZn4&,const ZZn12&);

    friend ZZn12 operator*(int,const ZZn12&);
    friend ZZn12 operator*(const ZZn12&,int);

    friend ZZn12 operator/(const ZZn12&,const ZZn12&);
    friend ZZn12 operator/(const ZZn12&,const ZZn4&);

    friend ZZn12 tx(const ZZn12&);
    friend ZZn12 pow(const ZZn12&,const Big&);
	friend ZZn12 pow(int,const ZZn12*,const Big*);
//    friend ZZn6 pow(int,const ZZn6*,const Big*);
  
    friend ZZn12 inverse(const ZZn12&);
	friend ZZn12 conj(const ZZn12&);
#ifndef MR_NO_RAND
    friend ZZn12 randn12(void);        // random ZZn12
#endif
    friend BOOL operator==(const ZZn12& x,const ZZn12& y)
    {if (x.a==y.a && x.b==y.b && x.c==y.c) return TRUE; else return FALSE; }

    friend BOOL operator!=(const ZZn12& x,const ZZn12& y)
    {if (x.a!=y.a || x.b!=y.b || x.c!=y.c) return TRUE; else return FALSE; }

#ifndef MR_NO_STANDARD_IO
    friend ostream& operator<<(ostream&,const ZZn12&);
#endif

    ~ZZn12()  {}
};
#ifndef MR_NO_RAND
extern ZZn12 randn12(void);   
#endif
#endif

