/*
 *    MIRACL  C++ Header file ZZn4.h
 *
 *    AUTHOR  : M. Scott
 *
 *    NOTE:   : Must be used in conjunction with zzn2.cpp big.cpp and zzn.cpp
 *            : This is designed as a "towering extension", so a ZZn4 consists
 *            : of a pair of ZZn2. An element looks like (a+x^2.b) + x(c+x^2.d)
 *
 *    PURPOSE : Definition of class ZZn4  (Arithmetic over n^4)
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
 * Irreducible poly is X^2+n, where n=w+sqrt(m), m= {-1,-2} and w= {0,1,2}
 *          if p=5 mod 8, n=sqrt(-2)
 *          if p=3 mod 8, n=1+sqrt(-1)
 *          if p=7 mod 8, p=2,3 mod 5, n=2+sqrt(-1)
 *
 *    Copyright (c) 2009 Shamus Software Ltd.
 */

#ifndef ZZN4_H
#define ZZN4_H

#include "zzn2.h"

class ZZn4
{
    ZZn2 a,b;
    BOOL unitary;
public:
    ZZn4()   {unitary=FALSE;}
    ZZn4(int w) {a=(ZZn2)w; b=0; if (w==1) unitary=TRUE; else unitary=FALSE;}
    ZZn4(const ZZn4& w) {a=w.a; b=w.b; unitary=w.unitary; }
    ZZn4(const ZZn2 &x) {a=x; b=0; unitary=FALSE;}
    ZZn4(const ZZn2 &x,const ZZn2& y) {a=x; b=y; unitary=FALSE;}
    ZZn4(const ZZn &x) {a=x; b=0; unitary=FALSE;}
    ZZn4(const Big &x) {a=(ZZn)x; b=0; unitary=FALSE;}
    
    void set(const ZZn2 &x,const ZZn2 &y) {a=x; b=y; }
    void set(const ZZn2 &x)  {a=x; b=0; }
    void seth(const ZZn2 &x) {a=0; b=x; }

    void set(const Big &x)          {a=(ZZn)x; b=0; }
   
    void get(ZZn2 &,ZZn2 &) ;
    void get(ZZn2 &) ;
    void geth(ZZn2 &);
    
    void clear() {a=0; b=0; unitary=FALSE;}
    void mark_as_unitary() {unitary=TRUE;}
    BOOL is_unitary() {return unitary;}


    BOOL iszero()  const {if (a.iszero() && b.iszero()) return TRUE; return FALSE; }
    BOOL isunity() const {if (a.isunity() && b.iszero()) return TRUE; return FALSE; }
 //   BOOL isminusone() const {if (a.isminusone() && b.iszero()) return TRUE; return FALSE; }

    ZZn4& powq(const ZZn2&);
    ZZn4& operator=(int i) {a=i; b=0; if (i==1) unitary=TRUE; else unitary=FALSE; return *this;}
    ZZn4& operator=(const ZZn& x) {a=x; b=0; unitary=FALSE; return *this; }
    ZZn4& operator=(const ZZn2& x) {a=x; b=0; unitary=FALSE; return *this; }
    ZZn4& operator=(const ZZn4& x) {a=x.a; b=x.b; unitary=x.unitary; return *this; }
    ZZn4& operator+=(const ZZn& x) {a+=x; unitary=FALSE; return *this; }
    ZZn4& operator+=(const ZZn2& x) {a+=x; unitary=FALSE; return *this; }
    ZZn4& operator+=(const ZZn4& x) {a+=x.a; b+=x.b; unitary=FALSE; return *this; }
    ZZn4& operator-=(const ZZn& x) {a-=x; unitary=FALSE;  return *this; }
    ZZn4& operator-=(const ZZn2& x) {a-=x; unitary=FALSE; return *this; }
    ZZn4& operator-=(const ZZn4& x) {a-=x.a; b-=x.b; unitary=FALSE; return *this; }
    ZZn4& operator*=(const ZZn4&); 
    ZZn4& operator*=(const ZZn2& x) {a*=x; b*=x; unitary=FALSE; return *this; }
    ZZn4& operator*=(const ZZn& x) {a*=x; b*=x; unitary=FALSE; return *this; }
    ZZn4& operator*=(int x) {a*=x; b*=x; unitary=FALSE; return *this;}
    ZZn4& operator/=(const ZZn4&); 
    ZZn4& operator/=(const ZZn2&);
    ZZn4& operator/=(const ZZn&);
    ZZn4& operator/=(int);
    ZZn4& conj() {b=-b; return *this;}

    friend ZZn4 operator+(const ZZn4&,const ZZn4&);
    friend ZZn4 operator+(const ZZn4&,const ZZn2&);
    friend ZZn4 operator+(const ZZn4&,const ZZn&);
    friend ZZn4 operator-(const ZZn4&,const ZZn4&);
    friend ZZn4 operator-(const ZZn4&,const ZZn2&);
    friend ZZn4 operator-(const ZZn4&,const ZZn&);
    friend ZZn4 operator-(const ZZn4&);

    friend ZZn4 operator*(const ZZn4&,const ZZn4&);
    friend ZZn4 operator*(const ZZn4&,const ZZn2&);
    friend ZZn4 operator*(const ZZn4&,const ZZn&);
    friend ZZn4 operator*(const ZZn&,const ZZn4&);
    friend ZZn4 operator*(const ZZn2&,const ZZn4&);

    friend ZZn4 operator*(int,const ZZn4&);
    friend ZZn4 operator*(const ZZn4&,int);

    friend ZZn4 operator/(const ZZn4&,const ZZn4&);
    friend ZZn4 operator/(const ZZn4&,const ZZn2&);
    friend ZZn4 operator/(const ZZn4&,const ZZn&);
    friend ZZn4 operator/(const ZZn4&,int);

	friend ZZn4 rhs(const ZZn4&);

    friend ZZn2  real(const ZZn4& x)      {return x.a;}
    friend ZZn2  imaginary(const ZZn4& x) {return x.b;}

    friend ZZn4 pow(const ZZn4&,const Big&);
    friend ZZn4 powu(const ZZn4&,const Big&);
    friend ZZn4 pow(int,const ZZn4*,const Big*);
    friend ZZn4 powl(const ZZn4&,const Big&);
    friend ZZn4 conj(const ZZn4&);
    friend ZZn4 tx(const ZZn4&);
    friend ZZn4 txd(const ZZn4&);
    friend ZZn4 inverse(const ZZn4&);
#ifndef MR_NO_RAND
    friend ZZn4 randn4(void);        // random ZZn4
#endif
    friend BOOL qr(const ZZn4&);
    friend BOOL is_on_curve(const ZZn4&);
    friend ZZn4 sqrt(const ZZn4&);   // square root - 0 if none exists

    friend BOOL operator==(const ZZn4& x,const ZZn4& y)
    {if (x.a==y.a && x.b==y.b) return TRUE; else return FALSE; }

    friend BOOL operator!=(const ZZn4& x,const ZZn4& y)
    {if (x.a!=y.a || x.b!=y.b) return TRUE; else return FALSE; }

#ifndef MR_NO_STANDARD_IO
    friend ostream& operator<<(ostream&,const ZZn4&);
#endif

    ~ZZn4()  {}
};
#ifndef MR_NO_RAND
extern ZZn4 randn4(void);   
#endif
#endif

