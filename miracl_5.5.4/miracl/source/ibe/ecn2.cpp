/*
 *    MIRACL  C++ Implementation file ecn2.cpp
 *
 *    AUTHOR  : M. Scott
 *  
 *    PURPOSE : Implementation of class ECn2  (Elliptic curves over n^2)
 *
 * WARNING: This class has been cobbled together for a specific use with
 * the MIRACL library. It is not complete, and may not work in other 
 * applications
 *
 *    Copyright (c) 2001-2008 Shamus Software Ltd.
 */

#include "ecn2.h"

using namespace std;

#ifndef MR_AFFINE_ONLY
void ECn2::get(ZZn2& x,ZZn2& y,ZZn2& z)
{ecn2_get(&fn,&(x.fn),&(y.fn),&(z.fn));} 
#endif

void ECn2::get(ZZn2& x,ZZn2& y)
{norm(); ecn2_getxy(&fn,&(x.fn),&(y.fn));  }

void ECn2::get(ZZn2& x)
{norm(); ecn2_getx(&fn,&(x.fn));}

#ifndef MR_AFFINE_ONLY
void ECn2::getZ(ZZn2& z)
{ecn2_getz(&fn,&(z.fn));}
#endif

void ECn2::norm(void)
{ // normalize a point    
    ecn2_norm(&(fn));
}

BOOL ECn2::set(ZZn2& xx,ZZn2& yy)
{
    return ecn2_set(&(xx.fn),&(yy.fn),&(fn));
}

BOOL ECn2::set(ZZn2& xx)
{
    return ecn2_setx(&(xx.fn),&(fn));
}

#ifndef MR_AFFINE_ONLY
void ECn2::set(ZZn2& xx,ZZn2& yy,ZZn2& zz)
{
    ecn2_setxyz(&(xx.fn),&(yy.fn),&(zz.fn),&(fn));
}
#endif

ECn2 operator-(const ECn2& a) 
{
    ECn2 w=a;
    ecn2_negate(&(w.fn),&(w.fn));
    return w; 
}  

ECn2& ECn2::operator*=(const Big& k)
{
    ecn2_mul(k.getbig(),&(this->fn));
    return *this;
}

ECn2 operator*(const Big& r,const ECn2& P)
{
    ECn2 T=P;
    T*=r;
    return T;
}

#ifndef MR_NO_STANDARD_IO

ostream& operator<<(ostream& s,ECn2& b)
{
    ZZn2 x,y,z;
    if (b.iszero())
        s << "(Infinity)";
    else
    {
        b.norm();
        b.get(x,y);
 
        s << "(" << x << "," << y << ")";
    }
    return s;
}

#endif

ECn2 operator+(ECn2& a,ECn2& b)
{ECn2 c=a; c+=b; return c;}

ECn2 operator-(ECn2& a,ECn2& b)
{ECn2 c=a; c-=b; return c;}

ECn2& ECn2::operator-=(ECn2& z)
{ECn2 t=(-z); *this+=t; return *this; }

ECn2& ECn2::operator+=(ECn2& w)
{
    ecn2_add(&(w.fn),&(this->fn));
    return *this;
}

#ifndef MR_EDWARDS

BOOL ECn2::add(ECn2& w,ZZn2& lam,ZZn2 &extra1)
{
    return ecn2_add2(&(w.fn),&(this->fn),&(lam.fn),&(extra1.fn));
}

BOOL ECn2::add(ECn2& w,ZZn2& lam)
{
    return ecn2_add1(&(w.fn),&(this->fn),&(lam.fn));
}

BOOL ECn2::add(ECn2& w,ZZn2& lam,ZZn2& extra1,ZZn2& extra2)
{
    return ecn2_add3(&(w.fn),&(this->fn),&(lam.fn),&(extra1.fn),&(extra2.fn));
}

#endif

#ifndef MR_NO_ECC_MULTIADD

ECn2 mul(Big& a,ECn2& P,Big& b,ECn2& Q)
{
    ECn2 R;
    ecn2_mul2_jsf(a.getbig(),&(P.fn),b.getbig(),&(Q.fn),&(R.fn));
	R.norm();
    return R;
}

// standard MIRACL multi-addition

#ifndef MR_STATIC

ECn2 mul(int n,ECn2* P,const Big* b)
{
    int i;
	ECn2 R;
    big  *x=(big  *)mr_alloc(n,sizeof(big));
	ecn2 *p=(ecn2 *)mr_alloc(n,sizeof(ecn2));
    for (i=0;i<n;i++)
	{
		x[i]=b[i].getbig();
		p[i]=P[i].fn;
	}

	ecn2_multn(n,x,p,&(R.fn));

	mr_free(p); mr_free(x);
	R.norm();
	return R;
}
#endif

#endif

