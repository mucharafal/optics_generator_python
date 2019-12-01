/*
    Files extracted from ROOT:
    All required interfaces are declared in TMultiDimFet.h
    a) Math: (can be reduced to: MIN, MAX, ABS, SQRT, Matrix row operations)
        - TMathBase
        - TMath

    b) Matrices:
        - TVectorD - Instantation of TVectorT<Double_t>
        - TMatrixD - Instantation of TMatrixT<Double_t>
        - TVectorT
        - TMatrixTBase
        - TMatrixT
        - TMatrixTUtils
        - TMatrixTSym
        - TMatrixTSparse
        - TMatrixTLazy
        - TMatrixTSymCramerInv
        - TDecompLU
        - TDecompBase
        - TMatrixDEigen
        - TMatrixDSymEigen

    c) Types - in TMultiDimFet.h
        c0) Math:
            - TMathBase
            - TMath

        c1) Matrices - methods:
            - TMatrixTBase
            - TMatrixTUtils
            - TMatrixTSym
            - TMatrixTSparse
            - TMatrixDfwd
            - TMatrixT
            - TVectorT
            - TMatrixDUtils
            - TMatrixDSym
            - TMatrixDSparse
            - TMatrixD
            - TMatrixTLazy
            - TMatrixTCramerInv
            - TMatrixTSymCramerInv
            - TDecompBase
            - TDecompLU
            - TMatrixDEigen
            - TMatrixDSymEigen

        c2) Matrices - types:
            - TMatrixFfwd
            - TMatrixFSparsefwd
            - TMatrixFSymfwd
            - TMatrixDSparsefwd
            - TMatrixDSymfwd
            - TMatrixDUtilsfwd
            - TVectorDfwd
            - TVectorFfwd
            - TMatrixDBasefwd
            - TMatrixFBasefwd

        c3) Basic ROOT:
            - RConfigure
            - Riostream
            - RtypesCore
            - DllImport
            - TypeTraits
            - Rtypes - important: class definition declaration
            - TObject - reduced to bit operation
            - TString - reduced to string comparison
            - TError - do not included - Error() and R__ASSERT() functions are commented out
*/


// @(#)root/hist:$Name: v5-12-00e $:$Id: TMultiDimFit.cxx,v 1.26 2006/05/26 09:27:12 brun Exp $
// Author: Christian Holm Christensen 07/11/2000


//#include "Riostream.h"
#include "TMultiDimFet.h"
//#include "TMath.h"
//#include "TH1.h"
//#include "TH2.h"
//#include "TROOT.h"
//#include "TBrowser.h"
//#include "TDecompChol.h"
#include <map>
#include <iostream>
//#include "TMultiDimFit_wrapper.h"

#define RADDEG (180. / TMath::Pi())
#define DEGRAD (TMath::Pi() / 180.)
#define HIST_XORIG     0
#define HIST_DORIG     1
#define HIST_XNORM     2
#define HIST_DSHIF     3
#define HIST_RX        4
#define HIST_RD        5
#define HIST_RTRAI     6
#define HIST_RTEST     7
#define PARAM_MAXSTUDY 1
#define PARAM_SEVERAL  2
#define PARAM_RELERR   3
#define PARAM_MAXTERMS 4

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TVectorT
    \ingroup Matrix

 TVectorT

 Template class of Vectors in the linear algebra package

 Unless otherwise specified, vector indices always start with 0,
 spanning up to the specified limit-1.

 For (n) vectors where n <= kSizeMax (5 currently) storage space is
 available on the stack, thus avoiding expensive allocation/
 deallocation of heap space . However, this introduces of course
 kSizeMax overhead for each vector object . If this is an issue
 recompile with a new appropriate value (>=0) for kSizeMax

 Another way to assign and store vector data is through Use
 see for instance stressLinear.cxx file .

 Note that Constructors/assignments exists for all different matrix
 views

 For usage examples see $ROOTSYS/test/stressLinear.cxx

*/

//#include "TVectorT.h"
//#include "TClass.h"
//#include "TMath.h"
//#include "TROOT.h"
//#include "Varargs.h"

/* @(#)root/base:$Id$ */

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_Varargs
#define ROOT_Varargs

#ifdef __CINT__
#include <stdarg.h>
#endif

#if defined(sparc) && defined(__CC_ATT301__)

   extern "C" __builtin_va_arg_incr(...);
   typedef char *va_list;
#   define va_end(ap)
#   define va_start(ap, parmN) ap= (char*)(&parmN+1)
#   define va_arg(ap, mode) ((mode*) __builtin_va_arg_incr((mode*)ap))[0]
#   define va_(arg) __builtin_va_alist

#   include <stdio.h>

   extern "C" {
      int vfprintf(FILE*, const char *fmt, va_list ap);
      char *vsprintf(char*, const char *fmt, va_list ap);
   };

#else
#   ifndef __CINT__
#   include <stdarg.h>
#   endif
#   if defined(sparc) && !defined(__GNUG__) && !defined(__CC_SUN21__) && !defined(__SVR4)
#      define va_(arg) __builtin_va_alist
#   else
#      define va_(arg) arg
#   endif

#endif

#if !defined(R__VA_COPY)
#  if defined(__GNUC__) && !defined(__FreeBSD__)
#     define R__VA_COPY(to, from) __va_copy((to), (from))
#  elif defined(__va_copy)
#     define R__VA_COPY(to, from) __va_copy((to), (from))
#  elif defined(va_copy)
#     define R__VA_COPY(to, from) va_copy((to), (from))
#  elif defined (R__VA_COPY_AS_ARRAY)
#     define R__VA_COPY(to, from) memmove((to), (from), sizeof(va_list))
#  elif defined(_WIN32) && _MSC_VER < 1310
#     define R__VA_COPY(to, from) (*(to) = *(from))
#  else
#     define R__VA_COPY(to, from) ((to) = (from))
#  endif
#endif

#endif

templateClassImp(TVectorT);


////////////////////////////////////////////////////////////////////////////////
/// Delete data pointer m, if it was assigned on the heap

template<class Element>
void TVectorT<Element>::Delete_m(Int_t size,Element *&m)
{
   if (m) {
      if (size > kSizeMax)
         delete [] m;
      m = 0;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Return data pointer . if requested size <= kSizeMax, assign pointer
/// to the stack space

template<class Element>
Element* TVectorT<Element>::New_m(Int_t size)
{
   if (size == 0) return 0;
   else {
      if ( size <= kSizeMax )
         return fDataStack;
      else {
         Element *heap = new Element[size];
         return heap;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Add vector v to this vector

template<class Element>
void TVectorT<Element>::Add(const TVectorT<Element> &v)
{
   if (gMatrixCheck && !AreCompatible(*this,v)) {
      //Error("Add(TVectorT<Element> &)","vector's not compatible");
      return;
   }

   const Element *sp = v.GetMatrixArray();
         Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+fNrows;
   while (tp < tp_last)
      *tp++ += *sp++;
}

////////////////////////////////////////////////////////////////////////////////
/// Set this vector to v1+v2

template<class Element>
void TVectorT<Element>::Add(const TVectorT<Element> &v1,const TVectorT<Element> &v2)
{
   if (gMatrixCheck) {
      if ( !AreCompatible(*this,v1) && !AreCompatible(*this,v2)) {
         //Error("Add(TVectorT<Element> &)","vectors not compatible");
         return;
      }
   }

   const Element *sv1 = v1.GetMatrixArray();
   const Element *sv2 = v2.GetMatrixArray();
         Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+fNrows;
   while (tp < tp_last)
      *tp++ = *sv1++ + *sv2++;
}

////////////////////////////////////////////////////////////////////////////////
/// Copy copySize doubles from *oldp to *newp . However take care of the
/// situation where both pointers are assigned to the same stack space

template<class Element>
Int_t TVectorT<Element>::Memcpy_m(Element *newp,const Element *oldp,Int_t copySize,
                                  Int_t newSize,Int_t oldSize)
{
   if (copySize == 0 || oldp == newp) return 0;
   else {
      if ( newSize <= kSizeMax && oldSize <= kSizeMax ) {
         // both pointers are inside fDataStack, be careful with copy direction !
         if (newp > oldp) {
            for (Int_t i = copySize-1; i >= 0; i--)
               newp[i] = oldp[i];
         } else {
            for (Int_t i = 0; i < copySize; i++)
               newp[i] = oldp[i];
         }
      }
      else {
         memcpy(newp,oldp,copySize*sizeof(Element));
      }
   }
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Allocate new vector. Arguments are number of rows and row
/// lowerbound (0 default).

template<class Element>
void TVectorT<Element>::Allocate(Int_t nrows,Int_t row_lwb,Int_t init)
{
   fIsOwner  = kTRUE;
   fNrows    = 0;
   fRowLwb   = 0;
   fElements = 0;

   if (nrows < 0)
   {
      //Error("Allocate","nrows=%d",nrows);
      return;
   }

   //MakeValid();
   fNrows   = nrows;
   fRowLwb  = row_lwb;

   fElements = New_m(fNrows);
   if (init)
      memset(fElements,0,fNrows*sizeof(Element));
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor n-vector

template<class Element>
TVectorT<Element>::TVectorT(Int_t n)
{
   Allocate(n,0,1);
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor [lwb..upb]-vector

template<class Element>
TVectorT<Element>::TVectorT(Int_t lwb,Int_t upb)
{
   Allocate(upb-lwb+1,lwb,1);
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor n-vector with data copied from array elements

template<class Element>
TVectorT<Element>::TVectorT(Int_t n,const Element *elements)
{
   Allocate(n,0);
   SetElements(elements);
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor [lwb..upb]-vector with data copied from array elements

template<class Element>
TVectorT<Element>::TVectorT(Int_t lwb,Int_t upb,const Element *elements)
{
   Allocate(upb-lwb+1,lwb);
   SetElements(elements);
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TVectorT<Element>::TVectorT(const TVectorT &another) : TObject(another)
{
   //R__ASSERT(another.IsValid());
   Allocate(another.GetUpb()-another.GetLwb()+1,another.GetLwb());
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor : create vector from matrix row

template<class Element>
TVectorT<Element>::TVectorT(const TMatrixTRow_const<Element> &mr) : TObject()
{
   const TMatrixTBase<Element> *mt = mr.GetMatrix();
   //R__ASSERT(mt->IsValid());
   Allocate(mt->GetColUpb()-mt->GetColLwb()+1,mt->GetColLwb());
   *this = mr;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor : create vector from matrix column

template<class Element>
TVectorT<Element>::TVectorT(const TMatrixTColumn_const<Element> &mc) : TObject()
{
   const TMatrixTBase<Element> *mt = mc.GetMatrix();
   //R__ASSERT(mt->IsValid());
   Allocate(mt->GetRowUpb()-mt->GetRowLwb()+1,mt->GetRowLwb());
   *this = mc;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor : create vector from matrix diagonal

template<class Element>
TVectorT<Element>::TVectorT(const TMatrixTDiag_const<Element> &md) : TObject()
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();
   //R__ASSERT(mt->IsValid());
   Allocate(TMath::Min(mt->GetNrows(),mt->GetNcols()));
   *this = md;
}

////////////////////////////////////////////////////////////////////////////////
/// Make a vector and assign initial values. Argument list should contain
/// Element values to assign to vector elements. The list must be
/// terminated by the string "END". Example:
/// TVectorT foo(1,3,0.0,1.0,1.5,"END");

template<class Element>
TVectorT<Element>::TVectorT(Int_t lwb,Int_t upb,Double_t iv1, ...)
{
   if (upb < lwb) {
      //Error("TVectorT(Int_t, Int_t, ...)","upb(%d) < lwb(%d)",upb,lwb);
      return;
   }

   Allocate(upb-lwb+1,lwb);

   va_list args;
   va_start(args,iv1);             // Init 'args' to the beginning of
                                        // the variable length list of args

   (*this)(lwb) = iv1;
   for (Int_t i = lwb+1; i <= upb; i++)
      (*this)(i) = (Element)va_arg(args,Double_t);

   if (strcmp((char *)va_arg(args,char *),"END")) {
   }
      //Error("TVectorT(Int_t, Int_t, ...)","argument list must be terminated by \"END\"");

   va_end(args);
}

////////////////////////////////////////////////////////////////////////////////
/// Resize the vector to [lwb:upb] .
/// New dynamic elemenst are created, the overlapping part of the old ones are
/// copied to the new structures, then the old elements are deleted.

template<class Element>
TVectorT<Element> &TVectorT<Element>::ResizeTo(Int_t lwb,Int_t upb)
{
   //R__ASSERT(IsValid());
   if (!fIsOwner) {
      //Error("ResizeTo(lwb,upb)","Not owner of data array,cannot resize");
      return *this;
   }

   const Int_t new_nrows = upb-lwb+1;

   if (fNrows > 0) {

      if (fNrows == new_nrows && fRowLwb == lwb)
         return *this;
      else if (new_nrows == 0) {
         Clear();
         return *this;
      }

      Element    *elements_old = GetMatrixArray();
      const Int_t  nrows_old    = fNrows;
      const Int_t  rowLwb_old   = fRowLwb;

      Allocate(new_nrows,lwb);
      //R__ASSERT(IsValid());
      if (fNrows > kSizeMax || nrows_old > kSizeMax)
         memset(GetMatrixArray(),0,fNrows*sizeof(Element));
      else if (fNrows > nrows_old)
         memset(GetMatrixArray()+nrows_old,0,(fNrows-nrows_old)*sizeof(Element));

    // Copy overlap
      const Int_t rowLwb_copy = TMath::Max(fRowLwb,rowLwb_old);
      const Int_t rowUpb_copy = TMath::Min(fRowLwb+fNrows-1,rowLwb_old+nrows_old-1);
      const Int_t nrows_copy  = rowUpb_copy-rowLwb_copy+1;

      const Int_t nelems_new = fNrows;
      Element *elements_new = GetMatrixArray();
      if (nrows_copy > 0) {
         const Int_t rowOldOff = rowLwb_copy-rowLwb_old;
         const Int_t rowNewOff = rowLwb_copy-fRowLwb;
         Memcpy_m(elements_new+rowNewOff,elements_old+rowOldOff,nrows_copy,nelems_new,nrows_old);
      }

      Delete_m(nrows_old,elements_old);
   } else {
      Allocate(upb-lwb+1,lwb,1);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Use the array data to fill the vector lwb..upb]

template<class Element>
TVectorT<Element> &TVectorT<Element>::Use(Int_t lwb,Int_t upb,Element *data)
{
   if (upb < lwb) {
      //Error("Use","upb(%d) < lwb(%d)",upb,lwb);
      return *this;
   }

   Clear();
   fNrows    = upb-lwb+1;
   fRowLwb   = lwb;
   fElements = data;
   fIsOwner  = kFALSE;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Get subvector [row_lwb..row_upb]; The indexing range of the
/// returned vector depends on the argument option:
///
/// option == "S" : return [0..row_upb-row_lwb+1] (default)
/// else          : return [row_lwb..row_upb]

template<class Element>
TVectorT<Element> &TVectorT<Element>::GetSub(Int_t row_lwb,Int_t row_upb,TVectorT<Element> &target,Option_t *option) const
{
   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      if (row_lwb < fRowLwb || row_lwb > fRowLwb+fNrows-1) {
         //Error("GetSub","row_lwb out of bounds");
         return target;
      }
      if (row_upb < fRowLwb || row_upb > fRowLwb+fNrows-1) {
         //Error("GetSub","row_upb out of bounds");
         return target;
      }
      if (row_upb < row_lwb) {
         //Error("GetSub","row_upb < row_lwb");
         return target;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t shift = (opt.Contains("S")) ? 1 : 0;

   Int_t row_lwb_sub;
   Int_t row_upb_sub;
   if (shift) {
      row_lwb_sub = 0;
      row_upb_sub = row_upb-row_lwb;
   } else {
      row_lwb_sub = row_lwb;
      row_upb_sub = row_upb;
   }

   target.ResizeTo(row_lwb_sub,row_upb_sub);
   const Int_t nrows_sub = row_upb_sub-row_lwb_sub+1;

   const Element *ap = this->GetMatrixArray()+(row_lwb-fRowLwb);
         Element *bp = target.GetMatrixArray();

   for (Int_t irow = 0; irow < nrows_sub; irow++)
      *bp++ = *ap++;

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Insert vector source starting at [row_lwb], thereby overwriting the part
/// [row_lwb..row_lwb+nrows_source];

template<class Element>
TVectorT<Element> &TVectorT<Element>::SetSub(Int_t row_lwb,const TVectorT<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(source.IsValid());

      if (row_lwb < fRowLwb && row_lwb > fRowLwb+fNrows-1) {
         //Error("SetSub","row_lwb outof bounds");
         return *this;
      }
      if (row_lwb+source.GetNrows() > fRowLwb+fNrows) {
         //Error("SetSub","source vector too large");
         return *this;
      }
   }

   const Int_t nRows_source = source.GetNrows();

   const Element *bp = source.GetMatrixArray();
         Element *ap = this->GetMatrixArray()+(row_lwb-fRowLwb);

   for (Int_t irow = 0; irow < nRows_source; irow++)
      *ap++ = *bp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set vector elements to zero

template<class Element>
TVectorT<Element> &TVectorT<Element>::Zero()
{
   //R__ASSERT(IsValid());
   memset(this->GetMatrixArray(),0,fNrows*sizeof(Element));
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Take an absolute value of a vector, i.e. apply Abs() to each element.

template<class Element>
TVectorT<Element> &TVectorT<Element>::Abs()
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      *ep = TMath::Abs(*ep);
      ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Square each element of the vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::Sqr()
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      *ep = (*ep) * (*ep);
      ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Take square root of all elements.

template<class Element>
TVectorT<Element> &TVectorT<Element>::Sqrt()
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      //R__ASSERT(*ep >= 0);
      if (*ep >= 0)
         *ep = TMath::Sqrt(*ep);
      //else
         //Error("Sqrt()","v(%ld) = %g < 0",Long_t(ep-this->GetMatrixArray()),(float)*ep);
      ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// v[i] = 1/v[i]

template<class Element>
TVectorT<Element> &TVectorT<Element>::Invert()
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      //R__ASSERT(*ep != 0.0);
      if (*ep != 0.0)
         *ep = 1./ *ep;
      //else
         //Error("Invert()","v(%ld) = %g",Long_t(ep-this->GetMatrixArray()),(float)*ep);
      ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Keep only element as selected through array select non-zero

template<class Element>
TVectorT<Element> &TVectorT<Element>::SelectNonZeros(const TVectorT<Element> &select)
{
   if (gMatrixCheck && !AreCompatible(*this,select)) {
      //Error("SelectNonZeros(const TVectorT<Element> &","vector's not compatible");
      return *this;
   }

   const Element *sp = select.GetMatrixArray();
         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      if (*sp == 0.0)
         *ep = 0.0;
      sp++; ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the 1-norm of the vector SUM{ |v[i]| }.

template<class Element>
Element TVectorT<Element>::Norm1() const
{
   //R__ASSERT(IsValid());

   Element norm = 0;
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      norm += TMath::Abs(*ep++);

   return norm;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the square of the 2-norm SUM{ v[i]^2 }.

template<class Element>
Element TVectorT<Element>::Norm2Sqr() const
{
   //R__ASSERT(IsValid());

   Element norm = 0;
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      norm += (*ep) * (*ep);
      ep++;
   }

   return norm;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the infinity-norm of the vector MAX{ |v[i]| }.

template<class Element>
Element TVectorT<Element>::NormInf() const
{
   //R__ASSERT(IsValid());

   Element norm = 0;
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      norm = TMath::Max(norm,TMath::Abs(*ep++));

   return norm;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the number of elements != 0.0

template<class Element>
Int_t TVectorT<Element>::NonZeros() const
{
   //R__ASSERT(IsValid());

   Int_t nr_nonzeros = 0;
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      if (*ep++) nr_nonzeros++;

   return nr_nonzeros;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute sum of elements

template<class Element>
Element TVectorT<Element>::Sum() const
{
   //R__ASSERT(IsValid());

   Element sum = 0.0;
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      sum += *ep++;

   return sum;
}

////////////////////////////////////////////////////////////////////////////////
/// return minimum vector element value

template<class Element>
Element TVectorT<Element>::Min() const
{
   //R__ASSERT(IsValid());

   const Int_t index = TMath::LocMin(fNrows,fElements);
   return fElements[index];
}

////////////////////////////////////////////////////////////////////////////////
/// return maximum vector element value

template<class Element>
Element TVectorT<Element>::Max() const
{
   //R__ASSERT(IsValid());

   const Int_t index = TMath::LocMax(fNrows,fElements);
   return fElements[index];
}

////////////////////////////////////////////////////////////////////////////////
/// Notice that this assignment does NOT change the ownership :
/// if the storage space was adopted, source is copied to
/// this space .

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator=(const TVectorT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator=(const TVectorT<Element> &)","vectors not compatible");
      return *this;
   }

   if (this->GetMatrixArray() != source.GetMatrixArray()) {
      //TObject::operator=(source);
      memcpy(fElements,source.GetMatrixArray(),fNrows*sizeof(Element));
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a matrix row to a vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator=(const TMatrixTRow_const<Element> &mr)
{
   const TMatrixTBase<Element> *mt = mr.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(mt->IsValid());
      if (mt->GetColLwb() != fRowLwb || mt->GetNcols() != fNrows) {
         //Error("operator=(const TMatrixTRow_const &)","vector and row not compatible");
         return *this;
      }
   }

   const Int_t inc   = mr.GetInc();
   const Element *rp = mr.GetPtr();              // Row ptr
         Element *ep = this->GetMatrixArray();   // Vector ptr
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      *ep++ = *rp;
       rp += inc;
   }

   //R__ASSERT(rp == mr.GetPtr()+mt->GetNcols());

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a matrix column to a vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator=(const TMatrixTColumn_const<Element> &mc)
{
   const TMatrixTBase<Element> *mt = mc.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(mt->IsValid());
      if (mt->GetRowLwb() != fRowLwb || mt->GetNrows() != fNrows) {
         //Error("operator=(const TMatrixTColumn_const &)","vector and column not compatible");
         return *this;
      }
   }

   const Int_t inc    = mc.GetInc();
   const Element *cp = mc.GetPtr();              // Column ptr
         Element *ep = this->GetMatrixArray();   // Vector ptr
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      *ep++ = *cp;
       cp += inc;
   }

   //R__ASSERT(cp == mc.GetPtr()+mt->GetNoElements());

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign the matrix diagonal to a vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator=(const TMatrixTDiag_const<Element> &md)
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(mt->IsValid());
      if (md.GetNdiags() != fNrows) {
         //Error("operator=(const TMatrixTDiag_const &)","vector and matrix-diagonal not compatible");
        return *this;
      }
   }

   const Int_t    inc = md.GetInc();
   const Element *dp = md.GetPtr();              // Diag ptr
         Element *ep = this->GetMatrixArray();   // Vector ptr
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      *ep++ = *dp;
       dp += inc;
   }

   //R__ASSERT(dp < md.GetPtr()+mt->GetNoElements()+inc);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a sparse matrix row to a vector. The matrix row is implicitly transposed
/// to allow the assignment in the strict sense.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator=(const TMatrixTSparseRow_const<Element> &mr)
{
   const TMatrixTBase<Element> *mt = mr.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(mt->IsValid());
      if (mt->GetColLwb() != fRowLwb || mt->GetNcols() != fNrows) {
         //Error("operator=(const TMatrixTSparseRow_const &)","vector and row not compatible");
         return *this;
      }
   }

   const Int_t nIndex = mr.GetNindex();
   const Element * const prData = mr.GetDataPtr();          // Row Data ptr
   const Int_t    * const prCol  = mr.GetColPtr();           // Col ptr
         Element * const pvData = this->GetMatrixArray();   // Vector ptr

   memset(pvData,0,fNrows*sizeof(Element));
   for (Int_t index = 0; index < nIndex; index++) {
      const Int_t icol = prCol[index];
      pvData[icol] = prData[index];
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a sparse matrix diagonal to a vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator=(const TMatrixTSparseDiag_const<Element> &md)
{
  const TMatrixTBase<Element> *mt = md.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(mt->IsValid());
      if (md.GetNdiags() != fNrows) {
         //Error("operator=(const TMatrixTSparseDiag_const &)","vector and matrix-diagonal not compatible");
         return *this;
      }
   }

   Element * const pvData = this->GetMatrixArray();
   for (Int_t idiag = 0; idiag < fNrows; idiag++)
      pvData[idiag] = md(idiag);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator=(Element val)
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      *ep++ = val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator+=(Element val)
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      *ep++ += val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract val from every element of the vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator-=(Element val)
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      *ep++ -= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the vector with val.

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator*=(Element val)
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      *ep++ *= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add vector source

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator+=(const TVectorT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator+=(const TVectorT<Element> &)","vector's not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
         Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+fNrows;
   while (tp < tp_last)
      *tp++ += *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract vector source

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator-=(const TVectorT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator-=(const TVectorT<Element> &)","vector's not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
         Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+fNrows;
   while (tp < tp_last)
      *tp++ -= *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// "Inplace" multiplication target = A*target. A needn't be a square one
/// If target has to be resized, it should own the storage: fIsOwner = kTRUE

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator*=(const TMatrixT<Element> &a)
{
   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(a.IsValid());
      if (a.GetNcols() != fNrows || a.GetColLwb() != fRowLwb) {
         //Error("operator*=(const TMatrixT &)","vector and matrix incompatible");
         return *this;
      }
   }

   const Bool_t doResize = (fNrows != a.GetNrows() || fRowLwb != a.GetRowLwb());
   if (doResize && !fIsOwner) {
      //Error("operator*=(const TMatrixT &)","vector has to be resized but not owner");
      return *this;
   }

   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *elements_old = work;
   const Int_t nrows_old = fNrows;
   if (nrows_old > kWorkMax) {
      isAllocated = kTRUE;
      elements_old = new Element[nrows_old];
   }
   memcpy(elements_old,fElements,nrows_old*sizeof(Element));

   if (doResize) {
      const Int_t rowlwb_new = a.GetRowLwb();
      const Int_t nrows_new  = a.GetNrows();
      ResizeTo(rowlwb_new,rowlwb_new+nrows_new-1);
   }
   memset(fElements,0,fNrows*sizeof(Element));

   const Element *mp = a.GetMatrixArray();     // Matrix row ptr
         Element *tp = this->GetMatrixArray(); // Target vector ptr
#ifdef CBLAS
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemv(CblasRowMajor,CblasNoTrans,a.GetNrows(),a.GetNcols(),1.0,mp,
                  a.GetNcols(),elements_old,1,0.0,tp,1);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemv(CblasRowMajor,CblasNoTrans,a.GetNrows(),a.GetNcols(),1.0,mp,
                  a.GetNcols(),elements_old,1,0.0,tp,1);
   //else
      //Error("operator*=","type %s not implemented in BLAS library",typeid(Element));
#else
   const Element * const tp_last = tp+fNrows;
   while (tp < tp_last) {
      Element sum = 0;
      for (const Element *sp = elements_old; sp < elements_old+nrows_old; )
         sum += *sp++ * *mp++;
      *tp++ = sum;
   }
   //R__ASSERT(mp == a.GetMatrixArray()+a.GetNoElements());
#endif

   if (isAllocated)
      delete [] elements_old;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// "Inplace" multiplication target = A*target. A needn't be a square one
/// If target has to be resized, it should own the storage: fIsOwner = kTRUE

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator*=(const TMatrixTSparse<Element> &a)
{
   if (gMatrixCheck) {
      //R__ASSERT(IsValid());
      //R__ASSERT(a.IsValid());
      if (a.GetNcols() != fNrows || a.GetColLwb() != fRowLwb) {
         //Error("operator*=(const TMatrixTSparse &)","vector and matrix incompatible");
         return *this;
      }
   }

   const Bool_t doResize = (fNrows != a.GetNrows() || fRowLwb != a.GetRowLwb());
   if (doResize && !fIsOwner) {
      //Error("operator*=(const TMatrixTSparse &)","vector has to be resized but not owner");
      return *this;
   }

   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *elements_old = work;
   const Int_t nrows_old = fNrows;
   if (nrows_old > kWorkMax) {
      isAllocated = kTRUE;
      elements_old = new Element[nrows_old];
   }
   memcpy(elements_old,fElements,nrows_old*sizeof(Element));

   if (doResize) {
      const Int_t rowlwb_new = a.GetRowLwb();
      const Int_t nrows_new  = a.GetNrows();
      ResizeTo(rowlwb_new,rowlwb_new+nrows_new-1);
   }
   memset(fElements,0,fNrows*sizeof(Element));

   const Int_t   * const pRowIndex = a.GetRowIndexArray();
   const Int_t   * const pColIndex = a.GetColIndexArray();
   const Element * const mp        = a.GetMatrixArray();     // Matrix row ptr

   const Element * const sp = elements_old;
         Element *       tp = this->GetMatrixArray(); // Target vector ptr

   for (Int_t irow = 0; irow < fNrows; irow++) {
      const Int_t sIndex = pRowIndex[irow];
      const Int_t eIndex = pRowIndex[irow+1];
      Element sum = 0.0;
      for (Int_t index = sIndex; index < eIndex; index++) {
         const Int_t icol = pColIndex[index];
         sum += mp[index]*sp[icol];
      }
      tp[irow] = sum;
   }

   if (isAllocated)
      delete [] elements_old;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// "Inplace" multiplication target = A*target. A is symmetric .
/// vector size will not change

template<class Element>
TVectorT<Element> &TVectorT<Element>::operator*=(const TMatrixTSym<Element> &a)
{
  if (gMatrixCheck) {
     //R__ASSERT(IsValid());
     //R__ASSERT(a.IsValid());
     if (a.GetNcols() != fNrows || a.GetColLwb() != fRowLwb) {
        //Error("operator*=(const TMatrixTSym &)","vector and matrix incompatible");
        return *this;
     }
  }

   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *elements_old = work;
   const Int_t nrows_old = fNrows;
   if (nrows_old > kWorkMax) {
      isAllocated = kTRUE;
      elements_old = new Element[nrows_old];
   }
   memcpy(elements_old,fElements,nrows_old*sizeof(Element));
   memset(fElements,0,fNrows*sizeof(Element));

   const Element *mp = a.GetMatrixArray();     // Matrix row ptr
         Element *tp = this->GetMatrixArray(); // Target vector ptr
#ifdef CBLAS
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymv(CblasRowMajor,CblasUpper,fNrows,1.0,mp,
                  fNrows,elements_old,1,0.0,tp,1);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymv(CblasRowMajor,CblasUpper,fNrows,1.0,mp,
                  fNrows,elements_old,1,0.0,tp,1);
   //else
      //Error("operator*=","type %s not implemented in BLAS library",typeid(Element));
#else
   const Element * const tp_last = tp+fNrows;
   while (tp < tp_last) {
      Element sum = 0;
      for (const Element *sp = elements_old; sp < elements_old+nrows_old; )
         sum += *sp++ * *mp++;
      *tp++ = sum;
   }
   //R__ASSERT(mp == a.GetMatrixArray()+a.GetNoElements());
#endif

   if (isAllocated)
      delete [] elements_old;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all vector elements equal to val?

template<class Element>
Bool_t TVectorT<Element>::operator==(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      if (!(*ep++ == val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all vector elements not equal to val?

template<class Element>
Bool_t TVectorT<Element>::operator!=(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      if (!(*ep++ != val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all vector elements < val?

template<class Element>
Bool_t TVectorT<Element>::operator<(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      if (!(*ep++ < val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all vector elements <= val?

template<class Element>
Bool_t TVectorT<Element>::operator<=(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      if (!(*ep++ <= val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all vector elements > val?

template<class Element>
Bool_t TVectorT<Element>::operator>(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      if (!(*ep++ > val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all vector elements >= val?

template<class Element>
Bool_t TVectorT<Element>::operator>=(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      if (!(*ep++ >= val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Check if vector elements as selected through array select are non-zero

template<class Element>
Bool_t TVectorT<Element>::MatchesNonZeroPattern(const TVectorT<Element> &select)
{
   if (gMatrixCheck && !AreCompatible(*this,select)) {
      //Error("MatchesNonZeroPattern(const TVectorT&)","vector's not compatible");
      return kFALSE;
   }

   const Element *sp = select.GetMatrixArray();
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      if (*sp == 0.0 && *ep != 0.0)
         return kFALSE;
      sp++; ep++;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Check if vector elements as selected through array select are all positive

template<class Element>
Bool_t TVectorT<Element>::SomePositive(const TVectorT<Element> &select)
{
   if (gMatrixCheck && !AreCompatible(*this,select)) {
      //Error("SomePositive(const TVectorT&)","vector's not compatible");
      return kFALSE;
   }

   const Element *sp = select.GetMatrixArray();
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      if (*sp != 0.0 && *ep <= 0.0)
         return kFALSE;
      sp++; ep++;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Add to vector elements as selected through array select the value val

template<class Element>
void TVectorT<Element>::AddSomeConstant(Element val,const TVectorT<Element> &select)
{
   if (gMatrixCheck && !AreCompatible(*this,select)) {}
      //Error("AddSomeConstant(Element,const TVectorT&)(const TVectorT&)","vector's not compatible");

   const Element *sp = select.GetMatrixArray();
         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp) {
      if (*sp)
         *ep += val;
      sp++; ep++;
   }
}

extern Double_t Drand(Double_t &ix);

////////////////////////////////////////////////////////////////////////////////
/// randomize vector elements value

template<class Element>
void TVectorT<Element>::Randomize(Element alpha,Element beta,Double_t &seed)
{
   //R__ASSERT(IsValid());

   const Element scale = beta-alpha;
   const Element shift = alpha/scale;

         Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNrows;
   while (ep < fp)
      *ep++ = scale*(Drand(seed)+shift);
}

////////////////////////////////////////////////////////////////////////////////
/// Apply action to each element of the vector.

template<class Element>
TVectorT<Element> &TVectorT<Element>::Apply(const TElementActionT<Element> &action)
{
   //R__ASSERT(IsValid());
   for (Element *ep = fElements; ep < fElements+fNrows; ep++)
      action.Operation(*ep);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Apply action to each element of the vector. In action the location
/// of the current element is known.

template<class Element>
TVectorT<Element> &TVectorT<Element>::Apply(const TElementPosActionT<Element> &action)
{
   //R__ASSERT(IsValid());

   Element *ep = fElements;
   for (action.fI = fRowLwb; action.fI < fRowLwb+fNrows; action.fI++)
      action.Operation(*ep++);

   //R__ASSERT(ep == fElements+fNrows);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Draw this vector
/// The histogram is named "TVectorT" by default and no title
/*
template<class Element>
void TVectorT<Element>::Draw(Option_t *option)
{
   gROOT->ProcessLine(Form("THistPainter::PaintSpecialObjects((TObject*)0x%lx,\"%s\");",
                           (ULong_t)this, option));
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Print the vector as a list of elements.

template<class Element>
void TVectorT<Element>::Print(Option_t *flag) const
{
  //if (!IsValid()) {
      //Error("Print","Vector is invalid");
      //return;
   //}

   printf("\nVector (%d) %s is as follows",fNrows,flag);

   printf("\n\n     |   %6d  |", 1);
   printf("\n%s\n", "------------------");
   for (Int_t i = 0; i < fNrows; i++) {
      printf("%4d |",i+fRowLwb);
      //printf("%11.4g \n",(*this)(i+fRowLwb));
      printf("%g \n",(*this)(i+fRowLwb));
   }
   printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
/// Check to see if two vectors are identical.

template<class Element>
Bool_t operator==(const TVectorT<Element> &v1,const TVectorT<Element> &v2)
{
   if (!AreCompatible(v1,v2)) return kFALSE;
   return (memcmp(v1.GetMatrixArray(),v2.GetMatrixArray(),v1.GetNrows()*sizeof(Element)) == 0);
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the scalar product.

template<class Element>
Element operator*(const TVectorT<Element> &v1,const TVectorT<Element> &v2)
{
   if (gMatrixCheck) {
      if (!AreCompatible(v1,v2)) {
         //Error("operator*(const TVectorT<Element> &,const TVectorT<Element> &)","vector's are incompatible");
         return 0.0;
      }
   }

   return Dot(v1,v2);
}

////////////////////////////////////////////////////////////////////////////////
/// Return source1+source2

template<class Element>
TVectorT<Element> operator+(const TVectorT<Element> &source1,const TVectorT<Element> &source2)
{
   TVectorT<Element> target = source1;
   target += source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Return source1-source2

template<class Element>
TVectorT<Element> operator-(const TVectorT<Element> &source1,const TVectorT<Element> &source2)
{
   TVectorT<Element> target = source1;
   target -= source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// return A * source

template<class Element>
TVectorT<Element> operator*(const TMatrixT<Element> &a,const TVectorT<Element> &source)
{
   //R__ASSERT(a.IsValid());
   TVectorT<Element> target(a.GetRowLwb(),a.GetRowUpb());
   return Add(target,Element(1.0),a,source);
}

////////////////////////////////////////////////////////////////////////////////
/// return A * source

template<class Element>
TVectorT<Element> operator*(const TMatrixTSym<Element> &a,const TVectorT<Element> &source)
{
   //R__ASSERT(a.IsValid());
   TVectorT<Element> target(a.GetRowLwb(),a.GetRowUpb());
   return Add(target,Element(1.0),a,source);
}

////////////////////////////////////////////////////////////////////////////////
/// return A * source

template<class Element>
TVectorT<Element> operator*(const TMatrixTSparse<Element> &a,const TVectorT<Element> &source)
{
   //R__ASSERT(a.IsValid());
   TVectorT<Element> target(a.GetRowLwb(),a.GetRowUpb());
   return Add(target,Element(1.0),a,source);
}

////////////////////////////////////////////////////////////////////////////////
/// return val * source

template<class Element>
TVectorT<Element> operator*(Element val,const TVectorT<Element> &source)
{
   TVectorT<Element> target = source;
   target *= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// return inner-produvt v1 . v2

template<class Element>
Element Dot(const TVectorT<Element> &v1,const TVectorT<Element> &v2)
{
   const Element *v1p = v1.GetMatrixArray();
   const Element *v2p = v2.GetMatrixArray();
   Element sum = 0.0;
   const Element * const fv1p = v1p+v1.GetNrows();
   while (v1p < fv1p)
      sum += *v1p++ * *v2p++;

   return sum;
}

////////////////////////////////////////////////////////////////////////////////
/// Return the matrix M = v1 * v2'

template <class Element1, class Element2>
TMatrixT<Element1>
OuterProduct(const TVectorT<Element1> &v1,const TVectorT<Element2> &v2)
{
   // TMatrixD::GetSub does:
   //   TMatrixT tmp;
   // Doesn't compile here, because we are outside the class?
   // So we'll be explicit:
   TMatrixT<Element1> target;

   return OuterProduct(target,v1,v2);
}

////////////////////////////////////////////////////////////////////////////////
/// Return the matrix M = v1 * v2'

template <class Element1,class Element2,class Element3>
TMatrixT<Element1>
&OuterProduct(TMatrixT<Element1> &target,const TVectorT<Element2> &v1,const TVectorT<Element3> &v2)
{
   target.ResizeTo(v1.GetLwb(), v1.GetUpb(), v2.GetLwb(), v2.GetUpb());

         Element1 *       mp      = target.GetMatrixArray();
   const Element1 * const m_last  = mp + target.GetNoElements();

   const Element2 *       v1p     = v1.GetMatrixArray();
   const Element2 * const v1_last = v1p + v1.GetNrows();

   const Element3 * const v20     = v2.GetMatrixArray();
   const Element3 *       v2p     = v20;
   const Element3 * const v2_last = v2p + v2.GetNrows();

   while (v1p < v1_last) {
      v2p = v20;
      while (v2p < v2_last) {
         *mp++ = *v1p * *v2p++ ;
      }
      v1p++;
  }

  //R__ASSERT(v1p == v1_last && mp == m_last && v2p == v2_last);

  return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Perform v1 * M * v2, a scalar result

template <class Element1, class Element2, class Element3>
Element1 Mult(const TVectorT<Element1> &v1,const TMatrixT<Element2> &m,
              const TVectorT<Element3> &v2)
{
   if (gMatrixCheck) {
      if (!AreCompatible(v1, m)) {
         //::Error("Mult", "Vector v1 and matrix m incompatible");
         return 0;
      }
      if (!AreCompatible(m, v2)) {
         //::Error("Mult", "Matrix m and vector v2 incompatible");
         return 0;
      }
   }

   const Element1 *       v1p     = v1.GetMatrixArray();    // first of v1
   const Element1 * const v1_last = v1p + v1.GetNrows();    // last of  v1

   const Element2 *       mp      = m.GetMatrixArray();     // first of m
   const Element2 * const m_last  = mp + m.GetNoElements(); // last of  m

   const Element3 * const v20     = v2.GetMatrixArray();    // first of v2
   const Element3 *       v2p     = v20;                    // running  v2
   const Element3 * const v2_last = v2p + v2.GetNrows();    // last of  v2

   Element1 sum     = 0;      // scalar result accumulator
   Element3 dot     = 0;      // M_row * v2 dot product accumulator

   while (v1p < v1_last) {
      v2p  = v20;               // at beginning of v2
      while (v2p < v2_last) {   // compute (M[i] * v2) dot product
         dot += *mp++ * *v2p++;
      }
      sum += *v1p++ * dot;      // v1[i] * (M[i] * v2)
      dot  = 0;                 // start next dot product
   }

   //R__ASSERT(v1p == v1_last && mp == m_last && v2p == v2_last);

   return sum;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * source.

template<class Element>
TVectorT<Element> &Add(TVectorT<Element> &target,Element scalar,const TVectorT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //Error("Add(TVectorT<Element> &,Element,const TVectorT<Element> &)","vector's are incompatible");
      return target;
   }

   const Element *       sp  = source.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();
   if (scalar == 1.0 ) {
      while ( tp < ftp )
         *tp++ += *sp++;
   } else if (scalar == -1.0) {
      while ( tp < ftp )
         *tp++ -= *sp++;
   } else {
      while ( tp < ftp )
         *tp++ += scalar * *sp++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * A * source.
/// NOTE: in case scalar=0, do  target = A * source.

template<class Element>
TVectorT<Element> &Add(TVectorT<Element> &target,Element scalar,
                       const TMatrixT<Element> &a,const TVectorT<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(target.IsValid());
      //R__ASSERT(a.IsValid());
      if (a.GetNrows() != target.GetNrows() || a.GetRowLwb() != target.GetLwb()) {
         //Error("Add(TVectorT &,const TMatrixT &,const TVectorT &)","target vector and matrix are incompatible");
         return target;
      }

      //R__ASSERT(source.IsValid());
      if (a.GetNcols() != source.GetNrows() || a.GetColLwb() != source.GetLwb()) {
         //Error("Add(TVectorT &,const TMatrixT &,const TVectorT &)","source vector and matrix are incompatible");
         return target;
      }
   }

   const Element * const sp = source.GetMatrixArray();  // sources vector ptr
   const Element *       mp = a.GetMatrixArray();       // Matrix row ptr
         Element *       tp = target.GetMatrixArray();  // Target vector ptr
#ifdef CBLAS
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymv(CblasRowMajor,CblasUpper,fNrows,scalar,mp,
                  fNrows,sp,1,0.0,tp,1);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymv(CblasRowMajor,CblasUpper,fNrows,scalar,mp,
                  fNrows,sp,1,0.0,tp,1);
   //else
      //Error("operator*=","type %s not implemented in BLAS library",typeid(Element));
#else
   const Element * const sp_last = sp+source.GetNrows();
   const Element * const tp_last = tp+target.GetNrows();
   if (scalar == 1.0) {
      while (tp < tp_last) {
         const Element *sp1 = sp;
         Element sum = 0;
         while (sp1 < sp_last)
            sum += *sp1++ * *mp++;
         *tp++ += sum;
      }
   } else if (scalar == 0.0) {
      while (tp < tp_last) {
         const Element *sp1 = sp;
         Element sum = 0;
         while (sp1 < sp_last)
            sum += *sp1++ * *mp++;
         *tp++  = sum;
      }
   } else if (scalar == -1.0) {
      while (tp < tp_last) {
         const Element *sp1 = sp;
         Element sum = 0;
         while (sp1 < sp_last)
            sum += *sp1++ * *mp++;
         *tp++ -= sum;
      }
   } else {
      while (tp < tp_last) {
        const Element *sp1 = sp;
        Element sum = 0;
        while (sp1 < sp_last)
           sum += *sp1++ * *mp++;
        *tp++ += scalar * sum;
      }
   }

   if (gMatrixCheck) {} //R__ASSERT(mp == a.GetMatrixArray()+a.GetNoElements());
#endif

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += A * source.
/// NOTE: in case scalar=0, do  target = A * source.

template<class Element>
TVectorT<Element> &Add(TVectorT<Element> &target,Element scalar,
                       const TMatrixTSym<Element> &a,const TVectorT<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(target.IsValid());
      //R__ASSERT(source.IsValid());
      //R__ASSERT(a.IsValid());
      if (a.GetNrows() != target.GetNrows() || a.GetRowLwb() != target.GetLwb()) {
         //Error("Add(TVectorT &,const TMatrixT &,const TVectorT &)","target vector and matrix are incompatible");
         return target;
      }
   }

   const Element * const sp = source.GetMatrixArray();  // sources vector ptr
   const Element *       mp = a.GetMatrixArray();       // Matrix row ptr
         Element *       tp = target.GetMatrixArray();  // Target vector ptr
#ifdef CBLAS
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymv(CblasRowMajor,CblasUpper,fNrows,1.0,mp,
                  fNrows,sp,1,0.0,tp,1);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymv(CblasRowMajor,CblasUpper,fNrows,1.0,mp,
                  fNrows,sp,1,0.0,tp,1);
   //else
      //Error("operator*=","type %s not implemented in BLAS library",typeid(Element));
#else
   const Element * const sp_last = sp+source.GetNrows();
   const Element * const tp_last = tp+target.GetNrows();
   if (scalar == 1.0) {
      while (tp < tp_last) {
         const Element *sp1 = sp;
         Element sum = 0;
         while (sp1 < sp_last)
            sum += *sp1++ * *mp++;
         *tp++ += sum;
      }
   } else if (scalar == 0.0) {
      while (tp < tp_last) {
         const Element *sp1 = sp;
         Element sum = 0;
         while (sp1 < sp_last)
            sum += *sp1++ * *mp++;
         *tp++  = sum;
      }
   } else if (scalar == -1.0) {
      while (tp < tp_last) {
         const Element *sp1 = sp;
         Element sum = 0;
         while (sp1 < sp_last)
            sum += *sp1++ * *mp++;
         *tp++ -= sum;
      }
   } else {
      while (tp < tp_last) {
         const Element *sp1 = sp;
         Element sum = 0;
         while (sp1 < sp_last)
            sum += *sp1++ * *mp++;
         *tp++ += scalar * sum;
      }
   }
   //R__ASSERT(mp == a.GetMatrixArray()+a.GetNoElements());
#endif

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += A * source.
/// NOTE: in case scalar=0, do  target = A * source.

template<class Element>
TVectorT<Element> &Add(TVectorT<Element> &target,Element scalar,
                       const TMatrixTSparse<Element> &a,const TVectorT<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(target.IsValid());
      //R__ASSERT(a.IsValid());
      if (a.GetNrows() != target.GetNrows() || a.GetRowLwb() != target.GetLwb()) {
         //Error("Add(TVectorT &,const TMatrixT &,const TVectorT &)","target vector and matrix are incompatible");
         return target;
      }

      //R__ASSERT(source.IsValid());
      if (a.GetNcols() != source.GetNrows() || a.GetColLwb() != source.GetLwb()) {
         //Error("Add(TVectorT &,const TMatrixT &,const TVectorT &)","source vector and matrix are incompatible");
         return target;
      }
   }

   const Int_t   * const pRowIndex = a.GetRowIndexArray();
   const Int_t   * const pColIndex = a.GetColIndexArray();
   const Element * const mp        = a.GetMatrixArray();     // Matrix row ptr

   const Element * const sp = source.GetMatrixArray(); // Source vector ptr
         Element *       tp = target.GetMatrixArray(); // Target vector ptr

   if (scalar == 1.0) {
      for (Int_t irow = 0; irow < a.GetNrows(); irow++) {
         const Int_t sIndex = pRowIndex[irow];
         const Int_t eIndex = pRowIndex[irow+1];
         Element sum = 0.0;
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = pColIndex[index];
            sum += mp[index]*sp[icol];
         }
         tp[irow] += sum;
      }
   } else if (scalar == 0.0) {
      for (Int_t irow = 0; irow < a.GetNrows(); irow++) {
         const Int_t sIndex = pRowIndex[irow];
         const Int_t eIndex = pRowIndex[irow+1];
         Element sum = 0.0;
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = pColIndex[index];
            sum += mp[index]*sp[icol];
         }
         tp[irow]  = sum;
      }
   } else if (scalar == -1.0) {
     for (Int_t irow = 0; irow < a.GetNrows(); irow++) {
        const Int_t sIndex = pRowIndex[irow];
        const Int_t eIndex = pRowIndex[irow+1];
        Element sum = 0.0;
        for (Int_t index = sIndex; index < eIndex; index++) {
           const Int_t icol = pColIndex[index];
           sum += mp[index]*sp[icol];
        }
        tp[irow] -= sum;
      }
   } else {
      for (Int_t irow = 0; irow < a.GetNrows(); irow++) {
        const Int_t sIndex = pRowIndex[irow];
        const Int_t eIndex = pRowIndex[irow+1];
        Element sum = 0.0;
        for (Int_t index = sIndex; index < eIndex; index++) {
           const Int_t icol = pColIndex[index];
           sum += mp[index]*sp[icol];
        }
        tp[irow] += scalar * sum;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * ElementMult(source1,source2) .

template<class Element>
TVectorT<Element> &AddElemMult(TVectorT<Element> &target,Element scalar,
                      const TVectorT<Element> &source1,const TVectorT<Element> &source2)
{
   if (gMatrixCheck && !(AreCompatible(target,source1) && AreCompatible(target,source2))) {
      //Error("AddElemMult(TVectorT<Element> &,Element,const TVectorT<Element> &,const TVectorT<Element> &)",
            // "vector's are incompatible");
      return target;
   }

   const Element *       sp1 = source1.GetMatrixArray();
   const Element *       sp2 = source2.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();

   if (scalar == 1.0 ) {
      while ( tp < ftp )
         *tp++ += *sp1++ * *sp2++;
   } else if (scalar == -1.0) {
      while ( tp < ftp )
         *tp++ -= *sp1++ * *sp2++;
   } else {
      while ( tp < ftp )
         *tp++ += scalar * *sp1++ * *sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * ElementMult(source1,source2) only for those elements
/// where select[i] != 0.0

template<class Element>
TVectorT<Element> &AddElemMult(TVectorT<Element> &target,Element scalar,
                      const TVectorT<Element> &source1,const TVectorT<Element> &source2,const TVectorT<Element> &select)
{
   if (gMatrixCheck && !( AreCompatible(target,source1) && AreCompatible(target,source2) &&
          AreCompatible(target,select) )) {
      //Error("AddElemMult(TVectorT<Element> &,Element,const TVectorT<Element> &,const TVectorT<Element> &,onst TVectorT<Element> &)",
             //"vector's are incompatible");
      return target;
   }

   const Element *       sp1 = source1.GetMatrixArray();
   const Element *       sp2 = source2.GetMatrixArray();
   const Element *       mp  = select.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();

   if (scalar == 1.0 ) {
      while ( tp < ftp ) {
         if (*mp) *tp += *sp1 * *sp2;
         mp++; tp++; sp1++; sp2++;
      }
   } else if (scalar == -1.0) {
      while ( tp < ftp ) {
         if (*mp) *tp -= *sp1 * *sp2;
         mp++; tp++; sp1++; sp2++;
      }
   } else {
      while ( tp < ftp ) {
         if (*mp) *tp += scalar * *sp1 * *sp2;
         mp++; tp++; sp1++; sp2++;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * ElementDiv(source1,source2) .

template<class Element>
TVectorT<Element> &AddElemDiv(TVectorT<Element> &target,Element scalar,
                     const TVectorT<Element> &source1,const TVectorT<Element> &source2)
{
   if (gMatrixCheck && !(AreCompatible(target,source1) && AreCompatible(target,source2))) {
      //Error("AddElemDiv(TVectorT<Element> &,Element,const TVectorT<Element> &,const TVectorT<Element> &)",
             //"vector's are incompatible");
      return target;
   }

   const Element *       sp1 = source1.GetMatrixArray();
   const Element *       sp2 = source2.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();

   if (scalar == 1.0 ) {
      while ( tp < ftp ) {
         if (*sp2 != 0.0)
            *tp += *sp1 / *sp2;
         else {
            const Int_t irow = (sp2-source2.GetMatrixArray())/source2.GetNrows();
            //Error("AddElemDiv","source2 (%d) is zero",irow);
         }
         tp++; sp1++; sp2++;
      }
   } else if (scalar == -1.0) {
      while ( tp < ftp ) {
         if (*sp2 != 0.0)
            *tp -= *sp1 / *sp2;
         else {
            const Int_t irow = (sp2-source2.GetMatrixArray())/source2.GetNrows();
            //Error("AddElemDiv","source2 (%d) is zero",irow);
         }
         tp++; sp1++; sp2++;
      }
   } else {
      while ( tp < ftp ) {
         if (*sp2 != 0.0)
            *tp += scalar * *sp1 / *sp2;
         else {
            const Int_t irow = (sp2-source2.GetMatrixArray())/source2.GetNrows();
            //Error("AddElemDiv","source2 (%d) is zero",irow);
         }
         tp++; sp1++; sp2++;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * ElementDiv(source1,source2) only for those elements
/// where select[i] != 0.0

template<class Element>
TVectorT<Element> &AddElemDiv(TVectorT<Element> &target,Element scalar,
                     const TVectorT<Element> &source1,const TVectorT<Element> &source2,const TVectorT<Element> &select)
{
   if (gMatrixCheck && !( AreCompatible(target,source1) && AreCompatible(target,source2) &&
          AreCompatible(target,select) )) {
      //Error("AddElemDiv(TVectorT<Element> &,Element,const TVectorT<Element> &,const TVectorT<Element> &,onst TVectorT<Element> &)",
             //"vector's are incompatible");
      return target;
   }

   const Element *       sp1 = source1.GetMatrixArray();
   const Element *       sp2 = source2.GetMatrixArray();
   const Element *       mp  = select.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();

   if (scalar == 1.0 ) {
      while ( tp < ftp ) {
         if (*mp) {
            if (*sp2 != 0.0)
               *tp += *sp1 / *sp2;
            else {
               const Int_t irow = (sp2-source2.GetMatrixArray())/source2.GetNrows();
               //Error("AddElemDiv","source2 (%d) is zero",irow);
            }
         }
         mp++; tp++; sp1++; sp2++;
      }
   } else if (scalar == -1.0) {
      while ( tp < ftp ) {
         if (*mp) {
            if (*sp2 != 0.0)
               *tp -= *sp1 / *sp2;
            else {
               const Int_t irow = (sp2-source2.GetMatrixArray())/source2.GetNrows();
               //Error("AddElemDiv","source2 (%d) is zero",irow);
            }
         }
         mp++; tp++; sp1++; sp2++;
      }
   } else {
      while ( tp < ftp ) {
         if (*mp) {
            if (*sp2 != 0.0)
               *tp += scalar * *sp1 / *sp2;
            else {
               const Int_t irow = (sp2-source2.GetMatrixArray())/source2.GetNrows();
               //Error("AddElemDiv","source2 (%d) is zero",irow);
            }
         }
         mp++; tp++; sp1++; sp2++;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element.

template<class Element>
TVectorT<Element> &ElementMult(TVectorT<Element> &target,const TVectorT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //Error("ElementMult(TVectorT<Element> &,const TVectorT<Element> &)","vector's are incompatible");
      return target;
   }

   const Element *       sp  = source.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();
   while ( tp < ftp )
      *tp++ *= *sp++;

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element only where select[i] != 0.0

template<class Element>
TVectorT<Element> &ElementMult(TVectorT<Element> &target,const TVectorT<Element> &source,const TVectorT<Element> &select)
{
   if (gMatrixCheck && !(AreCompatible(target,source) && AreCompatible(target,select))) {
      //Error("ElementMult(TVectorT<Element> &,const TVectorT<Element> &,const TVectorT<Element> &)","vector's are incompatible");
      return target;
   }

   const Element *       sp  = source.GetMatrixArray();
   const Element *       mp  = select.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();
   while ( tp < ftp ) {
      if (*mp) *tp *= *sp;
      mp++; tp++; sp++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Divide target by the source, element-by-element.

template<class Element>
TVectorT<Element> &ElementDiv(TVectorT<Element> &target,const TVectorT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //Error("ElementDiv(TVectorT<Element> &,const TVectorT<Element> &)","vector's are incompatible");
      return target;
   }

   const Element *       sp  = source.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();
   while ( tp < ftp ) {
      if (*sp  != 0.0)
         *tp++ /= *sp++;
      else {
         const Int_t irow = (sp-source.GetMatrixArray())/source.GetNrows();
         //Error("ElementDiv","source (%d) is zero",irow);
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Divide target by the source, element-by-element only where select[i] != 0.0

template<class Element>
TVectorT<Element> &ElementDiv(TVectorT<Element> &target,const TVectorT<Element> &source,const TVectorT<Element> &select)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //Error("ElementDiv(TVectorT<Element> &,const TVectorT<Element> &,const TVectorT<Element> &)","vector's are incompatible");
      return target;
   }

   const Element *       sp  = source.GetMatrixArray();
   const Element *       mp  = select.GetMatrixArray();
         Element *       tp  = target.GetMatrixArray();
   const Element * const ftp = tp+target.GetNrows();
   while ( tp < ftp ) {
      if (*mp) {
         if (*sp != 0.0)
            *tp /= *sp;
         else {
            const Int_t irow = (sp-source.GetMatrixArray())/source.GetNrows();
            //Error("ElementDiv","source (%d) is zero",irow);
         }
      }
      mp++; tp++; sp++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Check if v1 and v2 are both valid and have the same shape

template<class Element1,class Element2>
Bool_t AreCompatible(const TVectorT<Element1> &v1,const TVectorT<Element2> &v2,Int_t verbose)
{
   //if (!v1.IsValid()) {
      //if (verbose)
         //::Error("AreCompatible", "vector 1 not valid");
      //return kFALSE;
   //}
   //if (!v2.IsValid()) {
      //if (verbose)
         //::Error("AreCompatible", "vector 2 not valid");
      //return kFALSE;
   //}

   if (v1.GetNrows() != v2.GetNrows() || v1.GetLwb() != v2.GetLwb()) {
      if (verbose) {}
         //::Error("AreCompatible", "matrices 1 and 2 not compatible");
      return kFALSE;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Check if m and v are both valid and have compatible shapes for M * v

template<class Element1, class Element2>
Bool_t AreCompatible(const TMatrixT<Element1> &m,const TVectorT<Element2> &v,Int_t verbose)
{
   /*if (!m.IsValid()) {
      if (verbose)
         //::Error("AreCompatible", "Matrix not valid");
      return kFALSE;
   }
   if (!v.IsValid()) {
      if (verbose)
         //::Error("AreCompatible", "vector not valid");
      return kFALSE;
   }*/

   if (m.GetNcols() != v.GetNrows() ) {
      if (verbose) {}
         //::Error("AreCompatible", "matrix and vector not compatible");
      return kFALSE;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Check if m and v are both valid and have compatible shapes for v * M

template<class Element1, class Element2>
Bool_t AreCompatible(const TVectorT<Element1> &v,const TMatrixT<Element2> &m,Int_t verbose)
{
   /*if (!m.IsValid()) {
      if (verbose)
         //::Error("AreCompatible", "Matrix not valid");
      return kFALSE;
   }
   if (!v.IsValid()) {
      if (verbose)
         //::Error("AreCompatible", "vector not valid");
      return kFALSE;
   }*/

   if (v.GetNrows() != m.GetNrows() ) {
      if (verbose) {}
         //::Error("AreCompatible", "vector and matrix not compatible");
      return kFALSE;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Compare two vectors and print out the result of the comparison.

template<class Element>
void Compare(const TVectorT<Element> &v1,const TVectorT<Element> &v2)
{
   if (!AreCompatible(v1,v2)) {
      //Error("Compare(const TVectorT<Element> &,const TVectorT<Element> &)","vectors are incompatible");
      return;
   }

   printf("\n\nComparison of two TVectorTs:\n");

   Element norm1  = 0;       // Norm of the Matrices
   Element norm2  = 0;       // Norm of the Matrices
   Element ndiff  = 0;       // Norm of the difference
   Int_t    imax   = 0;       // For the elements that differ most
   Element difmax = -1;
   const Element *mp1 = v1.GetMatrixArray();    // Vector element pointers
   const Element *mp2 = v2.GetMatrixArray();

   for (Int_t i = 0; i < v1.GetNrows(); i++) {
      const Element mv1  = *mp1++;
      const Element mv2  = *mp2++;
      const Element diff = TMath::Abs(mv1-mv2);

      if (diff > difmax) {
         difmax = diff;
         imax = i;
      }
      norm1 += TMath::Abs(mv1);
      norm2 += TMath::Abs(mv2);
      ndiff += TMath::Abs(diff);
   }

   imax += v1.GetLwb();
   printf("\nMaximal discrepancy    \t\t%g",difmax);
   printf("\n   occured at the point\t\t(%d)",imax);
   const Element mv1 = v1(imax);
   const Element mv2 = v2(imax);
   printf("\n Vector 1 element is    \t\t%g",mv1);
   printf("\n Vector 2 element is    \t\t%g",mv2);
   printf("\n Absolute error v2[i]-v1[i]\t\t%g",mv2-mv1);
   printf("\n Relative error\t\t\t\t%g\n",
          (mv2-mv1)/TMath::Max(TMath::Abs(mv2+mv1)/2,(Element)1e-7));

   printf("\n||Vector 1||   \t\t\t%g",norm1);
   printf("\n||Vector 2||   \t\t\t%g",norm2);
   printf("\n||Vector1-Vector2||\t\t\t\t%g",ndiff);
   printf("\n||Vector1-Vector2||/sqrt(||Vector1|| ||Vector2||)\t%g\n\n",
          ndiff/TMath::Max(TMath::Sqrt(norm1*norm2),1e-7));
}

////////////////////////////////////////////////////////////////////////////////
/// Validate that all elements of vector have value val within maxDevAllow .

template<class Element>
Bool_t VerifyVectorValue(const TVectorT<Element> &v,Element val,
                         Int_t verbose,Element maxDevAllow)
{
   Int_t   imax      = 0;
   Element maxDevObs = 0;

   if (TMath::Abs(maxDevAllow) <= 0.0)
      maxDevAllow = std::numeric_limits<Element>::epsilon();

   for (Int_t i = v.GetLwb(); i <= v.GetUpb(); i++) {
      const Element dev = TMath::Abs(v(i)-val);
      if (dev > maxDevObs) {
         imax      = i;
         maxDevObs = dev;
      }
   }

   if (maxDevObs == 0)
      return kTRUE;

   if (verbose) {
      printf("Largest dev for (%d); dev = |%g - %g| = %g\n",imax,v(imax),val,maxDevObs);
      if (maxDevObs > maxDevAllow) {}
         //Error("VerifyVectorValue","Deviation > %g\n",maxDevAllow);
   }

   if (maxDevObs > maxDevAllow)
      return kFALSE;
   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Verify that elements of the two vectors are equal within maxDevAllow .

template<class Element>
Bool_t VerifyVectorIdentity(const TVectorT<Element> &v1,const TVectorT<Element> &v2,
                            Int_t verbose, Element maxDevAllow)
{
   Int_t   imax      = 0;
   Element maxDevObs = 0;

   if (!AreCompatible(v1,v2))
      return kFALSE;

   if (TMath::Abs(maxDevAllow) <= 0.0)
      maxDevAllow = std::numeric_limits<Element>::epsilon();

   for (Int_t i = v1.GetLwb(); i <= v1.GetUpb(); i++) {
      const Element dev = TMath::Abs(v1(i)-v2(i));
      if (dev > maxDevObs) {
         imax      = i;
         maxDevObs = dev;
      }
   }

   if (maxDevObs == 0)
      return kTRUE;

   if (verbose) {
      printf("Largest dev for (%d); dev = |%g - %g| = %g\n",imax,v1(imax),v2(imax),maxDevObs);
      if (maxDevObs > maxDevAllow) {}
         //Error("VerifyVectorIdentity","Deviation > %g\n",maxDevAllow);
   }

   if (maxDevObs > maxDevAllow) {
      return kFALSE;
   }
   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Stream an object of class TVectorT.
/*
template<class Element>
void TVectorT<Element>::Streamer(TBuffer &R__b)
{
   if (R__b.IsReading()) {
      UInt_t R__s, R__c;
      Version_t R__v = R__b.ReadVersion(&R__s,&R__c);
      if (R__v > 1) {
         Clear();
         R__b.ReadClassBuffer(TVectorT<Element>::Class(),this,R__v,R__s,R__c);
      } else { //====process old versions before automatic schema evolution
         TObject::Streamer(R__b);
         R__b >> fRowLwb;
         fNrows = R__b.ReadArray(fElements);
         R__b.CheckByteCount(R__s, R__c, TVectorT<Element>::IsA());
      }
      if (fNrows > 0 && fNrows <= kSizeMax) {
         memcpy(fDataStack,fElements,fNrows*sizeof(Element));
         delete [] fElements;
         fElements = fDataStack;
      } else if (fNrows < 0)
         Invalidate();

      if (R__v < 3)
         MakeValid();
    } else {
       R__b.WriteClassBuffer(TVectorT<Element>::Class(),this);
   }
}
*/
//#include "TMatrixFfwd.h"
//#include "TMatrixFSymfwd.h"
//#include "TMatrixFSparsefwd.h"

template class TVectorT<Float_t>;

template Bool_t    operator==          <Float_t>(const TVectorF       &source1,const TVectorF &source2);
template TVectorF  operator+           <Float_t>(const TVectorF       &source1,const TVectorF &source2);
template TVectorF  operator-           <Float_t>(const TVectorF       &source1,const TVectorF &source2);
template Float_t   operator*           <Float_t>(const TVectorF       &source1,const TVectorF &source2);
template TVectorF  operator*           <Float_t>(const TMatrixF       &a,      const TVectorF &source);
template TVectorF  operator*           <Float_t>(const TMatrixFSym    &a,      const TVectorF &source);
template TVectorF  operator*           <Float_t>(const TMatrixFSparse &a,      const TVectorF &source);
template TVectorF  operator*           <Float_t>(      Float_t         val,    const TVectorF &source);

template Float_t   Dot                 <Float_t>(const TVectorF       &v1,     const TVectorF &v2);
template TMatrixF  OuterProduct        <Float_t,Float_t>
                                                (const TVectorF       &v1,     const TVectorF &v2);
template TMatrixF &OuterProduct        <Float_t,Float_t,Float_t>
                                                (      TMatrixF       &target, const TVectorF &v1,     const TVectorF       &v2);
template Float_t   Mult                <Float_t,Float_t,Float_t>
                                                (const TVectorF       &v1,     const TMatrixF &m,      const TVectorF       &v2);

template TVectorF &Add                 <Float_t>(      TVectorF       &target,       Float_t   scalar, const TVectorF       &source);
template TVectorF &Add                 <Float_t>(      TVectorF       &target,       Float_t   scalar, const TMatrixF       &a,
                                                                               const TVectorF &source);
template TVectorF &Add                 <Float_t>(      TVectorF       &target,       Float_t   scalar, const TMatrixFSym    &a,
                                                                               const TVectorF &source);
template TVectorF &Add                 <Float_t>(      TVectorF       &target,       Float_t   scalar, const TMatrixFSparse &a,
                                                                               const TVectorF &source);
template TVectorF &AddElemMult         <Float_t>(      TVectorF       &target,       Float_t   scalar, const TVectorF       &source1,
                                                                               const TVectorF &source2);
template TVectorF &AddElemMult         <Float_t>(      TVectorF       &target,       Float_t   scalar, const TVectorF       &source1,
                                                                               const TVectorF &source2,const TVectorF       &select);
template TVectorF &AddElemDiv          <Float_t>(      TVectorF       &target,       Float_t   scalar, const TVectorF       &source1,
                                                                               const TVectorF &source2);
template TVectorF &AddElemDiv          <Float_t>(      TVectorF       &target,       Float_t   scalar, const TVectorF       &source1,
                                                                               const TVectorF &source2,const TVectorF       &select);
template TVectorF &ElementMult         <Float_t>(      TVectorF       &target, const TVectorF &source);
template TVectorF &ElementMult         <Float_t>(      TVectorF       &target, const TVectorF &source, const TVectorF       &select);
template TVectorF &ElementDiv          <Float_t>(      TVectorF       &target, const TVectorF &source);
template TVectorF &ElementDiv          <Float_t>(      TVectorF       &target, const TVectorF &source, const TVectorF       &select);

template Bool_t    AreCompatible       <Float_t,Float_t> (const TVectorF &v1,const TVectorF &v2,Int_t verbose);
template Bool_t    AreCompatible       <Float_t,Double_t>(const TVectorF &v1,const TVectorD &v2,Int_t verbose);
template Bool_t    AreCompatible       <Float_t,Float_t> (const TMatrixF &m, const TVectorF &v, Int_t verbose);
template Bool_t    AreCompatible       <Float_t,Float_t> (const TVectorF &v, const TMatrixF &m, Int_t verbose);

template void      Compare             <Float_t>         (const TVectorF &v1,const TVectorF &v2);
template Bool_t    VerifyVectorValue   <Float_t>         (const TVectorF &m,       Float_t   val,Int_t verbose,Float_t maxDevAllow);
template Bool_t    VerifyVectorIdentity<Float_t>         (const TVectorF &m1,const TVectorF &m2, Int_t verbose,Float_t maxDevAllow);

//#include "TMatrixDfwd.h"
//#include "TMatrixDSymfwd.h"
//#include "TMatrixDSparsefwd.h"

template class TVectorT<Double_t>;

template Bool_t    operator==          <Double_t>(const TVectorD       &source1,const TVectorD &source2);
template TVectorD  operator+           <Double_t>(const TVectorD       &source1,const TVectorD &source2);
template TVectorD  operator-           <Double_t>(const TVectorD       &source1,const TVectorD &source2);
template Double_t  operator*           <Double_t>(const TVectorD       &source1,const TVectorD &source2);
template TVectorD  operator*           <Double_t>(const TMatrixD       &a,      const TVectorD &source);
template TVectorD  operator*           <Double_t>(const TMatrixDSym    &a,      const TVectorD &source);
template TVectorD  operator*           <Double_t>(const TMatrixDSparse &a,      const TVectorD &source);
template TVectorD  operator*           <Double_t>(      Double_t        val,    const TVectorD &source);

template Double_t  Dot                 <Double_t>(const TVectorD       &v1,     const TVectorD &v2);
template TMatrixD  OuterProduct        <Double_t,Double_t>
                                                 (const TVectorD       &v1,     const TVectorD &v2);
template TMatrixD &OuterProduct        <Double_t,Double_t,Double_t>
                                                 (      TMatrixD       &target, const TVectorD &v1,     const TVectorD       &v2);
template Double_t  Mult                <Double_t,Double_t,Double_t>
                                                 (const TVectorD       &v1,     const TMatrixD &m,      const TVectorD       &v2);

template TVectorD &Add                 <Double_t>(      TVectorD       &target,       Double_t  scalar, const TVectorD       &source);
template TVectorD &Add                 <Double_t>(      TVectorD       &target,       Double_t  scalar, const TMatrixD       &a,
                                                                                const TVectorD &source);
template TVectorD &Add                 <Double_t>(      TVectorD       &target,       Double_t  scalar, const TMatrixDSym    &a
                                                                                ,      const TVectorD &source);
template TVectorD &Add                 <Double_t>(      TVectorD       &target,       Double_t  scalar, const TMatrixDSparse &a
                                                                                ,      const TVectorD &source);
template TVectorD &AddElemMult         <Double_t>(      TVectorD       &target,       Double_t  scalar, const TVectorD       &source1,
                                                                                const TVectorD &source2);
template TVectorD &AddElemMult         <Double_t>(      TVectorD       &target,       Double_t  scalar, const TVectorD       &source1,
                                                                                const TVectorD &source2,const TVectorD       &select);
template TVectorD &AddElemDiv          <Double_t>(      TVectorD       &target,       Double_t  scalar, const TVectorD       &source1,
                                                                                const TVectorD &source2);
template TVectorD &AddElemDiv          <Double_t>(      TVectorD       &target,       Double_t  scalar, const TVectorD       &source1,
                                                                                const TVectorD &source2,const TVectorD       &select);
template TVectorD &ElementMult         <Double_t>(      TVectorD       &target, const TVectorD &source);
template TVectorD &ElementMult         <Double_t>(      TVectorD       &target, const TVectorD &source, const TVectorD       &select);
template TVectorD &ElementDiv          <Double_t>(      TVectorD       &target, const TVectorD &source);
template TVectorD &ElementDiv          <Double_t>(      TVectorD       &target, const TVectorD &source, const TVectorD       &select);

template Bool_t    AreCompatible       <Double_t,Double_t>(const TVectorD &v1,const TVectorD &v2,Int_t verbose);
template Bool_t    AreCompatible       <Double_t,Float_t> (const TVectorD &v1,const TVectorF &v2,Int_t verbose);
template Bool_t    AreCompatible       <Double_t,Double_t>(const TMatrixD &m, const TVectorD &v, Int_t verbose);
template Bool_t    AreCompatible       <Double_t,Double_t>(const TVectorD &v, const TMatrixD &m, Int_t verbose);

template void      Compare             <Double_t>         (const TVectorD &v1,const TVectorD &v2);
template Bool_t    VerifyVectorValue   <Double_t>         (const TVectorD &m,       Double_t  val,Int_t verbose,Double_t maxDevAllow);
template Bool_t    VerifyVectorIdentity<Double_t>         (const TVectorD &m1,const TVectorD &m2, Int_t verbose,Double_t maxDevAllow);


// @(#)root/base:$Id$
// Authors: Rene Brun 08/02/2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** TMath Base functions
\ingroup Base

Define the functions Min, Max, Abs, Sign, Range for all types.
NB: These functions are unfortunately not available in a portable
way in std::.

More functions are defined in TMath.h. TMathBase.h is designed to be
a stable file and used in place of TMath.h in the ROOT miniCore.
*/

//#include "TMathBase.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
/// Return next prime number after x, unless x is a prime in which case
/// x is returned.

Long_t TMath::NextPrime(Long_t x)
{
   if (x <= 2)
      return 2;
   if (x == 3)
      return 3;

   if (x % 2 == 0)
      x++;

   Long_t sqr = (Long_t) sqrt((Double_t)x) + 1;

   for (;;) {
      Long_t n;
      for (n = 3; (n <= sqr) && ((x % n) != 0); n += 2)
         ;
      if (n > sqr)
         return x;
      x += 2;
   }
}

// @(#)root/mathcore:$Id$
// Authors: Rene Brun, Anna Kreshuk, Eddy Offermann, Fons Rademakers   29/07/95

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// TMath
//
// Encapsulate math routines.

//#include "TMath.h"
//#include "TError.h"
//#include <math.h>
#include <string.h>
#include <algorithm>
//#include "Riostream.h"
//#include "TString.h"

//#include <Math/SpecFuncMathCore.h>
//#include <Math/PdfFuncMathCore.h>
//#include <Math/ProbFuncMathCore.h>

//const Double_t
//   TMath::Pi = 3.14159265358979323846,
//   TMath::E  = 2.7182818284590452354;


// Without this macro the THtml doc for TMath can not be generated
#if !defined(R__SOLARIS) && !defined(R__ACC) && !defined(R__FBSD)
NamespaceImp(TMath)
#endif

namespace TMath {

   //Double_t GamCf(Double_t a,Double_t x);
   //Double_t GamSer(Double_t a,Double_t x);
   Double_t VavilovDenEval(Double_t rlam, Double_t *AC, Double_t *HC, Int_t itype);
   void VavilovSet(Double_t rkappa, Double_t beta2, Bool_t mode, Double_t *WCM, Double_t *AC, Double_t *HC, Int_t &itype, Int_t &npt);

}

////////////////////////////////////////////////////////////////////////////////

Long_t TMath::Hypot(Long_t x, Long_t y)
{
   return (Long_t) (hypot((Double_t)x, (Double_t)y) + 0.5);
}

////////////////////////////////////////////////////////////////////////////////

Double_t TMath::Hypot(Double_t x, Double_t y)
{
   return hypot(x, y);
}

////////////////////////////////////////////////////////////////////////////////

Double_t TMath::ASinH(Double_t x)
{
#if defined(WIN32)
   if(x==0.0) return 0.0;
   Double_t ax = Abs(x);
   return log(x+ax*sqrt(1.+1./(ax*ax)));
#else
   return asinh(x);
#endif
}

////////////////////////////////////////////////////////////////////////////////

Double_t TMath::ACosH(Double_t x)
{
#if defined(WIN32)
   if(x==0.0) return 0.0;
   Double_t ax = Abs(x);
   return log(x+ax*sqrt(1.-1./(ax*ax)));
#else
   return acosh(x);
#endif
}

////////////////////////////////////////////////////////////////////////////////

Double_t TMath::ATanH(Double_t x)
{
#if defined(WIN32)
   return log((1+x)/(1-x))/2;
#else
   return atanh(x);
#endif
}

////////////////////////////////////////////////////////////////////////////////

Double_t TMath::Log2(Double_t x)
{
   return log(x)/log(2.0);
}

////////////////////////////////////////////////////////////////////////////////
/// The DiLogarithm function
/// Code translated by R.Brun from CERNLIB DILOG function C332

Double_t TMath::DiLog(Double_t x)
{
   const Double_t hf  = 0.5;
   const Double_t pi  = TMath::Pi();
   const Double_t pi2 = pi*pi;
   const Double_t pi3 = pi2/3;
   const Double_t pi6 = pi2/6;
   const Double_t pi12 = pi2/12;
   const Double_t c[20] = {0.42996693560813697, 0.40975987533077105,
     -0.01858843665014592, 0.00145751084062268,-0.00014304184442340,
      0.00001588415541880,-0.00000190784959387, 0.00000024195180854,
     -0.00000003193341274, 0.00000000434545063,-0.00000000060578480,
      0.00000000008612098,-0.00000000001244332, 0.00000000000182256,
     -0.00000000000027007, 0.00000000000004042,-0.00000000000000610,
      0.00000000000000093,-0.00000000000000014, 0.00000000000000002};

   Double_t t,h,y,s,a,alfa,b1,b2,b0;
   t=h=y=s=a=alfa=b1=b2=b0=0.;

   if (x == 1) {
      h = pi6;
   } else if (x == -1) {
      h = -pi12;
   } else {
      t = -x;
      if (t <= -2) {
         y = -1/(1+t);
         s = 1;
         b1= TMath::Log(-t);
         b2= TMath::Log(1+1/t);
         a = -pi3+hf*(b1*b1-b2*b2);
      } else if (t < -1) {
         y = -1-t;
         s = -1;
         a = TMath::Log(-t);
         a = -pi6+a*(a+TMath::Log(1+1/t));
      } else if (t <= -0.5) {
         y = -(1+t)/t;
         s = 1;
         a = TMath::Log(-t);
         a = -pi6+a*(-hf*a+TMath::Log(1+t));
      } else if (t < 0) {
         y = -t/(1+t);
         s = -1;
         b1= TMath::Log(1+t);
         a = hf*b1*b1;
      } else if (t <= 1) {
         y = t;
         s = 1;
         a = 0;
      } else {
         y = 1/t;
         s = -1;
         b1= TMath::Log(t);
         a = pi6+hf*b1*b1;
      }
      h    = y+y-1;
      alfa = h+h;
      b1   = 0;
      b2   = 0;
      for (Int_t i=19;i>=0;i--){
         b0 = c[i] + alfa*b1-b2;
         b2 = b1;
         b1 = b0;
      }
      h = -(s*(b0-h*b2)+a);
   }
   return h;
}

////////////////////////////////////////////////////////////////////////////////
/// Computation of the error function erf(x).
/// Erf(x) = (2/sqrt(pi)) Integral(exp(-t^2))dt between 0 and x
/*
Double_t TMath::Erf(Double_t x)
{
   return ::ROOT::Math::erf(x);
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the complementary error function erfc(x).
/// Erfc(x) = (2/sqrt(pi)) Integral(exp(-t^2))dt between x and infinity
///

Double_t TMath::Erfc(Double_t x)
{
   return ::ROOT::Math::erfc(x);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// returns  the inverse error function
/// x must be  <-1<x<1
/*
Double_t TMath::ErfInverse(Double_t x)
{
   Int_t kMaxit    = 50;
   Double_t kEps   = 1e-14;
   Double_t kConst = 0.8862269254527579;     // sqrt(pi)/2.0

   if(TMath::Abs(x) <= kEps) return kConst*x;

   // Newton iterations
   Double_t erfi, derfi, y0,y1,dy0,dy1;
   if(TMath::Abs(x) < 1.0) {
      erfi  = kConst*TMath::Abs(x);
      y0    = TMath::Erf(0.9*erfi);
      derfi = 0.1*erfi;
      for (Int_t iter=0; iter<kMaxit; iter++) {
         y1  = 1. - TMath::Erfc(erfi);
         dy1 = TMath::Abs(x) - y1;
         if (TMath::Abs(dy1) < kEps)  {if (x < 0) return -erfi; else return erfi;}
         dy0    = y1 - y0;
         derfi *= dy1/dy0;
         y0     = y1;
         erfi  += derfi;
         if(TMath::Abs(derfi/erfi) < kEps) {if (x < 0) return -erfi; else return erfi;}
      }
   }
   return 0; //did not converge
}
*/
////////////////////////////////////////////////////////////////////////////////
/// returns  the inverse of the complementary error function
/// x must be  0<x<2
/// implement using  the quantile of the normal distribution
/// instead of ErfInverse for better numerical precision for large x

Double_t TMath::ErfcInverse(Double_t x)
{

   // erfc-1(x) = - 1/sqrt(2) * normal_quantile( 0.5 * x)
   return - 0.70710678118654752440 * TMath::NormQuantile( 0.5 * x);
}

////////////////////////////////////////////////////////////////////////////////
/// Compute factorial(n).

Double_t TMath::Factorial(Int_t n)
{
   if (n <= 0) return 1.;
   Double_t x = 1;
   Int_t b = 0;
   do {
      b++;
      x *= b;
   } while (b != n);
   return x;
}

////////////////////////////////////////////////////////////////////////////////
/// Computation of the normal frequency function freq(x).
/// Freq(x) = (1/sqrt(2pi)) Integral(exp(-t^2/2))dt between -infinity and x.
///
/// Translated from CERNLIB C300 by Rene Brun.

Double_t TMath::Freq(Double_t x)
{
   const Double_t c1 = 0.56418958354775629;
   const Double_t w2 = 1.41421356237309505;

   const Double_t p10 = 2.4266795523053175e+2,  q10 = 2.1505887586986120e+2,
                  p11 = 2.1979261618294152e+1,  q11 = 9.1164905404514901e+1,
                  p12 = 6.9963834886191355e+0,  q12 = 1.5082797630407787e+1,
                  p13 =-3.5609843701815385e-2,  q13 = 1;

   const Double_t p20 = 3.00459261020161601e+2, q20 = 3.00459260956983293e+2,
                  p21 = 4.51918953711872942e+2, q21 = 7.90950925327898027e+2,
                  p22 = 3.39320816734343687e+2, q22 = 9.31354094850609621e+2,
                  p23 = 1.52989285046940404e+2, q23 = 6.38980264465631167e+2,
                  p24 = 4.31622272220567353e+1, q24 = 2.77585444743987643e+2,
                  p25 = 7.21175825088309366e+0, q25 = 7.70001529352294730e+1,
                  p26 = 5.64195517478973971e-1, q26 = 1.27827273196294235e+1,
                  p27 =-1.36864857382716707e-7, q27 = 1;

   const Double_t p30 =-2.99610707703542174e-3, q30 = 1.06209230528467918e-2,
                  p31 =-4.94730910623250734e-2, q31 = 1.91308926107829841e-1,
                  p32 =-2.26956593539686930e-1, q32 = 1.05167510706793207e+0,
                  p33 =-2.78661308609647788e-1, q33 = 1.98733201817135256e+0,
                  p34 =-2.23192459734184686e-2, q34 = 1;

   Double_t v  = TMath::Abs(x)/w2;
   Double_t vv = v*v;
   Double_t ap, aq, h, hc, y;
   if (v < 0.5) {
      y=vv;
      ap=p13;
      aq=q13;
      ap = p12 +y*ap;
      ap = p11 +y*ap;
      ap = p10 +y*ap;
      aq = q12 +y*aq;
      aq = q11 +y*aq;
      aq = q10 +y*aq;
      h  = v*ap/aq;
      hc = 1-h;
   } else if (v < 4) {
      ap = p27;
      aq = q27;
      ap = p26 +v*ap;
      ap = p25 +v*ap;
      ap = p24 +v*ap;
      ap = p23 +v*ap;
      ap = p22 +v*ap;
      ap = p21 +v*ap;
      ap = p20 +v*ap;
      aq = q26 +v*aq;
      aq = q25 +v*aq;
      aq = q24 +v*aq;
      aq = q23 +v*aq;
      aq = q22 +v*aq;
      aq = q21 +v*aq;
      aq = q20 +v*aq;
      hc = TMath::Exp(-vv)*ap/aq;
      h  = 1-hc;
   } else {
      y  = 1/vv;
      ap = p34;
      aq = q34;
      ap = p33 +y*ap;
      ap = p32 +y*ap;
      ap = p31 +y*ap;
      ap = p30 +y*ap;
      aq = q33 +y*aq;
      aq = q32 +y*aq;
      aq = q31 +y*aq;
      aq = q30 +y*aq;
      hc = TMath::Exp(-vv)*(c1+y*ap/aq)/v;
      h  = 1-hc;
   }
   if (x > 0) return 0.5 +0.5*h;
   else return 0.5*hc;
}

////////////////////////////////////////////////////////////////////////////////
/// Computation of gamma(z) for all z.
///
/// C.Lanczos, SIAM Journal of Numerical Analysis B1 (1964), 86.
/*
Double_t TMath::Gamma(Double_t z)
{
   return ::ROOT::Math::tgamma(z);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computation of the normalized lower incomplete gamma function P(a,x) as defined in the
/// Handbook of Mathematical Functions by Abramowitz and Stegun, formula 6.5.1 on page 260 .
/// Its normalization is such that TMath::Gamma(a,+infinity) = 1 .
///
///  \f[
///  P(a, x) = \frac{1}{\Gamma(a)} \int_{0}^{x} t^{a-1} e^{-t} dt
///  \f]
///
/// \author NvE 14-nov-1998 UU-SAP Utrecht
/*
Double_t TMath::Gamma(Double_t a,Double_t x)
{
   return ::ROOT::Math::inc_gamma(a, x);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computation of the incomplete gamma function P(a,x)
/// via its continued fraction representation.
///
/// \author NvE 14-nov-1998 UU-SAP Utrecht
/*
Double_t TMath::GamCf(Double_t a,Double_t x)
{
   Int_t itmax    = 100;      // Maximum number of iterations
   Double_t eps   = 3.e-14;   // Relative accuracy
   Double_t fpmin = 1.e-30;   // Smallest Double_t value allowed here

   if (a <= 0 || x <= 0) return 0;

   Double_t gln = LnGamma(a);
   Double_t b   = x+1-a;
   Double_t c   = 1/fpmin;
   Double_t d   = 1/b;
   Double_t h   = d;
   Double_t an,del;
   for (Int_t i=1; i<=itmax; i++) {
      an = Double_t(-i)*(Double_t(i)-a);
      b += 2;
      d  = an*d+b;
      if (Abs(d) < fpmin) d = fpmin;
      c = b+an/c;
      if (Abs(c) < fpmin) c = fpmin;
      d   = 1/d;
      del = d*c;
      h   = h*del;
      if (Abs(del-1) < eps) break;
      //if (i==itmax) std::cout << "*GamCf(a,x)* a too large or itmax too small" << std::endl;
   }
   Double_t v = Exp(-x+a*Log(x)-gln)*h;
   return (1-v);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computation of the incomplete gamma function P(a,x)
/// via its series representation.
///
/// \author NvE 14-nov-1998 UU-SAP Utrecht
/*
Double_t TMath::GamSer(Double_t a,Double_t x)
{
   Int_t itmax  = 100;    // Maximum number of iterations
   Double_t eps = 3.e-14; // Relative accuracy

   if (a <= 0 || x <= 0) return 0;

   Double_t gln = LnGamma(a);
   Double_t ap  = a;
   Double_t sum = 1/a;
   Double_t del = sum;
   for (Int_t n=1; n<=itmax; n++) {
      ap  += 1;
      del  = del*x/ap;
      sum += del;
      if (TMath::Abs(del) < Abs(sum*eps)) break;
      //if (n==itmax) std::cout << "*GamSer(a,x)* a too large or itmax too small" << std::endl;
   }
   Double_t v = sum*Exp(-x+a*Log(x)-gln);
   return v;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Calculate a Breit Wigner function with mean and gamma.

Double_t TMath::BreitWigner(Double_t x, Double_t mean, Double_t gamma)
{
   Double_t bw = gamma/((x-mean)*(x-mean) + gamma*gamma/4);
   return bw/(2*Pi());
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate a gaussian function with mean and sigma.
/// If norm=kTRUE (default is kFALSE) the result is divided
/// by sqrt(2*Pi)*sigma.

Double_t TMath::Gaus(Double_t x, Double_t mean, Double_t sigma, Bool_t norm)
{
   if (sigma == 0) return 1.e30;
   Double_t arg = (x-mean)/sigma;
   // for |arg| > 39  result is zero in double precision
   if (arg < -39.0 || arg > 39.0) return 0.0;
   Double_t res = TMath::Exp(-0.5*arg*arg);
   if (!norm) return res;
   return res/(2.50662827463100024*sigma); //sqrt(2*Pi)=2.50662827463100024
}

////////////////////////////////////////////////////////////////////////////////
/// The LANDAU function.
///
/// mu is a location parameter and correspond approximately to the most probable value
/// and sigma is a scale parameter (not the sigma of the full distribution which is not defined)
/// Note that for mu=0 and sigma=1 (default values) the exact location of the maximum of the distribution
/// (most proper value) is at x = -0.22278
/// This function has been adapted from the CERNLIB routine G110 denlan.
/// If norm=kTRUE (default is kFALSE) the result is divided by sigma
/*
Double_t TMath::Landau(Double_t x, Double_t mu, Double_t sigma, Bool_t norm)
{
   if (sigma <= 0) return 0;
   Double_t den = ::ROOT::Math::landau_pdf( (x-mu)/sigma );
   if (!norm) return den;
   return den/sigma;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computation of ln[gamma(z)] for all z.
///
/// C.Lanczos, SIAM Journal of Numerical Analysis B1 (1964), 86.
///
/// The accuracy of the result is better than 2e-10.
///
/// \author NvE 14-nov-1998 UU-SAP Utrecht
/*
Double_t TMath::LnGamma(Double_t z)
{
   return ::ROOT::Math::lgamma(z);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Normalize a vector v in place.
/// Returns the norm of the original vector.

Float_t TMath::Normalize(Float_t v[3])
{
   Float_t d = Sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
   if (d != 0) {
      v[0] /= d;
      v[1] /= d;
      v[2] /= d;
   }
   return d;
}

////////////////////////////////////////////////////////////////////////////////
/// Normalize a vector v in place.
/// Returns the norm of the original vector.
/// This implementation (thanks Kevin Lynch <krlynch@bu.edu>) is protected
/// against possible overflows.

Double_t TMath::Normalize(Double_t v[3])
{
   // Find the largest element, and divide that one out.

   Double_t av0 = Abs(v[0]), av1 = Abs(v[1]), av2 = Abs(v[2]);

   Double_t amax, foo, bar;
   // 0 >= {1, 2}
   if( av0 >= av1 && av0 >= av2 ) {
      amax = av0;
      foo = av1;
      bar = av2;
   }
   // 1 >= {0, 2}
   else if (av1 >= av0 && av1 >= av2) {
      amax = av1;
      foo = av0;
      bar = av2;
   }
   // 2 >= {0, 1}
   else {
      amax = av2;
      foo = av0;
      bar = av1;
   }

   if (amax == 0.0)
      return 0.;

   Double_t foofrac = foo/amax, barfrac = bar/amax;
   Double_t d = amax * Sqrt(1.+foofrac*foofrac+barfrac*barfrac);

   v[0] /= d;
   v[1] /= d;
   v[2] /= d;
   return d;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the Poisson distribution function for (x,par)
/// The Poisson PDF is implemented by means of Euler's Gamma-function
/// (for the factorial), so for any x integer argument it is correct.
/// BUT for non-integer x values, it IS NOT equal to the Poisson distribution.
/// see TMath::PoissonI to get a non-smooth function.
/// Note that for large values of par, it is better to call
///
///     TMath::Gaus(x,par,sqrt(par),kTRUE)
///
/// Begin_Macro
/// {
///   TCanvas *c1 = new TCanvas("c1", "c1", 700, 500);
///   TF1 *poisson = new TF1("poisson", "TMath::Poisson(x, 5)", 0, 15);
///   poisson->Draw("L");
/// }
/// End_Macro
/*
Double_t TMath::Poisson(Double_t x, Double_t par)
{
   if (x<0)
      return 0;
   else if (x == 0.0)
      return 1./Exp(par);
   else {
      Double_t lnpoisson = x*log(par)-par-LnGamma(x+1.);
      return Exp(lnpoisson);
   }
   // An alternative strategy is to transition to a Gaussian approximation for
   // large values of par ...
   //   else {
   //     return Gaus(x,par,Sqrt(par),kTRUE);
   //   }
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Compute the Poisson distribution function for (x,par)
/// This is a non-smooth function.
/// This function is equivalent to ROOT::Math::poisson_pdf
///
/// Begin_Macro
/// {
///   TCanvas *c1 = new TCanvas("c1", "c1", 700, 500);
///   TF1 *poissoni = new TF1("poissoni", "TMath::PoissonI(x, 5)", 0, 15);
///   poissoni->SetNpx(1000);
///   poissoni->Draw("L");
/// }
/// End_Macro
/*
Double_t TMath::PoissonI(Double_t x, Double_t par)
{
   Int_t ix = Int_t(x);
   return Poisson(ix,par);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computation of the probability for a certain Chi-squared (chi2)
/// and number of degrees of freedom (ndf).
///
/// Calculations are based on the incomplete gamma function P(a,x),
/// where a=ndf/2 and x=chi2/2.
///
/// P(a,x) represents the probability that the observed Chi-squared
/// for a correct model should be less than the value chi2.
///
/// The returned probability corresponds to 1-P(a,x),
/// which denotes the probability that an observed Chi-squared exceeds
/// the value chi2 by chance, even for a correct model.
///
/// \author NvE 14-nov-1998 UU-SAP Utrecht
/*
Double_t TMath::Prob(Double_t chi2,Int_t ndf)
{
   if (ndf <= 0) return 0; // Set CL to zero in case ndf<=0

   if (chi2 <= 0) {
      if (chi2 < 0) return 0;
      else          return 1;
   }

   return ::ROOT::Math::chisquared_cdf_c(chi2,ndf);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Calculates the Kolmogorov distribution function,
///
/// \f[
/// P(z) = 2 \sum_{j=1}^{\infty} (-1)^{j-1} e^{-2 j^2 z^2}
/// \f]
///
/// which gives the probability that Kolmogorov's test statistic will exceed
/// the value z assuming the null hypothesis. This gives a very powerful
/// test for comparing two one-dimensional distributions.
/// see, for example, Eadie et al, "statistical Methods in Experimental
/// Physics', pp 269-270).
///
/// This function returns the confidence level for the null hypothesis, where:
///  - \f$ z = dn \sqrt{n} \f$, and
///     - \f$ dn \f$  is the maximum deviation between a hypothetical distribution
///           function and an experimental distribution with
///     - \f$ n \f$  events
///
/// NOTE: To compare two experimental distributions with m and n events,
///       use \f$ z = \sqrt{m n/(m+n)) dn} \f$
///
/// Accuracy: The function is far too accurate for any imaginable application.
///           Probabilities less than \f$ 10^{-15} \f$ are returned as zero.
///           However, remember that the formula is only valid for "large" n.
///
/// Theta function inversion formula is used for z <= 1
///
/// This function was translated by Rene Brun from PROBKL in CERNLIB.

Double_t TMath::KolmogorovProb(Double_t z)
{
   Double_t fj[4] = {-2,-8,-18,-32}, r[4];
   const Double_t w = 2.50662827;
   // c1 - -pi**2/8, c2 = 9*c1, c3 = 25*c1
   const Double_t c1 = -1.2337005501361697;
   const Double_t c2 = -11.103304951225528;
   const Double_t c3 = -30.842513753404244;

   Double_t u = TMath::Abs(z);
   Double_t p;
   if (u < 0.2) {
      p = 1;
   } else if (u < 0.755) {
      Double_t v = 1./(u*u);
      p = 1 - w*(TMath::Exp(c1*v) + TMath::Exp(c2*v) + TMath::Exp(c3*v))/u;
   } else if (u < 6.8116) {
      r[1] = 0;
      r[2] = 0;
      r[3] = 0;
      Double_t v = u*u;
      Int_t maxj = TMath::Max(1,TMath::Nint(3./u));
      for (Int_t j=0; j<maxj;j++) {
         r[j] = TMath::Exp(fj[j]*v);
      }
      p = 2*(r[0] - r[1] +r[2] - r[3]);
   } else {
      p = 0;
   }
   return p;
   }

////////////////////////////////////////////////////////////////////////////////
///  Statistical test whether two one-dimensional sets of points are compatible
///  with coming from the same parent distribution, using the Kolmogorov test.
///  That is, it is used to compare two experimental distributions of unbinned data.
///
/// ### Input:
///  a,b: One-dimensional arrays of length na, nb, respectively.
///       The elements of a and b must be given in ascending order.
///  option is a character string to specify options
///         "D" Put out a line of "Debug" printout
///         "M" Return the Maximum Kolmogorov distance instead of prob
///
/// ### Output:
/// The returned value prob is a calculated confidence level which gives a
/// statistical test for compatibility of a and b.
/// Values of prob close to zero are taken as indicating a small probability
/// of compatibility. For two point sets drawn randomly from the same parent
/// distribution, the value of prob should be uniformly distributed between
/// zero and one.
///   in case of error the function return -1
///   If the 2 sets have a different number of points, the minimum of
///   the two sets is used.
///
/// ### Method:
/// The Kolmogorov test is used. The test statistic is the maximum deviation
/// between the two integrated distribution functions, multiplied by the
/// normalizing factor (rdmax*sqrt(na*nb/(na+nb)).
///
///  Code adapted by Rene Brun from CERNLIB routine TKOLMO (Fred James)
///   (W.T. Eadie, D. Drijard, F.E. James, M. Roos and B. Sadoulet,
///      Statistical Methods in Experimental Physics, (North-Holland,
///      Amsterdam 1971) 269-271)
///
/// ### Method Improvement by Jason A Detwiler (JADetwiler@lbl.gov)
///
///   The nuts-and-bolts of the TMath::KolmogorovTest() algorithm is a for-loop
///   over the two sorted arrays a and b representing empirical distribution
///   functions. The for-loop handles 3 cases: when the next points to be
///   evaluated satisfy a>b, a<b, or a=b:
///
/// ~~~ {cpp}
///      for (Int_t i=0;i<na+nb;i++) {
///         if (a[ia-1] < b[ib-1]) {
///            rdiff -= sa;
///            ia++;
///            if (ia > na) {ok = kTRUE; break;}
///         } else if (a[ia-1] > b[ib-1]) {
///            rdiff += sb;
///            ib++;
///            if (ib > nb) {ok = kTRUE; break;}
///         } else {
///            rdiff += sb - sa;
///            ia++;
///            ib++;
///            if (ia > na) {ok = kTRUE; break;}
///            if (ib > nb) {ok = kTRUE; break;}
///        }
///         rdmax = TMath::Max(rdmax,TMath::Abs(rdiff));
///      }
/// ~~~
///
///   For the last case, a=b, the algorithm advances each array by one index in an
///   attempt to move through the equality. However, this is incorrect when one or
///   the other of a or b (or both) have a repeated value, call it x. For the KS
///   statistic to be computed properly, rdiff needs to be calculated after all of
///   the a and b at x have been tallied (this is due to the definition of the
///   empirical distribution function; another way to convince yourself that the
///   old CERNLIB method is wrong is that it implies that the function defined as the
///   difference between a and b is multi-valued at x -- besides being ugly, this
///   would invalidate Kolmogorov's theorem).
///
///   The solution is to just add while-loops into the equality-case handling to
///   perform the tally:
///
/// ~~~ {cpp}
///         } else {
///            double x = a[ia-1];
///            while(a[ia-1] == x && ia <= na) {
///              rdiff -= sa;
///              ia++;
///            }
///            while(b[ib-1] == x && ib <= nb) {
///              rdiff += sb;
///              ib++;
///            }
///            if (ia > na) {ok = kTRUE; break;}
///            if (ib > nb) {ok = kTRUE; break;}
///         }
/// ~~~
///
/// ### Note:
///  A good description of the Kolmogorov test can be seen at:
///    http://www.itl.nist.gov/div898/handbook/eda/section3/eda35g.htm

Double_t TMath::KolmogorovTest(Int_t na, const Double_t *a, Int_t nb, const Double_t *b, Option_t *option)
{
//  LM: Nov 2010: clean up and returns now a zero distance when vectors are the same

   TString opt = option;
   opt.ToUpper();

   Double_t prob = -1;
//      Require at least two points in each graph
   if (!a || !b || na <= 2 || nb <= 2) {
      //Error("KolmogorovTest","Sets must have more than 2 points");
      return prob;
   }
//     Constants needed
   Double_t rna = na;
   Double_t rnb = nb;
   Double_t sa  = 1./rna;
   Double_t sb  = 1./rnb;
   Double_t rdiff = 0;
   Double_t rdmax = 0;
   Int_t ia = 0;
   Int_t ib = 0;

//    Main loop over point sets to find max distance
//    rdiff is the running difference, and rdmax the max.
   Bool_t ok = kFALSE;
   for (Int_t i=0;i<na+nb;i++) {
      if (a[ia] < b[ib]) {
         rdiff -= sa;
         ia++;
         if (ia >= na) {ok = kTRUE; break;}
      } else if (a[ia] > b[ib]) {
         rdiff += sb;
         ib++;
         if (ib >= nb) {ok = kTRUE; break;}
      } else {
         // special cases for the ties
         double x = a[ia];
         while(ia < na && a[ia] == x) {
            rdiff -= sa;
            ia++;
         }
         while(ib < nb && b[ib] == x) {
            rdiff += sb;
            ib++;
         }
         if (ia >= na) {ok = kTRUE; break;}
         if (ib >= nb) {ok = kTRUE; break;}
      }
      rdmax = TMath::Max(rdmax,TMath::Abs(rdiff));
   }
   //    Should never terminate this loop with ok = kFALSE!
   //R__ASSERT(ok);

   if (ok) {
      rdmax = TMath::Max(rdmax,TMath::Abs(rdiff));
      Double_t z = rdmax * TMath::Sqrt(rna*rnb/(rna+rnb));
      prob = TMath::KolmogorovProb(z);
   }
      // debug printout
   if (opt.Contains("D")) {
      printf(" Kolmogorov Probability = %g, Max Dist = %g\n",prob,rdmax);
   }
   if(opt.Contains("M")) return rdmax;
   else                  return prob;
}


////////////////////////////////////////////////////////////////////////////////
/// Computation of Voigt function (normalised).
/// Voigt is a convolution of the two functions:
/// \f[
/// gauss(xx) = \frac{1}{(\sqrt{2\pi} sigma)} e^{\frac{xx^{2}}{(2 sigma{^2})}}
/// \f]
/// and
/// \f[
/// lorentz(xx) = \frac{ \frac{1}{\pi} \frac{lg}{2} }{ (xx^{2} + \frac{lg^{2}}{4}) }
/// \f]
/// .
///
/// The Voigt function is known to be the real part of Faddeeva function also
/// called complex error function [2].
///
/// The algoritm was developed by J. Humlicek [1].
/// This code is based on fortran code presented by R. J. Wells [2].
/// Translated and adapted by Miha D. Puc
///
/// To calculate the Faddeeva function with relative error less than 10^(-r).
/// r can be set by the the user subject to the constraints 2 <= r <= 5.
///
///  - [1] J. Humlicek, JQSRT, 21, 437 (1982).
///  - [2] [R.J. Wells "Rapid Approximation to the Voigt/Faddeeva Function and its Derivatives" JQSRT 62 (1999), pp 29-48.](http://www-atm.physics.ox.ac.uk/user/wells/voigt.html)

Double_t TMath::Voigt(Double_t xx, Double_t sigma, Double_t lg, Int_t r)
{
   if ((sigma < 0 || lg < 0) || (sigma==0 && lg==0)) {
      return 0;  // Not meant to be for those who want to be thinner than 0
   }

   if (sigma == 0) {
      return lg * 0.159154943  / (xx*xx + lg*lg /4); //pure Lorentz
   }

   if (lg == 0) {   //pure gauss
      return 0.39894228 / sigma * TMath::Exp(-xx*xx / (2*sigma*sigma));
   }

   Double_t x, y, k;
   x = xx / sigma / 1.41421356;
   y = lg / 2 / sigma / 1.41421356;

   Double_t r0, r1;

   if (r < 2) r = 2;
   if (r > 5) r = 5;

   r0=1.51 * exp(1.144 * (Double_t)r);
   r1=1.60 * exp(0.554 * (Double_t)r);

   // Constants

   const Double_t rrtpi = 0.56418958;  // 1/SQRT(pi)

   Double_t y0, y0py0, y0q;                      // for CPF12 algorithm
   y0 = 1.5;
   y0py0 = y0 + y0;
   y0q = y0 * y0;

   Double_t c[6] = { 1.0117281, -0.75197147, 0.012557727, 0.010022008, -0.00024206814, 0.00000050084806};
   Double_t s[6] = { 1.393237, 0.23115241, -0.15535147, 0.0062183662, 0.000091908299, -0.00000062752596};
   Double_t t[6] = { 0.31424038, 0.94778839, 1.5976826, 2.2795071, 3.0206370, 3.8897249};

   // Local variables

   int j;                                        // Loop variables
   int rg1, rg2, rg3;                            // y polynomial flags
   Double_t abx, xq, yq, yrrtpi;                 // --x--, x^2, y^2, y/SQRT(pi)
   Double_t xlim0, xlim1, xlim2, xlim3, xlim4;   // --x-- on region boundaries
   Double_t a0=0, d0=0, d2=0, e0=0, e2=0, e4=0, h0=0, h2=0, h4=0, h6=0;// W4 temporary variables
   Double_t p0=0, p2=0, p4=0, p6=0, p8=0, z0=0, z2=0, z4=0, z6=0, z8=0;
   Double_t xp[6], xm[6], yp[6], ym[6];          // CPF12 temporary values
   Double_t mq[6], pq[6], mf[6], pf[6];
   Double_t d, yf, ypy0, ypy0q;

   //***** Start of executable code *****************************************

   rg1 = 1;  // Set flags
   rg2 = 1;
   rg3 = 1;
   yq = y * y;  // y^2
   yrrtpi = y * rrtpi;  // y/SQRT(pi)

   // Region boundaries when both k and L are required or when R<>4

   xlim0 = r0 - y;
   xlim1 = r1 - y;
   xlim3 = 3.097 * y - 0.45;
   xlim2 = 6.8 - y;
   xlim4 = 18.1 * y + 1.65;
   if ( y <= 1e-6 ) {                      // When y<10^-6 avoid W4 algorithm
      xlim1 = xlim0;
      xlim2 = xlim0;
   }

   abx = fabs(x);                                // |x|
   xq = abx * abx;                               // x^2
   if ( abx > xlim0 ) {                          // Region 0 algorithm
      k = yrrtpi / (xq + yq);
   } else if ( abx > xlim1 ) {                   // Humlicek W4 Region 1
      if ( rg1 != 0 ) {                          // First point in Region 1
         rg1 = 0;
         a0 = yq + 0.5;                          // Region 1 y-dependents
         d0 = a0*a0;
         d2 = yq + yq - 1.0;
      }
      d = rrtpi / (d0 + xq*(d2 + xq));
      k = d * y * (a0 + xq);
   } else if ( abx > xlim2 ) {                   // Humlicek W4 Region 2
      if ( rg2 != 0 ) {                          // First point in Region 2
         rg2 = 0;
         h0 = 0.5625 + yq * (4.5 + yq * (10.5 + yq * (6.0 + yq)));
                                                 // Region 2 y-dependents
         h2 = -4.5 + yq * (9.0 + yq * ( 6.0 + yq * 4.0));
         h4 = 10.5 - yq * (6.0 - yq * 6.0);
         h6 = -6.0 + yq * 4.0;
         e0 = 1.875 + yq * (8.25 + yq * (5.5 + yq));
         e2 = 5.25 + yq * (1.0 + yq * 3.0);
         e4 = 0.75 * h6;
      }
      d = rrtpi / (h0 + xq * (h2 + xq * (h4 + xq * (h6 + xq))));
      k = d * y * (e0 + xq * (e2 + xq * (e4 + xq)));
   } else if ( abx < xlim3 ) {                   // Humlicek W4 Region 3
      if ( rg3 != 0 ) {                          // First point in Region 3
         rg3 = 0;
         z0 = 272.1014 + y * (1280.829 + y *
                              (2802.870 + y *
                               (3764.966 + y *
                                (3447.629 + y *
                                 (2256.981 + y *
                                  (1074.409 + y *
                                   (369.1989  + y *
                                    (88.26741 + y *
                                     (13.39880 + y)
                                     ))))))));   // Region 3 y-dependents
         z2 = 211.678 + y * (902.3066 + y *
                             (1758.336 + y *
                              (2037.310 + y *
                               (1549.675 + y *
                                (793.4273 + y *
                                 (266.2987 + y *
                                  (53.59518 + y * 5.0)
                                  ))))));
         z4 = 78.86585 + y * (308.1852 + y *
                              (497.3014 + y *
                               (479.2576 + y *
                                (269.2916 + y *
                                 (80.39278 + y * 10.0)
                                 ))));
         z6 = 22.03523 + y * (55.02933 + y *
                              (92.75679 + y *
                               (53.59518 + y * 10.0)
                               ));
         z8 = 1.496460 + y * (13.39880 + y * 5.0);
         p0 = 153.5168 + y * (549.3954 + y *
                              (919.4955 + y *
                               (946.8970 + y *
                                (662.8097 + y *
                                 (328.2151 + y *
                                  (115.3772 + y *
                                   (27.93941 + y *
                                    (4.264678 + y * 0.3183291)
                                    )))))));
         p2 = -34.16955 + y * (-1.322256+ y *
                               (124.5975 + y *
                                (189.7730 + y *
                                 (139.4665 + y *
                                  (56.81652 + y *
                                   (12.79458 + y * 1.2733163)
                                   )))));
         p4 = 2.584042 + y * (10.46332 + y *
                              (24.01655 + y *
                               (29.81482 + y *
                                (12.79568 + y * 1.9099744)
                                )));
         p6 = -0.07272979 + y * (0.9377051 + y *
                                 (4.266322 + y * 1.273316));
         p8 = 0.0005480304 + y * 0.3183291;
      }
      d = 1.7724538 / (z0 + xq * (z2 + xq * (z4 + xq * (z6 + xq * (z8 + xq)))));
      k = d * (p0 + xq * (p2 + xq * (p4 + xq * (p6 + xq * p8))));
   } else {                             // Humlicek CPF12 algorithm
      ypy0 = y + y0;
      ypy0q = ypy0 * ypy0;
      k = 0.0;
      for (j = 0; j <= 5; j++) {
         d = x - t[j];
         mq[j] = d * d;
         mf[j] = 1.0 / (mq[j] + ypy0q);
         xm[j] = mf[j] * d;
         ym[j] = mf[j] * ypy0;
         d = x + t[j];
         pq[j] = d * d;
         pf[j] = 1.0 / (pq[j] + ypy0q);
         xp[j] = pf[j] * d;
         yp[j] = pf[j] * ypy0;
      }
      if ( abx <= xlim4 ) {                      // Humlicek CPF12 Region I
         for (j = 0; j <= 5; j++) {
            k = k + c[j]*(ym[j]+yp[j]) - s[j]*(xm[j]-xp[j]) ;
         }
      } else {                                   // Humlicek CPF12 Region II
         yf = y + y0py0;
         for ( j = 0; j <= 5; j++) {
            k = k + (c[j] *
                 (mq[j] * mf[j] - y0 * ym[j])
                    + s[j] * yf * xm[j]) / (mq[j]+y0q)
                 + (c[j] * (pq[j] * pf[j] - y0 * yp[j])
                   - s[j] * yf * xp[j]) / (pq[j]+y0q);
         }
         k = y * k + exp( -xq );
      }
   }
   return k / 2.506628 / sigma; // Normalize by dividing by sqrt(2*pi)*sigma.
}

////////////////////////////////////////////////////////////////////////////////
/// Calculates roots of polynomial of 3rd order a*x^3 + b*x^2 + c*x + d, where
///  - a == coef[3],
///  - b == coef[2],
///  - c == coef[1],
///  - d == coef[0]
///
///coef[3] must be different from 0
///
/// If the boolean returned by the method is false:
///    ==> there are 3 real roots a,b,c

/// If the boolean returned by the method is true:
///    ==> there is one real root a and 2 complex conjugates roots (b+i*c,b-i*c)
///
/// \author Francois-Xavier Gentit

Bool_t TMath::RootsCubic(const Double_t coef[4],Double_t &a, Double_t &b, Double_t &c)
{
   Bool_t complex = kFALSE;
   Double_t r,s,t,p,q,d,ps3,ps33,qs2,u,v,tmp,lnu,lnv,su,sv,y1,y2,y3;
   a    = 0;
   b    = 0;
   c    = 0;
   if (coef[3] == 0) return complex;
   r    = coef[2]/coef[3];
   s    = coef[1]/coef[3];
   t    = coef[0]/coef[3];
   p    = s - (r*r)/3;
   ps3  = p/3;
   q    = (2*r*r*r)/27.0 - (r*s)/3 + t;
   qs2  = q/2;
   ps33 = ps3*ps3*ps3;
   d    = ps33 + qs2*qs2;
   if (d>=0) {
      complex = kTRUE;
      d   = TMath::Sqrt(d);
      u   = -qs2 + d;
      v   = -qs2 - d;
      tmp = 1./3.;
      lnu = TMath::Log(TMath::Abs(u));
      lnv = TMath::Log(TMath::Abs(v));
      su  = TMath::Sign(1.,u);
      sv  = TMath::Sign(1.,v);
      u   = su*TMath::Exp(tmp*lnu);
      v   = sv*TMath::Exp(tmp*lnv);
      y1  = u + v;
      y2  = -y1/2;
      y3  = ((u-v)*TMath::Sqrt(3.))/2;
      tmp = r/3;
      a   = y1 - tmp;
      b   = y2 - tmp;
      c   = y3;
   } else {
      Double_t phi,cphi,phis3,c1,c2,c3,pis3;
      ps3   = -ps3;
      ps33  = -ps33;
      cphi  = -qs2/TMath::Sqrt(ps33);
      phi   = TMath::ACos(cphi);
      phis3 = phi/3;
      pis3  = TMath::Pi()/3;
      c1    = TMath::Cos(phis3);
      c2    = TMath::Cos(pis3 + phis3);
      c3    = TMath::Cos(pis3 - phis3);
      tmp   = TMath::Sqrt(ps3);
      y1    = 2*tmp*c1;
      y2    = -2*tmp*c2;
      y3    = -2*tmp*c3;
      tmp = r/3;
      a   = y1 - tmp;
      b   = y2 - tmp;
      c   = y3 - tmp;
   }
   return complex;
}

////////////////////////////////////////////////////////////////////////////////
///Computes sample quantiles, corresponding to the given probabilities
///
///  \param[in] x           the data sample
///  \param[in] n           its size
///  \param[out] quantiles  computed quantiles are returned in there
///  \param[in] prob        probabilities where to compute quantiles
///  \param[in] nprob       size of prob array
///  \param[in] isSorted    is the input array x sorted ?
///  \param[in] type        method to compute (from 1 to 9).
///
/// #### NOTE:
///  When the input is not sorted, an array of integers of size n needs
///  to be allocated. It can be passed by the user in parameter index,
///  or, if not passed, it will be allocated inside the function
///
/// ### Following types are provided:
///  - Discontinuous:
///    - type=1 - inverse of the empirical distribution function
///    - type=2 - like type 1, but with averaging at discontinuities
///    - type=3 - SAS definition: nearest even order statistic
///  - Piecewise linear continuous:
///    - In this case, sample quantiles can be obtained by linear interpolation
///       between the k-th order statistic and p(k).
///     -type=4 - linear interpolation of empirical cdf, p(k)=k/n;
///    - type=5 - a very popular definition, p(k) = (k-0.5)/n;
///    - type=6 - used by Minitab and SPSS, p(k) = k/(n+1);
///    - type=7 - used by S-Plus and R, p(k) = (k-1)/(n-1);
///    - type=8 - resulting sample quantiles are approximately median unbiased
///               regardless of the distribution of x. p(k) = (k-1/3)/(n+1/3);
///    - type=9 - resulting sample quantiles are approximately unbiased, when
///               the sample comes from Normal distribution. p(k)=(k-3/8)/(n+1/4);
///
///    default type = 7
///
/// ### References:
///  1. Hyndman, R.J and Fan, Y, (1996) "Sample quantiles in statistical packages"
///                                     American Statistician, 50, 361-365
///  2. R Project documentation for the function quantile of package {stats}

void TMath::Quantiles(Int_t n, Int_t nprob, Double_t *x, Double_t *quantiles, Double_t *prob, Bool_t isSorted, Int_t *index, Int_t type)
{

   if (type<1 || type>9){
      printf("illegal value of type\n");
      return;
   }
   Int_t *ind = 0;
   Bool_t isAllocated = kFALSE;
   if (!isSorted){
      if (index) ind = index;
      else {
         ind = new Int_t[n];
         isAllocated = kTRUE;
      }
   }

   // re-implemented by L.M (9/11/2011) to fix bug https://savannah.cern.ch/bugs/?87251
   // following now exactly R implementation (available in library/stats/R/quantile.R )
   // which follows precisely Hyndman-Fan paper
   // (older implementation had a bug for type =3)

   for (Int_t i=0; i<nprob; i++){

      Double_t nppm = 0;
      Double_t gamma = 0;
      Int_t j = 0;

      //Discontinuous functions
      // type = 1,2, or 3
      if (type < 4 ){
         if (type == 3)
            nppm = n*prob[i]-0.5;   // use m = -0.5
         else
            nppm = n*prob[i]; // use m = 0

         // be careful with machine precision
         double eps = 4 * TMath::Limits<Double_t>::Epsilon();
         j = TMath::FloorNint(nppm + eps);

         // LM : fix for numerical problems if nppm is actually equal to j, but results different for numerical error
         // g in the paper is nppm -j
         if (type == 1)
            gamma = ( (nppm -j) > j*TMath::Limits<Double_t>::Epsilon() ) ? 1 : 0;
         else if (type == 2)
            gamma = ( (nppm -j) > j*TMath::Limits<Double_t>::Epsilon() ) ? 1 : 0.5;
         else if (type == 3)
            // gamma = 0 for g=0 and j even
            gamma = ( TMath::Abs(nppm -j) <= j*TMath::Limits<Double_t>::Epsilon()   && TMath::Even(j) ) ? 0 : 1;

      }
      else {
         // for continuous quantiles  type 4 to 9)
         // define alpha and beta
         double a = 0;
         double b = 0;
         if (type == 4)       { a = 0; b = 1; }
         else if (type == 5)  { a = 0.5; b = 0.5; }
         else if (type == 6)  { a = 0.; b = 0.; }
         else if (type == 7)  { a = 1.; b = 1.; }
         else if (type == 8)  { a = 1./3.; b = a; }
         else if (type == 9)  { a = 3./8.; b = a; }

         // be careful with machine precision
         double eps  = 4 * TMath::Limits<Double_t>::Epsilon();
         nppm = a + prob[i] * ( n + 1 -a -b);       // n * p + m
         j = TMath::FloorNint(nppm + eps);
         gamma = nppm - j;
         if (gamma < eps) gamma = 0;
      }

      // since index j starts from 1 first is j-1 and second is j
      // add protection to keep indices in range [0,n-1]
      int first  = (j > 0 && j <=n) ? j-1 : ( j <=0 ) ? 0 : n-1;
      int second = (j > 0 && j < n) ?  j  : ( j <=0 ) ? 0 : n-1;

      Double_t xj, xjj;
      if (isSorted){
         xj = x[first];
         xjj = x[second];
      } else {
         xj = TMath::KOrdStat(n, x, first, ind);
         xjj = TMath::KOrdStat(n, x, second, ind);
      }
      quantiles[i] = (1-gamma)*xj + gamma*xjj;
      // printf("x[j] = %12f  x[j+1] = %12f \n",xj, xjj);

   }



   if (isAllocated)
      delete [] ind;
}

////////////////////////////////////////////////////////////////////////////////
/// Bubble sort variant to obtain the order of an array's elements into
/// an index in order to do more useful things than the standard built
/// in functions.
/// \param[in] *arr1  is unchanged;
/// \param[in] *arr2  is the array of indicies corresponding to the descending value
///            of arr1 with arr2[0] corresponding to the largest arr1 value and
///            arr2[Narr] the smallest.
///
/// \author Adrian Bevan (bevan@slac.stanford.edu)

void TMath::BubbleHigh(Int_t Narr, Double_t *arr1, Int_t *arr2)
{
   if (Narr <= 0) return;
   double *localArr1 = new double[Narr];
   int    *localArr2 = new int[Narr];
   int iEl;
   int iEl2;

   for(iEl = 0; iEl < Narr; iEl++) {
      localArr1[iEl] = arr1[iEl];
      localArr2[iEl] = iEl;
   }

   for (iEl = 0; iEl < Narr; iEl++) {
      for (iEl2 = Narr-1; iEl2 > iEl; --iEl2) {
         if (localArr1[iEl2-1] < localArr1[iEl2]) {
            double tmp        = localArr1[iEl2-1];
            localArr1[iEl2-1] = localArr1[iEl2];
            localArr1[iEl2]   = tmp;

            int    tmp2       = localArr2[iEl2-1];
            localArr2[iEl2-1] = localArr2[iEl2];
            localArr2[iEl2]   = tmp2;
         }
      }
   }

   for (iEl = 0; iEl < Narr; iEl++) {
      arr2[iEl] = localArr2[iEl];
   }
   delete [] localArr2;
   delete [] localArr1;
}

////////////////////////////////////////////////////////////////////////////////
/// Opposite ordering of the array arr2[] to that of BubbleHigh.
///
/// \author Adrian Bevan (bevan@slac.stanford.edu)

void TMath::BubbleLow(Int_t Narr, Double_t *arr1, Int_t *arr2)
{
   if (Narr <= 0) return;
   double *localArr1 = new double[Narr];
   int    *localArr2 = new int[Narr];
   int iEl;
   int iEl2;

   for (iEl = 0; iEl < Narr; iEl++) {
      localArr1[iEl] = arr1[iEl];
      localArr2[iEl] = iEl;
   }

   for (iEl = 0; iEl < Narr; iEl++) {
      for (iEl2 = Narr-1; iEl2 > iEl; --iEl2) {
         if (localArr1[iEl2-1] > localArr1[iEl2]) {
            double tmp        = localArr1[iEl2-1];
            localArr1[iEl2-1] = localArr1[iEl2];
            localArr1[iEl2]   = tmp;

            int    tmp2       = localArr2[iEl2-1];
            localArr2[iEl2-1] = localArr2[iEl2];
            localArr2[iEl2]   = tmp2;
         }
      }
   }

   for (iEl = 0; iEl < Narr; iEl++) {
      arr2[iEl] = localArr2[iEl];
   }
   delete [] localArr2;
   delete [] localArr1;
}


////////////////////////////////////////////////////////////////////////////////
/// Calculates hash index from any char string.
/// Based on pre-calculated table of 256 specially selected numbers.
/// These numbers are selected in such a way, that for string
/// length == 4 (integer number) the hash is unambiguous, i.e.
/// from hash value we can recalculate input (no degeneration).
///
/// The quality of hash method is good enough, that
/// "random" numbers made as R = Hash(1), Hash(2), ...Hash(N)
/// tested by <R>, <R*R>, <Ri*Ri+1> gives the same result
/// as for libc rand().
///
///  - For string:  i = TMath::Hash(string,nstring);
///  - For int:     i = TMath::Hash(&intword,sizeof(int));
///  - For pointer: i = TMath::Hash(&pointer,sizeof(void*));
///
///              V.Perev
/// This function is kept for back compatibility. The code previously in this function
/// has been moved to the static function TString::Hash
/*
ULong_t TMath::Hash(const void *txt, Int_t ntxt)
{
   return TString::Hash(txt,ntxt);
}
*/

////////////////////////////////////////////////////////////////////////////////

ULong_t TMath::Hash(const char *txt)
{
   return Hash(txt, Int_t(strlen(txt)));
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the modified Bessel function I_0(x) for any real x.
///
/// \author NvE 12-mar-2000 UU-SAP Utrecht

Double_t TMath::BesselI0(Double_t x)
{
   // Parameters of the polynomial approximation
   const Double_t p1=1.0,          p2=3.5156229,    p3=3.0899424,
                  p4=1.2067492,    p5=0.2659732,    p6=3.60768e-2,  p7=4.5813e-3;

   const Double_t q1= 0.39894228,  q2= 1.328592e-2, q3= 2.25319e-3,
                  q4=-1.57565e-3,  q5= 9.16281e-3,  q6=-2.057706e-2,
                  q7= 2.635537e-2, q8=-1.647633e-2, q9= 3.92377e-3;

   const Double_t k1 = 3.75;
   Double_t ax = TMath::Abs(x);

   Double_t y=0, result=0;

   if (ax < k1) {
      Double_t xx = x/k1;
      y = xx*xx;
      result = p1+y*(p2+y*(p3+y*(p4+y*(p5+y*(p6+y*p7)))));
   } else {
      y = k1/ax;
      result = (TMath::Exp(ax)/TMath::Sqrt(ax))*(q1+y*(q2+y*(q3+y*(q4+y*(q5+y*(q6+y*(q7+y*(q8+y*q9))))))));
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the modified Bessel function K_0(x) for positive real x.
///
///  M.Abramowitz and I.A.Stegun, Handbook of Mathematical Functions,
///     Applied Mathematics Series vol. 55 (1964), Washington.
///
/// \author NvE 12-mar-2000 UU-SAP Utrecht

Double_t TMath::BesselK0(Double_t x)
{
   // Parameters of the polynomial approximation
   const Double_t p1=-0.57721566,  p2=0.42278420,   p3=0.23069756,
                  p4= 3.488590e-2, p5=2.62698e-3,   p6=1.0750e-4,    p7=7.4e-6;

   const Double_t q1= 1.25331414,  q2=-7.832358e-2, q3= 2.189568e-2,
                  q4=-1.062446e-2, q5= 5.87872e-3,  q6=-2.51540e-3,  q7=5.3208e-4;

   if (x <= 0) {
      //Error("TMath::BesselK0", "*K0* Invalid argument x = %g\n",x);
      return 0;
   }

   Double_t y=0, result=0;

   if (x <= 2) {
      y = x*x/4;
      result = (-log(x/2.)*TMath::BesselI0(x))+(p1+y*(p2+y*(p3+y*(p4+y*(p5+y*(p6+y*p7))))));
   } else {
      y = 2/x;
      result = (exp(-x)/sqrt(x))*(q1+y*(q2+y*(q3+y*(q4+y*(q5+y*(q6+y*q7))))));
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the modified Bessel function I_1(x) for any real x.
///
///  M.Abramowitz and I.A.Stegun, Handbook of Mathematical Functions,
///     Applied Mathematics Series vol. 55 (1964), Washington.
///
/// \author NvE 12-mar-2000 UU-SAP Utrecht

Double_t TMath::BesselI1(Double_t x)
{
   // Parameters of the polynomial approximation
   const Double_t p1=0.5,          p2=0.87890594,   p3=0.51498869,
                  p4=0.15084934,   p5=2.658733e-2,  p6=3.01532e-3,  p7=3.2411e-4;

   const Double_t q1= 0.39894228,  q2=-3.988024e-2, q3=-3.62018e-3,
                  q4= 1.63801e-3,  q5=-1.031555e-2, q6= 2.282967e-2,
                  q7=-2.895312e-2, q8= 1.787654e-2, q9=-4.20059e-3;

   const Double_t k1 = 3.75;
   Double_t ax = TMath::Abs(x);

   Double_t y=0, result=0;

   if (ax < k1) {
      Double_t xx = x/k1;
      y = xx*xx;
      result = x*(p1+y*(p2+y*(p3+y*(p4+y*(p5+y*(p6+y*p7))))));
   } else {
      y = k1/ax;
      result = (exp(ax)/sqrt(ax))*(q1+y*(q2+y*(q3+y*(q4+y*(q5+y*(q6+y*(q7+y*(q8+y*q9))))))));
      if (x < 0) result = -result;
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the modified Bessel function K_1(x) for positive real x.
///
///  M.Abramowitz and I.A.Stegun, Handbook of Mathematical Functions,
///     Applied Mathematics Series vol. 55 (1964), Washington.
///
/// \author NvE 12-mar-2000 UU-SAP Utrecht

Double_t TMath::BesselK1(Double_t x)
{
   // Parameters of the polynomial approximation
   const Double_t p1= 1.,          p2= 0.15443144,  p3=-0.67278579,
                  p4=-0.18156897,  p5=-1.919402e-2, p6=-1.10404e-3,  p7=-4.686e-5;

   const Double_t q1= 1.25331414,  q2= 0.23498619,  q3=-3.655620e-2,
                  q4= 1.504268e-2, q5=-7.80353e-3,  q6= 3.25614e-3,  q7=-6.8245e-4;

   if (x <= 0) {
      //Error("TMath::BesselK1", "*K1* Invalid argument x = %g\n",x);
      return 0;
   }

   Double_t y=0,result=0;

   if (x <= 2) {
      y = x*x/4;
      result = (log(x/2.)*TMath::BesselI1(x))+(1./x)*(p1+y*(p2+y*(p3+y*(p4+y*(p5+y*(p6+y*p7))))));
   } else {
      y = 2/x;
      result = (exp(-x)/sqrt(x))*(q1+y*(q2+y*(q3+y*(q4+y*(q5+y*(q6+y*q7))))));
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the Integer Order Modified Bessel function K_n(x)
/// for n=0,1,2,... and positive real x.
///
/// \author NvE 12-mar-2000 UU-SAP Utrecht

Double_t TMath::BesselK(Int_t n,Double_t x)
{
   if (x <= 0 || n < 0) {
      //Error("TMath::BesselK", "*K* Invalid argument(s) (n,x) = (%d, %g)\n",n,x);
      return 0;
   }

   if (n==0) return TMath::BesselK0(x);
   if (n==1) return TMath::BesselK1(x);

   // Perform upward recurrence for all x
   Double_t tox = 2/x;
   Double_t bkm = TMath::BesselK0(x);
   Double_t bk  = TMath::BesselK1(x);
   Double_t bkp = 0;
   for (Int_t j=1; j<n; j++) {
      bkp = bkm+Double_t(j)*tox*bk;
      bkm = bk;
      bk  = bkp;
   }
   return bk;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the Integer Order Modified Bessel function I_n(x)
/// for n=0,1,2,... and any real x.
///
/// \author NvE 12-mar-2000 UU-SAP Utrecht

Double_t TMath::BesselI(Int_t n,Double_t x)
{
   Int_t iacc = 40; // Increase to enhance accuracy
   const Double_t kBigPositive = 1.e10;
   const Double_t kBigNegative = 1.e-10;

   if (n < 0) {
      //Error("TMath::BesselI", "*I* Invalid argument (n,x) = (%d, %g)\n",n,x);
      return 0;
   }

   if (n==0) return TMath::BesselI0(x);
   if (n==1) return TMath::BesselI1(x);

   if (x == 0) return 0;
   if (TMath::Abs(x) > kBigPositive) return 0;

   Double_t tox = 2/TMath::Abs(x);
   Double_t bip = 0, bim = 0;
   Double_t bi  = 1;
   Double_t result = 0;
   Int_t m = 2*((n+Int_t(sqrt(Float_t(iacc*n)))));
   for (Int_t j=m; j>=1; j--) {
      bim = bip+Double_t(j)*tox*bi;
      bip = bi;
      bi  = bim;
      // Renormalise to prevent overflows
      if (TMath::Abs(bi) > kBigPositive)  {
         result *= kBigNegative;
         bi     *= kBigNegative;
         bip    *= kBigNegative;
      }
      if (j==n) result=bip;
   }

   result *= TMath::BesselI0(x)/bi; // Normalise with BesselI0(x)
   if ((x < 0) && (n%2 == 1)) result = -result;

   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the Bessel function J0(x) for any real x.

Double_t TMath::BesselJ0(Double_t x)
{
   Double_t ax,z;
   Double_t xx,y,result,result1,result2;
   const Double_t p1  = 57568490574.0, p2  = -13362590354.0, p3 = 651619640.7;
   const Double_t p4  = -11214424.18,  p5  = 77392.33017,    p6 = -184.9052456;
   const Double_t p7  = 57568490411.0, p8  = 1029532985.0,   p9 = 9494680.718;
   const Double_t p10 = 59272.64853,   p11 = 267.8532712;

   const Double_t q1  = 0.785398164;
   const Double_t q2  = -0.1098628627e-2,  q3  = 0.2734510407e-4;
   const Double_t q4  = -0.2073370639e-5,  q5  = 0.2093887211e-6;
   const Double_t q6  = -0.1562499995e-1,  q7  = 0.1430488765e-3;
   const Double_t q8  = -0.6911147651e-5,  q9  = 0.7621095161e-6;
   const Double_t q10 =  0.934935152e-7,   q11 = 0.636619772;

   if ((ax=fabs(x)) < 8) {
      y=x*x;
      result1 = p1 + y*(p2 + y*(p3 + y*(p4  + y*(p5  + y*p6))));
      result2 = p7 + y*(p8 + y*(p9 + y*(p10 + y*(p11 + y))));
      result  = result1/result2;
   } else {
      z  = 8/ax;
      y  = z*z;
      xx = ax-q1;
      result1 = 1  + y*(q2 + y*(q3 + y*(q4 + y*q5)));
      result2 = q6 + y*(q7 + y*(q8 + y*(q9 - y*q10)));
      result  = sqrt(q11/ax)*(cos(xx)*result1-z*sin(xx)*result2);
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the Bessel function J1(x) for any real x.

Double_t TMath::BesselJ1(Double_t x)
{
   Double_t ax,z;
   Double_t xx,y,result,result1,result2;
   const Double_t p1  = 72362614232.0,  p2  = -7895059235.0, p3 = 242396853.1;
   const Double_t p4  = -2972611.439,   p5  = 15704.48260,   p6 = -30.16036606;
   const Double_t p7  = 144725228442.0, p8  = 2300535178.0,  p9 = 18583304.74;
   const Double_t p10 = 99447.43394,    p11 = 376.9991397;

   const Double_t q1  = 2.356194491;
   const Double_t q2  = 0.183105e-2,     q3  = -0.3516396496e-4;
   const Double_t q4  = 0.2457520174e-5, q5  = -0.240337019e-6;
   const Double_t q6  = 0.04687499995,   q7  = -0.2002690873e-3;
   const Double_t q8  = 0.8449199096e-5, q9  = -0.88228987e-6;
   const Double_t q10 = 0.105787412e-6,  q11 = 0.636619772;

   if ((ax=fabs(x)) < 8) {
      y=x*x;
      result1 = x*(p1 + y*(p2 + y*(p3 + y*(p4  + y*(p5  + y*p6)))));
      result2 = p7    + y*(p8 + y*(p9 + y*(p10 + y*(p11 + y))));
      result  = result1/result2;
   } else {
      z  = 8/ax;
      y  = z*z;
      xx = ax-q1;
      result1 = 1  + y*(q2 + y*(q3 + y*(q4 + y*q5)));
      result2 = q6 + y*(q7 + y*(q8 + y*(q9 + y*q10)));
      result  = sqrt(q11/ax)*(cos(xx)*result1-z*sin(xx)*result2);
      if (x < 0) result = -result;
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the Bessel function Y0(x) for positive x.

Double_t TMath::BesselY0(Double_t x)
{
   Double_t z,xx,y,result,result1,result2;
   const Double_t p1  = -2957821389.,  p2  = 7062834065.0, p3  = -512359803.6;
   const Double_t p4  = 10879881.29,   p5  = -86327.92757, p6  = 228.4622733;
   const Double_t p7  = 40076544269.,  p8  = 745249964.8,  p9  = 7189466.438;
   const Double_t p10 = 47447.26470,   p11 = 226.1030244,  p12 = 0.636619772;

   const Double_t q1  =  0.785398164;
   const Double_t q2  = -0.1098628627e-2, q3  = 0.2734510407e-4;
   const Double_t q4  = -0.2073370639e-5, q5  = 0.2093887211e-6;
   const Double_t q6  = -0.1562499995e-1, q7  = 0.1430488765e-3;
   const Double_t q8  = -0.6911147651e-5, q9  = 0.7621095161e-6;
   const Double_t q10 = -0.934945152e-7,  q11 = 0.636619772;

   if (x < 8) {
      y = x*x;
      result1 = p1 + y*(p2 + y*(p3 + y*(p4  + y*(p5  + y*p6))));
      result2 = p7 + y*(p8 + y*(p9 + y*(p10 + y*(p11 + y))));
      result  = (result1/result2) + p12*TMath::BesselJ0(x)*log(x);
   } else {
      z  = 8/x;
      y  = z*z;
      xx = x-q1;
      result1 = 1  + y*(q2 + y*(q3 + y*(q4 + y*q5)));
      result2 = q6 + y*(q7 + y*(q8 + y*(q9 + y*q10)));
      result  = sqrt(q11/x)*(sin(xx)*result1+z*cos(xx)*result2);
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the Bessel function Y1(x) for positive x.

Double_t TMath::BesselY1(Double_t x)
{
   Double_t z,xx,y,result,result1,result2;
   const Double_t p1  = -0.4900604943e13, p2  = 0.1275274390e13;
   const Double_t p3  = -0.5153438139e11, p4  = 0.7349264551e9;
   const Double_t p5  = -0.4237922726e7,  p6  = 0.8511937935e4;
   const Double_t p7  =  0.2499580570e14, p8  = 0.4244419664e12;
   const Double_t p9  =  0.3733650367e10, p10 = 0.2245904002e8;
   const Double_t p11 =  0.1020426050e6,  p12 = 0.3549632885e3;
   const Double_t p13 =  0.636619772;
   const Double_t q1  =  2.356194491;
   const Double_t q2  =  0.183105e-2,     q3  = -0.3516396496e-4;
   const Double_t q4  =  0.2457520174e-5, q5  = -0.240337019e-6;
   const Double_t q6  =  0.04687499995,   q7  = -0.2002690873e-3;
   const Double_t q8  =  0.8449199096e-5, q9  = -0.88228987e-6;
   const Double_t q10 =  0.105787412e-6,  q11 =  0.636619772;

   if (x < 8) {
      y=x*x;
      result1 = x*(p1 + y*(p2 + y*(p3 + y*(p4 + y*(p5  + y*p6)))));
      result2 = p7 + y*(p8 + y*(p9 + y*(p10 + y*(p11  + y*(p12+y)))));
      result  = (result1/result2) + p13*(TMath::BesselJ1(x)*log(x)-1/x);
   } else {
      z  = 8/x;
      y  = z*z;
      xx = x-q1;
      result1 = 1  + y*(q2 + y*(q3 + y*(q4 + y*q5)));
      result2 = q6 + y*(q7 + y*(q8 + y*(q9 + y*q10)));
      result  = sqrt(q11/x)*(sin(xx)*result1+z*cos(xx)*result2);
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Struve Functions of Order 0
///
/// Converted from CERNLIB M342 by Rene Brun.

Double_t TMath::StruveH0(Double_t x)
{
   const Int_t n1 = 15;
   const Int_t n2 = 25;
   const Double_t c1[16] = { 1.00215845609911981, -1.63969292681309147,
                             1.50236939618292819, -.72485115302121872,
                              .18955327371093136, -.03067052022988,
                              .00337561447375194, -2.6965014312602e-4,
                             1.637461692612e-5,   -7.8244408508e-7,
                             3.021593188e-8,      -9.6326645e-10,
                             2.579337e-11,        -5.8854e-13,
                             1.158e-14,           -2e-16 };
   const Double_t c2[26] = {  .99283727576423943, -.00696891281138625,
                             1.8205103787037e-4,  -1.063258252844e-5,
                             9.8198294287e-7,     -1.2250645445e-7,
                             1.894083312e-8,      -3.44358226e-9,
                             7.1119102e-10,       -1.6288744e-10,
                             4.065681e-11,        -1.091505e-11,
                             3.12005e-12,         -9.4202e-13,
                             2.9848e-13,          -9.872e-14,
                             3.394e-14,           -1.208e-14,
                             4.44e-15,            -1.68e-15,
                             6.5e-16,             -2.6e-16,
                             1.1e-16,             -4e-17,
                             2e-17,               -1e-17 };

   const Double_t c0  = 2/TMath::Pi();

   Int_t i;
   Double_t alfa, h, r, y, b0, b1, b2;
   Double_t v = TMath::Abs(x);

   v = TMath::Abs(x);
   if (v < 8) {
      y = v/8;
      h = 2*y*y -1;
      alfa = h + h;
      b0 = 0;
      b1 = 0;
      b2 = 0;
      for (i = n1; i >= 0; --i) {
         b0 = c1[i] + alfa*b1 - b2;
         b2 = b1;
         b1 = b0;
      }
      h = y*(b0 - h*b2);
   } else {
      r = 1/v;
      h = 128*r*r -1;
      alfa = h + h;
      b0 = 0;
      b1 = 0;
      b2 = 0;
      for (i = n2; i >= 0; --i) {
         b0 = c2[i] + alfa*b1 - b2;
         b2 = b1;
         b1 = b0;
      }
      h = TMath::BesselY0(v) + r*c0*(b0 - h*b2);
   }
   if (x < 0)  h = -h;
   return h;
}

////////////////////////////////////////////////////////////////////////////////
/// Struve Functions of Order 1
///
/// Converted from CERNLIB M342 by Rene Brun.

Double_t TMath::StruveH1(Double_t x)
{
   const Int_t n3 = 16;
   const Int_t n4 = 22;
   const Double_t c3[17] = { .5578891446481605,   -.11188325726569816,
                            -.16337958125200939,   .32256932072405902,
                            -.14581632367244242,   .03292677399374035,
                            -.00460372142093573,  4.434706163314e-4,
                            -3.142099529341e-5,   1.7123719938e-6,
                            -7.416987005e-8,      2.61837671e-9,
                            -7.685839e-11,        1.9067e-12,
                            -4.052e-14,           7.5e-16,
                            -1e-17 };
   const Double_t c4[23] = { 1.00757647293865641,  .00750316051248257,
                            -7.043933264519e-5,   2.66205393382e-6,
                            -1.8841157753e-7,     1.949014958e-8,
                            -2.6126199e-9,        4.236269e-10,
                            -7.955156e-11,        1.679973e-11,
                            -3.9072e-12,          9.8543e-13,
                            -2.6636e-13,          7.645e-14,
                            -2.313e-14,           7.33e-15,
                            -2.42e-15,            8.3e-16,
                            -3e-16,               1.1e-16,
                            -4e-17,               2e-17,-1e-17 };

   const Double_t c0  = 2/TMath::Pi();
   const Double_t cc  = 2/(3*TMath::Pi());

   Int_t i, i1;
   Double_t alfa, h, r, y, b0, b1, b2;
   Double_t v = TMath::Abs(x);

   if (v == 0) {
      h = 0;
   } else if (v <= 0.3) {
      y = v*v;
      r = 1;
      h = 1;
      i1 = (Int_t)(-8. / TMath::Log10(v));
      for (i = 1; i <= i1; ++i) {
         h = -h*y / ((2*i+ 1)*(2*i + 3));
         r += h;
      }
      h = cc*y*r;
   } else if (v < 8) {
      h = v*v/32 -1;
      alfa = h + h;
      b0 = 0;
      b1 = 0;
      b2 = 0;
      for (i = n3; i >= 0; --i) {
         b0 = c3[i] + alfa*b1 - b2;
         b2 = b1;
         b1 = b0;
      }
      h = b0 - h*b2;
   } else {
      h = 128/(v*v) -1;
      alfa = h + h;
      b0 = 0;
      b1 = 0;
      b2 = 0;
      for (i = n4; i >= 0; --i) {
         b0 = c4[i] + alfa*b1 - b2;
         b2 = b1;
         b1 = b0;
      }
      h = TMath::BesselY1(v) + c0*(b0 - h*b2);
   }
   return h;
}

////////////////////////////////////////////////////////////////////////////////
/// Modified Struve Function of Order 0.
/// By Kirill Filimonov.

Double_t TMath::StruveL0(Double_t x)
{
   const Double_t pi=TMath::Pi();

   Double_t s=1.0;
   Double_t r=1.0;

   Double_t a0,sl0,a1,bi0;

   Int_t km,i;

   if (x<=20.) {
      a0=2.0*x/pi;
      for (i=1; i<=60;i++) {
         r*=(x/(2*i+1))*(x/(2*i+1));
         s+=r;
         if(TMath::Abs(r/s)<1.e-12) break;
      }
      sl0=a0*s;
   } else {
      km=int(5*(x+1.0));
      if(x>=50.0)km=25;
      for (i=1; i<=km; i++) {
         r*=(2*i-1)*(2*i-1)/x/x;
         s+=r;
         if(TMath::Abs(r/s)<1.0e-12) break;
      }
      a1=TMath::Exp(x)/TMath::Sqrt(2*pi*x);
      r=1.0;
      bi0=1.0;
      for (i=1; i<=16; i++) {
         r=0.125*r*(2.0*i-1.0)*(2.0*i-1.0)/(i*x);
         bi0+=r;
         if(TMath::Abs(r/bi0)<1.0e-12) break;
      }

      bi0=a1*bi0;
      sl0=-2.0/(pi*x)*s+bi0;
   }
   return sl0;
}

////////////////////////////////////////////////////////////////////////////////
/// Modified Struve Function of Order 1.
/// By Kirill Filimonov.

Double_t TMath::StruveL1(Double_t x)
{
   const Double_t pi=TMath::Pi();
   Double_t a1,sl1,bi1,s;
   Double_t r=1.0;
   Int_t km,i;

   if (x<=20.) {
      s=0.0;
      for (i=1; i<=60;i++) {
         r*=x*x/(4.0*i*i-1.0);
         s+=r;
         if(TMath::Abs(r)<TMath::Abs(s)*1.e-12) break;
      }
      sl1=2.0/pi*s;
   } else {
      s=1.0;
      km=int(0.5*x);
      if(x>50.0)km=25;
      for (i=1; i<=km; i++) {
         r*=(2*i+3)*(2*i+1)/x/x;
         s+=r;
         if(TMath::Abs(r/s)<1.0e-12) break;
      }
      sl1=2.0/pi*(-1.0+1.0/(x*x)+3.0*s/(x*x*x*x));
      a1=TMath::Exp(x)/TMath::Sqrt(2*pi*x);
      r=1.0;
      bi1=1.0;
      for (i=1; i<=16; i++) {
         r=-0.125*r*(4.0-(2.0*i-1.0)*(2.0*i-1.0))/(i*x);
         bi1+=r;
         if(TMath::Abs(r/bi1)<1.0e-12) break;
      }
      sl1+=a1*bi1;
   }
   return sl1;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculates Beta-function Gamma(p)*Gamma(q)/Gamma(p+q).
/*
Double_t TMath::Beta(Double_t p, Double_t q)
{
   return ::ROOT::Math::beta(p, q);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Continued fraction evaluation by modified Lentz's method
/// used in calculation of incomplete Beta function.

Double_t TMath::BetaCf(Double_t x, Double_t a, Double_t b)
{
   Int_t itmax = 500;
   Double_t eps = 3.e-14;
   Double_t fpmin = 1.e-30;

   Int_t m, m2;
   Double_t aa, c, d, del, qab, qam, qap;
   Double_t h;
   qab = a+b;
   qap = a+1.0;
   qam = a-1.0;
   c = 1.0;
   d = 1.0 - qab*x/qap;
   if (TMath::Abs(d)<fpmin) d=fpmin;
   d=1.0/d;
   h=d;
   for (m=1; m<=itmax; m++) {
      m2=m*2;
      aa = m*(b-m)*x/((qam+ m2)*(a+m2));
      d = 1.0 +aa*d;
      if(TMath::Abs(d)<fpmin) d = fpmin;
      c = 1 +aa/c;
      if (TMath::Abs(c)<fpmin) c = fpmin;
      d=1.0/d;
      h*=d*c;
      aa = -(a+m)*(qab +m)*x/((a+m2)*(qap+m2));
      d=1.0+aa*d;
      if(TMath::Abs(d)<fpmin) d = fpmin;
      c = 1.0 +aa/c;
      if (TMath::Abs(c)<fpmin) c = fpmin;
      d=1.0/d;
      del = d*c;
      h*=del;
      if (TMath::Abs(del-1)<=eps) break;
   }
   if (m>itmax) {
      //Info("TMath::BetaCf", "a or b too big, or itmax too small, a=%g, b=%g, x=%g, h=%g, itmax=%d",
           //a,b,x,h,itmax);
   }
   return h;
}

////////////////////////////////////////////////////////////////////////////////
/// Computes the probability density function of the Beta distribution
/// (the distribution function is computed in BetaDistI).
/// The first argument is the point, where the function will be
/// computed, second and third are the function parameters.
/// Since the Beta distribution is bounded on both sides, it's often
/// used to represent processes with natural lower and upper limits.
/*
Double_t TMath::BetaDist(Double_t x, Double_t p, Double_t q)
{
   if ((x<0) || (x>1) || (p<=0) || (q<=0)){
      Error("TMath::BetaDist", "parameter value outside allowed range");
      return 0;
   }
   Double_t beta = TMath::Beta(p, q);
   Double_t r = TMath::Power(x, p-1)*TMath::Power(1-x, q-1)/beta;
   return r;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computes the distribution function of the Beta distribution.
/// The first argument is the point, where the function will be
/// computed, second and third are the function parameters.
/// Since the Beta distribution is bounded on both sides, it's often
/// used to represent processes with natural lower and upper limits.
/*
Double_t TMath::BetaDistI(Double_t x, Double_t p, Double_t q)
{
   if ((x<0) || (x>1) || (p<=0) || (q<=0)){
      Error("TMath::BetaDistI", "parameter value outside allowed range");
      return 0;
   }
   Double_t betai = TMath::BetaIncomplete(x, p, q);
   return betai;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Calculates the incomplete Beta-function.
/*
Double_t TMath::BetaIncomplete(Double_t x, Double_t a, Double_t b)
{
   return ::ROOT::Math::inc_beta(x, a, b);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Calculate the binomial coefficient n over k.

Double_t TMath::Binomial(Int_t n,Int_t k)
{
   if (n<0 || k<0 || n<k) return TMath::SignalingNaN();
   if (k==0 || n==k) return 1;

   Int_t k1=TMath::Min(k,n-k);
   Int_t k2=n-k1;
   Double_t fact=k2+1;
   for (Double_t i=k1;i>1.;--i)
      fact *= (k2+i)/i;
   return fact;
}

////////////////////////////////////////////////////////////////////////////////
/// Suppose an event occurs with probability _p_ per trial
/// Then the probability P of its occurring _k_ or more times
/// in _n_ trials is termed a cumulative binomial probability
/// the formula is P = sum_from_j=k_to_n(TMath::Binomial(n, j)*
/// *TMath::Power(p, j)*TMath::Power(1-p, n-j)
/// For _n_ larger than 12 BetaIncomplete is a much better way
/// to evaluate the sum than would be the straightforward sum calculation
/// for _n_ smaller than 12 either method is acceptable
/// ("Numerical Recipes")
///     --implementation by Anna Kreshuk
/*
Double_t TMath::BinomialI(Double_t p, Int_t n, Int_t k)
{
   if(k <= 0) return 1.0;
   if(k > n) return 0.0;
   if(k == n) return TMath::Power(p, n);

   return BetaIncomplete(p, Double_t(k), Double_t(n-k+1));
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computes the density of Cauchy distribution at point x
/// by default, standard Cauchy distribution is used (t=0, s=1)
///  - t is the location parameter
///  - s is the scale parameter
///
/// The Cauchy distribution, also called Lorentzian distribution,
/// is a continuous distribution describing resonance behavior
/// The mean and standard deviation of the Cauchy distribution are undefined.
/// The practical meaning of this is that collecting 1,000 data points gives
/// no more accurate an estimate of the mean and standard deviation than
/// does a single point.
/// The formula was taken from "Engineering Statistics Handbook" on site
/// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3663.htm
/// Implementation by Anna Kreshuk.
///
/// Example:
///
/// ~~~ {cpp}
///    TF1* fc = new TF1("fc", "TMath::CauchyDist(x, [0], [1])", -5, 5);
///    fc->SetParameters(0, 1);
///    fc->Draw();
/// ~~~

Double_t TMath::CauchyDist(Double_t x, Double_t t, Double_t s)
{
   Double_t temp= (x-t)*(x-t)/(s*s);
   Double_t result = 1/(s*TMath::Pi()*(1+temp));
   return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Evaluate the quantiles of the chi-squared probability distribution function.
/// Algorithm AS 91   Appl. Statist. (1975) Vol.24, P.35
/// implemented by Anna Kreshuk.
/// Incorporates the suggested changes in AS R85 (vol.40(1), pp.233-5, 1991)
///
/// \param[in] p     the probability value, at which the quantile is computed
/// \param[in] ndf   number of degrees of freedom
/*
Double_t TMath::ChisquareQuantile(Double_t p, Double_t ndf)
{
   Double_t c[]={0, 0.01, 0.222222, 0.32, 0.4, 1.24, 2.2,
                 4.67, 6.66, 6.73, 13.32, 60.0, 70.0,
                 84.0, 105.0, 120.0, 127.0, 140.0, 175.0,
                 210.0, 252.0, 264.0, 294.0, 346.0, 420.0,
                 462.0, 606.0, 672.0, 707.0, 735.0, 889.0,
                 932.0, 966.0, 1141.0, 1182.0, 1278.0, 1740.0,
                 2520.0, 5040.0};
   Double_t e = 5e-7;
   Double_t aa = 0.6931471806;
   Int_t maxit = 20;
   Double_t ch, p1, p2, q, t, a, b, x;
   Double_t s1, s2, s3, s4, s5, s6;

   if (ndf <= 0) return 0;

   Double_t g = TMath::LnGamma(0.5*ndf);

   Double_t xx = 0.5 * ndf;
   Double_t cp = xx - 1;
   if (ndf >= TMath::Log(p)*(-c[5])){
   //starting approximation for ndf less than or equal to 0.32
      if (ndf > c[3]) {
         x = TMath::NormQuantile(p);
         //starting approximation using Wilson and Hilferty estimate
         p1=c[2]/ndf;
         ch = ndf*TMath::Power((x*TMath::Sqrt(p1) + 1 - p1), 3);
         if (ch > c[6]*ndf + 6)
            ch = -2 * (TMath::Log(1-p) - cp * TMath::Log(0.5 * ch) + g);
      } else {
         ch = c[4];
         a = TMath::Log(1-p);
         do{
            q = ch;
            p1 = 1 + ch * (c[7]+ch);
            p2 = ch * (c[9] + ch * (c[8] + ch));
            t = -0.5 + (c[7] + 2 * ch) / p1 - (c[9] + ch * (c[10] + 3 * ch)) / p2;
            ch = ch - (1 - TMath::Exp(a + g + 0.5 * ch + cp * aa) *p2 / p1) / t;
         }while (TMath::Abs(q/ch - 1) > c[1]);
      }
   } else {
      ch = TMath::Power((p * xx * TMath::Exp(g + xx * aa)),(1./xx));
      if (ch < e) return ch;
   }
//call to algorithm AS 239 and calculation of seven term  Taylor series
   for (Int_t i=0; i<maxit; i++){
      q = ch;
      p1 = 0.5 * ch;
      p2 = p - TMath::Gamma(xx, p1);

      t = p2 * TMath::Exp(xx * aa + g + p1 - cp * TMath::Log(ch));
      b = t / ch;
      a = 0.5 * t - b * cp;
      s1 = (c[19] + a * (c[17] + a * (c[14] + a * (c[13] + a * (c[12] +c[11] * a))))) / c[24];
      s2 = (c[24] + a * (c[29] + a * (c[32] + a * (c[33] + c[35] * a)))) / c[37];
      s3 = (c[19] + a * (c[25] + a * (c[28] + c[31] * a))) / c[37];
      s4 = (c[20] + a * (c[27] + c[34] * a) + cp * (c[22] + a * (c[30] + c[36] * a))) / c[38];
      s5 = (c[13] + c[21] * a + cp * (c[18] + c[26] * a)) / c[37];
      s6 = (c[15] + cp * (c[23] + c[16] * cp)) / c[38];
      ch = ch + t * (1 + 0.5 * t * s1 - b * cp * (s1 - b * (s2 - b * (s3 - b * (s4 - b * (s5 - b * s6))))));
      if (TMath::Abs(q / ch - 1) > e) break;
   }
   return ch;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computes the density function of F-distribution
/// (probability function, integral of density, is computed in FDistI).
///
/// Parameters N and M stand for degrees of freedom of chi-squares
/// mentioned above parameter F is the actual variable x of the
/// density function p(x) and the point at which the density function
/// is calculated.
///
/// ### About F distribution:
/// F-distribution arises in testing whether two random samples
/// have the same variance. It is the ratio of two chi-square
/// distributions, with N and M degrees of freedom respectively,
/// where each chi-square is first divided by it's number of degrees
/// of freedom.
/// Implementation by Anna Kreshuk.
/*
Double_t TMath::FDist(Double_t F, Double_t N, Double_t M)
{
   return ::ROOT::Math::fdistribution_pdf(F,N,M);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Calculates the cumulative distribution function of F-distribution,
/// this function occurs in the statistical test of whether two observed
/// samples have the same variance. For this test a certain statistic F,
/// the ratio of observed dispersion of the first sample to that of the
/// second sample, is calculated. N and M stand for numbers of degrees
/// of freedom in the samples 1-FDistI() is the significance level at
/// which the hypothesis "1 has smaller variance than 2" can be rejected.
/// A small numerical value of 1 - FDistI() implies a very significant
/// rejection, in turn implying high confidence in the hypothesis
/// "1 has variance greater than 2".
///
/// Implementation by Anna Kreshuk.
/*
Double_t TMath::FDistI(Double_t F, Double_t N, Double_t M)
{
   Double_t fi = ::ROOT::Math::fdistribution_cdf(F,N,M);
   return fi;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computes the density function of Gamma distribution at point x.
///
/// \param[in] gamma   shape parameter
/// \param[in] mu      location parameter
/// \param[in] beta    scale parameter
///
/// The definition can be found in "Engineering Statistics Handbook" on site
/// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366b.htm
/// use now implementation in ROOT::Math::gamma_pdf
///
/// Begin_Macro
/// {
///   TCanvas *c1 = new TCanvas("c1", "c1", 700, 500);
///
///   c1->SetLogy();
///   c1->SetGridx();
///   c1->SetGridy();
///
///   TF1 *gdist = new TF1("gdist", "TMath::GammaDist(x, [0], [1], [2])", 0, 10);
///
///   gdist->SetParameters(0.5, 0., 1.);
///   gdist->SetLineColor(2);
///   TF1 *gdist1 = gdist->DrawCopy("L");
///   gdist->SetParameters(1.0, 0., 1.);
///   gdist->SetLineColor(3);
///   TF1 *gdist2 = gdist->DrawCopy("LSAME");
///   gdist->SetParameters(2.0, 0., 1.);
///   gdist->SetLineColor(4);
///   TF1 *gdist3 = gdist->DrawCopy("LSAME");
///   gdist->SetParameters(5.0, 0., 1.);
///   gdist->SetLineColor(6);
///   TF1 *gdist4 = gdist->DrawCopy("LSAME");
///
///   legend = new TLegend(0.15, 0.15, 0.5, 0.35);
///   legend->AddEntry(gdist1, "gamma = 0.5, mu = 0, beta = 1", "L");
///   legend->AddEntry(gdist2, "gamma = 1.0, mu = 0, beta = 1", "L");
///   legend->AddEntry(gdist3, "gamma = 2.0, mu = 0, beta = 1", "L");
///   legend->AddEntry(gdist4, "gamma = 5.0, mu = 0, beta = 1", "L");
///   legend->Draw();
/// }
/// End_Macro
/*
Double_t TMath::GammaDist(Double_t x, Double_t gamma, Double_t mu, Double_t beta)
{
   if ((x<mu) || (gamma<=0) || (beta <=0)) {
      Error("TMath::GammaDist", "illegal parameter values x = %f , gamma = %f beta = %f",x,gamma,beta);
      return 0;
   }
   return ::ROOT::Math::gamma_pdf(x, gamma, beta, mu);
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computes the probability density function of Laplace distribution
/// at point x, with location parameter alpha and shape parameter beta.
/// By default, alpha=0, beta=1
/// This distribution is known under different names, most common is
/// double exponential distribution, but it also appears as
/// the two-tailed exponential or the bilateral exponential distribution

Double_t TMath::LaplaceDist(Double_t x, Double_t alpha, Double_t beta)
{
   Double_t temp;
   temp  = TMath::Exp(-TMath::Abs((x-alpha)/beta));
   temp /= (2.*beta);
   return temp;
}

////////////////////////////////////////////////////////////////////////////////
/// Computes the distribution function of Laplace distribution
/// at point x, with location parameter alpha and shape parameter beta.
/// By default, alpha=0, beta=1
/// This distribution is known under different names, most common is
/// double exponential distribution, but it also appears as
/// the two-tailed exponential or the bilateral exponential distribution

Double_t TMath::LaplaceDistI(Double_t x, Double_t alpha, Double_t beta)
{
   Double_t temp;
   if (x<=alpha){
      temp = 0.5*TMath::Exp(-TMath::Abs((x-alpha)/beta));
   } else {
      temp = 1-0.5*TMath::Exp(-TMath::Abs((x-alpha)/beta));
   }
   return temp;
}

////////////////////////////////////////////////////////////////////////////////
/// Computes the density of LogNormal distribution at point x.
/// Variable X has lognormal distribution if Y=Ln(X) has normal distribution
///
/// \param[in] sigma  is the shape parameter
/// \param[in] theta  is the location parameter
/// \param[in] m      is the scale parameter
///
/// The formula was taken from "Engineering Statistics Handbook" on site
/// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3669.htm
/// Implementation using ROOT::Math::lognormal_pdf
///
/// Begin_Macro
/// {
///   TCanvas *c1 = new TCanvas("c1", "c1", 700, 500);
///
///   c1->SetLogy();
///   c1->SetGridx();
///   c1->SetGridy();
///
///   TF1 *logn = new TF1("logn", "TMath::LogNormal(x, [0], [1], [2])", 0, 5);
///   logn->SetMinimum(1e-3);
///
///   logn->SetParameters(0.5, 0., 1.);
///   logn->SetLineColor(2);
///   TF1 *logn1 = logn->DrawCopy("L");
///   logn->SetParameters(1.0, 0., 1.);
///   logn->SetLineColor(3);
///   TF1 *logn2 = logn->DrawCopy("LSAME");
///   logn->SetParameters(2.0, 0., 1.);
///   logn->SetLineColor(4);
///   TF1 *logn3 = logn->DrawCopy("LSAME");
///   logn->SetParameters(5.0, 0., 1.);
///   logn->SetLineColor(6);
///   TF1 *logn4 = logn->DrawCopy("LSAME");
///
///   legend = new TLegend(0.15, 0.15, 0.5, 0.35);
///   legend->AddEntry(logn1, "sigma = 0.5, theta = 0, m = 1", "L");
///   legend->AddEntry(logn2, "sigma = 1.0, theta = 0, m = 1", "L");
///   legend->AddEntry(logn3, "sigma = 2.0, theta = 0, m = 1", "L");
///   legend->AddEntry(logn4, "sigma = 5.0, theta = 0, m = 1", "L");
///   legend->Draw();
/// }
/// End_Macro
/*
Double_t TMath::LogNormal(Double_t x, Double_t sigma, Double_t theta, Double_t m)
{
   if ((x<theta) || (sigma<=0) || (m<=0)) {
      Error("TMath::Lognormal", "illegal parameter values");
      return 0;
   }
   // lognormal_pdf uses same definition of http://en.wikipedia.org/wiki/Log-normal_distribution
   // where mu = log(m)

   return ::ROOT::Math::lognormal_pdf(x, TMath::Log(m), sigma, theta);

}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computes quantiles for standard normal distribution N(0, 1)
/// at probability p
///
/// ALGORITHM AS241  APPL. STATIST. (1988) VOL. 37, NO. 3, 477-484.

Double_t TMath::NormQuantile(Double_t p)
{
   if ((p<=0)||(p>=1)) {
      //Error("TMath::NormQuantile", "probability outside (0, 1)");
      return 0;
   }

   Double_t  a0 = 3.3871328727963666080e0;
   Double_t  a1 = 1.3314166789178437745e+2;
   Double_t  a2 = 1.9715909503065514427e+3;
   Double_t  a3 = 1.3731693765509461125e+4;
   Double_t  a4 = 4.5921953931549871457e+4;
   Double_t  a5 = 6.7265770927008700853e+4;
   Double_t  a6 = 3.3430575583588128105e+4;
   Double_t  a7 = 2.5090809287301226727e+3;
   Double_t  b1 = 4.2313330701600911252e+1;
   Double_t  b2 = 6.8718700749205790830e+2;
   Double_t  b3 = 5.3941960214247511077e+3;
   Double_t  b4 = 2.1213794301586595867e+4;
   Double_t  b5 = 3.9307895800092710610e+4;
   Double_t  b6 = 2.8729085735721942674e+4;
   Double_t  b7 = 5.2264952788528545610e+3;
   Double_t  c0 = 1.42343711074968357734e0;
   Double_t  c1 = 4.63033784615654529590e0;
   Double_t  c2 = 5.76949722146069140550e0;
   Double_t  c3 = 3.64784832476320460504e0;
   Double_t  c4 = 1.27045825245236838258e0;
   Double_t  c5 = 2.41780725177450611770e-1;
   Double_t  c6 = 2.27238449892691845833e-2;
   Double_t  c7 = 7.74545014278341407640e-4;
   Double_t  d1 = 2.05319162663775882187e0;
   Double_t  d2 = 1.67638483018380384940e0;
   Double_t  d3 = 6.89767334985100004550e-1;
   Double_t  d4 = 1.48103976427480074590e-1;
   Double_t  d5 = 1.51986665636164571966e-2;
   Double_t  d6 = 5.47593808499534494600e-4;
   Double_t  d7 = 1.05075007164441684324e-9;
   Double_t  e0 = 6.65790464350110377720e0;
   Double_t  e1 = 5.46378491116411436990e0;
   Double_t  e2 = 1.78482653991729133580e0;
   Double_t  e3 = 2.96560571828504891230e-1;
   Double_t  e4 = 2.65321895265761230930e-2;
   Double_t  e5 = 1.24266094738807843860e-3;
   Double_t  e6 = 2.71155556874348757815e-5;
   Double_t  e7 = 2.01033439929228813265e-7;
   Double_t  f1 = 5.99832206555887937690e-1;
   Double_t  f2 = 1.36929880922735805310e-1;
   Double_t  f3 = 1.48753612908506148525e-2;
   Double_t  f4 = 7.86869131145613259100e-4;
   Double_t  f5 = 1.84631831751005468180e-5;
   Double_t  f6 = 1.42151175831644588870e-7;
   Double_t  f7 = 2.04426310338993978564e-15;

   Double_t split1 = 0.425;
   Double_t split2=5.;
   Double_t konst1=0.180625;
   Double_t konst2=1.6;

   Double_t q, r, quantile;
   q=p-0.5;
   if (TMath::Abs(q)<split1) {
      r=konst1-q*q;
      quantile = q* (((((((a7 * r + a6) * r + a5) * r + a4) * r + a3)
                 * r + a2) * r + a1) * r + a0) /
                 (((((((b7 * r + b6) * r + b5) * r + b4) * r + b3)
                 * r + b2) * r + b1) * r + 1.);
   } else {
      if(q<0) r=p;
      else    r=1-p;
      //error case
      if (r<=0)
         quantile=0;
      else {
         r=TMath::Sqrt(-TMath::Log(r));
         if (r<=split2) {
            r=r-konst2;
            quantile=(((((((c7 * r + c6) * r + c5) * r + c4) * r + c3)
                     * r + c2) * r + c1) * r + c0) /
                     (((((((d7 * r + d6) * r + d5) * r + d4) * r + d3)
                     * r + d2) * r + d1) * r + 1);
         } else{
            r=r-split2;
            quantile=(((((((e7 * r + e6) * r + e5) * r + e4) * r + e3)
                     * r + e2) * r + e1) * r + e0) /
                     (((((((f7 * r + f6) * r + f5) * r + f4) * r + f3)
                     * r + f2) * r + f1) * r + 1);
         }
         if (q<0) quantile=-quantile;
      }
   }
   return quantile;
}

////////////////////////////////////////////////////////////////////////////////
/// Simple recursive algorithm to find the permutations of
/// n natural numbers, not necessarily all distinct
/// adapted from CERNLIB routine PERMU.
/// The input array has to be initialised with a non descending
/// sequence. The method returns kFALSE when
/// all combinations are exhausted.

Bool_t TMath::Permute(Int_t n, Int_t *a)
{
   Int_t i,itmp;
   Int_t i1=-1;

   // find rightmost upward transition
   for(i=n-2; i>-1; i--) {
      if(a[i]<a[i+1]) {
         i1=i;
         break;
      }
   }
   // no more upward transitions, end of the story
   if(i1==-1) return kFALSE;
   else {
      // find lower right element higher than the lower
      // element of the upward transition
      for(i=n-1;i>i1;i--) {
         if(a[i] > a[i1]) {
            // swap the two
            itmp=a[i1];
            a[i1]=a[i];
            a[i]=itmp;
            break;
         }
      }
      // order the rest, in fact just invert, as there
      // are only downward transitions from here on
      for(i=0;i<(n-i1-1)/2;i++) {
         itmp=a[i1+i+1];
         a[i1+i+1]=a[n-i-1];
         a[n-i-1]=itmp;
      }
   }
   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Computes density function for Student's t- distribution
/// (the probability function (integral of density) is computed in StudentI).
///
/// First parameter stands for x - the actual variable of the
/// density function p(x) and the point at which the density is calculated.
/// Second parameter stands for number of degrees of freedom.
///
/// About Student distribution:
/// Student's t-distribution is used for many significance tests, for example,
/// for the Student's t-tests for the statistical significance of difference
/// between two sample means and for confidence intervals for the difference
/// between two population means.
///
/// Example: suppose we have a random sample of size n drawn from normal
/// distribution with mean Mu and st.deviation Sigma. Then the variable
///
///   t = (sample_mean - Mu)/(sample_deviation / sqrt(n))
///
/// has Student's t-distribution with n-1 degrees of freedom.
///
/// NOTE that this function's second argument is number of degrees of freedom,
/// not the sample size.
///
/// As the number of degrees of freedom grows, t-distribution approaches
/// Normal(0,1) distribution.
///
/// Implementation by Anna Kreshuk.
/*
Double_t TMath::Student(Double_t T, Double_t ndf)
{
   if (ndf < 1) {
      return 0;
   }

   Double_t r   = ndf;
   Double_t rh  = 0.5*r;
   Double_t rh1 = rh + 0.5;
   Double_t denom = TMath::Sqrt(r*TMath::Pi())*TMath::Gamma(rh)*TMath::Power(1+T*T/r, rh1);
   return TMath::Gamma(rh1)/denom;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Calculates the cumulative distribution function of Student's
/// t-distribution second parameter stands for number of degrees of freedom,
/// not for the number of samples
/// if x has Student's t-distribution, the function returns the probability of
/// x being less than T.
///
/// Implementation by Anna Kreshuk.
/*
Double_t TMath::StudentI(Double_t T, Double_t ndf)
{
   Double_t r = ndf;

   Double_t si = (T>0) ?
                 (1 - 0.5*BetaIncomplete((r/(r + T*T)), r*0.5, 0.5)) :
                 0.5*BetaIncomplete((r/(r + T*T)), r*0.5, 0.5);
   return si;
}
*/
////////////////////////////////////////////////////////////////////////////////
/// Computes quantiles of the Student's t-distribution
/// 1st argument is the probability, at which the quantile is computed
/// 2nd argument - the number of degrees of freedom of the
/// Student distribution
/// When the 3rd argument lower_tail is kTRUE (default)-
/// the algorithm returns such x0, that
///
///   P(x < x0)=p
///
/// upper tail (lower_tail is kFALSE)- the algorithm returns such x0, that
///
///   P(x > x0)=p
///
/// the algorithm was taken from:
///   G.W.Hill, "Algorithm 396, Student's t-quantiles"
///             "Communications of the ACM", 13(10), October 1970

Double_t TMath::StudentQuantile(Double_t p, Double_t ndf, Bool_t lower_tail)
{
   Double_t quantile;
   Double_t temp;
   Bool_t neg;
   Double_t q;
   if (ndf<1 || p>=1 || p<=0) {
      //Error("TMath::StudentQuantile", "illegal parameter values");
      return 0;
   }
   if ((lower_tail && p>0.5)||(!lower_tail && p<0.5)){
      neg=kFALSE;
      q=2*(lower_tail ? (1-p) : p);
   } else {
      neg=kTRUE;
      q=2*(lower_tail? p : (1-p));
   }

   if ((ndf-1)<1e-8) {
      temp=TMath::PiOver2()*q;
      quantile = TMath::Cos(temp)/TMath::Sin(temp);
   } else {
      if ((ndf-2)<1e-8) {
         quantile = TMath::Sqrt(2./(q*(2-q))-2);
      } else {
         Double_t a=1./(ndf-0.5);
         Double_t b=48./(a*a);
         Double_t c=((20700*a/b -98)*a-16)*a+96.36;
         Double_t d=((94.5/(b+c)-3.)/b+1)*TMath::Sqrt(a*TMath::PiOver2())*ndf;
         Double_t x=q*d;
         Double_t y=TMath::Power(x, (2./ndf));
         if (y>0.05+a){
            //asymptotic inverse expansion about normal
            x=TMath::NormQuantile(q*0.5);
            y=x*x;
            if (ndf<5) c+=0.3*(ndf-4.5)*(x+0.6);
            c+=(((0.05*d*x-5.)*x-7.)*x-2.)*x +b;
            y=(((((0.4*y+6.3)*y+36.)*y+94.5)/c - y-3.)/b+1)*x;
            y=a*y*y;
            if(y>0.002) y  = TMath::Exp(y)-1;
            else        y += 0.5*y*y;
         } else {
            y=((1./(((ndf+6.)/(ndf*y)-0.089*d-0.822)*(ndf+2.)*3)+0.5/(ndf+4.))*y-1.)*
              (ndf+1.)/(ndf+2.)+1/y;
         }
         quantile = TMath::Sqrt(ndf*y);
      }
   }
   if(neg) quantile=-quantile;
   return quantile;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the value of the Vavilov density function
///
/// \param[in] x      the point were the density function is evaluated
/// \param[in] kappa  value of kappa (distribution parameter)
/// \param[in] beta2  value of beta2 (distribution parameter)
///
/// The algorithm was taken from the CernLib function vavden(G115)
/// Reference: A.Rotondi and P.Montagna, Fast Calculation of Vavilov distribution
/// Nucl.Instr. and Meth. B47(1990), 215-224
///
/// Accuracy: quote from the reference above:
///
/// "The results of our code have been compared with the values of the Vavilov
/// density function computed numerically in an accurate way: our approximation
/// shows a difference of less than 3% around the peak of the density function, slowly
/// increasing going towards the extreme tails to the right and to the left"
///
/// Begin_Macro
/// {
///   TCanvas *c1 = new TCanvas("c1", "c1", 700, 500);
///
///   c1->SetGridx();
///   c1->SetGridy();
///
///   TF1 *vavilov = new TF1("vavilov", "TMath::Vavilov(x, [0], [1])", -3, 11);
///
///   vavilov->SetParameters(0.5, 0.);
///   vavilov->SetLineColor(2);
///   TF1 *vavilov1 = vavilov->DrawCopy("L");
///   vavilov->SetParameters(0.3, 0.);
///   vavilov->SetLineColor(3);
///   TF1 *vavilov2 = vavilov->DrawCopy("LSAME");
///   vavilov->SetParameters(0.2, 0.);
///   vavilov->SetLineColor(4);
///   TF1 *vavilov3 = vavilov->DrawCopy("LSAME");
///   vavilov->SetParameters(0.1, 0.);
///   vavilov->SetLineColor(6);
///   TF1 *vavilov4 = vavilov->DrawCopy("LSAME");
///
///   legend = new TLegend(0.5, 0.65, 0.85, 0.85);
///   legend->AddEntry(vavilov1, "kappa = 0.5, beta2 = 0", "L");
///   legend->AddEntry(vavilov2, "kappa = 0.3, beta2 = 0", "L");
///   legend->AddEntry(vavilov3, "kappa = 0.2, beta2 = 0", "L");
///   legend->AddEntry(vavilov4, "kappa = 0.1, beta2 = 0", "L");
///   legend->Draw();
/// }
/// End_Macro

Double_t TMath::Vavilov(Double_t x, Double_t kappa, Double_t beta2)
{
   Double_t *ac = new Double_t[14];
   Double_t *hc = new Double_t[9];

   Int_t itype;
   Int_t npt;
   TMath::VavilovSet(kappa, beta2, 0, 0, ac, hc, itype, npt);
   Double_t v =  TMath::VavilovDenEval(x, ac, hc, itype);
   delete [] ac;
   delete [] hc;
   return v;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the value of the Vavilov distribution function
///
/// \param[in] x      the point were the density function is evaluated
/// \param[in] kappa  value of kappa (distribution parameter)
/// \param[in] beta2  value of beta2 (distribution parameter)
///
/// The algorithm was taken from the CernLib function vavden(G115)
///
/// Reference: A.Rotondi and P.Montagna, Fast Calculation of Vavilov distribution
/// Nucl.Instr. and Meth. B47(1990), 215-224
///
/// Accuracy: quote from the reference above:
///
/// "The results of our code have been compared with the values of the Vavilov
/// density function computed numerically in an accurate way: our approximation
/// shows a difference of less than 3% around the peak of the density function, slowly
/// increasing going towards the extreme tails to the right and to the left"

Double_t TMath::VavilovI(Double_t x, Double_t kappa, Double_t beta2)
{
   Double_t *ac = new Double_t[14];
   Double_t *hc = new Double_t[9];
   Double_t *wcm = new Double_t[201];
   Int_t itype;
   Int_t npt;
   Int_t k;
   Double_t xx, v;
   TMath::VavilovSet(kappa, beta2, 1, wcm, ac, hc, itype, npt);
   if (x < ac[0]) v = 0;
   else if (x >=ac[8]) v = 1;
   else {
      xx = x - ac[0];
      k = Int_t(xx*ac[10]);
      v = TMath::Min(wcm[k] + (xx - k*ac[9])*(wcm[k+1]-wcm[k])*ac[10], 1.);
   }
   delete [] ac;
   delete [] hc;
   delete [] wcm;
   return v;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns the value of the Landau distribution function at point x.
/// The algorithm was taken from the Cernlib function dislan(G110)
/// Reference: K.S.Kolbig and B.Schorr, "A program package for the Landau
/// distribution", Computer Phys.Comm., 31(1984), 97-111
/*
Double_t TMath::LandauI(Double_t x)
{
   return ::ROOT::Math::landau_cdf(x);
}
*/

////////////////////////////////////////////////////////////////////////////////
/// Internal function, called by Vavilov and VavilovI

void TMath::VavilovSet(Double_t rkappa, Double_t beta2, Bool_t mode, Double_t *WCM, Double_t *AC, Double_t *HC, Int_t &itype, Int_t &npt)
{

   Double_t BKMNX1 = 0.02, BKMNY1 = 0.05, BKMNX2 = 0.12, BKMNY2 = 0.05,
      BKMNX3 = 0.22, BKMNY3 = 0.05, BKMXX1 = 0.1 , BKMXY1 = 1,
      BKMXX2 = 0.2 , BKMXY2 = 1   , BKMXX3 = 0.3 , BKMXY3 = 1;

   Double_t FBKX1 = 2/(BKMXX1-BKMNX1), FBKX2 = 2/(BKMXX2-BKMNX2),
      FBKX3 = 2/(BKMXX3-BKMNX3), FBKY1 = 2/(BKMXY1-BKMNY1),
      FBKY2 = 2/(BKMXY2-BKMNY2), FBKY3 = 2/(BKMXY3-BKMNY3);

   Double_t FNINV[] = {0, 1, 0.5, 0.33333333, 0.25, 0.2};

   Double_t EDGEC[]= {0, 0, 0.16666667e+0, 0.41666667e-1, 0.83333333e-2,
                      0.13888889e-1, 0.69444444e-2, 0.77160493e-3};

   Double_t U1[] = {0, 0.25850868e+0,  0.32477982e-1, -0.59020496e-2,
                    0.            , 0.24880692e-1,  0.47404356e-2,
                    -0.74445130e-3,  0.73225731e-2,  0.           ,
                    0.11668284e-2,  0.           , -0.15727318e-2,-0.11210142e-2};

   Double_t U2[] = {0, 0.43142611e+0,  0.40797543e-1, -0.91490215e-2,
                    0.           ,  0.42127077e-1,  0.73167928e-2,
                    -0.14026047e-2,  0.16195241e-1,  0.24714789e-2,
                    0.20751278e-2,  0.           , -0.25141668e-2,-0.14064022e-2};

   Double_t U3[] = {0,  0.25225955e+0,  0.64820468e-1, -0.23615759e-1,
                    0.           ,  0.23834176e-1,  0.21624675e-2,
                    -0.26865597e-2, -0.54891384e-2,  0.39800522e-2,
                    0.48447456e-2, -0.89439554e-2, -0.62756944e-2,-0.24655436e-2};

   Double_t U4[] = {0, 0.12593231e+1, -0.20374501e+0,  0.95055662e-1,
                    -0.20771531e-1, -0.46865180e-1, -0.77222986e-2,
                    0.32241039e-2,  0.89882920e-2, -0.67167236e-2,
                    -0.13049241e-1,  0.18786468e-1,  0.14484097e-1};

   Double_t U5[] = {0, -0.24864376e-1, -0.10368495e-2,  0.14330117e-2,
                    0.20052730e-3,  0.18751903e-2,  0.12668869e-2,
                    0.48736023e-3,  0.34850854e-2,  0.           ,
                    -0.36597173e-3,  0.19372124e-2,  0.70761825e-3, 0.46898375e-3};

   Double_t U6[] = {0,  0.35855696e-1, -0.27542114e-1,  0.12631023e-1,
                    -0.30188807e-2, -0.84479939e-3,  0.           ,
                    0.45675843e-3, -0.69836141e-2,  0.39876546e-2,
                    -0.36055679e-2,  0.           ,  0.15298434e-2, 0.19247256e-2};

   Double_t U7[] = {0, 0.10234691e+2, -0.35619655e+1,  0.69387764e+0,
                    -0.14047599e+0, -0.19952390e+1, -0.45679694e+0,
                    0.           ,  0.50505298e+0};
   Double_t U8[] = {0,  0.21487518e+2, -0.11825253e+2,  0.43133087e+1,
                    -0.14500543e+1, -0.34343169e+1, -0.11063164e+1,
                    -0.21000819e+0,  0.17891643e+1, -0.89601916e+0,
                    0.39120793e+0,  0.73410606e+0,  0.           ,-0.32454506e+0};

   Double_t V1[] = {0, 0.27827257e+0, -0.14227603e-2,  0.24848327e-2,
                    0.           ,  0.45091424e-1,  0.80559636e-2,
                    -0.38974523e-2,  0.           , -0.30634124e-2,
                    0.75633702e-3,  0.54730726e-2,  0.19792507e-2};

   Double_t V2[] = {0, 0.41421789e+0, -0.30061649e-1,  0.52249697e-2,
                    0.           ,  0.12693873e+0,  0.22999801e-1,
                    -0.86792801e-2,  0.31875584e-1, -0.61757928e-2,
                    0.           ,  0.19716857e-1,  0.32596742e-2};

   Double_t V3[] = {0, 0.20191056e+0, -0.46831422e-1,  0.96777473e-2,
                    -0.17995317e-2,  0.53921588e-1,  0.35068740e-2,
                    -0.12621494e-1, -0.54996531e-2, -0.90029985e-2,
                    0.34958743e-2,  0.18513506e-1,  0.68332334e-2,-0.12940502e-2};

   Double_t V4[] = {0, 0.13206081e+1,  0.10036618e+0, -0.22015201e-1,
                    0.61667091e-2, -0.14986093e+0, -0.12720568e-1,
                    0.24972042e-1, -0.97751962e-2,  0.26087455e-1,
                    -0.11399062e-1, -0.48282515e-1, -0.98552378e-2};

   Double_t V5[] = {0, 0.16435243e-1,  0.36051400e-1,  0.23036520e-2,
                    -0.61666343e-3, -0.10775802e-1,  0.51476061e-2,
                    0.56856517e-2, -0.13438433e-1,  0.           ,
                    0.           , -0.25421507e-2,  0.20169108e-2,-0.15144931e-2};

   Double_t V6[] = {0, 0.33432405e-1,  0.60583916e-2, -0.23381379e-2,
                    0.83846081e-3, -0.13346861e-1, -0.17402116e-2,
                    0.21052496e-2,  0.15528195e-2,  0.21900670e-2,
                    -0.13202847e-2, -0.45124157e-2, -0.15629454e-2, 0.22499176e-3};

   Double_t V7[] = {0, 0.54529572e+1, -0.90906096e+0,  0.86122438e-1,
                    0.           , -0.12218009e+1, -0.32324120e+0,
                    -0.27373591e-1,  0.12173464e+0,  0.           ,
                    0.           ,  0.40917471e-1};

   Double_t V8[] = {0, 0.93841352e+1, -0.16276904e+1,  0.16571423e+0,
                    0.           , -0.18160479e+1, -0.50919193e+0,
                    -0.51384654e-1,  0.21413992e+0,  0.           ,
                    0.           ,  0.66596366e-1};

   Double_t W1[] = {0, 0.29712951e+0,  0.97572934e-2,  0.           ,
                    -0.15291686e-2,  0.35707399e-1,  0.96221631e-2,
                    -0.18402821e-2, -0.49821585e-2,  0.18831112e-2,
                    0.43541673e-2,  0.20301312e-2, -0.18723311e-2,-0.73403108e-3};

   Double_t W2[] = {0, 0.40882635e+0,  0.14474912e-1,  0.25023704e-2,
                    -0.37707379e-2,  0.18719727e+0,  0.56954987e-1,
                    0.           ,  0.23020158e-1,  0.50574313e-2,
                    0.94550140e-2,  0.19300232e-1};

   Double_t W3[] = {0, 0.16861629e+0,  0.           ,  0.36317285e-2,
                    -0.43657818e-2,  0.30144338e-1,  0.13891826e-1,
                    -0.58030495e-2, -0.38717547e-2,  0.85359607e-2,
                    0.14507659e-1,  0.82387775e-2, -0.10116105e-1,-0.55135670e-2};

   Double_t W4[] = {0, 0.13493891e+1, -0.26863185e-2, -0.35216040e-2,
                    0.24434909e-1, -0.83447911e-1, -0.48061360e-1,
                    0.76473951e-2,  0.24494430e-1, -0.16209200e-1,
                    -0.37768479e-1, -0.47890063e-1,  0.17778596e-1, 0.13179324e-1};

   Double_t W5[] = {0,  0.10264945e+0,  0.32738857e-1,  0.           ,
                    0.43608779e-2, -0.43097757e-1, -0.22647176e-2,
                    0.94531290e-2, -0.12442571e-1, -0.32283517e-2,
                    -0.75640352e-2, -0.88293329e-2,  0.52537299e-2, 0.13340546e-2};

   Double_t W6[] = {0, 0.29568177e-1, -0.16300060e-2, -0.21119745e-3,
                    0.23599053e-2, -0.48515387e-2, -0.40797531e-2,
                    0.40403265e-3,  0.18200105e-2, -0.14346306e-2,
                    -0.39165276e-2, -0.37432073e-2,  0.19950380e-2, 0.12222675e-2};

   Double_t W8[] = {0,  0.66184645e+1, -0.73866379e+0,  0.44693973e-1,
                    0.           , -0.14540925e+1, -0.39529833e+0,
                    -0.44293243e-1,  0.88741049e-1};

   itype = 0;
   if (rkappa <0.01 || rkappa >12) {
      //Error("Vavilov distribution", "illegal value of kappa");
      return;
   }

   Double_t DRK[6];
   Double_t DSIGM[6];
   Double_t ALFA[8];
   Int_t j;
   Double_t x, y, xx, yy, x2, x3, y2, y3, xy, p2, p3, q2, q3, pq;
   if (rkappa >= 0.29) {
      itype = 1;
      npt = 100;
      Double_t wk = 1./TMath::Sqrt(rkappa);

      AC[0] = (-0.032227*beta2-0.074275)*rkappa + (0.24533*beta2+0.070152)*wk + (-0.55610*beta2-3.1579);
      AC[8] = (-0.013483*beta2-0.048801)*rkappa + (-1.6921*beta2+8.3656)*wk + (-0.73275*beta2-3.5226);
      DRK[1] = wk*wk;
      DSIGM[1] = TMath::Sqrt(rkappa/(1-0.5*beta2));
      for (j=1; j<=4; j++) {
         DRK[j+1] = DRK[1]*DRK[j];
         DSIGM[j+1] = DSIGM[1]*DSIGM[j];
         ALFA[j+1] = (FNINV[j]-beta2*FNINV[j+1])*DRK[j];
      }
      HC[0]=TMath::Log(rkappa)+beta2+0.42278434;
      HC[1]=DSIGM[1];
      HC[2]=ALFA[3]*DSIGM[3];
      HC[3]=(3*ALFA[2]*ALFA[2] + ALFA[4])*DSIGM[4]-3;
      HC[4]=(10*ALFA[2]*ALFA[3]+ALFA[5])*DSIGM[5]-10*HC[2];
      HC[5]=HC[2]*HC[2];
      HC[6]=HC[2]*HC[3];
      HC[7]=HC[2]*HC[5];
      for (j=2; j<=7; j++)
         HC[j]*=EDGEC[j];
      HC[8]=0.39894228*HC[1];
   }
   else if (rkappa >=0.22) {
      itype = 2;
      npt = 150;
      x = 1+(rkappa-BKMXX3)*FBKX3;
      y = 1+(TMath::Sqrt(beta2)-BKMXY3)*FBKY3;
      xx = 2*x;
      yy = 2*y;
      x2 = xx*x-1;
      x3 = xx*x2-x;
      y2 = yy*y-1;
      y3 = yy*y2-y;
      xy = x*y;
      p2 = x2*y;
      p3 = x3*y;
      q2 = y2*x;
      q3 = y3*x;
      pq = x2*y2;
      AC[1] = W1[1] + W1[2]*x + W1[4]*x3 + W1[5]*y + W1[6]*y2 + W1[7]*y3 +
         W1[8]*xy + W1[9]*p2 + W1[10]*p3 + W1[11]*q2 + W1[12]*q3 + W1[13]*pq;
      AC[2] = W2[1] + W2[2]*x + W2[3]*x2 + W2[4]*x3 + W2[5]*y + W2[6]*y2 +
         W2[8]*xy + W2[9]*p2 + W2[10]*p3 + W2[11]*q2;
      AC[3] = W3[1] + W3[3]*x2 + W3[4]*x3 + W3[5]*y + W3[6]*y2 + W3[7]*y3 +
         W3[8]*xy + W3[9]*p2 + W3[10]*p3 + W3[11]*q2 + W3[12]*q3 + W3[13]*pq;
      AC[4] = W4[1] + W4[2]*x + W4[3]*x2 + W4[4]*x3 + W4[5]*y + W4[6]*y2 + W4[7]*y3 +
         W4[8]*xy + W4[9]*p2 + W4[10]*p3 + W4[11]*q2 + W4[12]*q3 + W4[13]*pq;
      AC[5] = W5[1] + W5[2]*x + W5[4]*x3 + W5[5]*y + W5[6]*y2 + W5[7]*y3 +
         W5[8]*xy + W5[9]*p2 + W5[10]*p3 + W5[11]*q2 + W5[12]*q3 + W5[13]*pq;
      AC[6] = W6[1] + W6[2]*x + W6[3]*x2 + W6[4]*x3 + W6[5]*y + W6[6]*y2 + W6[7]*y3 +
         W6[8]*xy + W6[9]*p2 + W6[10]*p3 + W6[11]*q2 + W6[12]*q3 + W6[13]*pq;
      AC[8] = W8[1] + W8[2]*x + W8[3]*x2 + W8[5]*y + W8[6]*y2 + W8[7]*y3 + W8[8]*xy;
      AC[0] = -3.05;
   } else if (rkappa >= 0.12) {
      itype = 3;
      npt = 200;
      x = 1 + (rkappa-BKMXX2)*FBKX2;
      y = 1 + (TMath::Sqrt(beta2)-BKMXY2)*FBKY2;
      xx = 2*x;
      yy = 2*y;
      x2 = xx*x-1;
      x3 = xx*x2-x;
      y2 = yy*y-1;
      y3 = yy*y2-y;
      xy = x*y;
      p2 = x2*y;
      p3 = x3*y;
      q2 = y2*x;
      q3 = y3*x;
      pq = x2*y2;
      AC[1] = V1[1] + V1[2]*x + V1[3]*x2 + V1[5]*y + V1[6]*y2 + V1[7]*y3 +
         V1[9]*p2 + V1[10]*p3 + V1[11]*q2 + V1[12]*q3;
      AC[2] = V2[1] + V2[2]*x + V2[3]*x2 + V2[5]*y + V2[6]*y2 + V2[7]*y3 +
         V2[8]*xy + V2[9]*p2 + V2[11]*q2 + V2[12]*q3;
      AC[3] = V3[1] + V3[2]*x + V3[3]*x2 + V3[4]*x3 + V3[5]*y + V3[6]*y2 + V3[7]*y3 +
         V3[8]*xy + V3[9]*p2 + V3[10]*p3 + V3[11]*q2 + V3[12]*q3 + V3[13]*pq;
      AC[4] = V4[1] + V4[2]*x + V4[3]*x2 + V4[4]*x3 + V4[5]*y + V4[6]*y2 + V4[7]*y3 +
         V4[8]*xy + V4[9]*p2 + V4[10]*p3 + V4[11]*q2 + V4[12]*q3;
      AC[5] = V5[1] + V5[2]*x + V5[3]*x2 + V5[4]*x3 + V5[5]*y + V5[6]*y2 + V5[7]*y3 +
         V5[8]*xy + V5[11]*q2 + V5[12]*q3 + V5[13]*pq;
      AC[6] = V6[1] + V6[2]*x + V6[3]*x2 + V6[4]*x3 + V6[5]*y + V6[6]*y2 + V6[7]*y3 +
         V6[8]*xy + V6[9]*p2 + V6[10]*p3 + V6[11]*q2 + V6[12]*q3 + V6[13]*pq;
      AC[7] = V7[1] + V7[2]*x + V7[3]*x2 + V7[5]*y + V7[6]*y2 + V7[7]*y3 +
         V7[8]*xy + V7[11]*q2;
      AC[8] = V8[1] + V8[2]*x + V8[3]*x2 + V8[5]*y + V8[6]*y2 + V8[7]*y3 +
         V8[8]*xy + V8[11]*q2;
      AC[0] = -3.04;
   } else {
      itype = 4;
      if (rkappa >=0.02) itype = 3;
      npt = 200;
      x = 1+(rkappa-BKMXX1)*FBKX1;
      y = 1+(TMath::Sqrt(beta2)-BKMXY1)*FBKY1;
      xx = 2*x;
      yy = 2*y;
      x2 = xx*x-1;
      x3 = xx*x2-x;
      y2 = yy*y-1;
      y3 = yy*y2-y;
      xy = x*y;
      p2 = x2*y;
      p3 = x3*y;
      q2 = y2*x;
      q3 = y3*x;
      pq = x2*y2;
      if (itype==3){
         AC[1] = U1[1] + U1[2]*x + U1[3]*x2 + U1[5]*y + U1[6]*y2 + U1[7]*y3 +
            U1[8]*xy + U1[10]*p3 + U1[12]*q3 + U1[13]*pq;
         AC[2] = U2[1] + U2[2]*x + U2[3]*x2 + U2[5]*y + U2[6]*y2 + U2[7]*y3 +
            U2[8]*xy + U2[9]*p2 + U2[10]*p3 + U2[12]*q3 + U2[13]*pq;
         AC[3] = U3[1] + U3[2]*x + U3[3]*x2 + U3[5]*y + U3[6]*y2 + U3[7]*y3 +
            U3[8]*xy + U3[9]*p2 + U3[10]*p3 + U3[11]*q2 + U3[12]*q3 + U3[13]*pq;
         AC[4] = U4[1] + U4[2]*x + U4[3]*x2 + U4[4]*x3 + U4[5]*y + U4[6]*y2 + U4[7]*y3 +
            U4[8]*xy + U4[9]*p2 + U4[10]*p3 + U4[11]*q2 + U4[12]*q3;
         AC[5] = U5[1] + U5[2]*x + U5[3]*x2 + U5[4]*x3 + U5[5]*y + U5[6]*y2 + U5[7]*y3 +
            U5[8]*xy + U5[10]*p3 + U5[11]*q2 + U5[12]*q3 + U5[13]*pq;
         AC[6] = U6[1] + U6[2]*x + U6[3]*x2 + U6[4]*x3 + U6[5]*y + U6[7]*y3 +
            U6[8]*xy + U6[9]*p2 + U6[10]*p3 + U6[12]*q3 + U6[13]*pq;
         AC[7] = U7[1] + U7[2]*x + U7[3]*x2 + U7[4]*x3 + U7[5]*y + U7[6]*y2 + U7[8]*xy;
      }
      AC[8] = U8[1] + U8[2]*x + U8[3]*x2 + U8[4]*x3 + U8[5]*y + U8[6]*y2 + U8[7]*y3 +
         U8[8]*xy + U8[9]*p2 + U8[10]*p3 + U8[11]*q2 + U8[13]*pq;
      AC[0] = -3.03;
   }

   AC[9] = (AC[8] - AC[0])/npt;
   AC[10] = 1./AC[9];
   if (itype == 3) {
      x = (AC[7]-AC[8])/(AC[7]*AC[8]);
      y = 1./TMath::Log(AC[8]/AC[7]);
      p2 = AC[7]*AC[7];
      AC[11] = p2*(AC[1]*TMath::Exp(-AC[2]*(AC[7]+AC[5]*p2)-
                                    AC[3]*TMath::Exp(-AC[4]*(AC[7]+AC[6]*p2)))-0.045*y/AC[7])/(1+x*y*AC[7]);
      AC[12] = (0.045+x*AC[11])*y;
   }
   if (itype == 4) AC[13] = 0.995/LandauI(AC[8]);

   if (mode==0) return;
   //
   x = AC[0];
   WCM[0] = 0;
   Double_t fl, fu;
   Int_t k;
   fl = TMath::VavilovDenEval(x, AC, HC, itype);
   for (k=1; k<=npt; k++) {
      x += AC[9];
      fu = TMath::VavilovDenEval(x, AC, HC, itype);
      WCM[k] = WCM[k-1] + fl + fu;
      fl = fu;
   }
   x = 0.5*AC[9];
   for (k=1; k<=npt; k++)
      WCM[k]*=x;
}

////////////////////////////////////////////////////////////////////////////////
/// Internal function, called by Vavilov and VavilovSet

Double_t TMath::VavilovDenEval(Double_t rlam, Double_t *AC, Double_t *HC, Int_t itype)
{
   Double_t v = 0;
   if (rlam < AC[0] || rlam > AC[8])
      return 0;
   Int_t k;
   Double_t x, fn, s;
   Double_t h[10];
   if (itype ==1 ) {
      fn = 1;
      x = (rlam + HC[0])*HC[1];
      h[1] = x;
      h[2] = x*x -1;
      for (k=2; k<=8; k++) {
         fn++;
         h[k+1] = x*h[k]-fn*h[k-1];
      }
      s = 1 + HC[7]*h[9];
      for (k=2; k<=6; k++)
         s+=HC[k]*h[k+1];
      v = HC[8]*TMath::Exp(-0.5*x*x)*TMath::Max(s, 0.);
   }
   else if (itype == 2) {
      x = rlam*rlam;
      v = AC[1]*TMath::Exp(-AC[2]*(rlam+AC[5]*x) - AC[3]*TMath::Exp(-AC[4]*(rlam+AC[6]*x)));
   }
   else if (itype == 3) {
      if (rlam < AC[7]) {
         x = rlam*rlam;
         v = AC[1]*TMath::Exp(-AC[2]*(rlam+AC[5]*x)-AC[3]*TMath::Exp(-AC[4]*(rlam+AC[6]*x)));
      } else {
         x = 1./rlam;
         v = (AC[11]*x + AC[12])*x;
      }
   }
   else if (itype == 4) {
      v = AC[13]*TMath::Landau(rlam);
   }
   return v;
}


//explicitly instantiate template functions from VecCore
#ifdef R__HAS_VECCORE
//#include <Math/Types.h>
template ROOT::Double_v vecCore::math::Sin(const ROOT::Double_v & x);
template ROOT::Double_v vecCore::math::Cos(const ROOT::Double_v & x);
template ROOT::Double_v vecCore::math::ASin(const ROOT::Double_v & x);
template ROOT::Double_v vecCore::math::ATan(const ROOT::Double_v & x);
template ROOT::Double_v vecCore::math::ATan2(const ROOT::Double_v & x,const ROOT::Double_v & y);
// missing in veccore
// template ROOT::Double_v vecCore::math::ACos(const ROOT::Double_v & x);
// template ROOT::Double_v vecCore::math::Sinh(const ROOT::Double_v & x);
// template ROOT::Double_v vecCore::math::Cosh(const ROOT::Double_v & x);
// template ROOT::Double_v vecCore::math::Tanh(const ROOT::Double_v & x);
// template ROOT::Double_v vecCore::math::Cbrt(const ROOT::Double_v & x);
#endif

// @(#)root/matrix:$Id: 2d00df45ce4c38c7ea0930d6b520cbf4cfb9152e $
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixTBase
    \ingroup Matrix
    \brief Linear Algebra Package

 ### Linear Algebra Package

 The present package implements all the basic algorithms dealing
 with vectors, matrices, matrix columns, rows, diagonals, etc.
 In addition eigen-Vector analysis and several matrix decomposition
 have been added (LU,QRH,Cholesky,Bunch-Kaufman and SVD) .
 The decompositions are used in matrix inversion, equation solving.

 For a dense matrix, elements are arranged in memory in a ROW-wise
 fashion . For (n x m) matrices where n*m <=kSizeMax (=25 currently)
 storage space is available on the stack, thus avoiding expensive
 allocation/deallocation of heap space . However, this introduces of
 course kSizeMax overhead for each matrix object . If this is an
 issue recompile with a new appropriate value (>=0) for kSizeMax

 Sparse matrices are also stored in row-wise fashion but additional
 row/column information is stored, see TMatrixTSparse source for
 additional details .

 Another way to assign and store matrix data is through Use
 see for instance stressLinear.cxx file .

 Unless otherwise specified, matrix and vector indices always start
 with 0, spanning up to the specified limit-1. However, there are
 constructors to which one can specify aribtrary lower and upper
 bounds, e.g. TMatrixD m(1,10,1,5) defines a matrix that ranges
 from 1..10, 1..5 (a(1,1)..a(10,5)).

 The present package provides all facilities to completely AVOID
 returning matrices. Use "TMatrixD A(TMatrixD::kTransposed,B);"
 and other fancy constructors as much as possible. If one really needs
 to return a matrix, return a TMatrixTLazy object instead. The
 conversion is completely transparent to the end user, e.g.
 "TMatrixT m = THaarMatrixT(5);" and _is_ efficient.

 Since TMatrixT et al. are fully integrated in ROOT, they of course
 can be stored in a ROOT database.

 For usage examples see $ROOTSYS/test/stressLinear.cxx

 ### Acknowledgements

 1. Oleg E. Kiselyov
    First implementations were based on the his code . We have diverged
    quite a bit since then but the ideas/code for lazy matrix and
    "nested function" are 100% his .
    You can see him and his code in action at http://okmij.org/ftp
 2. Chris R. Birchenhall,
    We adapted his idea of the implementation for the decomposition
    classes instead of our messy installation of matrix inversion
    His installation of matrix condition number, using an iterative
    scheme using the Hage algorithm is worth looking at !
    Chris has a nice writeup (matdoc.ps) on his matrix classes at
    ftp://ftp.mcc.ac.uk/pub/matclass/
 3. Mark Fischler and Steven Haywood of CLHEP
    They did the slave labor of spelling out all sub-determinants
    for Cramer inversion  of (4x4),(5x5) and (6x6) matrices
    The stack storage for small matrices was also taken from them
 4. Roldan Pozo of TNT (http://math.nist.gov/tnt/)
    He converted the EISPACK routines for the eigen-vector analysis to
    C++ . We started with his implementation
 5. Siegmund Brandt (http://siux00.physik.uni-siegen.de/~brandt/datan
    We adapted his (very-well) documented SVD routines

### How to efficiently use this package

#### 1. Never return complex objects (matrices or vectors)
   Danger: For example, when the following snippet:
~~~
   TMatrixD foo(int n)
   {
     TMatrixD foom(n,n); fill_in(foom); return foom;
   }
   TMatrixD m = foo(5);
~~~
   runs, it constructs matrix foo:foom, copies it onto stack as a
   return value and destroys foo:foom. Return value (a matrix)
   from foo() is then copied over to m (via a copy constructor),
   and the return value is destroyed. So, the matrix constructor is
   called 3 times and the destructor 2 times. For big matrices,
   the cost of multiple constructing/copying/destroying of objects
   may be very large. *Some* optimized compilers can cut down on 1
   copying/destroying, but still it leaves at least two calls to
   the constructor. Note, TMatrixDLazy (see below) can construct
   TMatrixD m "inplace", with only a _single_ call to the
   constructor.

#### 2. Use "two-address instructions"
~~~
   "void TMatrixD::operator += (const TMatrixD &B);"
~~~
    as much as possible.
    That is, to add two matrices, it's much more efficient to write
~~~
   A += B;
~~~
    than
~~~
   TMatrixD C = A + B;
~~~
   (if both operand should be preserved,
     TMatrixD C = A; C += B;
   is still better).

#### 3. Use glorified constructors when returning of an object seems inevitable:
~~~
   "TMatrixD A(TMatrixD::kTransposed,B);"
   "TMatrixD C(A,TMatrixD::kTransposeMult,B);"
~~~

  like in the following snippet (from $ROOTSYS/test/vmatrix.cxx)
  that verifies that for an orthogonal matrix T, T'T = TT' = E.

~~~
   TMatrixD haar = THaarMatrixD(5);
   TMatrixD unit(TMatrixD::kUnit,haar);
   TMatrixD haar_t(TMatrixD::kTransposed,haar);
   TMatrixD hth(haar,TMatrixD::kTransposeMult,haar);
   TMatrixD hht(haar,TMatrixD::kMult,haar_t);
   TMatrixD hht1 = haar; hht1 *= haar_t;
   VerifyMatrixIdentity(unit,hth);
   VerifyMatrixIdentity(unit,hht);
   VerifyMatrixIdentity(unit,hht1);
~~~

#### 4. Accessing row/col/diagonal of a matrix without much fuss
   (and without moving a lot of stuff around):

~~~
   TMatrixD m(n,n); TVectorD v(n); TMatrixDDiag(m) += 4;
   v = TMatrixDRow(m,0);
   TMatrixDColumn m1(m,1); m1(2) = 3; // the same as m(2,1)=3;
~~~
   Note, constructing of, say, TMatrixDDiag does *not* involve any
   copying of any elements of the source matrix.

#### 5. It's possible (and encouraged) to use "nested" functions
   For example, creating of a Hilbert matrix can be done as follows:

~~~
   void foo(const TMatrixD &m)
   {
    TMatrixD m1(TMatrixD::kZero,m);
    struct MakeHilbert : public TElementPosActionD {
       void Operation(Double_t &element)
          { element = 1./(fI+fJ-1); }
    };
    m1.Apply(MakeHilbert());
   }
~~~

   of course, using a special method THilbertMatrixD() is
   still more optimal, but not by a whole lot. And that's right,
   class MakeHilbert is declared *within* a function and local to
   that function. It means one can define another MakeHilbert class
   (within another function or outside of any function, that is, in
   the global scope), and it still will be OK. Note, this currently
   is not yet supported by the interpreter CINT.

   Another example is applying of a simple function to each matrix element:

~~~
   void foo(TMatrixD &m,TMatrixD &m1)
   {
    typedef  double (*dfunc_t)(double);
    class ApplyFunction : public TElementActionD {
       dfunc_t fFunc;
       void Operation(Double_t &element)
            { element=fFunc(element); }
     public:
       ApplyFunction(dfunc_t func):fFunc(func) {}
    };
    ApplyFunction x(TMath::Sin);
    m.Apply(x);
   }
~~~

   Validation code $ROOTSYS/test/vmatrix.cxx and vvector.cxx contain
   a few more examples of that kind.

#### 6. Lazy matrices:
   instead of returning an object return a "recipe"
   how to make it. The full matrix would be rolled out only when
   and where it's needed:
~~~
   TMatrixD haar = THaarMatrixD(5);
~~~
   THaarMatrixD() is a *class*, not a simple function. However
   similar this looks to a returning of an object (see note #1
   above), it's dramatically different. THaarMatrixD() constructs a
   TMatrixDLazy, an object of just a few bytes long. A special
   "TMatrixD(const TMatrixDLazy &recipe)" constructor follows the
   recipe and makes the matrix haar() right in place. No matrix
   element is moved whatsoever!

*/

////////////////////////////////////////////////////////////////////////////////
///
/// TMatrixTBase
///
/// Template of base class in the linear algebra package
///
///  matrix properties are stored here, however the data storage is part
///  of the derived classes

//#include "TMatrixTBase.h"
//#include "TVectorT.h"
//#include "TROOT.h"
//#include "TClass.h"
//#include "TMath.h"
#include <limits.h>

Int_t gMatrixCheck = 1;

templateClassImp(TMatrixTBase);


////////////////////////////////////////////////////////////////////////////////
/// Lexical sort on array data using indices first and second

template<class Element>
void TMatrixTBase<Element>::DoubleLexSort(Int_t n,Int_t *first,Int_t *second,Element *data)
{
   const int incs[] = {1,5,19,41,109,209,505,929,2161,3905,8929,16001,INT_MAX};

   Int_t kinc = 0;
   while (incs[kinc] <= n/2)
      kinc++;
   kinc -= 1;

   // incs[kinc] is the greatest value in the sequence that is also <= n/2.
   // If n == {0,1}, kinc == -1 and so no sort will take place.

   for( ; kinc >= 0; kinc--) {
      const Int_t inc = incs[kinc];

      for (Int_t k = inc; k < n; k++) {
         const Element tmp = data[k];
         const Int_t fi = first [k];
         const Int_t se = second[k];
         Int_t j;
         for (j = k; j >= inc; j -= inc) {
            if ( fi < first[j-inc] || (fi == first[j-inc] && se < second[j-inc]) ) {
               data  [j] = data  [j-inc];
               first [j] = first [j-inc];
               second[j] = second[j-inc];
            } else
               break;
         }
         data  [j] = tmp;
         first [j] = fi;
         second[j] = se;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Lexical sort on array data using indices first and second

template<class Element>
void TMatrixTBase<Element>::IndexedLexSort(Int_t n,Int_t *first,Int_t swapFirst,
                                           Int_t *second,Int_t swapSecond,Int_t *index)
{
   const int incs[] = {1,5,19,41,109,209,505,929,2161,3905,8929,16001,INT_MAX};

   Int_t kinc = 0;
   while (incs[kinc] <= n/2)
      kinc++;
   kinc -= 1;

   // incs[kinc] is the greatest value in the sequence that is also less
   // than n/2.

   for( ; kinc >= 0; kinc--) {
      const Int_t inc = incs[kinc];

      if ( !swapFirst && !swapSecond ) {
         for (Int_t k = inc; k < n; k++) {
            // loop over all subarrays defined by the current increment
            const Int_t ktemp = index[k];
            const Int_t fi = first [ktemp];
            const Int_t se = second[ktemp];
            // Insert element k into the sorted subarray
            Int_t j;
            for (j = k; j >= inc; j -= inc) {
               // Loop over the elements in the current subarray
               if (fi < first[index[j-inc]] || (fi == first[index[j-inc]] && se < second[index[j-inc]])) {
                  // Swap elements j and j - inc, implicitly use the fact
                  // that ktemp hold element j to avoid having to assign to
                  // element j-inc
                    index[j] = index[j-inc];
               } else {
                  // There are no more elements in this sorted subarray which
                  // are less than element j
                  break;
               }
            } // End loop over the elements in the current subarray
            // Move index[j] out of temporary storage
            index[j] = ktemp;
            // The element has been inserted into the subarray.
         } // End loop over all subarrays defined by the current increment
      } else if ( swapSecond && !swapFirst ) {
         for (Int_t k = inc; k < n; k++) {
            const Int_t ktemp = index[k];
            const Int_t fi = first [ktemp];
            const Int_t se = second[k];
            Int_t j;
            for (j = k; j >= inc; j -= inc) {
               if (fi < first[index[j-inc]] || (fi == first[index[j-inc]] && se < second[j-inc])) {
                  index [j] = index[j-inc];
                  second[j] = second[j-inc];
               } else {
                  break;
               }
            }
            index[j]  = ktemp;
            second[j] = se;
         }
      } else if (swapFirst  && !swapSecond) {
         for (Int_t k = inc; k < n; k++ ) {
            const Int_t ktemp = index[k];
            const Int_t fi = first[k];
            const Int_t se = second[ktemp];
            Int_t j;
            for (j = k; j >= inc; j -= inc) {
               if ( fi < first[j-inc] || (fi == first[j-inc] && se < second[ index[j-inc]])) {
                  index[j] = index[j-inc];
                  first[j] = first[j-inc];
               } else {
                  break;
               }
            }
            index[j] = ktemp;
            first[j] = fi;
         }
      } else { // Swap both
         for (Int_t k = inc; k < n; k++ ) {
            const Int_t ktemp = index[k];
            const Int_t fi = first [k];
            const Int_t se = second[k];
            Int_t j;
            for (j = k; j >= inc; j -= inc) {
               if ( fi < first[j-inc] || (fi == first[j-inc] && se < second[j-inc])) {
                  index [j] = index [j-inc];
                  first [j] = first [j-inc];
                  second[j] = second[j-inc];
               } else {
                  break;
               }
            }
            index[j]  = ktemp;
            first[j]  = fi;
            second[j] = se;
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Copy array data to matrix . It is assumed that array is of size >= fNelems
/// (=)))) fNrows*fNcols
/// option indicates how the data is stored in the array:
/// option =
///         - 'F'   : column major (Fortran) m[i][j] = array[i+j*fNrows]
///         - else  : row major    (C)       m[i][j] = array[i*fNcols+j] (default)

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::SetMatrixArray(const Element *data,Option_t *option)
{
   //R__ASSERT(IsValid());

   TString opt = option;
   opt.ToUpper();

   Element *elem = GetMatrixArray();
   if (opt.Contains("F")) {
      for (Int_t irow = 0; irow < fNrows; irow++) {
         const Int_t off1 = irow*fNcols;
         Int_t off2 = 0;
         for (Int_t icol = 0; icol < fNcols; icol++) {
            elem[off1+icol] = data[off2+irow];
            off2 += fNrows;
         }
      }
   }
   else
      memcpy(elem,data,fNelems*sizeof(Element));

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Check whether matrix is symmetric

template<class Element>
Bool_t TMatrixTBase<Element>::IsSymmetric() const
{
  //R__ASSERT(IsValid());

   if ((fNrows != fNcols) || (fRowLwb != fColLwb))
      return kFALSE;

   const Element * const elem = GetMatrixArray();
   for (Int_t irow = 0; irow < fNrows; irow++) {
      const Int_t rowOff = irow*fNcols;
      Int_t colOff = 0;
      for (Int_t icol = 0; icol < irow; icol++) {
         if (elem[rowOff+icol] != elem[colOff+irow])
           return kFALSE;
         colOff += fNrows;
      }
   }
   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Copy matrix data to array . It is assumed that array is of size >= fNelems
/// (=)))) fNrows*fNcols
/// option indicates how the data is stored in the array:
/// option =
///         - 'F'   : column major (Fortran) array[i+j*fNrows] = m[i][j]
///         - else  : row major    (C)       array[i*fNcols+j] = m[i][j] (default)

template<class Element>
void TMatrixTBase<Element>::GetMatrix2Array(Element *data,Option_t *option) const
{
   //R__ASSERT(IsValid());

   TString opt = option;
   opt.ToUpper();

   const Element * const elem = GetMatrixArray();
   if (opt.Contains("F")) {
      for (Int_t irow = 0; irow < fNrows; irow++) {
         const Int_t off1 = irow*fNcols;
         Int_t off2 = 0;
         for (Int_t icol = 0; icol < fNcols; icol++) {
            data[off2+irow] = elem[off1+icol];
            off2 += fNrows;
         }
      }
   }
   else
      memcpy(data,elem,fNelems*sizeof(Element));
}

////////////////////////////////////////////////////////////////////////////////
/// Copy n elements from array v to row rown starting at column coln

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::InsertRow(Int_t rown,Int_t coln,const Element *v,Int_t n)
{
   const Int_t arown = rown-fRowLwb;
   const Int_t acoln = coln-fColLwb;
   const Int_t nr = (n > 0) ? n : fNcols;

   if (gMatrixCheck) {
      if (arown >= fNrows || arown < 0) {
         //Error("InsertRow","row %d out of matrix range",rown);
         return *this;
      }

      if (acoln >= fNcols || acoln < 0) {
         //Error("InsertRow","column %d out of matrix range",coln);
         return *this;
      }

      if (acoln+nr > fNcols || nr < 0) {
         //Error("InsertRow","row length %d out of range",nr);
         return *this;
      }
   }

   const Int_t off = arown*fNcols+acoln;
   Element * const elem = GetMatrixArray()+off;
   memcpy(elem,v,nr*sizeof(Element));

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Store in array v, n matrix elements of row rown starting at column coln

template<class Element>
void TMatrixTBase<Element>::ExtractRow(Int_t rown,Int_t coln,Element *v,Int_t n) const
{
   const Int_t arown = rown-fRowLwb;
   const Int_t acoln = coln-fColLwb;
   const Int_t nr = (n > 0) ? n : fNcols;

   if (gMatrixCheck) {
      if (arown >= fNrows || arown < 0) {
         //Error("ExtractRow","row %d out of matrix range",rown);
         return;
      }

      if (acoln >= fNcols || acoln < 0) {
         //Error("ExtractRow","column %d out of matrix range",coln);
         return;
      }

      if (acoln+n >= fNcols || nr < 0) {
         //Error("ExtractRow","row length %d out of range",nr);
         return;
      }
   }

   const Int_t off = arown*fNcols+acoln;
   const Element * const elem = GetMatrixArray()+off;
   memcpy(v,elem,nr*sizeof(Element));
}

////////////////////////////////////////////////////////////////////////////////
/// Shift the row index by adding row_shift and the column index by adding
/// col_shift, respectively. So [rowLwb..rowUpb][colLwb..colUpb] becomes
/// [rowLwb+row_shift..rowUpb+row_shift][colLwb+col_shift..colUpb+col_shift]

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Shift(Int_t row_shift,Int_t col_shift)
{
   fRowLwb += row_shift;
   fColLwb += col_shift;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set matrix elements to zero

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Zero()
{
   //R__ASSERT(IsValid());
   memset(this->GetMatrixArray(),0,fNelems*sizeof(Element));

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Take an absolute value of a matrix, i.e. apply Abs() to each element.

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Abs()
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNelems;
   while (ep < fp) {
      *ep = TMath::Abs(*ep);
      ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Square each element of the matrix.

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Sqr()
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNelems;
   while (ep < fp) {
      *ep = (*ep) * (*ep);
      ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Take square root of all elements.

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Sqrt()
{
   //R__ASSERT(IsValid());

         Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNelems;
   while (ep < fp) {
      *ep = TMath::Sqrt(*ep);
      ep++;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Make a unit matrix (matrix need not be a square one).

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::UnitMatrix()
{
   //R__ASSERT(IsValid());

   Element *ep = this->GetMatrixArray();
   memset(ep,0,fNelems*sizeof(Element));
   for (Int_t i = fRowLwb; i <= fRowLwb+fNrows-1; i++)
      for (Int_t j = fColLwb; j <= fColLwb+fNcols-1; j++)
         *ep++ = (i==j ? 1.0 : 0.0);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// option:
///  - "D"   :  b(i,j) = a(i,j)/sqrt(abs*(v(i)*v(j)))  (default)
///  - else  :  b(i,j) = a(i,j)*sqrt(abs*(v(i)*v(j)))  (default)

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::NormByDiag(const TVectorT<Element> &v,Option_t *option)
{
   //R__ASSERT(IsValid());
   //R__ASSERT(v.IsValid());

   if (gMatrixCheck) {
      const Int_t nMax = TMath::Max(fNrows,fNcols);
      if (v.GetNoElements() < nMax) {
         //Error("NormByDiag","vector shorter than matrix diagonal");
         return *this;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t divide = (opt.Contains("D")) ? 1 : 0;

   const Element *pV = v.GetMatrixArray();
         Element *mp = this->GetMatrixArray();

   if (divide) {
      for (Int_t irow = 0; irow < fNrows; irow++) {
         if (pV[irow] != 0.0) {
            for (Int_t icol = 0; icol < fNcols; icol++) {
               if (pV[icol] != 0.0) {
                  const Element val = TMath::Sqrt(TMath::Abs(pV[irow]*pV[icol]));
                  *mp++ /= val;
               } else {
                  //Error("NormbyDiag","vector element %d is zero",icol);
                  mp++;
               }
            }
         } else {
            //Error("NormbyDiag","vector element %d is zero",irow);
            mp += fNcols;
         }
      }
   } else {
      for (Int_t irow = 0; irow < fNrows; irow++) {
         for (Int_t icol = 0; icol < fNcols; icol++) {
            const Element val = TMath::Sqrt(TMath::Abs(pV[irow]*pV[icol]));
            *mp++ *= val;
         }
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Row matrix norm, MAX{ SUM{ |M(i,j)|, over j}, over i}.
/// The norm is induced by the infinity vector norm.

template<class Element>
Element TMatrixTBase<Element>::RowNorm() const
{
   //R__ASSERT(IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
         Element norm = 0;

   // Scan the matrix row-after-row
   while (ep < fp) {
      Element sum = 0;
      // Scan a row to compute the sum
      for (Int_t j = 0; j < fNcols; j++)
         sum += TMath::Abs(*ep++);
      norm = TMath::Max(norm,sum);
   }

   //R__ASSERT(ep == fp);

   return norm;
}

////////////////////////////////////////////////////////////////////////////////
/// Column matrix norm, MAX{ SUM{ |M(i,j)|, over i}, over j}.
/// The norm is induced by the 1 vector norm.

template<class Element>
Element TMatrixTBase<Element>::ColNorm() const
{
   //R__ASSERT(IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNcols;
         Element norm = 0;

   // Scan the matrix col-after-col
   while (ep < fp) {
      Element sum = 0;
      // Scan a col to compute the sum
      for (Int_t i = 0; i < fNrows; i++,ep += fNcols)
         sum += TMath::Abs(*ep);
      ep -= fNelems-1;         // Point ep to the beginning of the next col
      norm = TMath::Max(norm,sum);
   }

   //R__ASSERT(ep == fp);

   return norm;
}

////////////////////////////////////////////////////////////////////////////////
/// Square of the Euclidian norm, SUM{ m(i,j)^2 }.

template<class Element>
Element TMatrixTBase<Element>::E2Norm() const
{
   //R__ASSERT(IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
         Element sum = 0;

   for ( ; ep < fp; ep++)
      sum += (*ep) * (*ep);

   return sum;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute the number of elements != 0.0

template<class Element>
Int_t TMatrixTBase<Element>::NonZeros() const
{
   //R__ASSERT(IsValid());

   Int_t nr_nonzeros = 0;
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNelems;
   while (ep < fp)
      if (*ep++ != 0.0) nr_nonzeros++;

   return nr_nonzeros;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute sum of elements

template<class Element>
Element TMatrixTBase<Element>::Sum() const
{
   //R__ASSERT(IsValid());

   Element sum = 0.0;
   const Element *ep = this->GetMatrixArray();
   const Element * const fp = ep+fNelems;
   while (ep < fp)
      sum += *ep++;

   return sum;
}

////////////////////////////////////////////////////////////////////////////////
/// return minimum matrix element value

template<class Element>
Element TMatrixTBase<Element>::Min() const
{
   //R__ASSERT(IsValid());

   const Element * const ep = this->GetMatrixArray();
   const Int_t index = TMath::LocMin(fNelems,ep);
   return ep[index];
}

////////////////////////////////////////////////////////////////////////////////
/// return maximum vector element value

template<class Element>
Element TMatrixTBase<Element>::Max() const
{
   //R__ASSERT(IsValid());

   const Element * const ep = this->GetMatrixArray();
   const Int_t index = TMath::LocMax(fNelems,ep);
   return ep[index];
}

////////////////////////////////////////////////////////////////////////////////
/// Draw this matrix
/// The histogram is named "TMatrixT" by default and no title

template<class Element>
void TMatrixTBase<Element>::Draw(Option_t *option)
{
   //gROOT->ProcessLine(Form("THistPainter::PaintSpecialObjects((TObject*)0x%lx,\"%s\");",
                           //(ULong_t)this, option));
}

////////////////////////////////////////////////////////////////////////////////
/// Print the matrix as a table of elements.
/// By default the format "%11.4g" is used to print one element.
/// One can specify an alternative format with eg
///  option ="f=  %6.2f  "

template<class Element>
void TMatrixTBase<Element>::Print(Option_t *option) const
{
   //if (!IsValid()) {
      //Error("Print","Matrix is invalid");
      //return;
   //}

   //build format
   const char *format = "%11.4g ";
   if (option) {
      const char *f = strstr(option,"f=");
      if (f) format = f+2;
   }
   char topbar[100];
   snprintf(topbar,100,format,123.456789);
   Int_t nch = strlen(topbar)+1;
   if (nch > 18) nch = 18;
   char ftopbar[20];
   for (Int_t i = 0; i < nch; i++) ftopbar[i] = ' ';
   Int_t nk = 1 + Int_t(TMath::Log10(fNcols));
   snprintf(ftopbar+nch/2,20-nch/2,"%s%dd","%",nk);
   Int_t nch2 = strlen(ftopbar);
   for (Int_t i = nch2; i < nch; i++) ftopbar[i] = ' ';
   ftopbar[nch] = '|';
   ftopbar[nch+1] = 0;

   printf("\n%dx%d matrix is as follows",fNrows,fNcols);

   Int_t cols_per_sheet = 5;
   if (nch <= 8) cols_per_sheet =10;
   const Int_t ncols  = fNcols;
   const Int_t nrows  = fNrows;
   const Int_t collwb = fColLwb;
   const Int_t rowlwb = fRowLwb;
   nk = 5+nch*TMath::Min(cols_per_sheet,fNcols);
   for (Int_t i = 0; i < nk; i++) topbar[i] = '-';
   topbar[nk] = 0;
   for (Int_t sheet_counter = 1; sheet_counter <= ncols; sheet_counter += cols_per_sheet) {
      printf("\n\n     |");
      for (Int_t j = sheet_counter; j < sheet_counter+cols_per_sheet && j <= ncols; j++)
         printf(ftopbar,j+collwb-1);
      printf("\n%s\n",topbar);
      if (fNelems <= 0) continue;
      for (Int_t i = 1; i <= nrows; i++) {
         printf("%4d |",i+rowlwb-1);
         for (Int_t j = sheet_counter; j < sheet_counter+cols_per_sheet && j <= ncols; j++)
            printf(format,(*this)(i+rowlwb-1,j+collwb-1));
         printf("\n");
      }
   }
   printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
/// Are all matrix elements equal to val?

template<class Element>
Bool_t TMatrixTBase<Element>::operator==(Element val) const
{
   //R__ASSERT(IsValid());

   if (val == 0. && fNelems == 0)
      return kTRUE;

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
   for (; ep < fp; ep++)
      if (!(*ep == val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all matrix elements not equal to val?

template<class Element>
Bool_t TMatrixTBase<Element>::operator!=(Element val) const
{
   //R__ASSERT(IsValid());

   if (val == 0. && fNelems == 0)
      return kFALSE;

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
   for (; ep < fp; ep++)
      if (!(*ep != val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all matrix elements < val?

template<class Element>
Bool_t TMatrixTBase<Element>::operator<(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
   for (; ep < fp; ep++)
      if (!(*ep < val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all matrix elements <= val?

template<class Element>
Bool_t TMatrixTBase<Element>::operator<=(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
   for (; ep < fp; ep++)
      if (!(*ep <= val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all matrix elements > val?

template<class Element>
Bool_t TMatrixTBase<Element>::operator>(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
   for (; ep < fp; ep++)
      if (!(*ep > val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Are all matrix elements >= val?

template<class Element>
Bool_t TMatrixTBase<Element>::operator>=(Element val) const
{
   //R__ASSERT(IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
   for (; ep < fp; ep++)
      if (!(*ep >= val))
         return kFALSE;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Apply action to each matrix element

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Apply(const TElementActionT<Element> &action)
{
   //R__ASSERT(IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+fNelems;
   while (ep < ep_last)
      action.Operation(*ep++);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Apply action to each element of the matrix. To action the location
/// of the current element is passed.

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Apply(const TElementPosActionT<Element> &action)
{
   //R__ASSERT(IsValid());

   Element *ep = this->GetMatrixArray();
   for (action.fI = fRowLwb; action.fI < fRowLwb+fNrows; action.fI++)
      for (action.fJ = fColLwb; action.fJ < fColLwb+fNcols; action.fJ++)
         action.Operation(*ep++);

   //R__ASSERT(ep == this->GetMatrixArray()+fNelems);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Randomize matrix element values

template<class Element>
TMatrixTBase<Element> &TMatrixTBase<Element>::Randomize(Element alpha,Element beta,Double_t &seed)
{
   //R__ASSERT(IsValid());

   const Element scale = beta-alpha;
   const Element shift = alpha/scale;

         Element *       ep = GetMatrixArray();
   const Element * const fp = ep+fNelems;
   while (ep < fp)
      *ep++ = scale*(Drand(seed)+shift);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Check to see if two matrices are identical.

template<class Element>
Bool_t operator==(const TMatrixTBase<Element> &m1,const TMatrixTBase<Element> &m2)
{
   if (!AreCompatible(m1,m2)) return kFALSE;
   return (memcmp(m1.GetMatrixArray(),m2.GetMatrixArray(),
                   m1.GetNoElements()*sizeof(Element)) == 0);
}

////////////////////////////////////////////////////////////////////////////////
/// Square of the Euclidian norm of the difference between two matrices.

template<class Element>
Element E2Norm(const TMatrixTBase<Element> &m1,const TMatrixTBase<Element> &m2)
{
   if (gMatrixCheck && !AreCompatible(m1,m2)) {
      //::Error("E2Norm","matrices not compatible");
      return -1.0;
   }

   const Element *        mp1 = m1.GetMatrixArray();
   const Element *        mp2 = m2.GetMatrixArray();
   const Element * const fmp1 = mp1+m1.GetNoElements();

   Element sum = 0.0;
   for (; mp1 < fmp1; mp1++, mp2++)
      sum += (*mp1 - *mp2)*(*mp1 - *mp2);

   return sum;
}

////////////////////////////////////////////////////////////////////////////////
/// Check that matrice sm1 and m2 areboth valid and have identical shapes .

template<class Element1,class Element2>
Bool_t AreCompatible(const TMatrixTBase<Element1> &m1,const TMatrixTBase<Element2> &m2,Int_t verbose)
{
   //if (!m1.IsValid()) {
   //   if (verbose)
   //      ::Error("AreCompatible", "matrix 1 not valid");
    //  return kFALSE;
   //}
   //if (!m2.IsValid()) {
   //   if (verbose)
    //     ::Error("AreCompatible", "matrix 2 not valid");
    //  return kFALSE;
   //}

   if (m1.GetNrows()  != m2.GetNrows()  || m1.GetNcols()  != m2.GetNcols() ||
       m1.GetRowLwb() != m2.GetRowLwb() || m1.GetColLwb() != m2.GetColLwb()) {
      if (verbose) {}
         //::Error("AreCompatible", "matrices 1 and 2 not compatible");
      return kFALSE;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Compare two matrices and print out the result of the comparison.

template<class Element>
void Compare(const TMatrixTBase<Element> &m1,const TMatrixTBase<Element> &m2)
{
   if (!AreCompatible(m1,m2)) {
      //Error("Compare(const TMatrixTBase<Element> &,const TMatrixTBase<Element> &)","matrices are incompatible");
      return;
   }

   printf("\n\nComparison of two TMatrices:\n");

   Element norm1  = 0;      // Norm of the Matrices
   Element norm2  = 0;
   Element ndiff  = 0;      // Norm of the difference
   Int_t   imax   = 0;      // For the elements that differ most
   Int_t   jmax   = 0;
   Element difmax = -1;

   for (Int_t i = m1.GetRowLwb(); i <= m1.GetRowUpb(); i++) {
      for (Int_t j = m1.GetColLwb(); j < m1.GetColUpb(); j++) {
         const Element mv1 = m1(i,j);
         const Element mv2 = m2(i,j);
         const Element diff = TMath::Abs(mv1-mv2);

         if (diff > difmax) {
            difmax = diff;
            imax = i;
            jmax = j;
         }
         norm1 += TMath::Abs(mv1);
         norm2 += TMath::Abs(mv2);
         ndiff += TMath::Abs(diff);
      }
   }

   printf("\nMaximal discrepancy    \t\t%g", difmax);
   printf("\n   occured at the point\t\t(%d,%d)",imax,jmax);
   const Element mv1 = m1(imax,jmax);
   const Element mv2 = m2(imax,jmax);
   printf("\n Matrix 1 element is    \t\t%g", mv1);
   printf("\n Matrix 2 element is    \t\t%g", mv2);
   printf("\n Absolute error v2[i]-v1[i]\t\t%g", mv2-mv1);
   printf("\n Relative error\t\t\t\t%g\n",
          (mv2-mv1)/TMath::Max(TMath::Abs(mv2+mv1)/2,(Element)1e-7));

   printf("\n||Matrix 1||   \t\t\t%g", norm1);
   printf("\n||Matrix 2||   \t\t\t%g", norm2);
   printf("\n||Matrix1-Matrix2||\t\t\t\t%g", ndiff);
   printf("\n||Matrix1-Matrix2||/sqrt(||Matrix1|| ||Matrix2||)\t%g\n\n",
          ndiff/TMath::Max(TMath::Sqrt(norm1*norm2),1e-7));
}

////////////////////////////////////////////////////////////////////////////////
/// Validate that all elements of matrix have value val within maxDevAllow.

template<class Element>
Bool_t VerifyMatrixValue(const TMatrixTBase<Element> &m,Element val,Int_t verbose,Element maxDevAllow)
{
   //R__ASSERT(m.IsValid());

   if (m == 0)
      return kTRUE;

   Int_t   imax      = 0;
   Int_t   jmax      = 0;
   Element maxDevObs = 0;

   if (TMath::Abs(maxDevAllow) <= 0.0)
      maxDevAllow = std::numeric_limits<Element>::epsilon();

   for (Int_t i = m.GetRowLwb(); i <= m.GetRowUpb(); i++) {
      for (Int_t j = m.GetColLwb(); j <= m.GetColUpb(); j++) {
         const Element dev = TMath::Abs(m(i,j)-val);
         if (dev > maxDevObs) {
            imax    = i;
            jmax    = j;
            maxDevObs = dev;
         }
      }
   }

   if (maxDevObs == 0)
      return kTRUE;

   if (verbose) {
      printf("Largest dev for (%d,%d); dev = |%g - %g| = %g\n",imax,jmax,m(imax,jmax),val,maxDevObs);
      if(maxDevObs > maxDevAllow) {}
         //Error("VerifyElementValue","Deviation > %g\n",maxDevAllow);
   }

   if(maxDevObs > maxDevAllow)
      return kFALSE;
   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Verify that elements of the two matrices are equal within MaxDevAllow .

template<class Element>
Bool_t VerifyMatrixIdentity(const TMatrixTBase<Element> &m1,const TMatrixTBase<Element> &m2,Int_t verbose,
                            Element maxDevAllow)
{
   if (!AreCompatible(m1,m2,verbose))
      return kFALSE;

   if (m1 == 0 && m2 == 0)
      return kTRUE;

   Int_t   imax      = 0;
   Int_t   jmax      = 0;
   Element maxDevObs = 0;

   if (TMath::Abs(maxDevAllow) <= 0.0)
      maxDevAllow = std::numeric_limits<Element>::epsilon();

   for (Int_t i = m1.GetRowLwb(); i <= m1.GetRowUpb(); i++) {
      for (Int_t j = m1.GetColLwb(); j <= m1.GetColUpb(); j++) {
         const Element dev = TMath::Abs(m1(i,j)-m2(i,j));
         if (dev > maxDevObs) {
            imax = i;
            jmax = j;
            maxDevObs = dev;
         }
      }
   }

   if (maxDevObs == 0)
      return kTRUE;

   if (verbose) {
      printf("Largest dev for (%d,%d); dev = |%g - %g| = %g\n",
              imax,jmax,m1(imax,jmax),m2(imax,jmax),maxDevObs);
      if (maxDevObs > maxDevAllow) {}
         //Error("VerifyMatrixValue","Deviation > %g\n",maxDevAllow);
   }

   if (maxDevObs > maxDevAllow)
      return kFALSE;
   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Stream an object of class TMatrixTBase<Element>.
/*
template<class Element>
void TMatrixTBase<Element>::Streamer(TBuffer &R__b)
{
   if (R__b.IsReading()) {
      UInt_t R__s, R__c;
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c);
      if (R__v > 1) {
         R__b.ReadClassBuffer(TMatrixTBase<Element>::Class(),this,R__v,R__s,R__c);
      } else {
         //Error("TMatrixTBase<Element>::Streamer","Unknown version number: %d",R__v);
         //R__ASSERT(0);
      }
      if (R__v < 4) MakeValid();
   } else {
      R__b.WriteClassBuffer(TMatrixTBase<Element>::Class(),this);
   }
}
*/
// trick to return a reference to nan in operator(i,j_ when i,j are outside of range
template<class Element>
struct nan_value_t {
   static Element gNanValue;
};
template<>
Double_t nan_value_t<Double_t>::gNanValue = std::numeric_limits<Double_t>::quiet_NaN();
template<>
Float_t nan_value_t<Float_t>::gNanValue = std::numeric_limits<Float_t>::quiet_NaN();

template<class Element>
Element & TMatrixTBase<Element>::NaNValue()
{
   return nan_value_t<Element>::gNanValue;
}


template class TMatrixTBase<Float_t>;

template Bool_t   operator==          <Float_t>(const TMatrixFBase &m1,const TMatrixFBase &m2);
template Float_t  E2Norm              <Float_t>(const TMatrixFBase &m1,const TMatrixFBase &m2);
template Bool_t   AreCompatible<Float_t,Float_t>
                                               (const TMatrixFBase &m1,const TMatrixFBase &m2,Int_t verbose);
template Bool_t   AreCompatible<Float_t,Double_t>
                                               (const TMatrixFBase &m1,const TMatrixDBase &m2,Int_t verbose);
template void     Compare             <Float_t>(const TMatrixFBase &m1,const TMatrixFBase &m2);
template Bool_t   VerifyMatrixValue   <Float_t>(const TMatrixFBase &m,Float_t val,Int_t verbose,Float_t maxDevAllow);
template Bool_t   VerifyMatrixValue   <Float_t>(const TMatrixFBase &m,Float_t val);
template Bool_t   VerifyMatrixIdentity<Float_t>(const TMatrixFBase &m1,const TMatrixFBase &m2,
                                                Int_t verbose,Float_t maxDevAllowN);
template Bool_t   VerifyMatrixIdentity<Float_t>(const TMatrixFBase &m1,const TMatrixFBase &m2);

template class TMatrixTBase<Double_t>;

template Bool_t   operator==          <Double_t>(const TMatrixDBase &m1,const TMatrixDBase &m2);
template Double_t E2Norm              <Double_t>(const TMatrixDBase &m1,const TMatrixDBase &m2);
template Bool_t   AreCompatible<Double_t,Double_t>
                                               (const TMatrixDBase &m1,const TMatrixDBase &m2,Int_t verbose);
template Bool_t   AreCompatible<Double_t,Float_t>
                                               (const TMatrixDBase &m1,const TMatrixFBase &m2,Int_t verbose);
template void     Compare             <Double_t>(const TMatrixDBase &m1,const TMatrixDBase &m2);
template Bool_t   VerifyMatrixValue   <Double_t>(const TMatrixDBase &m,Double_t val,Int_t verbose,Double_t maxDevAllow);
template Bool_t   VerifyMatrixValue   <Double_t>(const TMatrixDBase &m,Double_t val);
template Bool_t   VerifyMatrixIdentity<Double_t>(const TMatrixDBase &m1,const TMatrixDBase &m2,
                                                 Int_t verbose,Double_t maxDevAllow);
template Bool_t   VerifyMatrixIdentity<Double_t>(const TMatrixDBase &m1,const TMatrixDBase &m2);

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixT
    \ingroup Matrix

 TMatrixT

 Template class of a general matrix in the linear algebra package
*/

#include <iostream>
#include <typeinfo>

//#include "TMatrixT.h"
//#include "TBuffer.h"
//#include "TMatrixTSym.h"
//#include "TMatrixTLazy.h"
//#include "TMatrixTCramerInv.h"
//#include "TDecompLU.h"
//#include "TMatrixDEigen.h"
//#include "TClass.h"
//#include "TMath.h"

templateClassImp(TMatrixT);

////////////////////////////////////////////////////////////////////////////////
/// Constructor for (nrows x ncols) matrix

template<class Element>
TMatrixT<Element>::TMatrixT(Int_t nrows,Int_t ncols)
{
   Allocate(nrows,ncols,0,0,1);
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor for ([row_lwb..row_upb] x [col_lwb..col_upb]) matrix

template<class Element>
TMatrixT<Element>::TMatrixT(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb)
{
   Allocate(row_upb-row_lwb+1,col_upb-col_lwb+1,row_lwb,col_lwb,1);
}

////////////////////////////////////////////////////////////////////////////////
/// option="F": array elements contains the matrix stored column-wise
///             like in Fortran, so a[i,j] = elements[i+no_rows*j],
/// else        it is supposed that array elements are stored row-wise
///             a[i,j] = elements[i*no_cols+j]
///
/// array elements are copied

template<class Element>
TMatrixT<Element>::TMatrixT(Int_t no_rows,Int_t no_cols,const Element *elements,Option_t *option)
{
   Allocate(no_rows,no_cols);
   TMatrixTBase<Element>::SetMatrixArray(elements,option);
}

////////////////////////////////////////////////////////////////////////////////
/// array elements are copied

template<class Element>
TMatrixT<Element>::TMatrixT(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                            const Element *elements,Option_t *option)
{
   Allocate(row_upb-row_lwb+1,col_upb-col_lwb+1,row_lwb,col_lwb);
   TMatrixTBase<Element>::SetMatrixArray(elements,option);
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixT<Element> &another) : TMatrixTBase<Element>(another)
{
   //R__ASSERT(another.IsValid());
   Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb());
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor of a symmetric matrix

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixTSym<Element> &another)
{
   //R__ASSERT(another.IsValid());
   Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb());
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor of a sparse matrix

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixTSparse<Element> &another)
{
   //R__ASSERT(another.IsValid());
   Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb());
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor of matrix applying a specific operation to the prototype.
/// Example: TMatrixT<Element> a(10,12); ...; TMatrixT<Element> b(TMatrixT::kTransposed, a);
/// Supported operations are: kZero, kUnit, kTransposed, kInverted and kAtA.

template<class Element>
TMatrixT<Element>::TMatrixT(EMatrixCreatorsOp1 op,const TMatrixT<Element> &prototype)
{
   //R__ASSERT(prototype.IsValid());

   switch(op) {
      case kZero:
         Allocate(prototype.GetNrows(),prototype.GetNcols(),
                  prototype.GetRowLwb(),prototype.GetColLwb(),1);
         break;

      case kUnit:
         Allocate(prototype.GetNrows(),prototype.GetNcols(),
                  prototype.GetRowLwb(),prototype.GetColLwb(),1);
         this->UnitMatrix();
         break;

      case kTransposed:
         Allocate(prototype.GetNcols(), prototype.GetNrows(),
                  prototype.GetColLwb(),prototype.GetRowLwb());
         Transpose(prototype);
         break;

      case kInverted:
      {
         Allocate(prototype.GetNrows(),prototype.GetNcols(),
                  prototype.GetRowLwb(),prototype.GetColLwb(),1);
         *this = prototype;
         // Since the user can not control the tolerance of this newly created matrix
         // we put it to the smallest possible number
         const Element oldTol = this->SetTol(std::numeric_limits<Element>::min());
         this->Invert();
         this->SetTol(oldTol);
         break;
      }

      case kAtA:
         Allocate(prototype.GetNcols(),prototype.GetNcols(),prototype.GetColLwb(),prototype.GetColLwb(),1);
         TMult(prototype,prototype);
         break;

      default:
         //Error("TMatrixT(EMatrixCreatorOp1)", "operation %d not yet implemented", op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor of matrix applying a specific operation to two prototypes.
/// Example: TMatrixT<Element> a(10,12), b(12,5); ...; TMatrixT<Element> c(a, TMatrixT::kMult, b);
/// Supported operations are: kMult (a*b), kTransposeMult (a'*b), kInvMult (a^(-1)*b)

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixT<Element> &a,EMatrixCreatorsOp2 op,const TMatrixT<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kMult:
         Allocate(a.GetNrows(),b.GetNcols(),a.GetRowLwb(),b.GetColLwb(),1);
         Mult(a,b);
         break;

      case kTransposeMult:
         Allocate(a.GetNcols(),b.GetNcols(),a.GetColLwb(),b.GetColLwb(),1);
         TMult(a,b);
         break;

      case kMultTranspose:
         Allocate(a.GetNrows(),b.GetNrows(),a.GetRowLwb(),b.GetRowLwb(),1);
         MultT(a,b);
         break;

      case kInvMult:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         *this = a;
         const Element oldTol = this->SetTol(std::numeric_limits<Element>::min());
         this->Invert();
         this->SetTol(oldTol);
         *this *= b;
         break;
      }

      case kPlus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Plus(a,b);
         break;
      }

      case kMinus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Minus(a,b);
         break;
      }

      default:
         //Error("TMatrixT(EMatrixCreatorOp2)", "operation %d not yet implemented", op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor of matrix applying a specific operation to two prototypes.
/// Example: TMatrixT<Element> a(10,12), b(12,5); ...; TMatrixT<Element> c(a, TMatrixT::kMult, b);
/// Supported operations are: kMult (a*b), kTransposeMult (a'*b), kInvMult (a^(-1)*b)

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixT<Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSym<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kMult:
         Allocate(a.GetNrows(),b.GetNcols(),a.GetRowLwb(),b.GetColLwb(),1);
         Mult(a,b);
         break;

      case kTransposeMult:
         Allocate(a.GetNcols(),b.GetNcols(),a.GetColLwb(),b.GetColLwb(),1);
         TMult(a,b);
         break;

      case kMultTranspose:
         Allocate(a.GetNrows(),b.GetNrows(),a.GetRowLwb(),b.GetRowLwb(),1);
         MultT(a,b);
         break;

      case kInvMult:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         *this = a;
         const Element oldTol = this->SetTol(std::numeric_limits<Element>::min());
         this->Invert();
         this->SetTol(oldTol);
         *this *= b;
         break;
      }

      case kPlus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Plus(a,b);
         break;
      }

      case kMinus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Minus(a,b);
         break;
      }

      default:
         //Error("TMatrixT(EMatrixCreatorOp2)", "operation %d not yet implemented", op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor of matrix applying a specific operation to two prototypes.
/// Example: TMatrixT<Element> a(10,12), b(12,5); ...; TMatrixT<Element> c(a, TMatrixT::kMult, b);
/// Supported operations are: kMult (a*b), kTransposeMult (a'*b), kInvMult (a^(-1)*b)

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixTSym<Element> &a,EMatrixCreatorsOp2 op,const TMatrixT<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kMult:
         Allocate(a.GetNrows(),b.GetNcols(),a.GetRowLwb(),b.GetColLwb(),1);
         Mult(a,b);
         break;

      case kTransposeMult:
         Allocate(a.GetNcols(),b.GetNcols(),a.GetColLwb(),b.GetColLwb(),1);
         TMult(a,b);
         break;

      case kMultTranspose:
         Allocate(a.GetNrows(),b.GetNrows(),a.GetRowLwb(),b.GetRowLwb(),1);
         MultT(a,b);
         break;

      case kInvMult:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         *this = a;
         const Element oldTol = this->SetTol(std::numeric_limits<Element>::min());
         this->Invert();
         this->SetTol(oldTol);
         *this *= b;
         break;
      }

      case kPlus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Plus(a,b);
         break;
      }

      case kMinus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Minus(a,b);
         break;
      }

      default:
         //Error("TMatrixT(EMatrixCreatorOp2)", "operation %d not yet implemented", op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor of matrix applying a specific operation to two prototypes.
/// Example: TMatrixT<Element> a(10,12), b(12,5); ...; TMatrixT<Element> c(a, TMatrixT::kMult, b);
/// Supported operations are: kMult (a*b), kTransposeMult (a'*b), kInvMult (a^(-1)*b)

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixTSym<Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSym<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kMult:
         Allocate(a.GetNrows(),b.GetNcols(),a.GetRowLwb(),b.GetColLwb(),1);
         Mult(a,b);
         break;

      case kTransposeMult:
         Allocate(a.GetNcols(),b.GetNcols(),a.GetColLwb(),b.GetColLwb(),1);
         TMult(a,b);
         break;

      case kMultTranspose:
         Allocate(a.GetNrows(),b.GetNrows(),a.GetRowLwb(),b.GetRowLwb(),1);
         MultT(a,b);
         break;

      case kInvMult:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         *this = a;
         const Element oldTol = this->SetTol(std::numeric_limits<Element>::min());
         this->Invert();
         this->SetTol(oldTol);
         *this *= b;
         break;
      }

      case kPlus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Plus(*dynamic_cast<const TMatrixT<Element> *>(&a),b);
         break;
      }

      case kMinus:
      {
         Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb(),1);
         Minus(*dynamic_cast<const TMatrixT<Element> *>(&a),b);
         break;
      }

      default:
         //Error("TMatrixT(EMatrixCreatorOp2)", "operation %d not yet implemented", op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor using the TMatrixTLazy class

template<class Element>
TMatrixT<Element>::TMatrixT(const TMatrixTLazy<Element> &lazy_constructor)
{
   Allocate(lazy_constructor.GetRowUpb()-lazy_constructor.GetRowLwb()+1,
            lazy_constructor.GetColUpb()-lazy_constructor.GetColLwb()+1,
            lazy_constructor.GetRowLwb(),lazy_constructor.GetColLwb(),1);
   lazy_constructor.FillIn(*this);
}

////////////////////////////////////////////////////////////////////////////////
/// Delete data pointer m, if it was assigned on the heap

template<class Element>
void TMatrixT<Element>::Delete_m(Int_t size,Element *&m)
{
   if (m) {
      if (size > this->kSizeMax)
         delete [] m;
      m = 0;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Return data pointer . if requested size <= kSizeMax, assign pointer
/// to the stack space

template<class Element>
Element* TMatrixT<Element>::New_m(Int_t size)
{
   if (size == 0) return 0;
   else {
      if ( size <= this->kSizeMax )
         return fDataStack;
      else {
         Element *heap = new Element[size];
         return heap;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Copy copySize doubles from *oldp to *newp . However take care of the
/// situation where both pointers are assigned to the same stack space

template<class Element>
Int_t TMatrixT<Element>::Memcpy_m(Element *newp,const Element *oldp,Int_t copySize,
                                  Int_t newSize,Int_t oldSize)
{
   if (copySize == 0 || oldp == newp)
      return 0;
   else {
      if ( newSize <= this->kSizeMax && oldSize <= this->kSizeMax ) {
         // both pointers are inside fDataStack, be careful with copy direction !
         if (newp > oldp) {
            for (Int_t i = copySize-1; i >= 0; i--)
               newp[i] = oldp[i];
         } else {
            for (Int_t i = 0; i < copySize; i++)
               newp[i] = oldp[i];
         }
      }
      else
         memcpy(newp,oldp,copySize*sizeof(Element));
   }
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Allocate new matrix. Arguments are number of rows, columns, row
/// lowerbound (0 default) and column lowerbound (0 default).

template<class Element>
void TMatrixT<Element>::Allocate(Int_t no_rows,Int_t no_cols,Int_t row_lwb,Int_t col_lwb,
                                 Int_t init,Int_t /*nr_nonzeros*/)
{
   this->fIsOwner = kTRUE;
   this->fTol     = std::numeric_limits<Element>::epsilon();
   fElements      = 0;
   this->fNrows   = 0;
   this->fNcols   = 0;
   this->fRowLwb  = 0;
   this->fColLwb  = 0;
   this->fNelems  = 0;

   if (no_rows < 0 || no_cols < 0)
   {
      //Error("Allocate","no_rows=%d no_cols=%d",no_rows,no_cols);
      //this->Invalidate();
      return;
   }

   //this->MakeValid();
   this->fNrows   = no_rows;
   this->fNcols   = no_cols;
   this->fRowLwb  = row_lwb;
   this->fColLwb  = col_lwb;
   this->fNelems  = this->fNrows*this->fNcols;

   // Check if fNelems does not have an overflow.
   if( ((Long64_t)this->fNrows)*this->fNcols != this->fNelems )
   {
      //Error("Allocate","too large: no_rows=%d no_cols=%d",no_rows,no_cols);
      //this->Invalidate();
      return;
   }

   if (this->fNelems > 0) {
      fElements = New_m(this->fNelems);
      if (init)
         memset(fElements,0,this->fNelems*sizeof(Element));
   } else
     fElements = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix summation. Create a matrix C such that C = A + B.

template<class Element>
void TMatrixT<Element>::Plus(const TMatrixT<Element> &a,const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      if (!AreCompatible(a,b)) {
         //Error("Plus","matrices not compatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Plus","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Plus","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

   const Element *       ap      = a.GetMatrixArray();
   const Element *       bp      = b.GetMatrixArray();
         Element *       cp      = this->GetMatrixArray();
   const Element * const cp_last = cp+this->fNelems;

   while (cp < cp_last) {
       *cp = *ap++ + *bp++;
       cp++;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix summation. Create a matrix C such that C = A + B.

template<class Element>
void TMatrixT<Element>::Plus(const TMatrixT<Element> &a,const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      if (!AreCompatible(a,b)) {
         //Error("Plus","matrices not compatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Plus","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Plus","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

   const Element *       ap      = a.GetMatrixArray();
   const Element *       bp      = b.GetMatrixArray();
         Element *       cp      = this->GetMatrixArray();
   const Element * const cp_last = cp+this->fNelems;

   while (cp < cp_last) {
       *cp = *ap++ + *bp++;
       cp++;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix summation. Create a matrix C such that C = A - B.

template<class Element>
void TMatrixT<Element>::Minus(const TMatrixT<Element> &a,const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      if (!AreCompatible(a,b)) {
         //Error("Minus","matrices not compatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Minus","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Minus","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

   const Element *       ap      = a.GetMatrixArray();
   const Element *       bp      = b.GetMatrixArray();
         Element *       cp      = this->GetMatrixArray();
   const Element * const cp_last = cp+this->fNelems;

   while (cp < cp_last) {
      *cp = *ap++ - *bp++;
      cp++;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix summation. Create a matrix C such that C = A - B.

template<class Element>
void TMatrixT<Element>::Minus(const TMatrixT<Element> &a,const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      if (!AreCompatible(a,b)) {
         //Error("Minus","matrices not compatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Minus","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Minus","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

   const Element *       ap      = a.GetMatrixArray();
   const Element *       bp      = b.GetMatrixArray();
         Element *       cp      = this->GetMatrixArray();
   const Element * const cp_last = cp+this->fNelems;

   while (cp < cp_last) {
       *cp = *ap++ - *bp++;
       cp++;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix multiplication. Create a matrix C such that C = A * B.

template<class Element>
void TMatrixT<Element>::Mult(const TMatrixT<Element> &a,const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      if (a.GetNcols() != b.GetNrows() || a.GetColLwb() != b.GetRowLwb()) {
         //Error("Mult","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasNoTrans,CblasNoTrans,fNrows,fNcols,a.GetNcols(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasNoTrans,CblasNoTrans,fNrows,fNcols,a.GetNcols(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   //else
      //Error("Mult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t na     = a.GetNoElements();
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AMultB(ap,na,ncolsa,bp,nb,ncolsb,cp);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix multiplication, with A symmetric and B general.
/// Create a matrix C such that C = A * B.

template<class Element>
void TMatrixT<Element>::Mult(const TMatrixTSym<Element> &a,const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());
      if (a.GetNcols() != b.GetNrows() || a.GetColLwb() != b.GetRowLwb()) {
         //Error("Mult","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymm (CblasRowMajor,CblasLeft,CblasUpper,fNrows,fNcols,1.0,
                   ap,a.GetNcols(),bp,b.GetNcols(),0.0,cp,fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymm (CblasRowMajor,CblasLeft,CblasUpper,fNrows,fNcols,1.0,
                   ap,a.GetNcols(),bp,b.GetNcols(),0.0,cp,fNcols);
   //else
      //Error("Mult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t na     = a.GetNoElements();
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AMultB(ap,na,ncolsa,bp,nb,ncolsb,cp);

#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix multiplication, with A general and B symmetric.
/// Create a matrix C such that C = A * B.

template<class Element>
void TMatrixT<Element>::Mult(const TMatrixT<Element> &a,const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());
      if (a.GetNcols() != b.GetNrows() || a.GetColLwb() != b.GetRowLwb()) {
         //Error("Mult","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymm (CblasRowMajor,CblasRight,CblasUpper,fNrows,fNcols,1.0,
                   bp,b.GetNcols(),ap,a.GetNcols(),0.0,cp,fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymm (CblasRowMajor,CblasRight,CblasUpper,fNrows,fNcols,1.0,
                   bp,b.GetNcols(),ap,a.GetNcols(),0.0,cp,fNcols);
   //else
      //Error("Mult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t na     = a.GetNoElements();
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AMultB(ap,na,ncolsa,bp,nb,ncolsb,cp);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix multiplication, with A symmetric and B symmetric.
/// (Actually copied for the moment routine for B general)
/// Create a matrix C such that C = A * B.

template<class Element>
void TMatrixT<Element>::Mult(const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());
      if (a.GetNcols() != b.GetNrows() || a.GetColLwb() != b.GetRowLwb()) {
         //Error("Mult","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Mult","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymm (CblasRowMajor,CblasLeft,CblasUpper,fNrows,fNcols,1.0,
                   ap,a.GetNcols(),bp,b.GetNcols(),0.0,cp,fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymm (CblasRowMajor,CblasLeft,CblasUpper,fNrows,fNcols,1.0,
                   ap,a.GetNcols(),bp,b.GetNcols(),0.0,cp,fNcols);
   //else
      //Error("Mult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t na     = a.GetNoElements();
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AMultB(ap,na,ncolsa,bp,nb,ncolsb,cp);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix C such that C = A' * B. In other words,
/// c[i,j] = SUM{ a[k,i] * b[k,j] }.

template<class Element>
void TMatrixT<Element>::TMult(const TMatrixT<Element> &a,const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());
      if (a.GetNrows() != b.GetNrows() || a.GetRowLwb() != b.GetRowLwb()) {
         //Error("TMult","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("TMult","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("TMult","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasTrans,CblasNoTrans,this->fNrows,this->fNcols,a.GetNrows(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,this->fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasTrans,CblasNoTrans,fNrows,fNcols,a.GetNrows(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   //else
      //Error("TMult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AtMultB(ap,ncolsa,bp,nb,ncolsb,cp);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix C such that C = A' * B. In other words,
/// c[i,j] = SUM{ a[k,i] * b[k,j] }.

template<class Element>
void TMatrixT<Element>::TMult(const TMatrixT<Element> &a,const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());
      if (a.GetNrows() != b.GetNrows() || a.GetRowLwb() != b.GetRowLwb()) {
         //Error("TMult","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("TMult","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("TMult","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasTrans,CblasNoTrans,fNrows,fNcols,a.GetNrows(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasTrans,CblasNoTrans,fNrows,fNcols,a.GetNrows(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   //else
      //Error("TMult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AtMultB(ap,ncolsa,bp,nb,ncolsb,cp);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix multiplication. Create a matrix C such that C = A * B^T.

template<class Element>
void TMatrixT<Element>::MultT(const TMatrixT<Element> &a,const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNcols() != b.GetNcols() || a.GetColLwb() != b.GetColLwb()) {
         //Error("MultT","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("MultT","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("MultT","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasNoTrans,CblasTrans,fNrows,fNcols,a.GetNcols(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasNoTrans,CblasTrans,fNrows,fNcols,a.GetNcols(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   //else
      //Error("MultT","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t na     = a.GetNoElements();
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AMultBt(ap,na,ncolsa,bp,nb,ncolsb,cp);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix multiplication, with A symmetric and B general.
/// Create a matrix C such that C = A * B^T.

template<class Element>
void TMatrixT<Element>::MultT(const TMatrixTSym<Element> &a,const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());
      if (a.GetNcols() != b.GetNcols() || a.GetColLwb() != b.GetColLwb()) {
         //Error("MultT","A rows and B columns incompatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("MultT","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("MultT","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasNoTrans,CblasTrans,this->fNrows,this->fNcols,a.GetNcols(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,this->fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasNoTrans,CblasTrans,fNrows,fNcols,a.GetNcols(),
                   1.0,ap,a.GetNcols(),bp,b.GetNcols(),1.0,cp,fNcols);
   //else
      //Error("MultT","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t na     = a.GetNoElements();
   const Int_t nb     = b.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = b.GetNcols();
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = b.GetMatrixArray();
         Element *       cp = this->GetMatrixArray();

   AMultBt(ap,na,ncolsa,bp,nb,ncolsb,cp);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Use the array data to fill the matrix ([row_lwb..row_upb] x [col_lwb..col_upb])

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::Use(Int_t row_lwb,Int_t row_upb,
                                          Int_t col_lwb,Int_t col_upb,Element *data)
{
   if (gMatrixCheck) {
      if (row_upb < row_lwb)
      {
         //Error("Use","row_upb=%d < row_lwb=%d",row_upb,row_lwb);
         return *this;
      }
      if (col_upb < col_lwb)
      {
         //Error("Use","col_upb=%d < col_lwb=%d",col_upb,col_lwb);
         return *this;
      }
   }

   Clear();
   this->fNrows    = row_upb-row_lwb+1;
   this->fNcols    = col_upb-col_lwb+1;
   this->fRowLwb   = row_lwb;
   this->fColLwb   = col_lwb;
   this->fNelems   = this->fNrows*this->fNcols;
         fElements = data;
   this->fIsOwner  = kFALSE;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Get submatrix [row_lwb..row_upb] x [col_lwb..col_upb]; The indexing range of the
/// returned matrix depends on the argument option:
///
/// option == "S" : return [0..row_upb-row_lwb][0..col_upb-col_lwb] (default)
/// else          : return [row_lwb..row_upb][col_lwb..col_upb]

template<class Element>
TMatrixTBase<Element> &TMatrixT<Element>::GetSub(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                 TMatrixTBase<Element> &target,Option_t *option) const
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_lwb out of bounds");
         return target;
      }
      if (col_lwb < this->fColLwb || col_lwb > this->fColLwb+this->fNcols-1) {
         //Error("GetSub","col_lwb out of bounds");
         return target;
      }
      if (row_upb < this->fRowLwb || row_upb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_upb out of bounds");
         return target;
      }
      if (col_upb < this->fColLwb || col_upb > this->fColLwb+this->fNcols-1) {
         //Error("GetSub","col_upb out of bounds");
         return target;
      }
      if (row_upb < row_lwb || col_upb < col_lwb) {
         //Error("GetSub","row_upb < row_lwb || col_upb < col_lwb");
         return target;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t shift = (opt.Contains("S")) ? 1 : 0;

   const Int_t row_lwb_sub = (shift) ? 0               : row_lwb;
   const Int_t row_upb_sub = (shift) ? row_upb-row_lwb : row_upb;
   const Int_t col_lwb_sub = (shift) ? 0               : col_lwb;
   const Int_t col_upb_sub = (shift) ? col_upb-col_lwb : col_upb;

   target.ResizeTo(row_lwb_sub,row_upb_sub,col_lwb_sub,col_upb_sub);
   const Int_t nrows_sub = row_upb_sub-row_lwb_sub+1;
   const Int_t ncols_sub = col_upb_sub-col_lwb_sub+1;

   if (target.GetRowIndexArray() && target.GetColIndexArray()) {
      for (Int_t irow = 0; irow < nrows_sub; irow++) {
         for (Int_t icol = 0; icol < ncols_sub; icol++) {
            target(irow+row_lwb_sub,icol+col_lwb_sub) = (*this)(row_lwb+irow,col_lwb+icol);
         }
      }
   } else {
      const Element *ap = this->GetMatrixArray()+(row_lwb-this->fRowLwb)*this->fNcols+(col_lwb-this->fColLwb);
            Element *bp = target.GetMatrixArray();

      for (Int_t irow = 0; irow < nrows_sub; irow++) {
         const Element *ap_sub = ap;
         for (Int_t icol = 0; icol < ncols_sub; icol++) {
            *bp++ = *ap_sub++;
         }
         ap += this->fNcols;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Insert matrix source starting at [row_lwb][col_lwb], thereby overwriting the part
/// [row_lwb..row_lwb+nrows_source][col_lwb..col_lwb+ncols_source];

template<class Element>
TMatrixTBase<Element> &TMatrixT<Element>::SetSub(Int_t row_lwb,Int_t col_lwb,const TMatrixTBase<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());

      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("SetSub","row_lwb outof bounds");
         return *this;
      }
      if (col_lwb < this->fColLwb || col_lwb > this->fColLwb+this->fNcols-1) {
         //Error("SetSub","col_lwb outof bounds");
         return *this;
      }
      if (row_lwb+source.GetNrows() > this->fRowLwb+this->fNrows ||
            col_lwb+source.GetNcols() > this->fColLwb+this->fNcols) {
         //Error("SetSub","source matrix too large");
         return *this;
      }
   }

   const Int_t nRows_source = source.GetNrows();
   const Int_t nCols_source = source.GetNcols();

   if (source.GetRowIndexArray() && source.GetColIndexArray()) {
      const Int_t rowlwb_s = source.GetRowLwb();
      const Int_t collwb_s = source.GetColLwb();
      for (Int_t irow = 0; irow < nRows_source; irow++) {
         for (Int_t icol = 0; icol < nCols_source; icol++) {
            (*this)(row_lwb+irow,col_lwb+icol) = source(rowlwb_s+irow,collwb_s+icol);
         }
      }
   } else {
      const Element *bp = source.GetMatrixArray();
            Element *ap = this->GetMatrixArray()+(row_lwb-this->fRowLwb)*this->fNcols+(col_lwb-this->fColLwb);

      for (Int_t irow = 0; irow < nRows_source; irow++) {
         Element *ap_sub = ap;
         for (Int_t icol = 0; icol < nCols_source; icol++) {
            *ap_sub++ = *bp++;
         }
         ap += this->fNcols;
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set size of the matrix to nrows x ncols
/// New dynamic elements are created, the overlapping part of the old ones are
/// copied to the new structures, then the old elements are deleted.

template<class Element>
TMatrixTBase<Element> &TMatrixT<Element>::ResizeTo(Int_t nrows,Int_t ncols,Int_t /*nr_nonzeros*/)
{
   //R__ASSERT(this->IsValid());
   if (!this->fIsOwner) {
      //Error("ResizeTo(Int_t,Int_t)","Not owner of data array,cannot resize");
      return *this;
   }

   if (this->fNelems > 0) {
      if (this->fNrows == nrows && this->fNcols == ncols)
         return *this;
      else if (nrows == 0 || ncols == 0) {
         this->fNrows = nrows; this->fNcols = ncols;
         Clear();
         return *this;
      }

      Element    *elements_old = GetMatrixArray();
      const Int_t nelems_old   = this->fNelems;
      const Int_t nrows_old    = this->fNrows;
      const Int_t ncols_old    = this->fNcols;

      Allocate(nrows,ncols);
      //R__ASSERT(this->IsValid());

      Element *elements_new = GetMatrixArray();
      // new memory should be initialized but be careful not to wipe out the stack
      // storage. Initialize all when old or new storage was on the heap
      if (this->fNelems > this->kSizeMax || nelems_old > this->kSizeMax)
         memset(elements_new,0,this->fNelems*sizeof(Element));
      else if (this->fNelems > nelems_old)
         memset(elements_new+nelems_old,0,(this->fNelems-nelems_old)*sizeof(Element));

      // Copy overlap
      const Int_t ncols_copy = TMath::Min(this->fNcols,ncols_old);
      const Int_t nrows_copy = TMath::Min(this->fNrows,nrows_old);

      const Int_t nelems_new = this->fNelems;
      if (ncols_old < this->fNcols) {
         for (Int_t i = nrows_copy-1; i >= 0; i--) {
            Memcpy_m(elements_new+i*this->fNcols,elements_old+i*ncols_old,ncols_copy,
                     nelems_new,nelems_old);
            if (this->fNelems <= this->kSizeMax && nelems_old <= this->kSizeMax)
               memset(elements_new+i*this->fNcols+ncols_copy,0,(this->fNcols-ncols_copy)*sizeof(Element));
         }
      } else {
         for (Int_t i = 0; i < nrows_copy; i++)
            Memcpy_m(elements_new+i*this->fNcols,elements_old+i*ncols_old,ncols_copy,
                     nelems_new,nelems_old);
      }

      Delete_m(nelems_old,elements_old);
   } else {
      Allocate(nrows,ncols,0,0,1);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set size of the matrix to [row_lwb:row_upb] x [col_lwb:col_upb]
/// New dynamic elemenst are created, the overlapping part of the old ones are
/// copied to the new structures, then the old elements are deleted.

template<class Element>
TMatrixTBase<Element> &TMatrixT<Element>::ResizeTo(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                   Int_t /*nr_nonzeros*/)
{
   //R__ASSERT(this->IsValid());
   if (!this->fIsOwner) {
      //Error("ResizeTo(Int_t,Int_t,Int_t,Int_t)","Not owner of data array,cannot resize");
      return *this;
   }

   const Int_t new_nrows = row_upb-row_lwb+1;
   const Int_t new_ncols = col_upb-col_lwb+1;

   if (this->fNelems > 0) {

      if (this->fNrows  == new_nrows  && this->fNcols  == new_ncols &&
           this->fRowLwb == row_lwb    && this->fColLwb == col_lwb)
          return *this;
      else if (new_nrows == 0 || new_ncols == 0) {
         this->fNrows = new_nrows; this->fNcols = new_ncols;
         this->fRowLwb = row_lwb; this->fColLwb = col_lwb;
         Clear();
         return *this;
      }

      Element    *elements_old = GetMatrixArray();
      const Int_t nelems_old   = this->fNelems;
      const Int_t nrows_old    = this->fNrows;
      const Int_t ncols_old    = this->fNcols;
      const Int_t rowLwb_old   = this->fRowLwb;
      const Int_t colLwb_old   = this->fColLwb;

      Allocate(new_nrows,new_ncols,row_lwb,col_lwb);
      //R__ASSERT(this->IsValid());

      Element *elements_new = GetMatrixArray();
      // new memory should be initialized but be careful not to wipe out the stack
      // storage. Initialize all when old or new storage was on the heap
      if (this->fNelems > this->kSizeMax || nelems_old > this->kSizeMax)
         memset(elements_new,0,this->fNelems*sizeof(Element));
      else if (this->fNelems > nelems_old)
         memset(elements_new+nelems_old,0,(this->fNelems-nelems_old)*sizeof(Element));

      // Copy overlap
      const Int_t rowLwb_copy = TMath::Max(this->fRowLwb,rowLwb_old);
      const Int_t colLwb_copy = TMath::Max(this->fColLwb,colLwb_old);
      const Int_t rowUpb_copy = TMath::Min(this->fRowLwb+this->fNrows-1,rowLwb_old+nrows_old-1);
      const Int_t colUpb_copy = TMath::Min(this->fColLwb+this->fNcols-1,colLwb_old+ncols_old-1);

      const Int_t nrows_copy = rowUpb_copy-rowLwb_copy+1;
      const Int_t ncols_copy = colUpb_copy-colLwb_copy+1;

      if (nrows_copy > 0 && ncols_copy > 0) {
         const Int_t colOldOff = colLwb_copy-colLwb_old;
         const Int_t colNewOff = colLwb_copy-this->fColLwb;
         if (ncols_old < this->fNcols) {
            for (Int_t i = nrows_copy-1; i >= 0; i--) {
               const Int_t iRowOld = rowLwb_copy+i-rowLwb_old;
               const Int_t iRowNew = rowLwb_copy+i-this->fRowLwb;
               Memcpy_m(elements_new+iRowNew*this->fNcols+colNewOff,
                        elements_old+iRowOld*ncols_old+colOldOff,ncols_copy,this->fNelems,nelems_old);
               if (this->fNelems <= this->kSizeMax && nelems_old <= this->kSizeMax)
                  memset(elements_new+iRowNew*this->fNcols+colNewOff+ncols_copy,0,
                         (this->fNcols-ncols_copy)*sizeof(Element));
            }
         } else {
            for (Int_t i = 0; i < nrows_copy; i++) {
               const Int_t iRowOld = rowLwb_copy+i-rowLwb_old;
               const Int_t iRowNew = rowLwb_copy+i-this->fRowLwb;
               Memcpy_m(elements_new+iRowNew*this->fNcols+colNewOff,
                        elements_old+iRowOld*ncols_old+colOldOff,ncols_copy,this->fNelems,nelems_old);
            }
         }
      }

      Delete_m(nelems_old,elements_old);
   } else {
      Allocate(new_nrows,new_ncols,row_lwb,col_lwb,1);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Return the matrix determinant

template<class Element>
Double_t TMatrixT<Element>::Determinant() const
{
   const TMatrixT<Element> &tmp = *this;
   TDecompLU lu(tmp,this->fTol);
   Double_t d1,d2;
   lu.Det(d1,d2);
   return d1*TMath::Power(2.0,d2);
}

////////////////////////////////////////////////////////////////////////////////
/// Return the matrix determinant as d1,d2 where det = d1*TMath::Power(2.0,d2)

template<class Element>
void TMatrixT<Element>::Determinant(Double_t &d1,Double_t &d2) const
{
   const TMatrixT<Element> &tmp = *this;
   TDecompLU lu(tmp,Double_t(this->fTol));
   lu.Det(d1,d2);
}

////////////////////////////////////////////////////////////////////////////////
/// Invert the matrix and calculate its determinant

template <>
TMatrixT<Double_t> &TMatrixT<Double_t>::Invert(Double_t *det)
{
   //R__ASSERT(this->IsValid());
   TDecompLU::InvertLU(*this, Double_t(fTol), det);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Invert the matrix and calculate its determinant

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::Invert(Double_t *det)
{
   TMatrixD tmp(*this);
   if (TDecompLU::InvertLU(tmp, Double_t(this->fTol),det))
      std::copy(tmp.GetMatrixArray(), tmp.GetMatrixArray() + this->GetNoElements(), this->GetMatrixArray());

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Invert the matrix and calculate its determinant, however upto (6x6)
/// a fast Cramer inversion is used .

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::InvertFast(Double_t *det)
{
   //R__ASSERT(this->IsValid());

   const Char_t nRows = Char_t(this->GetNrows());
   switch (nRows) {
      case 1:
      {
         if (this->GetNrows() != this->GetNcols() || this->GetRowLwb() != this->GetColLwb()) {
             //Error("Invert()","matrix should be square");
         } else {
            Element *pM = this->GetMatrixArray();
            if (*pM == 0.) {
               //Error("InvertFast","matrix is singular");
               *det = 0;
            }
            else {
               *det = *pM;
               *pM = 1.0/(*pM);
            }
         }
         return *this;
      }
      case 2:
      {
         TMatrixTCramerInv::Inv2x2<Element>(*this,det);
         return *this;
      }
      case 3:
      {
         TMatrixTCramerInv::Inv3x3<Element>(*this,det);
         return *this;
      }
      case 4:
      {
         TMatrixTCramerInv::Inv4x4<Element>(*this,det);
         return *this;
      }
      case 5:
      {
         TMatrixTCramerInv::Inv5x5<Element>(*this,det);
         return *this;
      }
      case 6:
      {
         TMatrixTCramerInv::Inv6x6<Element>(*this,det);
         return *this;
      }
      default:
      {
         return Invert(det);
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Transpose matrix source.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::Transpose(const TMatrixT<Element> &source)
{
   //R__ASSERT(this->IsValid());
   //R__ASSERT(source.IsValid());

   if (this->GetMatrixArray() == source.GetMatrixArray()) {
      Element *ap = this->GetMatrixArray();
      if (this->fNrows == this->fNcols && this->fRowLwb == this->fColLwb) {
         for (Int_t i = 0; i < this->fNrows; i++) {
            const Int_t off_i = i*this->fNrows;
            for (Int_t j = i+1; j < this->fNcols; j++) {
               const Int_t off_j = j*this->fNcols;
               const Element tmp = ap[off_i+j];
               ap[off_i+j] = ap[off_j+i];
               ap[off_j+i] = tmp;
            }
         }
      } else {
         Element *oldElems = new Element[source.GetNoElements()];
         memcpy(oldElems,source.GetMatrixArray(),source.GetNoElements()*sizeof(Element));
         const Int_t nrows_old  = this->fNrows;
         const Int_t ncols_old  = this->fNcols;
         const Int_t rowlwb_old = this->fRowLwb;
         const Int_t collwb_old = this->fColLwb;

         this->fNrows  = ncols_old;  this->fNcols  = nrows_old;
         this->fRowLwb = collwb_old; this->fColLwb = rowlwb_old;
         for (Int_t irow = this->fRowLwb; irow < this->fRowLwb+this->fNrows; irow++) {
            for (Int_t icol = this->fColLwb; icol < this->fColLwb+this->fNcols; icol++) {
               const Int_t off = (icol-collwb_old)*ncols_old;
               (*this)(irow,icol) = oldElems[off+irow-rowlwb_old];
            }
         }
         delete [] oldElems;
      }
   } else {
      if (this->fNrows  != source.GetNcols()  || this->fNcols  != source.GetNrows() ||
          this->fRowLwb != source.GetColLwb() || this->fColLwb != source.GetRowLwb())
      {
         //Error("Transpose","matrix has wrong shape");
         return *this;
      }

      const Element *sp1 = source.GetMatrixArray();
      const Element *scp = sp1; // Row source pointer
            Element *tp  = this->GetMatrixArray();
      const Element * const tp_last = this->GetMatrixArray()+this->fNelems;

      // (This: target) matrix is traversed row-wise way,
      // whilst the source matrix is scanned column-wise
      while (tp < tp_last) {
         const Element *sp2 = scp++;

         // Move tp to the next elem in the row and sp to the next elem in the curr col
         while (sp2 < sp1+this->fNelems) {
            *tp++ = *sp2;
            sp2 += this->fNrows;
         }
      }
      //R__ASSERT(tp == tp_last && scp == sp1+this->fNrows);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Perform a rank 1 operation on matrix A:
///     A += alpha * v * v^T

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::Rank1Update(const TVectorT<Element> &v,Element alpha)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(v.IsValid());
      if (v.GetNoElements() < TMath::Max(this->fNrows,this->fNcols)) {
         //Error("Rank1Update","vector too short");
         return *this;
      }
   }

   const Element * const pv = v.GetMatrixArray();
         Element *mp = this->GetMatrixArray();

   for (Int_t i = 0; i < this->fNrows; i++) {
      const Element tmp = alpha*pv[i];
      for (Int_t j = 0; j < this->fNcols; j++)
         *mp++ += tmp*pv[j];
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Perform a rank 1 operation on matrix A:
///     A += alpha * v1 * v2^T

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::Rank1Update(const TVectorT<Element> &v1,const TVectorT<Element> &v2,Element alpha)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(v1.IsValid());
      //R__ASSERT(v2.IsValid());
      if (v1.GetNoElements() < this->fNrows) {
         //Error("Rank1Update","vector v1 too short");
         return *this;
      }

      if (v2.GetNoElements() < this->fNcols) {
         //Error("Rank1Update","vector v2 too short");
         return *this;
      }
   }

   const Element * const pv1 = v1.GetMatrixArray();
   const Element * const pv2 = v2.GetMatrixArray();
         Element *mp = this->GetMatrixArray();

   for (Int_t i = 0; i < this->fNrows; i++) {
      const Element tmp = alpha*pv1[i];
      for (Int_t j = 0; j < this->fNcols; j++)
         *mp++ += tmp*pv2[j];
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate scalar v * (*this) * v^T

template<class Element>
Element TMatrixT<Element>::Similarity(const TVectorT<Element> &v) const
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(v.IsValid());
      if (this->fNcols != this->fNrows || this->fColLwb != this->fRowLwb) {
         //Error("Similarity(const TVectorT &)","matrix is not square");
         return -1.;
      }

      if (this->fNcols != v.GetNrows() || this->fColLwb != v.GetLwb()) {
         //Error("Similarity(const TVectorT &)","vector and matrix incompatible");
         return -1.;
      }
   }

   const Element *mp = this->GetMatrixArray(); // Matrix row ptr
   const Element *vp = v.GetMatrixArray();     // vector ptr

   Element sum1 = 0;
   const Element * const vp_first = vp;
   const Element * const vp_last  = vp+v.GetNrows();
   while (vp < vp_last) {
      Element sum2 = 0;
      for (const Element *sp = vp_first; sp < vp_last; )
         sum2 += *mp++ * *sp++;
      sum1 += sum2 * *vp++;
   }

   //R__ASSERT(mp == this->GetMatrixArray()+this->GetNoElements());

   return sum1;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply/divide matrix columns by a vector:
/// option:
/// "D"   :  b(i,j) = a(i,j)/v(i)   i = 0,fNrows-1 (default)
/// else  :  b(i,j) = a(i,j)*v(i)

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::NormByColumn(const TVectorT<Element> &v,Option_t *option)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(v.IsValid());
      if (v.GetNoElements() < this->fNrows) {
         //Error("NormByColumn","vector shorter than matrix column");
         return *this;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t divide = (opt.Contains("D")) ? 1 : 0;

   const Element *pv = v.GetMatrixArray();
         Element *mp = this->GetMatrixArray();
   const Element * const mp_last = mp+this->fNelems;

   if (divide) {
      for ( ; mp < mp_last; pv++) {
         for (Int_t j = 0; j < this->fNcols; j++)
         {
            if (*pv != 0.0)
               *mp++ /= *pv;
            else {
               //Error("NormbyColumn","vector element %ld is zero",Long_t(pv-v.GetMatrixArray()));
               mp++;
            }
         }
      }
   } else {
      for ( ; mp < mp_last; pv++)
         for (Int_t j = 0; j < this->fNcols; j++)
            *mp++ *= *pv;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply/divide matrix rows with a vector:
/// option:
/// "D"   :  b(i,j) = a(i,j)/v(j)   i = 0,fNcols-1 (default)
/// else  :  b(i,j) = a(i,j)*v(j)

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::NormByRow(const TVectorT<Element> &v,Option_t *option)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(v.IsValid());
      if (v.GetNoElements() < this->fNcols) {
         //Error("NormByRow","vector shorter than matrix column");
         return *this;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t divide = (opt.Contains("D")) ? 1 : 0;

   const Element *pv0 = v.GetMatrixArray();
   const Element *pv  = pv0;
         Element *mp  = this->GetMatrixArray();
   const Element * const mp_last = mp+this->fNelems;

   if (divide) {
      for ( ; mp < mp_last; pv = pv0 )
         for (Int_t j = 0; j < this->fNcols; j++) {
            if (*pv != 0.0)
               *mp++ /= *pv++;
            else {
               //Error("NormbyRow","vector element %ld is zero",Long_t(pv-pv0));
               mp++;
            }
         }
    } else {
       for ( ; mp < mp_last; pv = pv0 )
          for (Int_t j = 0; j < this->fNcols; j++)
             *mp++ *= *pv++;
    }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator=(const TMatrixT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator=(const TMatrixT &)","matrices not compatible");
      return *this;
   }

   if (this->GetMatrixArray() != source.GetMatrixArray()) {
      //TObject::operator=(source);
      memcpy(fElements,source.GetMatrixArray(),this->fNelems*sizeof(Element));
      this->fTol = source.GetTol();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator=(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator=(const TMatrixTSym &)","matrices not compatible");
      return *this;
   }

   if (this->GetMatrixArray() != source.GetMatrixArray()) {
      //TObject::operator=(source);
      memcpy(fElements,source.GetMatrixArray(),this->fNelems*sizeof(Element));
      this->fTol = source.GetTol();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator=(const TMatrixTSparse<Element> &source)
{
   if ((gMatrixCheck &&
        this->GetNrows()  != source.GetNrows())  || this->GetNcols()  != source.GetNcols() ||
        this->GetRowLwb() != source.GetRowLwb() || this->GetColLwb() != source.GetColLwb()) {
      //Error("operator=(const TMatrixTSparse &","matrices not compatible");
      return *this;
   }

   if (this->GetMatrixArray() != source.GetMatrixArray()) {
      //TObject::operator=(source);
      memset(fElements,0,this->fNelems*sizeof(Element));

      const Element * const sp = source.GetMatrixArray();
            Element *       tp = this->GetMatrixArray();

      const Int_t * const pRowIndex = source.GetRowIndexArray();
      const Int_t * const pColIndex = source.GetColIndexArray();

      for (Int_t irow = 0; irow < this->fNrows; irow++ ) {
         const Int_t off = irow*this->fNcols;
         const Int_t sIndex = pRowIndex[irow];
         const Int_t eIndex = pRowIndex[irow+1];
         for (Int_t index = sIndex; index < eIndex; index++)
            tp[off+pColIndex[index]] = sp[index];
      }
      this->fTol = source.GetTol();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator=(const TMatrixTLazy<Element> &lazy_constructor)
{
   //R__ASSERT(this->IsValid());

   if (lazy_constructor.GetRowUpb() != this->GetRowUpb() ||
       lazy_constructor.GetColUpb() != this->GetColUpb() ||
       lazy_constructor.GetRowLwb() != this->GetRowLwb() ||
       lazy_constructor.GetColLwb() != this->GetColLwb()) {
      //Error("operator=(const TMatrixTLazy&)", "matrix is incompatible with "
            //"the assigned Lazy matrix");
      return *this;
   }

   lazy_constructor.FillIn(*this);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ = val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the matrix.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator+=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ += val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract val from every element of the matrix.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator-=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ -= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix with val.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator*=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ *= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add the source matrix.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator+=(const TMatrixT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator+=(const TMatrixT &)","matrices not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
   Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+this->fNelems;
   while (tp < tp_last)
      *tp++ += *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add the source matrix.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator+=(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator+=(const TMatrixTSym &)","matrices not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
   Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+this->fNelems;
   while (tp < tp_last)
      *tp++ += *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract the source matrix.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator-=(const TMatrixT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator=-(const TMatrixT &)","matrices not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
   Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+this->fNelems;
   while (tp < tp_last)
      *tp++ -= *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract the source matrix.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator-=(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator=-(const TMatrixTSym &)","matrices not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
   Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+this->fNelems;
   while (tp < tp_last)
      *tp++ -= *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute target = target * source inplace. Strictly speaking, it can't be
/// done inplace, though only the row of the target matrix needs to be saved.
/// "Inplace" multiplication is only allowed when the 'source' matrix is square.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator*=(const TMatrixT<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());
      if (this->fNcols != source.GetNrows() || this->fColLwb != source.GetRowLwb() ||
          this->fNcols != source.GetNcols() || this->fColLwb != source.GetColLwb()) {
         //Error("operator*=(const TMatrixT &)","source matrix has wrong shape");
         return *this;
      }
   }

   // Check for A *= A;
   const Element *sp;
   TMatrixT<Element> tmp;
   if (this->GetMatrixArray() == source.GetMatrixArray()) {
      tmp.ResizeTo(source);
      tmp = source;
      sp = tmp.GetMatrixArray();
   }
   else
      sp = source.GetMatrixArray();

   // One row of the old_target matrix
   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *trp = work;
   if (this->fNcols > kWorkMax) {
      isAllocated = kTRUE;
      trp = new Element[this->fNcols];
   }

         Element *cp   = this->GetMatrixArray();
   const Element *trp0 = cp; // Pointer to  target[i,0];
   const Element * const trp0_last = trp0+this->fNelems;
   while (trp0 < trp0_last) {
      memcpy(trp,trp0,this->fNcols*sizeof(Element));        // copy the i-th row of target, Start at target[i,0]
      for (const Element *scp = sp; scp < sp+this->fNcols; ) {  // Pointer to the j-th column of source,
                                                           // Start scp = source[0,0]
         Element cij = 0;
         for (Int_t j = 0; j < this->fNcols; j++) {
            cij += trp[j] * *scp;                        // the j-th col of source
            scp += this->fNcols;
         }
         *cp++ = cij;
         scp -= source.GetNoElements()-1;               // Set bcp to the (j+1)-th col
      }
      trp0 += this->fNcols;                            // Set trp0 to the (i+1)-th row
      //R__ASSERT(trp0 == cp);
   }

   //R__ASSERT(cp == trp0_last && trp0 == trp0_last);
   if (isAllocated)
      delete [] trp;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Compute target = target * source inplace. Strictly speaking, it can't be
/// done inplace, though only the row of the target matrix needs to be saved.

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator*=(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());
      if (this->fNcols != source.GetNrows() || this->fColLwb != source.GetRowLwb()) {
         //Error("operator*=(const TMatrixTSym &)","source matrix has wrong shape");
         return *this;
      }
   }

   // Check for A *= A;
   const Element *sp;
   TMatrixT<Element> tmp;
   if (this->GetMatrixArray() == source.GetMatrixArray()) {
      tmp.ResizeTo(source);
      tmp = source;
      sp = tmp.GetMatrixArray();
   }
   else
      sp = source.GetMatrixArray();

   // One row of the old_target matrix
   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *trp = work;
   if (this->fNcols > kWorkMax) {
      isAllocated = kTRUE;
      trp = new Element[this->fNcols];
   }

         Element *cp   = this->GetMatrixArray();
   const Element *trp0 = cp; // Pointer to  target[i,0];
   const Element * const trp0_last = trp0+this->fNelems;
   while (trp0 < trp0_last) {
      memcpy(trp,trp0,this->fNcols*sizeof(Element));        // copy the i-th row of target, Start at target[i,0]
      for (const Element *scp = sp; scp < sp+this->fNcols; ) {  // Pointer to the j-th column of source,
                                                           // Start scp = source[0,0]
         Element cij = 0;
         for (Int_t j = 0; j < this->fNcols; j++) {
            cij += trp[j] * *scp;                        // the j-th col of source
            scp += this->fNcols;
         }
         *cp++ = cij;
         scp -= source.GetNoElements()-1;               // Set bcp to the (j+1)-th col
      }
      trp0 += this->fNcols;                            // Set trp0 to the (i+1)-th row
      //R__ASSERT(trp0 == cp);
   }

   //R__ASSERT(cp == trp0_last && trp0 == trp0_last);
   if (isAllocated)
      delete [] trp;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply a matrix row by the diagonal of another matrix
/// matrix(i,j) *= diag(j), j=0,fNcols-1

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator*=(const TMatrixTDiag_const<Element> &diag)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(diag.GetMatrix()->IsValid());
      if (this->fNcols != diag.GetNdiags()) {
         //Error("operator*=(const TMatrixTDiag_const &)","wrong diagonal length");
         return *this;
      }
   }

   Element *mp = this->GetMatrixArray();  // Matrix ptr
   const Element * const mp_last = mp+this->fNelems;
   const Int_t inc = diag.GetInc();
   while (mp < mp_last) {
      const Element *dp = diag.GetPtr();
      for (Int_t j = 0; j < this->fNcols; j++) {
         *mp++ *= *dp;
         dp += inc;
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Divide a matrix row by the diagonal of another matrix
/// matrix(i,j) /= diag(j)

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator/=(const TMatrixTDiag_const<Element> &diag)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(diag.GetMatrix()->IsValid());
      if (this->fNcols != diag.GetNdiags()) {
         //Error("operator/=(const TMatrixTDiag_const &)","wrong diagonal length");
         return *this;
      }
   }

   Element *mp = this->GetMatrixArray();  // Matrix ptr
   const Element * const mp_last = mp+this->fNelems;
   const Int_t inc = diag.GetInc();
   while (mp < mp_last) {
      const Element *dp = diag.GetPtr();
      for (Int_t j = 0; j < this->fNcols; j++) {
         if (*dp != 0.0)
            *mp++ /= *dp;
         else {
            //Error("operator/=","%d-diagonal element is zero",j);
            mp++;
         }
         dp += inc;
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply a matrix by the column of another matrix
/// matrix(i,j) *= another(i,k) for fixed k

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator*=(const TMatrixTColumn_const<Element> &col)
{
   const TMatrixTBase<Element> *mt = col.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(mt->IsValid());
      if (this->fNrows != mt->GetNrows()) {
         //Error("operator*=(const TMatrixTColumn_const &)","wrong column length");
         return *this;
      }
   }

   const Element * const endp = col.GetPtr()+mt->GetNoElements();
   Element *mp = this->GetMatrixArray();  // Matrix ptr
   const Element * const mp_last = mp+this->fNelems;
   const Element *cp = col.GetPtr();      //  ptr
   const Int_t inc = col.GetInc();
   while (mp < mp_last) {
      //R__ASSERT(cp < endp);
      for (Int_t j = 0; j < this->fNcols; j++)
         *mp++ *= *cp;
      cp += inc;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Divide a matrix by the column of another matrix
/// matrix(i,j) /= another(i,k) for fixed k

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator/=(const TMatrixTColumn_const<Element> &col)
{
   const TMatrixTBase<Element> *mt = col.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(mt->IsValid());
      if (this->fNrows != mt->GetNrows()) {
         //Error("operator/=(const TMatrixTColumn_const &)","wrong column matrix");
         return *this;
      }
   }

   const Element * const endp = col.GetPtr()+mt->GetNoElements();
   Element *mp = this->GetMatrixArray();  // Matrix ptr
   const Element * const mp_last = mp+this->fNelems;
   const Element *cp = col.GetPtr();      //  ptr
   const Int_t inc = col.GetInc();
   while (mp < mp_last) {
      //R__ASSERT(cp < endp);
      if (*cp != 0.0) {
         for (Int_t j = 0; j < this->fNcols; j++)
            *mp++ /= *cp;
      } else {
         const Int_t icol = (cp-mt->GetMatrixArray())/inc;
         //Error("operator/=","%d-row of matrix column is zero",icol);
         mp += this->fNcols;
      }
      cp += inc;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply a matrix by the row of another matrix
/// matrix(i,j) *= another(k,j) for fixed k

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator*=(const TMatrixTRow_const<Element> &row)
{
   const TMatrixTBase<Element> *mt = row.GetMatrix();

   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(mt->IsValid());
      if (this->fNcols != mt->GetNcols()) {
         //Error("operator*=(const TMatrixTRow_const &)","wrong row length");
         return *this;
      }
   }

   const Element * const endp = row.GetPtr()+mt->GetNoElements();
   Element *mp = this->GetMatrixArray();  // Matrix ptr
   const Element * const mp_last = mp+this->fNelems;
   const Int_t inc = row.GetInc();
   while (mp < mp_last) {
      const Element *rp = row.GetPtr();    // Row ptr
      for (Int_t j = 0; j < this->fNcols; j++) {
         //R__ASSERT(rp < endp);
         *mp++ *= *rp;
         rp += inc;
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Divide a matrix by the row of another matrix
/// matrix(i,j) /= another(k,j) for fixed k

template<class Element>
TMatrixT<Element> &TMatrixT<Element>::operator/=(const TMatrixTRow_const<Element> &row)
{
   const TMatrixTBase<Element> *mt = row.GetMatrix();
   //R__ASSERT(this->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fNcols != mt->GetNcols()) {
      //Error("operator/=(const TMatrixTRow_const &)","wrong row length");
      return *this;
   }

   const Element * const endp = row.GetPtr()+mt->GetNoElements();
   Element *mp = this->GetMatrixArray();  // Matrix ptr
   const Element * const mp_last = mp+this->fNelems;
   const Int_t inc = row.GetInc();
   while (mp < mp_last) {
      const Element *rp = row.GetPtr();    // Row ptr
      for (Int_t j = 0; j < this->fNcols; j++) {
         //R__ASSERT(rp < endp);
         if (*rp != 0.0) {
           *mp++ /= *rp;
         } else {
            //Error("operator/=","%d-col of matrix row is zero",j);
            mp++;
         }
         rp += inc;
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Return a matrix containing the eigen-vectors ordered by descending values
/// of Re^2+Im^2 of the complex eigen-values .
/// If the matrix is asymmetric, only the real part of the eigen-values is
/// returned . For full functionality use TMatrixDEigen .

template<class Element>
const TMatrixT<Element> TMatrixT<Element>::EigenVectors(TVectorT<Element> &eigenValues) const
{
   if (!this->IsSymmetric()) {}
      //Warning("EigenVectors(TVectorT &)","Only real part of eigen-values will be returned");
   TMatrixDEigen eigen(*this);
   eigenValues.ResizeTo(this->fNrows);
   eigenValues = eigen.GetEigenValuesRe();
   return eigen.GetEigenVectors();
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1+source2

template<class Element>
TMatrixT<Element> operator+(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target(source1);
   target += source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1+source2

template<class Element>
TMatrixT<Element> operator+(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target(source1);
   target += source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1+source2

template<class Element>
TMatrixT<Element> operator+(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator+(source2,source1);
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source+val

template<class Element>
TMatrixT<Element> operator+(const TMatrixT<Element> &source,Element val)
{
   TMatrixT<Element> target(source);
   target += val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = val+source

template<class Element>
TMatrixT<Element> operator+(Element val,const TMatrixT<Element> &source)
{
   return operator+(source,val);
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1-source2

template<class Element>
TMatrixT<Element> operator-(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target(source1);
   target -= source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1-source2

template<class Element>
TMatrixT<Element> operator-(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target(source1);
   target -= source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1-source2

template<class Element>
TMatrixT<Element> operator-(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return Element(-1.0)*(operator-(source2,source1));
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source-val

template<class Element>
TMatrixT<Element> operator-(const TMatrixT<Element> &source,Element val)
{
   TMatrixT<Element> target(source);
   target -= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = val-source

template<class Element>
TMatrixT<Element> operator-(Element val,const TMatrixT<Element> &source)
{
   return Element(-1.0)*operator-(source,val);
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = val*source

template<class Element>
TMatrixT<Element> operator*(Element val,const TMatrixT<Element> &source)
{
   TMatrixT<Element> target(source);
   target *= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = val*source

template<class Element>
TMatrixT<Element> operator*(const TMatrixT<Element> &source,Element val)
{
   return operator*(val,source);
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1*source2

template<class Element>
TMatrixT<Element> operator*(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target(source1,TMatrixT<Element>::kMult,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1*source2

template<class Element>
TMatrixT<Element> operator*(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target(source1,TMatrixT<Element>::kMult,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1*source2

template<class Element>
TMatrixT<Element> operator*(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target(source1,TMatrixT<Element>::kMult,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// operation this = source1*source2

template<class Element>
TMatrixT<Element> operator*(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target(source1,TMatrixT<Element>::kMult,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Logical AND

template<class Element>
TMatrixT<Element> operator&&(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator&&(const TMatrixT&,const TMatrixT&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last)
      *tp++ = (*sp1++ != 0.0 && *sp2++ != 0.0);

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Logical AND

template<class Element>
TMatrixT<Element> operator&&(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator&&(const TMatrixT&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last)
      *tp++ = (*sp1++ != 0.0 && *sp2++ != 0.0);

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Logical AND

template<class Element>
TMatrixT<Element> operator&&(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator&&(source2,source1);
}

////////////////////////////////////////////////////////////////////////////////
/// Logical OR

template<class Element>
TMatrixT<Element> operator||(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator||(const TMatrixT&,const TMatrixT&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last)
      *tp++ = (*sp1++ != 0.0 || *sp2++ != 0.0);

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Logical OR

template<class Element>
TMatrixT<Element> operator||(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator||(const TMatrixT&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last)
      *tp++ = (*sp1++ != 0.0 || *sp2++ != 0.0);

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Logical OR

template<class Element>
TMatrixT<Element> operator||(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator||(source2,source1);
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 > source2

template<class Element>
TMatrixT<Element> operator>(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator|(const TMatrixT&,const TMatrixT&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) > (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 > source2

template<class Element>
TMatrixT<Element> operator>(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator>(const TMatrixT&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) > (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 > source2

template<class Element>
TMatrixT<Element> operator>(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator<=(source2,source1);
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 >= source2

template<class Element>
TMatrixT<Element> operator>=(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator>=(const TMatrixT&,const TMatrixT&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) >= (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 >= source2

template<class Element>
TMatrixT<Element> operator>=(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator>=(const TMatrixT&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) >= (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 >= source2

template<class Element>
TMatrixT<Element> operator>=(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator<(source2,source1);
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 <= source2

template<class Element>
TMatrixT<Element> operator<=(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator<=(const TMatrixT&,const TMatrixT&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) <= (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 <= source2

template<class Element>
TMatrixT<Element> operator<=(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator<=(const TMatrixT&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) <= (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 <= source2

template<class Element>
TMatrixT<Element> operator<=(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator>(source2,source1);
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 < source2

template<class Element>
TMatrixT<Element> operator<(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator<(const TMatrixT&,const TMatrixT&)","matrices not compatible");
      return target;
   }

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) < (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 < source2

template<class Element>
TMatrixT<Element> operator<(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
  TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator<(const TMatrixT&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) < (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 < source2

template<class Element>
TMatrixT<Element> operator<(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator>=(source2,source1);
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 != source2

template<class Element>
TMatrixT<Element> operator!=(const TMatrixT<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator!=(const TMatrixT&,const TMatrixT&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp != tp_last) {
      *tp++ = (*sp1) != (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 != source2

template<class Element>
TMatrixT<Element> operator!=(const TMatrixT<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixT<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator!=(const TMatrixT&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp != tp_last) {
      *tp++ = (*sp1) != (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 != source2

template<class Element>
TMatrixT<Element> operator!=(const TMatrixTSym<Element> &source1,const TMatrixT<Element> &source2)
{
   return operator!=(source2,source1);
}

/*
////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 != val

template<class Element>
TMatrixT<Element> operator!=(const TMatrixT<Element> &source1,Element val)
{
   TMatrixT<Element> target; target.ResizeTo(source1);

   const Element *sp = source1.GetMatrixArray();
         Element *tp = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp != tp_last) {
      *tp++ = (*sp != val); sp++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// logical operation source1 != val

template<class Element>
TMatrixT<Element> operator!=(Element val,const TMatrixT<Element> &source1)
{
   return operator!=(source1,val);
}
*/

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * source.

template<class Element>
TMatrixT<Element> &Add(TMatrixT<Element> &target,Element scalar,const TMatrixT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("Add(TMatrixT &,Element,const TMatrixT &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   if (scalar == 0) {
       while ( tp < ftp )
          *tp++  = scalar * (*sp++);
   } else if (scalar == 1.) {
       while ( tp < ftp )
          *tp++ = (*sp++);
   } else {
       while ( tp < ftp )
          *tp++ += scalar * (*sp++);
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * source.

template<class Element>
TMatrixT<Element> &Add(TMatrixT<Element> &target,Element scalar,const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("Add(TMatrixT &,Element,const TMatrixTSym &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   while ( tp < ftp )
      *tp++ += scalar * (*sp++);

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element.

template<class Element>
TMatrixT<Element> &ElementMult(TMatrixT<Element> &target,const TMatrixT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementMult(TMatrixT &,const TMatrixT &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   while ( tp < ftp )
      *tp++ *= *sp++;

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element.

template<class Element>
TMatrixT<Element> &ElementMult(TMatrixT<Element> &target,const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementMult(TMatrixT &,const TMatrixTSym &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   while ( tp < ftp )
      *tp++ *= *sp++;

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Divide target by the source, element-by-element.

template<class Element>
TMatrixT<Element> &ElementDiv(TMatrixT<Element> &target,const TMatrixT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementDiv(TMatrixT &,const TMatrixT &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   while ( tp < ftp ) {
      if (*sp != 0.0)
         *tp++ /= *sp++;
      else {
         const Int_t irow = (sp-source.GetMatrixArray())/source.GetNcols();
         const Int_t icol = (sp-source.GetMatrixArray())%source.GetNcols();
         //Error("ElementDiv","source (%d,%d) is zero",irow,icol);
         tp++;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element.

template<class Element>
TMatrixT<Element> &ElementDiv(TMatrixT<Element> &target,const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementDiv(TMatrixT &,const TMatrixTSym &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   while ( tp < ftp ) {
      if (*sp != 0.0)
         *tp++ /= *sp++;
      else {
         const Int_t irow = (sp-source.GetMatrixArray())/source.GetNcols();
         const Int_t icol = (sp-source.GetMatrixArray())%source.GetNcols();
         //Error("ElementDiv","source (%d,%d) is zero",irow,icol);
         *tp++ = 0.0;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Elementary routine to calculate matrix multiplication A*B

template<class Element>
void AMultB(const Element * const ap,Int_t na,Int_t ncolsa,
            const Element * const bp,Int_t nb,Int_t ncolsb,Element *cp)
{
   const Element *arp0 = ap;                     // Pointer to  A[i,0];
   while (arp0 < ap+na) {
      for (const Element *bcp = bp; bcp < bp+ncolsb; ) { // Pointer to the j-th column of B, Start bcp = B[0,0]
         const Element *arp = arp0;                       // Pointer to the i-th row of A, reset to A[i,0]
         Element cij = 0;
         while (bcp < bp+nb) {                     // Scan the i-th row of A and
            cij += *arp++ * *bcp;                   // the j-th col of B
            bcp += ncolsb;
         }
         *cp++ = cij;
         bcp -= nb-1;                              // Set bcp to the (j+1)-th col
      }
      arp0 += ncolsa;                             // Set ap to the (i+1)-th row
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Elementary routine to calculate matrix multiplication A^T*B

template<class Element>
void AtMultB(const Element * const ap,Int_t ncolsa,
             const Element * const bp,Int_t nb,Int_t ncolsb,Element *cp)
{
   const Element *acp0 = ap;           // Pointer to  A[i,0];
   while (acp0 < ap+ncolsa) {
      for (const Element *bcp = bp; bcp < bp+ncolsb; ) { // Pointer to the j-th column of B, Start bcp = B[0,0]
         const Element *acp = acp0;                       // Pointer to the i-th column of A, reset to A[0,i]
         Element cij = 0;
         while (bcp < bp+nb) {           // Scan the i-th column of A and
            cij += *acp * *bcp;           // the j-th col of B
            acp += ncolsa;
            bcp += ncolsb;
         }
         *cp++ = cij;
         bcp -= nb-1;                    // Set bcp to the (j+1)-th col
      }
      acp0++;                           // Set acp0 to the (i+1)-th col
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Elementary routine to calculate matrix multiplication A*B^T

template<class Element>
void AMultBt(const Element * const ap,Int_t na,Int_t ncolsa,
             const Element * const bp,Int_t nb,Int_t ncolsb,Element *cp)
{
   const Element *arp0 = ap;                    // Pointer to  A[i,0];
   while (arp0 < ap+na) {
      const Element *brp0 = bp;                  // Pointer to  B[j,0];
      while (brp0 < bp+nb) {
         const Element *arp = arp0;               // Pointer to the i-th row of A, reset to A[i,0]
         const Element *brp = brp0;               // Pointer to the j-th row of B, reset to B[j,0]
         Element cij = 0;
         while (brp < brp0+ncolsb)                 // Scan the i-th row of A and
            cij += *arp++ * *brp++;                 // the j-th row of B
         *cp++ = cij;
         brp0 += ncolsb;                           // Set brp0 to the (j+1)-th row
      }
      arp0 += ncolsa;                             // Set arp0 to the (i+1)-th row
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Stream an object of class TMatrixT.
/*
template<class Element>
void TMatrixT<Element>::Streamer(TBuffer &R__b)
{
   if (R__b.IsReading()) {
      UInt_t R__s, R__c;
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c);
      if (R__v > 2) {
         Clear();
         R__b.ReadClassBuffer(TMatrixT<Element>::Class(),this,R__v,R__s,R__c);
      } else if (R__v == 2) { //process old version 2
         Clear();
         TObject::Streamer(R__b);
         this->MakeValid();
         R__b >> this->fNrows;
         R__b >> this->fNcols;
         R__b >> this->fNelems;
         R__b >> this->fRowLwb;
         R__b >> this->fColLwb;
         Char_t isArray;
         R__b >> isArray;
         if (isArray) {
            if (this->fNelems > 0) {
               fElements = new Element[this->fNelems];
               R__b.ReadFastArray(fElements,this->fNelems);
            } else
               fElements = 0;
         }
         R__b.CheckByteCount(R__s,R__c,TMatrixT<Element>::IsA());
      } else { //====process old versions before automatic schema evolution
         TObject::Streamer(R__b);
         this->MakeValid();
         R__b >> this->fNrows;
         R__b >> this->fNcols;
         R__b >> this->fRowLwb;
         R__b >> this->fColLwb;
         this->fNelems = R__b.ReadArray(fElements);
         R__b.CheckByteCount(R__s,R__c,TMatrixT<Element>::IsA());
      }
      // in version <=2 , the matrix was stored column-wise
      if (R__v <= 2 && fElements) {
         for (Int_t i = 0; i < this->fNrows; i++) {
            const Int_t off_i = i*this->fNcols;
            for (Int_t j = i; j < this->fNcols; j++) {
               const Int_t off_j = j*this->fNrows;
               const Element tmp = fElements[off_i+j];
               fElements[off_i+j] = fElements[off_j+i];
               fElements[off_j+i] = tmp;
            }
         }
      }
      if (this->fNelems > 0 && this->fNelems <= this->kSizeMax) {
         if (fElements) {
            memcpy(fDataStack,fElements,this->fNelems*sizeof(Element));
            delete [] fElements;
         }
         fElements = fDataStack;
      } else if (this->fNelems < 0)
         this->Invalidate();
      } else {
         R__b.WriteClassBuffer(TMatrixT<Element>::Class(),this);
   }
}
*/

template class TMatrixT<Float_t>;

//#include "TMatrixFfwd.h"
//#include "TMatrixFSymfwd.h"

template TMatrixF  operator+  <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator+  <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator+  <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator+  <Float_t>(const TMatrixF    &source ,      Float_t      val    );
template TMatrixF  operator+  <Float_t>(      Float_t      val    ,const TMatrixF    &source );
template TMatrixF  operator-  <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator-  <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator-  <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator-  <Float_t>(const TMatrixF    &source ,      Float_t      val    );
template TMatrixF  operator-  <Float_t>(      Float_t      val    ,const TMatrixF    &source );
template TMatrixF  operator*  <Float_t>(      Float_t      val    ,const TMatrixF    &source );
template TMatrixF  operator*  <Float_t>(const TMatrixF    &source ,      Float_t      val    );
template TMatrixF  operator*  <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator*  <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator*  <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator*  <Float_t>(const TMatrixFSym &source1,const TMatrixFSym &source2);
template TMatrixF  operator&& <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator&& <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator&& <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator|| <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator|| <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator|| <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator>  <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator>  <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator>  <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator>= <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator>= <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator>= <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator<= <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator<= <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator<= <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator<  <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator<  <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator<  <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);
template TMatrixF  operator!= <Float_t>(const TMatrixF    &source1,const TMatrixF    &source2);
template TMatrixF  operator!= <Float_t>(const TMatrixF    &source1,const TMatrixFSym &source2);
template TMatrixF  operator!= <Float_t>(const TMatrixFSym &source1,const TMatrixF    &source2);

template TMatrixF &Add        <Float_t>(TMatrixF &target,      Float_t      scalar,const TMatrixF    &source);
template TMatrixF &Add        <Float_t>(TMatrixF &target,      Float_t      scalar,const TMatrixFSym &source);
template TMatrixF &ElementMult<Float_t>(TMatrixF &target,const TMatrixF    &source);
template TMatrixF &ElementMult<Float_t>(TMatrixF &target,const TMatrixFSym &source);
template TMatrixF &ElementDiv <Float_t>(TMatrixF &target,const TMatrixF    &source);
template TMatrixF &ElementDiv <Float_t>(TMatrixF &target,const TMatrixFSym &source);

template void AMultB <Float_t>(const Float_t * const ap,Int_t na,Int_t ncolsa,
                               const Float_t * const bp,Int_t nb,Int_t ncolsb,Float_t *cp);
template void AtMultB<Float_t>(const Float_t * const ap,Int_t ncolsa,
                               const Float_t * const bp,Int_t nb,Int_t ncolsb,Float_t *cp);
template void AMultBt<Float_t>(const Float_t * const ap,Int_t na,Int_t ncolsa,
                               const Float_t * const bp,Int_t nb,Int_t ncolsb,Float_t *cp);

//#include "TMatrixDfwd.h"
//#include "TMatrixDSymfwd.h"

template class TMatrixT<Double_t>;

template TMatrixD  operator+  <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator+  <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator+  <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator+  <Double_t>(const TMatrixD    &source ,      Double_t     val    );
template TMatrixD  operator+  <Double_t>(      Double_t     val    ,const TMatrixD    &source );
template TMatrixD  operator-  <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator-  <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator-  <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator-  <Double_t>(const TMatrixD    &source ,      Double_t     val    );
template TMatrixD  operator-  <Double_t>(      Double_t     val    ,const TMatrixD    &source );
template TMatrixD  operator*  <Double_t>(      Double_t     val    ,const TMatrixD    &source );
template TMatrixD  operator*  <Double_t>(const TMatrixD    &source ,      Double_t     val    );
template TMatrixD  operator*  <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator*  <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator*  <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator*  <Double_t>(const TMatrixDSym &source1,const TMatrixDSym &source2);
template TMatrixD  operator&& <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator&& <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator&& <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator|| <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator|| <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator|| <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator>  <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator>  <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator>  <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator>= <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator>= <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator>= <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator<= <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator<= <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator<= <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator<  <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator<  <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator<  <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);
template TMatrixD  operator!= <Double_t>(const TMatrixD    &source1,const TMatrixD    &source2);
template TMatrixD  operator!= <Double_t>(const TMatrixD    &source1,const TMatrixDSym &source2);
template TMatrixD  operator!= <Double_t>(const TMatrixDSym &source1,const TMatrixD    &source2);

template TMatrixD &Add        <Double_t>(TMatrixD &target,      Double_t     scalar,const TMatrixD    &source);
template TMatrixD &Add        <Double_t>(TMatrixD &target,      Double_t     scalar,const TMatrixDSym &source);
template TMatrixD &ElementMult<Double_t>(TMatrixD &target,const TMatrixD    &source);
template TMatrixD &ElementMult<Double_t>(TMatrixD &target,const TMatrixDSym &source);
template TMatrixD &ElementDiv <Double_t>(TMatrixD &target,const TMatrixD    &source);
template TMatrixD &ElementDiv <Double_t>(TMatrixD &target,const TMatrixDSym &source);

template void AMultB <Double_t>(const Double_t * const ap,Int_t na,Int_t ncolsa,
                                const Double_t * const bp,Int_t nb,Int_t ncolsb,Double_t *cp);
template void AtMultB<Double_t>(const Double_t * const ap,Int_t ncolsa,
                                const Double_t * const bp,Int_t nb,Int_t ncolsb,Double_t *cp);
template void AMultBt<Double_t>(const Double_t * const ap,Int_t na,Int_t ncolsa,
                                const Double_t * const bp,Int_t nb,Int_t ncolsb,Double_t *cp);

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixTUtils
    \ingroup Matrix

 Matrix utility classes.

 Templates of utility classes in the Linear Algebra Package.
 The following classes are defined here:

 Different matrix views without copying data elements :
~~~
   TMatrixTRow_const        TMatrixTRow
   TMatrixTColumn_const     TMatrixTColumn
   TMatrixTDiag_const       TMatrixTDiag
   TMatrixTFlat_const       TMatrixTFlat
   TMatrixTSub_const        TMatrixTSub
   TMatrixTSparseRow_const  TMatrixTSparseRow
   TMatrixTSparseDiag_const TMatrixTSparseDiag

   TElementActionT
   TElementPosActionT
~~~
*/

//#include "TMatrixTUtils.h"
//#include "TMatrixT.h"
//#include "TMatrixTSym.h"
//#include "TMatrixTSparse.h"
//#include "TMath.h"
//#include "TVectorT.h"

////////////////////////////////////////////////////////////////////////////////
/// Constructor with row "row" of matrix

template<class Element>
TMatrixTRow_const<Element>::TMatrixTRow_const(const TMatrixT<Element> &matrix,Int_t row)
{
   //R__ASSERT(matrix.IsValid());

   fRowInd = row-matrix.GetRowLwb();
   if (fRowInd >= matrix.GetNrows() || fRowInd < 0) {
      //Error("TMatrixTRow_const(const TMatrixT<Element> &,Int_t)","row index out of bounds");
      fMatrix = 0;
      fPtr = 0;
      fInc = 0;
      return;
   }

   fMatrix = &matrix;
   fPtr = matrix.GetMatrixArray()+fRowInd*matrix.GetNcols();
   fInc = 1;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with row "row" of symmetric matrix

template<class Element>
TMatrixTRow_const<Element>::TMatrixTRow_const(const TMatrixTSym<Element> &matrix,Int_t row)
{
   //R__ASSERT(matrix.IsValid());

   fRowInd = row-matrix.GetRowLwb();
   if (fRowInd >= matrix.GetNrows() || fRowInd < 0) {
      //Error("TMatrixTRow_const(const TMatrixTSym &,Int_t)","row index out of bounds");
      fMatrix = 0;
      fPtr = 0;
      fInc = 0;
      return;
   }

   fMatrix = &matrix;
   fPtr = matrix.GetMatrixArray()+fRowInd*matrix.GetNcols();
   fInc = 1;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with row "row" of symmetric matrix

template<class Element>
TMatrixTRow<Element>::TMatrixTRow(TMatrixT<Element> &matrix,Int_t row)
            :TMatrixTRow_const<Element>(matrix,row)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with row "row" of symmetric matrix

template<class Element>
TMatrixTRow<Element>::TMatrixTRow(TMatrixTSym<Element> &matrix,Int_t row)
            :TMatrixTRow_const<Element>(matrix,row)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TMatrixTRow<Element>::TMatrixTRow(const TMatrixTRow<Element> &mr) : TMatrixTRow_const<Element>(mr)
{
   *this = mr;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix row.

template<class Element>
void TMatrixTRow<Element>::Assign(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fPtr);
   for ( ; rp < this->fPtr+this->fMatrix->GetNcols(); rp += this->fInc)
      *rp = val;
}

template<class Element>
void TMatrixTRow<Element>::operator=(std::initializer_list<Element>  l)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fPtr);
   auto litr = l.begin();
   for ( ; rp < this->fPtr+this->fMatrix->GetNcols() && litr != l.end(); rp += this->fInc)
      *rp = *litr++;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the matrix row.

template<class Element>
void TMatrixTRow<Element>::operator+=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fPtr);
   for ( ; rp < this->fPtr+this->fMatrix->GetNcols(); rp += this->fInc)
      *rp += val;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix row with val.

template<class Element>
void TMatrixTRow<Element>::operator*=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fPtr);
   for ( ; rp < this->fPtr + this->fMatrix->GetNcols(); rp += this->fInc)
      *rp *= val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTRow<Element>::operator=(const TMatrixTRow_const<Element> &mr)
{
   const TMatrixTBase<Element> *mt = mr.GetMatrix();
   if (this->fMatrix->GetMatrixArray() == mt->GetMatrixArray() && this->fRowInd == mr.GetRowIndex()) return;

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fMatrix->GetNcols() != mt->GetNcols() || this->fMatrix->GetColLwb() != mt->GetColLwb()) {
      //Error("operator=(const TMatrixTRow_const &)", "matrix rows not compatible");
      return;
   }

   Element *rp1 = const_cast<Element *>(this->fPtr);
   const Element *rp2 = mr.GetPtr();
   for ( ; rp1 < this->fPtr+this->fMatrix->GetNcols(); rp1 += this->fInc,rp2 += mr.GetInc())
      *rp1 = *rp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a vector to a matrix row. The vector is considered row-vector
/// to allow the assignment in the strict sense.

template<class Element>
void TMatrixTRow<Element>::operator=(const TVectorT<Element> &vec)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(vec.IsValid());

   if (this->fMatrix->GetColLwb() != vec.GetLwb() || this->fMatrix->GetNcols() != vec.GetNrows()) {
      //Error("operator=(const TVectorT &)","vector length != matrix-row length");
      return;
   }

   Element *rp = const_cast<Element *>(this->fPtr);
   const Element *vp = vec.GetMatrixArray();
   for ( ; rp < this->fPtr+this->fMatrix->GetNcols(); rp += this->fInc)
      *rp = *vp++;
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the matrix row the corresponding element of row r.

template<class Element>
void TMatrixTRow<Element>::operator+=(const TMatrixTRow_const<Element> &r)
{
  const TMatrixTBase<Element> *mt = r.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fMatrix->GetColLwb() != mt->GetColLwb() || this->fMatrix->GetNcols() != mt->GetNcols()) {
      //Error("operator+=(const TMatrixTRow_const &)","different row lengths");
      return;
   }

   Element *rp1 = const_cast<Element *>(this->fPtr);
   const Element *rp2 = r.GetPtr();
   for ( ; rp1 < this->fPtr+this->fMatrix->GetNcols(); rp1 += this->fInc,rp2 += r.GetInc())
     *rp1 += *rp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix row with the
/// corresponding element of row r.

template<class Element>
void TMatrixTRow<Element>::operator*=(const TMatrixTRow_const<Element> &r)
{
   const TMatrixTBase<Element> *mt = r.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fMatrix->GetColLwb() != mt->GetColLwb() || this->fMatrix->GetNcols() != mt->GetNcols()) {
      //Error("operator*=(const TMatrixTRow_const &)","different row lengths");
      return;
   }

   Element *rp1 = const_cast<Element *>(this->fPtr);
   const Element *rp2 = r.GetPtr();
   for ( ; rp1 < this->fPtr+this->fMatrix->GetNcols(); rp1 += this->fInc,rp2 += r.GetInc())
      *rp1 *= *rp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with column "col" of matrix

template<class Element>
TMatrixTColumn_const<Element>::TMatrixTColumn_const(const TMatrixT<Element> &matrix,Int_t col)
{
   //R__ASSERT(matrix.IsValid());

   this->fColInd = col-matrix.GetColLwb();
   if (this->fColInd >= matrix.GetNcols() || this->fColInd < 0) {
      //Error("TMatrixTColumn_const(const TMatrixT &,Int_t)","column index out of bounds");
      fMatrix = 0;
      fPtr = 0;
      fInc = 0;
      return;
   }

   fMatrix = &matrix;
   fPtr = matrix.GetMatrixArray()+fColInd;
   fInc = matrix.GetNcols();
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with column "col" of matrix

template<class Element>
TMatrixTColumn_const<Element>::TMatrixTColumn_const(const TMatrixTSym<Element> &matrix,Int_t col)
{
   //R__ASSERT(matrix.IsValid());

   fColInd = col-matrix.GetColLwb();
   if (fColInd >= matrix.GetNcols() || fColInd < 0) {
      //Error("TMatrixTColumn_const(const TMatrixTSym &,Int_t)","column index out of bounds");
      fMatrix = 0;
      fPtr = 0;
      fInc = 0;
      return;
   }

   fMatrix = &matrix;
   fPtr = matrix.GetMatrixArray()+fColInd;
   fInc = matrix.GetNcols();
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with column "col" of matrix

template<class Element>
TMatrixTColumn<Element>::TMatrixTColumn(TMatrixT<Element> &matrix,Int_t col)
               :TMatrixTColumn_const<Element>(matrix,col)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with column "col" of matrix

template<class Element>
TMatrixTColumn<Element>::TMatrixTColumn(TMatrixTSym<Element> &matrix,Int_t col)
               :TMatrixTColumn_const<Element>(matrix,col)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TMatrixTColumn<Element>::TMatrixTColumn(const TMatrixTColumn<Element> &mc) : TMatrixTColumn_const<Element>(mc)
{
   *this = mc;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix column.

template<class Element>
void TMatrixTColumn<Element>::Assign(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *cp = const_cast<Element *>(this->fPtr);
   for ( ; cp < this->fPtr+this->fMatrix->GetNoElements(); cp += this->fInc)
      *cp = val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign element of the matrix column using given initializer list

template<class Element>
void TMatrixTColumn<Element>::operator=(std::initializer_list<Element>  l)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fPtr);
   auto litr = l.begin();
   for ( ; rp < this->fPtr+this->fMatrix->GetNoElements() && litr != l.end(); rp += this->fInc)
      *rp = *litr++;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the matrix column.

template<class Element>
void TMatrixTColumn<Element>::operator+=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *cp = const_cast<Element *>(this->fPtr);
   for ( ; cp < this->fPtr+this->fMatrix->GetNoElements(); cp += this->fInc)
      *cp += val;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix column with val.

template<class Element>
void TMatrixTColumn<Element>::operator*=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *cp = const_cast<Element *>(this->fPtr);
   for ( ; cp < this->fPtr+this->fMatrix->GetNoElements(); cp += this->fInc)
      *cp *= val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTColumn<Element>::operator=(const TMatrixTColumn_const<Element> &mc)
{
   const TMatrixTBase<Element> *mt = mc.GetMatrix();
   if (this->fMatrix->GetMatrixArray() == mt->GetMatrixArray() && this->fColInd == mc.GetColIndex()) return;

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fMatrix->GetNrows() != mt->GetNrows() || this->fMatrix->GetRowLwb() != mt->GetRowLwb()) {
      //Error("operator=(const TMatrixTColumn_const &)", "matrix columns not compatible");
      return;
   }

   Element *cp1 = const_cast<Element *>(this->fPtr);
   const Element *cp2 = mc.GetPtr();
   for ( ; cp1 < this->fPtr+this->fMatrix->GetNoElements(); cp1 += this->fInc,cp2 += mc.GetInc())
      *cp1 = *cp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a vector to a matrix column.

template<class Element>
void TMatrixTColumn<Element>::operator=(const TVectorT<Element> &vec)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(vec.IsValid());

   if (this->fMatrix->GetRowLwb() != vec.GetLwb() || this->fMatrix->GetNrows() != vec.GetNrows()) {
      //Error("operator=(const TVectorT &)","vector length != matrix-column length");
      return;
   }

   Element *cp = const_cast<Element *>(this->fPtr);
   const Element *vp = vec.GetMatrixArray();
   for ( ; cp < this->fPtr+this->fMatrix->GetNoElements(); cp += this->fInc)
      *cp = *vp++;

   //R__ASSERT(vp == vec.GetMatrixArray()+vec.GetNrows());
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the matrix row the corresponding element of row mc.

template<class Element>
void TMatrixTColumn<Element>::operator+=(const TMatrixTColumn_const<Element> &mc)
{
   const TMatrixTBase<Element> *mt = mc.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fMatrix->GetRowLwb() != mt->GetRowLwb() || this->fMatrix->GetNrows() != mt->GetNrows()) {
      //Error("operator+=(const TMatrixTColumn_const &)","different row lengths");
      return;
   }

   Element *cp1 = const_cast<Element *>(this->fPtr);
   const Element *cp2 = mc.GetPtr();
   for ( ; cp1 < this->fPtr+this->fMatrix->GetNoElements(); cp1 += this->fInc,cp2 += mc.GetInc())
      *cp1 += *cp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix column with the
/// corresponding element of column mc.

template<class Element>
void TMatrixTColumn<Element>::operator*=(const TMatrixTColumn_const<Element> &mc)
{
   const TMatrixTBase<Element> *mt = mc.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fMatrix->GetRowLwb() != mt->GetRowLwb() || this->fMatrix->GetNrows() != mt->GetNrows()) {
      //Error("operator*=(const TMatrixTColumn_const &)","different row lengths");
      return;
   }

   Element *cp1 = const_cast<Element *>(this->fPtr);
   const Element *cp2 = mc.GetPtr();
   for ( ; cp1 < this->fPtr+this->fMatrix->GetNoElements(); cp1 += this->fInc,cp2 += mc.GetInc())
      *cp1 *= *cp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTDiag_const<Element>::TMatrixTDiag_const(const TMatrixT<Element> &matrix)
{
   //R__ASSERT(matrix.IsValid());

   fMatrix = &matrix;
   fNdiag  = TMath::Min(matrix.GetNrows(),matrix.GetNcols());
   fPtr    = matrix.GetMatrixArray();
   fInc    = matrix.GetNcols()+1;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTDiag_const<Element>::TMatrixTDiag_const(const TMatrixTSym<Element> &matrix)
{
   //R__ASSERT(matrix.IsValid());

   fMatrix = &matrix;
   fNdiag  = TMath::Min(matrix.GetNrows(),matrix.GetNcols());
   fPtr    = matrix.GetMatrixArray();
   fInc    = matrix.GetNcols()+1;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTDiag<Element>::TMatrixTDiag(TMatrixT<Element> &matrix)
             :TMatrixTDiag_const<Element>(matrix)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTDiag<Element>::TMatrixTDiag(TMatrixTSym<Element> &matrix)
             :TMatrixTDiag_const<Element>(matrix)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TMatrixTDiag<Element>::TMatrixTDiag(const TMatrixTDiag<Element> &md) : TMatrixTDiag_const<Element>(md)
{
   *this = md;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix diagonal.

template<class Element>
void TMatrixTDiag<Element>::operator=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *dp = const_cast<Element *>(this->fPtr);
   for (Int_t i = 0; i < this->fNdiag; i++, dp += this->fInc)
      *dp = val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix diagonal.

template<class Element>
void TMatrixTDiag<Element>::operator+=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *dp = const_cast<Element *>(this->fPtr);
   for (Int_t i = 0; i < this->fNdiag; i++, dp += this->fInc)
      *dp += val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix diagonal.

template<class Element>
void TMatrixTDiag<Element>::operator*=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *dp = const_cast<Element *>(this->fPtr);
   for (Int_t i = 0; i < this->fNdiag; i++, dp += this->fInc)
      *dp *= val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTDiag<Element>::operator=(const TMatrixTDiag_const<Element> &md)
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();
   if (this->fMatrix == mt) return;

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->GetNdiags() != md.GetNdiags()) {
      //Error("operator=(const TMatrixTDiag_const &)","diagonals not compatible");
      return;
   }

   Element *dp1 = const_cast<Element *>(this->fPtr);
   const Element *dp2 = md.GetPtr();
   for (Int_t i = 0; i < this->fNdiag; i++, dp1 += this->fInc, dp2 += md.GetInc())
      *dp1 = *dp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a vector to the matrix diagonal.

template<class Element>
void TMatrixTDiag<Element>::operator=(const TVectorT<Element> &vec)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(vec.IsValid());

   if (this->fNdiag != vec.GetNrows()) {
      //Error("operator=(const TVectorT &)","vector length != matrix-diagonal length");
      return;
   }

   Element *dp = const_cast<Element *>(this->fPtr);
   const Element *vp = vec.GetMatrixArray();
   for ( ; vp < vec.GetMatrixArray()+vec.GetNrows(); dp += this->fInc)
      *dp = *vp++;
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the matrix diagonal the
/// corresponding element of diagonal md.

template<class Element>
void TMatrixTDiag<Element>::operator+=(const TMatrixTDiag_const<Element> &md)
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fNdiag != md.GetNdiags()) {
      //Error("operator=(const TMatrixTDiag_const &)","matrix-diagonal's different length");
      return;
   }

   Element *dp1 = const_cast<Element *>(this->fPtr);
   const Element *dp2 = md.GetPtr();
   for (Int_t i = 0; i < this->fNdiag; i++, dp1 += this->fInc, dp2 += md.GetInc())
      *dp1 += *dp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix diagonal with the
/// corresponding element of diagonal md.

template<class Element>
void TMatrixTDiag<Element>::operator*=(const TMatrixTDiag_const<Element> &md)
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fNdiag != md.GetNdiags()) {
      //Error("operator*=(const TMatrixTDiag_const &)","matrix-diagonal's different length");
      return;
   }

   Element *dp1 = const_cast<Element *>(this->fPtr);
   const Element *dp2 = md.GetPtr();
   for (Int_t i = 0; i < this->fNdiag; i++, dp1 += this->fInc, dp2 += md.GetInc())
      *dp1 *= *dp2;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTFlat_const<Element>::TMatrixTFlat_const(const TMatrixT<Element> &matrix)
{
   //R__ASSERT(matrix.IsValid());

   fMatrix = &matrix;
   fPtr    = matrix.GetMatrixArray();
   fNelems = matrix.GetNoElements();
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTFlat_const<Element>::TMatrixTFlat_const(const TMatrixTSym<Element> &matrix)
{
   //R__ASSERT(matrix.IsValid());

   fMatrix = &matrix;
   fPtr    = matrix.GetMatrixArray();
   fNelems = matrix.GetNoElements();
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTFlat<Element>::TMatrixTFlat(TMatrixT<Element> &matrix)
             :TMatrixTFlat_const<Element>(matrix)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTFlat<Element>::TMatrixTFlat(TMatrixTSym<Element> &matrix)
             :TMatrixTFlat_const<Element>(matrix)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TMatrixTFlat<Element>::TMatrixTFlat(const TMatrixTFlat<Element> &mf) : TMatrixTFlat_const<Element>(mf)
{
   *this = mf;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix.

template<class Element>
void TMatrixTFlat<Element>::operator=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *fp = const_cast<Element *>(this->fPtr);
   while (fp < this->fPtr+this->fMatrix->GetNoElements())
      *fp++ = val;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the matrix.

template<class Element>
void TMatrixTFlat<Element>::operator+=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *fp = const_cast<Element *>(this->fPtr);
   while (fp < this->fPtr+this->fMatrix->GetNoElements())
      *fp++ += val;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix with val.

template<class Element>
void TMatrixTFlat<Element>::operator*=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *fp = const_cast<Element *>(this->fPtr);
   while (fp < this->fPtr+this->fMatrix->GetNoElements())
      *fp++ *= val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTFlat<Element>::operator=(const TMatrixTFlat_const<Element> &mf)
{
   const TMatrixTBase<Element> *mt = mf.GetMatrix();
   if (this->fMatrix->GetMatrixArray() == mt->GetMatrixArray()) return;

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fMatrix->GetNoElements() != mt->GetNoElements()) {
      //Error("operator=(const TMatrixTFlat_const &)","matrix lengths different");
      return;
   }

   Element *fp1 = const_cast<Element *>(this->fPtr);
   const Element *fp2 = mf.GetPtr();
   while (fp1 < this->fPtr+this->fMatrix->GetNoElements())
      *fp1++ = *fp2++;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a vector to the matrix. The matrix is traversed row-wise

template<class Element>
void TMatrixTFlat<Element>::operator=(const TVectorT<Element> &vec)
{
   //R__ASSERT(vec.IsValid());

   if (this->fMatrix->GetNoElements() != vec.GetNrows()) {
      //Error("operator=(const TVectorT &)","vector length != # matrix-elements");
      return;
   }

   Element *fp = const_cast<Element *>(this->fPtr);
   const Element *vp = vec.GetMatrixArray();
   while (fp < this->fPtr+this->fMatrix->GetNoElements())
       *fp++ = *vp++;
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the matrix the corresponding element of matrix mf.

template<class Element>
void TMatrixTFlat<Element>::operator+=(const TMatrixTFlat_const<Element> &mf)
{
   const TMatrixTBase<Element> *mt = mf.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fMatrix->GetNoElements() != mt->GetNoElements()) {
      //Error("operator+=(const TMatrixTFlat_const &)","matrices lengths different");
      return;
   }

   Element *fp1 = const_cast<Element *>(this->fPtr);
   const Element *fp2 = mf.GetPtr();
   while (fp1 < this->fPtr + this->fMatrix->GetNoElements())
      *fp1++ += *fp2++;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix with the corresponding element of diagonal mf.

template<class Element>
void TMatrixTFlat<Element>::operator*=(const TMatrixTFlat_const<Element> &mf)
{
   const TMatrixTBase<Element> *mt = mf.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fMatrix->GetNoElements() != mt->GetNoElements()) {
      //Error("operator*=(const TMatrixTFlat_const &)","matrices lengths different");
      return;
   }

   Element *fp1 = const_cast<Element *>(this->fPtr);
   const Element *fp2 = mf.GetPtr();
   while (fp1 < this->fPtr + this->fMatrix->GetNoElements())
      *fp1++ *= *fp2++;
}

////////////////////////////////////////////////////////////////////////////////
/// make a reference to submatrix [row_lwbs..row_upbs][col_lwbs..col_upbs];
/// The indexing range of the reference is
/// [0..row_upbs-row_lwbs+1][0..col_upb-col_lwbs+1] (default)

template<class Element>
TMatrixTSub_const<Element>::TMatrixTSub_const(const TMatrixT<Element> &matrix,Int_t row_lwbs,Int_t row_upbs,
                                              Int_t col_lwbs,Int_t col_upbs)
{
   //R__ASSERT(matrix.IsValid());

   fRowOff    = 0;
   fColOff    = 0;
   fNrowsSub  = 0;
   fNcolsSub  = 0;
   fMatrix = &matrix;

   if (row_upbs < row_lwbs) {
      //Error("TMatrixTSub_const","Request sub-matrix with row_upbs(%d) < row_lwbs(%d)",row_upbs,row_lwbs);
      return;
   }
   if (col_upbs < col_lwbs) {
      //Error("TMatrixTSub_const","Request sub-matrix with col_upbs(%d) < col_lwbs(%d)",col_upbs,col_lwbs);
      return;
   }

   const Int_t rowLwb = matrix.GetRowLwb();
   const Int_t rowUpb = matrix.GetRowUpb();
   const Int_t colLwb = matrix.GetColLwb();
   const Int_t colUpb = matrix.GetColUpb();

   if (row_lwbs < rowLwb || row_lwbs > rowUpb) {
      //Error("TMatrixTSub_const","Request row_lwbs sub-matrix(%d) outside matrix range of %d - %d",row_lwbs,rowLwb,rowUpb);
      return;
   }
   if (col_lwbs < colLwb || col_lwbs > colUpb) {
      //Error("TMatrixTSub_const","Request col_lwbs sub-matrix(%d) outside matrix range of %d - %d",col_lwbs,colLwb,colUpb);
      return;
   }
   if (row_upbs < rowLwb || row_upbs > rowUpb) {
      //Error("TMatrixTSub_const","Request row_upbs sub-matrix(%d) outside matrix range of %d - %d",row_upbs,rowLwb,rowUpb);
      return;
   }
   if (col_upbs < colLwb || col_upbs > colUpb) {
      //Error("TMatrixTSub_const","Request col_upbs sub-matrix(%d) outside matrix range of %d - %d",col_upbs,colLwb,colUpb);
      return;
   }

   fRowOff    = row_lwbs-rowLwb;
   fColOff    = col_lwbs-colLwb;
   fNrowsSub  = row_upbs-row_lwbs+1;
   fNcolsSub  = col_upbs-col_lwbs+1;
}

////////////////////////////////////////////////////////////////////////////////
/// make a reference to submatrix [row_lwbs..row_upbs][col_lwbs..col_upbs];
/// The indexing range of the reference is
/// [0..row_upbs-row_lwbs+1][0..col_upb-col_lwbs+1] (default)

template<class Element>
TMatrixTSub_const<Element>::TMatrixTSub_const(const TMatrixTSym<Element> &matrix,Int_t row_lwbs,Int_t row_upbs,
                                              Int_t col_lwbs,Int_t col_upbs)
{
   //R__ASSERT(matrix.IsValid());

   fRowOff    = 0;
   fColOff    = 0;
   fNrowsSub  = 0;
   fNcolsSub  = 0;
   fMatrix    = &matrix;

   if (row_upbs < row_lwbs) {
      //Error("TMatrixTSub_const","Request sub-matrix with row_upbs(%d) < row_lwbs(%d)",row_upbs,row_lwbs);
      return;
   }
   if (col_upbs < col_lwbs) {
      //Error("TMatrixTSub_const","Request sub-matrix with col_upbs(%d) < col_lwbs(%d)",col_upbs,col_lwbs);
      return;
   }

   const Int_t rowLwb = matrix.GetRowLwb();
   const Int_t rowUpb = matrix.GetRowUpb();
   const Int_t colLwb = matrix.GetColLwb();
   const Int_t colUpb = matrix.GetColUpb();

   if (row_lwbs < rowLwb || row_lwbs > rowUpb) {
      //Error("TMatrixTSub_const","Request row_lwbs sub-matrix(%d) outside matrix range of %d - %d",row_lwbs,rowLwb,rowUpb);
      return;
   }
   if (col_lwbs < colLwb || col_lwbs > colUpb) {
      //Error("TMatrixTSub_const","Request col_lwbs sub-matrix(%d) outside matrix range of %d - %d",col_lwbs,colLwb,colUpb);
      return;
   }
   if (row_upbs < rowLwb || row_upbs > rowUpb) {
      //Error("TMatrixTSub_const","Request row_upbs sub-matrix(%d) outside matrix range of %d - %d",row_upbs,rowLwb,rowUpb);
      return;
   }
   if (col_upbs < colLwb || col_upbs > colUpb) {
      //Error("TMatrixTSub_const","Request col_upbs sub-matrix(%d) outside matrix range of %d - %d",col_upbs,colLwb,colUpb);
      return;
   }

   fRowOff    = row_lwbs-rowLwb;
   fColOff    = col_lwbs-colLwb;
   fNrowsSub  = row_upbs-row_lwbs+1;
   fNcolsSub  = col_upbs-col_lwbs+1;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTSub<Element>::TMatrixTSub(TMatrixT<Element> &matrix,Int_t row_lwbs,Int_t row_upbs,
                                  Int_t col_lwbs,Int_t col_upbs)
            :TMatrixTSub_const<Element>(matrix,row_lwbs,row_upbs,col_lwbs,col_upbs)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTSub<Element>::TMatrixTSub(TMatrixTSym<Element> &matrix,Int_t row_lwbs,Int_t row_upbs,
                                  Int_t col_lwbs,Int_t col_upbs)
            :TMatrixTSub_const<Element>(matrix,row_lwbs,row_upbs,col_lwbs,col_upbs)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TMatrixTSub<Element>::TMatrixTSub(const TMatrixTSub<Element> &ms) : TMatrixTSub_const<Element>(ms)
{
   *this = ms;
}

////////////////////////////////////////////////////////////////////////////////
/// Perform a rank 1 operation on the matrix:
///     A += alpha * v * v^T

template<class Element>
void TMatrixTSub<Element>::Rank1Update(const TVectorT<Element> &v,Element alpha)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(v.IsValid());

   if (v.GetNoElements() < TMath::Max(this->fNrowsSub,this->fNcolsSub)) {
      //Error("Rank1Update","vector too short");
      return;
   }

   const Element * const pv = v.GetMatrixArray();
         Element *mp = (const_cast<TMatrixTBase<Element> *>(this->fMatrix))->GetMatrixArray();

   const Int_t ncols = this->fMatrix->GetNcols();
   for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
      const Int_t off = (irow+this->fRowOff)*ncols+this->fColOff;
      const Element tmp = alpha*pv[irow];
      for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
         mp[off+icol] += tmp*pv[icol];
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the sub matrix.

template<class Element>
void TMatrixTSub<Element>::operator=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());

   Element *p = (const_cast<TMatrixTBase<Element> *>(this->fMatrix))->GetMatrixArray();
   const Int_t ncols = this->fMatrix->GetNcols();
   for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
      const Int_t off = (irow+this->fRowOff)*ncols+this->fColOff;
      for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
         p[off+icol] = val;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the sub matrix.

template<class Element>
void TMatrixTSub<Element>::operator+=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());

   Element *p = (const_cast<TMatrixTBase<Element> *>(this->fMatrix))->GetMatrixArray();
   const Int_t ncols = this->fMatrix->GetNcols();
   for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
      const Int_t off = (irow+this->fRowOff)*ncols+this->fColOff;
      for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
         p[off+icol] += val;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the sub matrix by val .

template<class Element>
void TMatrixTSub<Element>::operator*=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());

   Element *p = (const_cast<TMatrixTBase<Element> *>(this->fMatrix))->GetMatrixArray();
   const Int_t ncols = this->fMatrix->GetNcols();
   for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
      const Int_t off = (irow+this->fRowOff)*ncols+this->fColOff;
      for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
         p[off+icol] *= val;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTSub<Element>::operator=(const TMatrixTSub_const<Element> &ms)
{
   const TMatrixTBase<Element> *mt = ms.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->fMatrix == mt &&
       (this->GetNrows()  == ms.GetNrows () && this->GetNcols()  == ms.GetNcols () &&
        this->GetRowOff() == ms.GetRowOff() && this->GetColOff() == ms.GetColOff()) )
     return;

   if (this->GetNrows() != ms.GetNrows() || this->GetNcols() != ms.GetNcols()) {
     //Error("operator=(const TMatrixTSub_const &)","sub matrices have different size");
      return;
   }

   const Int_t rowOff2 = ms.GetRowOff();
   const Int_t colOff2 = ms.GetColOff();

   Bool_t overlap = (this->fMatrix == mt) &&
                    ( (rowOff2 >= this->fRowOff && rowOff2 < this->fRowOff+this->fNrowsSub) ||
                      (colOff2 >= this->fColOff && colOff2 < this->fColOff+this->fNcolsSub) );

   Element *p1 = const_cast<Element *>(this->fMatrix->GetMatrixArray());
   if (!overlap) {
      const Element *p2 = mt->GetMatrixArray();

      const Int_t ncols1 = this->fMatrix->GetNcols();
      const Int_t ncols2 = mt->GetNcols();
      for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
         const Int_t off1 = (irow+this->fRowOff)*ncols1+this->fColOff;
         const Int_t off2 = (irow+rowOff2)*ncols2+colOff2;
         for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
            p1[off1+icol] = p2[off2+icol];
      }
   } else {
      const Int_t row_lwbs = rowOff2+mt->GetRowLwb();
      const Int_t row_upbs = row_lwbs+this->fNrowsSub-1;
      const Int_t col_lwbs = colOff2+mt->GetColLwb();
      const Int_t col_upbs = col_lwbs+this->fNcolsSub-1;
      TMatrixT<Element> tmp; mt->GetSub(row_lwbs,row_upbs,col_lwbs,col_upbs,tmp);
      const Element *p2 = tmp.GetMatrixArray();

      const Int_t ncols1 = this->fMatrix->GetNcols();
      const Int_t ncols2 = tmp.GetNcols();
      for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
         const Int_t off1 = (irow+this->fRowOff)*ncols1+this->fColOff;
         const Int_t off2 = irow*ncols2;
         for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
            p1[off1+icol] = p2[off2+icol];
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTSub<Element>::operator=(const TMatrixTBase<Element> &m)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(m.IsValid());

   if (this->fMatrix->GetMatrixArray() == m.GetMatrixArray()) return;

   if (this->fNrowsSub != m.GetNrows() || this->fNcolsSub != m.GetNcols()) {
      //Error("operator=(const TMatrixTBase<Element> &)","sub matrices and matrix have different size");
      return;
   }
   const Int_t row_lwbs = this->fRowOff+this->fMatrix->GetRowLwb();
   const Int_t col_lwbs = this->fColOff+this->fMatrix->GetColLwb();
   (const_cast<TMatrixTBase<Element> *>(this->fMatrix))->SetSub(row_lwbs,col_lwbs,m);
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the submatrix the corresponding element of submatrix ms.

template<class Element>
void TMatrixTSub<Element>::operator+=(const TMatrixTSub_const<Element> &ms)
{
   const TMatrixTBase<Element> *mt = ms.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());

   if (this->GetNrows() != ms.GetNrows() || this->GetNcols() != ms.GetNcols()) {
      //Error("operator+=(const TMatrixTSub_const &)","sub matrices have different size");
      return;
   }

   const Int_t rowOff2 = ms.GetRowOff();
   const Int_t colOff2 = ms.GetColOff();

   Bool_t overlap = (this->fMatrix == mt) &&
                    ( (rowOff2 >= this->fRowOff && rowOff2 < this->fRowOff+this->fNrowsSub) ||
                      (colOff2 >= this->fColOff && colOff2 < this->fColOff+this->fNcolsSub) );

   Element *p1 = const_cast<Element *>(this->fMatrix->GetMatrixArray());
   if (!overlap) {
      const Element *p2 = mt->GetMatrixArray();

      const Int_t ncols1 = this->fMatrix->GetNcols();
      const Int_t ncols2 = mt->GetNcols();
      for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
         const Int_t off1 = (irow+this->fRowOff)*ncols1+this->fColOff;
         const Int_t off2 = (irow+rowOff2)*ncols2+colOff2;
         for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
            p1[off1+icol] += p2[off2+icol];
      }
   } else {
      const Int_t row_lwbs = rowOff2+mt->GetRowLwb();
      const Int_t row_upbs = row_lwbs+this->fNrowsSub-1;
      const Int_t col_lwbs = colOff2+mt->GetColLwb();
      const Int_t col_upbs = col_lwbs+this->fNcolsSub-1;
      TMatrixT<Element> tmp; mt->GetSub(row_lwbs,row_upbs,col_lwbs,col_upbs,tmp);
      const Element *p2 = tmp.GetMatrixArray();

      const Int_t ncols1 = this->fMatrix->GetNcols();
      const Int_t ncols2 = tmp.GetNcols();
      for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
         const Int_t off1 = (irow+this->fRowOff)*ncols1+this->fColOff;
         const Int_t off2 = irow*ncols2;
         for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
            p1[off1+icol] += p2[off2+icol];
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply submatrix with submatrix ms.

template<class Element>
void TMatrixTSub<Element>::operator*=(const TMatrixTSub_const<Element> &ms)
{
   if (this->fNcolsSub != ms.GetNrows() || this->fNcolsSub != ms.GetNcols()) {
      //Error("operator*=(const TMatrixTSub_const &)","source sub matrix has wrong shape");
      return;
   }

   const TMatrixTBase<Element> *source = ms.GetMatrix();

   TMatrixT<Element> source_sub;
   {
      const Int_t row_lwbs = ms.GetRowOff()+source->GetRowLwb();
      const Int_t row_upbs = row_lwbs+this->fNrowsSub-1;
      const Int_t col_lwbs = ms.GetColOff()+source->GetColLwb();
      const Int_t col_upbs = col_lwbs+this->fNcolsSub-1;
      source->GetSub(row_lwbs,row_upbs,col_lwbs,col_upbs,source_sub);
   }

   const Element *sp = source_sub.GetMatrixArray();
   const Int_t ncols = this->fMatrix->GetNcols();

   // One row of the old_target matrix
   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *trp = work;
   if (this->fNcolsSub > kWorkMax) {
      isAllocated = kTRUE;
      trp = new Element[this->fNcolsSub];
   }

         Element *cp   = const_cast<Element *>(this->fMatrix->GetMatrixArray())+this->fRowOff*ncols+this->fColOff;
   const Element *trp0 = cp; // Pointer to  target[i,0];
   const Element * const trp0_last = trp0+this->fNrowsSub*ncols;
   while (trp0 < trp0_last) {
      memcpy(trp,trp0,this->fNcolsSub*sizeof(Element));         // copy the i-th row of target, Start at target[i,0]
      for (const Element *scp = sp; scp < sp+this->fNcolsSub; ) {  // Pointer to the j-th column of source,
                                                                 // Start scp = source[0,0]
         Element cij = 0;
         for (Int_t j = 0; j < this->fNcolsSub; j++) {
            cij += trp[j] * *scp;                            // the j-th col of source
            scp += this->fNcolsSub;
         }
         *cp++ = cij;
         scp -= source_sub.GetNoElements()-1;               // Set bcp to the (j+1)-th col
      }
      cp   += ncols-this->fNcolsSub;
      trp0 += ncols;                                      // Set trp0 to the (i+1)-th row
      //R__ASSERT(trp0 == cp);
   }

   //R__ASSERT(cp == trp0_last && trp0 == trp0_last);
   if (isAllocated)
      delete [] trp;
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the submatrix the corresponding element of matrix mt.

template<class Element>
void TMatrixTSub<Element>::operator+=(const TMatrixTBase<Element> &mt)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt.IsValid());

   if (this->GetNrows() != mt.GetNrows() || this->GetNcols() != mt.GetNcols()) {
      //Error("operator+=(const TMatrixTBase<Element> &)","sub matrix and matrix have different size");
      return;
   }

   Element *p1 = const_cast<Element *>(this->fMatrix->GetMatrixArray());
   const Element *p2 = mt.GetMatrixArray();

   const Int_t ncols1 = this->fMatrix->GetNcols();
   const Int_t ncols2 = mt.GetNcols();
   for (Int_t irow = 0; irow < this->fNrowsSub; irow++) {
      const Int_t off1 = (irow+this->fRowOff)*ncols1+this->fColOff;
      const Int_t off2 = irow*ncols2;
      for (Int_t icol = 0; icol < this->fNcolsSub; icol++)
         p1[off1+icol] += p2[off2+icol];
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply submatrix with matrix source.

template<class Element>
void TMatrixTSub<Element>::operator*=(const TMatrixT<Element> &source)
{
   if (this->fNcolsSub != source.GetNrows() || this->fNcolsSub != source.GetNcols()) {
      //Error("operator*=(const TMatrixT<Element> &)","source matrix has wrong shape");
      return;
   }

   // Check for A *= A;
   const Element *sp;
   TMatrixT<Element> tmp;
   if (this->fMatrix->GetMatrixArray() == source.GetMatrixArray()) {
      tmp.ResizeTo(source);
      tmp = source;
      sp = tmp.GetMatrixArray();
   }
   else
      sp = source.GetMatrixArray();

   const Int_t ncols = this->fMatrix->GetNcols();

   // One row of the old_target matrix
   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
    Element *trp = work;
   if (this->fNcolsSub > kWorkMax) {
      isAllocated = kTRUE;
      trp = new Element[this->fNcolsSub];
   }

         Element *cp   = const_cast<Element *>(this->fMatrix->GetMatrixArray())+this->fRowOff*ncols+this->fColOff;
   const Element *trp0 = cp;                               // Pointer to  target[i,0];
   const Element * const trp0_last = trp0+this->fNrowsSub*ncols;
   while (trp0 < trp0_last) {
      memcpy(trp,trp0,this->fNcolsSub*sizeof(Element));           // copy the i-th row of target, Start at target[i,0]
      for (const Element *scp = sp; scp < sp+this->fNcolsSub; ) { // Pointer to the j-th column of source,
                                                                  // Start scp = source[0,0]
         Element cij = 0;
         for (Int_t j = 0; j < this->fNcolsSub; j++) {
            cij += trp[j] * *scp;                              // the j-th col of source
            scp += this->fNcolsSub;
         }
         *cp++ = cij;
         scp -= source.GetNoElements()-1;                    // Set bcp to the (j+1)-th col
      }
      cp   += ncols-this->fNcolsSub;
      trp0 += ncols;                                        // Set trp0 to the (i+1)-th row
      //R__ASSERT(trp0 == cp);
   }

   //R__ASSERT(cp == trp0_last && trp0 == trp0_last);
   if (isAllocated)
      delete [] trp;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply submatrix with matrix source.

template<class Element>
void TMatrixTSub<Element>::operator*=(const TMatrixTSym<Element> &source)
{
   if (this->fNcolsSub != source.GetNrows() || this->fNcolsSub != source.GetNcols()) {
      //Error("operator*=(const TMatrixTSym<Element> &)","source matrix has wrong shape");
      return;
   }

   // Check for A *= A;
   const Element *sp;
   TMatrixTSym<Element> tmp;
   if (this->fMatrix->GetMatrixArray() == source.GetMatrixArray()) {
      tmp.ResizeTo(source);
      tmp = source;
      sp = tmp.GetMatrixArray();
   }
   else
      sp = source.GetMatrixArray();

   const Int_t ncols = this->fMatrix->GetNcols();

   // One row of the old_target matrix
   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *trp = work;
   if (this->fNcolsSub > kWorkMax) {
      isAllocated = kTRUE;
      trp = new Element[this->fNcolsSub];
   }

         Element *cp   = const_cast<Element *>(this->fMatrix->GetMatrixArray())+this->fRowOff*ncols+this->fColOff;
   const Element *trp0 = cp;                               // Pointer to  target[i,0];
   const Element * const trp0_last = trp0+this->fNrowsSub*ncols;
   while (trp0 < trp0_last) {
      memcpy(trp,trp0,this->fNcolsSub*sizeof(Element));           // copy the i-th row of target, Start at target[i,0]
      for (const Element *scp = sp; scp < sp+this->fNcolsSub; ) { // Pointer to the j-th column of source,
                                                                // Start scp = source[0,0]
         Element cij = 0;
         for (Int_t j = 0; j < this->fNcolsSub; j++) {
            cij += trp[j] * *scp;                              // the j-th col of source
            scp += this->fNcolsSub;
         }
         *cp++ = cij;
         scp -= source.GetNoElements()-1;                     // Set bcp to the (j+1)-th col
      }
      cp   += ncols-this->fNcolsSub;
      trp0 += ncols;                                         // Set trp0 to the (i+1)-th row
      //R__ASSERT(trp0 == cp);
   }

   //R__ASSERT(cp == trp0_last && trp0 == trp0_last);
   if (isAllocated)
      delete [] trp;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with row "row" of matrix

template<class Element>
TMatrixTSparseRow_const<Element>::TMatrixTSparseRow_const(const TMatrixTSparse<Element> &matrix,Int_t row)
{
   //R__ASSERT(matrix.IsValid());

   fRowInd = row-matrix.GetRowLwb();
   if (fRowInd >= matrix.GetNrows() || fRowInd < 0) {
      //Error("TMatrixTSparseRow_const(const TMatrixTSparse &,Int_t)","row index out of bounds");
      fMatrix  = 0;
      fNindex  = 0;
      fColPtr  = 0;
      fDataPtr = 0;
      return;
   }

   const Int_t sIndex = matrix.GetRowIndexArray()[fRowInd];
   const Int_t eIndex = matrix.GetRowIndexArray()[fRowInd+1];
   fMatrix  = &matrix;
   fNindex  = eIndex-sIndex;
   fColPtr  = matrix.GetColIndexArray()+sIndex;
   fDataPtr = matrix.GetMatrixArray()+sIndex;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Element TMatrixTSparseRow_const<Element>::operator()(Int_t i) const
{
  if (!fMatrix) return TMatrixTBase<Element>::NaNValue();
  //R__ASSERT(fMatrix->IsValid());
  const Int_t acoln = i-fMatrix->GetColLwb();
  if (acoln < fMatrix->GetNcols() && acoln >= 0) {
     const Int_t index = TMath::BinarySearch(fNindex,fColPtr,acoln);
     if (index >= 0 && fColPtr[index] == acoln) return fDataPtr[index];
     else                                       return 0.0;
  } else {
     //Error("operator()","Request col(%d) outside matrix range of %d - %d",
                       // i,fMatrix->GetColLwb(),fMatrix->GetColLwb()+fMatrix->GetNcols());
     return TMatrixTBase<Element>::NaNValue();
  }
 }

////////////////////////////////////////////////////////////////////////////////
/// Constructor with row "row" of matrix

template<class Element>
TMatrixTSparseRow<Element>::TMatrixTSparseRow(TMatrixTSparse<Element> &matrix,Int_t row)
                                    : TMatrixTSparseRow_const<Element>(matrix,row)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

template<class Element>
TMatrixTSparseRow<Element>::TMatrixTSparseRow(const TMatrixTSparseRow<Element> &mr)
                                    : TMatrixTSparseRow_const<Element>(mr)
{
   *this = mr;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Element TMatrixTSparseRow<Element>::operator()(Int_t i) const
{
   if (!this->fMatrix) return TMatrixTBase<Element>::NaNValue();
   //R__ASSERT(this->fMatrix->IsValid());
   const Int_t acoln = i-this->fMatrix->GetColLwb();
   if (acoln < this->fMatrix->GetNcols() && acoln >= 0) {
      const Int_t index = TMath::BinarySearch(this->fNindex,this->fColPtr,acoln);
      if (index >= 0 && this->fColPtr[index] == acoln) return this->fDataPtr[index];
      else                                             return 0.0;
   } else {
      //Error("operator()","Request col(%d) outside matrix range of %d - %d",
            //i,this->fMatrix->GetColLwb(),this->fMatrix->GetColLwb()+this->fMatrix->GetNcols());
      return TMatrixTBase<Element>::NaNValue();
   }
}

////////////////////////////////////////////////////////////////////////////////
/// operator() : pick element row(i)

template<class Element>
Element &TMatrixTSparseRow<Element>::operator()(Int_t i)
{
   if (!this->fMatrix) return TMatrixTBase<Element>::NaNValue();
   //R__ASSERT(this->fMatrix->IsValid());

   const Int_t acoln = i-this->fMatrix->GetColLwb();
   if (acoln >= this->fMatrix->GetNcols() || acoln < 0) {
      //Error("operator()(Int_t","Requested element %d outside range : %d - %d",i,
            //this->fMatrix->GetColLwb(),this->fMatrix->GetColLwb()+this->fMatrix->GetNcols());
      return TMatrixTBase<Element>::NaNValue();
   }

   Int_t index = TMath::BinarySearch(this->fNindex,this->fColPtr,acoln);
   if (index >= 0 && this->fColPtr[index] == acoln)
      return (const_cast<Element*>(this->fDataPtr))[index];
   else {
      TMatrixTSparse<Element> *mt = const_cast<TMatrixTSparse<Element> *>(this->fMatrix);
      const Int_t row = this->fRowInd+mt->GetRowLwb();
      Element val = 0.;
      mt->InsertRow(row,i,&val,1);
      const Int_t sIndex = mt->GetRowIndexArray()[this->fRowInd];
      const Int_t eIndex = mt->GetRowIndexArray()[this->fRowInd+1];
      this->fNindex  = eIndex-sIndex;
      this->fColPtr  = mt->GetColIndexArray()+sIndex;
      this->fDataPtr = mt->GetMatrixArray()+sIndex;
      index = TMath::BinarySearch(this->fNindex,this->fColPtr,acoln);
      if (index >= 0 && this->fColPtr[index] == acoln)
         return (const_cast<Element*>(this->fDataPtr))[index];
      else {
         //Error("operator()(Int_t","Insert row failed");
         return TMatrixTBase<Element>::NaNValue();
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every non-zero (!) element of the matrix row.

template<class Element>
void TMatrixTSparseRow<Element>::operator=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fDataPtr);
   for ( ; rp < this->fDataPtr+this->fNindex; rp++)
      *rp = val;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every non-zero (!) element of the matrix row.

template<class Element>
void TMatrixTSparseRow<Element>::operator+=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fDataPtr);
   for ( ; rp < this->fDataPtr+this->fNindex; rp++)
      *rp += val;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix row by val.

template<class Element>
void TMatrixTSparseRow<Element>::operator*=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   Element *rp = const_cast<Element *>(this->fDataPtr);
   for ( ; rp < this->fDataPtr+this->fNindex; rp++)
      *rp *= val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTSparseRow<Element>::operator=(const TMatrixTSparseRow_const<Element> &mr)
{
   const TMatrixTBase<Element> *mt = mr.GetMatrix();
   if (this->fMatrix == mt) return;

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fMatrix->GetColLwb() != mt->GetColLwb() || this->fMatrix->GetNcols() != mt->GetNcols()) {
      //Error("operator=(const TMatrixTSparseRow_const &)","matrix rows not compatible");
      return;
   }

   const Int_t ncols = this->fMatrix->GetNcols();
   const Int_t row1  = this->fRowInd+this->fMatrix->GetRowLwb();
   const Int_t row2  = mr.GetRowIndex()+mt->GetRowLwb();
   const Int_t col   = this->fMatrix->GetColLwb();

   TVectorT<Element> v(ncols);
   mt->ExtractRow(row2,col,v.GetMatrixArray());
   const_cast<TMatrixTSparse<Element> *>(this->fMatrix)->InsertRow(row1,col,v.GetMatrixArray());

   const Int_t sIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd];
   const Int_t eIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd+1];
   this->fNindex  = eIndex-sIndex;
   this->fColPtr  = this->fMatrix->GetColIndexArray()+sIndex;
   this->fDataPtr = this->fMatrix->GetMatrixArray()+sIndex;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a vector to a matrix row. The vector is considered row-vector
/// to allow the assignment in the strict sense.

template<class Element>
void TMatrixTSparseRow<Element>::operator=(const TVectorT<Element> &vec)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(vec.IsValid());

   if (this->fMatrix->GetColLwb() != vec.GetLwb() || this->fMatrix->GetNcols() != vec.GetNrows()) {
      //Error("operator=(const TVectorT &)","vector length != matrix-row length");
      return;
   }

   const Element *vp = vec.GetMatrixArray();
   const Int_t row = this->fRowInd+this->fMatrix->GetRowLwb();
   const Int_t col = this->fMatrix->GetColLwb();
   const_cast<TMatrixTSparse<Element> *>(this->fMatrix)->InsertRow(row,col,vp,vec.GetNrows());

   const Int_t sIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd];
   const Int_t eIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd+1];
   this->fNindex  = eIndex-sIndex;
   this->fColPtr  = this->fMatrix->GetColIndexArray()+sIndex;
   this->fDataPtr = this->fMatrix->GetMatrixArray()+sIndex;
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the matrix row the corresponding element of row r.

template<class Element>
void TMatrixTSparseRow<Element>::operator+=(const TMatrixTSparseRow_const<Element> &r)
{
   const TMatrixTBase<Element> *mt = r.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fMatrix->GetColLwb() != mt->GetColLwb() || this->fMatrix->GetNcols() != mt->GetNcols()) {
      //Error("operator+=(const TMatrixTRow_const &)","different row lengths");
      return;
   }

   const Int_t ncols = this->fMatrix->GetNcols();
   const Int_t row1  = this->fRowInd+this->fMatrix->GetRowLwb();
   const Int_t row2  = r.GetRowIndex()+mt->GetRowLwb();
   const Int_t col   = this->fMatrix->GetColLwb();

   TVectorT<Element> v1(ncols);
   TVectorT<Element> v2(ncols);
   this->fMatrix->ExtractRow(row1,col,v1.GetMatrixArray());
   mt           ->ExtractRow(row2,col,v2.GetMatrixArray());
   v1 += v2;
   const_cast<TMatrixTSparse<Element> *>(this->fMatrix)->InsertRow(row1,col,v1.GetMatrixArray());

   const Int_t sIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd];
   const Int_t eIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd+1];
   this->fNindex  = eIndex-sIndex;
   this->fColPtr  = this->fMatrix->GetColIndexArray()+sIndex;
   this->fDataPtr = this->fMatrix->GetMatrixArray()+sIndex;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix row with the
/// corresponding element of row r.

template<class Element>
void TMatrixTSparseRow<Element>::operator*=(const TMatrixTSparseRow_const<Element> &r)
{
   const TMatrixTBase<Element> *mt = r.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fMatrix->GetColLwb() != mt->GetColLwb() || this->fMatrix->GetNcols() != mt->GetNcols()) {
      //Error("operator+=(const TMatrixTRow_const &)","different row lengths");
      return;
   }

   const Int_t ncols = this->fMatrix->GetNcols();
   const Int_t row1  = r.GetRowIndex()+mt->GetRowLwb();
   const Int_t row2  = r.GetRowIndex()+mt->GetRowLwb();
   const Int_t col   = this->fMatrix->GetColLwb();

   TVectorT<Element> v1(ncols);
   TVectorT<Element> v2(ncols);
   this->fMatrix->ExtractRow(row1,col,v1.GetMatrixArray());
   mt           ->ExtractRow(row2,col,v2.GetMatrixArray());

   ElementMult(v1,v2);
   const_cast<TMatrixTSparse<Element> *>(this->fMatrix)->InsertRow(row1,col,v1.GetMatrixArray());

   const Int_t sIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd];
   const Int_t eIndex = this->fMatrix->GetRowIndexArray()[this->fRowInd+1];
   this->fNindex  = eIndex-sIndex;
   this->fColPtr  = this->fMatrix->GetColIndexArray()+sIndex;
   this->fDataPtr = this->fMatrix->GetMatrixArray()+sIndex;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTSparseDiag_const<Element>::TMatrixTSparseDiag_const(const TMatrixTSparse<Element> &matrix)
{
   //R__ASSERT(matrix.IsValid());

   fMatrix  = &matrix;
   fNdiag   = TMath::Min(matrix.GetNrows(),matrix.GetNcols());
   fDataPtr = matrix.GetMatrixArray();
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Element TMatrixTSparseDiag_const<Element>::operator()(Int_t i) const
{
  //R__ASSERT(fMatrix->IsValid());
  if (i < fNdiag && i >= 0) {
     const Int_t   * const pR = fMatrix->GetRowIndexArray();
     const Int_t   * const pC = fMatrix->GetColIndexArray();
     const Element * const pD = fMatrix->GetMatrixArray();
     const Int_t sIndex = pR[i];
     const Int_t eIndex = pR[i+1];
     const Int_t index = TMath::BinarySearch(eIndex-sIndex,pC+sIndex,i)+sIndex;
     if (index >= sIndex && pC[index] == i) return pD[index];
     else                                   return 0.0;
  } else {
     //Error("operator()","Request diagonal(%d) outside matrix range of 0 - %d",i,fNdiag);
     return 0.0;
  }
  return 0.0;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTSparseDiag<Element>::TMatrixTSparseDiag(TMatrixTSparse<Element> &matrix)
                   :TMatrixTSparseDiag_const<Element>(matrix)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor

template<class Element>
TMatrixTSparseDiag<Element>::TMatrixTSparseDiag(const TMatrixTSparseDiag<Element> &md)
                  : TMatrixTSparseDiag_const<Element>(md)
{
   *this = md;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Element TMatrixTSparseDiag<Element>::operator()(Int_t i) const
{
    //R__ASSERT(this->fMatrix->IsValid());
    if (i < this->fNdiag && i >= 0) {
       const Int_t   * const pR = this->fMatrix->GetRowIndexArray();
       const Int_t   * const pC = this->fMatrix->GetColIndexArray();
       const Element * const pD = this->fMatrix->GetMatrixArray();
       const Int_t sIndex = pR[i];
       const Int_t eIndex = pR[i+1];
       const Int_t index = TMath::BinarySearch(eIndex-sIndex,pC+sIndex,i)+sIndex;
       if (index >= sIndex && pC[index] == i) return pD[index];
       else                                   return 0.0;
    } else {
       //Error("operator()","Request diagonal(%d) outside matrix range of 0 - %d",i,this->fNdiag);
       return 0.0;
    }
    return 0.0;
 }

////////////////////////////////////////////////////////////////////////////////
/// operator() : pick element diag(i)

template<class Element>
Element &TMatrixTSparseDiag<Element>::operator()(Int_t i)
{
   //R__ASSERT(this->fMatrix->IsValid());

   if (i < 0 || i >= this->fNdiag) {
      //Error("operator()(Int_t","Requested element %d outside range : 0 - %d",i,this->fNdiag);
      return (const_cast<Element*>(this->fDataPtr))[0];
   }

   TMatrixTSparse<Element> *mt = const_cast<TMatrixTSparse<Element> *>(this->fMatrix);
   const Int_t *pR = mt->GetRowIndexArray();
   const Int_t *pC = mt->GetColIndexArray();
   Int_t sIndex = pR[i];
   Int_t eIndex = pR[i+1];
   Int_t index = TMath::BinarySearch(eIndex-sIndex,pC+sIndex,i)+sIndex;
   if (index >= sIndex && pC[index] == i)
      return (const_cast<Element*>(this->fDataPtr))[index];
   else {
      const Int_t row = i+mt->GetRowLwb();
      const Int_t col = i+mt->GetColLwb();
      Element val = 0.;
      mt->InsertRow(row,col,&val,1);
      this->fDataPtr = mt->GetMatrixArray();
      pR = mt->GetRowIndexArray();
      pC = mt->GetColIndexArray();
      sIndex = pR[i];
      eIndex = pR[i+1];
      index = TMath::BinarySearch(eIndex-sIndex,pC+sIndex,i)+sIndex;
      if (index >= sIndex && pC[index] == i)
         return (const_cast<Element*>(this->fDataPtr))[index];
      else {
         //Error("operator()(Int_t","Insert row failed");
         return (const_cast<Element*>(this->fDataPtr))[0];
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix diagonal.

template<class Element>
void TMatrixTSparseDiag<Element>::operator=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   for (Int_t i = 0; i < this->fNdiag; i++)
      (*this)(i) = val;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the matrix diagonal.

template<class Element>
void TMatrixTSparseDiag<Element>::operator+=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   for (Int_t i = 0; i < this->fNdiag; i++)
      (*this)(i) += val;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix diagonal by val.

template<class Element>
void TMatrixTSparseDiag<Element>::operator*=(Element val)
{
   //R__ASSERT(this->fMatrix->IsValid());
   for (Int_t i = 0; i < this->fNdiag; i++)
      (*this)(i) *= val;
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

template<class Element>
void TMatrixTSparseDiag<Element>::operator=(const TMatrixTSparseDiag_const<Element> &md)
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();
   if (this->fMatrix == mt) return;

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fNdiag != md.GetNdiags()) {
      //Error("operator=(const TMatrixTSparseDiag_const &)","matrix-diagonal's different length");
      return;
   }

   for (Int_t i = 0; i < this->fNdiag; i++)
      (*this)(i) = md(i);
}

////////////////////////////////////////////////////////////////////////////////
/// Assign a vector to the matrix diagonal.

template<class Element>
void TMatrixTSparseDiag<Element>::operator=(const TVectorT<Element> &vec)
{
   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(vec.IsValid());

   if (this->fNdiag != vec.GetNrows()) {
      //Error("operator=(const TVectorT &)","vector length != matrix-diagonal length");
      return;
   }

   const Element *vp = vec.GetMatrixArray();
   for (Int_t i = 0; i < this->fNdiag; i++)
      (*this)(i) = vp[i];
}

////////////////////////////////////////////////////////////////////////////////
/// Add to every element of the matrix diagonal the
/// corresponding element of diagonal md.

template<class Element>
void TMatrixTSparseDiag<Element>::operator+=(const TMatrixTSparseDiag_const<Element> &md)
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fNdiag != md.GetNdiags()) {
      //Error("operator+=(const TMatrixTSparseDiag_const &)","matrix-diagonal's different length");
      return;
   }

   for (Int_t i = 0; i < this->fNdiag; i++)
      (*this)(i) += md(i);
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix diagonal with the
/// corresponding element of diagonal md.

template<class Element>
void TMatrixTSparseDiag<Element>::operator*=(const TMatrixTSparseDiag_const<Element> &md)
{
   const TMatrixTBase<Element> *mt = md.GetMatrix();

   //R__ASSERT(this->fMatrix->IsValid());
   //R__ASSERT(mt->IsValid());
   if (this->fNdiag != md.GetNdiags()) {
      //Error("operator*=(const TMatrixTSparseDiag_const &)","matrix-diagonal's different length");
      return;
   }

   for (Int_t i = 0; i < this->fNdiag; i++)
      (*this)(i) *= md(i);
}

////////////////////////////////////////////////////////////////////////////////
/// Random number generator [0....1] with seed ix

Double_t Drand(Double_t &ix)
{
   const Double_t a   = 16807.0;
   const Double_t b15 = 32768.0;
   const Double_t b16 = 65536.0;
   const Double_t p   = 2147483647.0;
   Double_t xhi = ix/b16;
   Int_t xhiint = (Int_t) xhi;
   xhi = xhiint;
   Double_t xalo = (ix-xhi*b16)*a;

   Double_t leftlo = xalo/b16;
   Int_t leftloint = (int) leftlo;
   leftlo = leftloint;
   Double_t fhi = xhi*a+leftlo;
   Double_t k = fhi/b15;
   Int_t kint = (Int_t) k;
   k = kint;
   ix = (((xalo-leftlo*b16)-p)+(fhi-k*b15)*b16)+k;
   if (ix < 0.0) ix = ix+p;

   return (ix*4.656612875e-10);
}

template class TMatrixTRow_const       <Float_t>;
template class TMatrixTColumn_const    <Float_t>;
template class TMatrixTDiag_const      <Float_t>;
template class TMatrixTFlat_const      <Float_t>;
template class TMatrixTSub_const       <Float_t>;
template class TMatrixTSparseRow_const <Float_t>;
template class TMatrixTSparseDiag_const<Float_t>;
template class TMatrixTRow             <Float_t>;
template class TMatrixTColumn          <Float_t>;
template class TMatrixTDiag            <Float_t>;
template class TMatrixTFlat            <Float_t>;
template class TMatrixTSub             <Float_t>;
template class TMatrixTSparseRow       <Float_t>;
template class TMatrixTSparseDiag      <Float_t>;
template class TElementActionT         <Float_t>;
template class TElementPosActionT      <Float_t>;

template class TMatrixTRow_const       <Double_t>;
template class TMatrixTColumn_const    <Double_t>;
template class TMatrixTDiag_const      <Double_t>;
template class TMatrixTFlat_const      <Double_t>;
template class TMatrixTSub_const       <Double_t>;
template class TMatrixTSparseRow_const <Double_t>;
template class TMatrixTSparseDiag_const<Double_t>;
template class TMatrixTRow             <Double_t>;
template class TMatrixTColumn          <Double_t>;
template class TMatrixTDiag            <Double_t>;
template class TMatrixTFlat            <Double_t>;
template class TMatrixTSub             <Double_t>;
template class TMatrixTSparseRow       <Double_t>;
template class TMatrixTSparseDiag      <Double_t>;
template class TElementActionT         <Double_t>;
template class TElementPosActionT      <Double_t>;

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixTSym
    \ingroup Matrix

 TMatrixTSym

 Template class of a symmetric matrix in the linear algebra package

 Note that in this implementation both matrix element m[i][j] and
 m[j][i] are updated and stored in memory . However, when making the
 object persistent only the upper right triangle is stored .

*/

//#include "TMatrixTSym.h"
//#include "TBuffer.h"
//#include "TMatrixTLazy.h"
//#include "TMatrixTSymCramerInv.h"
//#include "TDecompLU.h"
//#include "TMatrixDSymEigen.h"
//#include "TClass.h"
//#include "TMath.h"

templateClassImp(TMatrixTSym);


////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(Int_t no_rows)
{
   Allocate(no_rows,no_rows,0,0,1);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(Int_t row_lwb,Int_t row_upb)
{
   const Int_t no_rows = row_upb-row_lwb+1;
   Allocate(no_rows,no_rows,row_lwb,row_lwb,1);
}

////////////////////////////////////////////////////////////////////////////////
/// option=
///  - "F": array elements contains the matrix stored column-wise
///         like in Fortran, so a[i,j] = elements[i+no_rows*j],
///  - else it is supposed that array elements are stored row-wise
///         a[i,j] = elements[i*no_cols+j]
///
/// array elements are copied

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(Int_t no_rows,const Element *elements,Option_t *option)
{
   Allocate(no_rows,no_rows);
   SetMatrixArray(elements,option);
   if (!this->IsSymmetric()) {
      //Error("TMatrixTSym(Int_t,Element*,Option_t*)","matrix not symmetric");
   }
}

////////////////////////////////////////////////////////////////////////////////
/// array elements are copied

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(Int_t row_lwb,Int_t row_upb,const Element *elements,Option_t *option)
{
   const Int_t no_rows = row_upb-row_lwb+1;
   Allocate(no_rows,no_rows,row_lwb,row_lwb);
   SetMatrixArray(elements,option);
   if (!this->IsSymmetric()) {
      //Error("TMatrixTSym(Int_t,Int_t,Element*,Option_t*)","matrix not symmetric");
   }
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(const TMatrixTSym<Element> &another) : TMatrixTBase<Element>(another)
{
   //R__ASSERT(another.IsValid());
   Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb());
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix applying a specific operation to the prototype.
/// Example: TMatrixTSym<Element> a(10,12); ...; TMatrixTSym<Element> b(TMatrixT::kTransposed, a);
/// Supported operations are: kZero, kUnit, kTransposed, kInverted and kAtA.

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(EMatrixCreatorsOp1 op,const TMatrixTSym<Element> &prototype)
{
   //R__ASSERT(prototype.IsValid());

   switch(op) {
      case kZero:
         Allocate(prototype.GetNrows(),prototype.GetNcols(),
                  prototype.GetRowLwb(),prototype.GetColLwb(),1);
         break;

      case kUnit:
         Allocate(prototype.GetNrows(),prototype.GetNcols(),
                  prototype.GetRowLwb(),prototype.GetColLwb(),1);
         this->UnitMatrix();
         break;

      case kTransposed:
         Allocate(prototype.GetNcols(), prototype.GetNrows(),
                  prototype.GetColLwb(),prototype.GetRowLwb());
         Transpose(prototype);
         break;

      case kInverted:
      {
         Allocate(prototype.GetNrows(),prototype.GetNcols(),
                  prototype.GetRowLwb(),prototype.GetColLwb(),1);
         *this = prototype;
         // Since the user can not control the tolerance of this newly created matrix
         // we put it to the smallest possible number
         const Element oldTol = this->SetTol(std::numeric_limits<Element>::min());
         this->Invert();
         this->SetTol(oldTol);
         break;
      }

      case kAtA:
         Allocate(prototype.GetNcols(),prototype.GetNcols(),prototype.GetColLwb(),prototype.GetColLwb(),1);
         TMult(prototype);
         break;

      default:
        // Error("TMatrixTSym(EMatrixCreatorOp1,const TMatrixTSym)",
              // "operation %d not yet implemented", op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(EMatrixCreatorsOp1 op,const TMatrixT<Element> &prototype)
{
   //R__ASSERT(prototype.IsValid());

   switch(op) {
      case kAtA:
         Allocate(prototype.GetNcols(),prototype.GetNcols(),prototype.GetColLwb(),prototype.GetColLwb(),1);
         TMult(prototype);
         break;

      default:
        // Error("TMatrixTSym(EMatrixCreatorOp1,const TMatrixT)",
                //"operation %d not yet implemented", op);
        return;
   }
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(const TMatrixTSym<Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSym<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kPlus:
      {
         Allocate(a.GetNcols(),a.GetNcols(),a.GetColLwb(),a.GetColLwb(),1);
         Plus(a,b);
         break;
      }

      case kMinus:
      {
         Allocate(a.GetNcols(),a.GetNcols(),a.GetColLwb(),a.GetColLwb(),1);
         Minus(a,b);
         break;
      }

      default:
        // Error("TMatrixTSym(EMatrixCreatorOp2)", "operation %d not yet implemented", op);
        return;
   }
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element>::TMatrixTSym(const TMatrixTSymLazy<Element> &lazy_constructor)
{
   Allocate(lazy_constructor.GetRowUpb()-lazy_constructor.GetRowLwb()+1,
            lazy_constructor.GetRowUpb()-lazy_constructor.GetRowLwb()+1,
            lazy_constructor.GetRowLwb(),lazy_constructor.GetRowLwb(),1);
   lazy_constructor.FillIn(*this);
   if (!this->IsSymmetric()) {
      //Error("TMatrixTSym(TMatrixTSymLazy)","matrix not symmetric");
   }
}

////////////////////////////////////////////////////////////////////////////////
/// delete data pointer m, if it was assigned on the heap

template<class Element>
void TMatrixTSym<Element>::Delete_m(Int_t size,Element *&m)
{
   if (m) {
      if (size > this->kSizeMax)
         delete [] m;
      m = 0;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// return data pointer . if requested size <= kSizeMax, assign pointer
/// to the stack space

template<class Element>
Element* TMatrixTSym<Element>::New_m(Int_t size)
{
   if (size == 0) return 0;
   else {
      if ( size <= this->kSizeMax )
         return fDataStack;
      else {
         Element *heap = new Element[size];
         return heap;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// copy copySize doubles from *oldp to *newp . However take care of the
/// situation where both pointers are assigned to the same stack space

template<class Element>
Int_t TMatrixTSym<Element>::Memcpy_m(Element *newp,const Element *oldp,Int_t copySize,
                                     Int_t newSize,Int_t oldSize)
{
   if (copySize == 0 || oldp == newp)
      return 0;
   else {
      if ( newSize <= this->kSizeMax && oldSize <= this->kSizeMax ) {
         // both pointers are inside fDataStack, be careful with copy direction !
         if (newp > oldp) {
            for (Int_t i = copySize-1; i >= 0; i--)
               newp[i] = oldp[i];
         } else {
            for (Int_t i = 0; i < copySize; i++)
               newp[i] = oldp[i];
         }
      }
      else
         memcpy(newp,oldp,copySize*sizeof(Element));
   }
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Allocate new matrix. Arguments are number of rows, columns, row
/// lowerbound (0 default) and column lowerbound (0 default).

template<class Element>
void TMatrixTSym<Element>::Allocate(Int_t no_rows,Int_t no_cols,Int_t row_lwb,Int_t col_lwb,
                                    Int_t init,Int_t /*nr_nonzeros*/)
{
   this->fIsOwner = kTRUE;
   this->fTol     = std::numeric_limits<Element>::epsilon();
   this->fNrows   = 0;
   this->fNcols   = 0;
   this->fRowLwb  = 0;
   this->fColLwb  = 0;
   this->fNelems  = 0;
   fElements      = 0;

   if (no_rows < 0 || no_cols < 0)
   {
      //Error("Allocate","no_rows=%d no_cols=%d",no_rows,no_cols);
      //this->Invalidate();
      return;
   }

   //this->MakeValid();
   this->fNrows   = no_rows;
   this->fNcols   = no_cols;
   this->fRowLwb  = row_lwb;
   this->fColLwb  = col_lwb;
   this->fNelems  = this->fNrows*this->fNcols;

   if (this->fNelems > 0) {
      fElements = New_m(this->fNelems);
      if (init)
         memset(fElements,0,this->fNelems*sizeof(Element));
   } else
     fElements = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Symmetric matrix summation. Create a matrix C such that C = A + B.

template<class Element>
void TMatrixTSym<Element>::Plus(const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      if (!AreCompatible(a,b)) {
         //Error("Plus","matrices not compatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Plus","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Plus","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

   const Element *       ap      = a.GetMatrixArray();
   const Element *       bp      = b.GetMatrixArray();
         Element *       cp      = this->GetMatrixArray();
   const Element * const cp_last = cp+this->fNelems;

   while (cp < cp_last) {
       *cp = *ap++ + *bp++;
       cp++;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Symmetric matrix summation. Create a matrix C such that C = A + B.

template<class Element>
void TMatrixTSym<Element>::Minus(const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      if (!AreCompatible(a,b)) {
         //Error("Minus","matrices not compatible");
         return;
      }

      if (this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("Minus","this->GetMatrixArray() == a.GetMatrixArray()");
         return;
      }

      if (this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("Minus","this->GetMatrixArray() == b.GetMatrixArray()");
         return;
      }
   }

   const Element *       ap      = a.GetMatrixArray();
   const Element *       bp      = b.GetMatrixArray();
         Element *       cp      = this->GetMatrixArray();
   const Element * const cp_last = cp+this->fNelems;

   while (cp < cp_last) {
       *cp = *ap++ - *bp++;
       cp++;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix C such that C = A' * A. In other words,
/// c[i,j] = SUM{ a[k,i] * a[k,j] }.

template<class Element>
void TMatrixTSym<Element>::TMult(const TMatrixT<Element> &a)
{
   //R__ASSERT(a.IsValid());

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasTrans,CblasNoTrans,this->fNrows,this->fNcols,a.GetNrows(),
                   1.0,ap,a.GetNcols(),ap,a.GetNcols(),1.0,cp,this->fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasTrans,CblasNoTrans,fNrows,fNcols,a.GetNrows(),
                   1.0,ap,a.GetNcols(),ap,a.GetNcols(),1.0,cp,fNcols);
  //else
      //Error("TMult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t nb     = a.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = ncolsa;
  const Element * const ap = a.GetMatrixArray();
   const Element * const bp = ap;
         Element *       cp = this->GetMatrixArray();

   const Element *acp0 = ap;           // Pointer to  A[i,0];
   while (acp0 < ap+a.GetNcols()) {
      for (const Element *bcp = bp; bcp < bp+ncolsb; ) { // Pointer to the j-th column of A, Start bcp = A[0,0]
         const Element *acp = acp0;                       // Pointer to the i-th column of A, reset to A[0,i]
         Element cij = 0;
         while (bcp < bp+nb) {           // Scan the i-th column of A and
            cij += *acp * *bcp;           // the j-th col of A
            acp += ncolsa;
            bcp += ncolsb;
         }
         *cp++ = cij;
         bcp -= nb-1;                    // Set bcp to the (j+1)-th col
      }
      acp0++;                           // Set acp0 to the (i+1)-th col
   }

   //R__ASSERT(cp == this->GetMatrixArray()+this->fNelems && acp0 == ap+ncolsa);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix multiplication, with A symmetric
/// Create a matrix C such that C = A' * A = A * A = A * A'

template<class Element>
void TMatrixTSym<Element>::TMult(const TMatrixTSym<Element> &a)
{
   //R__ASSERT(a.IsValid());

#ifdef CBLAS
   const Element *ap = a.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymm (CblasRowMajor,CblasLeft,CblasUpper,this->fNrows,this->fNcols,1.0,
                   ap,a.GetNcols(),ap,a.GetNcols(),0.0,cp,this->fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymm (CblasRowMajor,CblasLeft,CblasUpper,fNrows,fNcols,1.0,
                   ap1,a.GetNcols(),ap,a.GetNcols(),0.0,cp,fNcols);
   //else
      //Error("TMult","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t nb     = a.GetNoElements();
   const Int_t ncolsa = a.GetNcols();
   const Int_t ncolsb = ncolsa;
   const Element * const ap = a.GetMatrixArray();
   const Element * const bp = ap;
         Element *       cp = this->GetMatrixArray();

   const Element *acp0 = ap;           // Pointer to  A[i,0];
   while (acp0 < ap+a.GetNcols()) {
      for (const Element *bcp = bp; bcp < bp+ncolsb; ) { // Pointer to the j-th column of A, Start bcp = A[0,0]
         const Element *acp = acp0;                       // Pointer to the i-th column of A, reset to A[0,i]
         Element cij = 0;
         while (bcp < bp+nb) {           // Scan the i-th column of A and
            cij += *acp * *bcp;           // the j-th col of A
            acp += ncolsa;
            bcp += ncolsb;
         }
         *cp++ = cij;
         bcp -= nb-1;                    // Set bcp to the (j+1)-th col
      }
      acp0++;                           // Set acp0 to the (i+1)-th col
   }

   //R__ASSERT(cp == this->GetMatrixArray()+this->fNelems && acp0 == ap+ncolsa);
#endif
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::Use(Int_t row_lwb,Int_t row_upb,Element *data)
{
   if (gMatrixCheck && row_upb < row_lwb)
   {
      //Error("Use","row_upb=%d < row_lwb=%d",row_upb,row_lwb);
      return *this;
   }

   this->Clear();
   this->fNrows    = row_upb-row_lwb+1;
   this->fNcols    = this->fNrows;
   this->fRowLwb   = row_lwb;
   this->fColLwb   = row_lwb;
   this->fNelems   = this->fNrows*this->fNcols;
   fElements = data;
   this->fIsOwner  = kFALSE;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Get submatrix [row_lwb..row_upb][row_lwb..row_upb]; The indexing range of the
/// returned matrix depends on the argument option:
///
/// option == "S" : return [0..row_upb-row_lwb+1][0..row_upb-row_lwb+1] (default)
/// else          : return [row_lwb..row_upb][row_lwb..row_upb]

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::GetSub(Int_t row_lwb,Int_t row_upb,
                                                   TMatrixTSym<Element> &target,Option_t *option) const
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_lwb out of bounds");
         return target;
      }
      if (row_upb < this->fRowLwb || row_upb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_upb out of bounds");
         return target;
      }
      if (row_upb < row_lwb) {
         //Error("GetSub","row_upb < row_lwb");
         return target;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t shift = (opt.Contains("S")) ? 1 : 0;

   Int_t row_lwb_sub;
   Int_t row_upb_sub;
   if (shift) {
      row_lwb_sub = 0;
      row_upb_sub = row_upb-row_lwb;
   } else {
      row_lwb_sub = row_lwb;
      row_upb_sub = row_upb;
   }

   target.ResizeTo(row_lwb_sub,row_upb_sub,row_lwb_sub,row_upb_sub);
   const Int_t nrows_sub = row_upb_sub-row_lwb_sub+1;

   if (target.GetRowIndexArray() && target.GetColIndexArray()) {
      for (Int_t irow = 0; irow < nrows_sub; irow++) {
         for (Int_t icol = 0; icol < nrows_sub; icol++) {
            target(irow+row_lwb_sub,icol+row_lwb_sub) = (*this)(row_lwb+irow,row_lwb+icol);
         }
      }
   } else {
      const Element *ap = this->GetMatrixArray()+(row_lwb-this->fRowLwb)*this->fNrows+(row_lwb-this->fRowLwb);
            Element *bp = target.GetMatrixArray();

      for (Int_t irow = 0; irow < nrows_sub; irow++) {
         const Element *ap_sub = ap;
         for (Int_t icol = 0; icol < nrows_sub; icol++) {
            *bp++ = *ap_sub++;
         }
         ap += this->fNrows;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Get submatrix [row_lwb..row_upb][col_lwb..col_upb]; The indexing range of the
/// returned matrix depends on the argument option:
///
/// option == "S" : return [0..row_upb-row_lwb+1][0..col_upb-col_lwb+1] (default)
/// else          : return [row_lwb..row_upb][col_lwb..col_upb]

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::GetSub(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                    TMatrixTBase<Element> &target,Option_t *option) const
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_lwb out of bounds");
         return target;
      }
      if (col_lwb < this->fColLwb || col_lwb > this->fColLwb+this->fNcols-1) {
         //Error("GetSub","col_lwb out of bounds");
         return target;
      }
      if (row_upb < this->fRowLwb || row_upb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_upb out of bounds");
         return target;
      }
      if (col_upb < this->fColLwb || col_upb > this->fColLwb+this->fNcols-1) {
         //Error("GetSub","col_upb out of bounds");
         return target;
      }
      if (row_upb < row_lwb || col_upb < col_lwb) {
         //Error("GetSub","row_upb < row_lwb || col_upb < col_lwb");
         return target;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t shift = (opt.Contains("S")) ? 1 : 0;

   const Int_t row_lwb_sub = (shift) ? 0               : row_lwb;
   const Int_t row_upb_sub = (shift) ? row_upb-row_lwb : row_upb;
   const Int_t col_lwb_sub = (shift) ? 0               : col_lwb;
   const Int_t col_upb_sub = (shift) ? col_upb-col_lwb : col_upb;

   target.ResizeTo(row_lwb_sub,row_upb_sub,col_lwb_sub,col_upb_sub);
   const Int_t nrows_sub = row_upb_sub-row_lwb_sub+1;
   const Int_t ncols_sub = col_upb_sub-col_lwb_sub+1;

   if (target.GetRowIndexArray() && target.GetColIndexArray()) {
      for (Int_t irow = 0; irow < nrows_sub; irow++) {
         for (Int_t icol = 0; icol < ncols_sub; icol++) {
            target(irow+row_lwb_sub,icol+col_lwb_sub) = (*this)(row_lwb+irow,col_lwb+icol);
         }
      }
   } else {
      const Element *ap = this->GetMatrixArray()+(row_lwb-this->fRowLwb)*this->fNcols+(col_lwb-this->fColLwb);
            Element *bp = target.GetMatrixArray();

      for (Int_t irow = 0; irow < nrows_sub; irow++) {
         const Element *ap_sub = ap;
         for (Int_t icol = 0; icol < ncols_sub; icol++) {
            *bp++ = *ap_sub++;
         }
         ap += this->fNcols;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Insert matrix source starting at [row_lwb][row_lwb], thereby overwriting the part
/// [row_lwb..row_lwb+nrows_source][row_lwb..row_lwb+nrows_source];

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::SetSub(Int_t row_lwb,const TMatrixTBase<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());

      if (!source.IsSymmetric()) {
         //Error("SetSub","source matrix is not symmetric");
         return *this;
      }
      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("SetSub","row_lwb outof bounds");
         return *this;
      }
      if (row_lwb+source.GetNrows() > this->fRowLwb+this->fNrows) {
         //Error("SetSub","source matrix too large");
         return *this;
      }
   }

   const Int_t nRows_source = source.GetNrows();

   if (source.GetRowIndexArray() && source.GetColIndexArray()) {
      const Int_t rowlwb_s = source.GetRowLwb();
      for (Int_t irow = 0; irow < nRows_source; irow++) {
         for (Int_t icol = 0; icol < nRows_source; icol++) {
            (*this)(row_lwb+irow,row_lwb+icol) = source(rowlwb_s+irow,rowlwb_s+icol);
         }
      }
   } else {
      const Element *bp = source.GetMatrixArray();
            Element *ap = this->GetMatrixArray()+(row_lwb-this->fRowLwb)*this->fNrows+(row_lwb-this->fRowLwb);

      for (Int_t irow = 0; irow < nRows_source; irow++) {
         Element *ap_sub = ap;
         for (Int_t icol = 0; icol < nRows_source; icol++) {
            *ap_sub++ = *bp++;
         }
         ap += this->fNrows;
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Insert matrix source starting at [row_lwb][col_lwb] in a symmetric fashion, thereby overwriting the part
/// [row_lwb..row_lwb+nrows_source][row_lwb..row_lwb+nrows_source];

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::SetSub(Int_t row_lwb,Int_t col_lwb,const TMatrixTBase<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());

      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("SetSub","row_lwb out of bounds");
         return *this;
      }
      if (col_lwb < this->fColLwb || col_lwb > this->fColLwb+this->fNcols-1) {
         //Error("SetSub","col_lwb out of bounds");
         return *this;
      }

      if (row_lwb+source.GetNrows() > this->fRowLwb+this->fNrows || col_lwb+source.GetNcols() > this->fRowLwb+this->fNrows) {
         //Error("SetSub","source matrix too large");
         return *this;
      }
      if (col_lwb+source.GetNcols() > this->fRowLwb+this->fNrows || row_lwb+source.GetNrows() > this->fRowLwb+this->fNrows) {
         //Error("SetSub","source matrix too large");
         return *this;
      }
   }

   const Int_t nRows_source = source.GetNrows();
   const Int_t nCols_source = source.GetNcols();

   const Int_t rowlwb_s = source.GetRowLwb();
   const Int_t collwb_s = source.GetColLwb();
   if (row_lwb >= col_lwb) {
      // lower triangle
      Int_t irow;
      for (irow = 0; irow < nRows_source; irow++) {
         for (Int_t icol = 0; col_lwb+icol <= row_lwb+irow &&
                                icol < nCols_source; icol++) {
            (*this)(row_lwb+irow,col_lwb+icol) = source(irow+rowlwb_s,icol+collwb_s);
         }
      }

      // upper triangle
      for (irow = 0; irow < nCols_source; irow++) {
         for (Int_t icol = nRows_source-1; row_lwb+icol > irow+col_lwb &&
                                 icol >= 0; icol--) {
            (*this)(col_lwb+irow,row_lwb+icol) = source(icol+rowlwb_s,irow+collwb_s);
         }
      }
   } else {

   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::SetMatrixArray(const Element *data,Option_t *option)
{
   TMatrixTBase<Element>::SetMatrixArray(data,option);
   if (!this->IsSymmetric()) {
      //Error("SetMatrixArray","Matrix is not symmetric after Set");
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::Shift(Int_t row_shift,Int_t col_shift)
{
   if (row_shift != col_shift) {
      //Error("Shift","row_shift != col_shift");
      return *this;
   }
   return TMatrixTBase<Element>::Shift(row_shift,col_shift);
}

////////////////////////////////////////////////////////////////////////////////
/// Set size of the matrix to nrows x ncols
/// New dynamic elements are created, the overlapping part of the old ones are
/// copied to the new structures, then the old elements are deleted.

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::ResizeTo(Int_t nrows,Int_t ncols,Int_t /*nr_nonzeros*/)
{
   //R__ASSERT(this->IsValid());
   if (!this->fIsOwner) {
      //Error("ResizeTo(Int_t,Int_t)","Not owner of data array,cannot resize");
      return *this;
   }

   if (nrows != ncols) {
      //Error("ResizeTo(Int_t,Int_t)","nrows != ncols");
      return *this;
   }

   if (this->fNelems > 0) {
      if (this->fNrows == nrows && this->fNcols == ncols)
         return *this;
      else if (nrows == 0 || ncols == 0) {
         this->fNrows = nrows; this->fNcols = ncols;
         this->Clear();
         return *this;
      }

      Element     *elements_old = GetMatrixArray();
      const Int_t  nelems_old   = this->fNelems;
      const Int_t  nrows_old    = this->fNrows;
      const Int_t  ncols_old    = this->fNcols;

      Allocate(nrows,ncols);
      //R__ASSERT(this->IsValid());

      Element *elements_new = GetMatrixArray();
      // new memory should be initialized but be careful not to wipe out the stack
      // storage. Initialize all when old or new storage was on the heap
      if (this->fNelems > this->kSizeMax || nelems_old > this->kSizeMax)
         memset(elements_new,0,this->fNelems*sizeof(Element));
      else if (this->fNelems > nelems_old)
         memset(elements_new+nelems_old,0,(this->fNelems-nelems_old)*sizeof(Element));

      // Copy overlap
      const Int_t ncols_copy = TMath::Min(this->fNcols,ncols_old);
      const Int_t nrows_copy = TMath::Min(this->fNrows,nrows_old);

      const Int_t nelems_new = this->fNelems;
      if (ncols_old < this->fNcols) {
         for (Int_t i = nrows_copy-1; i >= 0; i--) {
            Memcpy_m(elements_new+i*this->fNcols,elements_old+i*ncols_old,ncols_copy,
                     nelems_new,nelems_old);
            if (this->fNelems <= this->kSizeMax && nelems_old <= this->kSizeMax)
               memset(elements_new+i*this->fNcols+ncols_copy,0,(this->fNcols-ncols_copy)*sizeof(Element));
         }
      } else {
         for (Int_t i = 0; i < nrows_copy; i++)
            Memcpy_m(elements_new+i*this->fNcols,elements_old+i*ncols_old,ncols_copy,
                     nelems_new,nelems_old);
      }

      Delete_m(nelems_old,elements_old);
   } else {
     Allocate(nrows,ncols,0,0,1);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set size of the matrix to [row_lwb:row_upb] x [col_lwb:col_upb]
/// New dynamic elements are created, the overlapping part of the old ones are
/// copied to the new structures, then the old elements are deleted.

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::ResizeTo(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                      Int_t /*nr_nonzeros*/)
{
   //R__ASSERT(this->IsValid());
   if (!this->fIsOwner) {
      //Error("ResizeTo(Int_t,Int_t,Int_t,Int_t)","Not owner of data array,cannot resize");
      return *this;
   }

   if (row_lwb != col_lwb) {
      //Error("ResizeTo(Int_t,Int_t,Int_t,Int_t)","row_lwb != col_lwb");
      return *this;
   }
   if (row_upb != col_upb) {
      //Error("ResizeTo(Int_t,Int_t,Int_t,Int_t)","row_upb != col_upb");
      return *this;
   }

   const Int_t new_nrows = row_upb-row_lwb+1;
   const Int_t new_ncols = col_upb-col_lwb+1;

   if (this->fNelems > 0) {

      if (this->fNrows  == new_nrows  && this->fNcols  == new_ncols &&
          this->fRowLwb == row_lwb    && this->fColLwb == col_lwb)
          return *this;
      else if (new_nrows == 0 || new_ncols == 0) {
         this->fNrows = new_nrows; this->fNcols = new_ncols;
         this->fRowLwb = row_lwb; this->fColLwb = col_lwb;
         this->Clear();
         return *this;
      }

      Element    *elements_old = GetMatrixArray();
      const Int_t  nelems_old   = this->fNelems;
      const Int_t  nrows_old    = this->fNrows;
      const Int_t  ncols_old    = this->fNcols;
      const Int_t  rowLwb_old   = this->fRowLwb;
      const Int_t  colLwb_old   = this->fColLwb;

      Allocate(new_nrows,new_ncols,row_lwb,col_lwb);
      //R__ASSERT(this->IsValid());

      Element *elements_new = GetMatrixArray();
      // new memory should be initialized but be careful ot to wipe out the stack
      // storage. Initialize all when old or new storage was on the heap
      if (this->fNelems > this->kSizeMax || nelems_old > this->kSizeMax)
         memset(elements_new,0,this->fNelems*sizeof(Element));
      else if (this->fNelems > nelems_old)
         memset(elements_new+nelems_old,0,(this->fNelems-nelems_old)*sizeof(Element));

      // Copy overlap
      const Int_t rowLwb_copy = TMath::Max(this->fRowLwb,rowLwb_old);
      const Int_t colLwb_copy = TMath::Max(this->fColLwb,colLwb_old);
      const Int_t rowUpb_copy = TMath::Min(this->fRowLwb+this->fNrows-1,rowLwb_old+nrows_old-1);
      const Int_t colUpb_copy = TMath::Min(this->fColLwb+this->fNcols-1,colLwb_old+ncols_old-1);

      const Int_t nrows_copy = rowUpb_copy-rowLwb_copy+1;
      const Int_t ncols_copy = colUpb_copy-colLwb_copy+1;

      if (nrows_copy > 0 && ncols_copy > 0) {
         const Int_t colOldOff = colLwb_copy-colLwb_old;
         const Int_t colNewOff = colLwb_copy-this->fColLwb;
         if (ncols_old < this->fNcols) {
            for (Int_t i = nrows_copy-1; i >= 0; i--) {
               const Int_t iRowOld = rowLwb_copy+i-rowLwb_old;
               const Int_t iRowNew = rowLwb_copy+i-this->fRowLwb;
               Memcpy_m(elements_new+iRowNew*this->fNcols+colNewOff,
                        elements_old+iRowOld*ncols_old+colOldOff,ncols_copy,this->fNelems,nelems_old);
               if (this->fNelems <= this->kSizeMax && nelems_old <= this->kSizeMax)
                  memset(elements_new+iRowNew*this->fNcols+colNewOff+ncols_copy,0,
                         (this->fNcols-ncols_copy)*sizeof(Element));
            }
         } else {
             for (Int_t i = 0; i < nrows_copy; i++) {
                const Int_t iRowOld = rowLwb_copy+i-rowLwb_old;
                const Int_t iRowNew = rowLwb_copy+i-this->fRowLwb;
                Memcpy_m(elements_new+iRowNew*this->fNcols+colNewOff,
                         elements_old+iRowOld*ncols_old+colOldOff,ncols_copy,this->fNelems,nelems_old);
            }
         }
      }

      Delete_m(nelems_old,elements_old);
   } else {
      Allocate(new_nrows,new_ncols,row_lwb,col_lwb,1);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Double_t TMatrixTSym<Element>::Determinant() const
{
   const TMatrixT<Element> &tmp = *this;
   TDecompLU lu(tmp,this->fTol);
   Double_t d1,d2;
   lu.Det(d1,d2);
   return d1*TMath::Power(2.0,d2);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
void TMatrixTSym<Element>::Determinant(Double_t &d1,Double_t &d2) const
{
   const TMatrixT<Element> &tmp = *this;
   TDecompLU lu(tmp,this->fTol);
   lu.Det(d1,d2);
}

////////////////////////////////////////////////////////////////////////////////
/// Invert the matrix and calculate its determinant
/// Notice that the LU decomposition is used instead of Bunch-Kaufman
/// Bunch-Kaufman guarantees a symmetric inverted matrix but is slower than LU .
/// The user can access Bunch-Kaufman through the TDecompBK class .

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::Invert(Double_t *det)
{
   //R__ASSERT(this->IsValid());
   TMatrixD tmp(*this);
   if (TDecompLU::InvertLU(tmp,Double_t(this->fTol),det)) {
      const Double_t *p1 = tmp.GetMatrixArray();
            Element  *p2 = this->GetMatrixArray();
      for (Int_t i = 0; i < this->GetNoElements(); i++)
         p2[i] = p1[i];
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Invert the matrix and calculate its determinant

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::InvertFast(Double_t *det)
{
   //R__ASSERT(this->IsValid());

   const Char_t nRows = Char_t(this->GetNrows());
   switch (nRows) {
      case 1:
      {
         Element *pM = this->GetMatrixArray();
         if (*pM == 0.) {
            //Error("InvertFast","matrix is singular");
            *det = 0;
         } else {
            *det = *pM;
            *pM = 1.0/(*pM);
         }
         return *this;
      }
      case 2:
      {
         TMatrixTSymCramerInv::Inv2x2<Element>(*this,det);
         return *this;
      }
      case 3:
      {
         TMatrixTSymCramerInv::Inv3x3<Element>(*this,det);
         return *this;
      }
      case 4:
      {
         TMatrixTSymCramerInv::Inv4x4<Element>(*this,det);
         return *this;
      }
      case 5:
      {
         TMatrixTSymCramerInv::Inv5x5<Element>(*this,det);
         return *this;
      }
      case 6:
      {
         TMatrixTSymCramerInv::Inv6x6<Element>(*this,det);
         return *this;
      }

      default:
      {
         TMatrixD tmp(*this);
         if (TDecompLU::InvertLU(tmp,Double_t(this->fTol),det)) {
            const Double_t *p1 = tmp.GetMatrixArray();
                  Element  *p2 = this->GetMatrixArray();
            for (Int_t i = 0; i < this->GetNoElements(); i++)
               p2[i] = p1[i];
         }
         return *this;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Transpose a matrix.

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::Transpose(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());

      if (this->fNrows != source.GetNcols() || this->fRowLwb != source.GetColLwb())
      {
         //Error("Transpose","matrix has wrong shape");
         return *this;
      }
   }

   *this = source;
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Perform a rank 1 operation on the matrix:
///     A += alpha * v * v^T

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::Rank1Update(const TVectorT<Element> &v,Element alpha)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(v.IsValid());
      if (v.GetNoElements() < this->fNrows) {
         //Error("Rank1Update","vector too short");
         return *this;
      }
   }

   const Element * const pv = v.GetMatrixArray();
         Element *trp = this->GetMatrixArray(); // pointer to UR part and diagonal, traverse row-wise
         Element *tcp = trp;                    // pointer to LL part,              traverse col-wise
   for (Int_t i = 0; i < this->fNrows; i++) {
      trp += i;               // point to [i,i]
      tcp += i*this->fNcols;  // point to [i,i]
      const Element tmp = alpha*pv[i];
      for (Int_t j = i; j < this->fNcols; j++) {
         if (j > i) *tcp += tmp*pv[j];
         *trp++ += tmp*pv[j];
         tcp += this->fNcols;
      }
      tcp -= this->fNelems-1; // point to [0,i]
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate B * (*this) * B^T , final matrix will be (nrowsb x nrowsb)
/// This is a similarity transform when B is orthogonal . It is more
/// efficient than applying the actual multiplication because this
/// routine realizes that  the final matrix is symmetric .

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::Similarity(const TMatrixT<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(b.IsValid());
      if (this->fNcols != b.GetNcols() || this->fColLwb != b.GetColLwb()) {
         //Error("Similarity(const TMatrixT &)","matrices incompatible");
         return *this;
      }
   }

   const Int_t ncolsa  = this->fNcols;
   const Int_t nb      = b.GetNoElements();
   const Int_t nrowsb  = b.GetNrows();
   const Int_t ncolsb  = b.GetNcols();

   const Element * const bp = b.GetMatrixArray();

   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *bap = work;
   if (nrowsb*ncolsa > kWorkMax) {
      isAllocated = kTRUE;
      bap = new Element[nrowsb*ncolsa];
   }

   AMultB(bp,nb,ncolsb,this->fElements,this->fNelems,this->fNcols,bap);

   if (nrowsb != this->fNrows)
      this->ResizeTo(nrowsb,nrowsb);

#ifdef CBLAS
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasNoTrans,CblasTrans,this->fNrows,this->fNcols,ba.GetNcols(),
                   1.0,bap,ba.GetNcols(),bp,b.GetNcols(),1.0,cp,this->fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasNoTrans,CblasTrans,this->fNrows,this->fNcols,ba.GetNcols(),
                   1.0,bap,ba.GetNcols(),bp,b.GetNcols(),1.0,cp,this->fNcols);
   //else
      //Error("Similarity","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t nba     = nrowsb*ncolsa;
   const Int_t ncolsba = ncolsa;
   const Element *       bi1p = bp;
         Element *       cp   = this->GetMatrixArray();
         Element * const cp0  = cp;

   Int_t ishift = 0;
   const Element *barp0 = bap;
   while (barp0 < bap+nba) {
      const Element *brp0 = bi1p;
      while (brp0 < bp+nb) {
         const Element *barp = barp0;
         const Element *brp  = brp0;
         Element cij = 0;
         while (brp < brp0+ncolsb)
            cij += *barp++ * *brp++;
         *cp++ = cij;
         brp0 += ncolsb;
      }
      barp0 += ncolsba;
      bi1p += ncolsb;
      cp += ++ishift;
   }

   //R__ASSERT(cp == cp0+this->fNelems+ishift && barp0 == bap+nba);

   cp = cp0;
   for (Int_t irow = 0; irow < this->fNrows; irow++) {
      const Int_t rowOff1 = irow*this->fNrows;
      for (Int_t icol = 0; icol < irow; icol++) {
         const Int_t rowOff2 = icol*this->fNrows;
         cp[rowOff1+icol] = cp[rowOff2+irow];
      }
   }
#endif

   if (isAllocated)
      delete [] bap;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate B * (*this) * B^T , final matrix will be (nrowsb x nrowsb)
/// This is a similarity transform when B is orthogonal . It is more
/// efficient than applying the actual multiplication because this
/// routine realizes that  the final matrix is symmetric .

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::Similarity(const TMatrixTSym<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(b.IsValid());
      if (this->fNcols != b.GetNcols() || this->fColLwb != b.GetColLwb()) {
         //Error("Similarity(const TMatrixTSym &)","matrices incompatible");
         return *this;
      }
   }

#ifdef CBLAS
   const Int_t nrowsb = b.GetNrows();
   const Int_t ncolsa = this->GetNcols();

   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *abtp = work;
   if (this->fNcols > kWorkMax) {
      isAllocated = kTRUE;
      abtp = new Element[this->fNcols];
   }

   const TMatrixT<Element> abt(*this,TMatrixT<Element>::kMultTranspose,b);

   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dsymm (CblasRowMajor,CblasLeft,CblasUpper,this->fNrows,this->fNcols,1.0,
                   bp,b.GetNcols(),abtp,abt.GetNcols(),0.0,cp,this->fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_ssymm (CblasRowMajor,CblasLeft,CblasUpper,this->fNrows,this->fNcols,1.0,
                   bp,b.GetNcols(),abtp,abt.GetNcols(),0.0,cp,this->fNcols);
   //else
      //Error("Similarity","type %s not implemented in BLAS library",typeid(Element));

   if (isAllocated)
      delete [] abtp;
#else
   const Int_t ncolsa = this->GetNcols();
   const Int_t nb     = b.GetNoElements();
   const Int_t nrowsb = b.GetNrows();
   const Int_t ncolsb = b.GetNcols();

   const Element * const bp = b.GetMatrixArray();

   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *bap = work;
   if (nrowsb*ncolsa > kWorkMax) {
      isAllocated = kTRUE;
      bap = new Element[nrowsb*ncolsa];
   }

   AMultB(bp,nb,ncolsb,this->fElements,this->fNelems,this->fNcols,bap);

   const Int_t nba     = nrowsb*ncolsa;
   const Int_t ncolsba = ncolsa;
   const Element *       bi1p = bp;
         Element *       cp   = this->GetMatrixArray();
         Element * const cp0  = cp;

   Int_t ishift = 0;
   const Element *barp0 = bap;
   while (barp0 < bap+nba) {
      const Element *brp0 = bi1p;
      while (brp0 < bp+nb) {
         const Element *barp = barp0;
         const Element *brp  = brp0;
         Element cij = 0;
         while (brp < brp0+ncolsb)
            cij += *barp++ * *brp++;
         *cp++ = cij;
         brp0 += ncolsb;
      }
      barp0 += ncolsba;
      bi1p += ncolsb;
      cp += ++ishift;
   }

   //R__ASSERT(cp == cp0+this->fNelems+ishift && barp0 == bap+nba);

   cp = cp0;
   for (Int_t irow = 0; irow < this->fNrows; irow++) {
      const Int_t rowOff1 = irow*this->fNrows;
      for (Int_t icol = 0; icol < irow; icol++) {
         const Int_t rowOff2 = icol*this->fNrows;
         cp[rowOff1+icol] = cp[rowOff2+irow];
      }
   }

   if (isAllocated)
      delete [] bap;
#endif

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate scalar v * (*this) * v^T

template<class Element>
Element TMatrixTSym<Element>::Similarity(const TVectorT<Element> &v) const
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(v.IsValid());
      if (this->fNcols != v.GetNrows() || this->fColLwb != v.GetLwb()) {
         //Error("Similarity(const TVectorT &)","vector and matrix incompatible");
         return -1.;
      }
   }

   const Element *mp = this->GetMatrixArray(); // Matrix row ptr
   const Element *vp = v.GetMatrixArray();     // vector ptr

   Element sum1 = 0;
   const Element * const vp_first = vp;
   const Element * const vp_last  = vp+v.GetNrows();
   while (vp < vp_last) {
      Element sum2 = 0;
      for (const Element *sp = vp_first; sp < vp_last; )
         sum2 += *mp++ * *sp++;
      sum1 += sum2 * *vp++;
   }

   //R__ASSERT(mp == this->GetMatrixArray()+this->GetNoElements());

   return sum1;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate B^T * (*this) * B , final matrix will be (ncolsb x ncolsb)
/// It is more efficient than applying the actual multiplication because this
/// routine realizes that  the final matrix is symmetric .

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::SimilarityT(const TMatrixT<Element> &b)
{
  if (gMatrixCheck) {
     //R__ASSERT(this->IsValid());
     //R__ASSERT(b.IsValid());
     if (this->fNrows != b.GetNrows() || this->fRowLwb != b.GetRowLwb()) {
        //Error("SimilarityT(const TMatrixT &)","matrices incompatible");
        return *this;
     }
  }

   const Int_t ncolsb = b.GetNcols();
   const Int_t ncolsa = this->GetNcols();

   Element work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Element *btap = work;
   if (ncolsb*ncolsa > kWorkMax) {
      isAllocated = kTRUE;
      btap = new Element[ncolsb*ncolsa];
   }

   TMatrixT<Element> bta; bta.Use(ncolsb,ncolsa,btap);
   bta.TMult(b,*this);

   if (ncolsb != this->fNcols)
      this->ResizeTo(ncolsb,ncolsb);

#ifdef CBLAS
   const Element *bp = b.GetMatrixArray();
         Element *cp = this->GetMatrixArray();
   if (typeid(Element) == typeid(Double_t))
      cblas_dgemm (CblasRowMajor,CblasNoTrans,CblasNoTrans,this->fNrows,this->fNcols,bta.GetNcols(),
                   1.0,btap,bta.GetNcols(),bp,b.GetNcols(),1.0,cp,this->fNcols);
   else if (typeid(Element) != typeid(Float_t))
      cblas_sgemm (CblasRowMajor,CblasNoTrans,CblasNoTrans,this->fNrows,this->fNcols,bta.GetNcols(),
                   1.0,btap,bta.GetNcols(),bp,b.GetNcols(),1.0,cp,this->fNcols);
   //else
      //Error("similarityT","type %s not implemented in BLAS library",typeid(Element));
#else
   const Int_t nbta     = bta.GetNoElements();
   const Int_t nb       = b.GetNoElements();
   const Int_t ncolsbta = bta.GetNcols();
   const Element * const bp   = b.GetMatrixArray();
         Element *       cp   = this->GetMatrixArray();
         Element * const cp0  = cp;

   Int_t ishift = 0;
   const Element *btarp0 = btap;                     // Pointer to  A[i,0];
   const Element *bcp0   = bp;
   while (btarp0 < btap+nbta) {
      for (const Element *bcp = bcp0; bcp < bp+ncolsb; ) { // Pointer to the j-th column of B, Start bcp = B[0,0]
         const Element *btarp = btarp0;                   // Pointer to the i-th row of A, reset to A[i,0]
         Element cij = 0;
         while (bcp < bp+nb) {                         // Scan the i-th row of A and
            cij += *btarp++ * *bcp;                     // the j-th col of B
            bcp += ncolsb;
         }
         *cp++ = cij;
         bcp -= nb-1;                                  // Set bcp to the (j+1)-th col
      }
      btarp0 += ncolsbta;                             // Set ap to the (i+1)-th row
      bcp0++;
      cp += ++ishift;
   }

   //R__ASSERT(cp == cp0+this->fNelems+ishift && btarp0 == btap+nbta);

   cp = cp0;
   for (Int_t irow = 0; irow < this->fNrows; irow++) {
      const Int_t rowOff1 = irow*this->fNrows;
      for (Int_t icol = 0; icol < irow; icol++) {
         const Int_t rowOff2 = icol*this->fNrows;
         cp[rowOff1+icol] = cp[rowOff2+irow];
      }
   }
#endif

   if (isAllocated)
      delete [] btap;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator=(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator=","matrices not compatible");
      return *this;
   }

   if (this->GetMatrixArray() != source.GetMatrixArray()) {
      //TObject::operator=(source);
      memcpy(this->GetMatrixArray(),source.fElements,this->fNelems*sizeof(Element));
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator=(const TMatrixTSymLazy<Element> &lazy_constructor)
{
   //R__ASSERT(this->IsValid());

   if (lazy_constructor.fRowUpb != this->GetRowUpb() ||
       lazy_constructor.fRowLwb != this->GetRowLwb()) {
       //Error("operator=(const TMatrixTSymLazy&)", "matrix is incompatible with "
           //  "the assigned Lazy matrix");
      return *this;
   }

   lazy_constructor.FillIn(*this);
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix.

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = fElements;
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ = val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the matrix.

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator+=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = fElements;
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ += val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract val from every element of the matrix.

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator-=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = fElements;
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ -= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix with val.

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator*=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = fElements;
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ *= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add the source matrix.

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator+=(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator+=","matrices not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
   Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+this->fNelems;
   while (tp < tp_last)
      *tp++ += *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract the source matrix.

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::operator-=(const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator-=","matrices not compatible");
      return *this;
   }

   const Element *sp = source.GetMatrixArray();
   Element *tp = this->GetMatrixArray();
   const Element * const tp_last = tp+this->fNelems;
   while (tp < tp_last)
      *tp++ -= *sp++;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::Apply(const TElementActionT<Element> &action)
{
   //R__ASSERT(this->IsValid());

   Element val = 0;
   Element *trp = this->GetMatrixArray(); // pointer to UR part and diagonal, traverse row-wise
   Element *tcp = trp;                    // pointer to LL part,              traverse col-wise
   for (Int_t i = 0; i < this->fNrows; i++) {
      trp += i;               // point to [i,i]
      tcp += i*this->fNcols;  // point to [i,i]
      for (Int_t j = i; j < this->fNcols; j++) {
         action.Operation(val);
         if (j > i) *tcp = val;
         *trp++ = val;
         tcp += this->fNcols;
      }
      tcp -= this->fNelems-1; // point to [0,i]
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Apply action to each element of the matrix. To action the location
/// of the current element is passed.

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::Apply(const TElementPosActionT<Element> &action)
{
   //R__ASSERT(this->IsValid());

   Element val = 0;
   Element *trp = this->GetMatrixArray(); // pointer to UR part and diagonal, traverse row-wise
   Element *tcp = trp;                    // pointer to LL part,              traverse col-wise
   for (Int_t i = 0; i < this->fNrows; i++) {
      action.fI = i+this->fRowLwb;
      trp += i;               // point to [i,i]
      tcp += i*this->fNcols;  // point to [i,i]
      for (Int_t j = i; j < this->fNcols; j++) {
         action.fJ = j+this->fColLwb;
         action.Operation(val);
         if (j > i) *tcp = val;
         *trp++ = val;
         tcp += this->fNcols;
      }
      tcp -= this->fNelems-1; // point to [0,i]
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// randomize matrix element values but keep matrix symmetric

template<class Element>
TMatrixTBase<Element> &TMatrixTSym<Element>::Randomize(Element alpha,Element beta,Double_t &seed)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      if (this->fNrows != this->fNcols || this->fRowLwb != this->fColLwb) {
         //Error("Randomize(Element,Element,Element &","matrix should be square");
         return *this;
      }
   }

   const Element scale = beta-alpha;
   const Element shift = alpha/scale;

   Element *ep = GetMatrixArray();
   for (Int_t i = 0; i < this->fNrows; i++) {
      const Int_t off = i*this->fNcols;
      for (Int_t j = 0; j <= i; j++) {
         ep[off+j] = scale*(Drand(seed)+shift);
         if (i != j) {
            ep[j*this->fNcols+i] = ep[off+j];
         }
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// randomize matrix element values but keep matrix symmetric positive definite

template<class Element>
TMatrixTSym<Element> &TMatrixTSym<Element>::RandomizePD(Element alpha,Element beta,Double_t &seed)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      if (this->fNrows != this->fNcols || this->fRowLwb != this->fColLwb) {
         //Error("RandomizeSym(Element,Element,Element &","matrix should be square");
         return *this;
      }
   }

   const Element scale = beta-alpha;
   const Element shift = alpha/scale;

   Element *ep = GetMatrixArray();
   Int_t i;
   for (i = 0; i < this->fNrows; i++) {
      const Int_t off = i*this->fNcols;
      for (Int_t j = 0; j <= i; j++)
         ep[off+j] = scale*(Drand(seed)+shift);
   }

   for (i = this->fNrows-1; i >= 0; i--) {
      const Int_t off1 = i*this->fNcols;
      for (Int_t j = i; j >= 0; j--) {
         const Int_t off2 = j*this->fNcols;
         ep[off1+j] *= ep[off2+j];
         for (Int_t k = j-1; k >= 0; k--) {
            ep[off1+j] += ep[off1+k]*ep[off2+k];
         }
         if (i != j)
            ep[off2+i] = ep[off1+j];
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Return a matrix containing the eigen-vectors ordered by descending eigen-values.
/// For full functionality use TMatrixDSymEigen .

template<class Element>
const TMatrixT<Element> TMatrixTSym<Element>::EigenVectors(TVectorT<Element> &eigenValues) const
{
   TMatrixDSym tmp = *this;
   TMatrixDSymEigen eigen(tmp);
   eigenValues.ResizeTo(this->fNrows);
   eigenValues = eigen.GetEigenValues();
   return eigen.GetEigenVectors();
}

////////////////////////////////////////////////////////////////////////////////
/// Check to see if two matrices are identical.

template<class Element>
Bool_t operator==(const TMatrixTSym<Element> &m1,const TMatrixTSym<Element> &m2)
{
   if (!AreCompatible(m1,m2)) return kFALSE;
   return (memcmp(m1.GetMatrixArray(),m2.GetMatrixArray(),
                  m1.GetNoElements()*sizeof(Element)) == 0);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator+(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixTSym<Element> target(source1);
   target += source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator+(const TMatrixTSym<Element> &source1,Element val)
{
   TMatrixTSym<Element> target(source1);
   target += val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator+(Element val,const TMatrixTSym<Element> &source1)
{
   return operator+(source1,val);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator-(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixTSym<Element> target(source1);
   target -= source2;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator-(const TMatrixTSym<Element> &source1,Element val)
{
   TMatrixTSym<Element> target(source1);
   target -= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator-(Element val,const TMatrixTSym<Element> &source1)
{
   return Element(-1.0)*operator-(source1,val);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator*(const TMatrixTSym<Element> &source1,Element val)
{
   TMatrixTSym<Element> target(source1);
   target *= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSym<Element> operator*(Element val,const TMatrixTSym<Element> &source1)
{
  return operator*(source1,val);
}

////////////////////////////////////////////////////////////////////////////////
/// Logical AND

template<class Element>
TMatrixTSym<Element> operator&&(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixTSym<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator&&(const TMatrixTSym&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last)
      *tp++ = (*sp1++ != 0.0 && *sp2++ != 0.0);

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Logical Or

template<class Element>
TMatrixTSym<Element> operator||(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixTSym<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator||(const TMatrixTSym&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last)
      *tp++ = (*sp1++ != 0.0 || *sp2++ != 0.0);

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// source1 > source2

template<class Element>
TMatrixTSym<Element> operator>(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
  TMatrixTSym<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator>(const TMatrixTSym&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) > (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// source1 >= source2

template<class Element>
TMatrixTSym<Element> operator>=(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixTSym<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator>=(const TMatrixTSym&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) >= (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// source1 <= source2

template<class Element>
TMatrixTSym<Element> operator<=(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
   TMatrixTSym<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator<=(const TMatrixTSym&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) <= (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// source1 < source2

template<class Element>
TMatrixTSym<Element> operator<(const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2)
{
  TMatrixTSym<Element> target;

   if (gMatrixCheck && !AreCompatible(source1,source2)) {
      //Error("operator<(const TMatrixTSym&,const TMatrixTSym&)","matrices not compatible");
      return target;
   }

   target.ResizeTo(source1);

   const Element *sp1 = source1.GetMatrixArray();
   const Element *sp2 = source2.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element * const tp_last = tp+target.GetNoElements();
   while (tp < tp_last) {
      *tp++ = (*sp1) < (*sp2); sp1++; sp2++;
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * source.

template<class Element>
TMatrixTSym<Element> &Add(TMatrixTSym<Element> &target,Element scalar,const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("Add","matrices not compatible");
      return target;
   }

   const Int_t nrows  = target.GetNrows();
   const Int_t ncols  = target.GetNcols();
   const Int_t nelems = target.GetNoElements();
   const Element *sp  = source.GetMatrixArray();
         Element *trp = target.GetMatrixArray(); // pointer to UR part and diagonal, traverse row-wise
         Element *tcp = target.GetMatrixArray(); // pointer to LL part,              traverse col-wise
   for (Int_t i = 0; i < nrows; i++) {
      sp  += i;
      trp += i;        // point to [i,i]
      tcp += i*ncols;  // point to [i,i]
      for (Int_t j = i; j < ncols; j++) {
         const Element tmp = scalar * *sp++;
         if (j > i) *tcp += tmp;
         *trp++ += tmp;
         tcp += ncols;
      }
      tcp -= nelems-1; // point to [0,i]
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element.

template<class Element>
TMatrixTSym<Element> &ElementMult(TMatrixTSym<Element> &target,const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementMult","matrices not compatible");
      return target;
   }

   const Int_t nrows  = target.GetNrows();
   const Int_t ncols  = target.GetNcols();
   const Int_t nelems = target.GetNoElements();
   const Element *sp  = source.GetMatrixArray();
         Element *trp = target.GetMatrixArray(); // pointer to UR part and diagonal, traverse row-wise
         Element *tcp = target.GetMatrixArray(); // pointer to LL part,              traverse col-wise
   for (Int_t i = 0; i < nrows; i++) {
      sp  += i;
      trp += i;        // point to [i,i]
      tcp += i*ncols;  // point to [i,i]
      for (Int_t j = i; j < ncols; j++) {
         if (j > i) *tcp *= *sp;
         *trp++ *= *sp++;
         tcp += ncols;
      }
      tcp -= nelems-1; // point to [0,i]
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element.

template<class Element>
TMatrixTSym<Element> &ElementDiv(TMatrixTSym<Element> &target,const TMatrixTSym<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementDiv","matrices not compatible");
      return target;
   }

   const Int_t nrows  = target.GetNrows();
   const Int_t ncols  = target.GetNcols();
   const Int_t nelems = target.GetNoElements();
   const Element *sp  = source.GetMatrixArray();
         Element *trp = target.GetMatrixArray(); // pointer to UR part and diagonal, traverse row-wise
         Element *tcp = target.GetMatrixArray(); // pointer to LL part,              traverse col-wise
   for (Int_t i = 0; i < nrows; i++) {
      sp  += i;
      trp += i;        // point to [i,i]
      tcp += i*ncols;  // point to [i,i]
      for (Int_t j = i; j < ncols; j++) {
         if (*sp != 0.0) {
            if (j > i) *tcp /= *sp;
            *trp++ /= *sp++;
         } else {
            const Int_t irow = (sp-source.GetMatrixArray())/source.GetNcols();
            const Int_t icol = (sp-source.GetMatrixArray())%source.GetNcols();
            //Error("ElementDiv","source (%d,%d) is zero",irow,icol);
            trp++;
         }
         tcp += ncols;
      }
      tcp -= nelems-1; // point to [0,i]
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Stream an object of class TMatrixTSym.
/*
template<class Element>
void TMatrixTSym<Element>::Streamer(TBuffer &R__b)
{
   if (R__b.IsReading()) {
      UInt_t R__s, R__c;
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c);
      Clear();
      R__b.ReadClassBuffer(TMatrixTBase<Element>::Class(),this,R__v,R__s,R__c);
      fElements = new Element[this->fNelems];
      Int_t i;
      for (i = 0; i < this->fNrows; i++) {
         R__b.ReadFastArray(fElements+i*this->fNcols+i,this->fNcols-i);
      }
      // copy to Lower left triangle
      for (i = 0; i < this->fNrows; i++) {
         for (Int_t j = 0; j < i; j++) {
            fElements[i*this->fNcols+j] = fElements[j*this->fNrows+i];
        }
      }
      if (this->fNelems <= this->kSizeMax) {
         memcpy(fDataStack,fElements,this->fNelems*sizeof(Element));
         delete [] fElements;
         fElements = fDataStack;
      }
   } else {
      R__b.WriteClassBuffer(TMatrixTBase<Element>::Class(),this);
      // Only write the Upper right triangle
      for (Int_t i = 0; i < this->fNrows; i++) {
         R__b.WriteFastArray(fElements+i*this->fNcols+i,this->fNcols-i);
      }
   }
}
*/
//#include "TMatrixFSymfwd.h"

template class TMatrixTSym<Float_t>;

template Bool_t       operator== <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator+  <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator+  <Float_t>(const TMatrixFSym &source1,      Float_t       val);
template TMatrixFSym  operator+  <Float_t>(      Float_t      val    ,const TMatrixFSym  &source2);
template TMatrixFSym  operator-  <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator-  <Float_t>(const TMatrixFSym &source1,      Float_t       val);
template TMatrixFSym  operator-  <Float_t>(      Float_t      val    ,const TMatrixFSym  &source2);
template TMatrixFSym  operator*  <Float_t>(const TMatrixFSym &source,       Float_t       val    );
template TMatrixFSym  operator*  <Float_t>(      Float_t      val,    const TMatrixFSym  &source );
template TMatrixFSym  operator&& <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator|| <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator>  <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator>= <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator<= <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);
template TMatrixFSym  operator<  <Float_t>(const TMatrixFSym &source1,const TMatrixFSym  &source2);

template TMatrixFSym &Add        <Float_t>(TMatrixFSym &target,      Float_t      scalar,const TMatrixFSym &source);
template TMatrixFSym &ElementMult<Float_t>(TMatrixFSym &target,const TMatrixFSym &source);
template TMatrixFSym &ElementDiv <Float_t>(TMatrixFSym &target,const TMatrixFSym &source);

//#include "TMatrixDSymfwd.h"

template class TMatrixTSym<Double_t>;

template Bool_t       operator== <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator+  <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator+  <Double_t>(const TMatrixDSym &source1,      Double_t      val);
template TMatrixDSym  operator+  <Double_t>(      Double_t     val    ,const TMatrixDSym  &source2);
template TMatrixDSym  operator-  <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator-  <Double_t>(const TMatrixDSym &source1,      Double_t      val);
template TMatrixDSym  operator-  <Double_t>(      Double_t     val    ,const TMatrixDSym  &source2);
template TMatrixDSym  operator*  <Double_t>(const TMatrixDSym &source,       Double_t      val    );
template TMatrixDSym  operator*  <Double_t>(      Double_t     val,    const TMatrixDSym  &source );
template TMatrixDSym  operator&& <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator|| <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator>  <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator>= <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator<= <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);
template TMatrixDSym  operator<  <Double_t>(const TMatrixDSym &source1,const TMatrixDSym  &source2);

template TMatrixDSym &Add        <Double_t>(TMatrixDSym &target,      Double_t     scalar,const TMatrixDSym &source);
template TMatrixDSym &ElementMult<Double_t>(TMatrixDSym &target,const TMatrixDSym &source);
template TMatrixDSym &ElementDiv <Double_t>(TMatrixDSym &target,const TMatrixDSym &source);

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Feb 2004

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixTSparse
    \ingroup Matrix

 TMatrixTSparse

 Template class of a general sparse matrix in the Harwell-Boeing
 format

 Besides the usual shape/size decsriptors of a matrix like fNrows,
 fRowLwb,fNcols and fColLwb, we also store a row index, fRowIndex and
 column index, fColIndex only for those elements unequal zero:

~~~
 fRowIndex[0,..,fNrows]:    Stores for each row the index range of
                            the elements in the data and column array
 fColIndex[0,..,fNelems-1]: Stores the column number for each data
                            element != 0
~~~

 As an example how to access all sparse data elements:

~~~
 for (Int_t irow = 0; irow < this->fNrows; irow++) {
   const Int_t sIndex = fRowIndex[irow];
   const Int_t eIndex = fRowIndex[irow+1];
   for (Int_t index = sIndex; index < eIndex; index++) {
     const Int_t icol = fColIndex[index];
     const Element data = fElements[index];
     printf("data(%d,%d) = %.4e\n",irow+this->fRowLwb,icol+
                                               this->fColLwb,data);
   }
 }
~~~

 When checking whether sparse matrices are compatible (like in an
 assigment !), not only the shape parameters are compared but also
 the sparse structure through fRowIndex and fColIndex .

 Several methods exist to fill a sparse matrix with data entries.
 Most are the same like for dense matrices but some care has to be
 taken with regard to performance. In the constructor, always the
 shape of the matrix has to be specified in some form . Data can be
 entered through the following methods :
 1. constructor
~~~
    TMatrixTSparse(Int_t row_lwb,Int_t row_upb,Int_t dol_lwb,
                   Int_t col_upb,Int_t nr_nonzeros,
                   Int_t *row, Int_t *col,Element *data);
~~~
    It uses SetMatrixArray(..), see below
 2. copy constructors
 3. SetMatrixArray(Int_t nr,Int_t *irow,Int_t *icol,Element *data)
    where it is expected that the irow,icol and data array contain
    nr entries . Only the entries with non-zero data[i] value are
    inserted. Be aware that the input data array will be modified
    inside the routine for doing the necessary sorting of indices !
 4. TMatrixTSparse a(n,m); for(....) { a(i,j) = ....
    This is a very flexible method but expensive :
    - if no entry for slot (i,j) is found in the sparse index table
      it will be entered, which involves some memory management !
    - before invoking this method in a loop it is smart to first
      set the index table through a call to SetSparseIndex(..)
 5. SetSub(Int_t row_lwb,Int_t col_lwb,const TMatrixTBase &source)
    the matrix to be inserted at position (row_lwb,col_lwb) can be
    both dense or sparse .

*/

//#include "TMatrixTSparse.h"
//#include "TBuffer.h"
//#include "TMatrixT.h"
//#include "TMath.h"

templateClassImp(TMatrixTSparse);


////////////////////////////////////////////////////////////////////////////////
/// Space is allocated for row/column indices and data, but the sparse structure
/// information has still to be set !

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(Int_t no_rows,Int_t no_cols)
{
   Allocate(no_rows,no_cols,0,0,1);
}

////////////////////////////////////////////////////////////////////////////////
/// Space is allocated for row/column indices and data, but the sparse structure
/// information has still to be set !

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb)
{
   Allocate(row_upb-row_lwb+1,col_upb-col_lwb+1,row_lwb,col_lwb,1);
}

////////////////////////////////////////////////////////////////////////////////
/// Space is allocated for row/column indices and data. Sparse row/column index
/// structure together with data is coming from the arrays, row, col and data, resp .

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                        Int_t nr,Int_t *row, Int_t *col,Element *data)
{
   const Int_t irowmin = TMath::LocMin(nr,row);
   const Int_t irowmax = TMath::LocMax(nr,row);
   const Int_t icolmin = TMath::LocMin(nr,col);
   const Int_t icolmax = TMath::LocMax(nr,col);

   if (row[irowmin] < row_lwb || row[irowmax] > row_upb) {
      //Error("TMatrixTSparse","Inconsistency between row index and its range");
      if (row[irowmin] < row_lwb) {
         //Info("TMatrixTSparse","row index lower bound adjusted to %d",row[irowmin]);
         row_lwb = row[irowmin];
      }
      if (row[irowmax] > row_upb) {
         //Info("TMatrixTSparse","row index upper bound adjusted to %d",row[irowmax]);
         col_lwb = col[irowmax];
      }
   }
   if (col[icolmin] < col_lwb || col[icolmax] > col_upb) {
      //Error("TMatrixTSparse","Inconsistency between column index and its range");
      if (col[icolmin] < col_lwb) {
         //Info("TMatrixTSparse","column index lower bound adjusted to %d",col[icolmin]);
         col_lwb = col[icolmin];
      }
      if (col[icolmax] > col_upb) {
         //Info("TMatrixTSparse","column index upper bound adjusted to %d",col[icolmax]);
         col_upb = col[icolmax];
      }
   }

   Allocate(row_upb-row_lwb+1,col_upb-col_lwb+1,row_lwb,col_lwb,1,nr);

   SetMatrixArray(nr,row,col,data);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(const TMatrixTSparse<Element> &another) : TMatrixTBase<Element>(another)
{
   Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb(),1,
            another.GetNoElements());
   memcpy(fRowIndex,another.GetRowIndexArray(),this->fNrowIndex*sizeof(Int_t));
   memcpy(fColIndex,another.GetColIndexArray(),this->fNelems*sizeof(Int_t));

   *this = another;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(const TMatrixT<Element> &another) : TMatrixTBase<Element>(another)
{
   const Int_t nr_nonzeros = another.NonZeros();
   Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb(),1,nr_nonzeros);
   SetSparseIndex(another);
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix applying a specific operation to the prototype.
/// Supported operations are: kZero, kUnit, kTransposed and kAtA

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(EMatrixCreatorsOp1 op,const TMatrixTSparse<Element> &prototype)
{
   //R__ASSERT(prototype.IsValid());

   Int_t nr_nonzeros = 0;

   switch(op) {
      case kZero:
      {
         Allocate(prototype.GetNrows(),prototype.GetNcols(),
                  prototype.GetRowLwb(),prototype.GetColLwb(),1,nr_nonzeros);
         break;
      }
      case kUnit:
      {
         const Int_t nrows  = prototype.GetNrows();
         const Int_t ncols  = prototype.GetNcols();
         const Int_t rowLwb = prototype.GetRowLwb();
         const Int_t colLwb = prototype.GetColLwb();
         for (Int_t i = rowLwb; i <= rowLwb+nrows-1; i++)
            for (Int_t j = colLwb; j <= colLwb+ncols-1; j++)
               if (i==j) nr_nonzeros++;
         Allocate(nrows,ncols,rowLwb,colLwb,1,nr_nonzeros);
         UnitMatrix();
         break;
      }
      case kTransposed:
      {
          Allocate(prototype.GetNcols(), prototype.GetNrows(),
                   prototype.GetColLwb(),prototype.GetRowLwb(),1,prototype.GetNoElements());
          Transpose(prototype);
          break;
      }
      case kAtA:
      {
         const TMatrixTSparse<Element> at(TMatrixTSparse<Element>::kTransposed,prototype);
         AMultBt(at,at,1);
         break;
      }

      default:
         //Error("TMatrixTSparse(EMatrixCreatorOp1)","operation %d not yet implemented", op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix applying a specific operation to two prototypes.
/// Supported operations are: kMult (a*b), kMultTranspose (a*b'), kPlus (a+b), kMinus (a-b)

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(const TMatrixTSparse<Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSparse<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kMult:
         AMultB(a,b,1);
         break;

      case kMultTranspose:
         AMultBt(a,b,1);
         break;

      case kPlus:
         APlusB(a,b,1);
         break;

      case kMinus:
         AMinusB(a,b,1);
         break;

      default:
         //Error("TMatrixTSparse(EMatrixCreatorOp2)", "operation %d not yet implemented",op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix applying a specific operation to two prototypes.
/// Supported operations are: kMult (a*b), kMultTranspose (a*b'), kPlus (a+b), kMinus (a-b)

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(const TMatrixTSparse<Element> &a,EMatrixCreatorsOp2 op,const TMatrixT<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kMult:
         AMultB(a,b,1);
         break;

      case kMultTranspose:
         AMultBt(a,b,1);
         break;

      case kPlus:
         APlusB(a,b,1);
         break;

      case kMinus:
         AMinusB(a,b,1);
         break;

      default:
         //Error("TMatrixTSparse(EMatrixCreatorOp2)", "operation %d not yet implemented",op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Create a matrix applying a specific operation to two prototypes.
/// Supported operations are: kMult (a*b), kMultTranspose (a*b'), kPlus (a+b), kMinus (a-b)

template<class Element>
TMatrixTSparse<Element>::TMatrixTSparse(const TMatrixT<Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSparse<Element> &b)
{
   //R__ASSERT(a.IsValid());
   //R__ASSERT(b.IsValid());

   switch(op) {
      case kMult:
         AMultB(a,b,1);
         break;

      case kMultTranspose:
         AMultBt(a,b,1);
         break;

      case kPlus:
         APlusB(a,b,1);
         break;

      case kMinus:
         AMinusB(a,b,1);
         break;

      default:
         //Error("TMatrixTSparse(EMatrixCreatorOp2)", "operation %d not yet implemented",op);
         return;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Allocate new matrix. Arguments are number of rows, columns, row lowerbound (0 default)
/// and column lowerbound (0 default), 0 initialization flag and number of non-zero
/// elements (only relevant for sparse format).

template<class Element>
void TMatrixTSparse<Element>::Allocate(Int_t no_rows,Int_t no_cols,Int_t row_lwb,Int_t col_lwb,
                              Int_t init,Int_t nr_nonzeros)
{
   if ( (nr_nonzeros > 0 && (no_rows == 0 || no_cols == 0)) ||
       (no_rows < 0 || no_cols < 0 || nr_nonzeros < 0) )
   {
      //Error("Allocate","no_rows=%d no_cols=%d non_zeros=%d",no_rows,no_cols,nr_nonzeros);
      //this->Invalidate();
      return;
   }

   //this->MakeValid();
   this->fNrows     = no_rows;
   this->fNcols     = no_cols;
   this->fRowLwb    = row_lwb;
   this->fColLwb    = col_lwb;
   this->fNrowIndex = this->fNrows+1;
   this->fNelems    = nr_nonzeros;
   this->fIsOwner   = kTRUE;
   this->fTol       = std::numeric_limits<Element>::epsilon();

   fRowIndex = new Int_t[this->fNrowIndex];
   if (init)
      memset(fRowIndex,0,this->fNrowIndex*sizeof(Int_t));

   if (this->fNelems > 0) {
      fElements = new Element[this->fNelems];
      fColIndex = new Int_t   [this->fNelems];
      if (init) {
         memset(fElements,0,this->fNelems*sizeof(Element));
         memset(fColIndex,0,this->fNelems*sizeof(Int_t));
      }
   } else {
      fElements = 0;
      fColIndex = 0;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Insert in row rown, n elements of array v at column coln

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::InsertRow(Int_t rown,Int_t coln,const Element *v,Int_t n)
{
   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;
   const Int_t nr = (n > 0) ? n : this->fNcols;

   if (gMatrixCheck) {
      if (arown >= this->fNrows || arown < 0) {
         //Error("InsertRow","row %d out of matrix range",rown);
         return *this;
      }

      if (acoln >= this->fNcols || acoln < 0) {
         //Error("InsertRow","column %d out of matrix range",coln);
         return *this;
      }

      if (acoln+nr > this->fNcols || nr < 0) {
         //Error("InsertRow","row length %d out of range",nr);
         return *this;
      }
   }

   const Int_t sIndex = fRowIndex[arown];
   const Int_t eIndex = fRowIndex[arown+1];

   // check first how many slots are available from [acoln,..,acoln+nr-1]
   // also note lIndex and rIndex so that [sIndex..lIndex] and [rIndex..eIndex-1]
   // contain the row entries except for the region to be inserted

   Int_t nslots = 0;
   Int_t lIndex = sIndex-1;
   Int_t rIndex = sIndex-1;
   Int_t index;
   for (index = sIndex; index < eIndex; index++) {
      const Int_t icol = fColIndex[index];
      rIndex++;
      if (icol >= acoln+nr) break;
      if (icol >= acoln) nslots++;
      else               lIndex++;
   }

   const Int_t nelems_old = this->fNelems;
   const Int_t    *colIndex_old = fColIndex;
   const Element *elements_old = fElements;

   const Int_t ndiff = nr-nslots;
   this->fNelems += ndiff;
   fColIndex = new Int_t[this->fNelems];
   fElements = new Element[this->fNelems];

   for (Int_t irow = arown+1; irow < this->fNrows+1; irow++)
      fRowIndex[irow] += ndiff;

   if (lIndex+1 > 0) {
      memmove(fColIndex,colIndex_old,(lIndex+1)*sizeof(Int_t));
      memmove(fElements,elements_old,(lIndex+1)*sizeof(Element));
   }

   if (nelems_old > 0 && nelems_old-rIndex > 0) {
      memmove(fColIndex+rIndex+ndiff,colIndex_old+rIndex,(nelems_old-rIndex)*sizeof(Int_t));
      memmove(fElements+rIndex+ndiff,elements_old+rIndex,(nelems_old-rIndex)*sizeof(Element));
   }

   index = lIndex+1;
   for (Int_t i = 0; i < nr; i++) {
      fColIndex[index] = acoln+i;
      fElements[index] = v[i];
      index++;
   }

   if (colIndex_old) delete [] (Int_t*)    colIndex_old;
   if (elements_old) delete [] (Element*) elements_old;

   //R__ASSERT(this->fNelems == fRowIndex[this->fNrowIndex-1]);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Store in array v, n matrix elements of row rown starting at column coln

template<class Element>
void TMatrixTSparse<Element>::ExtractRow(Int_t rown, Int_t coln, Element *v,Int_t n) const
{
   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;
   const Int_t nr = (n > 0) ? n : this->fNcols;

   if (gMatrixCheck) {
      if (arown >= this->fNrows || arown < 0) {
         //Error("ExtractRow","row %d out of matrix range",rown);
         return;
      }

      if (acoln >= this->fNcols || acoln < 0) {
         //Error("ExtractRow","column %d out of matrix range",coln);
         return;
      }

      if (acoln+nr > this->fNcols || nr < 0) {
         //Error("ExtractRow","row length %d out of range",nr);
         return;
      }
   }

   const Int_t sIndex = fRowIndex[arown];
   const Int_t eIndex = fRowIndex[arown+1];

   memset(v,0,nr*sizeof(Element));
   const Int_t   * const pColIndex = GetColIndexArray();
   const Element * const pData     = GetMatrixArray();
   for (Int_t index = sIndex; index < eIndex; index++) {
      const Int_t icol = pColIndex[index];
      if (icol < acoln || icol >= acoln+nr) continue;
       v[icol-acoln] = pData[index];
   }
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix multiplication. Create a matrix C such that C = A * B'.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::AMultBt(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNcols() != b.GetNcols() || a.GetColLwb() != b.GetColLwb()) {
         //Error("AMultBt","A and B columns incompatible");
         return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("AMultB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("AMultB","this = &b");
         return;
      }
   }

   const Int_t * const pRowIndexa = a.GetRowIndexArray();
   const Int_t * const pColIndexa = a.GetColIndexArray();
   const Int_t * const pRowIndexb = b.GetRowIndexArray();
   const Int_t * const pColIndexb = b.GetColIndexArray();

   Int_t *pRowIndexc;
   Int_t *pColIndexc;
   if (constr) {
      // make a best guess of the sparse structure; it will guarantee
      // enough allocated space !

      Int_t nr_nonzero_rowa = 0;
      {
         for (Int_t irowa = 0; irowa < a.GetNrows(); irowa++)
            if (pRowIndexa[irowa] < pRowIndexa[irowa+1])
               nr_nonzero_rowa++;
      }
      Int_t nr_nonzero_rowb = 0;
      {
         for (Int_t irowb = 0; irowb < b.GetNrows(); irowb++)
            if (pRowIndexb[irowb] < pRowIndexb[irowb+1])
              nr_nonzero_rowb++;
      }

      const Int_t nc = nr_nonzero_rowa*nr_nonzero_rowb; // best guess
      Allocate(a.GetNrows(),b.GetNrows(),a.GetRowLwb(),b.GetRowLwb(),1,nc);

      pRowIndexc = this->GetRowIndexArray();
      pColIndexc = this->GetColIndexArray();

      pRowIndexc[0] = 0;
      Int_t ielem = 0;
      for (Int_t irowa = 0; irowa < a.GetNrows(); irowa++) {
         pRowIndexc[irowa+1] = pRowIndexc[irowa];
         if (pRowIndexa[irowa] >= pRowIndexa[irowa+1]) continue;
         for (Int_t irowb = 0; irowb < b.GetNrows(); irowb++) {
            if (pRowIndexb[irowb] >= pRowIndexb[irowb+1]) continue;
            pRowIndexc[irowa+1]++;
            pColIndexc[ielem++] = irowb;
         }
      }
   } else {
      pRowIndexc = this->GetRowIndexArray();
      pColIndexc = this->GetColIndexArray();
   }

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         const Int_t sIndexb = pRowIndexb[icolc];
         const Int_t eIndexb = pRowIndexb[icolc+1];
         Element sum = 0.0;
         Int_t indexb = sIndexb;
         for (Int_t indexa = sIndexa; indexa < eIndexa && indexb < eIndexb; indexa++) {
            const Int_t icola = pColIndexa[indexa];
            while (indexb < eIndexb && pColIndexb[indexb] <= icola) {
               if (icola == pColIndexb[indexb]) {
                 sum += pDataa[indexa]*pDatab[indexb];
                 break;
               }
               indexb++;
            }
         }
         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1] = indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix multiplication. Create a matrix C such that C = A * B'.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::AMultBt(const TMatrixTSparse<Element> &a,const TMatrixT<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNcols() != b.GetNcols() || a.GetColLwb() != b.GetColLwb()) {
         //Error("AMultBt","A and B columns incompatible");
         return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("AMultB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("AMultB","this = &b");
         return;
      }
   }

   const Int_t * const pRowIndexa = a.GetRowIndexArray();
   const Int_t * const pColIndexa = a.GetColIndexArray();

   Int_t *pRowIndexc;
   Int_t *pColIndexc;
   if (constr) {
      // make a best guess of the sparse structure; it will guarantee
      // enough allocated space !

      Int_t nr_nonzero_rowa = 0;
      {
         for (Int_t irowa = 0; irowa < a.GetNrows(); irowa++)
            if (pRowIndexa[irowa] < pRowIndexa[irowa+1])
               nr_nonzero_rowa++;
      }
      Int_t nr_nonzero_rowb = b.GetNrows();

      const Int_t nc = nr_nonzero_rowa*nr_nonzero_rowb; // best guess
      Allocate(a.GetNrows(),b.GetNrows(),a.GetRowLwb(),b.GetRowLwb(),1,nc);

      pRowIndexc = this->GetRowIndexArray();
      pColIndexc = this->GetColIndexArray();

      pRowIndexc[0] = 0;
      Int_t ielem = 0;
      for (Int_t irowa = 0; irowa < a.GetNrows(); irowa++) {
         pRowIndexc[irowa+1] = pRowIndexc[irowa];
         for (Int_t irowb = 0; irowb < b.GetNrows(); irowb++) {
            pRowIndexc[irowa+1]++;
            pColIndexc[ielem++] = irowb;
         }
      }
   } else {
      pRowIndexc = this->GetRowIndexArray();
      pColIndexc = this->GetColIndexArray();
   }

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         const Int_t off = icolc*b.GetNcols();
         Element sum = 0.0;
         for (Int_t indexa = sIndexa; indexa < eIndexa; indexa++) {
            const Int_t icola = pColIndexa[indexa];
            sum += pDataa[indexa]*pDatab[off+icola];
         }
         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1]= indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix multiplication. Create a matrix C such that C = A * B'.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::AMultBt(const TMatrixT<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNcols() != b.GetNcols() || a.GetColLwb() != b.GetColLwb()) {
         //Error("AMultBt","A and B columns incompatible");
         return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("AMultB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("AMultB","this = &b");
         return;
      }
   }

   const Int_t * const pRowIndexb = b.GetRowIndexArray();
   const Int_t * const pColIndexb = b.GetColIndexArray();

   Int_t *pRowIndexc;
   Int_t *pColIndexc;
   if (constr) {
      // make a best guess of the sparse structure; it will guarantee
      // enough allocated space !

      Int_t nr_nonzero_rowa = a.GetNrows();
      Int_t nr_nonzero_rowb = 0;
      {
         for (Int_t irowb = 0; irowb < b.GetNrows(); irowb++)
            if (pRowIndexb[irowb] < pRowIndexb[irowb+1])
               nr_nonzero_rowb++;
      }

      const Int_t nc = nr_nonzero_rowa*nr_nonzero_rowb; // best guess
      Allocate(a.GetNrows(),b.GetNrows(),a.GetRowLwb(),b.GetRowLwb(),1,nc);

      pRowIndexc = this->GetRowIndexArray();
      pColIndexc = this->GetColIndexArray();

      pRowIndexc[0] = 0;
      Int_t ielem = 0;
      for (Int_t irowa = 0; irowa < a.GetNrows(); irowa++) {
         pRowIndexc[irowa+1] = pRowIndexc[irowa];
         for (Int_t irowb = 0; irowb < b.GetNrows(); irowb++) {
            if (pRowIndexb[irowb] >= pRowIndexb[irowb+1]) continue;
            pRowIndexc[irowa+1]++;
            pColIndexc[ielem++] = irowb;
         }
      }
   } else {
      pRowIndexc = this->GetRowIndexArray();
      pColIndexc = this->GetColIndexArray();
   }

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t off = irowc*a.GetNcols();
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         const Int_t sIndexb = pRowIndexb[icolc];
         const Int_t eIndexb = pRowIndexb[icolc+1];
         Element sum = 0.0;
         for (Int_t indexb = sIndexb; indexb < eIndexb; indexb++) {
            const Int_t icolb = pColIndexb[indexb];
            sum += pDataa[off+icolb]*pDatab[indexb];
         }
         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1] = indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix addition. Create a matrix C such that C = A + B.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::APlusB(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNrows()  != b.GetNrows()  || a.GetNcols()  != b.GetNcols() ||
          a.GetRowLwb() != b.GetRowLwb() || a.GetColLwb() != b.GetColLwb()) {
         //Error("APlusB(const TMatrixTSparse &,const TMatrixTSparse &","matrices not compatible");
         return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("APlusB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("APlusB","this = &b");
         return;
      }
   }

   const Int_t * const pRowIndexa = a.GetRowIndexArray();
   const Int_t * const pRowIndexb = b.GetRowIndexArray();
   const Int_t * const pColIndexa = a.GetColIndexArray();
   const Int_t * const pColIndexb = b.GetColIndexArray();

   if (constr) {
      Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb());
      SetSparseIndexAB(a,b);
   }

   Int_t * const pRowIndexc = this->GetRowIndexArray();
   Int_t * const pColIndexc = this->GetColIndexArray();

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      const Int_t sIndexb = pRowIndexb[irowc];
      const Int_t eIndexb = pRowIndexb[irowc+1];
      Int_t indexa = sIndexa;
      Int_t indexb = sIndexb;
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         Element sum = 0.0;
         while (indexa < eIndexa && pColIndexa[indexa] <= icolc) {
            if (icolc == pColIndexa[indexa]) {
               sum += pDataa[indexa];
               break;
            }
            indexa++;
         }
         while (indexb < eIndexb && pColIndexb[indexb] <= icolc) {
            if (icolc == pColIndexb[indexb]) {
               sum += pDatab[indexb];
               break;
            }
            indexb++;
         }

         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1] = indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix addition. Create a matrix C such that C = A + B.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::APlusB(const TMatrixTSparse<Element> &a,const TMatrixT<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNrows()  != b.GetNrows()  || a.GetNcols()  != b.GetNcols() ||
          a.GetRowLwb() != b.GetRowLwb() || a.GetColLwb() != b.GetColLwb()) {
         //Error("APlusB(const TMatrixTSparse &,const TMatrixT &","matrices not compatible");
         return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("APlusB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("APlusB","this = &b");
         return;
      }
   }

   if (constr) {
      Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb());
      SetSparseIndexAB(a,b);
   }

   Int_t * const pRowIndexc = this->GetRowIndexArray();
   Int_t * const pColIndexc = this->GetColIndexArray();

   const Int_t * const pRowIndexa = a.GetRowIndexArray();
   const Int_t * const pColIndexa = a.GetColIndexArray();

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      const Int_t off = irowc*this->GetNcols();
      Int_t indexa = sIndexa;
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         Element sum = pDatab[off+icolc];
         while (indexa < eIndexa && pColIndexa[indexa] <= icolc) {
            if (icolc == pColIndexa[indexa]) {
               sum += pDataa[indexa];
               break;
            }
            indexa++;
         }

         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1] = indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix subtraction. Create a matrix C such that C = A - B.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::AMinusB(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNrows()  != b.GetNrows()  || a.GetNcols()  != b.GetNcols() ||
          a.GetRowLwb() != b.GetRowLwb() || a.GetColLwb() != b.GetColLwb()) {
         //Error("AMinusB(const TMatrixTSparse &,const TMatrixTSparse &","matrices not compatible");
         return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("AMinusB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("AMinusB","this = &b");
         return;
      }
   }

   const Int_t * const pRowIndexa = a.GetRowIndexArray();
   const Int_t * const pRowIndexb = b.GetRowIndexArray();
   const Int_t * const pColIndexa = a.GetColIndexArray();
   const Int_t * const pColIndexb = b.GetColIndexArray();

   if (constr) {
      Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb());
      SetSparseIndexAB(a,b);
   }

   Int_t * const pRowIndexc = this->GetRowIndexArray();
   Int_t * const pColIndexc = this->GetColIndexArray();

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      const Int_t sIndexb = pRowIndexb[irowc];
      const Int_t eIndexb = pRowIndexb[irowc+1];
      Int_t indexa = sIndexa;
      Int_t indexb = sIndexb;
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         Element sum = 0.0;
         while (indexa < eIndexa && pColIndexa[indexa] <= icolc) {
            if (icolc == pColIndexa[indexa]) {
               sum += pDataa[indexa];
               break;
            }
            indexa++;
         }
         while (indexb < eIndexb && pColIndexb[indexb] <= icolc) {
            if (icolc == pColIndexb[indexb]) {
               sum -= pDatab[indexb];
               break;
            }
            indexb++;
         }

         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1] = indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix subtraction. Create a matrix C such that C = A - B.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::AMinusB(const TMatrixTSparse<Element> &a,const TMatrixT<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNrows()  != b.GetNrows()  || a.GetNcols()  != b.GetNcols() ||
          a.GetRowLwb() != b.GetRowLwb() || a.GetColLwb() != b.GetColLwb()) {
          //Error("AMinusB(const TMatrixTSparse &,const TMatrixT &","matrices not compatible");
          return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("AMinusB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("AMinusB","this = &b");
         return;
      }
   }

   if (constr) {
      Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb());
      SetSparseIndexAB(a,b);
   }

   Int_t * const pRowIndexc = this->GetRowIndexArray();
   Int_t * const pColIndexc = this->GetColIndexArray();

   const Int_t * const pRowIndexa = a.GetRowIndexArray();
   const Int_t * const pColIndexa = a.GetColIndexArray();

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      const Int_t off = irowc*this->GetNcols();
      Int_t indexa = sIndexa;
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         Element sum = -pDatab[off+icolc];
         while (indexa < eIndexa && pColIndexa[indexa] <= icolc) {
            if (icolc == pColIndexa[indexa]) {
               sum += pDataa[indexa];
               break;
            }
            indexa++;
         }

         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1] = indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// General matrix subtraction. Create a matrix C such that C = A - B.
/// Note, matrix C is allocated for constr=1.

template<class Element>
void TMatrixTSparse<Element>::AMinusB(const TMatrixT<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNrows()  != b.GetNrows()  || a.GetNcols()  != b.GetNcols() ||
          a.GetRowLwb() != b.GetRowLwb() || a.GetColLwb() != b.GetColLwb()) {
         //Error("AMinusB(const TMatrixT &,const TMatrixTSparse &","matrices not compatible");
         return;
      }

      if (!constr && this->GetMatrixArray() == a.GetMatrixArray()) {
         //Error("AMinusB","this = &a");
         return;
      }

      if (!constr && this->GetMatrixArray() == b.GetMatrixArray()) {
         //Error("AMinusB","this = &b");
         return;
      }
   }

   if (constr) {
      Allocate(a.GetNrows(),a.GetNcols(),a.GetRowLwb(),a.GetColLwb());
      SetSparseIndexAB(a,b);
   }

   Int_t * const pRowIndexc = this->GetRowIndexArray();
   Int_t * const pColIndexc = this->GetColIndexArray();

   const Int_t * const pRowIndexb = b.GetRowIndexArray();
   const Int_t * const pColIndexb = b.GetColIndexArray();

   const Element * const pDataa = a.GetMatrixArray();
   const Element * const pDatab = b.GetMatrixArray();
   Element * const pDatac = this->GetMatrixArray();
   Int_t indexc_r = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexb = pRowIndexb[irowc];
      const Int_t eIndexb = pRowIndexb[irowc+1];
      const Int_t off = irowc*this->GetNcols();
      Int_t indexb = sIndexb;
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         Element sum = pDataa[off+icolc];
         while (indexb < eIndexb && pColIndexb[indexb] <= icolc) {
            if (icolc == pColIndexb[indexb]) {
               sum -= pDatab[indexb];
               break;
            }
            indexb++;
         }

         if (sum != 0.0) {
            pColIndexc[indexc_r] = icolc;
            pDatac[indexc_r] = sum;
            indexc_r++;
         }
      }
      pRowIndexc[irowc+1] = indexc_r;
   }

   if (constr)
      SetSparseIndex(indexc_r);
}

////////////////////////////////////////////////////////////////////////////////
/// Copy matrix data to array . It is assumed that array is of size >= fNelems

template<class Element>
void TMatrixTSparse<Element>::GetMatrix2Array(Element *data,Option_t * /*option*/) const
{
   //R__ASSERT(this->IsValid());

   const Element * const elem = GetMatrixArray();
   memcpy(data,elem,this->fNelems*sizeof(Element));
}

////////////////////////////////////////////////////////////////////////////////
/// Copy nr elements from row/col index and data array to matrix . It is assumed
/// that arrays are of size >= nr
/// Note that the input arrays are not passed as const since they will be modified !

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::SetMatrixArray(Int_t nr,Int_t *row,Int_t *col,Element *data)
{
   //R__ASSERT(this->IsValid());
   if (nr <= 0) {
      //Error("SetMatrixArray(Int_t,Int_t*,Int_t*,Element*","nr <= 0");
      return *this;
   }

   const Int_t irowmin = TMath::LocMin(nr,row);
   const Int_t irowmax = TMath::LocMax(nr,row);
   const Int_t icolmin = TMath::LocMin(nr,col);
   const Int_t icolmax = TMath::LocMax(nr,col);

   //R__ASSERT(row[irowmin] >= this->fRowLwb && row[irowmax] <= this->fRowLwb+this->fNrows-1);
   //R__ASSERT(col[icolmin] >= this->fColLwb && col[icolmax] <= this->fColLwb+this->fNcols-1);

   if (row[irowmin] < this->fRowLwb || row[irowmax] > this->fRowLwb+this->fNrows-1) {
      //Error("SetMatrixArray","Inconsistency between row index and its range");
      if (row[irowmin] < this->fRowLwb) {
         //Info("SetMatrixArray","row index lower bound adjusted to %d",row[irowmin]);
         this->fRowLwb = row[irowmin];
      }
      if (row[irowmax] > this->fRowLwb+this->fNrows-1) {
         //Info("SetMatrixArray","row index upper bound adjusted to %d",row[irowmax]);
         this->fNrows = row[irowmax]-this->fRowLwb+1;
      }
   }
   if (col[icolmin] < this->fColLwb || col[icolmax] > this->fColLwb+this->fNcols-1) {
      //Error("SetMatrixArray","Inconsistency between column index and its range");
      if (col[icolmin] < this->fColLwb) {
         //Info("SetMatrixArray","column index lower bound adjusted to %d",col[icolmin]);
         this->fColLwb = col[icolmin];
      }
      if (col[icolmax] > this->fColLwb+this->fNcols-1) {
         //Info("SetMatrixArray","column index upper bound adjusted to %d",col[icolmax]);
         this->fNcols = col[icolmax]-this->fColLwb+1;
      }
   }

   TMatrixTBase<Element>::DoubleLexSort(nr,row,col,data);

   Int_t nr_nonzeros = 0;
   const Element *ep        = data;
   const Element * const fp = data+nr;

   while (ep < fp)
      if (*ep++ != 0.0) nr_nonzeros++;

   if (nr_nonzeros != this->fNelems) {
      if (fColIndex) { delete [] fColIndex; fColIndex = 0; }
      if (fElements) { delete [] fElements; fElements = 0; }
      this->fNelems = nr_nonzeros;
      if (this->fNelems > 0) {
         fColIndex = new Int_t[nr_nonzeros];
         fElements = new Element[nr_nonzeros];
      } else {
         fColIndex = 0;
         fElements = 0;
      }
   }

   if (this->fNelems <= 0)
      return *this;

   fRowIndex[0] = 0;
   Int_t ielem = 0;
   nr_nonzeros = 0;
   for (Int_t irow = 1; irow < this->fNrows+1; irow++) {
      if (ielem < nr && row[ielem] < irow) {
         while (ielem < nr) {
            if (data[ielem] != 0.0) {
               fColIndex[nr_nonzeros] = col[ielem]-this->fColLwb;
               fElements[nr_nonzeros] = data[ielem];
               nr_nonzeros++;
            }
            ielem++;
            if (ielem >= nr || row[ielem] != row[ielem-1])
               break;
         }
      }
      fRowIndex[irow] = nr_nonzeros;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Increase/decrease the number of non-zero elements to nelems_new

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::SetSparseIndex(Int_t nelems_new)
{
   if (nelems_new != this->fNelems) {
      Int_t nr = TMath::Min(nelems_new,this->fNelems);
      Int_t *oIp = fColIndex;
      fColIndex = new Int_t[nelems_new];
      if (oIp) {
         memmove(fColIndex,oIp,nr*sizeof(Int_t));
         delete [] oIp;
      }
      Element *oDp = fElements;
      fElements = new Element[nelems_new];
      if (oDp) {
         memmove(fElements,oDp,nr*sizeof(Element));
         delete [] oDp;
      }
      this->fNelems = nelems_new;
      if (nelems_new > nr) {
         memset(fElements+nr,0,(nelems_new-nr)*sizeof(Element));
         memset(fColIndex+nr,0,(nelems_new-nr)*sizeof(Int_t));
      } else {
         for (Int_t irow = 0; irow < this->fNrowIndex; irow++)
            if (fRowIndex[irow] > nelems_new)
               fRowIndex[irow] = nelems_new;
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Use non-zero data of matrix source to set the sparse structure

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::SetSparseIndex(const TMatrixTBase<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(source.IsValid());
      if (this->GetNrows()  != source.GetNrows()  || this->GetNcols()  != source.GetNcols() ||
          this->GetRowLwb() != source.GetRowLwb() || this->GetColLwb() != source.GetColLwb()) {
         //Error("SetSparseIndex","matrices not compatible");
         return *this;
      }
   }

   const Int_t nr_nonzeros = source.NonZeros();

   if (nr_nonzeros != this->fNelems)
      SetSparseIndex(nr_nonzeros);

   if (source.GetRowIndexArray() && source.GetColIndexArray()) {
      memmove(fRowIndex,source.GetRowIndexArray(),this->fNrowIndex*sizeof(Int_t));
      memmove(fColIndex,source.GetColIndexArray(),this->fNelems*sizeof(Int_t));
   } else {
      const Element *ep = source.GetMatrixArray();
      Int_t nr = 0;
      for (Int_t irow = 0; irow < this->fNrows; irow++) {
         fRowIndex[irow] = nr;
         for (Int_t icol = 0; icol < this->fNcols; icol++) {
            if (*ep != 0.0) {
               fColIndex[nr] = icol;
               nr++;
            }
            ep++;
         }
      }
      fRowIndex[this->fNrows] = nr;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set the row/column indices to the "sum" of matrices a and b
/// It is checked that enough space has been allocated

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::SetSparseIndexAB(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNrows()  != b.GetNrows()  || a.GetNcols()  != b.GetNcols() ||
          a.GetRowLwb() != b.GetRowLwb() || a.GetColLwb() != b.GetColLwb()) {
         //Error("SetSparseIndexAB","source matrices not compatible");
         return *this;
      }

      if (this->GetNrows()  != a.GetNrows()  || this->GetNcols()  != a.GetNcols() ||
          this->GetRowLwb() != a.GetRowLwb() || this->GetColLwb() != a.GetColLwb()) {
         //Error("SetSparseIndexAB","matrix not compatible with source matrices");
         return *this;
      }
   }

   const Int_t * const pRowIndexa = a.GetRowIndexArray();
   const Int_t * const pRowIndexb = b.GetRowIndexArray();
   const Int_t * const pColIndexa = a.GetColIndexArray();
   const Int_t * const pColIndexb = b.GetColIndexArray();

   // Count first the number of non-zero slots that are needed
   Int_t nc = 0;
   for (Int_t irowc = 0; irowc < a.GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      const Int_t sIndexb = pRowIndexb[irowc];
      const Int_t eIndexb = pRowIndexb[irowc+1];
      nc += eIndexa-sIndexa;
      Int_t indexb = sIndexb;
      for (Int_t indexa = sIndexa; indexa < eIndexa; indexa++) {
         const Int_t icola = pColIndexa[indexa];
         for (; indexb < eIndexb; indexb++) {
            if (pColIndexb[indexb] >= icola) {
               if (pColIndexb[indexb] == icola)
                  indexb++;
               break;
            }
            nc++;
         }
      }
      while (indexb < eIndexb) {
         const Int_t icola = (eIndexa > sIndexa && eIndexa > 0) ? pColIndexa[eIndexa-1] : -1;
         if (pColIndexb[indexb++] > icola)
            nc++;
      }
   }

   // Allocate the necessary space in fRowIndex and fColIndex
   if (this->NonZeros() != nc)
      SetSparseIndex(nc);

   Int_t * const pRowIndexc = this->GetRowIndexArray();
   Int_t * const pColIndexc = this->GetColIndexArray();

   nc = 0;
   pRowIndexc[0] = 0;
   for (Int_t irowc = 0; irowc < a.GetNrows(); irowc++) {
      const Int_t sIndexa = pRowIndexa[irowc];
      const Int_t eIndexa = pRowIndexa[irowc+1];
      const Int_t sIndexb = pRowIndexb[irowc];
      const Int_t eIndexb = pRowIndexb[irowc+1];
      Int_t indexb = sIndexb;
      for (Int_t indexa = sIndexa; indexa < eIndexa; indexa++) {
         const Int_t icola = pColIndexa[indexa];
         for (; indexb < eIndexb; indexb++) {
            if (pColIndexb[indexb] >= icola) {
               if (pColIndexb[indexb] == icola)
                  indexb++;
               break;
            }
            pColIndexc[nc++] = pColIndexb[indexb];
         }
         pColIndexc[nc++] = pColIndexa[indexa];
      }
      while (indexb < eIndexb) {
         const Int_t icola = (eIndexa > 0) ? pColIndexa[eIndexa-1] : -1;
         if (pColIndexb[indexb++] > icola)
            pColIndexc[nc++] = pColIndexb[indexb-1];
      }
      pRowIndexc[irowc+1] = nc;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set the row/column indices to the "sum" of matrices a and b
/// It is checked that enough space has been allocated

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::SetSparseIndexAB(const TMatrixT<Element> &a,const TMatrixTSparse<Element> &b)
{
   if (gMatrixCheck) {
      //R__ASSERT(a.IsValid());
      //R__ASSERT(b.IsValid());

      if (a.GetNrows()  != b.GetNrows()  || a.GetNcols()  != b.GetNcols() ||
          a.GetRowLwb() != b.GetRowLwb() || a.GetColLwb() != b.GetColLwb()) {
         //Error("SetSparseIndexAB","source matrices not compatible");
         return *this;
      }

      if (this->GetNrows()  != a.GetNrows()  || this->GetNcols()  != a.GetNcols() ||
          this->GetRowLwb() != a.GetRowLwb() || this->GetColLwb() != a.GetColLwb()) {
         //Error("SetSparseIndexAB","matrix not compatible with source matrices");
         return *this;
      }
   }

   const Element * const pDataa = a.GetMatrixArray();

   const Int_t * const pRowIndexb = b.GetRowIndexArray();
   const Int_t * const pColIndexb = b.GetColIndexArray();

   // Count first the number of non-zero slots that are needed
   Int_t nc = a.NonZeros();
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexb = pRowIndexb[irowc];
      const Int_t eIndexb = pRowIndexb[irowc+1];
      const Int_t off = irowc*this->GetNcols();
      Int_t indexb = sIndexb;
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         if (pDataa[off+icolc] != 0.0 || pColIndexb[indexb] > icolc) continue;
         for (; indexb < eIndexb; indexb++) {
            if (pColIndexb[indexb] >= icolc) {
               if (pColIndexb[indexb] == icolc) {
                  nc++;
                  indexb++;
               }
               break;
            }
         }
      }
   }

   // Allocate the necessary space in fRowIndex and fColIndex
   if (this->NonZeros() != nc)
      SetSparseIndex(nc);

   Int_t * const pRowIndexc = this->GetRowIndexArray();
   Int_t * const pColIndexc = this->GetColIndexArray();

   nc = 0;
   pRowIndexc[0] = 0;
   for (Int_t irowc = 0; irowc < this->GetNrows(); irowc++) {
      const Int_t sIndexb = pRowIndexb[irowc];
      const Int_t eIndexb = pRowIndexb[irowc+1];
      const Int_t off = irowc*this->GetNcols();
      Int_t indexb = sIndexb;
      for (Int_t icolc = 0; icolc < this->GetNcols(); icolc++) {
         if (pDataa[off+icolc] != 0.0)
            pColIndexc[nc++] = icolc;
         else if (pColIndexb[indexb] <= icolc) {
            for (; indexb < eIndexb; indexb++) {
               if (pColIndexb[indexb] >= icolc) {
                  if (pColIndexb[indexb] == icolc)
                     pColIndexc[nc++] = pColIndexb[indexb++];
                  break;
               }
            }
         }
      }
      pRowIndexc[irowc+1] = nc;
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set size of the matrix to nrows x ncols with nr_nonzeros non-zero entries
/// if nr_nonzeros > 0 .
/// New dynamic elements are created, the overlapping part of the old ones are
/// copied to the new structures, then the old elements are deleted.

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::ResizeTo(Int_t nrows,Int_t ncols,Int_t nr_nonzeros)
{
   //R__ASSERT(this->IsValid());
   if (!this->fIsOwner) {
      //Error("ResizeTo(Int_t,Int_t,Int_t)","Not owner of data array,cannot resize");
      return *this;
   }

   if (this->fNelems > 0) {
      if (this->fNrows == nrows && this->fNcols == ncols &&
         (this->fNelems == nr_nonzeros || nr_nonzeros < 0))
         return *this;
      else if (nrows == 0 || ncols == 0 || nr_nonzeros == 0) {
         this->fNrows = nrows; this->fNcols = ncols;
         Clear();
         return *this;
      }

      const Element *elements_old = GetMatrixArray();
      const Int_t   *rowIndex_old = GetRowIndexArray();
      const Int_t   *colIndex_old = GetColIndexArray();

      Int_t nrows_old     = this->fNrows;
      Int_t nrowIndex_old = this->fNrowIndex;

      Int_t nelems_new;
      if (nr_nonzeros > 0)
         nelems_new = nr_nonzeros;
      else {
         nelems_new = 0;
         for (Int_t irow = 0; irow < nrows_old; irow++) {
            if (irow >= nrows) continue;
            const Int_t sIndex = rowIndex_old[irow];
            const Int_t eIndex = rowIndex_old[irow+1];
            for (Int_t index = sIndex; index < eIndex; index++) {
               const Int_t icol = colIndex_old[index];
               if (icol < ncols)
                  nelems_new++;
            }
         }
      }

      Allocate(nrows,ncols,0,0,1,nelems_new);
      //R__ASSERT(this->IsValid());

      Element *elements_new = GetMatrixArray();
      Int_t   *rowIndex_new = GetRowIndexArray();
      Int_t   *colIndex_new = GetColIndexArray();

      Int_t nelems_copy = 0;
      rowIndex_new[0] = 0;
      Bool_t cont = kTRUE;
      for (Int_t irow = 0; irow < nrows_old && cont; irow++) {
         if (irow >= nrows) continue;
         const Int_t sIndex = rowIndex_old[irow];
         const Int_t eIndex = rowIndex_old[irow+1];
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = colIndex_old[index];
            if (icol < ncols) {
               rowIndex_new[irow+1]      = nelems_copy+1;
               colIndex_new[nelems_copy] = icol;
               elements_new[nelems_copy] = elements_old[index];
               nelems_copy++;
            }
            if (nelems_copy >= nelems_new) {
               cont = kFALSE;
               break;
            }
         }
      }

      if (rowIndex_old) delete [] (Int_t*)   rowIndex_old;
      if (colIndex_old) delete [] (Int_t*)   colIndex_old;
      if (elements_old) delete [] (Element*) elements_old;

      if (nrowIndex_old < this->fNrowIndex) {
          for (Int_t irow = nrowIndex_old; irow < this->fNrowIndex; irow++)
            rowIndex_new[irow] = rowIndex_new[nrowIndex_old-1];
      }
   } else {
      const Int_t nelems_new = (nr_nonzeros >= 0) ? nr_nonzeros : 0;
      Allocate(nrows,ncols,0,0,1,nelems_new);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Set size of the matrix to [row_lwb:row_upb] x [col_lwb:col_upb] with nr_nonzeros
/// non-zero entries if nr_nonzeros > 0 .
/// New dynamic elements are created, the overlapping part of the old ones are
/// copied to the new structures, then the old elements are deleted.

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::ResizeTo(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                         Int_t nr_nonzeros)
{
   //R__ASSERT(this->IsValid());
   if (!this->fIsOwner) {
      //Error("ResizeTo(Int_t,Int_t,Int_t,Int_t,Int_t)","Not owner of data array,cannot resize");
      return *this;
   }

   const Int_t new_nrows = row_upb-row_lwb+1;
   const Int_t new_ncols = col_upb-col_lwb+1;

   if (this->fNelems > 0) {
      if (this->fNrows  == new_nrows && this->fNcols  == new_ncols &&
          this->fRowLwb == row_lwb   && this->fColLwb == col_lwb &&
          (this->fNelems == nr_nonzeros || nr_nonzeros < 0))
          return *this;
      else if (new_nrows == 0 || new_ncols == 0 || nr_nonzeros == 0) {
         this->fNrows = new_nrows; this->fNcols = new_ncols;
         this->fRowLwb = row_lwb; this->fColLwb = col_lwb;
         Clear();
         return *this;
      }

      const Int_t   *rowIndex_old = GetRowIndexArray();
      const Int_t   *colIndex_old = GetColIndexArray();
      const Element *elements_old = GetMatrixArray();

      const Int_t  nrowIndex_old = this->fNrowIndex;

      const Int_t  nrows_old     = this->fNrows;
      const Int_t  rowLwb_old    = this->fRowLwb;
      const Int_t  colLwb_old    = this->fColLwb;

      Int_t nelems_new;
      if (nr_nonzeros > 0)
         nelems_new = nr_nonzeros;
      else {
         nelems_new = 0;
         for (Int_t irow = 0; irow < nrows_old; irow++) {
            if (irow+rowLwb_old > row_upb || irow+rowLwb_old < row_lwb) continue;
            const Int_t sIndex = rowIndex_old[irow];
            const Int_t eIndex = rowIndex_old[irow+1];
            for (Int_t index = sIndex; index < eIndex; index++) {
               const Int_t icol = colIndex_old[index];
               if (icol+colLwb_old <= col_upb && icol+colLwb_old >= col_lwb)
                  nelems_new++;
            }
         }
      }

      Allocate(new_nrows,new_ncols,row_lwb,col_lwb,1,nelems_new);
      //R__ASSERT(this->IsValid());

      Int_t    *rowIndex_new = GetRowIndexArray();
      Int_t    *colIndex_new = GetColIndexArray();
      Element *elements_new = GetMatrixArray();

      Int_t nelems_copy = 0;
      rowIndex_new[0] = 0;
      const Int_t row_off = rowLwb_old-row_lwb;
      const Int_t col_off = colLwb_old-col_lwb;
      for (Int_t irow = 0; irow < nrows_old; irow++) {
         if (irow+rowLwb_old > row_upb || irow+rowLwb_old < row_lwb) continue;
         const Int_t sIndex = rowIndex_old[irow];
         const Int_t eIndex = rowIndex_old[irow+1];
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = colIndex_old[index];
            if (icol+colLwb_old <= col_upb && icol+colLwb_old >= col_lwb) {
               rowIndex_new[irow+row_off+1] = nelems_copy+1;
               colIndex_new[nelems_copy]    = icol+col_off;
               elements_new[nelems_copy]    = elements_old[index];
               nelems_copy++;
            }
            if (nelems_copy >= nelems_new) {
               break;
            }
         }
      }

      if (rowIndex_old) delete [] (Int_t*)   rowIndex_old;
      if (colIndex_old) delete [] (Int_t*)   colIndex_old;
      if (elements_old) delete [] (Element*) elements_old;

      if (nrowIndex_old < this->fNrowIndex) {
         for (Int_t irow = nrowIndex_old; irow < this->fNrowIndex; irow++)
            rowIndex_new[irow] = rowIndex_new[nrowIndex_old-1];
      }
   } else {
      const Int_t nelems_new = (nr_nonzeros >= 0) ? nr_nonzeros : 0;
      Allocate(new_nrows,new_ncols,row_lwb,col_lwb,1,nelems_new);
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::Use(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                      Int_t nr_nonzeros,Int_t *pRowIndex,Int_t *pColIndex,Element *pData)
{
   if (gMatrixCheck) {
      if (row_upb < row_lwb) {
         //Error("Use","row_upb=%d < row_lwb=%d",row_upb,row_lwb);
         return *this;
      }
      if (col_upb < col_lwb) {
         //Error("Use","col_upb=%d < col_lwb=%d",col_upb,col_lwb);
         return *this;
      }
   }

   Clear();

   this->fNrows     = row_upb-row_lwb+1;
   this->fNcols     = col_upb-col_lwb+1;
   this->fRowLwb    = row_lwb;
   this->fColLwb    = col_lwb;
   this->fNrowIndex = this->fNrows+1;
   this->fNelems    = nr_nonzeros;
   this->fIsOwner   = kFALSE;
   this->fTol       = std::numeric_limits<Element>::epsilon();

   fElements  = pData;
   fRowIndex  = pRowIndex;
   fColIndex  = pColIndex;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Get submatrix [row_lwb..row_upb][col_lwb..col_upb]; The indexing range of the
/// returned matrix depends on the argument option:
///
/// option == "S" : return [0..row_upb-row_lwb+1][0..col_upb-col_lwb+1] (default)
/// else          : return [row_lwb..row_upb][col_lwb..col_upb]

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::GetSub(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                       TMatrixTBase<Element> &target,Option_t *option) const
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_lwb out-of-bounds");
         return target;
      }
      if (col_lwb < this->fColLwb || col_lwb > this->fColLwb+this->fNcols-1) {
         //Error("GetSub","col_lwb out-of-bounds");
         return target;
      }
      if (row_upb < this->fRowLwb || row_upb > this->fRowLwb+this->fNrows-1) {
         //Error("GetSub","row_upb out-of-bounds");
         return target;
      }
      if (col_upb < this->fColLwb || col_upb > this->fColLwb+this->fNcols-1) {
         //Error("GetSub","col_upb out-of-bounds");
         return target;
      }
      if (row_upb < row_lwb || col_upb < col_lwb) {
         //Error("GetSub","row_upb < row_lwb || col_upb < col_lwb");
         return target;
      }
   }

   TString opt(option);
   opt.ToUpper();
   const Int_t shift = (opt.Contains("S")) ? 1 : 0;

   const Int_t row_lwb_sub = (shift) ? 0               : row_lwb;
   const Int_t row_upb_sub = (shift) ? row_upb-row_lwb : row_upb;
   const Int_t col_lwb_sub = (shift) ? 0               : col_lwb;
   const Int_t col_upb_sub = (shift) ? col_upb-col_lwb : col_upb;

   Int_t nr_nonzeros = 0;
   for (Int_t irow = 0; irow < this->fNrows; irow++) {
      if (irow+this->fRowLwb > row_upb || irow+this->fRowLwb < row_lwb) continue;
      const Int_t sIndex = fRowIndex[irow];
      const Int_t eIndex = fRowIndex[irow+1];
      for (Int_t index = sIndex; index < eIndex; index++) {
         const Int_t icol = fColIndex[index];
         if (icol+this->fColLwb <= col_upb && icol+this->fColLwb >= col_lwb)
            nr_nonzeros++;
      }
   }

   target.ResizeTo(row_lwb_sub,row_upb_sub,col_lwb_sub,col_upb_sub,nr_nonzeros);

   const Element *ep = this->GetMatrixArray();

   Int_t   *rowIndex_sub = target.GetRowIndexArray();
   Int_t   *colIndex_sub = target.GetColIndexArray();
   Element *ep_sub       = target.GetMatrixArray();

   if (target.GetRowIndexArray() && target.GetColIndexArray()) {
      Int_t nelems_copy = 0;
      rowIndex_sub[0] = 0;
      const Int_t row_off = this->fRowLwb-row_lwb;
      const Int_t col_off = this->fColLwb-col_lwb;
      for (Int_t irow = 0; irow < this->fNrows; irow++) {
         if (irow+this->fRowLwb > row_upb || irow+this->fRowLwb < row_lwb) continue;
         const Int_t sIndex = fRowIndex[irow];
         const Int_t eIndex = fRowIndex[irow+1];
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = fColIndex[index];
            if (icol+this->fColLwb <= col_upb && icol+this->fColLwb >= col_lwb) {
               rowIndex_sub[irow+row_off+1] = nelems_copy+1;
               colIndex_sub[nelems_copy]    = icol+col_off;
               ep_sub[nelems_copy]          = ep[index];
               nelems_copy++;
            }
         }
      }
   } else {
      const Int_t row_off = this->fRowLwb-row_lwb;
      const Int_t col_off = this->fColLwb-col_lwb;
      const Int_t ncols_sub = col_upb_sub-col_lwb_sub+1;
      for (Int_t irow = 0; irow < this->fNrows; irow++) {
         if (irow+this->fRowLwb > row_upb || irow+this->fRowLwb < row_lwb) continue;
         const Int_t sIndex = fRowIndex[irow];
         const Int_t eIndex = fRowIndex[irow+1];
         const Int_t off = (irow+row_off)*ncols_sub;
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = fColIndex[index];
            if (icol+this->fColLwb <= col_upb && icol+this->fColLwb >= col_lwb)
               ep_sub[off+icol+col_off] = ep[index];
         }
      }
    }

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Insert matrix source starting at [row_lwb][col_lwb], thereby overwriting the part
/// [row_lwb..row_lwb+nrows_source-1][col_lwb..col_lwb+ncols_source-1];

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::SetSub(Int_t row_lwb,Int_t col_lwb,const TMatrixTBase<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());

      if (row_lwb < this->fRowLwb || row_lwb > this->fRowLwb+this->fNrows-1) {
         //Error("SetSub","row_lwb out-of-bounds");
         return *this;
      }
      if (col_lwb < this->fColLwb || col_lwb > this->fColLwb+this->fNcols-1) {
         //Error("SetSub","col_lwb out-of-bounds");
         return *this;
      }
      if (row_lwb+source.GetNrows() > this->fRowLwb+this->fNrows || col_lwb+source.GetNcols() > this->fColLwb+this->fNcols) {
         //Error("SetSub","source matrix too large");
         return *this;
      }
   }

   const Int_t nRows_source = source.GetNrows();
   const Int_t nCols_source = source.GetNcols();

   // Determine how many non-zero's are already available in
   // [row_lwb..row_lwb+nrows_source-1][col_lwb..col_lwb+ncols_source-1]
   Int_t nr_nonzeros = 0;
   for (Int_t irow = 0; irow < this->fNrows; irow++) {
      if (irow+this->fRowLwb >= row_lwb+nRows_source || irow+this->fRowLwb < row_lwb) continue;
      const Int_t sIndex = fRowIndex[irow];
      const Int_t eIndex = fRowIndex[irow+1];
      for (Int_t index = sIndex; index < eIndex; index++) {
         const Int_t icol = fColIndex[index];
         if (icol+this->fColLwb < col_lwb+nCols_source && icol+this->fColLwb >= col_lwb)
            nr_nonzeros++;
      }
   }

   const Int_t   *rowIndex_s = source.GetRowIndexArray();
   const Int_t   *colIndex_s = source.GetColIndexArray();
   const Element *elements_s = source.GetMatrixArray();

   const Int_t nelems_old = this->fNelems;
   const Int_t   *rowIndex_old = GetRowIndexArray();
   const Int_t   *colIndex_old = GetColIndexArray();
   const Element *elements_old = GetMatrixArray();

   const Int_t nelems_new = nelems_old+source.NonZeros()-nr_nonzeros;
   fRowIndex = new Int_t[this->fNrowIndex];
   fColIndex = new Int_t[nelems_new];
   fElements = new Element[nelems_new];
   this->fNelems   = nelems_new;

   Int_t   *rowIndex_new = GetRowIndexArray();
   Int_t   *colIndex_new = GetColIndexArray();
   Element *elements_new = GetMatrixArray();

   const Int_t row_off = row_lwb-this->fRowLwb;
   const Int_t col_off = col_lwb-this->fColLwb;

   Int_t nr = 0;
   rowIndex_new[0] = 0;
   for (Int_t irow = 0; irow < this->fNrows; irow++) {
      rowIndex_new[irow+1] = rowIndex_new[irow];
      Bool_t flagRow = kFALSE;
      if (irow+this->fRowLwb < row_lwb+nRows_source && irow+this->fRowLwb >= row_lwb)
         flagRow = kTRUE;

      const Int_t sIndex_o = rowIndex_old[irow];
      const Int_t eIndex_o = rowIndex_old[irow+1];

      if (flagRow) {
         const Int_t icol_left = col_off-1;
         const Int_t left = TMath::BinarySearch(eIndex_o-sIndex_o,colIndex_old+sIndex_o,icol_left)+sIndex_o;
         for (Int_t index = sIndex_o; index <= left; index++) {
            rowIndex_new[irow+1]++;
            colIndex_new[nr] = colIndex_old[index];
            elements_new[nr] = elements_old[index];
            nr++;
         }

         if (rowIndex_s && colIndex_s) {
            const Int_t sIndex_s = rowIndex_s[irow-row_off];
            const Int_t eIndex_s = rowIndex_s[irow-row_off+1];
            for (Int_t index = sIndex_s; index < eIndex_s; index++) {
               rowIndex_new[irow+1]++;
               colIndex_new[nr] = colIndex_s[index]+col_off;
               elements_new[nr] = elements_s[index];
               nr++;
            }
         } else {
            const Int_t off = (irow-row_off)*nCols_source;
            for (Int_t icol = 0; icol < nCols_source; icol++) {
                rowIndex_new[irow+1]++;
                colIndex_new[nr] = icol+col_off;
                elements_new[nr] = elements_s[off+icol];
                nr++;
            }
         }

         const Int_t icol_right = col_off+nCols_source-1;
         if (colIndex_old) {
            Int_t right = TMath::BinarySearch(eIndex_o-sIndex_o,colIndex_old+sIndex_o,icol_right)+sIndex_o;
            while (right < eIndex_o-1 && colIndex_old[right+1] <= icol_right)
               right++;
            right++;

            for (Int_t index = right; index < eIndex_o; index++) {
               rowIndex_new[irow+1]++;
               colIndex_new[nr] = colIndex_old[index];
               elements_new[nr] = elements_old[index];
               nr++;
            }
         }
      } else {
         for (Int_t index = sIndex_o; index < eIndex_o; index++) {
            rowIndex_new[irow+1]++;
            colIndex_new[nr] = colIndex_old[index];
            elements_new[nr] = elements_old[index];
            nr++;
         }
      }
   }

   //R__ASSERT(this->fNelems == fRowIndex[this->fNrowIndex-1]);

   if (rowIndex_old) delete [] (Int_t*)    rowIndex_old;
   if (colIndex_old) delete [] (Int_t*)    colIndex_old;
   if (elements_old) delete [] (Element*) elements_old;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Transpose a matrix.

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::Transpose(const TMatrixTSparse<Element> &source)
{
   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());
      //R__ASSERT(source.IsValid());

      if (this->fNrows  != source.GetNcols()  || this->fNcols  != source.GetNrows() ||
          this->fRowLwb != source.GetColLwb() || this->fColLwb != source.GetRowLwb()) {
         //Error("Transpose","matrix has wrong shape");
         return *this;
      }

      if (source.NonZeros() <= 0)
         return *this;
   }

   const Int_t nr_nonzeros = source.NonZeros();

   const Int_t   * const pRowIndex_s = source.GetRowIndexArray();
   const Int_t   * const pColIndex_s = source.GetColIndexArray();
   const Element * const pData_s     = source.GetMatrixArray();

   Int_t   *rownr   = new Int_t  [nr_nonzeros];
   Int_t   *colnr   = new Int_t  [nr_nonzeros];
   Element *pData_t = new Element[nr_nonzeros];

   Int_t ielem = 0;
   for (Int_t irow_s = 0; irow_s < source.GetNrows(); irow_s++) {
      const Int_t sIndex = pRowIndex_s[irow_s];
      const Int_t eIndex = pRowIndex_s[irow_s+1];
      for (Int_t index = sIndex; index < eIndex; index++) {
         rownr[ielem]   = pColIndex_s[index]+this->fRowLwb;
         colnr[ielem]   = irow_s+this->fColLwb;
         pData_t[ielem] = pData_s[index];
         ielem++;
      }
   }

   //R__ASSERT(nr_nonzeros >= ielem);

   TMatrixTBase<Element>::DoubleLexSort(nr_nonzeros,rownr,colnr,pData_t);
   SetMatrixArray(nr_nonzeros,rownr,colnr,pData_t);

   //R__ASSERT(this->fNelems == fRowIndex[this->fNrowIndex-1]);

   if (pData_t) delete [] pData_t;
   if (rownr)   delete [] rownr;
   if (colnr)   delete [] colnr;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::Zero()
{
   //R__ASSERT(this->IsValid());

   if (fElements) { delete [] fElements; fElements = 0; }
   if (fColIndex) { delete [] fColIndex; fColIndex = 0; }
   this->fNelems = 0;
   memset(this->GetRowIndexArray(),0,this->fNrowIndex*sizeof(Int_t));

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Make a unit matrix (matrix need not be a square one).

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::UnitMatrix()
{
   //R__ASSERT(this->IsValid());

   Int_t i;

   Int_t nr_nonzeros = 0;
   for (i = this->fRowLwb; i <= this->fRowLwb+this->fNrows-1; i++)
      for (Int_t j = this->fColLwb; j <= this->fColLwb+this->fNcols-1; j++)
         if (i == j) nr_nonzeros++;

   if (nr_nonzeros != this->fNelems) {
      this->fNelems = nr_nonzeros;
      Int_t *oIp = fColIndex;
      fColIndex = new Int_t[nr_nonzeros];
      if (oIp) delete [] oIp;
      Element *oDp = fElements;
      fElements = new Element[nr_nonzeros];
      if (oDp) delete [] oDp;
   }

   Int_t ielem = 0;
   fRowIndex[0] = 0;
   for (i = this->fRowLwb; i <= this->fRowLwb+this->fNrows-1; i++) {
      for (Int_t j = this->fColLwb; j <= this->fColLwb+this->fNcols-1; j++) {
         if (i == j) {
            const Int_t irow = i-this->fRowLwb;
            fRowIndex[irow+1]  = ielem+1;
            fElements[ielem]   = 1.0;
            fColIndex[ielem++] = j-this->fColLwb;
         }
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Row matrix norm, MAX{ SUM{ |M(i,j)|, over j}, over i}.
/// The norm is induced by the infinity vector norm.

template<class Element>
Element TMatrixTSparse<Element>::RowNorm() const
{
   //R__ASSERT(this->IsValid());

   const Element *       ep = GetMatrixArray();
   const Element * const fp = ep+this->fNelems;
   const Int_t   * const pR = GetRowIndexArray();
         Element norm = 0;

   // Scan the matrix row-after-row
   for (Int_t irow = 0; irow < this->fNrows; irow++) {
      const Int_t sIndex = pR[irow];
      const Int_t eIndex = pR[irow+1];
      Element sum = 0;
      for (Int_t index = sIndex; index < eIndex; index++)
          sum += TMath::Abs(*ep++);
      norm = TMath::Max(norm,sum);
   }

   //R__ASSERT(ep == fp);

   return norm;
}

////////////////////////////////////////////////////////////////////////////////
/// Column matrix norm, MAX{ SUM{ |M(i,j)|, over i}, over j}.
/// The norm is induced by the 1 vector norm.

template<class Element>
Element TMatrixTSparse<Element>::ColNorm() const
{
   //R__ASSERT(this->IsValid());

   const TMatrixTSparse<Element> mt(kTransposed,*this);

   const Element *       ep = mt.GetMatrixArray();
   const Element * const fp = ep+this->fNcols;
         Element norm = 0;

   // Scan the matrix col-after-col
   while (ep < fp) {
      Element sum = 0;
      // Scan a col to compute the sum
      for (Int_t i = 0; i < this->fNrows; i++,ep += this->fNcols)
         sum += TMath::Abs(*ep);
      ep -= this->fNelems-1;         // Point ep to the beginning of the next col
      norm = TMath::Max(norm,sum);
   }

   //R__ASSERT(ep == fp);

   return norm;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Element &TMatrixTSparse<Element>::operator()(Int_t rown,Int_t coln)
{
   //R__ASSERT(this->IsValid());

   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;
   if (arown >= this->fNrows || arown < 0) {
      //Error("operator()","Request row(%d) outside matrix range of %d - %d",rown,this->fRowLwb,this->fRowLwb+this->fNrows);
      return fElements[0];
   }
   if (acoln >= this->fNcols || acoln < 0) {
      //Error("operator()","Request column(%d) outside matrix range of %d - %d",coln,this->fColLwb,this->fColLwb+this->fNcols);
      return fElements[0];
   }

   Int_t index = -1;
   Int_t sIndex = 0;
   Int_t eIndex = 0;
   if (this->fNrowIndex > 0 && fRowIndex[this->fNrowIndex-1] != 0) {
      sIndex = fRowIndex[arown];
      eIndex = fRowIndex[arown+1];
      index = TMath::BinarySearch(eIndex-sIndex,fColIndex+sIndex,acoln)+sIndex;
   }

   if (index >= sIndex && fColIndex[index] == acoln)
      return fElements[index];
   else {
      Element val = 0.;
      InsertRow(rown,coln,&val,1);
      sIndex = fRowIndex[arown];
      eIndex = fRowIndex[arown+1];
      index = TMath::BinarySearch(eIndex-sIndex,fColIndex+sIndex,acoln)+sIndex;
      if (index >= sIndex && fColIndex[index] == acoln)
         return fElements[index];
      else {
         //Error("operator()(Int_t,Int_t","Insert row failed");
         return fElements[0];
      }
   }
}

////////////////////////////////////////////////////////////////////////////////

template <class Element>
Element TMatrixTSparse<Element>::operator()(Int_t rown,Int_t coln) const
{
   //R__ASSERT(this->IsValid());
   if (this->fNrowIndex > 0 && this->fRowIndex[this->fNrowIndex-1] == 0) {
      //Error("operator()(Int_t,Int_t) const","row/col indices are not set");
      //Info("operator()","fNrowIndex = %d fRowIndex[fNrowIndex-1] = %d\n",this->fNrowIndex,this->fRowIndex[this->fNrowIndex-1]);
      return 0.0;
   }
   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;

   if (arown >= this->fNrows || arown < 0) {
      //Error("operator()","Request row(%d) outside matrix range of %d - %d",rown,this->fRowLwb,this->fRowLwb+this->fNrows);
      return 0.0;
   }
   if (acoln >= this->fNcols || acoln < 0) {
      //Error("operator()","Request column(%d) outside matrix range of %d - %d",coln,this->fColLwb,this->fColLwb+this->fNcols);
      return 0.0;
   }

   const Int_t sIndex = fRowIndex[arown];
   const Int_t eIndex = fRowIndex[arown+1];
   const Int_t index = (Int_t)TMath::BinarySearch(eIndex-sIndex,fColIndex+sIndex,acoln)+sIndex;
   if (index < sIndex || fColIndex[index] != acoln) return 0.0;
   else                                             return fElements[index];
}

////////////////////////////////////////////////////////////////////////////////
/// Notice that the sparsity of the matrix is NOT changed : its fRowIndex/fColIndex
/// are used !

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::operator=(const TMatrixTSparse<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,source)) {
      //Error("operator=(const TMatrixTSparse &)","matrices not compatible");
      return *this;
   }

   if (this->GetMatrixArray() != source.GetMatrixArray()) {
      //TObject::operator=(source);

      const Element * const sp = source.GetMatrixArray();
            Element * const tp = this->GetMatrixArray();
      memcpy(tp,sp,this->fNelems*sizeof(Element));
      this->fTol = source.GetTol();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Notice that the sparsity of the matrix is NOT changed : its fRowIndex/fColIndex
/// are used !

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::operator=(const TMatrixT<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(*this,(TMatrixTBase<Element> &)source)) {
      //Error("operator=(const TMatrixT &)","matrices not compatible");
      return *this;
   }

   if (this->GetMatrixArray() != source.GetMatrixArray()) {
      //TObject::operator=(source);

      const Element * const sp = source.GetMatrixArray();
            Element * const tp = this->GetMatrixArray();
      for (Int_t irow = 0; irow < this->fNrows; irow++) {
         const Int_t sIndex = fRowIndex[irow];
         const Int_t eIndex = fRowIndex[irow+1];
         const Int_t off = irow*this->fNcols;
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = fColIndex[index];
            tp[index] = sp[off+icol];
         }
      }
      this->fTol = source.GetTol();
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Assign val to every element of the matrix. Check that the row/col
/// indices are set !

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::operator=(Element val)
{
   //R__ASSERT(this->IsValid());

   if (fRowIndex[this->fNrowIndex-1] == 0) {
      //Error("operator=(Element","row/col indices are not set");
      return *this;
   }

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ = val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Add val to every element of the matrix.

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::operator+=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ += val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtract val from every element of the matrix.

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::operator-=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ -= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply every element of the matrix with val.

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::operator*=(Element val)
{
   //R__ASSERT(this->IsValid());

   Element *ep = this->GetMatrixArray();
   const Element * const ep_last = ep+this->fNelems;
   while (ep < ep_last)
      *ep++ *= val;

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// randomize matrix element values

template<class Element>
TMatrixTBase<Element> &TMatrixTSparse<Element>::Randomize(Element alpha,Element beta,Double_t &seed)
{
   //R__ASSERT(this->IsValid());

   const Element scale = beta-alpha;
   const Element shift = alpha/scale;

   Int_t   * const pRowIndex = GetRowIndexArray();
   Int_t   * const pColIndex = GetColIndexArray();
   Element * const ep        = GetMatrixArray();

   const Int_t m = this->GetNrows();
   const Int_t n = this->GetNcols();

   // Knuth's algorithm for choosing "length" elements out of nn .
   const Int_t nn     = this->GetNrows()*this->GetNcols();
   const Int_t length = (this->GetNoElements() <= nn) ? this->GetNoElements() : nn;
   Int_t chosen   = 0;
   Int_t icurrent = 0;
   pRowIndex[0] = 0;
   for (Int_t k = 0; k < nn; k++) {
      const Element r = Drand(seed);

      if ((nn-k)*r < length-chosen) {
         pColIndex[chosen] = k%n;
         const Int_t irow  = k/n;

         if (irow > icurrent) {
            for ( ; icurrent < irow; icurrent++)
               pRowIndex[icurrent+1] = chosen;
         }
         ep[chosen] = scale*(Drand(seed)+shift);
         chosen++;
      }
   }
   for ( ; icurrent < m; icurrent++)
      pRowIndex[icurrent+1] = length;

   //R__ASSERT(chosen == length);

   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// randomize matrix element values but keep matrix symmetric positive definite

template<class Element>
TMatrixTSparse<Element> &TMatrixTSparse<Element>::RandomizePD(Element alpha,Element beta,Double_t &seed)
{
   const Element scale = beta-alpha;
   const Element shift = alpha/scale;

   if (gMatrixCheck) {
      //R__ASSERT(this->IsValid());

      if (this->fNrows != this->fNcols || this->fRowLwb != this->fColLwb) {
         //Error("RandomizePD(Element &","matrix should be square");
         return *this;
      }
   }

   const Int_t n = this->fNcols;

   Int_t   * const pRowIndex = this->GetRowIndexArray();
   Int_t   * const pColIndex = this->GetColIndexArray();
   Element * const ep        = GetMatrixArray();

   // We will always have non-zeros on the diagonal, so there
   // is no randomness there. In fact, choose the (0,0) element now
   pRowIndex[0] = 0;
   pColIndex[0] = 0;
   pRowIndex[1] = 1;
   ep[0]        = 1e-8+scale*(Drand(seed)+shift);

   // Knuth's algorithm for choosing length elements out of nn .
   // nn here is the number of elements in the strict lower triangle.
   const Int_t nn = n*(n-1)/2;

   // length is the number of elements that can be stored, minus the number
   // of elements in the diagonal, which will always be in the matrix.
   //  Int_t length = (this->fNelems-n)/2;
   Int_t length = this->fNelems-n;
   length = (length <= nn) ? length : nn;

   // chosen   : the number of elements that have already been chosen (now 0)
   // nnz      : the number of non-zeros in the matrix (now 1, because the
   //            (0,0) element is already in the matrix.
   // icurrent : the index of the last row whose start has been stored in pRowIndex;

   Int_t chosen   = 0;
   Int_t icurrent = 1;
   Int_t nnz      = 1;
   for (Int_t k = 0; k < nn; k++ ) {
      const Element r = Drand(seed);

      if( (nn-k)*r < length-chosen) {
         // Element k is chosen. What row is it in?
         // In a lower triangular matrix (including a diagonal), it will be in
         // the largest row such that row*(row+1)/2 < k. In other words

         Int_t row = (int) TMath::Floor((-1+TMath::Sqrt(1.0+8.0*k))/2);
         // and its column will be the remainder
         Int_t col = k-row*(row+1)/2;
         // but since we are only filling in the *strict* lower triangle of
         // the matrix, we shift the row by 1
         row++;

         if (row > icurrent) {
            // We have chosen a row beyond the current row.
            // Choose a diagonal element for each intermediate row and fix the
            // data structure.
            for ( ; icurrent < row; icurrent++) {
               // Choose the diagonal
               ep[nnz] = 0.0;
               for (Int_t ll = pRowIndex[icurrent]; ll < nnz; ll++)
                  ep[nnz] += TMath::Abs(ep[ll]);
               ep[nnz] +=  1e-8+scale*(Drand(seed)+shift);
               pColIndex[nnz] = icurrent;

               nnz++;
               pRowIndex[icurrent+1] = nnz;
            }
         } // end if we have chosen a row beyond the current row;
         ep[nnz] = scale*(Drand(seed)+shift);
         pColIndex[nnz] = col;
         // add the value of this element (which occurs symmetrically in the
         // upper triangle) to the appropriate diagonal element
         ep[pRowIndex[col+1]-1] += TMath::Abs(ep[nnz]);

         nnz++; // We have added another element to the matrix
         chosen++; // And finished choosing another element.
      }
   }

   //R__ASSERT(chosen == length);

   // and of course, we must choose all remaining diagonal elements .
   for ( ; icurrent < n; icurrent++) {
      // Choose the diagonal
      ep[nnz] = 0.0;
      for(Int_t ll = pRowIndex[icurrent]; ll < nnz; ll++)
         ep[nnz] += TMath::Abs(ep[ll]);
      ep[nnz] += 1e-8+scale*(Drand(seed)+shift);
      pColIndex[nnz] = icurrent;

      nnz++;
      pRowIndex[icurrent+1] = nnz;
   }
   this->fNelems = nnz;

   TMatrixTSparse<Element> tmp(TMatrixTSparse<Element>::kTransposed,*this);
   *this += tmp;

   // make sure to divide the diagonal by 2 because the operation
   // *this += tmp; adds the diagonal again
   {
      const Int_t    * const pR = this->GetRowIndexArray();
      const Int_t    * const pC = this->GetColIndexArray();
             Element * const pD = GetMatrixArray();
      for (Int_t irow = 0; irow < this->fNrows+1; irow++) {
         const Int_t sIndex = pR[irow];
         const Int_t eIndex = pR[irow+1];
         for (Int_t index = sIndex; index < eIndex; index++) {
            const Int_t icol = pC[index];
            if (irow == icol)
               pD[index] /= 2.;
         }
      }
   }

   return *this;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator+(const TMatrixTSparse<Element> &source1,const TMatrixTSparse<Element> &source2)
{
  TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kPlus,source2);
  return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator+(const TMatrixTSparse<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kPlus,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator+(const TMatrixT<Element> &source1,const TMatrixTSparse<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kPlus,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator+(const TMatrixTSparse<Element> &source,Element val)
{
   TMatrixTSparse<Element> target(source);
   target += val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator+(Element val,const TMatrixTSparse<Element> &source)
{
   TMatrixTSparse<Element> target(source);
   target += val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator-(const TMatrixTSparse<Element> &source1,const TMatrixTSparse<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kMinus,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator-(const TMatrixTSparse<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kMinus,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator-(const TMatrixT<Element> &source1,const TMatrixTSparse<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kMinus,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator-(const TMatrixTSparse<Element> &source,Element val)
{
   TMatrixTSparse<Element> target(source);
   target -= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator-(Element val,const TMatrixTSparse<Element> &source)
{
   TMatrixTSparse<Element> target(source);
   target -= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator*(const TMatrixTSparse<Element> &source1,const TMatrixTSparse<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kMult,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator*(const TMatrixTSparse<Element> &source1,const TMatrixT<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kMult,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator*(const TMatrixT<Element> &source1,const TMatrixTSparse<Element> &source2)
{
   TMatrixTSparse<Element> target(source1,TMatrixTSparse<Element>::kMult,source2);
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator*(Element val,const TMatrixTSparse<Element> &source)
{
   TMatrixTSparse<Element> target(source);
   target *= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
TMatrixTSparse<Element> operator*(const TMatrixTSparse<Element> &source,Element val)
{
   TMatrixTSparse<Element> target(source);
   target *= val;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Modify addition: target += scalar * source.

template<class Element>
TMatrixTSparse<Element> &Add(TMatrixTSparse<Element> &target,Element scalar,const TMatrixTSparse<Element> &source)
{
   target += scalar * source;
   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Multiply target by the source, element-by-element.

template<class Element>
TMatrixTSparse<Element> &ElementMult(TMatrixTSparse<Element> &target,const TMatrixTSparse<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementMult(TMatrixTSparse &,const TMatrixTSparse &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   while ( tp < ftp )
      *tp++ *= *sp++;

   return target;
}

////////////////////////////////////////////////////////////////////////////////
/// Divide target by the source, element-by-element.

template<class Element>
TMatrixTSparse<Element> &ElementDiv(TMatrixTSparse<Element> &target,const TMatrixTSparse<Element> &source)
{
   if (gMatrixCheck && !AreCompatible(target,source)) {
      //::Error("ElementDiv(TMatrixT &,const TMatrixT &)","matrices not compatible");
      return target;
   }

   const Element *sp  = source.GetMatrixArray();
         Element *tp  = target.GetMatrixArray();
   const Element *ftp = tp+target.GetNoElements();
   while ( tp < ftp ) {
      if (*sp != 0.0)
         *tp++ /= *sp++;
      else {
         //Error("ElementDiv","source element is zero");
         tp++;
      }
   }

   return target;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Bool_t AreCompatible(const TMatrixTSparse<Element> &m1,const TMatrixTSparse<Element> &m2,Int_t verbose)
{
   //if (!m1.IsValid()) {
      //if (verbose)
         //::Error("AreCompatible", "matrix 1 not valid");
      //return kFALSE;
   //}
   //if (!m2.IsValid()) {
      //if (verbose)
         //::Error("AreCompatible", "matrix 2 not valid");
      //return kFALSE;
   //}

   if (m1.GetNrows()  != m2.GetNrows()  || m1.GetNcols()  != m2.GetNcols() ||
       m1.GetRowLwb() != m2.GetRowLwb() || m1.GetColLwb() != m2.GetColLwb()) {
      if (verbose) {}
         //::Error("AreCompatible", "matrices 1 and 2 not compatible");
      return kFALSE;
   }

   const Int_t *pR1 = m1.GetRowIndexArray();
   const Int_t *pR2 = m2.GetRowIndexArray();
   const Int_t nRows = m1.GetNrows();
   if (memcmp(pR1,pR2,(nRows+1)*sizeof(Int_t))) {
      if (verbose) {}
         //::Error("AreCompatible", "matrices 1 and 2 have different rowIndex");
      for (Int_t i = 0; i < nRows+1; i++)
         printf("%d: %d %d\n",i,pR1[i],pR2[i]);
      return kFALSE;
   }
   const Int_t *pD1 = m1.GetColIndexArray();
   const Int_t *pD2 = m2.GetColIndexArray();
   const Int_t nData = m1.GetNoElements();
   if (memcmp(pD1,pD2,nData*sizeof(Int_t))) {
      if (verbose) {}
         //::Error("AreCompatible", "matrices 1 and 2 have different colIndex");
      for (Int_t i = 0; i < nData; i++)
         printf("%d: %d %d\n",i,pD1[i],pD2[i]);
      return kFALSE;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Stream an object of class TMatrixTSparse.
/*
template<class Element>
void TMatrixTSparse<Element>::Streamer(TBuffer &R__b)
{
   if (R__b.IsReading()) {
      UInt_t R__s, R__c;
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c);
      Clear();
      R__b.ReadClassBuffer(TMatrixTSparse<Element>::Class(),this,R__v,R__s,R__c);
      if (this->fNelems < 0)
         this->Invalidate();
      } else {
         R__b.WriteClassBuffer(TMatrixTSparse<Element>::Class(),this);
   }
}
*/
template class TMatrixTSparse<Float_t>;

//#include "TMatrixFSparsefwd.h"
//#include "TMatrixFfwd.h"

template TMatrixFSparse  operator+    <Float_t>(const TMatrixFSparse &source1,const TMatrixFSparse &source2);
template TMatrixFSparse  operator+    <Float_t>(const TMatrixFSparse &source1,const TMatrixF       &source2);
template TMatrixFSparse  operator+    <Float_t>(const TMatrixF       &source1,const TMatrixFSparse &source2);
template TMatrixFSparse  operator+    <Float_t>(const TMatrixFSparse &source ,      Float_t         val    );
template TMatrixFSparse  operator+    <Float_t>(      Float_t         val    ,const TMatrixFSparse &source );
template TMatrixFSparse  operator-    <Float_t>(const TMatrixFSparse &source1,const TMatrixFSparse &source2);
template TMatrixFSparse  operator-    <Float_t>(const TMatrixFSparse &source1,const TMatrixF       &source2);
template TMatrixFSparse  operator-    <Float_t>(const TMatrixF       &source1,const TMatrixFSparse &source2);
template TMatrixFSparse  operator-    <Float_t>(const TMatrixFSparse &source ,      Float_t         val    );
template TMatrixFSparse  operator-    <Float_t>(      Float_t         val    ,const TMatrixFSparse &source );
template TMatrixFSparse  operator*    <Float_t>(const TMatrixFSparse &source1,const TMatrixFSparse &source2);
template TMatrixFSparse  operator*    <Float_t>(const TMatrixFSparse &source1,const TMatrixF       &source2);
template TMatrixFSparse  operator*    <Float_t>(const TMatrixF       &source1,const TMatrixFSparse &source2);
template TMatrixFSparse  operator*    <Float_t>(      Float_t         val    ,const TMatrixFSparse &source );
template TMatrixFSparse  operator*    <Float_t>(const TMatrixFSparse &source,       Float_t         val    );

template TMatrixFSparse &Add          <Float_t>(TMatrixFSparse &target,      Float_t         scalar,const TMatrixFSparse &source);
template TMatrixFSparse &ElementMult  <Float_t>(TMatrixFSparse &target,const TMatrixFSparse &source);
template TMatrixFSparse &ElementDiv   <Float_t>(TMatrixFSparse &target,const TMatrixFSparse &source);

template Bool_t          AreCompatible<Float_t>(const TMatrixFSparse &m1,const TMatrixFSparse &m2,Int_t verbose);

//#include "TMatrixDSparsefwd.h"
//#include "TMatrixDfwd.h"

template class TMatrixTSparse<Double_t>;

template TMatrixDSparse  operator+    <Double_t>(const TMatrixDSparse &source1,const TMatrixDSparse &source2);
template TMatrixDSparse  operator+    <Double_t>(const TMatrixDSparse &source1,const TMatrixD       &source2);
template TMatrixDSparse  operator+    <Double_t>(const TMatrixD       &source1,const TMatrixDSparse &source2);
template TMatrixDSparse  operator+    <Double_t>(const TMatrixDSparse &source ,      Double_t        val    );
template TMatrixDSparse  operator+    <Double_t>(      Double_t        val    ,const TMatrixDSparse &source );
template TMatrixDSparse  operator-    <Double_t>(const TMatrixDSparse &source1,const TMatrixDSparse &source2);
template TMatrixDSparse  operator-    <Double_t>(const TMatrixDSparse &source1,const TMatrixD       &source2);
template TMatrixDSparse  operator-    <Double_t>(const TMatrixD       &source1,const TMatrixDSparse &source2);
template TMatrixDSparse  operator-    <Double_t>(const TMatrixDSparse &source ,      Double_t        val    );
template TMatrixDSparse  operator-    <Double_t>(      Double_t        val    ,const TMatrixDSparse &source );
template TMatrixDSparse  operator*    <Double_t>(const TMatrixDSparse &source1,const TMatrixDSparse &source2);
template TMatrixDSparse  operator*    <Double_t>(const TMatrixDSparse &source1,const TMatrixD       &source2);
template TMatrixDSparse  operator*    <Double_t>(const TMatrixD       &source1,const TMatrixDSparse &source2);
template TMatrixDSparse  operator*    <Double_t>(      Double_t        val    ,const TMatrixDSparse &source );
template TMatrixDSparse  operator*    <Double_t>(const TMatrixDSparse &source,       Double_t        val    );

template TMatrixDSparse &Add          <Double_t>(TMatrixDSparse &target,      Double_t        scalar,const TMatrixDSparse &source);
template TMatrixDSparse &ElementMult  <Double_t>(TMatrixDSparse &target,const TMatrixDSparse &source);
template TMatrixDSparse &ElementDiv   <Double_t>(TMatrixDSparse &target,const TMatrixDSparse &source);

template Bool_t          AreCompatible<Double_t>(const TMatrixDSparse &m1,const TMatrixDSparse &m2,Int_t verbose);

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixTLazy
    \ingroup Matrix

 Templates of Lazy Matrix classes.
~~~
   TMatrixTLazy
   TMatrixTSymLazy
   THaarMatrixT
   THilbertMatrixT
   THilbertMatrixTSym
~~~
*/

//#include "TMatrixT.h"
//#include "TMatrixTSym.h"
//#include "TMatrixTLazy.h"
//#include "TMath.h"

templateClassImp(TMatrixTLazy);
templateClassImp(TMatrixTSymLazy);
templateClassImp(THaarMatrixT);
templateClassImp(THilbertMatrixT);
templateClassImp(THilbertMatrixTSym);


////////////////////////////////////////////////////////////////////////////////

template<class Element>
THaarMatrixT<Element>::THaarMatrixT(Int_t order,Int_t no_cols)
    : TMatrixTLazy<Element>(1<<order, no_cols == 0 ? 1<<order : no_cols)
{
   if (order <= 0) {}
     // Error("THaarMatrixT","Haar order(%d) should be > 0",order);
   if (no_cols < 0) {}
      //Error("THaarMatrixT","#cols(%d) in Haar should be >= 0",no_cols);
}

////////////////////////////////////////////////////////////////////////////////
/// Create an orthonormal (2^n)*(no_cols) Haar (sub)matrix, whose columns
/// are Haar functions. If no_cols is 0, create the complete matrix with
/// 2^n columns. Example, the complete Haar matrix of the second order is:
/// column 1: [ 1  1  1  1]/2
/// column 2: [ 1  1 -1 -1]/2
/// column 3: [ 1 -1  0  0]/sqrt(2)
/// column 4: [ 0  0  1 -1]/sqrt(2)
/// Matrix m is assumed to be zero originally.

template<class Element>
void MakeHaarMat(TMatrixT<Element> &m)
{
   ////R__ASSERT(m.IsValid());
   const Int_t no_rows = m.GetNrows();
   const Int_t no_cols = m.GetNcols();

   if (no_rows < no_cols) {
      //Error("MakeHaarMat","#rows(%d) should be >= #cols(%d)",no_rows,no_cols);
      return;
   }
   if (no_cols <= 0) {
      //Error("MakeHaarMat","#cols(%d) should be > 0",no_cols);
      return;
   }

   // It is easier to calculate a Haar matrix when the elements are stored
   // column-wise . Since we are row-wise, the transposed Haar is calculated

   TMatrixT<Element> mtr(no_cols,no_rows);
         Element *cp    = mtr.GetMatrixArray();
   const Element *m_end = mtr.GetMatrixArray()+no_rows*no_cols;

   Element norm_factor = 1/TMath::Sqrt((Element)no_rows);

   // First row is always 1 (up to normalization)
   Int_t j;
   for (j = 0; j < no_rows; j++)
      *cp++ = norm_factor;

   // The other functions are kind of steps: stretch of 1 followed by the
   // equally long stretch of -1. The functions can be grouped in families
   // according to their order (step size), differing only in the location
   // of the step
   Int_t step_length = no_rows/2;
   while (cp < m_end && step_length > 0) {
      for (Int_t step_position = 0; cp < m_end && step_position < no_rows;
              step_position += 2*step_length, cp += no_rows) {
         Element *ccp = cp+step_position;
         for (j = 0; j < step_length; j++)
            *ccp++ = norm_factor;
         for (j = 0; j < step_length; j++)
            *ccp++ = -norm_factor;
      }
      step_length /= 2;
      norm_factor *= TMath::Sqrt(2.0);
   }

   //R__ASSERT(step_length != 0       || cp == m_end);
   //R__ASSERT(no_rows     != no_cols || step_length == 0);

   m.Transpose(mtr);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
void THaarMatrixT<Element>::FillIn(TMatrixT<Element> &m) const
{
   MakeHaarMat(m);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
THilbertMatrixT<Element>::THilbertMatrixT(Int_t no_rows,Int_t no_cols)
    : TMatrixTLazy<Element>(no_rows,no_cols)
{
   if (no_rows <= 0) {}
      //Error("THilbertMatrixT","#rows(%d) in Hilbert should be > 0",no_rows);
   if (no_cols <= 0) {}
      //Error("THilbertMatrixT","#cols(%d) in Hilbert should be > 0",no_cols);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
THilbertMatrixT<Element>::THilbertMatrixT(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb)
    : TMatrixTLazy<Element>(row_lwb,row_upb,col_lwb,col_upb)
{
   if (row_upb < row_lwb) {}
      //Error("THilbertMatrixT","row_upb(%d) in Hilbert should be >= row_lwb(%d)",row_upb,row_lwb);
   if (col_upb < col_lwb) {}
      //Error("THilbertMatrixT","col_upb(%d) in Hilbert should be >= col_lwb(%d)",col_upb,col_lwb);
}

////////////////////////////////////////////////////////////////////////////////
/// Make a Hilbert matrix. Hilb[i,j] = 1/(i+j+1),
/// i,j=0...max-1 (matrix need not be a square one).

template<class Element>
void MakeHilbertMat(TMatrixT<Element> &m)
{
   //R__ASSERT(m.IsValid());
   const Int_t no_rows = m.GetNrows();
   const Int_t no_cols = m.GetNcols();

   if (no_rows <= 0) {
      //Error("MakeHilbertMat","#rows(%d) should be > 0",no_rows);
      return;
   }
   if (no_cols <= 0) {
      //Error("MakeHilbertMat","#cols(%d) should be > 0",no_cols);
      return;
   }

   Element *cp = m.GetMatrixArray();
   for (Int_t i = 0; i < no_rows; i++)
      for (Int_t j = 0; j < no_cols; j++)
         *cp++ = 1.0/(i+j+1.0);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
void THilbertMatrixT<Element>::FillIn(TMatrixT<Element> &m) const
{
   MakeHilbertMat(m);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
THilbertMatrixTSym<Element>::THilbertMatrixTSym(Int_t no_rows)
    : TMatrixTSymLazy<Element>(no_rows)
{
   if (no_rows <= 0) {}
      //Error("THilbertMatrixTSym","#rows(%d) in Hilbert should be > 0",no_rows);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
THilbertMatrixTSym<Element>::THilbertMatrixTSym(Int_t row_lwb,Int_t row_upb)
    : TMatrixTSymLazy<Element>(row_lwb,row_upb)
{
   if (row_upb < row_lwb) {}
      //Error("THilbertMatrixTSym","row_upb(%d) in Hilbert should be >= row_lwb(%d)",row_upb,row_lwb);
}

////////////////////////////////////////////////////////////////////////////////
/// Make a Hilbert matrix. Hilb[i,j] = 1/(i+j+1),
/// i,j=0...max-1 (matrix must be square).

template<class Element>
void MakeHilbertMat(TMatrixTSym<Element> &m)
{
   //R__ASSERT(m.IsValid());
   const Int_t no_rows = m.GetNrows();
   if (no_rows <= 0) {
      //Error("MakeHilbertMat","#rows(%d) should be > 0",no_rows);
      return;
   }

   Element *cp = m.GetMatrixArray();
   for (Int_t i = 0; i < no_rows; i++)
      for (Int_t j = 0; j < no_rows; j++)
         *cp++ = 1.0/(i+j+1.0);
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
void THilbertMatrixTSym<Element>::FillIn(TMatrixTSym<Element> &m) const
{
   MakeHilbertMat(m);
}

template class TMatrixTLazy      <Float_t>;
template class TMatrixTSymLazy   <Float_t>;
template class THaarMatrixT      <Float_t>;
template class THilbertMatrixT   <Float_t>;
template class THilbertMatrixTSym<Float_t>;

template class TMatrixTLazy      <Double_t>;
template class TMatrixTSymLazy   <Double_t>;
template class THaarMatrixT      <Double_t>;
template class THilbertMatrixT   <Double_t>;
template class THilbertMatrixTSym<Double_t>;

// @(#)root/base:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Oct 2004

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixTSymCramerInv
    \ingroup Matrix

 TMatrixTSymCramerInv

 Encapsulate templates of Cramer Inversion routines.

 The 4x4, 5x5 and 6x6 are adapted from routines written by
 Mark Fischler and Steven Haywood as part of the CLHEP package

 Although for sizes <= 6x6 the Cramer Inversion has a gain in speed
 compared to factorization schemes (like LU) , one pays a price in
 accuracy  .

 For Example:
~~~
  H * H^-1 = U, where H is a 5x5 Hilbert matrix
                      U is a 5x5 Unity matrix

 LU    : |U_jk| < 10e-13 for  j!=k
 Cramer: |U_jk| < 10e-7  for  j!=k
~~~

  however Cramer algorithm is about 10 (!) times faster
*/

//#include "TMatrixTSymCramerInv.h"

//#include "TError.h"

#if !defined(R__SOLARIS) && !defined(R__ACC) && !defined(R__FBSD)
NamespaceImp(TMatrixTSymCramerInv);
#endif

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Bool_t TMatrixTSymCramerInv::Inv2x2(TMatrixTSym<Element> &m,Double_t *determ)
{
   if (m.GetNrows() != 2) {
      //Error("Inv2x2","matrix should be square 2x2");
      return kFALSE;
   }

   Element *pM = m.GetMatrixArray();

   const Double_t det = pM[0] * pM[3] - pM[1] * pM[1];

   if (determ)
      *determ = det;

   if ( det == 0 ) {
      //Error("Inv2x2","matrix is singular");
      return kFALSE;
   }

   const Double_t tmp1 =   pM[3] / det;
   pM[3] = pM[0] / det;
   pM[2] = pM[1] = -pM[1] / det;
   pM[0] = tmp1;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Bool_t TMatrixTSymCramerInv::Inv3x3(TMatrixTSym<Element> &m,Double_t *determ)
{
   if (m.GetNrows() != 3) {
      //Error("Inv3x3","matrix should be square 3x3");
      return kFALSE;
   }

   Element *pM = m.GetMatrixArray();

   const Double_t c00 = pM[4] * pM[8] - pM[5] * pM[5];
   const Double_t c01 = pM[5] * pM[2] - pM[1] * pM[8];
   const Double_t c02 = pM[1] * pM[5] - pM[4] * pM[2];
   const Double_t c11 = pM[8] * pM[0] - pM[2] * pM[2];
   const Double_t c12 = pM[2] * pM[1] - pM[5] * pM[0];
   const Double_t c22 = pM[0] * pM[4] - pM[1] * pM[1];

   const Double_t t0  = TMath::Abs(pM[0]);
   const Double_t t1  = TMath::Abs(pM[1]);
   const Double_t t2  = TMath::Abs(pM[2]);

   Double_t det;
   Double_t tmp;

   if (t0 >= t1) {
      if (t2 >= t0) {
         tmp = pM[2];
         det = c12*c01-c11*c02;
      } else {
         tmp = pM[0];
         det = c11*c22-c12*c12;
      }
   } else if (t2 >= t1) {
      tmp = pM[2];
      det = c12*c01-c11*c02;
   } else {
      tmp = pM[1];
      det = c02*c12-c01*c22;
   }

   if ( det == 0 || tmp == 0) {
      //Error("Inv3x3","matrix is singular");
      return kFALSE;
   }

   Double_t s = tmp/det;
   if (determ)
      *determ = 1./s;

   pM[0] = s*c00;
   pM[1] = s*c01;
   pM[2] = s*c02;
   pM[3] = pM[1];
   pM[4] = s*c11;
   pM[5] = s*c12;
   pM[6] = pM[2];
   pM[7] = pM[5];
   pM[8] = s*c22;

   return kTRUE;
}

// SFij are indices for a 4x4 symmetric matrix.

#define SF00 0
#define SF01 1
#define SF02 2
#define SF03 3

#define SF10 1
#define SF11 5
#define SF12 6
#define SF13 7

#define SF20 2
#define SF21 6
#define SF22 10
#define SF23 11

#define SF30 3
#define SF31 7
#define SF32 11
#define SF33 15

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Bool_t TMatrixTSymCramerInv::Inv4x4(TMatrixTSym<Element> &m,Double_t *determ)
{
   if (m.GetNrows() != 4) {
      //Error("Inv4x4","matrix should be square 4x4");
      return kFALSE;
   }

   Element *pM = m.GetMatrixArray();

   // Find all NECESSARY 2x2 dets:  (14 of them)

   const Double_t mDet2_12_01 = pM[SF10]*pM[SF21] - pM[SF11]*pM[SF20];
   const Double_t mDet2_12_02 = pM[SF10]*pM[SF22] - pM[SF12]*pM[SF20];
   const Double_t mDet2_12_12 = pM[SF11]*pM[SF22] - pM[SF12]*pM[SF21];
   const Double_t mDet2_13_01 = pM[SF10]*pM[SF31] - pM[SF11]*pM[SF30];
   const Double_t mDet2_13_02 = pM[SF10]*pM[SF32] - pM[SF12]*pM[SF30];
   const Double_t mDet2_13_03 = pM[SF10]*pM[SF33] - pM[SF13]*pM[SF30];
   const Double_t mDet2_13_12 = pM[SF11]*pM[SF32] - pM[SF12]*pM[SF31];
   const Double_t mDet2_13_13 = pM[SF11]*pM[SF33] - pM[SF13]*pM[SF31];
   const Double_t mDet2_23_01 = pM[SF20]*pM[SF31] - pM[SF21]*pM[SF30];
   const Double_t mDet2_23_02 = pM[SF20]*pM[SF32] - pM[SF22]*pM[SF30];
   const Double_t mDet2_23_03 = pM[SF20]*pM[SF33] - pM[SF23]*pM[SF30];
   const Double_t mDet2_23_12 = pM[SF21]*pM[SF32] - pM[SF22]*pM[SF31];
   const Double_t mDet2_23_13 = pM[SF21]*pM[SF33] - pM[SF23]*pM[SF31];
   const Double_t mDet2_23_23 = pM[SF22]*pM[SF33] - pM[SF23]*pM[SF32];

  // SFind all NECESSSFRY 3x3 dets:   (10 of them)

   const Double_t mDet3_012_012 = pM[SF00]*mDet2_12_12 - pM[SF01]*mDet2_12_02
                                + pM[SF02]*mDet2_12_01;
   const Double_t mDet3_013_012 = pM[SF00]*mDet2_13_12 - pM[SF01]*mDet2_13_02
                                + pM[SF02]*mDet2_13_01;
   const Double_t mDet3_013_013 = pM[SF00]*mDet2_13_13 - pM[SF01]*mDet2_13_03
                                + pM[SF03]*mDet2_13_01;
   const Double_t mDet3_023_012 = pM[SF00]*mDet2_23_12 - pM[SF01]*mDet2_23_02
                                + pM[SF02]*mDet2_23_01;
   const Double_t mDet3_023_013 = pM[SF00]*mDet2_23_13 - pM[SF01]*mDet2_23_03
                                + pM[SF03]*mDet2_23_01;
   const Double_t mDet3_023_023 = pM[SF00]*mDet2_23_23 - pM[SF02]*mDet2_23_03
                                + pM[SF03]*mDet2_23_02;
   const Double_t mDet3_123_012 = pM[SF10]*mDet2_23_12 - pM[SF11]*mDet2_23_02
                                + pM[SF12]*mDet2_23_01;
   const Double_t mDet3_123_013 = pM[SF10]*mDet2_23_13 - pM[SF11]*mDet2_23_03
                                + pM[SF13]*mDet2_23_01;
   const Double_t mDet3_123_023 = pM[SF10]*mDet2_23_23 - pM[SF12]*mDet2_23_03
                                + pM[SF13]*mDet2_23_02;
   const Double_t mDet3_123_123 = pM[SF11]*mDet2_23_23 - pM[SF12]*mDet2_23_13
                                + pM[SF13]*mDet2_23_12;

   // Find the 4x4 det:

   const Double_t det = pM[SF00]*mDet3_123_123 - pM[SF01]*mDet3_123_023
                      + pM[SF02]*mDet3_123_013 - pM[SF03]*mDet3_123_012;

   if (determ)
      *determ = det;

   if ( det == 0 ) {
      //Error("Inv4x4","matrix is singular");
      return kFALSE;
   }

   const Double_t oneOverDet = 1.0/det;
   const Double_t mn1OverDet = - oneOverDet;

   pM[SF00] =  mDet3_123_123 * oneOverDet;
   pM[SF01] =  mDet3_123_023 * mn1OverDet;
   pM[SF02] =  mDet3_123_013 * oneOverDet;
   pM[SF03] =  mDet3_123_012 * mn1OverDet;

   pM[SF11] =  mDet3_023_023 * oneOverDet;
   pM[SF12] =  mDet3_023_013 * mn1OverDet;
   pM[SF13] =  mDet3_023_012 * oneOverDet;

   pM[SF22] =  mDet3_013_013 * oneOverDet;
   pM[SF23] =  mDet3_013_012 * mn1OverDet;

   pM[SF33] =  mDet3_012_012 * oneOverDet;

   for (Int_t irow = 0; irow < 4; irow++) {
      const Int_t rowOff1 = irow*4;
      for (Int_t icol = 0; icol < irow; icol++) {
         const Int_t rowOff2 = icol*4;
         pM[rowOff1+icol] = pM[rowOff2+irow];
      }
   }

   return kTRUE;
}

// Mij are indices for a 5x5 matrix.

#define SM00 0
#define SM01 1
#define SM02 2
#define SM03 3
#define SM04 4

#define SM10 1
#define SM11 6
#define SM12 7
#define SM13 8
#define SM14 9

#define SM20 2
#define SM21 7
#define SM22 12
#define SM23 13
#define SM24 14

#define SM30 3
#define SM31 8
#define SM32 13
#define SM33 18
#define SM34 19

#define SM40 4
#define SM41 9
#define SM42 14
#define SM43 19
#define SM44 24

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Bool_t TMatrixTSymCramerInv::Inv5x5(TMatrixTSym<Element> &m,Double_t *determ)
{
   if (m.GetNrows() != 5) {
      //Error("Inv5x5","matrix should be square 5x5");
      return kFALSE;
   }

   Element *pM = m.GetMatrixArray();

   // Find all NECESSARY 2x2 dets:  (25 of them)

   const Double_t mDet2_23_01 = pM[SM20]*pM[SM31] - pM[SM21]*pM[SM30];
   const Double_t mDet2_23_02 = pM[SM20]*pM[SM32] - pM[SM22]*pM[SM30];
   const Double_t mDet2_23_03 = pM[SM20]*pM[SM33] - pM[SM23]*pM[SM30];
   const Double_t mDet2_23_12 = pM[SM21]*pM[SM32] - pM[SM22]*pM[SM31];
   const Double_t mDet2_23_13 = pM[SM21]*pM[SM33] - pM[SM23]*pM[SM31];
   const Double_t mDet2_23_23 = pM[SM22]*pM[SM33] - pM[SM23]*pM[SM32];
   const Double_t mDet2_24_01 = pM[SM20]*pM[SM41] - pM[SM21]*pM[SM40];
   const Double_t mDet2_24_02 = pM[SM20]*pM[SM42] - pM[SM22]*pM[SM40];
   const Double_t mDet2_24_03 = pM[SM20]*pM[SM43] - pM[SM23]*pM[SM40];
   const Double_t mDet2_24_04 = pM[SM20]*pM[SM44] - pM[SM24]*pM[SM40];
   const Double_t mDet2_24_12 = pM[SM21]*pM[SM42] - pM[SM22]*pM[SM41];
   const Double_t mDet2_24_13 = pM[SM21]*pM[SM43] - pM[SM23]*pM[SM41];
   const Double_t mDet2_24_14 = pM[SM21]*pM[SM44] - pM[SM24]*pM[SM41];
   const Double_t mDet2_24_23 = pM[SM22]*pM[SM43] - pM[SM23]*pM[SM42];
   const Double_t mDet2_24_24 = pM[SM22]*pM[SM44] - pM[SM24]*pM[SM42];
   const Double_t mDet2_34_01 = pM[SM30]*pM[SM41] - pM[SM31]*pM[SM40];
   const Double_t mDet2_34_02 = pM[SM30]*pM[SM42] - pM[SM32]*pM[SM40];
   const Double_t mDet2_34_03 = pM[SM30]*pM[SM43] - pM[SM33]*pM[SM40];
   const Double_t mDet2_34_04 = pM[SM30]*pM[SM44] - pM[SM34]*pM[SM40];
   const Double_t mDet2_34_12 = pM[SM31]*pM[SM42] - pM[SM32]*pM[SM41];
   const Double_t mDet2_34_13 = pM[SM31]*pM[SM43] - pM[SM33]*pM[SM41];
   const Double_t mDet2_34_14 = pM[SM31]*pM[SM44] - pM[SM34]*pM[SM41];
   const Double_t mDet2_34_23 = pM[SM32]*pM[SM43] - pM[SM33]*pM[SM42];
   const Double_t mDet2_34_24 = pM[SM32]*pM[SM44] - pM[SM34]*pM[SM42];
   const Double_t mDet2_34_34 = pM[SM33]*pM[SM44] - pM[SM34]*pM[SM43];

   // Find all NECESSARY 3x3 dets:   (30 of them)

   const Double_t mDet3_123_012 = pM[SM10]*mDet2_23_12 - pM[SM11]*mDet2_23_02 + pM[SM12]*mDet2_23_01;
   const Double_t mDet3_123_013 = pM[SM10]*mDet2_23_13 - pM[SM11]*mDet2_23_03 + pM[SM13]*mDet2_23_01;
   const Double_t mDet3_123_023 = pM[SM10]*mDet2_23_23 - pM[SM12]*mDet2_23_03 + pM[SM13]*mDet2_23_02;
   const Double_t mDet3_123_123 = pM[SM11]*mDet2_23_23 - pM[SM12]*mDet2_23_13 + pM[SM13]*mDet2_23_12;
   const Double_t mDet3_124_012 = pM[SM10]*mDet2_24_12 - pM[SM11]*mDet2_24_02 + pM[SM12]*mDet2_24_01;
   const Double_t mDet3_124_013 = pM[SM10]*mDet2_24_13 - pM[SM11]*mDet2_24_03 + pM[SM13]*mDet2_24_01;
   const Double_t mDet3_124_014 = pM[SM10]*mDet2_24_14 - pM[SM11]*mDet2_24_04 + pM[SM14]*mDet2_24_01;
   const Double_t mDet3_124_023 = pM[SM10]*mDet2_24_23 - pM[SM12]*mDet2_24_03 + pM[SM13]*mDet2_24_02;
   const Double_t mDet3_124_024 = pM[SM10]*mDet2_24_24 - pM[SM12]*mDet2_24_04 + pM[SM14]*mDet2_24_02;
   const Double_t mDet3_124_123 = pM[SM11]*mDet2_24_23 - pM[SM12]*mDet2_24_13 + pM[SM13]*mDet2_24_12;
   const Double_t mDet3_124_124 = pM[SM11]*mDet2_24_24 - pM[SM12]*mDet2_24_14 + pM[SM14]*mDet2_24_12;
   const Double_t mDet3_134_012 = pM[SM10]*mDet2_34_12 - pM[SM11]*mDet2_34_02 + pM[SM12]*mDet2_34_01;
   const Double_t mDet3_134_013 = pM[SM10]*mDet2_34_13 - pM[SM11]*mDet2_34_03 + pM[SM13]*mDet2_34_01;
   const Double_t mDet3_134_014 = pM[SM10]*mDet2_34_14 - pM[SM11]*mDet2_34_04 + pM[SM14]*mDet2_34_01;
   const Double_t mDet3_134_023 = pM[SM10]*mDet2_34_23 - pM[SM12]*mDet2_34_03 + pM[SM13]*mDet2_34_02;
   const Double_t mDet3_134_024 = pM[SM10]*mDet2_34_24 - pM[SM12]*mDet2_34_04 + pM[SM14]*mDet2_34_02;
   const Double_t mDet3_134_034 = pM[SM10]*mDet2_34_34 - pM[SM13]*mDet2_34_04 + pM[SM14]*mDet2_34_03;
   const Double_t mDet3_134_123 = pM[SM11]*mDet2_34_23 - pM[SM12]*mDet2_34_13 + pM[SM13]*mDet2_34_12;
   const Double_t mDet3_134_124 = pM[SM11]*mDet2_34_24 - pM[SM12]*mDet2_34_14 + pM[SM14]*mDet2_34_12;
   const Double_t mDet3_134_134 = pM[SM11]*mDet2_34_34 - pM[SM13]*mDet2_34_14 + pM[SM14]*mDet2_34_13;
   const Double_t mDet3_234_012 = pM[SM20]*mDet2_34_12 - pM[SM21]*mDet2_34_02 + pM[SM22]*mDet2_34_01;
   const Double_t mDet3_234_013 = pM[SM20]*mDet2_34_13 - pM[SM21]*mDet2_34_03 + pM[SM23]*mDet2_34_01;
   const Double_t mDet3_234_014 = pM[SM20]*mDet2_34_14 - pM[SM21]*mDet2_34_04 + pM[SM24]*mDet2_34_01;
   const Double_t mDet3_234_023 = pM[SM20]*mDet2_34_23 - pM[SM22]*mDet2_34_03 + pM[SM23]*mDet2_34_02;
   const Double_t mDet3_234_024 = pM[SM20]*mDet2_34_24 - pM[SM22]*mDet2_34_04 + pM[SM24]*mDet2_34_02;
   const Double_t mDet3_234_034 = pM[SM20]*mDet2_34_34 - pM[SM23]*mDet2_34_04 + pM[SM24]*mDet2_34_03;
   const Double_t mDet3_234_123 = pM[SM21]*mDet2_34_23 - pM[SM22]*mDet2_34_13 + pM[SM23]*mDet2_34_12;
   const Double_t mDet3_234_124 = pM[SM21]*mDet2_34_24 - pM[SM22]*mDet2_34_14 + pM[SM24]*mDet2_34_12;
   const Double_t mDet3_234_134 = pM[SM21]*mDet2_34_34 - pM[SM23]*mDet2_34_14 + pM[SM24]*mDet2_34_13;
   const Double_t mDet3_234_234 = pM[SM22]*mDet2_34_34 - pM[SM23]*mDet2_34_24 + pM[SM24]*mDet2_34_23;

   // Find all NECESSARY 4x4 dets:   (15 of them)

   const Double_t mDet4_0123_0123 = pM[SM00]*mDet3_123_123 - pM[SM01]*mDet3_123_023
                                  + pM[SM02]*mDet3_123_013 - pM[SM03]*mDet3_123_012;
   const Double_t mDet4_0124_0123 = pM[SM00]*mDet3_124_123 - pM[SM01]*mDet3_124_023
                                  + pM[SM02]*mDet3_124_013 - pM[SM03]*mDet3_124_012;
   const Double_t mDet4_0124_0124 = pM[SM00]*mDet3_124_124 - pM[SM01]*mDet3_124_024
                                  + pM[SM02]*mDet3_124_014 - pM[SM04]*mDet3_124_012;
   const Double_t mDet4_0134_0123 = pM[SM00]*mDet3_134_123 - pM[SM01]*mDet3_134_023
                                  + pM[SM02]*mDet3_134_013 - pM[SM03]*mDet3_134_012;
   const Double_t mDet4_0134_0124 = pM[SM00]*mDet3_134_124 - pM[SM01]*mDet3_134_024
                                  + pM[SM02]*mDet3_134_014 - pM[SM04]*mDet3_134_012;
   const Double_t mDet4_0134_0134 = pM[SM00]*mDet3_134_134 - pM[SM01]*mDet3_134_034
                                  + pM[SM03]*mDet3_134_014 - pM[SM04]*mDet3_134_013;
   const Double_t mDet4_0234_0123 = pM[SM00]*mDet3_234_123 - pM[SM01]*mDet3_234_023
                                  + pM[SM02]*mDet3_234_013 - pM[SM03]*mDet3_234_012;
   const Double_t mDet4_0234_0124 = pM[SM00]*mDet3_234_124 - pM[SM01]*mDet3_234_024
                                  + pM[SM02]*mDet3_234_014 - pM[SM04]*mDet3_234_012;
   const Double_t mDet4_0234_0134 = pM[SM00]*mDet3_234_134 - pM[SM01]*mDet3_234_034
                                  + pM[SM03]*mDet3_234_014 - pM[SM04]*mDet3_234_013;
   const Double_t mDet4_0234_0234 = pM[SM00]*mDet3_234_234 - pM[SM02]*mDet3_234_034
                                  + pM[SM03]*mDet3_234_024 - pM[SM04]*mDet3_234_023;
   const Double_t mDet4_1234_0123 = pM[SM10]*mDet3_234_123 - pM[SM11]*mDet3_234_023
                                  + pM[SM12]*mDet3_234_013 - pM[SM13]*mDet3_234_012;
   const Double_t mDet4_1234_0124 = pM[SM10]*mDet3_234_124 - pM[SM11]*mDet3_234_024
                                  + pM[SM12]*mDet3_234_014 - pM[SM14]*mDet3_234_012;
   const Double_t mDet4_1234_0134 = pM[SM10]*mDet3_234_134 - pM[SM11]*mDet3_234_034
                                  + pM[SM13]*mDet3_234_014 - pM[SM14]*mDet3_234_013;
   const Double_t mDet4_1234_0234 = pM[SM10]*mDet3_234_234 - pM[SM12]*mDet3_234_034
                                  + pM[SM13]*mDet3_234_024 - pM[SM14]*mDet3_234_023;
   const Double_t mDet4_1234_1234 = pM[SM11]*mDet3_234_234 - pM[SM12]*mDet3_234_134
                                  + pM[SM13]*mDet3_234_124 - pM[SM14]*mDet3_234_123;

   // Find the 5x5 det:

   const Double_t det = pM[SM00]*mDet4_1234_1234 - pM[SM01]*mDet4_1234_0234 + pM[SM02]*mDet4_1234_0134
                      - pM[SM03]*mDet4_1234_0124 + pM[SM04]*mDet4_1234_0123;
   if (determ)
      *determ = det;

   if ( det == 0 ) {
      //Error("Inv5x5","matrix is singular");
      return kFALSE;
   }

   const Double_t oneOverDet = 1.0/det;
   const Double_t mn1OverDet = - oneOverDet;

   pM[SM00] = mDet4_1234_1234 * oneOverDet;
   pM[SM01] = mDet4_1234_0234 * mn1OverDet;
   pM[SM02] = mDet4_1234_0134 * oneOverDet;
   pM[SM03] = mDet4_1234_0124 * mn1OverDet;
   pM[SM04] = mDet4_1234_0123 * oneOverDet;

   pM[SM11] = mDet4_0234_0234 * oneOverDet;
   pM[SM12] = mDet4_0234_0134 * mn1OverDet;
   pM[SM13] = mDet4_0234_0124 * oneOverDet;
   pM[SM14] = mDet4_0234_0123 * mn1OverDet;

   pM[SM22] = mDet4_0134_0134 * oneOverDet;
   pM[SM23] = mDet4_0134_0124 * mn1OverDet;
   pM[SM24] = mDet4_0134_0123 * oneOverDet;

   pM[SM33] = mDet4_0124_0124 * oneOverDet;
   pM[SM34] = mDet4_0124_0123 * mn1OverDet;

   pM[SM44] = mDet4_0123_0123 * oneOverDet;

   for (Int_t irow = 0; irow < 5; irow++) {
      const Int_t rowOff1 = irow*5;
      for (Int_t icol = 0; icol < irow; icol++) {
         const Int_t rowOff2 = icol*5;
         pM[rowOff1+icol] = pM[rowOff2+irow];
      }
   }

   return kTRUE;
}

// Aij are indices for a 6x6 symmetric matrix.

#define SA00 0
#define SA01 1
#define SA02 2
#define SA03 3
#define SA04 4
#define SA05 5

#define SA10 1
#define SA11 7
#define SA12 8
#define SA13 9
#define SA14 10
#define SA15 11

#define SA20 2
#define SA21 8
#define SA22 14
#define SA23 15
#define SA24 16
#define SA25 17

#define SA30 3
#define SA31 9
#define SA32 15
#define SA33 21
#define SA34 22
#define SA35 23

#define SA40 4
#define SA41 10
#define SA42 16
#define SA43 22
#define SA44 28
#define SA45 29

#define SA50 5
#define SA51 11
#define SA52 17
#define SA53 23
#define SA54 29
#define SA55 35

////////////////////////////////////////////////////////////////////////////////

template<class Element>
Bool_t TMatrixTSymCramerInv::Inv6x6(TMatrixTSym<Element> &m,Double_t *determ)
{
   if (m.GetNrows() != 6 || m.GetNcols() != 6 || m.GetRowLwb() != m.GetColLwb()) {
      //Error("Inv6x6","matrix should be square 6x6");
      return kFALSE;
   }

   Element *pM = m.GetMatrixArray();

   // Find all NECESSSARY 2x2 dets:  (39 of them)

   const Double_t mDet2_34_01 = pM[SA30]*pM[SA41] - pM[SA31]*pM[SA40];
   const Double_t mDet2_34_02 = pM[SA30]*pM[SA42] - pM[SA32]*pM[SA40];
   const Double_t mDet2_34_03 = pM[SA30]*pM[SA43] - pM[SA33]*pM[SA40];
   const Double_t mDet2_34_04 = pM[SA30]*pM[SA44] - pM[SA34]*pM[SA40];
   const Double_t mDet2_34_12 = pM[SA31]*pM[SA42] - pM[SA32]*pM[SA41];
   const Double_t mDet2_34_13 = pM[SA31]*pM[SA43] - pM[SA33]*pM[SA41];
   const Double_t mDet2_34_14 = pM[SA31]*pM[SA44] - pM[SA34]*pM[SA41];
   const Double_t mDet2_34_23 = pM[SA32]*pM[SA43] - pM[SA33]*pM[SA42];
   const Double_t mDet2_34_24 = pM[SA32]*pM[SA44] - pM[SA34]*pM[SA42];
   const Double_t mDet2_34_34 = pM[SA33]*pM[SA44] - pM[SA34]*pM[SA43];
   const Double_t mDet2_35_01 = pM[SA30]*pM[SA51] - pM[SA31]*pM[SA50];
   const Double_t mDet2_35_02 = pM[SA30]*pM[SA52] - pM[SA32]*pM[SA50];
   const Double_t mDet2_35_03 = pM[SA30]*pM[SA53] - pM[SA33]*pM[SA50];
   const Double_t mDet2_35_04 = pM[SA30]*pM[SA54] - pM[SA34]*pM[SA50];
   const Double_t mDet2_35_05 = pM[SA30]*pM[SA55] - pM[SA35]*pM[SA50];
   const Double_t mDet2_35_12 = pM[SA31]*pM[SA52] - pM[SA32]*pM[SA51];
   const Double_t mDet2_35_13 = pM[SA31]*pM[SA53] - pM[SA33]*pM[SA51];
   const Double_t mDet2_35_14 = pM[SA31]*pM[SA54] - pM[SA34]*pM[SA51];
   const Double_t mDet2_35_15 = pM[SA31]*pM[SA55] - pM[SA35]*pM[SA51];
   const Double_t mDet2_35_23 = pM[SA32]*pM[SA53] - pM[SA33]*pM[SA52];
   const Double_t mDet2_35_24 = pM[SA32]*pM[SA54] - pM[SA34]*pM[SA52];
   const Double_t mDet2_35_25 = pM[SA32]*pM[SA55] - pM[SA35]*pM[SA52];
   const Double_t mDet2_35_34 = pM[SA33]*pM[SA54] - pM[SA34]*pM[SA53];
   const Double_t mDet2_35_35 = pM[SA33]*pM[SA55] - pM[SA35]*pM[SA53];
   const Double_t mDet2_45_01 = pM[SA40]*pM[SA51] - pM[SA41]*pM[SA50];
   const Double_t mDet2_45_02 = pM[SA40]*pM[SA52] - pM[SA42]*pM[SA50];
   const Double_t mDet2_45_03 = pM[SA40]*pM[SA53] - pM[SA43]*pM[SA50];
   const Double_t mDet2_45_04 = pM[SA40]*pM[SA54] - pM[SA44]*pM[SA50];
   const Double_t mDet2_45_05 = pM[SA40]*pM[SA55] - pM[SA45]*pM[SA50];
   const Double_t mDet2_45_12 = pM[SA41]*pM[SA52] - pM[SA42]*pM[SA51];
   const Double_t mDet2_45_13 = pM[SA41]*pM[SA53] - pM[SA43]*pM[SA51];
   const Double_t mDet2_45_14 = pM[SA41]*pM[SA54] - pM[SA44]*pM[SA51];
   const Double_t mDet2_45_15 = pM[SA41]*pM[SA55] - pM[SA45]*pM[SA51];
   const Double_t mDet2_45_23 = pM[SA42]*pM[SA53] - pM[SA43]*pM[SA52];
   const Double_t mDet2_45_24 = pM[SA42]*pM[SA54] - pM[SA44]*pM[SA52];
   const Double_t mDet2_45_25 = pM[SA42]*pM[SA55] - pM[SA45]*pM[SA52];
   const Double_t mDet2_45_34 = pM[SA43]*pM[SA54] - pM[SA44]*pM[SA53];
   const Double_t mDet2_45_35 = pM[SA43]*pM[SA55] - pM[SA45]*pM[SA53];
   const Double_t mDet2_45_45 = pM[SA44]*pM[SA55] - pM[SA45]*pM[SA54];

   // Find all NECESSSARY 3x3 dets:  (65 of them)

   const Double_t mDet3_234_012 = pM[SA20]*mDet2_34_12 - pM[SA21]*mDet2_34_02 + pM[SA22]*mDet2_34_01;
   const Double_t mDet3_234_013 = pM[SA20]*mDet2_34_13 - pM[SA21]*mDet2_34_03 + pM[SA23]*mDet2_34_01;
   const Double_t mDet3_234_014 = pM[SA20]*mDet2_34_14 - pM[SA21]*mDet2_34_04 + pM[SA24]*mDet2_34_01;
   const Double_t mDet3_234_023 = pM[SA20]*mDet2_34_23 - pM[SA22]*mDet2_34_03 + pM[SA23]*mDet2_34_02;
   const Double_t mDet3_234_024 = pM[SA20]*mDet2_34_24 - pM[SA22]*mDet2_34_04 + pM[SA24]*mDet2_34_02;
   const Double_t mDet3_234_034 = pM[SA20]*mDet2_34_34 - pM[SA23]*mDet2_34_04 + pM[SA24]*mDet2_34_03;
   const Double_t mDet3_234_123 = pM[SA21]*mDet2_34_23 - pM[SA22]*mDet2_34_13 + pM[SA23]*mDet2_34_12;
   const Double_t mDet3_234_124 = pM[SA21]*mDet2_34_24 - pM[SA22]*mDet2_34_14 + pM[SA24]*mDet2_34_12;
   const Double_t mDet3_234_134 = pM[SA21]*mDet2_34_34 - pM[SA23]*mDet2_34_14 + pM[SA24]*mDet2_34_13;
   const Double_t mDet3_234_234 = pM[SA22]*mDet2_34_34 - pM[SA23]*mDet2_34_24 + pM[SA24]*mDet2_34_23;
   const Double_t mDet3_235_012 = pM[SA20]*mDet2_35_12 - pM[SA21]*mDet2_35_02 + pM[SA22]*mDet2_35_01;
   const Double_t mDet3_235_013 = pM[SA20]*mDet2_35_13 - pM[SA21]*mDet2_35_03 + pM[SA23]*mDet2_35_01;
   const Double_t mDet3_235_014 = pM[SA20]*mDet2_35_14 - pM[SA21]*mDet2_35_04 + pM[SA24]*mDet2_35_01;
   const Double_t mDet3_235_015 = pM[SA20]*mDet2_35_15 - pM[SA21]*mDet2_35_05 + pM[SA25]*mDet2_35_01;
   const Double_t mDet3_235_023 = pM[SA20]*mDet2_35_23 - pM[SA22]*mDet2_35_03 + pM[SA23]*mDet2_35_02;
   const Double_t mDet3_235_024 = pM[SA20]*mDet2_35_24 - pM[SA22]*mDet2_35_04 + pM[SA24]*mDet2_35_02;
   const Double_t mDet3_235_025 = pM[SA20]*mDet2_35_25 - pM[SA22]*mDet2_35_05 + pM[SA25]*mDet2_35_02;
   const Double_t mDet3_235_034 = pM[SA20]*mDet2_35_34 - pM[SA23]*mDet2_35_04 + pM[SA24]*mDet2_35_03;
   const Double_t mDet3_235_035 = pM[SA20]*mDet2_35_35 - pM[SA23]*mDet2_35_05 + pM[SA25]*mDet2_35_03;
   const Double_t mDet3_235_123 = pM[SA21]*mDet2_35_23 - pM[SA22]*mDet2_35_13 + pM[SA23]*mDet2_35_12;
   const Double_t mDet3_235_124 = pM[SA21]*mDet2_35_24 - pM[SA22]*mDet2_35_14 + pM[SA24]*mDet2_35_12;
   const Double_t mDet3_235_125 = pM[SA21]*mDet2_35_25 - pM[SA22]*mDet2_35_15 + pM[SA25]*mDet2_35_12;
   const Double_t mDet3_235_134 = pM[SA21]*mDet2_35_34 - pM[SA23]*mDet2_35_14 + pM[SA24]*mDet2_35_13;
   const Double_t mDet3_235_135 = pM[SA21]*mDet2_35_35 - pM[SA23]*mDet2_35_15 + pM[SA25]*mDet2_35_13;
   const Double_t mDet3_235_234 = pM[SA22]*mDet2_35_34 - pM[SA23]*mDet2_35_24 + pM[SA24]*mDet2_35_23;
   const Double_t mDet3_235_235 = pM[SA22]*mDet2_35_35 - pM[SA23]*mDet2_35_25 + pM[SA25]*mDet2_35_23;
   const Double_t mDet3_245_012 = pM[SA20]*mDet2_45_12 - pM[SA21]*mDet2_45_02 + pM[SA22]*mDet2_45_01;
   const Double_t mDet3_245_013 = pM[SA20]*mDet2_45_13 - pM[SA21]*mDet2_45_03 + pM[SA23]*mDet2_45_01;
   const Double_t mDet3_245_014 = pM[SA20]*mDet2_45_14 - pM[SA21]*mDet2_45_04 + pM[SA24]*mDet2_45_01;
   const Double_t mDet3_245_015 = pM[SA20]*mDet2_45_15 - pM[SA21]*mDet2_45_05 + pM[SA25]*mDet2_45_01;
   const Double_t mDet3_245_023 = pM[SA20]*mDet2_45_23 - pM[SA22]*mDet2_45_03 + pM[SA23]*mDet2_45_02;
   const Double_t mDet3_245_024 = pM[SA20]*mDet2_45_24 - pM[SA22]*mDet2_45_04 + pM[SA24]*mDet2_45_02;
   const Double_t mDet3_245_025 = pM[SA20]*mDet2_45_25 - pM[SA22]*mDet2_45_05 + pM[SA25]*mDet2_45_02;
   const Double_t mDet3_245_034 = pM[SA20]*mDet2_45_34 - pM[SA23]*mDet2_45_04 + pM[SA24]*mDet2_45_03;
   const Double_t mDet3_245_035 = pM[SA20]*mDet2_45_35 - pM[SA23]*mDet2_45_05 + pM[SA25]*mDet2_45_03;
   const Double_t mDet3_245_045 = pM[SA20]*mDet2_45_45 - pM[SA24]*mDet2_45_05 + pM[SA25]*mDet2_45_04;
   const Double_t mDet3_245_123 = pM[SA21]*mDet2_45_23 - pM[SA22]*mDet2_45_13 + pM[SA23]*mDet2_45_12;
   const Double_t mDet3_245_124 = pM[SA21]*mDet2_45_24 - pM[SA22]*mDet2_45_14 + pM[SA24]*mDet2_45_12;
   const Double_t mDet3_245_125 = pM[SA21]*mDet2_45_25 - pM[SA22]*mDet2_45_15 + pM[SA25]*mDet2_45_12;
   const Double_t mDet3_245_134 = pM[SA21]*mDet2_45_34 - pM[SA23]*mDet2_45_14 + pM[SA24]*mDet2_45_13;
   const Double_t mDet3_245_135 = pM[SA21]*mDet2_45_35 - pM[SA23]*mDet2_45_15 + pM[SA25]*mDet2_45_13;
   const Double_t mDet3_245_145 = pM[SA21]*mDet2_45_45 - pM[SA24]*mDet2_45_15 + pM[SA25]*mDet2_45_14;
   const Double_t mDet3_245_234 = pM[SA22]*mDet2_45_34 - pM[SA23]*mDet2_45_24 + pM[SA24]*mDet2_45_23;
   const Double_t mDet3_245_235 = pM[SA22]*mDet2_45_35 - pM[SA23]*mDet2_45_25 + pM[SA25]*mDet2_45_23;
   const Double_t mDet3_245_245 = pM[SA22]*mDet2_45_45 - pM[SA24]*mDet2_45_25 + pM[SA25]*mDet2_45_24;
   const Double_t mDet3_345_012 = pM[SA30]*mDet2_45_12 - pM[SA31]*mDet2_45_02 + pM[SA32]*mDet2_45_01;
   const Double_t mDet3_345_013 = pM[SA30]*mDet2_45_13 - pM[SA31]*mDet2_45_03 + pM[SA33]*mDet2_45_01;
   const Double_t mDet3_345_014 = pM[SA30]*mDet2_45_14 - pM[SA31]*mDet2_45_04 + pM[SA34]*mDet2_45_01;
   const Double_t mDet3_345_015 = pM[SA30]*mDet2_45_15 - pM[SA31]*mDet2_45_05 + pM[SA35]*mDet2_45_01;
   const Double_t mDet3_345_023 = pM[SA30]*mDet2_45_23 - pM[SA32]*mDet2_45_03 + pM[SA33]*mDet2_45_02;
   const Double_t mDet3_345_024 = pM[SA30]*mDet2_45_24 - pM[SA32]*mDet2_45_04 + pM[SA34]*mDet2_45_02;
   const Double_t mDet3_345_025 = pM[SA30]*mDet2_45_25 - pM[SA32]*mDet2_45_05 + pM[SA35]*mDet2_45_02;
   const Double_t mDet3_345_034 = pM[SA30]*mDet2_45_34 - pM[SA33]*mDet2_45_04 + pM[SA34]*mDet2_45_03;
   const Double_t mDet3_345_035 = pM[SA30]*mDet2_45_35 - pM[SA33]*mDet2_45_05 + pM[SA35]*mDet2_45_03;
   const Double_t mDet3_345_045 = pM[SA30]*mDet2_45_45 - pM[SA34]*mDet2_45_05 + pM[SA35]*mDet2_45_04;
   const Double_t mDet3_345_123 = pM[SA31]*mDet2_45_23 - pM[SA32]*mDet2_45_13 + pM[SA33]*mDet2_45_12;
   const Double_t mDet3_345_124 = pM[SA31]*mDet2_45_24 - pM[SA32]*mDet2_45_14 + pM[SA34]*mDet2_45_12;
   const Double_t mDet3_345_125 = pM[SA31]*mDet2_45_25 - pM[SA32]*mDet2_45_15 + pM[SA35]*mDet2_45_12;
   const Double_t mDet3_345_134 = pM[SA31]*mDet2_45_34 - pM[SA33]*mDet2_45_14 + pM[SA34]*mDet2_45_13;
   const Double_t mDet3_345_135 = pM[SA31]*mDet2_45_35 - pM[SA33]*mDet2_45_15 + pM[SA35]*mDet2_45_13;
   const Double_t mDet3_345_145 = pM[SA31]*mDet2_45_45 - pM[SA34]*mDet2_45_15 + pM[SA35]*mDet2_45_14;
   const Double_t mDet3_345_234 = pM[SA32]*mDet2_45_34 - pM[SA33]*mDet2_45_24 + pM[SA34]*mDet2_45_23;
   const Double_t mDet3_345_235 = pM[SA32]*mDet2_45_35 - pM[SA33]*mDet2_45_25 + pM[SA35]*mDet2_45_23;
   const Double_t mDet3_345_245 = pM[SA32]*mDet2_45_45 - pM[SA34]*mDet2_45_25 + pM[SA35]*mDet2_45_24;
   const Double_t mDet3_345_345 = pM[SA33]*mDet2_45_45 - pM[SA34]*mDet2_45_35 + pM[SA35]*mDet2_45_34;

   // Find all NECESSSARY 4x4 dets:  (55 of them)

   const Double_t mDet4_1234_0123 = pM[SA10]*mDet3_234_123 - pM[SA11]*mDet3_234_023
                                  + pM[SA12]*mDet3_234_013 - pM[SA13]*mDet3_234_012;
   const Double_t mDet4_1234_0124 = pM[SA10]*mDet3_234_124 - pM[SA11]*mDet3_234_024
                                  + pM[SA12]*mDet3_234_014 - pM[SA14]*mDet3_234_012;
   const Double_t mDet4_1234_0134 = pM[SA10]*mDet3_234_134 - pM[SA11]*mDet3_234_034
                                  + pM[SA13]*mDet3_234_014 - pM[SA14]*mDet3_234_013;
   const Double_t mDet4_1234_0234 = pM[SA10]*mDet3_234_234 - pM[SA12]*mDet3_234_034
                                  + pM[SA13]*mDet3_234_024 - pM[SA14]*mDet3_234_023;
   const Double_t mDet4_1234_1234 = pM[SA11]*mDet3_234_234 - pM[SA12]*mDet3_234_134
                                  + pM[SA13]*mDet3_234_124 - pM[SA14]*mDet3_234_123;
   const Double_t mDet4_1235_0123 = pM[SA10]*mDet3_235_123 - pM[SA11]*mDet3_235_023
                                  + pM[SA12]*mDet3_235_013 - pM[SA13]*mDet3_235_012;
   const Double_t mDet4_1235_0124 = pM[SA10]*mDet3_235_124 - pM[SA11]*mDet3_235_024
                                  + pM[SA12]*mDet3_235_014 - pM[SA14]*mDet3_235_012;
   const Double_t mDet4_1235_0125 = pM[SA10]*mDet3_235_125 - pM[SA11]*mDet3_235_025
                                  + pM[SA12]*mDet3_235_015 - pM[SA15]*mDet3_235_012;
   const Double_t mDet4_1235_0134 = pM[SA10]*mDet3_235_134 - pM[SA11]*mDet3_235_034
                                  + pM[SA13]*mDet3_235_014 - pM[SA14]*mDet3_235_013;
   const Double_t mDet4_1235_0135 = pM[SA10]*mDet3_235_135 - pM[SA11]*mDet3_235_035
                                  + pM[SA13]*mDet3_235_015 - pM[SA15]*mDet3_235_013;
   const Double_t mDet4_1235_0234 = pM[SA10]*mDet3_235_234 - pM[SA12]*mDet3_235_034
                                  + pM[SA13]*mDet3_235_024 - pM[SA14]*mDet3_235_023;
   const Double_t mDet4_1235_0235 = pM[SA10]*mDet3_235_235 - pM[SA12]*mDet3_235_035
                                  + pM[SA13]*mDet3_235_025 - pM[SA15]*mDet3_235_023;
   const Double_t mDet4_1235_1234 = pM[SA11]*mDet3_235_234 - pM[SA12]*mDet3_235_134
                                  + pM[SA13]*mDet3_235_124 - pM[SA14]*mDet3_235_123;
   const Double_t mDet4_1235_1235 = pM[SA11]*mDet3_235_235 - pM[SA12]*mDet3_235_135
                                  + pM[SA13]*mDet3_235_125 - pM[SA15]*mDet3_235_123;
   const Double_t mDet4_1245_0123 = pM[SA10]*mDet3_245_123 - pM[SA11]*mDet3_245_023
                                  + pM[SA12]*mDet3_245_013 - pM[SA13]*mDet3_245_012;
   const Double_t mDet4_1245_0124 = pM[SA10]*mDet3_245_124 - pM[SA11]*mDet3_245_024
                                  + pM[SA12]*mDet3_245_014 - pM[SA14]*mDet3_245_012;
   const Double_t mDet4_1245_0125 = pM[SA10]*mDet3_245_125 - pM[SA11]*mDet3_245_025
                                  + pM[SA12]*mDet3_245_015 - pM[SA15]*mDet3_245_012;
   const Double_t mDet4_1245_0134 = pM[SA10]*mDet3_245_134 - pM[SA11]*mDet3_245_034
                                  + pM[SA13]*mDet3_245_014 - pM[SA14]*mDet3_245_013;
   const Double_t mDet4_1245_0135 = pM[SA10]*mDet3_245_135 - pM[SA11]*mDet3_245_035
                                  + pM[SA13]*mDet3_245_015 - pM[SA15]*mDet3_245_013;
   const Double_t mDet4_1245_0145 = pM[SA10]*mDet3_245_145 - pM[SA11]*mDet3_245_045
                                  + pM[SA14]*mDet3_245_015 - pM[SA15]*mDet3_245_014;
   const Double_t mDet4_1245_0234 = pM[SA10]*mDet3_245_234 - pM[SA12]*mDet3_245_034
                                  + pM[SA13]*mDet3_245_024 - pM[SA14]*mDet3_245_023;
   const Double_t mDet4_1245_0235 = pM[SA10]*mDet3_245_235 - pM[SA12]*mDet3_245_035
                                  + pM[SA13]*mDet3_245_025 - pM[SA15]*mDet3_245_023;
   const Double_t mDet4_1245_0245 = pM[SA10]*mDet3_245_245 - pM[SA12]*mDet3_245_045
                                  + pM[SA14]*mDet3_245_025 - pM[SA15]*mDet3_245_024;
   const Double_t mDet4_1245_1234 = pM[SA11]*mDet3_245_234 - pM[SA12]*mDet3_245_134
                                  + pM[SA13]*mDet3_245_124 - pM[SA14]*mDet3_245_123;
   const Double_t mDet4_1245_1235 = pM[SA11]*mDet3_245_235 - pM[SA12]*mDet3_245_135
                                  + pM[SA13]*mDet3_245_125 - pM[SA15]*mDet3_245_123;
   const Double_t mDet4_1245_1245 = pM[SA11]*mDet3_245_245 - pM[SA12]*mDet3_245_145
                                  + pM[SA14]*mDet3_245_125 - pM[SA15]*mDet3_245_124;
   const Double_t mDet4_1345_0123 = pM[SA10]*mDet3_345_123 - pM[SA11]*mDet3_345_023
                                  + pM[SA12]*mDet3_345_013 - pM[SA13]*mDet3_345_012;
   const Double_t mDet4_1345_0124 = pM[SA10]*mDet3_345_124 - pM[SA11]*mDet3_345_024
                                  + pM[SA12]*mDet3_345_014 - pM[SA14]*mDet3_345_012;
   const Double_t mDet4_1345_0125 = pM[SA10]*mDet3_345_125 - pM[SA11]*mDet3_345_025
                                  + pM[SA12]*mDet3_345_015 - pM[SA15]*mDet3_345_012;
   const Double_t mDet4_1345_0134 = pM[SA10]*mDet3_345_134 - pM[SA11]*mDet3_345_034
                                  + pM[SA13]*mDet3_345_014 - pM[SA14]*mDet3_345_013;
   const Double_t mDet4_1345_0135 = pM[SA10]*mDet3_345_135 - pM[SA11]*mDet3_345_035
                                  + pM[SA13]*mDet3_345_015 - pM[SA15]*mDet3_345_013;
   const Double_t mDet4_1345_0145 = pM[SA10]*mDet3_345_145 - pM[SA11]*mDet3_345_045
                                  + pM[SA14]*mDet3_345_015 - pM[SA15]*mDet3_345_014;
   const Double_t mDet4_1345_0234 = pM[SA10]*mDet3_345_234 - pM[SA12]*mDet3_345_034
                                  + pM[SA13]*mDet3_345_024 - pM[SA14]*mDet3_345_023;
   const Double_t mDet4_1345_0235 = pM[SA10]*mDet3_345_235 - pM[SA12]*mDet3_345_035
                                  + pM[SA13]*mDet3_345_025 - pM[SA15]*mDet3_345_023;
   const Double_t mDet4_1345_0245 = pM[SA10]*mDet3_345_245 - pM[SA12]*mDet3_345_045
                                  + pM[SA14]*mDet3_345_025 - pM[SA15]*mDet3_345_024;
   const Double_t mDet4_1345_0345 = pM[SA10]*mDet3_345_345 - pM[SA13]*mDet3_345_045
                                  + pM[SA14]*mDet3_345_035 - pM[SA15]*mDet3_345_034;
   const Double_t mDet4_1345_1234 = pM[SA11]*mDet3_345_234 - pM[SA12]*mDet3_345_134
                                  + pM[SA13]*mDet3_345_124 - pM[SA14]*mDet3_345_123;
   const Double_t mDet4_1345_1235 = pM[SA11]*mDet3_345_235 - pM[SA12]*mDet3_345_135
                                  + pM[SA13]*mDet3_345_125 - pM[SA15]*mDet3_345_123;
   const Double_t mDet4_1345_1245 = pM[SA11]*mDet3_345_245 - pM[SA12]*mDet3_345_145
                                  + pM[SA14]*mDet3_345_125 - pM[SA15]*mDet3_345_124;
   const Double_t mDet4_1345_1345 = pM[SA11]*mDet3_345_345 - pM[SA13]*mDet3_345_145
                                  + pM[SA14]*mDet3_345_135 - pM[SA15]*mDet3_345_134;
   const Double_t mDet4_2345_0123 = pM[SA20]*mDet3_345_123 - pM[SA21]*mDet3_345_023
                                  + pM[SA22]*mDet3_345_013 - pM[SA23]*mDet3_345_012;
   const Double_t mDet4_2345_0124 = pM[SA20]*mDet3_345_124 - pM[SA21]*mDet3_345_024
                                  + pM[SA22]*mDet3_345_014 - pM[SA24]*mDet3_345_012;
   const Double_t mDet4_2345_0125 = pM[SA20]*mDet3_345_125 - pM[SA21]*mDet3_345_025
                                  + pM[SA22]*mDet3_345_015 - pM[SA25]*mDet3_345_012;
   const Double_t mDet4_2345_0134 = pM[SA20]*mDet3_345_134 - pM[SA21]*mDet3_345_034
                                  + pM[SA23]*mDet3_345_014 - pM[SA24]*mDet3_345_013;
   const Double_t mDet4_2345_0135 = pM[SA20]*mDet3_345_135 - pM[SA21]*mDet3_345_035
                                  + pM[SA23]*mDet3_345_015 - pM[SA25]*mDet3_345_013;
   const Double_t mDet4_2345_0145 = pM[SA20]*mDet3_345_145 - pM[SA21]*mDet3_345_045
                                  + pM[SA24]*mDet3_345_015 - pM[SA25]*mDet3_345_014;
   const Double_t mDet4_2345_0234 = pM[SA20]*mDet3_345_234 - pM[SA22]*mDet3_345_034
                                  + pM[SA23]*mDet3_345_024 - pM[SA24]*mDet3_345_023;
   const Double_t mDet4_2345_0235 = pM[SA20]*mDet3_345_235 - pM[SA22]*mDet3_345_035
                                  + pM[SA23]*mDet3_345_025 - pM[SA25]*mDet3_345_023;
   const Double_t mDet4_2345_0245 = pM[SA20]*mDet3_345_245 - pM[SA22]*mDet3_345_045
                                  + pM[SA24]*mDet3_345_025 - pM[SA25]*mDet3_345_024;
   const Double_t mDet4_2345_0345 = pM[SA20]*mDet3_345_345 - pM[SA23]*mDet3_345_045
                                  + pM[SA24]*mDet3_345_035 - pM[SA25]*mDet3_345_034;
   const Double_t mDet4_2345_1234 = pM[SA21]*mDet3_345_234 - pM[SA22]*mDet3_345_134
                                  + pM[SA23]*mDet3_345_124 - pM[SA24]*mDet3_345_123;
   const Double_t mDet4_2345_1235 = pM[SA21]*mDet3_345_235 - pM[SA22]*mDet3_345_135
                                  + pM[SA23]*mDet3_345_125 - pM[SA25]*mDet3_345_123;
   const Double_t mDet4_2345_1245 = pM[SA21]*mDet3_345_245 - pM[SA22]*mDet3_345_145
                                  + pM[SA24]*mDet3_345_125 - pM[SA25]*mDet3_345_124;
   const Double_t mDet4_2345_1345 = pM[SA21]*mDet3_345_345 - pM[SA23]*mDet3_345_145
                                  + pM[SA24]*mDet3_345_135 - pM[SA25]*mDet3_345_134;
   const Double_t mDet4_2345_2345 = pM[SA22]*mDet3_345_345 - pM[SA23]*mDet3_345_245
                                  + pM[SA24]*mDet3_345_235 - pM[SA25]*mDet3_345_234;

   // Find all NECESSSARY 5x5 dets:  (19 of them)

   const Double_t mDet5_01234_01234 = pM[SA00]*mDet4_1234_1234 - pM[SA01]*mDet4_1234_0234
                                    + pM[SA02]*mDet4_1234_0134 - pM[SA03]*mDet4_1234_0124 + pM[SA04]*mDet4_1234_0123;
   const Double_t mDet5_01235_01234 = pM[SA00]*mDet4_1235_1234 - pM[SA01]*mDet4_1235_0234
                                    + pM[SA02]*mDet4_1235_0134 - pM[SA03]*mDet4_1235_0124 + pM[SA04]*mDet4_1235_0123;
   const Double_t mDet5_01235_01235 = pM[SA00]*mDet4_1235_1235 - pM[SA01]*mDet4_1235_0235
                                    + pM[SA02]*mDet4_1235_0135 - pM[SA03]*mDet4_1235_0125 + pM[SA05]*mDet4_1235_0123;
   const Double_t mDet5_01245_01234 = pM[SA00]*mDet4_1245_1234 - pM[SA01]*mDet4_1245_0234
                                    + pM[SA02]*mDet4_1245_0134 - pM[SA03]*mDet4_1245_0124 + pM[SA04]*mDet4_1245_0123;
   const Double_t mDet5_01245_01235 = pM[SA00]*mDet4_1245_1235 - pM[SA01]*mDet4_1245_0235
                                    + pM[SA02]*mDet4_1245_0135 - pM[SA03]*mDet4_1245_0125 + pM[SA05]*mDet4_1245_0123;
   const Double_t mDet5_01245_01245 = pM[SA00]*mDet4_1245_1245 - pM[SA01]*mDet4_1245_0245
                                    + pM[SA02]*mDet4_1245_0145 - pM[SA04]*mDet4_1245_0125 + pM[SA05]*mDet4_1245_0124;
   const Double_t mDet5_01345_01234 = pM[SA00]*mDet4_1345_1234 - pM[SA01]*mDet4_1345_0234
                                    + pM[SA02]*mDet4_1345_0134 - pM[SA03]*mDet4_1345_0124 + pM[SA04]*mDet4_1345_0123;
   const Double_t mDet5_01345_01235 = pM[SA00]*mDet4_1345_1235 - pM[SA01]*mDet4_1345_0235
                                    + pM[SA02]*mDet4_1345_0135 - pM[SA03]*mDet4_1345_0125 + pM[SA05]*mDet4_1345_0123;
   const Double_t mDet5_01345_01245 = pM[SA00]*mDet4_1345_1245 - pM[SA01]*mDet4_1345_0245
                                    + pM[SA02]*mDet4_1345_0145 - pM[SA04]*mDet4_1345_0125 + pM[SA05]*mDet4_1345_0124;
   const Double_t mDet5_01345_01345 = pM[SA00]*mDet4_1345_1345 - pM[SA01]*mDet4_1345_0345
                                    + pM[SA03]*mDet4_1345_0145 - pM[SA04]*mDet4_1345_0135 + pM[SA05]*mDet4_1345_0134;
   const Double_t mDet5_02345_01234 = pM[SA00]*mDet4_2345_1234 - pM[SA01]*mDet4_2345_0234
                                    + pM[SA02]*mDet4_2345_0134 - pM[SA03]*mDet4_2345_0124 + pM[SA04]*mDet4_2345_0123;
   const Double_t mDet5_02345_01235 = pM[SA00]*mDet4_2345_1235 - pM[SA01]*mDet4_2345_0235
                                    + pM[SA02]*mDet4_2345_0135 - pM[SA03]*mDet4_2345_0125 + pM[SA05]*mDet4_2345_0123;
   const Double_t mDet5_02345_01245 = pM[SA00]*mDet4_2345_1245 - pM[SA01]*mDet4_2345_0245
                                    + pM[SA02]*mDet4_2345_0145 - pM[SA04]*mDet4_2345_0125 + pM[SA05]*mDet4_2345_0124;
   const Double_t mDet5_02345_01345 = pM[SA00]*mDet4_2345_1345 - pM[SA01]*mDet4_2345_0345
                                    + pM[SA03]*mDet4_2345_0145 - pM[SA04]*mDet4_2345_0135 + pM[SA05]*mDet4_2345_0134;
   const Double_t mDet5_02345_02345 = pM[SA00]*mDet4_2345_2345 - pM[SA02]*mDet4_2345_0345
                                    + pM[SA03]*mDet4_2345_0245 - pM[SA04]*mDet4_2345_0235 + pM[SA05]*mDet4_2345_0234;
   const Double_t mDet5_12345_01234 = pM[SA10]*mDet4_2345_1234 - pM[SA11]*mDet4_2345_0234
                                    + pM[SA12]*mDet4_2345_0134 - pM[SA13]*mDet4_2345_0124 + pM[SA14]*mDet4_2345_0123;
   const Double_t mDet5_12345_01235 = pM[SA10]*mDet4_2345_1235 - pM[SA11]*mDet4_2345_0235
                                    + pM[SA12]*mDet4_2345_0135 - pM[SA13]*mDet4_2345_0125 + pM[SA15]*mDet4_2345_0123;
   const Double_t mDet5_12345_01245 = pM[SA10]*mDet4_2345_1245 - pM[SA11]*mDet4_2345_0245
                                    + pM[SA12]*mDet4_2345_0145 - pM[SA14]*mDet4_2345_0125 + pM[SA15]*mDet4_2345_0124;
   const Double_t mDet5_12345_01345 = pM[SA10]*mDet4_2345_1345 - pM[SA11]*mDet4_2345_0345
                                    + pM[SA13]*mDet4_2345_0145 - pM[SA14]*mDet4_2345_0135 + pM[SA15]*mDet4_2345_0134;
   const Double_t mDet5_12345_02345 = pM[SA10]*mDet4_2345_2345 - pM[SA12]*mDet4_2345_0345
                                    + pM[SA13]*mDet4_2345_0245 - pM[SA14]*mDet4_2345_0235 + pM[SA15]*mDet4_2345_0234;
   const Double_t mDet5_12345_12345 = pM[SA11]*mDet4_2345_2345 - pM[SA12]*mDet4_2345_1345
                                    + pM[SA13]*mDet4_2345_1245 - pM[SA14]*mDet4_2345_1235 + pM[SA15]*mDet4_2345_1234;

   // Find the determinant

   const Double_t det = pM[SA00]*mDet5_12345_12345 - pM[SA01]*mDet5_12345_02345 + pM[SA02]*mDet5_12345_01345
                      - pM[SA03]*mDet5_12345_01245 + pM[SA04]*mDet5_12345_01235 - pM[SA05]*mDet5_12345_01234;

   if (determ)
      *determ = det;

   if ( det == 0 ) {
      //Error("Inv6x6","matrix is singular");
      return kFALSE;
   }

   const Double_t oneOverDet = 1.0/det;
   const Double_t mn1OverDet = - oneOverDet;

   pM[SA00] =  mDet5_12345_12345*oneOverDet;
   pM[SA01] =  mDet5_12345_02345*mn1OverDet;
   pM[SA02] =  mDet5_12345_01345*oneOverDet;
   pM[SA03] =  mDet5_12345_01245*mn1OverDet;
   pM[SA04] =  mDet5_12345_01235*oneOverDet;
   pM[SA05] =  mDet5_12345_01234*mn1OverDet;

   pM[SA11] =  mDet5_02345_02345*oneOverDet;
   pM[SA12] =  mDet5_02345_01345*mn1OverDet;
   pM[SA13] =  mDet5_02345_01245*oneOverDet;
   pM[SA14] =  mDet5_02345_01235*mn1OverDet;
   pM[SA15] =  mDet5_02345_01234*oneOverDet;

   pM[SA22] =  mDet5_01345_01345*oneOverDet;
   pM[SA23] =  mDet5_01345_01245*mn1OverDet;
   pM[SA24] =  mDet5_01345_01235*oneOverDet;
   pM[SA25] =  mDet5_01345_01234*mn1OverDet;

   pM[SA33] =  mDet5_01245_01245*oneOverDet;
   pM[SA34] =  mDet5_01245_01235*mn1OverDet;
   pM[SA35] =  mDet5_01245_01234*oneOverDet;

   pM[SA44] =  mDet5_01235_01235*oneOverDet;
   pM[SA45] =  mDet5_01235_01234*mn1OverDet;

   pM[SA55] =  mDet5_01234_01234*oneOverDet;

   for (Int_t irow = 0; irow < 6; irow++) {
      const Int_t rowOff1 = irow*6;
      for (Int_t icol = 0; icol < irow; icol++) {
         const Int_t rowOff2 = icol*6;
         pM[rowOff1+icol] = pM[rowOff2+irow];
      }
   }

   return kTRUE;
}

//#include "TMatrixFSymfwd.h"

template Bool_t TMatrixTSymCramerInv::Inv2x2<Float_t>(TMatrixFSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv3x3<Float_t>(TMatrixFSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv4x4<Float_t>(TMatrixFSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv5x5<Float_t>(TMatrixFSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv6x6<Float_t>(TMatrixFSym&,Double_t*);

//#include "TMatrixDSymfwd.h"

template Bool_t TMatrixTSymCramerInv::Inv2x2<Double_t>(TMatrixDSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv3x3<Double_t>(TMatrixDSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv4x4<Double_t>(TMatrixDSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv5x5<Double_t>(TMatrixDSym&,Double_t*);
template Bool_t TMatrixTSymCramerInv::Inv6x6<Double_t>(TMatrixDSym&,Double_t*);

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//#include "TDecompLU.h"
//#include "TMath.h"

ClassImp(TDecompLU);

/** \class TDecompLU
    \ingroup Matrix

 LU Decomposition class

 Decompose  a general n x n matrix A into P A = L U

 where P is a permutation matrix, L is unit lower triangular and U
 is upper triangular.
 L is stored in the strict lower triangular part of the matrix fLU.
 The diagonal elements of L are unity and are not stored.
 U is stored in the diagonal and upper triangular part of the matrix
 fU.
 P is stored in the index array fIndex : j = fIndex[i] indicates that
 row j and row i should be swapped .

 fSign gives the sign of the permutation, (-1)^n, where n is the
 number of interchanges in the permutation.

 fLU has the same indexing range as matrix A .

 The decomposition fails if a diagonal element of abs(fLU) is == 0,
 The matrix fUL is made invalid .
*/

////////////////////////////////////////////////////////////////////////////////
/// Default constructor

TDecompLU::TDecompLU()
{
   fSign = 0.0;
   fNIndex = 0;
   fIndex = 0;
   fImplicitPivot = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor for (nrows x nrows) matrix

TDecompLU::TDecompLU(Int_t nrows)
{
   fSign = 1.0;
   fNIndex = nrows;
   fIndex = new Int_t[fNIndex];
   memset(fIndex,0,fNIndex*sizeof(Int_t));
   fImplicitPivot = 0;
   fLU.ResizeTo(nrows,nrows);
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor for ([row_lwb..row_upb] x [row_lwb..row_upb]) matrix

TDecompLU::TDecompLU(Int_t row_lwb,Int_t row_upb)
{
   const Int_t nrows = row_upb-row_lwb+1;
   fSign = 1.0;
   fNIndex = nrows;
   fIndex = new Int_t[fNIndex];
   memset(fIndex,0,fNIndex*sizeof(Int_t));
   fRowLwb = row_lwb;
   fColLwb = row_lwb;
   fImplicitPivot = 0;
   fLU.ResizeTo(row_lwb,row_lwb+nrows-1,row_lwb,row_lwb+nrows-1);
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor for matrix a

TDecompLU::TDecompLU(const TMatrixD &a,Double_t tol,Int_t implicit)
{
   //R__ASSERT(a.IsValid());

   if (a.GetNrows() != a.GetNcols() || a.GetRowLwb() != a.GetColLwb()) {
      //Error("TDecompLU(const TMatrixD &","matrix should be square");
      return;
   }

   SetBit(kMatrixSet);
   fCondition = a.Norm1();
   fImplicitPivot = implicit;
   fTol = a.GetTol();
   if (tol > 0)
      fTol = tol;

   fSign = 1.0;
   fNIndex = a.GetNcols();
   fIndex = new Int_t[fNIndex];
   memset(fIndex,0,fNIndex*sizeof(Int_t));

   fRowLwb = a.GetRowLwb();
   fColLwb = a.GetColLwb();
   fLU.ResizeTo(a);
   fLU = a;
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

TDecompLU::TDecompLU(const TDecompLU &another) : TDecompBase(another)
{
   fNIndex = 0;
   fIndex  = 0;
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix A is decomposed in components U and L so that P * A = U * L
/// If the decomposition succeeds, bit kDecomposed is set , otherwise kSingular

Bool_t TDecompLU::Decompose()
{
   if (TestBit(kDecomposed)) return kTRUE;

   if ( !TestBit(kMatrixSet) ) {
      //Error("Decompose()","Matrix has not been set");
      return kFALSE;
   }

   Int_t nrZeros = 0;
   Bool_t ok;
   if (fImplicitPivot)
      ok = DecomposeLUCrout(fLU,fIndex,fSign,fTol,nrZeros);
   else
      ok = DecomposeLUGauss(fLU,fIndex,fSign,fTol,nrZeros);

   if (!ok) SetBit(kSingular);
   else     SetBit(kDecomposed);

   return ok;
}

////////////////////////////////////////////////////////////////////////////////
/// Reconstruct the original matrix using the decomposition parts

const TMatrixD TDecompLU::GetMatrix()
{
   if (TestBit(kSingular)) {
      //Error("GetMatrix()","Matrix is singular");
      return TMatrixD();
   }
   if ( !TestBit(kDecomposed) ) {
      if (!Decompose()) {
         //Error("GetMatrix()","Decomposition failed");
         return TMatrixD();
      }
   }

   TMatrixD mL = fLU;
   TMatrixD mU = fLU;
   Double_t * const pU = mU.GetMatrixArray();
   Double_t * const pL = mL.GetMatrixArray();
   const Int_t n = fLU.GetNcols();
   for (Int_t irow = 0; irow < n; irow++) {
      const Int_t off_row = irow*n;
         for (Int_t icol = 0; icol < n; icol++) {
            if (icol > irow)      pL[off_row+icol] = 0.;
            else if (icol < irow) pU[off_row+icol] = 0.;
            else                  pL[off_row+icol] = 1.;
         }
      }

   TMatrixD a = mL*mU;

   // swap rows

   Double_t * const pA = a.GetMatrixArray();
   for (Int_t i = n-1; i >= 0; i--) {
      const Int_t j = fIndex[i];
      if (j != i) {
         const Int_t off_j = j*n;
         const Int_t off_i = i*n;
         for (Int_t k = 0; k < n; k++) {
            const Double_t tmp = pA[off_j+k];
            pA[off_j+k] = pA[off_i+k];
            pA[off_i+k] = tmp;
         }
      }
   }

   return a;
}

////////////////////////////////////////////////////////////////////////////////
/// Set matrix to be decomposed

void TDecompLU::SetMatrix(const TMatrixD &a)
{
   //R__ASSERT(a.IsValid());

   ResetStatus();
   if (a.GetNrows() != a.GetNcols() || a.GetRowLwb() != a.GetColLwb()) {
      //Error("TDecompLU(const TMatrixD &","matrix should be square");
      return;
   }

   SetBit(kMatrixSet);
   fCondition = a.Norm1();

   fSign = 1.0;
   if (fNIndex != a.GetNcols()) {
      fNIndex = a.GetNcols();
      delete [] fIndex;
      fIndex = new Int_t[fNIndex];
      memset(fIndex,0,fNIndex*sizeof(Int_t));
   }

   fRowLwb = a.GetRowLwb();
   fColLwb = a.GetColLwb();
   fLU.ResizeTo(a);
   fLU = a;
}

////////////////////////////////////////////////////////////////////////////////
/// Solve Ax=b assuming the LU form of A is stored in fLU, but assume b has *not*
/// been transformed.  Solution returned in b.

Bool_t TDecompLU::Solve(TVectorD &b)
{
   //R__ASSERT(b.IsValid());
   if (TestBit(kSingular)) {
      //Error("Solve()","Matrix is singular");
      return kFALSE;
   }
   if ( !TestBit(kDecomposed) ) {
      if (!Decompose()) {
         //Error("Solve()","Decomposition failed");
         return kFALSE;
      }
   }

   if (fLU.GetNrows() != b.GetNrows() || fLU.GetRowLwb() != b.GetLwb()) {
      //Error("Solve(TVectorD &","vector and matrix incompatible");
      return kFALSE;
   }

   const Int_t n = fLU.GetNrows();

   const Double_t *pLU = fLU.GetMatrixArray();
   Double_t *pb  = b.GetMatrixArray();

   Int_t i;

   // Check for zero diagonals
   for (i = 0; i < n ; i++) {
      const Int_t off_i = i*n;
      if (TMath::Abs(pLU[off_i+i]) < fTol) {
         //Error("Solve(TVectorD &b)","LU[%d,%d]=%.4e < %.4e",i,i,pLU[off_i+i],fTol);
         return kFALSE;
      }
   }

   // Transform b allowing for leading zeros
   Int_t nonzero = -1;
   for (i = 0; i < n; i++) {
      const Int_t off_i = i*n;
      const Int_t iperm = fIndex[i];
      Double_t r = pb[iperm];
      pb[iperm] = pb[i];
      if (nonzero >= 0)
         for (Int_t j = nonzero; j < i; j++)
            r -= pLU[off_i+j]*pb[j];
      else if (r != 0.0)
         nonzero = i;
      pb[i] = r;
   }

   // Backward substitution
   for (i = n-1; i >= 0; i--) {
      const Int_t off_i = i*n;
      Double_t r = pb[i];
      for (Int_t j = i+1; j < n; j++)
         r -= pLU[off_i+j]*pb[j];
      pb[i] = r/pLU[off_i+i];
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Solve Ax=b assuming the LU form of A is stored in fLU, but assume b has *not*
/// been transformed.  Solution returned in b.

Bool_t TDecompLU::Solve(TMatrixDColumn &cb)
{
   TMatrixDBase *b = const_cast<TMatrixDBase *>(cb.GetMatrix());
   //R__ASSERT(b->IsValid());
   if (TestBit(kSingular)) {
      //Error("Solve()","Matrix is singular");
      return kFALSE;
   }
   if ( !TestBit(kDecomposed) ) {
      if (!Decompose()) {
         //Error("Solve()","Decomposition failed");
         return kFALSE;
      }
   }

   if (fLU.GetNrows() != b->GetNrows() || fLU.GetRowLwb() != b->GetRowLwb()) {
      //Error("Solve(TMatrixDColumn &","vector and matrix incompatible");
      return kFALSE;
   }

   const Int_t     n   = fLU.GetNrows();
   const Double_t *pLU = fLU.GetMatrixArray();

   Int_t i;

   // Check for zero diagonals
   for (i = 0; i < n ; i++) {
      const Int_t off_i = i*n;
      if (TMath::Abs(pLU[off_i+i]) < fTol) {
         //Error("Solve(TMatrixDColumn &cb)","LU[%d,%d]=%.4e < %.4e",i,i,pLU[off_i+i],fTol);
         return kFALSE;
      }
   }

   Double_t *pcb = cb.GetPtr();
   const Int_t     inc = cb.GetInc();

   // Transform b allowing for leading zeros
   Int_t nonzero = -1;
   for (i = 0; i < n; i++) {
      const Int_t off_i  = i*n;
      const Int_t off_i2 = i*inc;
      const Int_t iperm = fIndex[i];
      const Int_t off_iperm = iperm*inc;
      Double_t r = pcb[off_iperm];
      pcb[off_iperm] = pcb[off_i2];
      if (nonzero >=0)
         for (Int_t j = nonzero; j <= i-1; j++)
            r -= pLU[off_i+j]*pcb[j*inc];
      else if (r != 0.0)
         nonzero = i;
      pcb[off_i2] = r;
   }

   // Backward substitution
   for (i = n-1; i >= 0; i--) {
      const Int_t off_i  = i*n;
      const Int_t off_i2 = i*inc;
      Double_t r = pcb[off_i2];
      for (Int_t j = i+1; j < n; j++)
         r -= pLU[off_i+j]*pcb[j*inc];
      pcb[off_i2] = r/pLU[off_i+i];
   }

   return kTRUE;
}


////////////////////////////////////////////////////////////////////////////////
/// Solve A^T x=b assuming the LU form of A^T is stored in fLU, but assume b has *not*
/// been transformed.  Solution returned in b.

Bool_t TDecompLU::TransSolve(TVectorD &b)
{
   //R__ASSERT(b.IsValid());
   if (TestBit(kSingular)) {
      //Error("TransSolve()","Matrix is singular");
      return kFALSE;
   }
   if ( !TestBit(kDecomposed) ) {
      if (!Decompose()) {
         //Error("TransSolve()","Decomposition failed");
         return kFALSE;
      }
   }

   if (fLU.GetNrows() != b.GetNrows() || fLU.GetRowLwb() != b.GetLwb()) {
      //Error("TransSolve(TVectorD &","vector and matrix incompatible");
      return kFALSE;
   }

   const Int_t n = fLU.GetNrows();

   const Double_t *pLU = fLU.GetMatrixArray();
   Double_t *pb  = b.GetMatrixArray();

   Int_t i;

   // Check for zero diagonals
   for (i = 0; i < n ; i++) {
      const Int_t off_i = i*n;
      if (TMath::Abs(pLU[off_i+i]) < fTol) {
         //Error("TransSolve(TVectorD &b)","LU[%d,%d]=%.4e < %.4e",i,i,pLU[off_i+i],fTol);
         return kFALSE;
      }
   }

   // Forward Substitution
   for (i = 0; i < n; i++) {
      const Int_t off_i = i*n;
      Double_t r = pb[i];
      for (Int_t j = 0; j < i ; j++) {
         const Int_t off_j = j*n;
         r -= pLU[off_j+i]*pb[j];
      }
      pb[i] = r/pLU[off_i+i];
   }

   // Transform b allowing for leading zeros
   Int_t nonzero = -1;
   for (i = n-1 ; i >= 0; i--) {
      Double_t r = pb[i];
      if (nonzero >= 0) {
         for (Int_t j = i+1; j <= nonzero; j++) {
            const Int_t off_j = j*n;
            r -= pLU[off_j+i]*pb[j];
         }
      } else if (r != 0.0)
         nonzero = i;
      const Int_t iperm = fIndex[i];
      pb[i]     = pb[iperm];
      pb[iperm] = r;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Solve A^T x=b assuming the LU form of A^T is stored in fLU, but assume b has *not*
/// been transformed.  Solution returned in b.

Bool_t TDecompLU::TransSolve(TMatrixDColumn &cb)
{
   TMatrixDBase *b = const_cast<TMatrixDBase *>(cb.GetMatrix());
   //R__ASSERT(b->IsValid());
   if (TestBit(kSingular)) {
      //Error("TransSolve()","Matrix is singular");
      return kFALSE;
   }
   if ( !TestBit(kDecomposed) ) {
      if (!Decompose()) {
         //Error("TransSolve()","Decomposition failed");
         return kFALSE;
      }
   }

   if (fLU.GetNrows() != b->GetNrows() || fLU.GetRowLwb() != b->GetRowLwb()) {
      //Error("TransSolve(TMatrixDColumn &","vector and matrix incompatible");
      return kFALSE;
   }

   const Int_t n   = fLU.GetNrows();
   const Int_t lwb = fLU.GetRowLwb();

   const Double_t *pLU = fLU.GetMatrixArray();

   Int_t i;

   // Check for zero diagonals
   for (i = 0; i < n ; i++) {
      const Int_t off_i = i*n;
      if (TMath::Abs(pLU[off_i+i]) < fTol) {
         //Error("TransSolve(TMatrixDColumn &cb)","LU[%d,%d]=%.4e < %.4e",i,i,pLU[off_i+i],fTol);
         return kFALSE;
      }
   }

   // Forward Substitution
   for (i = 0; i < n; i++) {
      const Int_t off_i = i*n;
      Double_t r = cb(i+lwb);
      for (Int_t j = 0; j < i ; j++) {
         const Int_t off_j = j*n;
         r -= pLU[off_j+i]*cb(j+lwb);
      }
      cb(i+lwb) = r/pLU[off_i+i];
   }

   // Transform b allowing for leading zeros
   Int_t nonzero = -1;
   for (i = n-1 ; i >= 0; i--) {
      Double_t r = cb(i+lwb);
      if (nonzero >= 0) {
         for (Int_t j = i+1; j <= nonzero; j++) {
            const Int_t off_j = j*n;
            r -= pLU[off_j+i]*cb(j+lwb);
         }
      } else if (r != 0.0)
         nonzero = i;
      const Int_t iperm = fIndex[i];
      cb(i+lwb)     = cb(iperm+lwb);
      cb(iperm+lwb) = r;
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate determinant det = d1*TMath::Power(2.,d2)

void TDecompLU::Det(Double_t &d1,Double_t &d2)
{
   if ( !TestBit(kDetermined) ) {
      if ( !TestBit(kDecomposed) )
         Decompose();
      TDecompBase::Det(d1,d2);
      fDet1 *= fSign;
      SetBit(kDetermined);
   }
   d1 = fDet1;
   d2 = fDet2;
}

////////////////////////////////////////////////////////////////////////////////
/// For a matrix A(m,m), its inverse A_inv is defined as A * A_inv = A_inv * A = unit
/// (m x m) Ainv is returned .

Bool_t TDecompLU::Invert(TMatrixD &inv)
{
   if (inv.GetNrows()  != GetNrows()  || inv.GetNcols()  != GetNcols() ||
        inv.GetRowLwb() != GetRowLwb() || inv.GetColLwb() != GetColLwb()) {
      //Error("Invert(TMatrixD &","Input matrix has wrong shape");
      return kFALSE;
   }

   inv.UnitMatrix();
   const Bool_t status = MultiSolve(inv);

   return status;
}

////////////////////////////////////////////////////////////////////////////////
/// For a matrix A(m,n), its inverse A_inv is defined as A * A_inv = A_inv * A = unit
/// (n x m) Ainv is returned .

TMatrixD TDecompLU::Invert(Bool_t &status)
{
   const Int_t rowLwb = GetRowLwb();
   const Int_t rowUpb = rowLwb+GetNrows()-1;

   TMatrixD inv(rowLwb,rowUpb,rowLwb,rowUpb);
   inv.UnitMatrix();
   status = MultiSolve(inv);

   return inv;
}

////////////////////////////////////////////////////////////////////////////////
///Print internals of this object

void TDecompLU::Print(Option_t *opt) const
{
   TDecompBase::Print(opt);
   printf("fImplicitPivot = %d\n",fImplicitPivot);
   printf("fSign          = %f\n",fSign);
   printf("fIndex:\n");
   for (Int_t i = 0; i < fNIndex; i++)
      printf("[%d] = %d\n",i,fIndex[i]);
   fLU.Print("fLU");
}

////////////////////////////////////////////////////////////////////////////////
///assignment operator

TDecompLU &TDecompLU::operator=(const TDecompLU &source)
{
   if (this != &source) {
      TDecompBase::operator=(source);
      fLU.ResizeTo(source.fLU);
      fLU   = source.fLU;
      fSign = source.fSign;
      fImplicitPivot = source.fImplicitPivot;
      if (fNIndex != source.fNIndex) {
         if (fIndex)
            delete [] fIndex;
         fNIndex = source.fNIndex;
         fIndex = new Int_t[fNIndex];
      }
      if (fIndex) memcpy(fIndex,source.fIndex,fNIndex*sizeof(Int_t));
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Crout/Doolittle algorithm of LU decomposing a square matrix, with implicit partial
/// pivoting.  The decomposition is stored in fLU: U is explicit in the upper triag
/// and L is in multiplier form in the subdiagionals .
/// Row permutations are mapped out in fIndex. fSign, used for calculating the
/// determinant, is +/- 1 for even/odd row permutations. .

Bool_t TDecompLU::DecomposeLUCrout(TMatrixD &lu,Int_t *index,Double_t &sign,
                                   Double_t tol,Int_t &nrZeros)
{
   const Int_t     n     = lu.GetNcols();
   Double_t *pLU   = lu.GetMatrixArray();

   Double_t work[kWorkMax];
   Bool_t isAllocated = kFALSE;
   Double_t *scale = work;
   if (n > kWorkMax) {
      isAllocated = kTRUE;
      scale = new Double_t[n];
   }

   sign    = 1.0;
   nrZeros = 0;
   // Find implicit scaling factors for each row
   for (Int_t i = 0; i < n ; i++) {
      const Int_t off_i = i*n;
      Double_t max = 0.0;
      for (Int_t j = 0; j < n; j++) {
         const Double_t tmp = TMath::Abs(pLU[off_i+j]);
         if (tmp > max)
            max = tmp;
      }
      scale[i] = (max == 0.0 ? 0.0 : 1.0/max);
   }

   for (Int_t j = 0; j < n; j++) {
      const Int_t off_j = j*n;
      // Run down jth column from top to diag, to form the elements of U.
      for (Int_t i = 0; i < j; i++) {
         const Int_t off_i = i*n;
         Double_t r = pLU[off_i+j];
         for (Int_t k = 0; k < i; k++) {
            const Int_t off_k = k*n;
            r -= pLU[off_i+k]*pLU[off_k+j];
         }
         pLU[off_i+j] = r;
      }

      // Run down jth subdiag to form the residuals after the elimination of
      // the first j-1 subdiags.  These residuals divided by the appropriate
      // diagonal term will become the multipliers in the elimination of the jth.
      // subdiag. Find fIndex of largest scaled term in imax.

      Double_t max = 0.0;
      Int_t imax = 0;
      for (Int_t i = j; i < n; i++) {
         const Int_t off_i = i*n;
         Double_t r = pLU[off_i+j];
         for (Int_t k = 0; k < j; k++) {
            const Int_t off_k = k*n;
            r -= pLU[off_i+k]*pLU[off_k+j];
         }
         pLU[off_i+j] = r;
         const Double_t tmp = scale[i]*TMath::Abs(r);
         if (tmp >= max) {
            max = tmp;
            imax = i;
         }
      }

      // Permute current row with imax
      if (j != imax) {
         const Int_t off_imax = imax*n;
         for (Int_t k = 0; k < n; k++ ) {
            const Double_t tmp = pLU[off_imax+k];
            pLU[off_imax+k] = pLU[off_j+k];
            pLU[off_j+k]    = tmp;
         }
         sign = -sign;
         scale[imax] = scale[j];
      }
      index[j] = imax;

      // If diag term is not zero divide subdiag to form multipliers.
      if (pLU[off_j+j] != 0.0) {
         if (TMath::Abs(pLU[off_j+j]) < tol)
            nrZeros++;
         if (j != n-1) {
            const Double_t tmp = 1.0/pLU[off_j+j];
            for (Int_t i = j+1; i < n; i++) {
               const Int_t off_i = i*n;
               pLU[off_i+j] *= tmp;
            }
         }
      } else {
         //::Error("TDecompLU::DecomposeLUCrout","matrix is singular");
         if (isAllocated)  delete [] scale;
         return kFALSE;
      }
   }

   if (isAllocated)
      delete [] scale;

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// LU decomposition using Gaussian Elimination with partial pivoting (See Golub &
/// Van Loan, Matrix Computations, Algorithm 3.4.1) of a square matrix .
/// The decomposition is stored in fLU: U is explicit in the upper triag and L is in
/// multiplier form in the subdiagionals . Row permutations are mapped out in fIndex.
/// fSign, used for calculating the determinant, is +/- 1 for even/odd row permutations.
/// Since this algorithm uses partial pivoting without scaling like in Crout/Doolitle.
/// it is somewhat faster but less precise .

Bool_t TDecompLU::DecomposeLUGauss(TMatrixD &lu,Int_t *index,Double_t &sign,
                                   Double_t tol,Int_t &nrZeros)
{
   const Int_t     n   = lu.GetNcols();
   Double_t *pLU = lu.GetMatrixArray();

   sign    = 1.0;
   nrZeros = 0;

   index[n-1] = n-1;
   for (Int_t j = 0; j < n-1; j++) {
      const Int_t off_j = j*n;

      // Find maximum in the j-th column

      Double_t max = TMath::Abs(pLU[off_j+j]);
      Int_t i_pivot = j;

      for (Int_t i = j+1; i < n; i++) {
         const Int_t off_i = i*n;
         const Double_t mLUij = TMath::Abs(pLU[off_i+j]);

         if (mLUij > max) {
            max = mLUij;
            i_pivot = i;
         }
      }

      if (i_pivot != j) {
         const Int_t off_ipov = i_pivot*n;
         for (Int_t k = 0; k < n; k++ ) {
            const Double_t tmp = pLU[off_ipov+k];
            pLU[off_ipov+k] = pLU[off_j+k];
            pLU[off_j+k]    = tmp;
         }
         sign = -sign;
      }
      index[j] = i_pivot;

      const Double_t mLUjj = pLU[off_j+j];

      if (mLUjj != 0.0) {
         if (TMath::Abs(mLUjj) < tol)
            nrZeros++;
         for (Int_t i = j+1; i < n; i++) {
            const Int_t off_i = i*n;
            const Double_t mLUij = pLU[off_i+j]/mLUjj;
            pLU[off_i+j] = mLUij;

            for (Int_t k = j+1; k < n; k++) {
               const Double_t mLUik = pLU[off_i+k];
               const Double_t mLUjk = pLU[off_j+k];
               pLU[off_i+k] = mLUik-mLUij*mLUjk;
            }
         }
      } else {
         //::Error("TDecompLU::DecomposeLUGauss","matrix is singular");
         return kFALSE;
      }
   }

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate matrix inversion through in place forward/backward substitution

Bool_t TDecompLU::InvertLU(TMatrixD &lu,Double_t tol,Double_t *det)
{
   if (det)
      *det = 0.0;

   if (lu.GetNrows() != lu.GetNcols() || lu.GetRowLwb() != lu.GetColLwb()) {
      //::Error("TDecompLU::InvertLU","matrix should be square");
      return kFALSE;
   }

   const Int_t     n   = lu.GetNcols();
   Double_t *pLU = lu.GetMatrixArray();

   Int_t worki[kWorkMax];
   Bool_t isAllocatedI = kFALSE;
   Int_t *index = worki;
   if (n > kWorkMax) {
      isAllocatedI = kTRUE;
      index = new Int_t[n];
   }

   Double_t sign = 1.0;
   Int_t nrZeros = 0;
   if (!DecomposeLUCrout(lu,index,sign,tol,nrZeros) || nrZeros > 0) {
      if (isAllocatedI)
         delete [] index;
      //::Error("TDecompLU::InvertLU","matrix is singular, %d diag elements < tolerance of %.4e",nrZeros,tol);
      return kFALSE;
   }

   if (det) {
      Double_t d1;
      Double_t d2;
      const TVectorD diagv = TMatrixDDiag_const(lu);
      DiagProd(diagv,tol,d1,d2);
      d1 *= sign;
      *det = d1*TMath::Power(2.0,d2);
   }

   //  Form inv(U).

   Int_t j;

   for (j = 0; j < n; j++) {
      const Int_t off_j = j*n;

      pLU[off_j+j] = 1./pLU[off_j+j];
      const Double_t mLU_jj = -pLU[off_j+j];

//    Compute elements 0:j-1 of j-th column.

      Double_t *pX = pLU+j;
      Int_t k;
      for (k = 0; k <= j-1; k++) {
         const Int_t off_k = k*n;
         if ( pX[off_k] != 0.0 ) {
            const Double_t tmp = pX[off_k];
            for (Int_t i = 0; i <= k-1; i++) {
               const Int_t off_i = i*n;
               pX[off_i] += tmp*pLU[off_i+k];
            }
            pX[off_k] *= pLU[off_k+k];
         }
      }
      for (k = 0; k <= j-1; k++) {
         const Int_t off_k = k*n;
         pX[off_k] *= mLU_jj;
      }
   }

   // Solve the equation inv(A)*L = inv(U) for inv(A).

   Double_t workd[kWorkMax];
   Bool_t isAllocatedD = kFALSE;
   Double_t *pWorkd = workd;
   if (n > kWorkMax) {
      isAllocatedD = kTRUE;
      pWorkd = new Double_t[n];
   }

   for (j = n-1; j >= 0; j--) {

      // Copy current column j of L to WORK and replace with zeros.
      for (Int_t i = j+1; i < n; i++) {
         const Int_t off_i = i*n;
         pWorkd[i] = pLU[off_i+j];
         pLU[off_i+j] = 0.0;
      }

      // Compute current column of inv(A).

      if (j < n-1) {
         const Double_t *mp = pLU+j+1;  // Matrix row ptr
         Double_t *tp = pLU+j;          // Target vector ptr

         for (Int_t irow = 0; irow < n; irow++) {
            Double_t sum = 0.;
            const Double_t *sp = pWorkd+j+1; // Source vector ptr
            for (Int_t icol = 0; icol < n-1-j ; icol++)
               sum += *mp++ * *sp++;
            *tp = -sum + *tp;
            mp += j+1;
            tp += n;
         }
      }
   }

   if (isAllocatedD)
      delete [] pWorkd;

   // Apply column interchanges.
   for (j = n-1; j >= 0; j--) {
      const Int_t jperm = index[j];
      if (jperm != j) {
         for (Int_t i = 0; i < n; i++) {
            const Int_t off_i = i*n;
            const Double_t tmp = pLU[off_i+jperm];
            pLU[off_i+jperm] = pLU[off_i+j];
            pLU[off_i+j]     = tmp;
         }
      }
   }

   if (isAllocatedI)
      delete [] index;

   return kTRUE;
}

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TDecompBase
    \ingroup Matrix

 Decomposition Base class

 This class forms the base for all the decompositions methods in the
 linear algebra package .
 It or its derived classes have installed the methods to solve
 equations,invert matrices and calculate determinants while monitoring
 the accuracy.

 Each derived class has always the following methods available:

 #### Condition() :
   In an iterative scheme the condition number for matrix inversion is
   calculated . This number is of interest for estimating the accuracy
   of x in the equation Ax=b
   For example:
     A is a (10x10) Hilbert matrix which looks deceivingly innocent
     and simple, A(i,j) = 1/(i+j+1)
     b(i) = Sum_j A(i,j), so a sum of a row in A

     the solution is x(i) = 1. i=0,.,9

   However,
~~~
     TMatrixD m....; TVectorD b.....
     TDecompLU lu(m); lu.SetTol(1.0e-12); lu.Solve(b); b.Print()
~~~
   gives,

~~~
   {1.000,1.000,1.000,1.000,0.998,1.000,0.993,1.001,0.996,1.000}
~~~

   Looking at the condition number, this is in line with expected the
   accuracy . The condition number is 3.957e+12 . As a simple rule of
   thumb, a condition number of 1.0e+n means that you lose up to n
   digits of accuracy in a solution . Since doubles are stored with 15
   digits, we can expect the accuracy to be as small as 3 digits .

 #### Det(Double_t &d1,Double_t &d2)
   The determinant is d1*TMath::Power(2.,d2)
   Expressing the determinant this way makes under/over-flow very
   unlikely .

 #### Decompose()
   Here the actually decomposition is performed . One can change the
   matrix A after the decomposition constructor has been called
   without effecting the decomposition result

 #### Solve(TVectorD &b)
  Solve A x = b . x is supplied through the argument and replaced with
  the solution .

 #### TransSolve(TVectorD &b)
  Solve A^T x = b . x is supplied through the argument and replaced
  with the solution .

 #### MultiSolve(TMatrixD    &B)
  Solve A X = B . where X and are now matrices . X is supplied through
  the argument and replaced with the solution .

 #### Invert(TMatrixD &inv)
  This is of course just a call to MultiSolve with as input argument
  the unit matrix . Note that for a matrix a(m,n) with m > n  a
  pseudo-inverse is calculated .

 ### Tolerances and Scaling

 The tolerance parameter (which is a member of this base class) plays
 a crucial role in all operations of the decomposition classes . It
 gives the user a powerful tool to monitor and steer the operations
 Its default value is sqrt(epsilon) where 1+epsilon = 1

 If you do not want to be bothered by the following considerations,
 like in most other linear algebra packages, just set the tolerance
 with SetTol to an arbitrary small number .

 The tolerance number is used by each decomposition method to decide
 whether the matrix is near singular, except of course SVD which can
 handle singular matrices .
 For each decomposition this will be checked in a different way; in LU
 the matrix is considered singular when, at some point in the
 decomposition, a diagonal element < fTol . Therefore, we had to set in
 the example above of the (10x10) Hilbert, which is near singular, the
 tolerance on 10e-12 . (The fact that we have to set the tolerance <
 sqrt(epsilon) is a clear indication that we are losing precision .)

 If the matrix is flagged as being singular, operations with the
 decomposition will fail and will return matrices/vectors that are
 invalid .

 The observant reader will notice that by scaling the complete matrix
 by some small number the decomposition will detect a singular matrix .
 In this case the user will have to reduce the tolerance number by this
 factor . (For CPU time saving we decided not to make this an automatic
 procedure) .

 Code for this could look as follows:
~~~
 const Double_t max_abs = Abs(a).Max();
 const Double_t scale = TMath::Min(max_abs,1.);
 a.SetTol(a.GetTol()*scale);
~~~

 For usage examples see $ROOTSYS/test/stressLinear.cxx
*/

//#include "TDecompBase.h"
//#include "TMath.h"
//#include "TError.h"

ClassImp(TDecompBase);

////////////////////////////////////////////////////////////////////////////////
/// Default constructor

TDecompBase::TDecompBase()
{
   fTol       = std::numeric_limits<double>::epsilon();
   fDet1      = 0;
   fDet2      = 0;
   fCondition = -1.0;
   fRowLwb    = 0;
   fColLwb    = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

TDecompBase::TDecompBase(const TDecompBase &another) : TObject(another)
{
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////

Int_t TDecompBase::Hager(Double_t &est,Int_t iter)
{
// Estimates lower bound for norm1 of inverse of A. Returns norm
// estimate in est.  iter sets the maximum number of iterations to be used.
// The return value indicates the number of iterations remaining on exit from
// loop, hence if this is non-zero the processed "converged".
// This routine uses Hager's Convex Optimisation Algorithm.
// See Applied Numerical Linear Algebra, p139 & SIAM J Sci Stat Comp 1984 pp 311-16

   est = -1.0;

   const TMatrixDBase &m = GetDecompMatrix();
   if (!m.IsValid())
      return iter;

   const Int_t n = m.GetNrows();

   TVectorD b(n); TVectorD y(n); TVectorD z(n);
   b = Double_t(1.0/n);
   Double_t inv_norm1 = 0.0;
   Bool_t stop = kFALSE;
   do {
      y = b;
      if (!Solve(y))
         return iter;
      const Double_t ynorm1 = y.Norm1();
      if ( ynorm1 <= inv_norm1 ) {
         stop = kTRUE;
      } else {
         inv_norm1 = ynorm1;
         Int_t i;
         for (i = 0; i < n; i++)
            z(i) = ( y(i) >= 0.0 ? 1.0 : -1.0 );
         if (!TransSolve(z))
            return iter;
         Int_t imax = 0;
         Double_t maxz = TMath::Abs(z(0));
         for (i = 1; i < n; i++) {
            const Double_t absz = TMath::Abs(z(i));
            if ( absz > maxz ) {
               maxz = absz;
               imax = i;
            }
         }
         stop = (maxz <= b*z);
         if (!stop) {
            b = 0.0;
            b(imax) = 1.0;
         }
      }
      iter--;
   } while (!stop && iter);
   est = inv_norm1;

   return iter;
}

////////////////////////////////////////////////////////////////////////////////

void TDecompBase::DiagProd(const TVectorD &diag,Double_t tol,Double_t &d1,Double_t &d2)
{
// Returns product of matrix diagonal elements in d1 and d2. d1 is a mantissa and d2
// an exponent for powers of 2. If matrix is in diagonal or triangular-matrix form this
// will be the determinant.
// Based on Bowler, Martin, Peters and Wilkinson in HACLA

   const Double_t zero      = 0.0;
   const Double_t one       = 1.0;
   const Double_t four      = 4.0;
   const Double_t sixteen   = 16.0;
   const Double_t sixteenth = 0.0625;

   const Int_t n = diag.GetNrows();

   Double_t t1 = 1.0;
   Double_t t2 = 0.0;
   Int_t niter2 =0;
   Int_t niter3 =0;
   for (Int_t i = 0; (((i < n) && (t1 !=zero ))); i++) {
      if (TMath::Abs(diag(i)) > tol) {
         t1 *= (Double_t) diag(i);
         while ( TMath::Abs(t1) < one) {
            t1 *= sixteenth;
            t2 += four;
            niter2++;
            if ( niter2>100) break;
         }
         while ( TMath::Abs(t1) < sixteenth)  {
            t1 *= sixteen;
            t2 -= four;
            niter3++;
            if (niter3>100) break;
         }
      } else {
         t1 = zero;
         t2 = zero;
      }
   }
   d1 = t1;
   d2 = t2;

   return;
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix condition number

Double_t TDecompBase::Condition()
{
   if ( !TestBit(kCondition) ) {
      fCondition = -1;
      if (TestBit(kSingular))
         return fCondition;
      if ( !TestBit(kDecomposed) ) {
         if (!Decompose())
            return fCondition;
      }
      Double_t invNorm;
      if (Hager(invNorm))
         fCondition *= invNorm;
      //else // no convergence in Hager
         //Error("Condition()","Hager procedure did NOT converge");
      SetBit(kCondition);
   }
   return fCondition;
}

////////////////////////////////////////////////////////////////////////////////
/// Solve set of equations with RHS in columns of B

Bool_t TDecompBase::MultiSolve(TMatrixD &B)
{
   const TMatrixDBase &m = GetDecompMatrix();
   //R__ASSERT(m.IsValid() && B.IsValid());

   const Int_t colLwb = B.GetColLwb();
   const Int_t colUpb = B.GetColUpb();
   Bool_t status = kTRUE;
   for (Int_t icol = colLwb; icol <= colUpb && status; icol++) {
      TMatrixDColumn b(B,icol);
      status &= Solve(b);
   }

   return status;
}

////////////////////////////////////////////////////////////////////////////////
/// Matrix determinant det = d1*TMath::Power(2.,d2)

void TDecompBase::Det(Double_t &d1,Double_t &d2)
{
   if ( !TestBit(kDetermined) ) {
      if ( !TestBit(kDecomposed) )
         Decompose();
      if (TestBit(kSingular) ) {
         fDet1 = 0.0;
         fDet2 = 0.0;
      } else {
         const TMatrixDBase &m = GetDecompMatrix();
         //R__ASSERT(m.IsValid());
         TVectorD diagv(m.GetNrows());
         for (Int_t i = 0; i < diagv.GetNrows(); i++)
            diagv(i) = m(i,i);
         DiagProd(diagv,fTol,fDet1,fDet2);
      }
      SetBit(kDetermined);
   }
   d1 = fDet1;
   d2 = fDet2;
}

////////////////////////////////////////////////////////////////////////////////
/// Print class members

void TDecompBase::Print(Option_t * /*opt*/) const
{
   printf("fTol       = %.4e\n",fTol);
   printf("fDet1      = %.4e\n",fDet1);
   printf("fDet2      = %.4e\n",fDet2);
   printf("fCondition = %.4e\n",fCondition);
   printf("fRowLwb    = %d\n",fRowLwb);
   printf("fColLwb    = %d\n",fColLwb);
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

TDecompBase &TDecompBase::operator=(const TDecompBase &source)
{
   if (this != &source) {
      //TObject::operator=(source);
      fTol       = source.fTol;
      fDet1      = source.fDet1;
      fDet2      = source.fDet2;
      fCondition = source.fCondition;
      fRowLwb    = source.fRowLwb;
      fColLwb    = source.fColLwb;
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Define a Householder-transformation through the parameters up and b .

Bool_t DefHouseHolder(const TVectorD &vc,Int_t lp,Int_t l,Double_t &up,Double_t &beta,
                      Double_t tol)
{
   const Int_t n = vc.GetNrows();
   const Double_t * const vp = vc.GetMatrixArray();

   Double_t c = TMath::Abs(vp[lp]);
   Int_t i;
   for (i = l; i < n; i++)
      c = TMath::Max(TMath::Abs(vp[i]),c);

   up   = 0.0;
   beta = 0.0;
   if (c <= tol) {
//     Warning("DefHouseHolder","max vector=%.4e < %.4e",c,tol);
      return kFALSE;
   }

   Double_t sd = vp[lp]/c; sd *= sd;
   for (i = l; i < n; i++) {
      const Double_t tmp = vp[i]/c;
      sd += tmp*tmp;
   }

   Double_t vpprim = c*TMath::Sqrt(sd);
   if (vp[lp] > 0.) vpprim = -vpprim;
   up = vp[lp]-vpprim;
   beta = 1./(vpprim*up);

   return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Apply Householder-transformation.

void ApplyHouseHolder(const TVectorD &vc,Double_t up,Double_t beta,
                      Int_t lp,Int_t l,TMatrixDRow &cr)
{
   const Int_t nv = vc.GetNrows();
   const Int_t nc = (cr.GetMatrix())->GetNcols();

   if (nv > nc) {
      //Error("ApplyHouseHolder(const TVectorD &,..,TMatrixDRow &)","matrix row too short");
      return;
   }

   const Int_t inc_c = cr.GetInc();
   const Double_t * const vp = vc.GetMatrixArray();
         Double_t *       cp = cr.GetPtr();

   Double_t s = cp[lp*inc_c]*up;
   Int_t i;
   for (i = l; i < nv; i++)
      s += cp[i*inc_c]*vp[i];

   s = s*beta;
   cp[lp*inc_c] += s*up;
   for (i = l; i < nv; i++)
      cp[i*inc_c] += s*vp[i];
}

////////////////////////////////////////////////////////////////////////////////
/// Apply Householder-transformation.

void ApplyHouseHolder(const TVectorD &vc,Double_t up,Double_t beta,
                      Int_t lp,Int_t l,TMatrixDColumn &cc)
{
   const Int_t nv = vc.GetNrows();
   const Int_t nc = (cc.GetMatrix())->GetNrows();

   if (nv > nc) {
      //Error("ApplyHouseHolder(const TVectorD &,..,TMatrixDRow &)","matrix column too short");
      return;
   }

   const Int_t inc_c = cc.GetInc();
   const Double_t * const vp = vc.GetMatrixArray();
         Double_t *       cp = cc.GetPtr();

   Double_t s = cp[lp*inc_c]*up;
   Int_t i;
   for (i = l; i < nv; i++)
      s += cp[i*inc_c]*vp[i];

   s = s*beta;
   cp[lp*inc_c] += s*up;
   for (i = l; i < nv; i++)
      cp[i*inc_c] += s*vp[i];
}

////////////////////////////////////////////////////////////////////////////////
///  Apply Householder-transformation.

void ApplyHouseHolder(const TVectorD &vc,Double_t up,Double_t beta,
                      Int_t lp,Int_t l,TVectorD &cv)
{
   const Int_t nv = vc.GetNrows();
   const Int_t nc = cv.GetNrows();

   if (nv > nc) {
      //Error("ApplyHouseHolder(const TVectorD &,..,TVectorD &)","vector too short");
      return;
   }

   const Double_t * const vp = vc.GetMatrixArray();
         Double_t *       cp = cv.GetMatrixArray();

   Double_t s = cp[lp]*up;
   Int_t i;
   for (i = l; i < nv; i++)
      s += cp[i]*vp[i];

   s = s*beta;
   cp[lp] += s*up;
   for (i = l; i < nv; i++)
      cp[i] += s*vp[i];
}

////////////////////////////////////////////////////////////////////////////////
/// Defines a Givens-rotation by calculating 2 rotation parameters c and s.
/// The rotation is defined with the vector components v1 and v2.

void DefGivens(Double_t v1,Double_t v2,Double_t &c,Double_t &s)
{
   const Double_t a1 = TMath::Abs(v1);
   const Double_t a2 = TMath::Abs(v2);
   if (a1 > a2) {
      const Double_t w = v2/v1;
      const Double_t q = TMath::Hypot(1.,w);
      c = 1./q;
      if (v1 < 0.) c = -c;
      s = c*w;
   } else {
      if (v2 != 0) {
         const Double_t w = v1/v2;
         const Double_t q = TMath::Hypot(1.,w);
         s = 1./q;
         if (v2 < 0.) s = -s;
         c = s*w;
      } else {
         c = 1.;
         s = 0.;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Define and apply a Givens-rotation by calculating 2 rotation
/// parameters c and s. The rotation is defined with and applied to the vector
/// components v1 and v2.

void DefAplGivens(Double_t &v1,Double_t &v2,Double_t &c,Double_t &s)
{
   const Double_t a1 = TMath::Abs(v1);
   const Double_t a2 = TMath::Abs(v2);
   if (a1 > a2) {
      const Double_t w = v2/v1;
      const Double_t q = TMath::Hypot(1.,w);
      c = 1./q;
      if (v1 < 0.) c = -c;
      s  = c*w;
      v1 = a1*q;
      v2 = 0.;
   } else {
      if (v2 != 0) {
         const Double_t w = v1/v2;
         const Double_t q = TMath::Hypot(1.,w);
         s = 1./q;
         if (v2 < 0.) s = -s;
         c  = s*w;
         v1 = a2*q;
         v2 = 0.;
      } else {
         c = 1.;
         s = 0.;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Apply a Givens transformation as defined by c and s to the vector components
/// v1 and v2 .

void ApplyGivens(Double_t &z1,Double_t &z2,Double_t c,Double_t s)
{
   const Double_t w = z1*c+z2*s;
   z2 = -z1*s+z2*c;
   z1 = w;
}

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixDEigen
    \ingroup Matrix

 TMatrixDEigen

 Eigenvalues and eigenvectors of a real matrix.

 If A is not symmetric, then the eigenvalue matrix D is block
 diagonal with the real eigenvalues in 1-by-1 blocks and any complex
 eigenvalues, a + i*b, in 2-by-2 blocks, [a, b; -b, a].  That is, if
 the complex eigenvalues look like

~~~
     u + iv     .        .          .      .    .
       .      u - iv     .          .      .    .
       .        .      a + ib       .      .    .
       .        .        .        a - ib   .    .
       .        .        .          .      x    .
       .        .        .          .      .    y
~~~

 then D looks like

~~~
       u        v        .          .      .    .
      -v        u        .          .      .    .
       .        .        a          b      .    .
       .        .       -b          a      .    .
       .        .        .          .      x    .
       .        .        .          .      .    y
~~~

 This keeps V a real matrix in both symmetric and non-symmetric
 cases, and A*V = V*D.

*/

//#include "TMatrixDEigen.h"
//#include "TMath.h"

ClassImp(TMatrixDEigen);

////////////////////////////////////////////////////////////////////////////////
/// Constructor for eigen-problem of matrix A .

TMatrixDEigen::TMatrixDEigen(const TMatrixD &a)
{
   //R__ASSERT(a.IsValid());

   const Int_t nRows  = a.GetNrows();
   const Int_t nCols  = a.GetNcols();
   const Int_t rowLwb = a.GetRowLwb();
   const Int_t colLwb = a.GetColLwb();

   if (nRows != nCols || rowLwb != colLwb)
   {
      //Error("TMatrixDEigen(TMatrixD &)","matrix should be square");
      return;
   }

   const Int_t rowUpb = rowLwb+nRows-1;
   fEigenVectors.ResizeTo(rowLwb,rowUpb,rowLwb,rowUpb);
   fEigenValuesRe.ResizeTo(rowLwb,rowUpb);
   fEigenValuesIm.ResizeTo(rowLwb,rowUpb);

   TVectorD ortho;
   Double_t work[kWorkMax];
   if (nRows > kWorkMax) ortho.ResizeTo(nRows);
   else                  ortho.Use(nRows,work);

   TMatrixD mH = a;

   // Reduce to Hessenberg form.
   MakeHessenBerg(fEigenVectors,ortho,mH);

   // Reduce Hessenberg to real Schur form.
   MakeSchurr(fEigenVectors,fEigenValuesRe,fEigenValuesIm,mH);

   // Sort eigenvalues and corresponding vectors in descending order of Re^2+Im^2
   // of the complex eigenvalues .
   Sort(fEigenVectors,fEigenValuesRe,fEigenValuesIm);
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

TMatrixDEigen::TMatrixDEigen(const TMatrixDEigen &another)
{
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// Nonsymmetric reduction to Hessenberg form.
/// This is derived from the Algol procedures orthes and ortran, by Martin and Wilkinson,
/// Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
/// Fortran subroutines in EISPACK.

void TMatrixDEigen::MakeHessenBerg(TMatrixD &v,TVectorD &ortho,TMatrixD &H)
{
   Double_t *pV = v.GetMatrixArray();
   Double_t *pO = ortho.GetMatrixArray();
   Double_t *pH = H.GetMatrixArray();

   const UInt_t n = v.GetNrows();

   const UInt_t low  = 0;
   const UInt_t high = n-1;

   UInt_t i,j,m;
   for (m = low+1; m <= high-1; m++) {
      const UInt_t off_m = m*n;

      // Scale column.

      Double_t scale = 0.0;
      for (i = m; i <= high; i++) {
         const UInt_t off_i = i*n;
         scale = scale + TMath::Abs(pH[off_i+m-1]);
      }
      if (scale != 0.0) {

         // Compute Householder transformation.

         Double_t h = 0.0;
         for (i = high; i >= m; i--) {
            const UInt_t off_i = i*n;
            pO[i] = pH[off_i+m-1]/scale;
            h += pO[i]*pO[i];
         }
         Double_t g = TMath::Sqrt(h);
         if (pO[m] > 0)
            g = -g;
         h = h-pO[m]*g;
         pO[m] = pO[m]-g;

         // Apply Householder similarity transformation
         // H = (I-u*u'/h)*H*(I-u*u')/h)

         for (j = m; j < n; j++) {
            Double_t f = 0.0;
            for (i = high; i >= m; i--) {
               const UInt_t off_i = i*n;
               f += pO[i]*pH[off_i+j];
            }
            f = f/h;
            for (i = m; i <= high; i++) {
               const UInt_t off_i = i*n;
               pH[off_i+j] -= f*pO[i];
            }
         }

         for (i = 0; i <= high; i++) {
            const UInt_t off_i = i*n;
            Double_t f = 0.0;
            for (j = high; j >= m; j--)
               f += pO[j]*pH[off_i+j];
            f = f/h;
            for (j = m; j <= high; j++)
               pH[off_i+j] -= f*pO[j];
         }
         pO[m] = scale*pO[m];
         pH[off_m+m-1] = scale*g;
      }
   }

   // Accumulate transformations (Algol's ortran).

   for (i = 0; i < n; i++) {
      const UInt_t off_i = i*n;
      for (j = 0; j < n; j++)
         pV[off_i+j] = (i == j ? 1.0 : 0.0);
   }

   for (m = high-1; m >= low+1; m--) {
      const UInt_t off_m = m*n;
      if (pH[off_m+m-1] != 0.0) {
         for (i = m+1; i <= high; i++) {
            const UInt_t off_i = i*n;
            pO[i] = pH[off_i+m-1];
         }
         for (j = m; j <= high; j++) {
            Double_t g = 0.0;
            for (i = m; i <= high; i++) {
               const UInt_t off_i = i*n;
               g += pO[i]*pV[off_i+j];
            }
            // Double division avoids possible underflow
            g = (g/pO[m])/pH[off_m+m-1];
            for (i = m; i <= high; i++) {
               const UInt_t off_i = i*n;
               pV[off_i+j] += g*pO[i];
            }
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Complex scalar division.

static Double_t gCdivr, gCdivi;
static void cdiv(Double_t xr,Double_t xi,Double_t yr,Double_t yi) {
   Double_t r,d;
   if (TMath::Abs(yr) > TMath::Abs(yi)) {
      r = yi/yr;
      d = yr+r*yi;
      gCdivr = (xr+r*xi)/d;
      gCdivi = (xi-r*xr)/d;
   } else {
      r = yr/yi;
      d = yi+r*yr;
      gCdivr = (r*xr+xi)/d;
      gCdivi = (r*xi-xr)/d;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Nonsymmetric reduction from Hessenberg to real Schur form.
/// This is derived from the Algol procedure hqr2, by Martin and Wilkinson,
/// Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
/// Fortran subroutine in EISPACK.

void TMatrixDEigen::MakeSchurr(TMatrixD &v,TVectorD &d,TVectorD &e,TMatrixD &H)
{
   // Initialize

   const Int_t nn = v.GetNrows();
         Int_t n = nn-1;
   const Int_t low = 0;
   const Int_t high = nn-1;
   const Double_t eps = TMath::Power(2.0,-52.0);
   Double_t exshift = 0.0;
   Double_t p=0,q=0,r=0,s=0,z=0,t,w,x,y;

   Double_t *pV = v.GetMatrixArray();
   Double_t *pD = d.GetMatrixArray();
   Double_t *pE = e.GetMatrixArray();
   Double_t *pH = H.GetMatrixArray();

   // Store roots isolated by balanc and compute matrix norm

   Double_t norm = 0.0;
   Int_t i,j,k;
   for (i = 0; i < nn; i++) {
      const Int_t off_i = i*nn;
      if ((i < low) || (i > high)) {
         pD[i] = pH[off_i+i];
         pE[i] = 0.0;
      }
      for (j = TMath::Max(i-1,0); j < nn; j++)
         norm += TMath::Abs(pH[off_i+j]);
   }

   // Outer loop over eigenvalue index

   Int_t iter = 0;
   while (n >= low) {
      const Int_t off_n  = n*nn;
      const Int_t off_n1 = (n-1)*nn;

      // Look for single small sub-diagonal element

      Int_t l = n;
      while (l > low) {
         const Int_t off_l1 = (l-1)*nn;
         const Int_t off_l  = l*nn;
         s = TMath::Abs(pH[off_l1+l-1])+TMath::Abs(pH[off_l+l]);
         if (s == 0.0)
            s = norm;
         if (TMath::Abs(pH[off_l+l-1]) < eps*s)
            break;
         l--;
      }

      // Check for convergence
      // One root found

      if (l == n) {
         pH[off_n+n] = pH[off_n+n]+exshift;
         pD[n] = pH[off_n+n];
         pE[n] = 0.0;
         n--;
         iter = 0;

         // Two roots found

      } else if (l == n-1) {
         w = pH[off_n+n-1]*pH[off_n1+n];
         p = (pH[off_n1+n-1]-pH[off_n+n])/2.0;
         q = p*p+w;
         z = TMath::Sqrt(TMath::Abs(q));
         pH[off_n+n] = pH[off_n+n]+exshift;
         pH[off_n1+n-1] = pH[off_n1+n-1]+exshift;
         x = pH[off_n+n];

         // Double_t pair

         if (q >= 0) {
            if (p >= 0)
               z = p+z;
            else
               z = p-z;
            pD[n-1] = x+z;
            pD[n] = pD[n-1];
            if (z != 0.0)
               pD[n] = x-w/z;
            pE[n-1] = 0.0;
            pE[n] = 0.0;
            x = pH[off_n+n-1];
            s = TMath::Abs(x)+TMath::Abs(z);
            p = x/s;
            q = z/s;
            r = TMath::Sqrt((p*p)+(q*q));
            p = p/r;
            q = q/r;

            // Row modification

            for (j = n-1; j < nn; j++) {
               z = pH[off_n1+j];
               pH[off_n1+j] = q*z+p*pH[off_n+j];
               pH[off_n+j]  = q*pH[off_n+j]-p*z;
            }

            // Column modification

            for (i = 0; i <= n; i++) {
               const Int_t off_i = i*nn;
               z = pH[off_i+n-1];
               pH[off_i+n-1] = q*z+p*pH[off_i+n];
               pH[off_i+n]  = q*pH[off_i+n]-p*z;
            }

            // Accumulate transformations

            for (i = low; i <= high; i++) {
               const Int_t off_i = i*nn;
               z = pV[off_i+n-1];
               pV[off_i+n-1] = q*z+p*pV[off_i+n];
               pV[off_i+n]   = q*pV[off_i+n]-p*z;
            }

            // Complex pair

         } else {
            pD[n-1] = x+p;
            pD[n] = x+p;
            pE[n-1] = z;
            pE[n] = -z;
         }
         n = n-2;
         iter = 0;

         // No convergence yet

      } else {

         // Form shift

         x = pH[off_n+n];
         y = 0.0;
         w = 0.0;
         if (l < n) {
            y = pH[off_n1+n-1];
            w = pH[off_n+n-1]*pH[off_n1+n];
         }

         // Wilkinson's original ad hoc shift

         if (iter == 10) {
            exshift += x;
            for (i = low; i <= n; i++) {
               const Int_t off_i = i*nn;
               pH[off_i+i] -= x;
            }
            s = TMath::Abs(pH[off_n+n-1])+TMath::Abs(pH[off_n1+n-2]);
            x = y = 0.75*s;
            w = -0.4375*s*s;
         }

         // MATLAB's new ad hoc shift

         if (iter == 30) {
            s = (y-x)/2.0;
            s = s*s+w;
            if (s > 0) {
               s = TMath::Sqrt(s);
               if (y<x)
                  s = -s;
               s = x-w/((y-x)/2.0+s);
               for (i = low; i <= n; i++) {
                  const Int_t off_i = i*nn;
                  pH[off_i+i] -= s;
               }
               exshift += s;
               x = y = w = 0.964;
            }
         }

         if (iter++ == 50) {  // (check iteration count here.)
            //Error("MakeSchurr","too many iterations");
            break;
         }

         // Look for two consecutive small sub-diagonal elements

         Int_t m = n-2;
         while (m >= l) {
            const Int_t off_m   = m*nn;
            const Int_t off_m_1 = (m-1)*nn;
            const Int_t off_m1  = (m+1)*nn;
            const Int_t off_m2  = (m+2)*nn;
            z = pH[off_m+m];
            r = x-z;
            s = y-z;
            p = (r*s-w)/pH[off_m1+m]+pH[off_m+m+1];
            q = pH[off_m1+m+1]-z-r-s;
            r = pH[off_m2+m+1];
            s = TMath::Abs(p)+TMath::Abs(q)+TMath::Abs(r);
            p = p /s;
            q = q/s;
            r = r/s;
            if (m == l)
               break;
            if (TMath::Abs(pH[off_m+m-1])*(TMath::Abs(q)+TMath::Abs(r)) <
               eps*(TMath::Abs(p)*(TMath::Abs(pH[off_m_1+m-1])+TMath::Abs(z)+
               TMath::Abs(pH[off_m1+m+1]))))
               break;
            m--;
         }

         for (i = m+2; i <= n; i++) {
            const Int_t off_i = i*nn;
            pH[off_i+i-2] = 0.0;
            if (i > m+2)
               pH[off_i+i-3] = 0.0;
         }

         // Double QR step involving rows l:n and columns m:n

         for (k = m; k <= n-1; k++) {
            const Int_t off_k  = k*nn;
            const Int_t off_k1 = (k+1)*nn;
            const Int_t off_k2 = (k+2)*nn;
            const Int_t notlast = (k != n-1);
            if (k != m) {
               p = pH[off_k+k-1];
               q = pH[off_k1+k-1];
               r = (notlast ? pH[off_k2+k-1] : 0.0);
               x = TMath::Abs(p)+TMath::Abs(q)+TMath::Abs(r);
               if (x != 0.0) {
                  p = p/x;
                  q = q/x;
                  r = r/x;
               }
            }
            if (x == 0.0)
               break;
            s = TMath::Sqrt(p*p+q*q+r*r);
            if (p < 0) {
               s = -s;
            }
            if (s != 0) {
              if (k != m)
                 pH[off_k+k-1] = -s*x;
              else if (l != m)
                 pH[off_k+k-1] = -pH[off_k+k-1];
              p = p+s;
              x = p/s;
              y = q/s;
              z = r/s;
              q = q/p;
              r = r/p;

              // Row modification

              for (j = k; j < nn; j++) {
                 p = pH[off_k+j]+q*pH[off_k1+j];
                 if (notlast) {
                    p = p+r*pH[off_k2+j];
                    pH[off_k2+j] = pH[off_k2+j]-p*z;
                 }
                 pH[off_k+j]  = pH[off_k+j]-p*x;
                 pH[off_k1+j] = pH[off_k1+j]-p*y;
              }

              // Column modification

              for (i = 0; i <= TMath::Min(n,k+3); i++) {
                 const Int_t off_i = i*nn;
                 p = x*pH[off_i+k]+y*pH[off_i+k+1];
                 if (notlast) {
                    p = p+z*pH[off_i+k+2];
                    pH[off_i+k+2] = pH[off_i+k+2]-p*r;
                 }
                 pH[off_i+k]   = pH[off_i+k]-p;
                 pH[off_i+k+1] = pH[off_i+k+1]-p*q;
              }

              // Accumulate transformations

              for (i = low; i <= high; i++) {
                 const Int_t off_i = i*nn;
                 p = x*pV[off_i+k]+y*pV[off_i+k+1];
                 if (notlast) {
                    p = p+z*pV[off_i+k+2];
                    pV[off_i+k+2] = pV[off_i+k+2]-p*r;
                 }
                 pV[off_i+k]   = pV[off_i+k]-p;
                 pV[off_i+k+1] = pV[off_i+k+1]-p*q;
              }
            }  // (s != 0)
         }  // k loop
      }  // check convergence
   }  // while (n >= low)

   // Backsubstitute to find vectors of upper triangular form

   if (norm == 0.0)
      return;

   for (n = nn-1; n >= 0; n--) {
      p = pD[n];
      q = pE[n];

      // Double_t vector

      const Int_t off_n = n*nn;
      if (q == 0) {
         Int_t l = n;
         pH[off_n+n] = 1.0;
         for (i = n-1; i >= 0; i--) {
            const Int_t off_i  = i*nn;
            const Int_t off_i1 = (i+1)*nn;
            w = pH[off_i+i]-p;
            r = 0.0;
            for (j = l; j <= n; j++) {
               const Int_t off_j = j*nn;
               r = r+pH[off_i+j]*pH[off_j+n];
            }
            if (pE[i] < 0.0) {
               z = w;
               s = r;
            } else {
               l = i;
               if (pE[i] == 0.0) {
                  if (w != 0.0)
                     pH[off_i+n] = -r/w;
                  else
                     pH[off_i+n] = -r/(eps*norm);

                  // Solve real equations

               } else {
                  x = pH[off_i+i+1];
                  y = pH[off_i1+i];
                  q = (pD[i]-p)*(pD[i]-p)+pE[i]*pE[i];
                  t = (x*s-z*r)/q;
                  pH[off_i+n] = t;
                  if (TMath::Abs(x) > TMath::Abs(z))
                     pH[i+1+n] = (-r-w*t)/x;
                  else
                     pH[i+1+n] = (-s-y*t)/z;
               }

               // Overflow control

               t = TMath::Abs(pH[off_i+n]);
               if ((eps*t)*t > 1) {
                  for (j = i; j <= n; j++) {
                     const Int_t off_j = j*nn;
                     pH[off_j+n] = pH[off_j+n]/t;
                  }
               }
            }
         }

         // Complex vector

      } else if (q < 0) {
         Int_t l = n-1;
         const Int_t off_n1 = (n-1)*nn;

         // Last vector component imaginary so matrix is triangular

         if (TMath::Abs(pH[off_n+n-1]) > TMath::Abs(pH[off_n1+n])) {
            pH[off_n1+n-1] = q/pH[off_n+n-1];
            pH[off_n1+n]   = -(pH[off_n+n]-p)/pH[off_n+n-1];
         } else {
            cdiv(0.0,-pH[off_n1+n],pH[off_n1+n-1]-p,q);
            pH[off_n1+n-1] = gCdivr;
            pH[off_n1+n]   = gCdivi;
         }
         pH[off_n+n-1] = 0.0;
         pH[off_n+n]   = 1.0;
         for (i = n-2; i >= 0; i--) {
            const Int_t off_i  = i*nn;
            const Int_t off_i1 = (i+1)*nn;
            Double_t ra = 0.0;
            Double_t sa = 0.0;
            for (j = l; j <= n; j++) {
               const Int_t off_j = j*nn;
               ra += pH[off_i+j]*pH[off_j+n-1];
               sa += pH[off_i+j]*pH[off_j+n];
            }
            w = pH[off_i+i]-p;

            if (pE[i] < 0.0) {
               z = w;
               r = ra;
               s = sa;
            } else {
               l = i;
               if (pE[i] == 0) {
                  cdiv(-ra,-sa,w,q);
                  pH[off_i+n-1] = gCdivr;
                  pH[off_i+n]   = gCdivi;
               } else {

                  // Solve complex equations

                  x = pH[off_i+i+1];
                  y = pH[off_i1+i];
                  Double_t vr = (pD[i]-p)*(pD[i]-p)+pE[i]*pE[i]-q*q;
                  Double_t vi = (pD[i]-p)*2.0*q;
                  if ((vr == 0.0) && (vi == 0.0)) {
                     vr = eps*norm*(TMath::Abs(w)+TMath::Abs(q)+
                          TMath::Abs(x)+TMath::Abs(y)+TMath::Abs(z));
                  }
                  cdiv(x*r-z*ra+q*sa,x*s-z*sa-q*ra,vr,vi);
                  pH[off_i+n-1] = gCdivr;
                  pH[off_i+n]   = gCdivi;
                  if (TMath::Abs(x) > (TMath::Abs(z)+TMath::Abs(q))) {
                     pH[off_i1+n-1] = (-ra-w*pH[off_i+n-1]+q*pH[off_i+n])/x;
                     pH[off_i1+n]   = (-sa-w*pH[off_i+n]-q*pH[off_i+n-1])/x;
                  } else {
                     cdiv(-r-y*pH[off_i+n-1],-s-y*pH[off_i+n],z,q);
                     pH[off_i1+n-1] = gCdivr;
                     pH[off_i1+n]   = gCdivi;
                  }
               }

               // Overflow control

               t = TMath::Max(TMath::Abs(pH[off_i+n-1]),TMath::Abs(pH[off_i+n]));
               if ((eps*t)*t > 1) {
                  for (j = i; j <= n; j++) {
                     const Int_t off_j = j*nn;
                     pH[off_j+n-1] = pH[off_j+n-1]/t;
                     pH[off_j+n]   = pH[off_j+n]/t;
                  }
               }
            }
         }
      }
   }

   // Vectors of isolated roots

   for (i = 0; i < nn; i++) {
      if (i < low || i > high) {
         const Int_t off_i = i*nn;
         for (j = i; j < nn; j++)
            pV[off_i+j] = pH[off_i+j];
      }
   }

   // Back transformation to get eigenvectors of original matrix

   for (j = nn-1; j >= low; j--) {
      for (i = low; i <= high; i++) {
         const Int_t off_i = i*nn;
         z = 0.0;
         for (k = low; k <= TMath::Min(j,high); k++) {
            const Int_t off_k = k*nn;
            z = z+pV[off_i+k]*pH[off_k+j];
         }
         pV[off_i+j] = z;
      }
   }

}

////////////////////////////////////////////////////////////////////////////////
/// Sort eigenvalues and corresponding vectors in descending order of Re^2+Im^2
/// of the complex eigenvalues .

void TMatrixDEigen::Sort(TMatrixD &v,TVectorD &d,TVectorD &e)
{
   // Sort eigenvalues and corresponding vectors.
   Double_t *pV = v.GetMatrixArray();
   Double_t *pD = d.GetMatrixArray();
   Double_t *pE = e.GetMatrixArray();

   const Int_t n = v.GetNrows();

   for (Int_t i = 0; i < n-1; i++) {
      Int_t k = i;
      Double_t norm = pD[i]*pD[i]+pE[i]*pE[i];
      Int_t j;
      for (j = i+1; j < n; j++) {
         const Double_t norm_new = pD[j]*pD[j]+pE[j]*pE[j];
         if (norm_new > norm) {
            k = j;
            norm = norm_new;
         }
      }
      if (k != i) {
         Double_t tmp;
         tmp   = pD[k];
         pD[k] = pD[i];
         pD[i] = tmp;
         tmp   = pE[k];
         pE[k] = pE[i];
         pE[i] = tmp;
         for (j = 0; j < n; j++) {
            const Int_t off_j = j*n;
            tmp = pV[off_j+i];
            pV[off_j+i] = pV[off_j+k];
            pV[off_j+k] = tmp;
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

TMatrixDEigen &TMatrixDEigen::operator=(const TMatrixDEigen &source)
{
   if (this != &source) {
      fEigenVectors.ResizeTo(source.fEigenVectors);
      fEigenValuesRe.ResizeTo(source.fEigenValuesRe);
      fEigenValuesIm.ResizeTo(source.fEigenValuesIm);
   }
   return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Computes the block diagonal eigenvalue matrix.
/// If the original matrix A is not symmetric, then the eigenvalue
/// matrix D is block diagonal with the real eigenvalues in 1-by-1
/// blocks and any complex eigenvalues,
///    a + i*b, in 2-by-2 blocks, [a, b; -b, a].
///  That is, if the complex eigenvalues look like
///
/// ~~~
///     u + iv     .        .          .      .    .
///       .      u - iv     .          .      .    .
///       .        .      a + ib       .      .    .
///       .        .        .        a - ib   .    .
///       .        .        .          .      x    .
///       .        .        .          .      .    y
/// ~~~
///
/// then D looks like
///
/// ~~~
///     u        v        .          .      .    .
///    -v        u        .          .      .    .
///     .        .        a          b      .    .
///     .        .       -b          a      .    .
///     .        .        .          .      x    .
///     .        .        .          .      .    y
/// ~~~
///
/// This keeps V a real matrix in both symmetric and non-symmetric
/// cases, and A*V = V*D.
///
/// Indexing:
///  If matrix A has the index/shape (rowLwb,rowUpb,rowLwb,rowUpb)
///  each eigen-vector must have the shape (rowLwb,rowUpb) .
///  For convenience, the column index of the eigen-vector matrix
///  also runs from rowLwb to rowUpb so that the returned matrix
///  has also index/shape (rowLwb,rowUpb,rowLwb,rowUpb) .
///

const TMatrixD TMatrixDEigen::GetEigenValues() const
{
   const Int_t nrows  = fEigenVectors.GetNrows();
   const Int_t rowLwb = fEigenVectors.GetRowLwb();
   const Int_t rowUpb = rowLwb+nrows-1;

   TMatrixD mD(rowLwb,rowUpb,rowLwb,rowUpb);

   Double_t *pD = mD.GetMatrixArray();
   const Double_t * const pd = fEigenValuesRe.GetMatrixArray();
   const Double_t * const pe = fEigenValuesIm.GetMatrixArray();

   for (Int_t i = 0; i < nrows; i++) {
      const Int_t off_i = i*nrows;
      for (Int_t j = 0; j < nrows; j++)
         pD[off_i+j] = 0.0;
      pD[off_i+i] = pd[i];
      if (pe[i] > 0) {
         pD[off_i+i+1] = pe[i];
      } else if (pe[i] < 0) {
         pD[off_i+i-1] = pe[i];
      }
   }

   return mD;
}

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

/** \class TMatrixDSymEigen
    \ingroup Matrix

 TMatrixDSymEigen

 Eigenvalues and eigenvectors of a real symmetric matrix.

 If A is symmetric, then A = V*D*V' where the eigenvalue matrix D is
 diagonal and the eigenvector matrix V is orthogonal. That is, the
 diagonal values of D are the eigenvalues, and V*V' = I, where I is
 the identity matrix.  The columns of V represent the eigenvectors in
 the sense that A*V = V*D.
*/

//#include "TMatrixDSymEigen.h"
//#include "TMath.h"

ClassImp(TMatrixDSymEigen);

////////////////////////////////////////////////////////////////////////////////
/// Constructor for eigen-problem of symmetric matrix A .

TMatrixDSymEigen::TMatrixDSymEigen(const TMatrixDSym &a)
{
   //R__ASSERT(a.IsValid());

   const Int_t nRows  = a.GetNrows();
   const Int_t rowLwb = a.GetRowLwb();

   fEigenValues.ResizeTo(rowLwb,rowLwb+nRows-1);
   fEigenVectors.ResizeTo(a);

   fEigenVectors = a;

   TVectorD offDiag;
   Double_t work[kWorkMax];
   if (nRows > kWorkMax) offDiag.ResizeTo(nRows);
   else                  offDiag.Use(nRows,work);

   // Tridiagonalize matrix
   MakeTridiagonal(fEigenVectors,fEigenValues,offDiag);

   // Make eigenvectors and -values
   MakeEigenVectors(fEigenVectors,fEigenValues,offDiag);
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

TMatrixDSymEigen::TMatrixDSymEigen(const TMatrixDSymEigen &another)
{
   *this = another;
}

////////////////////////////////////////////////////////////////////////////////
/// This is derived from the Algol procedures tred2 by Bowdler, Martin, Reinsch, and
/// Wilkinson, Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
/// Fortran subroutine in EISPACK.

void TMatrixDSymEigen::MakeTridiagonal(TMatrixD &v,TVectorD &d,TVectorD &e)
{
   Double_t *pV = v.GetMatrixArray();
   Double_t *pD = d.GetMatrixArray();
   Double_t *pE = e.GetMatrixArray();

   const Int_t n = v.GetNrows();

   Int_t i,j,k;
   Int_t off_n1 = (n-1)*n;
   for (j = 0; j < n; j++)
      pD[j] = pV[off_n1+j];

   // Householder reduction to tridiagonal form.

   for (i = n-1; i > 0; i--) {
      const Int_t off_i1 = (i-1)*n;
      const Int_t off_i  = i*n;

      // Scale to avoid under/overflow.

      Double_t scale = 0.0;
      Double_t h = 0.0;
      for (k = 0; k < i; k++)
         scale = scale+TMath::Abs(pD[k]);
      if (scale == 0.0) {
         pE[i] = pD[i-1];
         for (j = 0; j < i; j++) {
            const Int_t off_j = j*n;
            pD[j] = pV[off_i1+j];
            pV[off_i+j] = 0.0;
            pV[off_j+i] = 0.0;
         }
      } else {

         // Generate Householder vector.

         for (k = 0; k < i; k++) {
            pD[k] /= scale;
            h += pD[k]*pD[k];
         }
         Double_t f = pD[i-1];
         Double_t g = TMath::Sqrt(h);
         if (f > 0)
            g = -g;
         pE[i]   = scale*g;
         h       = h-f*g;
         pD[i-1] = f-g;
         for (j = 0; j < i; j++)
            pE[j] = 0.0;

         // Apply similarity transformation to remaining columns.

         for (j = 0; j < i; j++) {
            const Int_t off_j = j*n;
            f = pD[j];
            pV[off_j+i] = f;
            g = pE[j]+pV[off_j+j]*f;
            for (k = j+1; k <= i-1; k++) {
               const Int_t off_k = k*n;
               g += pV[off_k+j]*pD[k];
               pE[k] += pV[off_k+j]*f;
            }
            pE[j] = g;
         }
         f = 0.0;
         for (j = 0; j < i; j++) {
            pE[j] /= h;
            f += pE[j]*pD[j];
         }
         Double_t hh = f/(h+h);
         for (j = 0; j < i; j++)
            pE[j] -= hh*pD[j];
         for (j = 0; j < i; j++) {
            f = pD[j];
            g = pE[j];
            for (k = j; k <= i-1; k++) {
               const Int_t off_k = k*n;
               pV[off_k+j] -= (f*pE[k]+g*pD[k]);
            }
            pD[j] = pV[off_i1+j];
            pV[off_i+j] = 0.0;
         }
      }
      pD[i] = h;
   }

   // Accumulate transformations.

   for (i = 0; i < n-1; i++) {
      const Int_t off_i  = i*n;
      pV[off_n1+i] = pV[off_i+i];
      pV[off_i+i] = 1.0;
      Double_t h = pD[i+1];
      if (h != 0.0) {
         for (k = 0; k <= i; k++) {
            const Int_t off_k = k*n;
            pD[k] = pV[off_k+i+1]/h;
         }
         for (j = 0; j <= i; j++) {
            Double_t g = 0.0;
            for (k = 0; k <= i; k++) {
               const Int_t off_k = k*n;
               g += pV[off_k+i+1]*pV[off_k+j];
            }
            for (k = 0; k <= i; k++) {
               const Int_t off_k = k*n;
               pV[off_k+j] -= g*pD[k];
            }
         }
      }
      for (k = 0; k <= i; k++) {
         const Int_t off_k = k*n;
         pV[off_k+i+1] = 0.0;
      }
   }
   for (j = 0; j < n; j++) {
      pD[j] = pV[off_n1+j];
      pV[off_n1+j] = 0.0;
   }
   pV[off_n1+n-1] = 1.0;
   pE[0] = 0.0;
}

////////////////////////////////////////////////////////////////////////////////
/// Symmetric tridiagonal QL algorithm.
/// This is derived from the Algol procedures tql2, by Bowdler, Martin, Reinsch, and
/// Wilkinson, Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
/// Fortran subroutine in EISPACK.

void TMatrixDSymEigen::MakeEigenVectors(TMatrixD &v,TVectorD &d,TVectorD &e)
{
   Double_t *pV = v.GetMatrixArray();
   Double_t *pD = d.GetMatrixArray();
   Double_t *pE = e.GetMatrixArray();

   const Int_t n = v.GetNrows();

   Int_t i,j,k,l;
   for (i = 1; i < n; i++)
      pE[i-1] = pE[i];
   pE[n-1] = 0.0;

   Double_t f = 0.0;
   Double_t tst1 = 0.0;
   Double_t eps = TMath::Power(2.0,-52.0);
   for (l = 0; l < n; l++) {

      // Find small subdiagonal element

      tst1 = TMath::Max(tst1,TMath::Abs(pD[l])+TMath::Abs(pE[l]));
      Int_t m = l;

      // Original while-loop from Java code
      while (m < n) {
         if (TMath::Abs(pE[m]) <= eps*tst1) {
            break;
         }
         m++;
      }

      // If m == l, pD[l] is an eigenvalue,
      // otherwise, iterate.

      if (m > l) {
         Int_t iter = 0;
         do {
            if (iter++ == 30) {  // (check iteration count here.)
               //Error("MakeEigenVectors","too many iterations");
               break;
            }

            // Compute implicit shift

            Double_t g = pD[l];
            Double_t p = (pD[l+1]-g)/(2.0*pE[l]);
            Double_t r = TMath::Hypot(p,1.0);
            if (p < 0)
               r = -r;
            pD[l] = pE[l]/(p+r);
            pD[l+1] = pE[l]*(p+r);
            Double_t dl1 = pD[l+1];
            Double_t h = g-pD[l];
            for (i = l+2; i < n; i++)
               pD[i] -= h;
            f = f+h;

            // Implicit QL transformation.

            p = pD[m];
            Double_t c = 1.0;
            Double_t c2 = c;
            Double_t c3 = c;
            Double_t el1 = pE[l+1];
            Double_t s = 0.0;
            Double_t s2 = 0.0;
            for (i = m-1; i >= l; i--) {
               c3 = c2;
               c2 = c;
               s2 = s;
               g = c*pE[i];
               h = c*p;
               r = TMath::Hypot(p,pE[i]);
               pE[i+1] = s*r;
               s = pE[i]/r;
               c = p/r;
               p = c*pD[i]-s*g;
               pD[i+1] = h+s*(c*g+s*pD[i]);

               // Accumulate transformation.

               for (k = 0; k < n; k++) {
                  const Int_t off_k = k*n;
                  h = pV[off_k+i+1];
                  pV[off_k+i+1] = s*pV[off_k+i]+c*h;
                  pV[off_k+i]   = c*pV[off_k+i]-s*h;
               }
            }
            p = -s*s2*c3*el1*pE[l]/dl1;
            pE[l] = s*p;
            pD[l] = c*p;

            // Check for convergence.

         } while (TMath::Abs(pE[l]) > eps*tst1);
      }
      pD[l] = pD[l]+f;
      pE[l] = 0.0;
   }

   // Sort eigenvalues and corresponding vectors.

   for (i = 0; i < n-1; i++) {
      k = i;
      Double_t p = pD[i];
      for (j = i+1; j < n; j++) {
         if (pD[j] > p) {
            k = j;
            p = pD[j];
         }
      }
      if (k != i) {
         pD[k] = pD[i];
         pD[i] = p;
         for (j = 0; j < n; j++) {
            const Int_t off_j = j*n;
            p = pV[off_j+i];
            pV[off_j+i] = pV[off_j+k];
            pV[off_j+k] = p;
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Assignment operator

TMatrixDSymEigen &TMatrixDSymEigen::operator=(const TMatrixDSymEigen &source)
{
   if (this != &source) {
      fEigenVectors.ResizeTo(source.fEigenVectors);
      fEigenValues.ResizeTo(source.fEigenValues);
   }
   return *this;
}

/////////////////////////////////
//////////////////////////////////
////////////////////////////////
/////////////////////////////
