/*
 *    MIRACL  C++ Header file ecn2.h
 *
 *    AUTHOR  : M. Scott
 *  
 *    PURPOSE : Definition of class ECn2 (Arithmetic on an Elliptic Curve,
 *               mod n^2)
 *
 *    NOTE    : Must be used in conjunction with zzn.cpp, big.cpp and 
 *              zzn2.cpp
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 *    Copyright (c) 2001 Shamus Software Ltd.
 */

#ifndef ECN2_H
#define ECN2_H

#include "zzn2.h"

#ifdef ZZNS

#ifndef MR_AFFINE_ONLY
#define MR_INIT_ECN2 {fn.x.a=&xat; xat.w=xa; xat.len=UZZNS; fn.x.b=&xbt; xbt.w=xb; xbt.len=UZZNS;  \
                      fn.y.a=&yat; yat.w=ya; yat.len=UZZNS; fn.y.b=&ybt; ybt.w=yb; ybt.len=UZZNS;  \
                      fn.z.a=&zat; zat.w=za; zat.len=UZZNS; fn.z.b=&zbt; zbt.w=zb; zbt.len=UZZNS;  \
                     } 

#define MR_CLONE_ECN2(x) {xat.len=x.xat.len; xbt.len=x.xbt.len; yat.len=x.yat.len; ybt.len=x.ybt.len; \
                          fn.marker=x.fn.marker; \
                          zat.len=x.zat.len; zbt.len=x.zbt.len;  \
                          for (int i=0;i<UZZNS;i++) { \
                          xa[i]=x.xa[i]; xb[i]=x.xb[i]; \
                          ya[i]=x.ya[i]; yb[i]=x.yb[i]; \
                          za[i]=x.za[i]; zb[i]=x.zb[i]; \
                          } \
                         }

#define MR_ZERO_ECN2 {xat.len=xbt.len=yat.len=ybt.len=0; \
                      zat.len=zbt.len=0; \
                      for (int i=0;i<UZZNS;i++) \
                     {xa[i]=xb[i]=ya[i]=yb[i]=0; \
                      za[i]=zb[i]=0; \
                      } fn.marker=MR_EPOINT_INFINITY;} 
#else
#define MR_INIT_ECN2 {fn.x.a=&xat; xat.w=xa; xat.len=UZZNS; fn.x.b=&xbt; xbt.w=xb; xbt.len=UZZNS;  \
                      fn.y.a=&yat; yat.w=ya; yat.len=UZZNS; fn.y.b=&ybt; ybt.w=yb; ybt.len=UZZNS;  \
                     } 

#define MR_CLONE_ECN2(x) {xat.len=x.xat.len; xbt.len=x.xbt.len; yat.len=x.yat.len; ybt.len=x.ybt.len; \
                          fn.marker=x.fn.marker; \
                          for (int i=0;i<UZZNS;i++) { \
                          xa[i]=x.xa[i]; xb[i]=x.xb[i]; \
                          ya[i]=x.ya[i]; yb[i]=x.yb[i]; \
                          } \
                         }

#define MR_ZERO_ECN2 {xat.len=xbt.len=yat.len=ybt.len=0; \
                      for (int i=0;i<UZZNS;i++) \
                     {xa[i]=xb[i]=ya[i]=yb[i]=0; \
                      } fn.marker=MR_EPOINT_INFINITY;} 

#endif

#else

#ifndef MR_AFFINE_ONLY
#define MR_INIT_ECN2 {fn.x.a=mirvar(0); fn.x.b=mirvar(0); \
                      fn.y.a=mirvar(0); fn.y.b=mirvar(0); \
                      fn.z.a=mirvar(0); fn.z.b=mirvar(0); \
                      fn.marker=MR_EPOINT_INFINITY;}
#else
#define MR_INIT_ECN2 {fn.x.a=mirvar(0); fn.x.b=mirvar(0); \
                      fn.y.a=mirvar(0); fn.y.b=mirvar(0); \
                      fn.marker=MR_EPOINT_INFINITY;}
#endif

#define MR_CLONE_ECN2(x) {ecn2_copy((ecn2 *)&x.fn,&fn);}
#define MR_ZERO_ECN2     {ecn2_zero(&fn);}
#endif

class ECn2
{
    ecn2 fn;
#ifdef ZZNS
    mr_small xa[UZZNS];
    mr_small xb[UZZNS];
    bigtype xat,xbt;
    mr_small ya[UZZNS];
    mr_small yb[UZZNS];
    bigtype yat,ybt;
#ifndef MR_AFFINE_ONLY
    mr_small za[UZZNS];
    mr_small zb[UZZNS];
    bigtype zat,zbt;
#endif
#endif
public:
    ECn2()     {MR_INIT_ECN2 MR_ZERO_ECN2}
    ECn2(const ECn2& b) 
               {MR_INIT_ECN2 MR_CLONE_ECN2(b) }

    ECn2& operator=(const ECn2& b) 
               {MR_CLONE_ECN2(b) return *this; }
    
    BOOL add(ECn2&,ZZn2&);
    BOOL add(ECn2&,ZZn2&,ZZn2&);
    BOOL add(ECn2&,ZZn2&,ZZn2&,ZZn2&);

    ECn2& operator+=(ECn2&); 
    ECn2& operator-=(ECn2&); 
    ECn2& operator*=(const Big&); 
   
    void clear() {MR_ZERO_ECN2}
	int type() {return fn.marker;}
    BOOL iszero() {if (fn.marker==MR_EPOINT_INFINITY) return TRUE; return FALSE;}

    void get(ZZn2&,ZZn2&);
    void get(ZZn2&);

#ifndef MR_AFFINE_ONLY
    void get(ZZn2&,ZZn2&,ZZn2&);
    void getZ(ZZn2&);
    void set(ZZn2&,ZZn2&,ZZn2&);
	
#endif
	void norm(void);
    BOOL set(ZZn2&,ZZn2&); // set on the curve - returns FALSE if no such point
    BOOL set(ZZn2&);       // sets x coordinate on curve, and finds y coordinate
    
    friend ECn2 operator-(const ECn2&);
    friend ECn2 operator+(ECn2&,ECn2&);
    friend ECn2 operator-(ECn2&,ECn2&);
    friend ECn2 mul(Big&,ECn2&,Big&,ECn2&);

    friend BOOL operator==(ECn2& a,ECn2 &b) 
        {if (ecn2_compare(&(a.fn),&(b.fn))) return TRUE;
         return FALSE; }
    friend BOOL operator!=(ECn2& a,ECn2 &b) 
        {if (!ecn2_compare(&(a.fn),&(b.fn))) return TRUE;
        return FALSE; }

    friend ECn2 operator*(const Big &,const ECn2&);

	friend ECn2 mul(int,ECn2*,const Big*);

#ifndef MR_NO_STANDARD_IO
    friend ostream& operator<<(ostream&,ECn2&);
#endif

    ~ECn2() {
    //    MR_ZERO_ECN2  // slower but safer
#ifndef ZZNS  
        mr_free(fn.x.a); 
        mr_free(fn.x.b);
        mr_free(fn.y.a); 
        mr_free(fn.y.b);
#ifndef MR_AFFINE_ONLY
        mr_free(fn.z.a); 
        mr_free(fn.z.b);
#endif
#endif
    }
};

#endif

