/*
 *    MIRACL  C++ Header file ZZn8.h
 *
 *    AUTHOR  : M. Scott
 *
 *    NOTE:   : Must be used in conjunction with zzn4.cpp zzn2.cpp big.cpp and zzn.cpp
 *            : This is designed as a "towering extension", so a ZZn8 consists
 *            : of a pair of ZZn4. An element looks like (a+x^2.b) + x(c+x^2.d)
 *
 *    PURPOSE : Definition of class ZZn8  (Arithmetic over n^8)
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 *
 *    Copyright (c) 2010 Shamus Software Ltd.
 */

#ifndef ZZN8_H
#define ZZN8_H

#include "zzn4.h"

class ZZn8
{
    ZZn4 a,b;
    BOOL unitary;
public:
    ZZn8()   {unitary=FALSE;}
    ZZn8(int w) {a=(ZZn4)w; b=0; if (w==1) unitary=TRUE; else unitary=FALSE;}
    ZZn8(const ZZn8& w) {a=w.a; b=w.b; unitary=w.unitary; }
    ZZn8(const ZZn4 &x,const ZZn4& y) {a=x; b=y; unitary=FALSE;}
	ZZn8(const ZZn4 &x) {a=x; b=0; unitary=FALSE; }
    ZZn8(const ZZn &x)    {a=x; b=0; unitary=FALSE;}
    ZZn8(const Big &x)    {a=(ZZn)x; b=0; unitary=FALSE;}
    
    void set(const ZZn4 &x,const ZZn4 &y) {a=x; b=y; unitary=FALSE; }
	void set(const ZZn4 &x)         {a=x; b=(ZZn4)0; unitary=FALSE;}
    void set(const Big &x)          {a=(ZZn)x; b=(ZZn4)0; unitary=FALSE; }

    void get(ZZn4 &,ZZn4 &) ;
    void get(ZZn4 &) ;
    
    void clear() {a=0; b=0; unitary=FALSE;}
    void mark_as_unitary() {unitary=TRUE;}
    BOOL is_unitary() {return unitary;}

    BOOL iszero()  const {if (a.iszero() && b.iszero()) return TRUE; return FALSE; }
    BOOL isunity() const {if (a.isunity() && b.iszero()) return TRUE; return FALSE; }
//    BOOL isminusone() const {if (a.isminusone() && b.iszero()) return TRUE; return FALSE; }

    ZZn8& powq(const ZZn2&);
    ZZn8& operator=(int i) {a=i; b=0; if (i==1) unitary=TRUE; else unitary=FALSE; return *this;}
    ZZn8& operator=(const ZZn& x) {a=x; b=0; unitary=FALSE; return *this; }
    ZZn8& operator=(const ZZn4& x) {a=x; b=0; unitary=FALSE; return *this; }
    ZZn8& operator=(const ZZn8& x) {a=x.a; b=x.b; unitary=x.unitary; return *this; }
    ZZn8& operator+=(const ZZn& x) {a+=x; unitary=FALSE; return *this; }
    ZZn8& operator+=(const ZZn4& x) {a+=x; unitary=FALSE; return *this; }
    ZZn8& operator+=(const ZZn8& x) {a+=x.a; b+=x.b; unitary=FALSE; return *this; }
    ZZn8& operator-=(const ZZn& x)  {a-=x; unitary=FALSE; return *this; }
    ZZn8& operator-=(const ZZn4& x) {a-=x; unitary=FALSE; return *this; }
    ZZn8& operator-=(const ZZn8& x) {a-=x.a; b-=x.b; unitary=FALSE; return *this; }
    ZZn8& operator*=(const ZZn8&); 
    ZZn8& operator*=(const ZZn4& x) {a*=x; b*=x; unitary=FALSE; return *this; }
    ZZn8& operator*=(const ZZn& x) {a*=x; b*=x; unitary=FALSE; return *this; }
    ZZn8& operator*=(int x) {a*=x; b*=x; unitary=FALSE; return *this;}
    ZZn8& operator/=(const ZZn8&); 
    ZZn8& operator/=(const ZZn4&);
    ZZn8& operator/=(const ZZn&);
    ZZn8& operator/=(int);
    ZZn8& conj() {b=-b; return *this;}

    friend ZZn8 operator+(const ZZn8&,const ZZn8&);
    friend ZZn8 operator+(const ZZn8&,const ZZn4&);
    friend ZZn8 operator+(const ZZn8&,const ZZn&);
    friend ZZn8 operator-(const ZZn8&,const ZZn8&);
    friend ZZn8 operator-(const ZZn8&,const ZZn4&);
    friend ZZn8 operator-(const ZZn8&,const ZZn&);
    friend ZZn8 operator-(const ZZn8&);

    friend ZZn8 operator*(const ZZn8&,const ZZn8&);
    friend ZZn8 operator*(const ZZn8&,const ZZn4&);
    friend ZZn8 operator*(const ZZn8&,const ZZn&);
    friend ZZn8 operator*(const ZZn&,const ZZn8&);
    friend ZZn8 operator*(const ZZn4&,const ZZn8&);

    friend ZZn8 operator*(int,const ZZn8&);
    friend ZZn8 operator*(const ZZn8&,int);

    friend ZZn8 operator/(const ZZn8&,const ZZn8&);
    friend ZZn8 operator/(const ZZn8&,const ZZn4&);
    friend ZZn8 operator/(const ZZn8&,const ZZn&);
    friend ZZn8 operator/(const ZZn8&,int);

    friend ZZn4  real(const ZZn8& x)      {return x.a;}
    friend ZZn4  imaginary(const ZZn8& x) {return x.b;}

    friend ZZn8 pow(const ZZn8&,const Big&);
    friend ZZn8 pow(int,const ZZn8*,const Big*);
    friend ZZn8 powl(const ZZn8&,const Big&);
    friend ZZn8 conj(const ZZn8&);
    friend ZZn8 tx(const ZZn8&);
	friend ZZn8 tx2(const ZZn8&);
    friend ZZn8 inverse(const ZZn8&);
#ifndef MR_NO_RAND
    friend ZZn8 randn8(void);        // random ZZn8
#endif
    friend BOOL qr(const ZZn8&);
    friend ZZn8 sqrt(const ZZn8&);   // square root - 0 if none exists

    friend BOOL operator==(const ZZn8& x,const ZZn8& y)
    {if (x.a==y.a && x.b==y.b) return TRUE; else return FALSE; }

    friend BOOL operator!=(const ZZn8& x,const ZZn8& y)
    {if (x.a!=y.a || x.b!=y.b) return TRUE; else return FALSE; }

#ifndef MR_NO_STANDARD_IO
    friend ostream& operator<<(ostream&,const ZZn8&);
#endif

    ~ZZn8()  {}
};
#ifndef MR_NO_RAND
extern ZZn8 randn8(void); 
#endif

#endif

