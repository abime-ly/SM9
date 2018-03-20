/*
 *    No matter where you got this code from, be aware that MIRACL is NOT 
 *    free software. For commercial use a license is required.
 *	  See www.shamus.ie
 *
 * pairing_1.h
 *
 * High level interface to pairing functions - Type 1 pairings
 * 
 * GT=pairing(G1,G1)
 *
 * This is calculated on a Pairing Friendly Curve (PFC), which must first be defined.
 *
 * G1 is a point over the base field 
 * GT is a finite field point over the k-th extension, where k is the embedding degree.
 *
 */

#ifndef PAIRING_1_H
#define PAIRING_1_H

// k=2 Super-Singular curve over GF(P)
#ifdef MR_PAIRING_SSP
#include "zzn2.h"	// GT
#include "ecn.h"	// G1
#define G1_TYPE ECn
#define G1_SUBTYPE ZZn
#define GT_TYPE ZZn2
#define WINDOW_SIZE 8 // window size for precomputation
extern void read_only_error(void);
#endif

// k=4 Super-Singular curve over GF(2^M)
#ifdef MR_PAIRING_SS2
#include "gf2m4x.h"	// GT
#include "ec2.h"	// G1
#define G1_TYPE EC2
#define GT_TYPE GF2m4x
#endif

class PFC;

class G1
{
public:
	G1_TYPE g;

#ifdef MR_PAIRING_SSP 
	G1_SUBTYPE *ptable;
	G1_TYPE *mtable;
	int mtbits;

	G1()   {mtable=NULL; mtbits=0; ptable=NULL;}
	G1(const G1& w) {mtable=NULL; mtbits=0; ptable=NULL; g=w.g;}

	G1& operator=(const G1& w) 
	{
		if (mtable==NULL && ptable==NULL) g=w.g; 
		else read_only_error(); 
		return *this;
	} 

#else
    G1()   {}
	G1(const G1& w) {g=w.g;}

	G1& operator=(const G1& w) 
	{
		g=w.g;  
		return *this;
	}
#endif	
	int spill(char *&);   // spill precomputation to byte array, and return length
	void restore(char *); // restore precomputation from byte array

	friend G1 operator-(const G1&);
	friend G1 operator+(const G1&,const G1&);
	friend BOOL operator==(const G1& x,const G1& y)
      {if (x.g==y.g) return TRUE; else return FALSE;}
	friend BOOL operator!=(const G1& x,const G1& y)
      {if (x.g!=y.g) return TRUE; else return FALSE;}

#ifdef MR_PAIRING_SSP
	~G1()  {if (ptable!=NULL) {delete [] ptable; ptable=NULL;}
			if (mtable!=NULL) {delete [] mtable; mtable=NULL;}}
#else
	~G1()  {}
#endif
};

class GT
{
public:
	GT_TYPE g;

#ifdef MR_PAIRING_SSP
	GT_TYPE *etable;
	int etbits;
	GT() {etable=NULL; etbits=0;}
	GT(const GT& w) {etable=NULL; etbits=0; g=w.g;}
	GT(int d) {etable=NULL; g=d;}

	GT& operator=(const GT& w)  
	{
		if (etable==NULL) g=w.g; 
		else read_only_error();
		return *this;
	} 
#else
	GT() {}
	GT(const GT& w) {g=w.g;}
	GT(int d) {g=d;}

	GT& operator=(const GT& w)  
	{
		g=w.g; 
		return *this;
	} 
#endif
	int spill(char *&);   // spill precomputation to byte array, and return length
	void restore(char *); // restore precomputation from byte array
	friend GT operator*(const GT&,const GT&);
	friend GT operator/(const GT&,const GT&);
	friend BOOL operator==(const GT& x,const GT& y)
      {if (x.g==y.g) return TRUE; else return FALSE;}
	friend BOOL operator!=(const GT& x,const GT& y)
      {if (x.g!=y.g) return TRUE; else return FALSE;}
#ifdef MR_PAIRING_SSP
	~GT() {if (etable!=NULL) {delete [] etable; etable=NULL;}}
#else
	~GT() {}
#endif
};

// pairing friendly curve class

class PFC
{
#ifdef MR_PAIRING_SSP
public:
	Big *mod;
	Big *cof;
#else
	int B;
public:
    int M;
	int CF;
#endif
	int S;
	Big *ord;
	sha256 SH;

	PFC(int);
	Big order(void) {return *ord;}

	GT power(const GT&,const Big&);  
	G1 mult(const G1&,const Big&);
	void hash_and_map(G1&,char *);
	void random(Big&);
	void rankey(Big&);
	void random(G1&);
	BOOL member(const GT&);		   // test if element is member of pairing friendly group

	int precomp_for_pairing(G1&);  // precompute multiples of G1 that occur in Miller loop
	int precomp_for_mult(G1&,BOOL small=FALSE);     // (precomputation may not be implemented!)
	int precomp_for_power(GT&,BOOL small=FALSE);    // returns number of precomputed values
// small=TRUE if exponent is always less than full group size and equal to 2*Security level
// creates a smaller table

	int spill(G1&,char *&);
	void restore(char *,G1&);

	Big hash_to_aes_key(const GT&);
	Big hash_to_group(char *);
	GT miller_loop(const G1&,const G1&);
	GT final_exp(const GT&);
	GT pairing(const G1&,const G1&);
// parameters: number of pairings n, pointers to pair of G1 elements
	GT multi_pairing(int n,G1 **,G1 **); //product of pairings
	GT multi_miller(int n,G1 **,G1 **);
	void start_hash(void);
	void add_to_hash(const G1&);
	void add_to_hash(const GT&);
	void add_to_hash(const Big&);
	Big finish_hash_to_group(void);
	~PFC() {
#ifdef MR_PAIRING_SSP
		delete mod; delete cof; 
#endif
		delete ord; mirexit(); }
};

#ifdef MR_PAIRING_SSP

#ifndef MR_AFFINE_ONLY

extern void force(ZZn&,ZZn&,ZZn&,ECn&);
extern void extract(ECn&,ZZn&,ZZn&,ZZn&);

#endif

extern void force(ZZn&,ZZn&,ECn&);
extern void extract(ECn&,ZZn&,ZZn&);
#endif

#endif
