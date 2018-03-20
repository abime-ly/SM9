/*
 *    No matter where you got this code from, be aware that MIRACL is NOT 
 *    free software. For commercial use a license is required.
 *	  See www.shamus.ie
 *
 *    MIRACL  C++  functions ecn.cpp
 *
 *    AUTHOR  :    M. Scott
 *             
 *    PURPOSE :    Implementation of class ECn functions using Montgomery
 *                 representation
 *    NOTE    :    Must be used in conjunction with big.h and big.cpp
 *
 *    Copyright (c) 1988-2004 Shamus Software Ltd.
 */

#include "ecn.h"

int ECn::get(Big& x,Big& y) const 
        {return epoint_get(p,x.getbig(),y.getbig());}
int ECn::get(Big& x) const   
        {return epoint_get(p,x.getbig(),x.getbig());}

#ifndef MR_STATIC
void ECn::getx(Big &x) const
        {epoint_getxyz(p,x.getbig(),NULL,NULL);}
void ECn::getxy(Big &x,Big &y) const
        {epoint_getxyz(p,x.getbig(),y.getbig(),NULL);}
void ECn::getxyz(Big &x,Big &y, Big &z) const
        {epoint_getxyz(p,x.getbig(),y.getbig(),z.getbig());}
#endif

// ecurve_add leaves some "goodies" in w6,w7 and w8
// Note if A=0 for the elliptic curve, ex1 doesn't return anything useful
// ex1=Z*Z, ex2=2Y^2, lam = line slope

int ECn::add(const ECn& b,big *lam,big *ex1,big *ex2) const
{
    int r=ecurve_add(b.p,p); *lam=get_mip()->w8; 
    if (ex1!=NULL) *ex1=get_mip()->w7; 
    if (ex2!=NULL) *ex2=get_mip()->w6; 
    return r;
}

int ECn::sub(const ECn& b,big *lam,big *ex1,big *ex2) const
{
    int r=ecurve_sub(b.p,p); *lam=get_mip()->w8; 
    if (ex1!=NULL) *ex1=get_mip()->w7; 
    if (ex2!=NULL) *ex2=get_mip()->w6;    
    return r;
}

BOOL ECn::iszero() const
        {if (p->marker==MR_EPOINT_INFINITY) return TRUE; return FALSE;}

epoint * ECn::get_point() const
{ return p; }

ECn operator-(const ECn& e)
{ ECn t=e; epoint_negate(t.p); return t;}

ECn operator*(const Big& e,const ECn& b)
{
    ECn t;
    ecurve_mult(e.getbig(),b.p,t.p);
    return t;
}

#ifndef MR_NO_ECC_MULTIADD

ECn mul(const Big& e1,const ECn& p1,const Big& e2,const ECn& p2)
{ 
    ECn t; 
    ecurve_mult2(e1.getbig(),p1.get_point(),e2.getbig(),p2.get_point(),t.get_point());
    return t;
}

#ifndef MR_STATIC

ECn mul(int n,const Big *y,ECn *x)
{
    ECn w;
    int i;
    big *a=(big *)mr_alloc(n,sizeof(big));
    epoint **b=(epoint **)mr_alloc(n,sizeof(epoint *));
    for (i=0;i<n;i++)
    {
        a[i]=y[i].getbig();
        b[i]=x[i].p;
    }
    ecurve_multn(n,a,b,w.p);

    mr_free(b);
    mr_free(a);

    return w;  
}
#ifndef MR_EDWARDS
void multi_norm(int m,ECn* e)
{
    int i;
    Big w[20];
    big a[20];
    epoint *b[20];   
    for (i=0;i<m;i++)
    {
        a[i]=w[i].getbig();
        b[i]=e[i].p;
    }
    epoint_multi_norm(m,a,b);   
}

void multi_add(int m,ECn *x, ECn *w)
{
    int i;
    epoint **xp=(epoint **)mr_alloc(m,sizeof(epoint *));
    epoint **wp=(epoint **)mr_alloc(m,sizeof(epoint *));
    for (i=0;i<m;i++)
    {
        xp[i]=x[i].p;
        wp[i]=w[i].p;
    }
    ecurve_multi_add(m,xp,wp);
    mr_free(wp);
    mr_free(xp);
}
#endif
#endif


#ifndef MR_EDWARDS
void double_add(ECn& A,ECn& B,ECn& C,ECn& D,big& s1,big& s2)
{
    ecurve_double_add(A.p,B.p,C.p,D.p,&s1,&s2);
}
#endif

#endif

#ifndef MR_NO_STANDARD_IO

ostream& operator<<(ostream& s,const ECn& b)
{
    Big x,y;
    if (b.iszero())
        s << "(Infinity)";
    else
    {
        b.get(x,y);
        s << "(" << x << "," << y << ")";
    }
    return s;
}

#endif

#ifndef MR_NOSUPPORT_COMPRESSION
#ifndef MR_NOTESTXONCURVE


BOOL is_on_curve(const Big& a)
{ return epoint_x(a.fn);}

#endif
#endif
