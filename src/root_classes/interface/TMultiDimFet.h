// @(#)root/hist:$Name: v5-12-00e $:$Id: TMultiDimFet.h,v 1.7 2006/05/17 09:37:20 couet Exp $
// Author: Christian Holm Christensen 07/11/2000

#ifndef ROOT_TMultiDimFet
#define ROOT_TMultiDimFet

//#ifndef ROOT_TNamed
//#include "TNamed.h"
//#endif
//#ifndef ROOT_TVectorD
//#include "TVectorD.h"
//#endif
//#ifndef ROOT_TMatrixD
//#include "TMatrixD.h"
//#endif
//#ifndef ROOT_TList
//#include "TList.h"
//#endif
//#ifndef ROOT_TVirtualFitter
//#include "TVirtualFitter.h"
//#endif

#include <vector>
#ifndef ROOT_TMultiDimFit_wrapper
#include "TMultiDimFit_wrapper.h" //what to do ?
#endif


//#include "Rtypes.h"
//#include "RtypesCore.h"
//#include "DllImport.h"
//#include "snprintf.h"   // part of stdio.h on systems that have it
//#include "strlcpy.h"    // part of string.h on systems that have it

//#include "TGenericClassInfo.h"
//#include "TIsAProxy.h"

//#include "TError.h"

//#include "TMath.h"
//#include "Riostream.h"
//#include "TString.h"
//#include <Math/SpecFuncMathCore.h>
//#include <Math/PdfFuncMathCore.h>
//#include <Math/ProbFuncMathCore.h>
// end of tmath - #include <Math/Types.h>

//#include "TMathBase.h"
//#include "TObject.h"

//#include "TBuffer.h"
//#include "TClass.h"

//#include "TMatrixFfwd.h"
//#include "TMatrixFSymfwd.h"
//#include "TMatrixFSparsefwd.h"

//#include "TMatrixDfwd.h"
//#include "TMatrixDSymfwd.h"
//#include "TMatrixDSparsefwd.h"
//#include "TMatrixDUtils.h"

//#include "TMatrixTUtils.h"
//#include "TMatrixDUtilsfwd.h"

//#include "TMatrixT.h"
//#include "TMatrixTSym.h"
//#include "TMatrixTSparse.h"
//#include "TVectorT.h"
//#include "TMatrixTUtils.h"

//#include "TMatrixTLazy.h"
//#include "TMatrixTSymCramerInv.h"

//#include "TDecompLU.h"
//#include "TMatrixDSymEigen.h"
//#include "TDecompBase.h"
//#include "TObject.h"

//#include "TMatrixTCramerInv.h"
//#include "TMatrixDEigen.h"

//#include "TMatrixTBase.h"
//#include "TObject.h"
//#include "TMathBase.h"
//#include "TMatrixFBasefwd.h"
//#include "TMatrixDBasefwd.h"

//#include "TString.h"
//#include "ROOT/RStringView.hxx"
//#include "RConfigure.h"
//#include "ROOT/TypeTraits.hxx"
//#include "ROOT/RSpan.hxx"

//#include "TROOT.h"
//#include "TClass.h"

//#include "TVectorT.h"
//#include "TVectorDfwd.h"
//#include "TMatrixD.h"
//#include "TMatrixDSym.h"
//#include "TMatrixDSparse.h"

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/* @(#)root/base:$Id$ */

/*************************************************************************
 * Copyright (C) 1995-2014, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_Rtypes
#define ROOT_Rtypes

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Rtypes                                                               //
//                                                                      //
// Basic types used by ROOT; ClassDef macros.                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


//#include "RtypesCore.h"
//#include "DllImport.h"

//#include "snprintf.h"   // part of stdio.h on systems that have it
//#include "strlcpy.h"    // part of string.h on systems that have it


#include <atomic>
#include <stdio.h>
#include <string.h>
#include <typeinfo>
#include <type_traits>

#ifndef __CLING__
// __attribute__ is not supported on Windows, but it is internally needed by Cling
// for autoloading and Clad rely on __attribute__((annotate("D")))
#if defined(R__WIN32)
#define __attribute__(unused)
#endif
#endif

//---- forward declared class types --------------------------------------------

class TClass;
class TBuffer;
class TDirectory;
class TMemberInspector;
class TObject;
class TNamed;
class TCollection;
class TFileMergeInfo;
class TString;

//Moved from TSystem.
enum ESysConstants {
   kMAXSIGNALS       = 15,
   kMAXPATHLEN       = 8192,
   kBUFFERSIZE       = 8192,
   kItimerResolution = 10      // interval-timer resolution in ms
};

enum EColor { kWhite =0,   kBlack =1,   kGray=920,
              kRed   =632, kGreen =416, kBlue=600, kYellow=400, kMagenta=616, kCyan=432,
              kOrange=800, kSpring=820, kTeal=840, kAzure =860, kViolet =880, kPink=900 };

// There is several streamer concepts.
class TClassStreamer;   // Streamer functor for a class
class TMemberStreamer;  // Streamer functor for a data member
typedef void (*ClassStreamerFunc_t)(TBuffer&, void*);  // Streamer function for a class
typedef void (*ClassConvStreamerFunc_t)(TBuffer&, void*, const TClass*);  // Streamer function for a class with conversion.
typedef void (*MemberStreamerFunc_t)(TBuffer&, void*, Int_t); // Streamer function for a data member

// This class is used to implement proxy around collection classes.
class TVirtualCollectionProxy;

typedef void    (*VoidFuncPtr_t)();  //pointer to void function
typedef TClass* (*DictFuncPtr_t)();  //pointer to dictionary function
// NOTE: the previous name must be changed.

//--- bit manipulation ---------------------------------------------------------

#define BIT(n)       (1ULL << (n))
#define SETBIT(n,i)  ((n) |= BIT(i))
#define CLRBIT(n,i)  ((n) &= ~BIT(i))
#define TESTBIT(n,i) ((Bool_t)(((n) & BIT(i)) != 0))


//---- debug global ------------------------------------------------------------

R__EXTERN Int_t gDebug;


//---- ClassDef macros ---------------------------------------------------------

typedef void (*ShowMembersFunc_t)(const void *obj, TMemberInspector &R__insp, Bool_t isTransient);
class TVirtualIsAProxy;
typedef TClass *(*IsAGlobalFunc_t)(const TClass*, const void *obj);

// TBuffer.h declares and implements the following 2 operators
template <class Tmpl> TBuffer &operator>>(TBuffer &buf, Tmpl *&obj);
template <class Tmpl> TBuffer &operator<<(TBuffer &buf, const Tmpl *obj);

// This might get used if we implement setting a class version.
// template <class RootClass> Short_t GetClassVersion(RootClass *);

namespace ROOT {

   class TGenericClassInfo;
   typedef void *(*NewFunc_t)(void *);
   typedef void *(*NewArrFunc_t)(Long_t size, void *arena);
   typedef void  (*DelFunc_t)(void *);
   typedef void  (*DelArrFunc_t)(void *);
   typedef void  (*DesFunc_t)(void *);
   typedef void  (*DirAutoAdd_t)(void *, TDirectory *);
   typedef Long64_t (*MergeFunc_t)(void *, TCollection *, TFileMergeInfo *);
   typedef void  (*ResetAfterMergeFunc_t)(void *, TFileMergeInfo *);

   template <class RootClass> Short_t SetClassVersion(RootClass *);

   extern TClass *CreateClass(const char *cname, Version_t id,
                              const std::type_info &info, TVirtualIsAProxy *isa,
                              const char *dfil, const char *ifil,
                              Int_t dl, Int_t il);
   extern void AddClass(const char *cname, Version_t id, const std::type_info &info,
                        DictFuncPtr_t dict, Int_t pragmabits);
   extern void RemoveClass(const char *cname);
   extern void ResetClassVersion(TClass*, const char*, Short_t);
   extern void AddClassAlternate(const char *normName, const char *alternate);

   extern TNamed *RegisterClassTemplate(const char *name,
                                        const char *file, Int_t line);

   extern void Class_ShowMembers(TClass *cl, const void *obj, TMemberInspector&);

#if 0
   // This function is only implemented in the dictionary file.
   // The parameter is 'only' for overloading resolution.
   // Used to be a template <class T> TGenericClassInfo *GenerateInitInstance(const T*);
   template <class T> TGenericClassInfo *GetClassInfo(const T* t) {
      TGenericClassInfo *GenerateInitInstance(const T*);
      return CreateInitInstance(t);
   };
#endif

   namespace Internal {
   class TInitBehavior {
      // This class defines the interface for the class registration and
      // the TClass creation. To modify the default behavior, one would
      // inherit from this class and overload ROOT::DefineBehavior().
      // See TQObject.h and table/inc/Ttypes.h for examples.
   public:
      virtual ~TInitBehavior() { }

      virtual void Register(const char *cname, Version_t id,
                            const std::type_info &info,
                            DictFuncPtr_t dict, Int_t pragmabits) const = 0;
      virtual void Unregister(const char *classname) const = 0;
      virtual TClass *CreateClass(const char *cname, Version_t id,
                                  const std::type_info &info, TVirtualIsAProxy *isa,
                                  const char *dfil, const char *ifil,
                                  Int_t dl, Int_t il) const = 0;
   };

   class TDefaultInitBehavior: public TInitBehavior {
   public:
      virtual void Register(const char *cname, Version_t id,
                            const std::type_info &info,
                            DictFuncPtr_t dict, Int_t pragmabits) const {
         ROOT::AddClass(cname, id, info, dict, pragmabits);
      }

      virtual void Unregister(const char *classname) const {
         ROOT::RemoveClass(classname);
      }

      virtual TClass *CreateClass(const char *cname, Version_t id,
                                  const std::type_info &info, TVirtualIsAProxy *isa,
                                  const char *dfil, const char *ifil,
                                  Int_t dl, Int_t il) const {
         return ROOT::CreateClass(cname, id, info, isa, dfil, ifil, dl, il);
      }
   };

   const TInitBehavior *DefineBehavior(void * /*parent_type*/,
                                       void * /*actual_type*/);
   } // namespace Internal

} // namespace ROOT

// The macros below use TGenericClassInfo and TInstrumentedIsAProxy, so let's
// ensure they are included.
//#include "TGenericClassInfo.h"

typedef std::atomic<TClass*> atomic_TClass_ptr;

//#include "TIsAProxy.h"

namespace ROOT { namespace Internal {

class TCDGIILIBase {
public:
   // All implemented in TGenericClassInfo.cxx.
   static void SetInstance(::ROOT::TGenericClassInfo& R__instance,
                    NewFunc_t, NewArrFunc_t, DelFunc_t, DelArrFunc_t, DesFunc_t);
   static void SetName(const std::string& name, std::string& nameMember);
   static void SetfgIsA(atomic_TClass_ptr& isA, TClass*(*dictfun)());
};

template <typename T>
class ClassDefGenerateInitInstanceLocalInjector:
   public TCDGIILIBase {
      static atomic_TClass_ptr fgIsA;
      static ::ROOT::TGenericClassInfo *fgGenericInfo;
   public:
      static void *New(void *p) { return p ? new(p) T : new T; };
      static void *NewArray(Long_t nElements, void *p) {
         return p ? new(p) T[nElements] : new T[nElements]; }
      static void Delete(void *p) { delete ((T*)p); }
      static void DeleteArray(void *p) { delete[] ((T*)p); }
      static void Destruct(void *p) { ((T*)p)->~T();  }
      static ::ROOT::TGenericClassInfo *GenerateInitInstanceLocal() {
         static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy<T>(0);
         static ::ROOT::TGenericClassInfo
            R__instance(T::Class_Name(), T::Class_Version(),
                        T::DeclFileName(), T::DeclFileLine(),
                        typeid(T), ::ROOT::Internal::DefineBehavior((T*)0, (T*)0),
                        &T::Dictionary, isa_proxy, 0, sizeof(T) );
         SetInstance(R__instance, &New, &NewArray, &Delete, &DeleteArray, &Destruct);
         return &R__instance;
      }
      // We need a reference to the template instance static member in a concrete function in order
      // to force its instantiation (even before the function is actually run)
      // Since we do have a reference to Dictionary (in T::Dictionary), using fgGenericInfo
      // here will insure that it is initialized at process start or library load time.
      static TClass *Dictionary() { fgIsA = fgGenericInfo->GetClass(); return fgIsA; }
      static TClass *Class() { SetfgIsA(fgIsA, &Dictionary); return fgIsA; }
      static const char* Name() {
         static std::string gName;
         if (gName.empty())
            SetName(GetDemangledTypeName(typeid(T)), gName);
         return gName.c_str();
      }
   };

   template<typename T>
   atomic_TClass_ptr ClassDefGenerateInitInstanceLocalInjector<T>::fgIsA{};
   template<typename T>
   ::ROOT::TGenericClassInfo *ClassDefGenerateInitInstanceLocalInjector<T>::fgGenericInfo {
      ClassDefGenerateInitInstanceLocalInjector<T>::GenerateInitInstanceLocal()
   };

   template <typename T>
   struct THashConsistencyHolder {
      static Bool_t fgHashConsistency;
   };

   template <typename T>
   Bool_t THashConsistencyHolder<T>::fgHashConsistency;

   void DefaultStreamer(TBuffer &R__b, const TClass *cl, void *objpointer);
   Bool_t HasConsistentHashMember(TClass &clRef);
   Bool_t HasConsistentHashMember(const char *clName);
}} // namespace ROOT::Internal


// Common part of ClassDef definition.
// DeclFileLine() is not part of it since CINT uses that as trigger for
// the class comment string.
#define _ClassDefBase_(name, id, virtual_keyword, overrd)                                                       \
private:          \
   static_assert(std::is_integral<decltype(id)>::value, "ClassDef(Inline) macro: the specified class version number is not an integer.");                                                        \
   virtual_keyword Bool_t CheckTObjectHashConsistency() const overrd                                            \
   {                                                                                                            \
      static std::atomic<UChar_t> recurseBlocker(0);                                                            \
      if (R__likely(recurseBlocker >= 2)) {                                                                     \
         return ::ROOT::Internal::THashConsistencyHolder<decltype(*this)>::fgHashConsistency;                   \
      } else if (recurseBlocker == 1) {                                                                         \
         return false;                                                                                          \
      } else if (recurseBlocker++ == 0) {                                                                       \
         ::ROOT::Internal::THashConsistencyHolder<decltype(*this)>::fgHashConsistency =                         \
            ::ROOT::Internal::HasConsistentHashMember(_QUOTE_(name)) ||                                         \
            ::ROOT::Internal::HasConsistentHashMember(*IsA());                                                  \
         ++recurseBlocker;                                                                                      \
         return ::ROOT::Internal::THashConsistencyHolder<decltype(*this)>::fgHashConsistency;                   \
      }                                                                                                         \
      return false; /* unreacheable */                                                                          \
   }                                                                                                            \
                                                                                                                \
public:                                                                                                         \
   static Version_t Class_Version() { return id; }                                                              \
   virtual_keyword TClass *IsA() const overrd { return name::Class(); }                                         \
   virtual_keyword void ShowMembers(TMemberInspector &insp) const overrd                                        \
   {                                                                                                            \
      ::ROOT::Class_ShowMembers(name::Class(), this, insp);                                                     \
   }                                                                                                            \
   void StreamerNVirtual(TBuffer &ClassDef_StreamerNVirtual_b) { name::Streamer(ClassDef_StreamerNVirtual_b); } \
   static const char *DeclFileName() { return __FILE__; }

#define _ClassDefOutline_(name,id, virtual_keyword, overrd) \
   _ClassDefBase_(name,id, virtual_keyword, overrd)       \
private: \
   static atomic_TClass_ptr fgIsA; \
public: \
   static int ImplFileLine(); \
   static const char *ImplFileName(); \
   static const char *Class_Name(); \
   static TClass *Dictionary(); \
   static TClass *Class(); \
   virtual_keyword void Streamer(TBuffer&) overrd;

#define _ClassDefInline_(name, id, virtual_keyword, overrd)                                                      \
   _ClassDefBase_(name, id, virtual_keyword, overrd) public : static int ImplFileLine() { return -1; }           \
   static const char *ImplFileName() { return 0; }                                                               \
   static const char *Class_Name()                                                                               \
   {                                                                                                             \
      return ::ROOT::Internal::ClassDefGenerateInitInstanceLocalInjector<name>::Name();                          \
   }                                                                                                             \
   static TClass *Dictionary()                                                                                   \
   {                                                                                                             \
      return ::ROOT::Internal::ClassDefGenerateInitInstanceLocalInjector<name>::Dictionary();                    \
   }                                                                                                             \
   static TClass *Class() { return ::ROOT::Internal::ClassDefGenerateInitInstanceLocalInjector<name>::Class(); } \
   virtual_keyword void Streamer(TBuffer &R__b) overrd { ::ROOT::Internal::DefaultStreamer(R__b, name::Class(), this); }

#define ClassDef(name,id) \
   _ClassDefOutline_(name,id,virtual,)   \
   static int DeclFileLine() { return __LINE__; }

#define ClassDefOverride(name,id) \
   _ClassDefOutline_(name,id,,override)   \
   static int DeclFileLine() { return __LINE__; }

#define ClassDefNV(name,id) \
   _ClassDefOutline_(name,id,,) \
   static int DeclFileLine() { return __LINE__; }

#define ClassDefInline(name,id) \
   _ClassDefInline_(name,id,virtual,)                   \
   static int DeclFileLine() { return __LINE__; }

#define ClassDefInlineOverride(name,id)                       \
   _ClassDefInline_(name,id,,override)                        \
   static int DeclFileLine() { return __LINE__; }

#define ClassDefInlineNV(name,id) \
   _ClassDefInline_(name,id,,)                         \
   static int DeclFileLine() { return __LINE__; }

//#define _ClassDefInterp_(name,id) ClassDefInline(name,id)

#define R__UseDummy(name) \
   class _NAME2_(name,_c) { public: _NAME2_(name,_c)() { if (name) { } } }


#define ClassImpUnique(name,key) \
   namespace ROOT { \
      TGenericClassInfo *GenerateInitInstance(const name*); \
      namespace { \
         static int _R__UNIQUE_(_NAME2_(R__dummyint,key)) __attribute__((unused)) = \
            GenerateInitInstance((name*)0x0)->SetImplFile(__FILE__, __LINE__); \
         R__UseDummy(_R__UNIQUE_(_NAME2_(R__dummyint,key))); \
      } \
   }
#define ClassImp(name) ClassImpUnique(name,default)

// Macro for Namespace

#define NamespaceImpUnique(name,key) \
   namespace name { \
      namespace ROOT { \
         ::ROOT::TGenericClassInfo *GenerateInitInstance(); \
         namespace { \
            static int _R__UNIQUE_(_NAME2_(R__dummyint,key)) = \
               GenerateInitInstance()->SetImplFile(__FILE__, __LINE__); \
            R__UseDummy(_R__UNIQUE_(_NAME2_(R__dummyint,key))); \
         } \
      } \
   }
#define NamespaceImp(name) NamespaceImpUnique(name,default)

//---- ClassDefT macros for templates with one template argument ---------------
// ClassDefT  corresponds to ClassDef
// ClassDefT2 goes in the same header as ClassDefT but must be
//            outside the class scope
// ClassImpT  corresponds to ClassImp


// This ClassDefT is stricly redundant and is kept only for
// backward compatibility.

#define ClassDefT(name,id) \
   _ClassDefOutline_(name,id,virtual,) \
   static int DeclFileLine() { return __LINE__; }

#define ClassDefTNV(name,id) \
   _ClassDefOutline_(name,id,virtual,) \
   static int DeclFileLine() { return __LINE__; }


#define ClassDefT2(name,Tmpl)

#define templateClassImpUnique(name, key)                                                                           \
   namespace ROOT {                                                                                                 \
   static TNamed *                                                                                                  \
      _R__UNIQUE_(_NAME2_(R__dummyholder, key)) = ::ROOT::RegisterClassTemplate(_QUOTE_(name), __FILE__, __LINE__); \
   R__UseDummy(_R__UNIQUE_(_NAME2_(R__dummyholder, key)));                                                          \
   }
#define templateClassImp(name) templateClassImpUnique(name,default)

#define ClassImpT(name,Tmpl) templateClassImp(name)

//---- ClassDefT macros for templates with two template arguments --------------
// ClassDef2T2 goes in the same header as ClassDefT but must be
//             outside the class scope
// ClassImp2T  corresponds to ClassImpT

#define ClassDef2T2(name,Tmpl1,Tmpl2)
#define ClassImp2T(name,Tmpl1,Tmpl2) templateClassImp(name)


//---- ClassDefT macros for templates with three template arguments ------------
// ClassDef3T2 goes in the same header as ClassDefT but must be
//             outside the class scope
// ClassImp3T  corresponds to ClassImpT

#define ClassDef3T2(name,Tmpl1,Tmpl2,Tmpl3)
#define ClassImp3T(name,Tmpl1,Tmpl2,Tmpl3) templateClassImp(name)


//---- Macro to set the class version of non instrumented classes --------------

#define RootClassVersion(name,VersionNumber) \
namespace ROOT { \
   TGenericClassInfo *GenerateInitInstance(const name*); \
   static Short_t _R__UNIQUE_(R__dummyVersionNumber) = \
           GenerateInitInstance((name*)0x0)->SetVersion(VersionNumber); \
   R__UseDummy(_R__UNIQUE_(R__dummyVersionNumber)); \
}

#define RootStreamer(name,STREAMER)                                  \
namespace ROOT {                                                     \
   TGenericClassInfo *GenerateInitInstance(const name*);             \
   static Short_t _R__UNIQUE_(R__dummyStreamer) =                    \
           GenerateInitInstance((name*)0x0)->SetStreamer(STREAMER);  \
   R__UseDummy(_R__UNIQUE_(R__dummyStreamer));                       \
}

//---- Macro to load a library into the interpreter --------------
// Call as R__LOAD_LIBRARY(libEvent)
// This macro intentionally does not take string as argument, to
// prevent compilation errors with complex diagnostics due to
//   TString BAD_DO_NOT_TRY = "lib";
//   R__LOAD_LIBRARY(BAD_DO_NOT_TRY + "BAD_DO_NOT_TRY.so") // ERROR!
#ifdef __CLING__
# define _R_PragmaStr(x) _Pragma(#x)
# define R__LOAD_LIBRARY(LIBRARY) _R_PragmaStr(cling load ( #LIBRARY ))
# define R__ADD_INCLUDE_PATH(PATH) _R_PragmaStr(cling add_include_path ( #PATH ))
# define R__ADD_LIBRARY_PATH(PATH) _R_PragmaStr(cling add_library_path ( #PATH ))
#elif defined(R__WIN32)
# define _R_PragmaStr(x) __pragma(#x)
# define R__LOAD_LIBRARY(LIBRARY) _R_PragmaStr(comment(lib, #LIBRARY))
# define R__ADD_INCLUDE_PATH(PATH) _R_PragmaStr(comment(path, #PATH))
# define R__ADD_LIBRARY_PATH(PATH) _R_PragmaStr(comment(path, #PATH))
#else
// No way to inform linker though preprocessor :-(
// We could even inform the user:
/*
# define R__LOAD_LIBRARY(LIBRARY) \
   _R_PragmaStr(message "Compiler cannot handle linking against " #LIBRARY \
                ". Use -L and -l instead.")
*/
# define R__LOAD_LIBRARY(LIBRARY)
# define R__ADD_INCLUDE_PATH(PATH)
# define R__ADD_LIBRARY_PATH(PATH)
#endif

// Convenience macros to disable cling pointer check.
#ifdef __CLING__
# define R__CLING_PTRCHECK(ONOFF) __attribute__((annotate("__cling__ptrcheck(" #ONOFF ")")))
#else
# define R__CLING_PTRCHECK(ONOFF)
#endif

// On Windows strtok_r does not exist: the function is called strtok_s.
inline char *R__STRTOK_R(char *str, const char *delim, char **saveptr)
{
#if defined(R__WIN32)
   return strtok_s(str, delim, saveptr);
#else
   return strtok_r(str, delim, saveptr);
#endif
}

#endif

// @(#)root/base:$Id$
// Author: Fons Rademakers   23/1/02

/*************************************************************************
 * Copyright (C) 1995-2012, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_Riostream
#define ROOT_Riostream


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Riostream                                                            //
//                                                                      //
// Backward compatibility header, #includes fstream, iostream, iomanip. //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <iomanip>

#endif

// @(#)root/mathcore:$Id$
// Authors: Rene Brun, Anna Kreshuk, Eddy Offermann, Fons Rademakers   29/07/95

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMath
#define ROOT_TMath

//#include "Rtypes.h"
//#include "TMathBase.h"

//#include "TError.h"
#include <algorithm>
#include <limits>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////
///
/// TMath
///
/// Encapsulate most frequently used Math functions.
/// NB. The basic functions Min, Max, Abs and Sign are defined
/// in TMathBase.

namespace TMath {

////////////////////////////////////////////////////////////////////////////////
// Fundamental constants

////////////////////////////////////////////////////////////////////////////////
/// \f[ \pi\f]
constexpr Double_t Pi()
{
   return 3.14159265358979323846;
}

////////////////////////////////////////////////////////////////////////////////
/// \f[ 2\pi\f]
constexpr Double_t TwoPi()
{
   return 2.0 * Pi();
}

////////////////////////////////////////////////////////////////////////////////
/// \f[ \frac{\pi}{2} \f]
constexpr Double_t PiOver2()
{
   return Pi() / 2.0;
}

////////////////////////////////////////////////////////////////////////////////
/// \f[ \frac{\pi}{4} \f]
constexpr Double_t PiOver4()
{
   return Pi() / 4.0;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ \frac{1.}{\pi}\f$
constexpr Double_t InvPi()
{
   return 1.0 / Pi();
}

////////////////////////////////////////////////////////////////////////////////
/// Conversion from radian to degree:
/// \f[ \frac{180}{\pi} \f]
constexpr Double_t RadToDeg()
{
   return 180.0 / Pi();
}

////////////////////////////////////////////////////////////////////////////////
/// Conversion from degree to radian:
/// \f[ \frac{\pi}{180} \f]
constexpr Double_t DegToRad()
{
   return Pi() / 180.0;
}

////////////////////////////////////////////////////////////////////////////////
/// \f[ \sqrt{2} \f]
constexpr Double_t Sqrt2()
{
   return 1.4142135623730950488016887242097;
}

////////////////////////////////////////////////////////////////////////////////
/// Base of natural log:
///  \f[ e \f]
constexpr Double_t E()
{
   return 2.71828182845904523536;
}

////////////////////////////////////////////////////////////////////////////////
/// Natural log of 10 (to convert log to ln)
constexpr Double_t Ln10()
{
   return 2.30258509299404568402;
}

////////////////////////////////////////////////////////////////////////////////
/// Base-10 log of e  (to convert ln to log)
constexpr Double_t LogE()
{
   return 0.43429448190325182765;
}

////////////////////////////////////////////////////////////////////////////////
/// Velocity of light in \f$ m s^{-1} \f$
constexpr Double_t C()
{
   return 2.99792458e8;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ cm s^{-1} \f$
constexpr Double_t Ccgs()
{
   return 100.0 * C();
}

////////////////////////////////////////////////////////////////////////////////
/// Speed of light uncertainty.
constexpr Double_t CUncertainty()
{
   return 0.0;
}

////////////////////////////////////////////////////////////////////////////////
/// Gravitational constant in: \f$ m^{3} kg^{-1} s^{-2} \f$
constexpr Double_t G()
{
   return 6.673e-11;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ cm^{3} g^{-1} s^{-2} \f$
constexpr Double_t Gcgs()
{
   return G() / 1000.0;
}

////////////////////////////////////////////////////////////////////////////////
/// Gravitational constant uncertainty.
constexpr Double_t GUncertainty()
{
   return 0.010e-11;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ \frac{G}{\hbar C} \f$ in \f$ (GeV/c^{2})^{-2} \f$
constexpr Double_t GhbarC()
{
   return 6.707e-39;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ \frac{G}{\hbar C} \f$ uncertainty.
constexpr Double_t GhbarCUncertainty()
{
   return 0.010e-39;
}

////////////////////////////////////////////////////////////////////////////////
/// Standard acceleration of gravity in \f$ m s^{-2} \f$
constexpr Double_t Gn()
{
   return 9.80665;
}

////////////////////////////////////////////////////////////////////////////////
/// Standard acceleration of gravity uncertainty.
constexpr Double_t GnUncertainty()
{
   return 0.0;
}

////////////////////////////////////////////////////////////////////////////////
/// Planck's constant in \f$ J s \f$
/// \f[ h \f]
constexpr Double_t H()
{
   return 6.62606876e-34;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ erg s \f$
constexpr Double_t Hcgs()
{
   return 1.0e7 * H();
}

////////////////////////////////////////////////////////////////////////////////
/// Planck's constant uncertainty.
constexpr Double_t HUncertainty()
{
   return 0.00000052e-34;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ \hbar \f$ in \f$ J s \f$
/// \f[ \hbar = \frac{h}{2\pi} \f]
constexpr Double_t Hbar()
{
   return 1.054571596e-34;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ erg s \f$
constexpr Double_t Hbarcgs()
{
   return 1.0e7 * Hbar();
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ \hbar \f$ uncertainty.
constexpr Double_t HbarUncertainty()
{
   return 0.000000082e-34;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ hc \f$ in \f$ J m \f$
constexpr Double_t HC()
{
   return H() * C();
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ erg cm \f$
constexpr Double_t HCcgs()
{
   return Hcgs() * Ccgs();
}

////////////////////////////////////////////////////////////////////////////////
/// Boltzmann's constant in \f$ J K^{-1} \f$
/// \f[ k \f]
constexpr Double_t K()
{
   return 1.3806503e-23;
}

////////////////////////////////////////////////////////////////////////////////
/// \f$ erg K^{-1} \f$
constexpr Double_t Kcgs()
{
   return 1.0e7 * K();
}

////////////////////////////////////////////////////////////////////////////////
/// Boltzmann's constant uncertainty.
constexpr Double_t KUncertainty()
{
   return 0.0000024e-23;
}

////////////////////////////////////////////////////////////////////////////////
/// Stefan-Boltzmann constant in \f$ W m^{-2} K^{-4}\f$
/// \f[ \sigma \f]
constexpr Double_t Sigma()
{
   return 5.6704e-8;
}

////////////////////////////////////////////////////////////////////////////////
/// Stefan-Boltzmann constant uncertainty.
constexpr Double_t SigmaUncertainty()
{
   return 0.000040e-8;
}

////////////////////////////////////////////////////////////////////////////////
/// Avogadro constant (Avogadro's Number) in \f$ mol^{-1} \f$
constexpr Double_t Na()
{
   return 6.02214199e+23;
}

////////////////////////////////////////////////////////////////////////////////
/// Avogadro constant (Avogadro's Number) uncertainty.
constexpr Double_t NaUncertainty()
{
   return 0.00000047e+23;
}

////////////////////////////////////////////////////////////////////////////////
/// [Universal gas constant](http://scienceworld.wolfram.com/physics/UniversalGasConstant.html)
/// (\f$ Na K \f$) in \f$ J K^{-1} mol^{-1} \f$
//
constexpr Double_t R()
{
   return K() * Na();
}

////////////////////////////////////////////////////////////////////////////////
/// Universal gas constant uncertainty.
constexpr Double_t RUncertainty()
{
   return R() * ((KUncertainty() / K()) + (NaUncertainty() / Na()));
}

////////////////////////////////////////////////////////////////////////////////
/// [Molecular weight of dry air 1976 US Standard Atmosphere](http://atmos.nmsu.edu/jsdap/encyclopediawork.html)
/// in \f$ kg kmol^{-1} \f$ or \f$ gm mol^{-1} \f$
constexpr Double_t MWair()
{
   return 28.9644;
}

////////////////////////////////////////////////////////////////////////////////
/// [Dry Air Gas Constant (R / MWair)](http://atmos.nmsu.edu/education_and_outreach/encyclopedia/gas_constant.htm)
/// in \f$ J kg^{-1} K^{-1} \f$
constexpr Double_t Rgair()
{
   return (1000.0 * R()) / MWair();
}

////////////////////////////////////////////////////////////////////////////////
/// Euler-Mascheroni Constant.
constexpr Double_t EulerGamma()
{
   return 0.577215664901532860606512090082402431042;
}

////////////////////////////////////////////////////////////////////////////////
/// Elementary charge in \f$ C \f$ .
constexpr Double_t Qe()
{
   return 1.602176462e-19;
}

////////////////////////////////////////////////////////////////////////////////
/// Elementary charge uncertainty.
constexpr Double_t QeUncertainty()
{
   return 0.000000063e-19;
}

////////////////////////////////////////////////////////////////////////////////
// Mathematical Functions

////////////////////////////////////////////////////////////////////////////////
// Trigonometrical Functions

inline Double_t Sin(Double_t);
inline Double_t Cos(Double_t);
inline Double_t Tan(Double_t);
inline Double_t SinH(Double_t);
inline Double_t CosH(Double_t);
inline Double_t TanH(Double_t);
inline Double_t ASin(Double_t);
inline Double_t ACos(Double_t);
inline Double_t ATan(Double_t);
inline Double_t ATan2(Double_t, Double_t);
Double_t ASinH(Double_t);
Double_t ACosH(Double_t);
Double_t ATanH(Double_t);
Double_t Hypot(Double_t x, Double_t y);

////////////////////////////////////////////////////////////////////////////////
// Elementary Functions

inline Double_t Ceil(Double_t x);
inline Int_t CeilNint(Double_t x);
inline Double_t Floor(Double_t x);
inline Int_t FloorNint(Double_t x);
template <typename T>
inline Int_t Nint(T x);

inline Double_t Sq(Double_t x);
inline Double_t Sqrt(Double_t x);
inline Double_t Exp(Double_t x);
inline Double_t Ldexp(Double_t x, Int_t exp);
Double_t Factorial(Int_t i);
inline LongDouble_t Power(LongDouble_t x, LongDouble_t y);
inline LongDouble_t Power(LongDouble_t x, Long64_t y);
inline LongDouble_t Power(Long64_t x, Long64_t y);
inline Double_t Power(Double_t x, Double_t y);
inline Double_t Power(Double_t x, Int_t y);
inline Double_t Log(Double_t x);
Double_t Log2(Double_t x);
inline Double_t Log10(Double_t x);
inline Int_t Finite(Double_t x);
inline Int_t Finite(Float_t x);
inline Bool_t IsNaN(Double_t x);
inline Bool_t IsNaN(Float_t x);

inline Double_t QuietNaN();
inline Double_t SignalingNaN();
inline Double_t Infinity();

template <typename T>
struct Limits {
   inline static T Min();
   inline static T Max();
   inline static T Epsilon();
   };

   // Some integer math
   Long_t   Hypot(Long_t x, Long_t y);     // sqrt(px*px + py*py)

   // Comparing floating points
   inline Bool_t AreEqualAbs(Double_t af, Double_t bf, Double_t epsilon) {
      //return kTRUE if absolute difference between af and bf is less than epsilon
      return TMath::Abs(af-bf) < epsilon;
   }
   inline Bool_t AreEqualRel(Double_t af, Double_t bf, Double_t relPrec) {
      //return kTRUE if relative difference between af and bf is less than relPrec
      return TMath::Abs(af - bf) <= 0.5 * relPrec * (TMath::Abs(af) + TMath::Abs(bf)) ||
             TMath::Abs(af - bf) < Limits<Double_t>::Min(); // handle denormals
   }

   /////////////////////////////////////////////////////////////////////////////
   // Array Algorithms

   // Min, Max of an array
   template <typename T> T MinElement(Long64_t n, const T *a);
   template <typename T> T MaxElement(Long64_t n, const T *a);

   // Locate Min, Max element number in an array
   template <typename T> Long64_t  LocMin(Long64_t n, const T *a);
   template <typename Iterator> Iterator LocMin(Iterator first, Iterator last);
   template <typename T> Long64_t  LocMax(Long64_t n, const T *a);
   template <typename Iterator> Iterator LocMax(Iterator first, Iterator last);

   // Hashing
   //ULong_t Hash(const void *txt, Int_t ntxt);
   //ULong_t Hash(const char *str);

   void BubbleHigh(Int_t Narr, Double_t *arr1, Int_t *arr2);
   void BubbleLow (Int_t Narr, Double_t *arr1, Int_t *arr2);

   Bool_t   Permute(Int_t n, Int_t *a); // Find permutations

   /////////////////////////////////////////////////////////////////////////////
   // Geometrical Functions

   //Sample quantiles
   void      Quantiles(Int_t n, Int_t nprob, Double_t *x, Double_t *quantiles, Double_t *prob,
                       Bool_t isSorted=kTRUE, Int_t *index = 0, Int_t type=7);

   // IsInside
   template <typename T> Bool_t IsInside(T xp, T yp, Int_t np, T *x, T *y);

   // Calculate the Cross Product of two vectors
   template <typename T> T *Cross(const T v1[3],const T v2[3], T out[3]);

   Float_t   Normalize(Float_t v[3]);  // Normalize a vector
   Double_t  Normalize(Double_t v[3]); // Normalize a vector

   //Calculate the Normalized Cross Product of two vectors
   template <typename T> inline T NormCross(const T v1[3],const T v2[3],T out[3]);

   // Calculate a normal vector of a plane
   template <typename T> T *Normal2Plane(const T v1[3],const T v2[3],const T v3[3], T normal[3]);

   /////////////////////////////////////////////////////////////////////////////
   // Polynomial Functions

   Bool_t    RootsCubic(const Double_t coef[4],Double_t &a, Double_t &b, Double_t &c);

   /////////////////////////////////////////////////////////////////////////////
   // Statistic Functions

   Double_t Binomial(Int_t n,Int_t k);  // Calculate the binomial coefficient n over k
   //Double_t BinomialI(Double_t p, Int_t n, Int_t k);
   Double_t BreitWigner(Double_t x, Double_t mean=0, Double_t gamma=1);
   Double_t CauchyDist(Double_t x, Double_t t=0, Double_t s=1);
   //Double_t ChisquareQuantile(Double_t p, Double_t ndf);
   //Double_t FDist(Double_t F, Double_t N, Double_t M);
   //Double_t FDistI(Double_t F, Double_t N, Double_t M);
   Double_t Gaus(Double_t x, Double_t mean=0, Double_t sigma=1, Bool_t norm=kFALSE);
   Double_t KolmogorovProb(Double_t z);
   Double_t KolmogorovTest(Int_t na, const Double_t *a, Int_t nb, const Double_t *b, Option_t *option);
   //Double_t Landau(Double_t x, Double_t mpv=0, Double_t sigma=1, Bool_t norm=kFALSE);
   //Double_t LandauI(Double_t x);
   Double_t LaplaceDist(Double_t x, Double_t alpha=0, Double_t beta=1);
   Double_t LaplaceDistI(Double_t x, Double_t alpha=0, Double_t beta=1);
   //Double_t LogNormal(Double_t x, Double_t sigma, Double_t theta=0, Double_t m=1);
   Double_t NormQuantile(Double_t p);
   //Double_t Poisson(Double_t x, Double_t par);
   //Double_t PoissonI(Double_t x, Double_t par);
   //Double_t Prob(Double_t chi2,Int_t ndf);
   //Double_t Student(Double_t T, Double_t ndf);
   //Double_t StudentI(Double_t T, Double_t ndf);
   Double_t StudentQuantile(Double_t p, Double_t ndf, Bool_t lower_tail=kTRUE);
   //Double_t Vavilov(Double_t x, Double_t kappa, Double_t beta2);
   //Double_t VavilovI(Double_t x, Double_t kappa, Double_t beta2);
   Double_t Voigt(Double_t x, Double_t sigma, Double_t lg, Int_t r = 4);

   /////////////////////////////////////////////////////////////////////////////
   // Statistics over arrays

   //Mean, Geometric Mean, Median, RMS(sigma)

   template <typename T> Double_t Mean(Long64_t n, const T *a, const Double_t *w=0);
   template <typename Iterator> Double_t Mean(Iterator first, Iterator last);
   template <typename Iterator, typename WeightIterator> Double_t Mean(Iterator first, Iterator last, WeightIterator wfirst);

   template <typename T> Double_t GeomMean(Long64_t n, const T *a);
   template <typename Iterator> Double_t GeomMean(Iterator first, Iterator last);

   template <typename T> Double_t RMS(Long64_t n, const T *a, const Double_t *w=0);
   template <typename Iterator> Double_t RMS(Iterator first, Iterator last);
   template <typename Iterator, typename WeightIterator> Double_t RMS(Iterator first, Iterator last, WeightIterator wfirst);

   template <typename T> Double_t StdDev(Long64_t n, const T *a, const Double_t * w = 0) { return RMS<T>(n,a,w); }
   template <typename Iterator> Double_t StdDev(Iterator first, Iterator last) { return RMS<Iterator>(first,last); }
   template <typename Iterator, typename WeightIterator> Double_t StdDev(Iterator first, Iterator last, WeightIterator wfirst) { return RMS<Iterator,WeightIterator>(first,last,wfirst); }

   template <typename T> Double_t Median(Long64_t n, const T *a,  const Double_t *w=0, Long64_t *work=0);

   //k-th order statistic
   template <class Element, typename Size> Element KOrdStat(Size n, const Element *a, Size k, Size *work = 0);

   /////////////////////////////////////////////////////////////////////////////
   // Special Functions

   //Double_t Beta(Double_t p, Double_t q);
   Double_t BetaCf(Double_t x, Double_t a, Double_t b);
   //Double_t BetaDist(Double_t x, Double_t p, Double_t q);
   //Double_t BetaDistI(Double_t x, Double_t p, Double_t q);
   //Double_t BetaIncomplete(Double_t x, Double_t a, Double_t b);

   // Bessel functions
   Double_t BesselI(Int_t n,Double_t x);  /// integer order modified Bessel function I_n(x)
   Double_t BesselK(Int_t n,Double_t x);  /// integer order modified Bessel function K_n(x)
   Double_t BesselI0(Double_t x);         /// modified Bessel function I_0(x)
   Double_t BesselK0(Double_t x);         /// modified Bessel function K_0(x)
   Double_t BesselI1(Double_t x);         /// modified Bessel function I_1(x)
   Double_t BesselK1(Double_t x);         /// modified Bessel function K_1(x)
   Double_t BesselJ0(Double_t x);         /// Bessel function J0(x) for any real x
   Double_t BesselJ1(Double_t x);         /// Bessel function J1(x) for any real x
   Double_t BesselY0(Double_t x);         /// Bessel function Y0(x) for positive x
   Double_t BesselY1(Double_t x);         /// Bessel function Y1(x) for positive x
   Double_t StruveH0(Double_t x);         /// Struve functions of order 0
   Double_t StruveH1(Double_t x);         /// Struve functions of order 1
   Double_t StruveL0(Double_t x);         /// Modified Struve functions of order 0
   Double_t StruveL1(Double_t x);         /// Modified Struve functions of order 1

   Double_t DiLog(Double_t x);
   //Double_t Erf(Double_t x);
   //Double_t ErfInverse(Double_t x);
   //Double_t Erfc(Double_t x);
   //Double_t ErfcInverse(Double_t x);
   Double_t Freq(Double_t x);
   //Double_t Gamma(Double_t z);
   //Double_t Gamma(Double_t a,Double_t x);
   //Double_t GammaDist(Double_t x, Double_t gamma, Double_t mu=0, Double_t beta=1);
   //Double_t LnGamma(Double_t z);
}

////////////////////////////////////////////////////////////////////////////////
// Trig and other functions

#include <float.h>

#if defined(R__WIN32) && !defined(__CINT__)
#   ifndef finite
#      define finite _finite
#   endif
#endif
#if defined(R__AIX) || defined(R__SOLARIS_CC50) || \
    defined(R__HPUX11) || defined(R__GLIBC) || \
    (defined(R__MACOSX) )
// math functions are defined inline so we have to include them here
#   include <math.h>
#   ifdef R__SOLARIS_CC50
       extern "C" { int finite(double); }
#   endif
// #   if defined(R__GLIBC) && defined(__STRICT_ANSI__)
// #      ifndef finite
// #         define finite __finite
// #      endif
// #      ifndef isnan
// #         define isnan  __isnan
// #      endif
// #   endif
#else
// don't want to include complete <math.h>
extern "C" {
   extern double sin(double);
   extern double cos(double);
   extern double tan(double);
   extern double sinh(double);
   extern double cosh(double);
   extern double tanh(double);
   extern double asin(double);
   extern double acos(double);
   extern double atan(double);
   extern double atan2(double, double);
   extern double sqrt(double);
   extern double exp(double);
   extern double pow(double, double);
   extern double log(double);
   extern double log10(double);
#ifndef R__WIN32
#   if !defined(finite)
       extern int finite(double);
#   endif
#   if !defined(isnan)
       extern int isnan(double);
#   endif
   extern double ldexp(double, int);
   extern double ceil(double);
   extern double floor(double);
#else
   _CRTIMP double ldexp(double, int);
   _CRTIMP double ceil(double);
   _CRTIMP double floor(double);
#endif
}
#endif

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Sin(Double_t x)
   { return sin(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Cos(Double_t x)
   { return cos(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Tan(Double_t x)
   { return tan(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::SinH(Double_t x)
   { return sinh(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::CosH(Double_t x)
   { return cosh(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::TanH(Double_t x)
   { return tanh(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::ASin(Double_t x)
   { if (x < -1.) return -TMath::Pi()/2;
     if (x >  1.) return  TMath::Pi()/2;
     return asin(x);
   }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::ACos(Double_t x)
   { if (x < -1.) return TMath::Pi();
     if (x >  1.) return 0;
     return acos(x);
   }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::ATan(Double_t x)
   { return atan(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::ATan2(Double_t y, Double_t x)
   { if (x != 0) return  atan2(y, x);
     if (y == 0) return  0;
     if (y >  0) return  Pi()/2;
     else        return -Pi()/2;
   }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Sq(Double_t x)
   { return x*x; }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Sqrt(Double_t x)
   { return sqrt(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Ceil(Double_t x)
   { return ceil(x); }

////////////////////////////////////////////////////////////////////////////////
inline Int_t TMath::CeilNint(Double_t x)
   { return TMath::Nint(ceil(x)); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Floor(Double_t x)
   { return floor(x); }

////////////////////////////////////////////////////////////////////////////////
inline Int_t TMath::FloorNint(Double_t x)
   { return TMath::Nint(floor(x)); }

////////////////////////////////////////////////////////////////////////////////
/// Round to nearest integer. Rounds half integers to the nearest even integer.
template<typename T>
inline Int_t TMath::Nint(T x)
{
   int i;
   if (x >= 0) {
      i = int(x + 0.5);
      if ( i & 1 && x + 0.5 == T(i) ) i--;
   } else {
      i = int(x - 0.5);
      if ( i & 1 && x - 0.5 == T(i) ) i++;
   }
   return i;
}

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Exp(Double_t x)
   { return exp(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Ldexp(Double_t x, Int_t exp)
   { return ldexp(x, exp); }

////////////////////////////////////////////////////////////////////////////////
inline LongDouble_t TMath::Power(LongDouble_t x, LongDouble_t y)
   { return std::pow(x,y); }

////////////////////////////////////////////////////////////////////////////////
inline LongDouble_t TMath::Power(LongDouble_t x, Long64_t y)
   { return std::pow(x,(LongDouble_t)y); }

////////////////////////////////////////////////////////////////////////////////
inline LongDouble_t TMath::Power(Long64_t x, Long64_t y)
   { return std::pow(x,y); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Power(Double_t x, Double_t y)
   { return pow(x, y); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Power(Double_t x, Int_t y) {
#ifdef R__ANSISTREAM
   return std::pow(x, y);
#else
   return pow(x, (Double_t) y);
#endif
}

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Log(Double_t x)
   { return log(x); }

////////////////////////////////////////////////////////////////////////////////
inline Double_t TMath::Log10(Double_t x)
   { return log10(x); }

////////////////////////////////////////////////////////////////////////////////
/// Check if it is finite with a mask in order to be consistent in presence of
/// fast math.
/// Inspired from the CMSSW FWCore/Utilities package
inline Int_t TMath::Finite(Double_t x)
#if defined(R__FAST_MATH)

{
   const unsigned long long mask = 0x7FF0000000000000LL;
   union { unsigned long long l; double d;} v;
   v.d =x;
   return (v.l&mask)!=mask;
}
#else
#  if defined(R__HPUX11)
   { return isfinite(x); }
#  elif defined(R__MACOSX)
#  ifdef isfinite
   // from math.h
   { return isfinite(x); }
#  else
   // from cmath
   { return std::isfinite(x); }
#  endif
#  else
   { return finite(x); }
#  endif
#endif

////////////////////////////////////////////////////////////////////////////////
/// Check if it is finite with a mask in order to be consistent in presence of
/// fast math.
/// Inspired from the CMSSW FWCore/Utilities package
inline Int_t TMath::Finite(Float_t x)
#if defined(R__FAST_MATH)

{
   const unsigned int mask =  0x7f800000;
   union { unsigned int l; float d;} v;
   v.d =x;
   return (v.l&mask)!=mask;
}
#else
{ return std::isfinite(x); }
#endif

// This namespace provides all the routines necessary for checking if a number
// is a NaN also in presence of optimisations affecting the behaviour of the
// floating point calculations.
// Inspired from the CMSSW FWCore/Utilities package

#if defined (R__FAST_MATH)
namespace ROOT {
namespace Internal {
namespace Math {
// abridged from GNU libc 2.6.1 - in detail from
//   math/math_private.h
//   sysdeps/ieee754/ldbl-96/math_ldbl.h

// part of ths file:
   /*
    * ====================================================
    * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
    *
    * Developed at SunPro, a Sun Microsystems, Inc. business.
    * Permission to use, copy, modify, and distribute this
    * software is freely granted, provided that this notice
    * is preserved.
    * ====================================================
    */

   // A union which permits us to convert between a double and two 32 bit ints.
   typedef union {
      Double_t value;
      struct {
         UInt_t lsw;
         UInt_t msw;
      } parts;
   } ieee_double_shape_type;

#define EXTRACT_WORDS(ix0,ix1,d)                                    \
   do {                                                             \
      ieee_double_shape_type ew_u;                                  \
      ew_u.value = (d);                                             \
      (ix0) = ew_u.parts.msw;                                       \
      (ix1) = ew_u.parts.lsw;                                       \
   } while (0)

   inline Bool_t IsNaN(Double_t x)
   {
      UInt_t hx, lx;

      EXTRACT_WORDS(hx, lx, x);

      lx |= hx & 0xfffff;
      hx &= 0x7ff00000;
      return (hx == 0x7ff00000) && (lx != 0);
   }

   typedef union {
      Float_t value;
      UInt_t word;
   } ieee_float_shape_type;

#define GET_FLOAT_WORD(i,d)                                         \
    do {                                                            \
      ieee_float_shape_type gf_u;                                   \
      gf_u.value = (d);                                             \
      (i) = gf_u.word;                                              \
    } while (0)

   inline Bool_t IsNaN(Float_t x)
   {
      UInt_t wx;
      GET_FLOAT_WORD (wx, x);
      wx &= 0x7fffffff;
      return (Bool_t)(wx > 0x7f800000);
   }
} } } // end NS ROOT::Internal::Math
#endif // End R__FAST_MATH

#if defined(R__FAST_MATH)
   inline Bool_t TMath::IsNaN(Double_t x) { return ROOT::Internal::Math::IsNaN(x); }
   inline Bool_t TMath::IsNaN(Float_t x) { return ROOT::Internal::Math::IsNaN(x); }
#else
   inline Bool_t TMath::IsNaN(Double_t x) { return std::isnan(x); }
   inline Bool_t TMath::IsNaN(Float_t x) { return std::isnan(x); }
#endif

////////////////////////////////////////////////////////////////////////////////
// Wrapper to numeric_limits

////////////////////////////////////////////////////////////////////////////////
/// Returns a quiet NaN as [defined by IEEE 754](http://en.wikipedia.org/wiki/NaN#Quiet_NaN)
inline Double_t TMath::QuietNaN() {

   return std::numeric_limits<Double_t>::quiet_NaN();
}

////////////////////////////////////////////////////////////////////////////////
/// Returns a signaling NaN as defined by IEEE 754](http://en.wikipedia.org/wiki/NaN#Signaling_NaN)
inline Double_t TMath::SignalingNaN() {
   return std::numeric_limits<Double_t>::signaling_NaN();
}

////////////////////////////////////////////////////////////////////////////////
/// Returns an infinity as defined by the IEEE standard
inline Double_t TMath::Infinity() {
   return std::numeric_limits<Double_t>::infinity();
}

////////////////////////////////////////////////////////////////////////////////
/// Returns maximum representation for type T
template<typename T>
inline T TMath::Limits<T>::Min() {
   return (std::numeric_limits<T>::min)();    //N.B. use this signature to avoid class with macro min() on Windows
}

////////////////////////////////////////////////////////////////////////////////
/// Returns minimum double representation
template<typename T>
inline T TMath::Limits<T>::Max() {
   return (std::numeric_limits<T>::max)();  //N.B. use this signature to avoid class with macro max() on Windows
}

////////////////////////////////////////////////////////////////////////////////
/// Returns minimum double representation
template<typename T>
inline T TMath::Limits<T>::Epsilon() {
   return std::numeric_limits<T>::epsilon();
}

////////////////////////////////////////////////////////////////////////////////
// Advanced.

////////////////////////////////////////////////////////////////////////////////
/// Calculate the Normalized Cross Product of two vectors
template <typename T> inline T TMath::NormCross(const T v1[3],const T v2[3],T out[3])
{
   return Normalize(Cross(v1,v2,out));
}

////////////////////////////////////////////////////////////////////////////////
/// Return minimum of array a of length n.
template <typename T>
T TMath::MinElement(Long64_t n, const T *a) {
   return *std::min_element(a,a+n);
}

////////////////////////////////////////////////////////////////////////////////
/// Return maximum of array a of length n.
template <typename T>
T TMath::MaxElement(Long64_t n, const T *a) {
   return *std::max_element(a,a+n);
}

////////////////////////////////////////////////////////////////////////////////
/// Return index of array with the minimum element.
/// If more than one element is minimum returns first found.
///
/// Implement here since this one is found to be faster (mainly on 64 bit machines)
/// than stl generic implementation.
/// When performing the comparison,  the STL implementation needs to de-reference both the array iterator
/// and the iterator pointing to the resulting minimum location
template <typename T>
Long64_t TMath::LocMin(Long64_t n, const T *a) {
   if  (n <= 0 || !a) return -1;
   T xmin = a[0];
   Long64_t loc = 0;
   for  (Long64_t i = 1; i < n; i++) {
      if (xmin > a[i])  {
         xmin = a[i];
         loc = i;
      }
   }
   return loc;
}

////////////////////////////////////////////////////////////////////////////////
/// Return index of array with the minimum element.
/// If more than one element is minimum returns first found.
template <typename Iterator>
Iterator TMath::LocMin(Iterator first, Iterator last) {

   return std::min_element(first, last);
}

////////////////////////////////////////////////////////////////////////////////
/// Return index of array with the maximum element.
/// If more than one element is maximum returns first found.
///
/// Implement here since it is faster (see comment in LocMin function)
template <typename T>
Long64_t TMath::LocMax(Long64_t n, const T *a) {
   if  (n <= 0 || !a) return -1;
   T xmax = a[0];
   Long64_t loc = 0;
   for  (Long64_t i = 1; i < n; i++) {
      if (xmax < a[i])  {
         xmax = a[i];
         loc = i;
      }
   }
   return loc;
}

////////////////////////////////////////////////////////////////////////////////
/// Return index of array with the maximum element.
/// If more than one element is maximum returns first found.
template <typename Iterator>
Iterator TMath::LocMax(Iterator first, Iterator last)
{

   return std::max_element(first, last);
}

////////////////////////////////////////////////////////////////////////////////
/// Return the weighted mean of an array defined by the iterators.
template <typename Iterator>
Double_t TMath::Mean(Iterator first, Iterator last)
{
   Double_t sum = 0;
   Double_t sumw = 0;
   while ( first != last )
   {
      sum += *first;
      sumw += 1;
      first++;
   }

   return sum/sumw;
}

////////////////////////////////////////////////////////////////////////////////
/// Return the weighted mean of an array defined by the first and
/// last iterators. The w iterator should point to the first element
/// of a vector of weights of the same size as the main array.
template <typename Iterator, typename WeightIterator>
Double_t TMath::Mean(Iterator first, Iterator last, WeightIterator w)
{

   Double_t sum = 0;
   Double_t sumw = 0;
   int i = 0;
   while ( first != last ) {
      if ( *w < 0) {
         //::Error("TMath::Mean","w[%d] = %.4e < 0 ?!",i,*w);
         return 0;
      }
      sum  += (*w) * (*first);
      sumw += (*w) ;
      ++w;
      ++first;
      ++i;
   }
   if (sumw <= 0) {
      //::Error("TMath::Mean","sum of weights == 0 ?!");
      return 0;
   }

   return sum/sumw;
}

////////////////////////////////////////////////////////////////////////////////
/// Return the weighted mean of an array a with length n.
template <typename T>
Double_t TMath::Mean(Long64_t n, const T *a, const Double_t *w)
{
   if (w) {
      return TMath::Mean(a, a+n, w);
   } else {
      return TMath::Mean(a, a+n);
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Return the geometric mean of an array defined by the iterators.
/// \f[ GeomMean = (\prod_{i=0}^{n-1} |a[i]|)^{1/n} \f]
template <typename Iterator>
Double_t TMath::GeomMean(Iterator first, Iterator last)
{
   Double_t logsum = 0.;
   Long64_t n = 0;
   while ( first != last ) {
      if (*first == 0) return 0.;
      Double_t absa = (Double_t) TMath::Abs(*first);
      logsum += TMath::Log(absa);
      ++first;
      ++n;
   }

   return TMath::Exp(logsum/n);
}

////////////////////////////////////////////////////////////////////////////////
/// Return the geometric mean of an array a of size n.
/// \f[ GeomMean = (\prod_{i=0}^{n-1} |a[i]|)^{1/n} \f]
template <typename T>
Double_t TMath::GeomMean(Long64_t n, const T *a)
{
   return TMath::GeomMean(a, a+n);
}

////////////////////////////////////////////////////////////////////////////////
/// Return the Standard Deviation of an array defined by the iterators.
/// Note that this function returns the sigma(standard deviation) and
/// not the root mean square of the array.
///
/// Use the two pass algorithm, which is slower (! a factor of 2) but much more
/// precise.  Since we have a vector the 2 pass algorithm is still faster than the
/// Welford algorithm. (See also ROOT-5545)
template <typename Iterator>
Double_t TMath::RMS(Iterator first, Iterator last)
{

   Double_t n = 0;

   Double_t tot = 0;
   Double_t mean = TMath::Mean(first,last);
   while ( first != last ) {
      Double_t x = Double_t(*first);
      tot += (x - mean)*(x - mean);
      ++first;
      ++n;
   }
   Double_t rms = (n > 1) ? TMath::Sqrt(tot/(n-1)) : 0.0;
   return rms;
}

////////////////////////////////////////////////////////////////////////////////
/// Return the weighted Standard Deviation of an array defined by the iterators.
/// Note that this function returns the sigma(standard deviation) and
/// not the root mean square of the array.
///
/// As in the unweighted case use the two pass algorithm
template <typename Iterator, typename WeightIterator>
Double_t TMath::RMS(Iterator first, Iterator last, WeightIterator w)
{
   Double_t tot = 0;
   Double_t sumw = 0;
   Double_t sumw2 = 0;
   Double_t mean = TMath::Mean(first,last,w);
   while ( first != last ) {
      Double_t x = Double_t(*first);
      sumw += *w;
      sumw2 += (*w) * (*w);
      tot += (*w) * (x - mean)*(x - mean);
      ++first;
      ++w;
   }
   // use the correction neff/(neff -1) for the unbiased formula
   Double_t rms =  TMath::Sqrt(tot * sumw/ (sumw*sumw - sumw2) );
   return rms;
}

////////////////////////////////////////////////////////////////////////////////
/// Return the Standard Deviation of an array a with length n.
/// Note that this function returns the sigma(standard deviation) and
/// not the root mean square of the array.
template <typename T>
Double_t TMath::RMS(Long64_t n, const T *a, const Double_t * w)
{
   return (w) ? TMath::RMS(a, a+n, w) : TMath::RMS(a, a+n);
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate the Cross Product of two vectors:
///         out = [v1 x v2]
template <typename T> T *TMath::Cross(const T v1[3],const T v2[3], T out[3])
{
   out[0] = v1[1] * v2[2] - v1[2] * v2[1];
   out[1] = v1[2] * v2[0] - v1[0] * v2[2];
   out[2] = v1[0] * v2[1] - v1[1] * v2[0];

   return out;
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate a normal vector of a plane.
///
/// \param[in]  p1, p2,p3     3 3D points belonged the plane to define it.
/// \param[out] normal        Pointer to 3D normal vector (normalized)
template <typename T> T * TMath::Normal2Plane(const T p1[3],const T p2[3],const T p3[3], T normal[3])
{
   T v1[3], v2[3];

   v1[0] = p2[0] - p1[0];
   v1[1] = p2[1] - p1[1];
   v1[2] = p2[2] - p1[2];

   v2[0] = p3[0] - p1[0];
   v2[1] = p3[1] - p1[1];
   v2[2] = p3[2] - p1[2];

   NormCross(v1,v2,normal);
   return normal;
}

////////////////////////////////////////////////////////////////////////////////
/// Function which returns kTRUE if point xp,yp lies inside the
/// polygon defined by the np points in arrays x and y, kFALSE otherwise.
/// Note that the polygon may be open or closed.
template <typename T> Bool_t TMath::IsInside(T xp, T yp, Int_t np, T *x, T *y)
{
   Int_t i, j = np-1 ;
   Bool_t oddNodes = kFALSE;

   for (i=0; i<np; i++) {
      if ((y[i]<yp && y[j]>=yp) || (y[j]<yp && y[i]>=yp)) {
         if (x[i]+(yp-y[i])/(y[j]-y[i])*(x[j]-x[i])<xp) {
            oddNodes = !oddNodes;
         }
      }
      j=i;
   }

   return oddNodes;
}

////////////////////////////////////////////////////////////////////////////////
/// Return the median of the array a where each entry i has weight w[i] .
/// Both arrays have a length of at least n . The median is a number obtained
/// from the sorted array a through
///
/// median = (a[jl]+a[jh])/2.  where (using also the sorted index on the array w)
///
/// sum_i=0,jl w[i] <= sumTot/2
/// sum_i=0,jh w[i] >= sumTot/2
/// sumTot = sum_i=0,n w[i]
///
/// If w=0, the algorithm defaults to the median definition where it is
/// a number that divides the sorted sequence into 2 halves.
/// When n is odd or n > 1000, the median is kth element k = (n + 1) / 2.
/// when n is even and n < 1000the median is a mean of the elements k = n/2 and k = n/2 + 1.
///
/// If the weights are supplied (w not 0) all weights must be >= 0
///
/// If work is supplied, it is used to store the sorting index and assumed to be
/// >= n . If work=0, local storage is used, either on the stack if n < kWorkMax
/// or on the heap for n >= kWorkMax .
template <typename T> Double_t TMath::Median(Long64_t n, const T *a,  const Double_t *w, Long64_t *work)
{

   const Int_t kWorkMax = 100;

   if (n <= 0 || !a) return 0;
   Bool_t isAllocated = kFALSE;
   Double_t median;
   Long64_t *ind;
   Long64_t workLocal[kWorkMax];

   if (work) {
      ind = work;
   } else {
      ind = workLocal;
      if (n > kWorkMax) {
         isAllocated = kTRUE;
         ind = new Long64_t[n];
      }
   }

   if (w) {
      Double_t sumTot2 = 0;
      for (Int_t j = 0; j < n; j++) {
         if (w[j] < 0) {
            //::Error("TMath::Median","w[%d] = %.4e < 0 ?!",j,w[j]);
            if (isAllocated)  delete [] ind;
            return 0;
         }
         sumTot2 += w[j];
      }

      sumTot2 /= 2.;

      Sort(n, a, ind, kFALSE);

      Double_t sum = 0.;
      Int_t jl;
      for (jl = 0; jl < n; jl++) {
         sum += w[ind[jl]];
         if (sum >= sumTot2) break;
      }

      Int_t jh;
      sum = 2.*sumTot2;
      for (jh = n-1; jh >= 0; jh--) {
         sum -= w[ind[jh]];
         if (sum <= sumTot2) break;
      }

      median = 0.5*(a[ind[jl]]+a[ind[jh]]);

   } else {

      if (n%2 == 1)
         median = KOrdStat(n, a,n/2, ind);
      else {
         median = 0.5*(KOrdStat(n, a, n/2 -1, ind)+KOrdStat(n, a, n/2, ind));
      }
   }

   if (isAllocated)
      delete [] ind;
   return median;
}

////////////////////////////////////////////////////////////////////////////////
/// Returns k_th order statistic of the array a of size n
/// (k_th smallest element out of n elements).
///
/// C-convention is used for array indexing, so if you want
/// the second smallest element, call KOrdStat(n, a, 1).
///
/// If work is supplied, it is used to store the sorting index and
/// assumed to be >= n. If work=0, local storage is used, either on
/// the stack if n < kWorkMax or on the heap for n >= kWorkMax.
/// Note that the work index array will not contain the sorted indices but
/// all indices of the smaller element in arbitrary order in work[0,...,k-1] and
/// all indices of the larger element in arbitrary order in work[k+1,..,n-1]
/// work[k] will contain instead the index of the returned element.
///
/// Taken from "Numerical Recipes in C++" without the index array
/// implemented by Anna Khreshuk.
///
/// See also the declarations at the top of this file
template <class Element, typename Size>
Element TMath::KOrdStat(Size n, const Element *a, Size k, Size *work)
{

   const Int_t kWorkMax = 100;

   typedef Size Index;

   Bool_t isAllocated = kFALSE;
   Size i, ir, j, l, mid;
   Index arr;
   Index *ind;
   Index workLocal[kWorkMax];
   Index temp;

   if (work) {
      ind = work;
   } else {
      ind = workLocal;
      if (n > kWorkMax) {
         isAllocated = kTRUE;
         ind = new Index[n];
      }
   }

   for (Size ii=0; ii<n; ii++) {
      ind[ii]=ii;
   }
   Size rk = k;
   l=0;
   ir = n-1;
   for(;;) {
      if (ir<=l+1) { //active partition contains 1 or 2 elements
         if (ir == l+1 && a[ind[ir]]<a[ind[l]])
            {temp = ind[l]; ind[l]=ind[ir]; ind[ir]=temp;}
         Element tmp = a[ind[rk]];
         if (isAllocated)
            delete [] ind;
         return tmp;
      } else {
         mid = (l+ir) >> 1; //choose median of left, center and right
         {temp = ind[mid]; ind[mid]=ind[l+1]; ind[l+1]=temp;}//elements as partitioning element arr.
         if (a[ind[l]]>a[ind[ir]])  //also rearrange so that a[l]<=a[l+1]
            {temp = ind[l]; ind[l]=ind[ir]; ind[ir]=temp;}

         if (a[ind[l+1]]>a[ind[ir]])
            {temp=ind[l+1]; ind[l+1]=ind[ir]; ind[ir]=temp;}

         if (a[ind[l]]>a[ind[l+1]])
            {temp = ind[l]; ind[l]=ind[l+1]; ind[l+1]=temp;}

         i=l+1;        //initialize pointers for partitioning
         j=ir;
         arr = ind[l+1];
         for (;;){
            do i++; while (a[ind[i]]<a[arr]);
            do j--; while (a[ind[j]]>a[arr]);
            if (j<i) break;  //pointers crossed, partitioning complete
               {temp=ind[i]; ind[i]=ind[j]; ind[j]=temp;}
         }
         ind[l+1]=ind[j];
         ind[j]=arr;
         if (j>=rk) ir = j-1; //keep active the partition that
         if (j<=rk) l=i;      //contains the k_th element
      }
   }
}

#endif

// @(#)root/base:
// Authors: Rene Brun, Fons Rademakers   29/07/95

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMathBase
#define ROOT_TMathBase


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMath Base functions                                                 //
//                                                                      //
// Define the functions Min, Max, Abs, Sign, Range for all types.       //
// NB: These functions are unfortunately not available in a portable    //
// way in std::.                                                        //
//                                                                      //
// More functions are defined in TMath.h. TMathBase.h is designed to be //
// a stable file and used in place of TMath.h in the ROOT miniCore.     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

#include <cstdlib>
#include <cmath>
#include <algorithm>

namespace TMath {

   // Abs
   inline Short_t  Abs(Short_t d);
   inline Int_t    Abs(Int_t d);
   inline Long_t   Abs(Long_t d);
   inline Long64_t Abs(Long64_t d);
   inline Float_t  Abs(Float_t d);
   inline Double_t Abs(Double_t d);
   inline LongDouble_t Abs(LongDouble_t d);

   // Even/Odd
   inline Bool_t   Even(Long_t a);
   inline Bool_t   Odd(Long_t a);

   // SignBit
   template<typename Integer>
   inline Bool_t SignBit(Integer a);
   inline Bool_t SignBit(Float_t a);
   inline Bool_t SignBit(Double_t a);
   inline Bool_t SignBit(LongDouble_t a);

   // Sign
   template<typename T1, typename T2>
   inline T1 Sign( T1 a, T2 b);
   inline Float_t  Sign(Float_t a, Float_t b);
   inline Double_t Sign(Double_t a, Double_t b);
   inline LongDouble_t Sign(LongDouble_t a, LongDouble_t b);

   // Min, Max of two scalars
   inline Short_t   Min(Short_t a, Short_t b);
   inline UShort_t  Min(UShort_t a, UShort_t b);
   inline Int_t     Min(Int_t a, Int_t b);
   inline UInt_t    Min(UInt_t a, UInt_t b);
   inline Long_t    Min(Long_t a, Long_t b);
   inline ULong_t   Min(ULong_t a, ULong_t b);
   inline Long64_t  Min(Long64_t a, Long64_t b);
   inline ULong64_t Min(ULong64_t a, ULong64_t b);
   inline Float_t   Min(Float_t a, Float_t b);
   inline Double_t  Min(Double_t a, Double_t b);

   inline Short_t   Max(Short_t a, Short_t b);
   inline UShort_t  Max(UShort_t a, UShort_t b);
   inline Int_t     Max(Int_t a, Int_t b);
   inline UInt_t    Max(UInt_t a, UInt_t b);
   inline Long_t    Max(Long_t a, Long_t b);
   inline ULong_t   Max(ULong_t a, ULong_t b);
   inline Long64_t  Max(Long64_t a, Long64_t b);
   inline ULong64_t Max(ULong64_t a, ULong64_t b);
   inline Float_t   Max(Float_t a, Float_t b);
   inline Double_t  Max(Double_t a, Double_t b);

   // Range
   inline Short_t   Range(Short_t lb, Short_t ub, Short_t x);
   inline Int_t     Range(Int_t lb, Int_t ub, Int_t x);
   inline Long_t    Range(Long_t lb, Long_t ub, Long_t x);
   inline ULong_t   Range(ULong_t lb, ULong_t ub, ULong_t x);
   inline Double_t  Range(Double_t lb, Double_t ub, Double_t x);

   //NextPrime is used by the Core classes.
   Long_t   NextPrime(Long_t x);   // Least prime number greater than x

   // Binary search
   template <typename T> Long64_t BinarySearch(Long64_t n, const T  *array, T value);
   template <typename T> Long64_t BinarySearch(Long64_t n, const T **array, T value);
   template <typename Iterator, typename Element> Iterator BinarySearch(Iterator first, Iterator last, Element value);

   // Sorting
   template <typename Element, typename Index>
   void Sort(Index n, const Element* a, Index* index, Bool_t down=kTRUE);
   template <typename Iterator, typename IndexIterator>
   void SortItr(Iterator first, Iterator last, IndexIterator index, Bool_t down=kTRUE);
}


//---- Even/odd ----------------------------------------------------------------

inline Bool_t TMath::Even(Long_t a)
   { return ! (a & 1); }

inline Bool_t TMath::Odd(Long_t a)
   { return (a & 1); }

//---- Abs ---------------------------------------------------------------------

inline Short_t TMath::Abs(Short_t d)
{ return (d >= 0) ? d : Short_t(-d);  }

inline Int_t TMath::Abs(Int_t d)
{ return std::abs(d); }

inline Long_t TMath::Abs(Long_t d)
{ return std::labs(d); }

inline Long64_t TMath::Abs(Long64_t d)
#if __cplusplus >= 201103
{ return std::llabs(d); }
#else
{ return (d >= 0) ? d : -d;  }
#endif

inline Float_t TMath::Abs(Float_t d)
{ return std::abs(d); }

inline Double_t TMath::Abs(Double_t d)
{ return std::abs(d); }

inline LongDouble_t TMath::Abs(LongDouble_t d)
{ return std::abs(d); }


//---- Sign Bit--------------------------------------------------------------------

template<typename Integer>
inline Bool_t TMath::SignBit( Integer a)
   { return (a < 0); }

inline Bool_t TMath::SignBit(Float_t a)
   { return std::signbit(a);  }

inline Bool_t TMath::SignBit(Double_t a)
   { return std::signbit(a);  }

inline Bool_t TMath::SignBit(LongDouble_t a)
   { return std::signbit(a);  }


//---- Sign --------------------------------------------------------------------

template<typename T1, typename T2>
inline T1 TMath::Sign( T1 a, T2 b)
   { return (SignBit(b)) ? - Abs(a) : Abs(a); }

inline Float_t TMath::Sign(Float_t a, Float_t b)
   { return std::copysign(a,b);  }

inline Double_t TMath::Sign(Double_t a, Double_t b)
   { return std::copysign(a,b);  }

inline LongDouble_t TMath::Sign(LongDouble_t a, LongDouble_t b)
   { return std::copysign(a,b);  }


//---- Min ---------------------------------------------------------------------

inline Short_t TMath::Min(Short_t a, Short_t b)
   { return a <= b ? a : b; }

inline UShort_t TMath::Min(UShort_t a, UShort_t b)
   { return a <= b ? a : b; }

inline Int_t TMath::Min(Int_t a, Int_t b)
   { return a <= b ? a : b; }

inline UInt_t TMath::Min(UInt_t a, UInt_t b)
   { return a <= b ? a : b; }

inline Long_t TMath::Min(Long_t a, Long_t b)
   { return a <= b ? a : b; }

inline ULong_t TMath::Min(ULong_t a, ULong_t b)
   { return a <= b ? a : b; }

inline Long64_t TMath::Min(Long64_t a, Long64_t b)
   { return a <= b ? a : b; }

inline ULong64_t TMath::Min(ULong64_t a, ULong64_t b)
   { return a <= b ? a : b; }

inline Float_t TMath::Min(Float_t a, Float_t b)
   { return a <= b ? a : b; }

inline Double_t TMath::Min(Double_t a, Double_t b)
   { return a <= b ? a : b; }

//---- Max ---------------------------------------------------------------------

inline Short_t TMath::Max(Short_t a, Short_t b)
   { return a >= b ? a : b; }

inline UShort_t TMath::Max(UShort_t a, UShort_t b)
   { return a >= b ? a : b; }

inline Int_t TMath::Max(Int_t a, Int_t b)
   { return a >= b ? a : b; }

inline UInt_t TMath::Max(UInt_t a, UInt_t b)
   { return a >= b ? a : b; }

inline Long_t TMath::Max(Long_t a, Long_t b)
   { return a >= b ? a : b; }

inline ULong_t TMath::Max(ULong_t a, ULong_t b)
   { return a >= b ? a : b; }

inline Long64_t TMath::Max(Long64_t a, Long64_t b)
   { return a >= b ? a : b; }

inline ULong64_t TMath::Max(ULong64_t a, ULong64_t b)
   { return a >= b ? a : b; }

inline Float_t TMath::Max(Float_t a, Float_t b)
   { return a >= b ? a : b; }

inline Double_t TMath::Max(Double_t a, Double_t b)
   { return a >= b ? a : b; }

//---- Range -------------------------------------------------------------------

inline Short_t TMath::Range(Short_t lb, Short_t ub, Short_t x)
   { return x < lb ? lb : (x > ub ? ub : x); }

inline Int_t TMath::Range(Int_t lb, Int_t ub, Int_t x)
   { return x < lb ? lb : (x > ub ? ub : x); }

inline Long_t TMath::Range(Long_t lb, Long_t ub, Long_t x)
   { return x < lb ? lb : (x > ub ? ub : x); }

inline ULong_t TMath::Range(ULong_t lb, ULong_t ub, ULong_t x)
   { return x < lb ? lb : (x > ub ? ub : x); }

inline Double_t TMath::Range(Double_t lb, Double_t ub, Double_t x)
   { return x < lb ? lb : (x > ub ? ub : x); }

template <typename Iterator, typename Element>
Iterator TMath::BinarySearch(Iterator first, Iterator last, Element value)
{
   // Binary search in an array defined by its iterators.
   //
   // The values in the iterators range are supposed to be sorted
   // prior to this call.  If match is found, function returns
   // position of element.  If no match found, function gives nearest
   // element smaller than value.

   Iterator pind;
   pind = std::lower_bound(first, last, value);
   if ( (pind != last) && (*pind == value) )
      return pind;
   else
      return ( pind - 1);
}


template <typename T> Long64_t TMath::BinarySearch(Long64_t n, const T  *array, T value)
{
   // Binary search in an array of n values to locate value.
   //
   // Array is supposed  to be sorted prior to this call.
   // If match is found, function returns position of element.
   // If no match found, function gives nearest element smaller than value.

   const T* pind;
   pind = std::lower_bound(array, array + n, value);
   if ( (pind != array + n) && (*pind == value) )
      return (pind - array);
   else
      return ( pind - array - 1);
}

template <typename T> Long64_t TMath::BinarySearch(Long64_t n, const T **array, T value)
{
   // Binary search in an array of n values to locate value.
   //
   // Array is supposed  to be sorted prior to this call.
   // If match is found, function returns position of element.
   // If no match found, function gives nearest element smaller than value.

   const T* pind;
   pind = std::lower_bound(*array, *array + n, value);
   if ( (pind != *array + n) && (*pind == value) )
      return (pind - *array);
   else
      return ( pind - *array - 1);
}

template<typename T>
struct CompareDesc {

   CompareDesc(T d) : fData(d) {}

   template<typename Index>
   bool operator()(Index i1, Index i2) {
      return *(fData + i1) > *(fData + i2);
   }

   T fData;
};

template<typename T>
struct CompareAsc {

   CompareAsc(T d) : fData(d) {}

   template<typename Index>
   bool operator()(Index i1, Index i2) {
      return *(fData + i1) < *(fData + i2);
   }

   T fData;
};

template <typename Iterator, typename IndexIterator>
void TMath::SortItr(Iterator first, Iterator last, IndexIterator index, Bool_t down)
{
   // Sort the n1 elements of the Short_t array defined by its
   // iterators.  In output the array index contains the indices of
   // the sorted array.  If down is false sort in increasing order
   // (default is decreasing order).

   // NOTE that the array index must be created with a length bigger
   // or equal than the main array before calling this function.

   int i = 0;

   IndexIterator cindex = index;
   for ( Iterator cfirst = first; cfirst != last; ++cfirst )
   {
      *cindex = i++;
      ++cindex;
   }

   if ( down )
      std::sort(index, cindex, CompareDesc<Iterator>(first) );
   else
      std::sort(index, cindex, CompareAsc<Iterator>(first) );
}

template <typename Element, typename Index> void TMath::Sort(Index n, const Element* a, Index* index, Bool_t down)
{
   // Sort the n elements of the  array a of generic templated type Element.
   // In output the array index of type Index contains the indices of the sorted array.
   // If down is false sort in increasing order (default is decreasing order).

   // NOTE that the array index must be created with a length >= n
   // before calling this function.
   // NOTE also that the size type for n must be the same type used for the index array
   // (templated type Index)

   for(Index i = 0; i < n; i++) { index[i] = i; }
   if ( down )
      std::sort(index, index + n, CompareDesc<const Element*>(a) );
   else
      std::sort(index, index + n, CompareAsc<const Element*>(a) );
}

#endif

/// \file ROOT/RSpan.h
/// \ingroup Base StdExt
/// \author Axel Naumann <axel@cern.ch>
/// \date 2015-09-06

/*************************************************************************
 * Copyright (C) 1995-2015, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_RSpan
#define ROOT_RSpan

//#include "RConfigure.h"

#ifdef R__HAS_STD_SPAN

#include <span>

#elif defined(R__HAS_STD_EXPERIMENTAL_SPAN)

#include <experimental/span>
namespace std {
  using template<class T> span = experimental::span<T>;

  // TODO: using make_view() overloads
}

#else
//# include "ROOT/span.hxx"
#endif

#endif

// @(#)root/foundation:
// Author: Axel Naumann, Enrico Guiraud, June 2017

/*************************************************************************
 * Copyright (C) 1995-2017, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TypeTraits
#define ROOT_TypeTraits

#include <memory> // shared_ptr, unique_ptr for IsSmartOrDumbPtr
#include <type_traits>
#include <vector> // for IsContainer
//#include "ROOT/RSpan.hxx" // for IsContainer

namespace ROOT {

/// ROOT type_traits extensions
namespace TypeTraits {
/// Lightweight storage for a collection of types.
/// Differently from std::tuple, no instantiation of objects of stored types is performed
template <typename... Types>
struct TypeList {
   static constexpr std::size_t list_size = sizeof...(Types);
};
} // end ns TypeTraits

namespace Detail {
template <typename T> constexpr auto HasCallOp(int /*goodOverload*/) -> decltype(&T::operator(), true) { return true; }
template <typename T> constexpr bool HasCallOp(char /*badOverload*/) { return false; }

/// Extract types from the signature of a callable object. See CallableTraits.
template <typename T, bool HasCallOp = ROOT::Detail::HasCallOp<T>(0)>
struct CallableTraitsImpl {};

// Extract signature of operator() and delegate to the appropriate CallableTraitsImpl overloads
template <typename T>
struct CallableTraitsImpl<T, true> {
   using arg_types = typename CallableTraitsImpl<decltype(&T::operator())>::arg_types;
   using arg_types_nodecay = typename CallableTraitsImpl<decltype(&T::operator())>::arg_types_nodecay;
   using ret_type = typename CallableTraitsImpl<decltype(&T::operator())>::ret_type;
};

// lambdas, std::function, const member functions
template <typename R, typename T, typename... Args>
struct CallableTraitsImpl<R (T::*)(Args...) const, false> {
   using arg_types = ROOT::TypeTraits::TypeList<typename std::decay<Args>::type...>;
   using arg_types_nodecay = ROOT::TypeTraits::TypeList<Args...>;
   using ret_type = R;
};

// mutable lambdas and functor classes, non-const member functions
template <typename R, typename T, typename... Args>
struct CallableTraitsImpl<R (T::*)(Args...), false> {
   using arg_types = ROOT::TypeTraits::TypeList<typename std::decay<Args>::type...>;
   using arg_types_nodecay = ROOT::TypeTraits::TypeList<Args...>;
   using ret_type = R;
};

// function pointers
template <typename R, typename... Args>
struct CallableTraitsImpl<R (*)(Args...), false> {
   using arg_types = ROOT::TypeTraits::TypeList<typename std::decay<Args>::type...>;
   using arg_types_nodecay = ROOT::TypeTraits::TypeList<Args...>;
   using ret_type = R;
};

// free functions
template <typename R, typename... Args>
struct CallableTraitsImpl<R(Args...), false> {
   using arg_types = ROOT::TypeTraits::TypeList<typename std::decay<Args>::type...>;
   using arg_types_nodecay = ROOT::TypeTraits::TypeList<Args...>;
   using ret_type = R;
};
} // end ns Detail

namespace TypeTraits {

///\class ROOT::TypeTraits::
template <class T>
class IsSmartOrDumbPtr : public std::integral_constant<bool, std::is_pointer<T>::value> {
};

template <class P>
class IsSmartOrDumbPtr<std::shared_ptr<P>> : public std::true_type {
};

template <class P>
class IsSmartOrDumbPtr<std::unique_ptr<P>> : public std::true_type {
};

/// Check for container traits.
template <typename T>
struct IsContainer {
   using Test_t = typename std::decay<T>::type;

   template <typename A>
   static constexpr bool Test(A *pt, A const *cpt = nullptr, decltype(pt->begin()) * = nullptr,
                              decltype(pt->end()) * = nullptr, decltype(cpt->begin()) * = nullptr,
                              decltype(cpt->end()) * = nullptr, typename A::iterator *pi = nullptr,
                              typename A::const_iterator *pci = nullptr)
   {
      using It_t = typename A::iterator;
      using CIt_t = typename A::const_iterator;
      using V_t = typename A::value_type;
      return std::is_same<Test_t, std::vector<bool>>::value ||
             (std::is_same<decltype(pt->begin()), It_t>::value && std::is_same<decltype(pt->end()), It_t>::value &&
              std::is_same<decltype(cpt->begin()), CIt_t>::value && std::is_same<decltype(cpt->end()), CIt_t>::value &&
              std::is_same<decltype(**pi), V_t &>::value && std::is_same<decltype(**pci), V_t const &>::value);
   }

   template <typename A>
   static constexpr bool Test(...)
   {
      return false;
   }

   static constexpr bool value = Test<Test_t>(nullptr);
};

template<typename T>
struct IsContainer<std::span<T>> {
   static constexpr bool value = true;
};

/// Checks for signed integers types that are not characters
template<class T>
struct IsSignedNumeral : std::integral_constant<bool,
   std::is_integral<T>::value &&
   std::is_signed<T>::value &&
   !std::is_same<T, char>::value
> {};

/// Checks for unsigned integer types that are not characters
template<class T>
struct IsUnsignedNumeral : std::integral_constant<bool,
   std::is_integral<T>::value &&
   !std::is_signed<T>::value &&
   !std::is_same<T, char>::value
> {};

/// Checks for floating point types (that are not characters)
template<class T>
using IsFloatNumeral = std::is_floating_point<T>;

/// Extract types from the signature of a callable object.
/// The `CallableTraits` struct contains three type aliases:
///   - arg_types: a `TypeList` of all types in the signature, decayed through std::decay
///   - arg_types_nodecay: a `TypeList` of all types in the signature, including cv-qualifiers
template<typename F>
using CallableTraits = ROOT::Detail::CallableTraitsImpl<F>;

// Return first of a variadic list of types.
template <typename T, typename... Rest>
struct TakeFirstType {
   using type = T;
};

template <typename... Types>
using TakeFirstType_t = typename TakeFirstType<Types...>::type;

// Remove first type from a variadic list of types, return a TypeList containing the rest.
// e.g. RemoveFirst_t<A,B,C> is TypeList<B,C>
template <typename T, typename... Rest>
struct RemoveFirst {
   using type = TypeList<Rest...>;
};

template <typename... Args>
using RemoveFirst_t = typename RemoveFirst<Args...>::type;

/// Return first of possibly many template parameters.
/// For non-template types, the result is void
/// e.g. TakeFirstParameter<U<A,B>> is A
///      TakeFirstParameter<T> is void
template <typename T>
struct TakeFirstParameter {
   using type = void;
};

template <template <typename...> class Template, typename T, typename... Rest>
struct TakeFirstParameter<Template<T, Rest...>> {
   using type = T;
};

template <typename T>
using TakeFirstParameter_t = typename TakeFirstParameter<T>::type;

/// Remove first of possibly many template parameters.
/// e.g. RemoveFirstParameter_t<U<A,B>> is U<B>
template <typename>
struct RemoveFirstParameter {
};

template <typename T, template <typename...> class U, typename... Rest>
struct RemoveFirstParameter<U<T, Rest...>> {
   using type = U<Rest...>;
};

template <typename T>
using RemoveFirstParameter_t = typename RemoveFirstParameter<T>::type;

template <typename T>
struct HasBeginAndEnd {

   template <typename V>
   using Begin_t = typename V::const_iterator (V::*)() const;

   template <typename V>
   using End_t = typename V::const_iterator (V::*)() const;

   template <typename V>
   static constexpr auto Check(int)
      -> decltype(static_cast<Begin_t<V>>(&V::begin), static_cast<End_t<V>>(&V::end), true)
   {
      return true;
   }

   template <typename V>
   static constexpr bool Check(...)
   {
      return false;
   }

   static constexpr bool const value = Check<T>(0);
};

} // ns TypeTraits
} // ns ROOT
#endif // ROOT_TTypeTraits

#ifndef ROOT_RConfigure
#define ROOT_RConfigure

/* Configurations file for linuxx8664gcc */
#ifdef R__HAVE_CONFIG
#define ROOTPREFIX    "$(ROOTSYS)"
#define ROOTBINDIR    "$(ROOTSYS)/bin"
#define ROOTLIBDIR    "$(ROOTSYS)/lib"
#define ROOTINCDIR    "$(ROOTSYS)/include"
#define ROOTETCDIR    "$(ROOTSYS)/etc"
#define ROOTDATADIR   "$(ROOTSYS)/."
#define ROOTDOCDIR    "$(ROOTSYS)/."
#define ROOTMACRODIR  "$(ROOTSYS)/macros"
#define ROOTTUTDIR    "$(ROOTSYS)/tutorials"
#define ROOTSRCDIR    "$(ROOTSYS)/src"
#define ROOTICONPATH  "$(ROOTSYS)/icons"
#define TTFFONTDIR    "$(ROOTSYS)/fonts"
#endif

#define EXTRAICONPATH ""

#define R__HAS_SETRESUID   /**/
#undef R__HAS_MATHMORE   /**/
#define R__HAS_PTHREAD    /**/
#define R__HAS_XFT    /**/
#undef R__HAS_COCOA    /**/
#undef R__HAS_VC    /**/
#define R__HAS_VDT    /**/
#undef R__HAS_VECCORE    /**/
#undef R__USE_CXXMODULES   /**/
#undef R__USE_LIBCXX    /**/
#undef R__HAS_STD_STRING_VIEW   /**/
#undef R__HAS_STD_EXPERIMENTAL_STRING_VIEW   /**/
#undef R__HAS_STOD_STRING_VIEW /**/
#undef R__HAS_STD_APPLY /**/
#undef R__HAS_STD_INVOKE /**/
#undef R__HAS_STD_INDEX_SEQUENCE /**/
#define R__HAS_ATTRIBUTE_ALWAYS_INLINE /**/
#define R__HAS_ATTRIBUTE_NOINLINE /**/
#undef R__EXTERN_LLVMDIR /**/
#define R__USE_IMT   /**/
#undef R__COMPLETE_MEM_TERMINATION /**/
#undef R__HAS_CEFWEB  /**/
#undef R__HAS_QT5WEB  /**/
#undef R__HAS_DAVIX  /**/

#if defined(R__HAS_VECCORE) && defined(R__HAS_VC)
#ifndef VECCORE_ENABLE_VC
#define VECCORE_ENABLE_VC
#endif
#endif

#undef R__HAS_DEFAULT_LZ4  /**/
#define R__HAS_DEFAULT_ZLIB  /**/
#undef R__HAS_DEFAULT_LZMA  /**/
#undef R__HAS_CLOUDFLARE_ZLIB /**/

#undef R__HAS_TMVACPU /**/
#undef R__HAS_TMVAGPU /**/


#endif

// -*- C++ -*-
// Author: Philippe Canal, March 2015

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef RStringView_H
#define RStringView_H

//#include "RConfigure.h"

#ifdef R__HAS_STD_STRING_VIEW

#include <string_view>

#else

# if defined(R__HAS_STD_EXPERIMENTAL_STRING_VIEW)
#  include <experimental/string_view>
# else
#  //include "RWrap_libcpp_string_view.h"
# endif

namespace std {

   template<class _CharT, class _Traits = std::char_traits<_CharT> >
   using basic_string_view = ::std::experimental::basic_string_view<_CharT,_Traits>;

   // basic_string_view typedef names
   typedef basic_string_view<char> string_view;
   typedef basic_string_view<char16_t> u16string_view;
   typedef basic_string_view<char32_t> u32string_view;
   typedef basic_string_view<wchar_t> wstring_view;

//   template<class _CharT, class _Traits = std::char_traits<_CharT> >
//   basic_string_view<_CharT,_Traits>
//   &operator=(basic_string_view<_CharT,_Traits> &lhs, const TString &rsh) {
//      *lhs = basic_string_view<_CharT,_Traits>(rsh);
//      return *lhs;
//   }

#ifndef R__HAS_STOD_STRING_VIEW
   inline double stod(std::string_view str, size_t *pos)
   {
      return std::stod(std::string(str.data(), str.size()),pos);
   }
#endif

}

#endif // ifdef else R__HAS_STD_STRING_VIEW

namespace ROOT {
namespace Internal {
    class TStringView {
       const char *fData{nullptr};
       size_t      fLength{0};

    public:
       explicit TStringView(const char *cstr, size_t len) : fData(cstr), fLength(len) {}

       operator std::string_view() const { return std::string_view(fData,fLength); }
    };
} // namespace Internal
} // namespace ROOT
#endif // RStringView_H

// @(#)root/base:$Id$
// Author: Fons Rademakers   04/08/95

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TString
#define ROOT_TString


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TString                                                              //
//                                                                      //
// Basic string class.                                                  //
//                                                                      //
// Cannot be stored in a TCollection... use TObjString instead.         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMathBase.h"

//#include "ROOT/RStringView.hxx"
//#include "ROOT/TypeTraits.hxx"

#include <iosfwd>
#include <stdarg.h>
#include <stdio.h>
#include <string>


class TString;
class TSubString;

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//  TSubString                                                          //
//                                                                      //
//  The TSubString class allows selected elements to be addressed.      //
//  There are no public constructors.                                   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
class TSubString {

friend class TString;

private:
   TString      &fStr;           // Referenced string
   Ssiz_t        fBegin;         // Index of starting character
   Ssiz_t        fExtent;        // Length of TSubString

   // NB: the only constructor is private
   TSubString(const TString &s, Ssiz_t start, Ssiz_t len);

public:
   TSubString(const TSubString &s)
     : fStr(s.fStr), fBegin(s.fBegin), fExtent(s.fExtent) { }

   void          ToLower();              // Convert self to lower-case
   void          ToUpper();              // Convert self to upper-case
};


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//  TString                                                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
class TString {

friend class TSubString;

private:

   TString();                           // Null string
   explicit TString(Ssiz_t ic);         // Suggested capacity
   TString(const TString &s);           // Copy constructor
   TString(TString &&s) noexcept;       // Move constructor
   TString(const char *s);              // Copy to embedded null
   TString(const char *s, Ssiz_t n);    // Copy past any embedded nulls
   TString(const std::string &s);
   TString(char c);
   TString(char c, Ssiz_t s);
   TString(const std::string_view &sub);
   TString(const TSubString &sub);

   virtual ~TString();

   // Assignment
   TString    &operator=(char s);                // Replace string
   TString    &operator=(const char *s);
   TString    &operator=(const TString &s);

   Bool_t       Contains(const char *pat,    ECaseCompare cmp = kExact) const;
   Bool_t       Contains(const TString &pat, ECaseCompare cmp = kExact) const;
   Bool_t       Contains(const TRegexp &pat) const;
   Bool_t       Contains(TPRegexp &pat) const;

   void         ToLower();                              // Change self to lower-case
   void         ToUpper();                              // Change self to upper-case

TString ToLower(const TString &s);    // Return lower-case version of argument
TString ToUpper(const TString &s);    // Return upper-case version of argument

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//  Inlines                                                             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

inline Bool_t TString::Contains(const TString &pat, ECaseCompare cmp) const
{ return Index(pat.Data(), pat.Length(), (Ssiz_t)0, cmp) != kNPOS; }

inline Bool_t TString::Contains(const char *s, ECaseCompare cmp) const
{ return Index(s, s ? strlen(s) : 0, (Ssiz_t)0, cmp) != kNPOS; }

inline Bool_t TString::Contains(const TRegexp &pat) const
{ return Index(pat, (Ssiz_t)0) != kNPOS; }

inline Bool_t TString::Contains(TPRegexp &pat) const
{ return Index(pat, (Ssiz_t)0) != kNPOS; }


#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDBasefwd
#define ROOT_TMatrixDBasefwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixDBase                                                         //
//                                                                      //
//  Forward declaration of TMatrixTBase<Double_t>                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixTBase;
typedef TMatrixTBase<Double_t> TMatrixDBase;

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixFBasefwd
#define ROOT_TMatrixFBasefwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixFBase                                                         //
//                                                                      //
//  Forward declaration of TMatrixTBase<Float_t>                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixTBase;
typedef TMatrixTBase<Float_t> TMatrixFBase;

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixTBase
#define ROOT_TMatrixTBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTBase                                                         //
//                                                                      //
// Template of base class in the linear algebra package                 //
//                                                                      //
//  matrix properties are stored here, however the data storage is part //
//  of the derived classes                                              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//======================================================================//
// Summary of the streamer version history                              //
//======================================================================//
//              3.10/02      4.00/a   4.00/b   4.00/c 4.00-08 5.05-1    //
// TMatrixFBase   -          2        2        2       4      5         //
// TMatrix        2          3        3        3       3      4         //
// TMatrixF       -          3        3        3       3      4         //
// TMatrixFSym    -          1        1        1       1      2         //
// TMatrixDSparse -          -        -        -       -      2         //
//                                                                      //
// TMatrixDBase   -          2        3        3       4      5         //
// TMatrixD       2          3        3        3       3      4         //
// TMatrixDSym    -          1        1        1       1      2         //
// TMatrixDSparse -          -        1        1       1      2         //
//                                                                      //
// TVector        2          3        3        3       3      4         //
// TVectorF       -          2        2        2       3      4         //
//                                                                      //
// TVectorD       2          2        2        2       3      4         //
//======================================================================//
//                                                                      //
// 4.00/a : (Jan 25 2004) introduced new classes/inheritance scheme,    //
//          TMatrix now inherits from TMatrixF                          //
//                                                                      //
//          TMatrixF::TMatrixFBase                                      //
//          TMatrixFSym::TMatrixFBase                                   //
//          TMatrixD::TMatrixDBase                                      //
//          TMatrixDSym::TMatrixDBase                                   //
//                                                                      //
// 4.00/b : (May 12 2004) introduced TMatrixDSparse and added new       //
//          element fNRowIndex to TMatrixFBase and TMatrixDBase         //
//          TMatrixDSparse::TMatrixDBase                                //
//                                                                      //
// 4.00/c : (May 27 2004) Used the TObject::fBits to store validity     //
//           state for vectors and matrices                             //
//                                                                      //
// 5.05-1 :  templates TMatrixTBase,TMatrixT,TMatrixTSym and            //
//           TMatrixTSparse were introduced, all versions were          //
//           increased by 1 .                                           //
//                                                                      //
//======================================================================//

//#include "TError.h"
//#include "TObject.h"
//#include "TMathBase.h"
//#include "TMatrixFBasefwd.h"
//#include "TMatrixDBasefwd.h"
//#include "TString.h"
//#include "TVectorFfwd.h"
//#include "TVectorDfwd.h"

#include <limits>

template<class Element> class TVectorT;
template<class Element> class TElementActionT;
template<class Element> class TElementPosActionT;

R__EXTERN Int_t gMatrixCheck;

template<class Element> class TMatrixTBase : public TObject {

private:
   Element *GetElements();  // This function is now obsolete (and is not implemented) you should use TMatrix::GetMatrixArray().

protected:
   Int_t    fNrows;               // number of rows
   Int_t    fNcols;               // number of columns
   Int_t    fRowLwb;              // lower bound of the row index
   Int_t    fColLwb;              // lower bound of the col index
   Int_t    fNelems;              // number of elements in matrix
   Int_t    fNrowIndex;           // length of row index array (= fNrows+1) wich is only used for sparse matrices

   Element  fTol;                 // sqrt(epsilon); epsilon is smallest number number so that  1+epsilon > 1
                                  //  fTol is used in matrix decomposition (like in inversion)

   Bool_t   fIsOwner;             //!default kTRUE, when Use array kFALSE

   static  void DoubleLexSort (Int_t n,Int_t *first,Int_t *second,Element *data);
   static  void IndexedLexSort(Int_t n,Int_t *first,Int_t swapFirst,
                               Int_t *second,Int_t swapSecond,Int_t *index);

   enum {kSizeMax = 25};          // size data container on stack, see New_m(),Delete_m()
   enum {kWorkMax = 100};         // size of work array's in several routines

   enum EMatrixStatusBits {
     kStatus = BIT(14) // set if matrix object is valid
   };

public:

   TMatrixTBase():
     fNrows(0), fNcols(0), fRowLwb(0), fColLwb(0), fNelems(0), fNrowIndex(0),
     fTol(0), fIsOwner(kTRUE) { }

   virtual ~TMatrixTBase() {}

           inline       Int_t     GetRowLwb     () const { return fRowLwb; }
           inline       Int_t     GetRowUpb     () const { return fNrows+fRowLwb-1; }
           inline       Int_t     GetNrows      () const { return fNrows; }
           inline       Int_t     GetColLwb     () const { return fColLwb; }
           inline       Int_t     GetColUpb     () const { return fNcols+fColLwb-1; }
           inline       Int_t     GetNcols      () const { return fNcols; }
           inline       Int_t     GetNoElements () const { return fNelems; }
           inline       Element   GetTol        () const { return fTol; }

   virtual        const Element  *GetMatrixArray  () const = 0;
   virtual              Element  *GetMatrixArray  ()       = 0;
   virtual        const Int_t    *GetRowIndexArray() const = 0;
   virtual              Int_t    *GetRowIndexArray()       = 0;
   virtual        const Int_t    *GetColIndexArray() const = 0;
   virtual              Int_t    *GetColIndexArray()       = 0;

   virtual              TMatrixTBase<Element> &SetRowIndexArray(Int_t *data) = 0;
   virtual              TMatrixTBase<Element> &SetColIndexArray(Int_t *data) = 0;
   virtual              TMatrixTBase<Element> &SetMatrixArray  (const Element *data,Option_t *option="");
           inline       Element                SetTol          (Element tol);

   virtual void   Clear      (Option_t *option="") = 0;

   inline  void   Invalidate ()       { SetBit(kStatus); }
   inline  void   MakeValid  ()       { ResetBit(kStatus); }
   inline  Bool_t IsValid    () const { return !TestBit(kStatus); }
   inline  Bool_t IsOwner    () const { return fIsOwner; }
   virtual Bool_t IsSymmetric() const;

   virtual TMatrixTBase<Element> &GetSub(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                         TMatrixTBase<Element> &target,Option_t *option="S") const = 0;
   virtual TMatrixTBase<Element> &SetSub(Int_t row_lwb,Int_t col_lwb,const TMatrixTBase<Element> &source) = 0;

   virtual void                   GetMatrix2Array(Element *data,Option_t *option="") const;
   virtual TMatrixTBase<Element> &InsertRow      (Int_t row,Int_t col,const Element *v,Int_t n = -1);
   virtual void                   ExtractRow     (Int_t row,Int_t col,      Element *v,Int_t n = -1) const;

   virtual TMatrixTBase<Element> &Shift          (Int_t row_shift,Int_t col_shift);
   virtual TMatrixTBase<Element> &ResizeTo       (Int_t nrows,Int_t ncols,Int_t nr_nonzeros=-1) = 0;
   virtual TMatrixTBase<Element> &ResizeTo       (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Int_t nr_nonzeros=-1) = 0;

   virtual Double_t Determinant() const                          { AbstractMethod("Determinant()"); return 0.; }
   virtual void     Determinant(Double_t &d1,Double_t &d2) const { AbstractMethod("Determinant()"); d1 = 0.; d2 = 0.; }

   virtual TMatrixTBase<Element> &Zero       ();
   virtual TMatrixTBase<Element> &Abs        ();
   virtual TMatrixTBase<Element> &Sqr        ();
   virtual TMatrixTBase<Element> &Sqrt       ();
   virtual TMatrixTBase<Element> &UnitMatrix ();

   virtual TMatrixTBase<Element> &NormByDiag (const TVectorT<Element> &v,Option_t *option="D");

   virtual Element RowNorm    () const;
   virtual Element ColNorm    () const;
   virtual Element E2Norm     () const;
   inline  Element NormInf    () const { return RowNorm(); }
   inline  Element Norm1      () const { return ColNorm(); }
   virtual Int_t   NonZeros   () const;
   virtual Element Sum        () const;
   virtual Element Min        () const;
   virtual Element Max        () const;

   //void Draw (Option_t *option="");       // *MENU*
   void Print(Option_t *name  ="") const; // *MENU*

   virtual Element   operator()(Int_t rown,Int_t coln) const = 0;
   virtual Element  &operator()(Int_t rown,Int_t coln)       = 0;

   Bool_t operator==(Element val) const;
   Bool_t operator!=(Element val) const;
   Bool_t operator< (Element val) const;
   Bool_t operator<=(Element val) const;
   Bool_t operator> (Element val) const;
   Bool_t operator>=(Element val) const;

   virtual TMatrixTBase<Element> &Apply(const TElementActionT<Element>    &action);
   virtual TMatrixTBase<Element> &Apply(const TElementPosActionT<Element> &action);

   virtual TMatrixTBase<Element> &Randomize(Element alpha,Element beta,Double_t &seed);

   // make it public since it can be called by TMatrixTRow
   static Element & NaNValue();

   ClassDef(TMatrixTBase,5) // Matrix base class (template)
};

#ifndef __CLING__
// When building with -fmodules, it instantiates all pending instantiations,
// instead of delaying them until the end of the translation unit.
// We 'got away with' probably because the use and the definition of the
// explicit specialization do not occur in the same TU.
//
// In case we are building with -fmodules, we need to forward declare the
// specialization in order to compile the dictionary G__Matrix.cxx.
template <> TClass *TMatrixTBase<double>::Class();
#endif // __CLING__


template<class Element> Element TMatrixTBase<Element>::SetTol(Element newTol)
{
   const Element  oldTol = fTol;
   if (newTol >= 0.0)
      fTol = newTol;
   return oldTol;
}

template<class Element> Bool_t  operator==   (const TMatrixTBase<Element>  &m1,const TMatrixTBase<Element>  &m2);
template<class Element> Element E2Norm       (const TMatrixTBase<Element>  &m1,const TMatrixTBase<Element>  &m2);
template<class Element1,class Element2>
                        Bool_t  AreCompatible(const TMatrixTBase<Element1> &m1,const TMatrixTBase<Element2> &m2,Int_t verbose=0);
template<class Element> void    Compare      (const TMatrixTBase<Element>  &m1,const TMatrixTBase<Element>  &m2);

// Service functions (useful in the verification code).
// They print some detail info if the validation condition fails

template<class Element> Bool_t VerifyMatrixValue   (const TMatrixTBase<Element> &m,Element val,
                                                    Int_t verbose,Element maxDevAllow);
template<class Element> Bool_t VerifyMatrixValue   (const TMatrixTBase<Element> &m,Element val,Int_t verbose)
                                                                           { return VerifyMatrixValue(m,val,verbose,Element(0.)); }
template<class Element> Bool_t VerifyMatrixValue   (const TMatrixTBase<Element> &m,Element val)
                                                                           { return VerifyMatrixValue(m,val,1,Element(0.)); }
template<class Element> Bool_t VerifyMatrixIdentity(const TMatrixTBase<Element> &m1,const TMatrixTBase<Element> &m2,
                                                    Int_t verbose,Element maxDevAllow);
template<class Element> Bool_t VerifyMatrixIdentity(const TMatrixTBase<Element> &m1,const TMatrixTBase<Element> &m2,Int_t verbose)
                                                                           { return VerifyMatrixIdentity(m1,m2,verbose,Element(0.)); }
template<class Element> Bool_t VerifyMatrixIdentity(const TMatrixTBase<Element> &m1,const TMatrixTBase<Element> &m2)
                                                                           { return VerifyMatrixIdentity(m1,m2,1,Element(0.)); }

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixTUtils
#define ROOT_TMatrixTUtils

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Matrix utility classes.                                              //
//                                                                      //
// Templates of utility classes in the Linear Algebra Package.          //
// The following classes are defined here:                              //
//                                                                      //
// Different matrix views without copying data elements :               //
//   TMatrixTRow_const        TMatrixTRow                               //
//   TMatrixTColumn_const     TMatrixTColumn                            //
//   TMatrixTDiag_const       TMatrixTDiag                              //
//   TMatrixTFlat_const       TMatrixTFlat                              //
//   TMatrixTSub_const        TMatrixTSub                               //
//   TMatrixTSparseRow_const  TMatrixTSparseRow                         //
//   TMatrixTSparseDiag_const TMatrixTSparseDiag                        //
//                                                                      //
//   TElementActionT                                                    //
//   TElementPosActionT                                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixTBase.h"

#include <initializer_list>

template<class Element> class TVectorT;
template<class Element> class TMatrixT;
template<class Element> class TMatrixTSym;
template<class Element> class TMatrixTSparse;

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TElementActionT                                                      //
//                                                                      //
// A class to do a specific operation on every vector or matrix element //
// (regardless of it position) as the object is being traversed.        //
// This is an abstract class. Derived classes need to implement the     //
// action function Operation().                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TElementActionT {

#ifndef __CINT__
friend class TMatrixTBase  <Element>;
friend class TMatrixT      <Element>;
friend class TMatrixTSym   <Element>;
friend class TMatrixTSparse<Element>;
friend class TVectorT      <Element>;
#endif

protected:
   virtual ~TElementActionT() { }
   virtual void Operation(Element &element) const = 0;

private:
   TElementActionT& operator=(const TElementActionT<Element> &) {return *this;}
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TElementPosActionT                                                   //
//                                                                      //
// A class to do a specific operation on every vector or matrix element //
// as the object is being traversed. This is an abstract class.         //
// Derived classes need to implement the action function Operation().   //
// In the action function the location of the current element is        //
// known (fI=row, fJ=columns).                                          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TElementPosActionT {

#ifndef __CINT__
friend class TMatrixTBase  <Element>;
friend class TMatrixT      <Element>;
friend class TMatrixTSym   <Element>;
friend class TMatrixTSparse<Element>;
friend class TVectorT      <Element>;
#endif

protected:
   mutable Int_t fI; // i position of element being passed to Operation()
   mutable Int_t fJ; // j position of element being passed to Operation()
   virtual ~TElementPosActionT() { }
   virtual void Operation(Element &element) const = 0;

private:
   TElementPosActionT<Element>& operator=(const TElementPosActionT<Element> &) {return *this;}
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTRow_const                                                    //
//                                                                      //
// Template class represents a row of a TMatrixT/TMatrixTSym            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTRow_const {

protected:
   const TMatrixTBase<Element> *fMatrix;  //  the matrix I am a row of
         Int_t                  fRowInd;  //  effective row index
         Int_t                  fInc;     //  if ptr = @a[row,i], then ptr+inc = @a[row,i+1]
   const Element               *fPtr;     //  pointer to the a[row,0]

public:
   TMatrixTRow_const() { fMatrix = 0; fRowInd = 0; fInc = 0; fPtr = 0; }
   TMatrixTRow_const(const TMatrixT   <Element> &matrix,Int_t row);
   TMatrixTRow_const(const TMatrixTSym<Element> &matrix,Int_t row);
  TMatrixTRow_const(const TMatrixTRow_const<Element>& trc):
    fMatrix(trc.fMatrix), fRowInd(trc.fRowInd), fInc(trc.fInc), fPtr(trc.fPtr) { }
  TMatrixTRow_const<Element>& operator=(const TMatrixTRow_const<Element>& trc) {
    if(this != &trc) { fMatrix=trc.fMatrix; fRowInd=trc.fRowInd; fInc=trc.fInc; fPtr=trc.fPtr; } return *this;}
   virtual ~TMatrixTRow_const() { }

   inline const TMatrixTBase<Element> *GetMatrix  () const { return fMatrix; }
   inline       Int_t                  GetRowIndex() const { return fRowInd; }
   inline       Int_t                  GetInc     () const { return fInc; }
   inline const Element               *GetPtr     () const { return fPtr; }
   inline const Element               &operator   ()(Int_t i) const {
      if (!fMatrix) return TMatrixTBase<Element>::NaNValue();
      R__ASSERT(fMatrix->IsValid());
      const Int_t acoln = i-fMatrix->GetColLwb();
      if (acoln < fMatrix->GetNcols() && acoln >= 0)
         return fPtr[acoln];
      else {
         //Error("operator()","Request col(%d) outside matrix range of %d - %d",
          //                  i,fMatrix->GetColLwb(),fMatrix->GetColLwb()+fMatrix->GetNcols());
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline const Element               &operator   [](Int_t i) const { return (*(const TMatrixTRow_const<Element> *)this)(i); }

   ClassDef(TMatrixTRow_const,0)  // Template of General Matrix Row Access class
};

template<class Element> class TMatrixTRow : public TMatrixTRow_const<Element> {

public:
   TMatrixTRow() {}
   TMatrixTRow(TMatrixT   <Element> &matrix,Int_t row);
   TMatrixTRow(TMatrixTSym<Element> &matrix,Int_t row);
   TMatrixTRow(const TMatrixTRow<Element> &mr);

   inline Element *GetPtr() const { return const_cast<Element *>(this->fPtr); }

   inline const Element &operator()(Int_t i) const {
      if (!this->fMatrix) return TMatrixTBase<Element>::NaNValue();
      R__ASSERT(this->fMatrix->IsValid());
      const Int_t acoln = i-this->fMatrix->GetColLwb();
      if (acoln < this->fMatrix->GetNcols() || acoln >= 0)
         return (this->fPtr)[acoln];
      else {
         //Error("operator()","Request col(%d) outside matrix range of %d - %d",
            //                i,this->fMatrix->GetColLwb(),this->fMatrix->GetColLwb()+this->fMatrix->GetNcols());
         return TMatrixTBase<Element>::NaNValue();
     }
   }
   inline       Element &operator()(Int_t i) {
      if (!this->fMatrix) return TMatrixTBase<Element>::NaNValue();
      R__ASSERT(this->fMatrix->IsValid());
      const Int_t acoln = i-this->fMatrix->GetColLwb();
      if (acoln < this->fMatrix->GetNcols() && acoln >= 0)
         return (const_cast<Element *>(this->fPtr))[acoln];
      else {
         //Error("operator()","Request col(%d) outside matrix range of %d - %d",
          //                  i,this->fMatrix->GetColLwb(),this->fMatrix->GetColLwb()+this->fMatrix->GetNcols());
         //return (const_cast<Element *>(this->fPtr))[0];
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline const Element &operator[](Int_t i) const { return (*(const TMatrixTRow<Element> *)this)(i); }
   inline       Element &operator[](Int_t i)       { return (*(      TMatrixTRow<Element> *)this)(i); }

   void Assign (Element  val);
   void operator= (std::initializer_list<Element>  l);
   void operator+=(Element val);
   void operator*=(Element val);

   void operator=(const TMatrixTRow_const<Element> &r);
   TMatrixTRow<Element>& operator=(const TMatrixTRow      <Element> &r) { operator=((TMatrixTRow_const<Element> &)r); return *this;}
   void operator=(const TVectorT         <Element> &vec);

   void operator+=(const TMatrixTRow_const<Element> &r);
   void operator*=(const TMatrixTRow_const<Element> &r);

   ClassDef(TMatrixTRow,0)  // Template of General Matrix Row Access class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTColumn_const                                                 //
//                                                                      //
// Template class represents a column of a TMatrixT/TMatrixTSym         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTColumn_const {

protected:
   const TMatrixTBase<Element> *fMatrix;  //  the matrix I am a column of
         Int_t                  fColInd;  //  effective column index
         Int_t                  fInc;     //  if ptr = @a[i,col], then ptr+inc = @a[i+1,col]
   const Element               *fPtr;     //  pointer to the a[0,col] column

public:
   TMatrixTColumn_const() { fMatrix = 0; fColInd = 0; fInc = 0; fPtr = 0; }
   TMatrixTColumn_const(const TMatrixT   <Element> &matrix,Int_t col);
   TMatrixTColumn_const(const TMatrixTSym<Element> &matrix,Int_t col);
   TMatrixTColumn_const(const TMatrixTColumn_const<Element>& trc):
     fMatrix(trc.fMatrix), fColInd(trc.fColInd), fInc(trc.fInc), fPtr(trc.fPtr) { }
   TMatrixTColumn_const<Element>& operator=(const TMatrixTColumn_const<Element>& trc) {
     if(this != &trc) { fMatrix=trc.fMatrix; fColInd=trc.fColInd; fInc=trc.fInc; fPtr=trc.fPtr; } return *this;}
   virtual ~TMatrixTColumn_const() { }

   inline const TMatrixTBase <Element> *GetMatrix  () const { return fMatrix; }
   inline       Int_t                   GetColIndex() const { return fColInd; }
   inline       Int_t                   GetInc     () const { return fInc; }
   inline const Element                *GetPtr     () const { return fPtr; }
   inline const Element                &operator   ()(Int_t i) const {
      if (!this->fMatrix) return TMatrixTBase<Element>::NaNValue();
      R__ASSERT(fMatrix->IsValid());
      const Int_t arown = i-fMatrix->GetRowLwb();
      if (arown < fMatrix->GetNrows() && arown >= 0)
         return fPtr[arown*fInc];
      else {
         //Error("operator()","Request row(%d) outside matrix range of %d - %d",
             //               i,fMatrix->GetRowLwb(),fMatrix->GetRowLwb()+fMatrix->GetNrows());
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline const Element                &operator [](Int_t i) const { return (*(const TMatrixTColumn_const<Element> *)this)(i); }

   ClassDef(TMatrixTColumn_const,0)  // Template of General Matrix Column Access class
};

template<class Element> class TMatrixTColumn : public TMatrixTColumn_const<Element> {

public:
   TMatrixTColumn() {}
   TMatrixTColumn(TMatrixT   <Element>&matrix,Int_t col);
   TMatrixTColumn(TMatrixTSym<Element>&matrix,Int_t col);
   TMatrixTColumn(const TMatrixTColumn <Element>&mc);

   inline Element *GetPtr() const { return const_cast<Element *>(this->fPtr); }

   inline const Element &operator()(Int_t i) const {
      if (!this->fMatrix) return TMatrixTBase<Element>::NaNValue();
      R__ASSERT(this->fMatrix->IsValid());
      const Int_t arown = i-this->fMatrix->GetRowLwb();
      if (arown < this->fMatrix->GetNrows() && arown >= 0)
         return (this->fPtr)[arown*this->fInc];
      else {
         //Error("operator()","Request row(%d) outside matrix range of %d - %d",
             //               i,this->fMatrix->GetRowLwb(),this->fMatrix->GetRowLwb()+this->fMatrix->GetNrows());
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline       Element &operator()(Int_t i) {
      if (!this->fMatrix) return TMatrixTBase<Element>::NaNValue();
      R__ASSERT(this->fMatrix->IsValid());
      const Int_t arown = i-this->fMatrix->GetRowLwb();

      if (arown < this->fMatrix->GetNrows() && arown >= 0)
         return (const_cast<Element *>(this->fPtr))[arown*this->fInc];
      else {
         //Error("operator()","Request row(%d) outside matrix range of %d - %d",
             //               i,this->fMatrix->GetRowLwb(),this->fMatrix->GetRowLwb()+this->fMatrix->GetNrows());
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline const Element &operator[](Int_t i) const { return (*(const TMatrixTColumn<Element> *)this)(i); }
   inline       Element &operator[](Int_t i)       { return (*(      TMatrixTColumn<Element> *)this)(i); }

   void Assign (Element val);
   // keep it for backward compatibility (but it has been removed for TMatrixTRow)
   void operator= (Element val) { return Assign(val); }
   void operator= (std::initializer_list<Element>  l);
   void operator+=(Element val);
   void operator*=(Element val);

   void operator=(const TMatrixTColumn_const<Element> &c);
   TMatrixTColumn<Element>& operator=(const TMatrixTColumn <Element> &c) { operator=((TMatrixTColumn_const<Element> &)c); return *this;}
   void operator=(const TVectorT            <Element> &vec);

   void operator+=(const TMatrixTColumn_const<Element> &c);
   void operator*=(const TMatrixTColumn_const<Element> &c);

   ClassDef(TMatrixTColumn,0)  // Template of General Matrix Column Access class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTDiag_const                                                   //
//                                                                      //
// Template class represents the diagonal of a TMatrixT/TMatrixTSym     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTDiag_const {

protected:
   const TMatrixTBase<Element> *fMatrix;  //  the matrix I am the diagonal of
         Int_t                  fInc;     //  if ptr=@a[i,i], then ptr+inc = @a[i+1,i+1]
         Int_t                  fNdiag;   //  number of diag elems, min(nrows,ncols)
   const Element               *fPtr;     //  pointer to the a[0,0]

public:
   TMatrixTDiag_const() { fMatrix = 0; fInc = 0; fNdiag = 0; fPtr = 0; }
   TMatrixTDiag_const(const TMatrixT   <Element> &matrix);
   TMatrixTDiag_const(const TMatrixTSym<Element> &matrix);
   TMatrixTDiag_const(const TMatrixTDiag_const<Element>& trc):
    fMatrix(trc.fMatrix), fInc(trc.fInc), fNdiag(trc.fNdiag), fPtr(trc.fPtr) { }
   TMatrixTDiag_const<Element>& operator=(const TMatrixTDiag_const<Element>& trc) {
      if(this != &trc) { fMatrix=trc.fMatrix; fInc=trc.fInc; fNdiag=trc.fNdiag; fPtr=trc.fPtr; } return *this;}
   virtual ~TMatrixTDiag_const() { }

   inline const TMatrixTBase<Element> *GetMatrix() const { return fMatrix; }
   inline const Element               *GetPtr   () const { return fPtr; }
   inline       Int_t                  GetInc   () const { return fInc; }
   inline const Element               &operator ()(Int_t i) const {
      R__ASSERT(fMatrix->IsValid());
      if (i < fNdiag && i >= 0)
         return fPtr[i*fInc];
      else {
         //Error("operator()","Request diagonal(%d) outside matrix range of 0 - %d",i,fNdiag);
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline const Element               &operator [](Int_t i) const { return (*(const TMatrixTDiag_const<Element> *)this)(i); }

   Int_t GetNdiags() const { return fNdiag; }

   ClassDef(TMatrixTDiag_const,0)  // Template of General Matrix Diagonal Access class
};

template<class Element> class TMatrixTDiag : public TMatrixTDiag_const<Element> {

public:
   TMatrixTDiag() {}
   TMatrixTDiag(TMatrixT   <Element>&matrix);
   TMatrixTDiag(TMatrixTSym<Element>&matrix);
   TMatrixTDiag(const TMatrixTDiag<Element> &md);

   inline Element *GetPtr() const { return const_cast<Element *>(this->fPtr); }

   inline const Element &operator()(Int_t i) const {
      R__ASSERT(this->fMatrix->IsValid());
      if (i < this->fNdiag && i >= 0)
         return (this->fPtr)[i*this->fInc];
      else {
         //Error("operator()","Request diagonal(%d) outside matrix range of 0 - %d",i,this->fNdiag);
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline       Element &operator()(Int_t i) {
      R__ASSERT(this->fMatrix->IsValid());
      if (i < this->fNdiag && i >= 0)
         return (const_cast<Element *>(this->fPtr))[i*this->fInc];
      else {
         //Error("operator()","Request diagonal(%d) outside matrix range of 0 - %d",i,this->fNdiag);
         return (const_cast<Element *>(this->fPtr))[0];
      }
   }
   inline const Element &operator[](Int_t i) const { return (*(const TMatrixTDiag<Element> *)this)(i); }
   inline       Element &operator[](Int_t i)       { return (*(      TMatrixTDiag *)this)(i); }

   void operator= (Element val);
   void operator+=(Element val);
   void operator*=(Element val);

   void operator=(const TMatrixTDiag_const<Element> &d);
   TMatrixTDiag<Element>& operator=(const TMatrixTDiag <Element> &d) { operator=((TMatrixTDiag_const<Element> &)d); return *this;}
   void operator=(const TVectorT          <Element> &vec);

   void operator+=(const TMatrixTDiag_const<Element> &d);
   void operator*=(const TMatrixTDiag_const<Element> &d);

   ClassDef(TMatrixTDiag,0)  // Template of General Matrix Diagonal Access class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTFlat_const                                                   //
//                                                                      //
// Template class represents a flat TMatrixT/TMatrixTSym                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTFlat_const {

protected:
   const TMatrixTBase<Element> *fMatrix;  //  the matrix I am the diagonal of
         Int_t                  fNelems;  //
   const Element               *fPtr;     //  pointer to the a[0,0]

public:
   TMatrixTFlat_const() { fMatrix = 0; fNelems = 0; fPtr = 0; }
   TMatrixTFlat_const(const TMatrixT   <Element> &matrix);
   TMatrixTFlat_const(const TMatrixTSym<Element> &matrix);
   TMatrixTFlat_const(const TMatrixTFlat_const<Element>& trc):
     fMatrix(trc.fMatrix), fNelems(trc.fNelems), fPtr(trc.fPtr) { }
   TMatrixTFlat_const<Element>& operator=(const TMatrixTFlat_const<Element>& trc) {
      if(this != &trc) { fMatrix=trc.fMatrix; fNelems=trc.fNelems; fPtr=trc.fPtr; } return *this;}
   virtual ~TMatrixTFlat_const() { }

   inline const TMatrixTBase<Element> *GetMatrix() const { return fMatrix; }
   inline const Element               *GetPtr   () const { return fPtr; }
   inline const Element               &operator ()(Int_t i) const {
      R__ASSERT(fMatrix->IsValid());
      if (i < fNelems && i >= 0)
         return fPtr[i];
      else {
         //Error("operator()","Request element(%d) outside matrix range of 0 - %d",i,fNelems);
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline const Element               &operator [](Int_t i) const { return (*(const TMatrixTFlat_const<Element> *)this)(i); }

   ClassDef(TMatrixTFlat_const,0)  // Template of General Matrix Flat Representation class
};

template<class Element> class TMatrixTFlat : public TMatrixTFlat_const<Element> {

public:
   TMatrixTFlat() {}
   TMatrixTFlat(TMatrixT   <Element> &matrix);
   TMatrixTFlat(TMatrixTSym<Element> &matrix);
   TMatrixTFlat(const TMatrixTFlat<Element> &mf);

   inline Element *GetPtr() const { return const_cast<Element *>(this->fPtr); }

   inline const Element &operator()(Int_t i) const {
      R__ASSERT(this->fMatrix->IsValid());
      if (i < this->fNelems && i >= 0)
         return (this->fPtr)[i];
      else {
         //Error("operator()","Request element(%d) outside matrix range of 0 - %d",i,this->fNelems);
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline       Element &operator()(Int_t i) {
      R__ASSERT(this->fMatrix->IsValid());
      if (i < this->fNelems && i >= 0)
         return (const_cast<Element *>(this->fPtr))[i];
      else {
         //Error("operator()","Request element(%d) outside matrix range of 0 - %d",i,this->fNelems);
         return TMatrixTBase<Element>::NaNValue();
      }
   }
   inline const Element &operator[](Int_t i) const { return (*(const TMatrixTFlat<Element> *)this)(i); }
   inline       Element &operator[](Int_t i)       { return (*(      TMatrixTFlat<Element> *)this)(i); }

   void operator= (Element val);
   void operator+=(Element val);
   void operator*=(Element val);

   void operator=(const TMatrixTFlat_const<Element> &f);
   TMatrixTFlat<Element>& operator=(const TMatrixTFlat <Element> &f) { operator=((TMatrixTFlat_const<Element> &)f); return *this;}
   void operator=(const TVectorT          <Element> &vec);

   void operator+=(const TMatrixTFlat_const<Element> &f);
   void operator*=(const TMatrixTFlat_const<Element> &f);

   ClassDef(TMatrixTFlat,0)  // Template of General Matrix Flat Representation class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTSub_const                                                    //
//                                                                      //
// Template class represents a sub matrix of TMatrixT/TMatrixTSym       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTSub_const {

protected:
   const TMatrixTBase<Element> *fMatrix;    //  the matrix I am a submatrix of
         Int_t                  fRowOff;    //
         Int_t                  fColOff;    //
         Int_t                  fNrowsSub;  //
         Int_t                  fNcolsSub;  //

public:
   TMatrixTSub_const() { fRowOff = fColOff = fNrowsSub = fNcolsSub = 0; fMatrix = 0; }
   TMatrixTSub_const(const TMatrixT   <Element> &matrix,Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb);
   TMatrixTSub_const(const TMatrixTSym<Element> &matrix,Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb);
   virtual ~TMatrixTSub_const() { }

   inline const TMatrixTBase<Element> *GetMatrix() const { return fMatrix; }
   inline       Int_t                  GetRowOff() const { return fRowOff; }
   inline       Int_t                  GetColOff() const { return fColOff; }
   inline       Int_t                  GetNrows () const { return fNrowsSub; }
   inline       Int_t                  GetNcols () const { return fNcolsSub; }
   inline const Element               &operator ()(Int_t rown,Int_t coln) const {
      R__ASSERT(fMatrix->IsValid());

      const Element *ptr = fMatrix->GetMatrixArray();
      if (rown >= fNrowsSub || rown < 0) {
         //Error("operator()","Request row(%d) outside matrix range of 0 - %d",rown,fNrowsSub);
         return TMatrixTBase<Element>::NaNValue();
      }
      if (coln >= fNcolsSub || coln < 0) {
         //Error("operator()","Request column(%d) outside matrix range of 0 - %d",coln,fNcolsSub);
         return TMatrixTBase<Element>::NaNValue();
      }
      const Int_t index = (rown+fRowOff)*fMatrix->GetNcols()+coln+fColOff;
      return ptr[index];
   }

   ClassDef(TMatrixTSub_const,0)  // Template of Sub Matrix Access class
};

template<class Element> class TMatrixTSub : public TMatrixTSub_const<Element> {

public:

   enum {kWorkMax = 100};

   TMatrixTSub() {}
   TMatrixTSub(TMatrixT   <Element> &matrix,Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb);
   TMatrixTSub(TMatrixTSym<Element> &matrix,Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb);
   TMatrixTSub(const TMatrixTSub<Element> &ms);

   inline Element &operator()(Int_t rown,Int_t coln) {
      R__ASSERT(this->fMatrix->IsValid());

      const Element *ptr = this->fMatrix->GetMatrixArray();
      if (rown >= this->fNrowsSub || rown < 0) {
         //Error("operator()","Request row(%d) outside matrix range of 0 - %d",rown,this->fNrowsSub);
         return TMatrixTBase<Element>::NaNValue();
      }
      if (coln >= this->fNcolsSub || coln < 0) {
         //Error("operator()","Request column(%d) outside matrix range of 0 - %d",coln,this->fNcolsSub);
         return TMatrixTBase<Element>::NaNValue();
      }
      const Int_t index = (rown+this->fRowOff)*this->fMatrix->GetNcols()+coln+this->fColOff;
      return (const_cast<Element *>(ptr))[index];
   }

   void Rank1Update(const TVectorT<Element> &vec,Element alpha=1.0);

   void operator= (Element val);
   void operator+=(Element val);
   void operator*=(Element val);

   void operator=(const TMatrixTSub_const<Element> &s);
   TMatrixTSub<Element>& operator=(const TMatrixTSub <Element> &s) { operator=((TMatrixTSub_const<Element> &)s); return *this;}
   void operator=(const TMatrixTBase     <Element> &m);

   void operator+=(const TMatrixTSub_const<Element> &s);
   void operator*=(const TMatrixTSub_const<Element> &s);
   void operator+=(const TMatrixTBase     <Element> &m);
   void operator*=(const TMatrixT         <Element> &m);
   void operator*=(const TMatrixTSym      <Element> &m);

   ClassDef(TMatrixTSub,0)  // Template of Sub Matrix Access class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTSparseRow_const                                              //
//                                                                      //
// Template class represents a row of TMatrixTSparse                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTSparseRow_const {

protected:
   const TMatrixTSparse<Element> *fMatrix;  // the matrix I am a row of
         Int_t                  fRowInd;  // effective row index
         Int_t                  fNindex;  // index range
   const Int_t                 *fColPtr;  // column index pointer
   const Element               *fDataPtr; // data pointer

public:
   TMatrixTSparseRow_const() { fMatrix = 0; fRowInd = 0; fNindex = 0; fColPtr = 0; fDataPtr = 0; }
   TMatrixTSparseRow_const(const TMatrixTSparse<Element> &matrix,Int_t row);
   TMatrixTSparseRow_const(const TMatrixTSparseRow_const<Element>& trc):
     fMatrix(trc.fMatrix), fRowInd(trc.fRowInd), fNindex(trc.fNindex), fColPtr(trc.fColPtr), fDataPtr(trc.fDataPtr) { }
   TMatrixTSparseRow_const<Element>& operator=(const TMatrixTSparseRow_const<Element>& trc) {
     if(this != &trc) { fMatrix=trc.fMatrix; fRowInd=trc.fRowInd; fNindex=trc.fNindex; fColPtr=trc.fColPtr; fDataPtr=trc.fDataPtr; }  return *this;}
   virtual ~TMatrixTSparseRow_const() { }

   inline const TMatrixTBase<Element> *GetMatrix  () const { return fMatrix; }
   inline const Element               *GetDataPtr () const { return fDataPtr; }
   inline const Int_t                 *GetColPtr  () const { return fColPtr; }
   inline       Int_t                  GetRowIndex() const { return fRowInd; }
   inline       Int_t                  GetNindex  () const { return fNindex; }

          Element operator()(Int_t i) const;
   inline Element operator[](Int_t i) const { return (*(const TMatrixTSparseRow_const<Element> *)this)(i); }

   ClassDef(TMatrixTSparseRow_const,0)  // Template of Sparse Matrix Row Access class
};

template<class Element> class TMatrixTSparseRow : public TMatrixTSparseRow_const<Element> {

public:
   TMatrixTSparseRow() {}
   TMatrixTSparseRow(TMatrixTSparse<Element> &matrix,Int_t row);
   TMatrixTSparseRow(const TMatrixTSparseRow<Element> &mr);

   inline Element *GetDataPtr() const { return const_cast<Element *>(this->fDataPtr); }

          Element  operator()(Int_t i) const;
          Element &operator()(Int_t i);
   inline Element  operator[](Int_t i) const { return (*(const TMatrixTSparseRow<Element> *)this)(i); }
   inline Element &operator[](Int_t i)       { return (*(TMatrixTSparseRow<Element> *)this)(i); }

   void operator= (Element val);
   void operator+=(Element val);
   void operator*=(Element val);

   void operator=(const TMatrixTSparseRow_const<Element> &r);
   TMatrixTSparseRow<Element>& operator=(const TMatrixTSparseRow <Element> &r) { operator=((TMatrixTSparseRow_const<Element> &)r); return *this;}
   void operator=(const TVectorT               <Element> &vec);

   void operator+=(const TMatrixTSparseRow_const<Element> &r);
   void operator*=(const TMatrixTSparseRow_const<Element> &r);

   ClassDef(TMatrixTSparseRow,0)  // Template of Sparse Matrix Row Access class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTSparseDiag_const                                             //
//                                                                      //
// Template class represents the diagonal of TMatrixTSparse             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTSparseDiag_const {

protected:
   const TMatrixTSparse<Element> *fMatrix;  //  the matrix I am the diagonal of
         Int_t                  fNdiag;   //  number of diag elems, min(nrows,ncols)
   const Element               *fDataPtr; //  data pointer

public:
   TMatrixTSparseDiag_const() { fMatrix = 0; fNdiag = 0; fDataPtr = 0; }
   TMatrixTSparseDiag_const(const TMatrixTSparse<Element> &matrix);
   TMatrixTSparseDiag_const(const TMatrixTSparseDiag_const<Element>& trc):
     fMatrix(trc.fMatrix), fNdiag(trc.fNdiag), fDataPtr(trc.fDataPtr) { }
   TMatrixTSparseDiag_const<Element>& operator=(const TMatrixTSparseDiag_const<Element>& trc) {
      if(this !=  &trc) { fMatrix=trc.fMatrix; fNdiag=trc.fNdiag; fDataPtr=trc.fDataPtr; } return *this;}
   virtual ~TMatrixTSparseDiag_const() { }

   inline const TMatrixTBase<Element> *GetMatrix () const { return fMatrix; }
   inline const Element               *GetDataPtr() const { return fDataPtr; }
   inline       Int_t                  GetNdiags () const { return fNdiag; }

          Element operator ()(Int_t i) const;
   inline Element operator [](Int_t i) const { return (*(const TMatrixTSparseRow_const<Element> *)this)(i); }

   ClassDef(TMatrixTSparseDiag_const,0)  // Template of Sparse Matrix Diagonal Access class
};

template<class Element> class TMatrixTSparseDiag : public TMatrixTSparseDiag_const<Element> {

public:
   TMatrixTSparseDiag() {}
   TMatrixTSparseDiag(TMatrixTSparse<Element> &matrix);
   TMatrixTSparseDiag(const TMatrixTSparseDiag<Element> &md);

   inline Element *GetDataPtr() const { return const_cast<Element *>(this->fDataPtr); }

                Element  operator()(Int_t i) const;
                Element &operator()(Int_t i);
   inline       Element  operator[](Int_t i) const { return (*(const TMatrixTSparseDiag<Element> *)this)(i); }
   inline       Element &operator[](Int_t i)       { return (*(TMatrixTSparseDiag<Element> *)this)(i); }

   void operator= (Element val);
   void operator+=(Element val);
   void operator*=(Element val);

   void operator=(const TMatrixTSparseDiag_const<Element> &d);
   TMatrixTSparseDiag<Element>& operator=(const TMatrixTSparseDiag <Element> &d) { operator=((TMatrixTSparseDiag_const<Element> &)d); return *this;}
   void operator=(const TVectorT                <Element> &vec);

   void operator+=(const TMatrixTSparseDiag_const<Element> &d);
   void operator*=(const TMatrixTSparseDiag_const<Element> &d);

   ClassDef(TMatrixTSparseDiag,0)  // Template of Sparse Matrix Diagonal Access class
};

Double_t Drand(Double_t &ix);
#endif


// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixT
#define ROOT_TMatrixT

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixT                                                             //
//                                                                      //
// Template class of a general matrix in the linear algebra package     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixTBase.h"
//#include "TMatrixTUtils.h"

#ifdef CBLAS
#include <vecLib/vBLAS.h>
//#include <cblas.h>
#endif

//#include "Rtypes.h"
//#include "TError.h"


template<class Element> class TMatrixTSym;
template<class Element> class TMatrixTSparse;
template<class Element> class TMatrixTLazy;

template<class Element> class TMatrixT : public TMatrixTBase<Element> {

protected:

   Element  fDataStack[TMatrixTBase<Element>::kSizeMax]; //! data container
   Element *fElements;                                   //[fNelems] elements themselves

   Element *New_m   (Int_t size);
   void     Delete_m(Int_t size,Element*&);
   Int_t    Memcpy_m(Element *newp,const Element *oldp,Int_t copySize,
                      Int_t newSize,Int_t oldSize);
   void     Allocate(Int_t nrows,Int_t ncols,Int_t row_lwb = 0,Int_t col_lwb = 0,Int_t init = 0,
                     Int_t /*nr_nonzeros*/ = -1);


public:


   enum {kWorkMax = 100};
   enum EMatrixCreatorsOp1 { kZero,kUnit,kTransposed,kInverted,kAtA };
   enum EMatrixCreatorsOp2 { kMult,kTransposeMult,kInvMult,kMultTranspose,kPlus,kMinus };

   TMatrixT(): fDataStack(), fElements(0) { }
   TMatrixT(Int_t nrows,Int_t ncols);
   TMatrixT(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb);
   TMatrixT(Int_t nrows,Int_t ncols,const Element *data,Option_t *option="");
   TMatrixT(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,const Element *data,Option_t *option="");
   TMatrixT(const TMatrixT      <Element> &another);
   TMatrixT(const TMatrixTSym   <Element> &another);
   TMatrixT(const TMatrixTSparse<Element> &another);
   template <class Element2> TMatrixT(const TMatrixT<Element2> &another): fElements(0)
   {
      R__ASSERT(another.IsValid());
      Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb());
      *this = another;
   }

   TMatrixT(EMatrixCreatorsOp1 op,const TMatrixT<Element> &prototype);
   TMatrixT(const TMatrixT    <Element> &a,EMatrixCreatorsOp2 op,const TMatrixT   <Element> &b);
   TMatrixT(const TMatrixT    <Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSym<Element> &b);
   TMatrixT(const TMatrixTSym <Element> &a,EMatrixCreatorsOp2 op,const TMatrixT   <Element> &b);
   TMatrixT(const TMatrixTSym <Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSym<Element> &b);
   TMatrixT(const TMatrixTLazy<Element> &lazy_constructor);

   virtual ~TMatrixT() { Clear(); }

   // Elementary constructors

   void Plus (const TMatrixT   <Element> &a,const TMatrixT   <Element> &b);
   void Plus (const TMatrixT   <Element> &a,const TMatrixTSym<Element> &b);
   void Plus (const TMatrixTSym<Element> &a,const TMatrixT   <Element> &b) { Plus(b,a); }

   void Minus(const TMatrixT   <Element> &a,const TMatrixT   <Element> &b);
   void Minus(const TMatrixT   <Element> &a,const TMatrixTSym<Element> &b);
   void Minus(const TMatrixTSym<Element> &a,const TMatrixT   <Element> &b) { Minus(b,a); }

   void Mult (const TMatrixT   <Element> &a,const TMatrixT   <Element> &b);
   void Mult (const TMatrixT   <Element> &a,const TMatrixTSym<Element> &b);
   void Mult (const TMatrixTSym<Element> &a,const TMatrixT   <Element> &b);
   void Mult (const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b);

   void TMult(const TMatrixT   <Element> &a,const TMatrixT   <Element> &b);
   void TMult(const TMatrixT   <Element> &a,const TMatrixTSym<Element> &b);
   void TMult(const TMatrixTSym<Element> &a,const TMatrixT   <Element> &b) { Mult(a,b); }
   void TMult(const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b) { Mult(a,b); }

   void MultT(const TMatrixT   <Element> &a,const TMatrixT   <Element> &b);
   void MultT(const TMatrixT   <Element> &a,const TMatrixTSym<Element> &b) { Mult(a,b); }
   void MultT(const TMatrixTSym<Element> &a,const TMatrixT   <Element> &b);
   void MultT(const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b) { Mult(a,b); }

   virtual const Element *GetMatrixArray  () const;
   virtual       Element *GetMatrixArray  ();
   virtual const Int_t   *GetRowIndexArray() const { return 0; }
   virtual       Int_t   *GetRowIndexArray()       { return 0; }
   virtual const Int_t   *GetColIndexArray() const { return 0; }
   virtual       Int_t   *GetColIndexArray()       { return 0; }

   virtual       TMatrixTBase<Element> &SetRowIndexArray(Int_t * /*data*/) { /*MayNotUse("SetRowIndexArray(Int_t *)");*/ return *this; }
   virtual       TMatrixTBase<Element> &SetColIndexArray(Int_t * /*data*/) { /*MayNotUse("SetColIndexArray(Int_t *)");*/ return *this; }

   virtual void Clear(Option_t * /*option*/ ="") { if (this->fIsOwner) Delete_m(this->fNelems,fElements);
                                                   else fElements = 0;
                                                   this->fNelems = 0; }

           TMatrixT    <Element> &Use     (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Element *data);
   const   TMatrixT    <Element> &Use     (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,const Element *data) const
                                            { return (const TMatrixT<Element>&)
                                                     ((const_cast<TMatrixT<Element> *>(this))->Use(row_lwb,row_upb,col_lwb,col_upb, const_cast<Element *>(data))); }
           TMatrixT    <Element> &Use     (Int_t nrows,Int_t ncols,Element *data);
   const   TMatrixT    <Element> &Use     (Int_t nrows,Int_t ncols,const Element *data) const;
           TMatrixT    <Element> &Use     (TMatrixT<Element> &a);
   const   TMatrixT    <Element> &Use     (const TMatrixT<Element> &a) const;

   virtual TMatrixTBase<Element> &GetSub  (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                           TMatrixTBase<Element> &target,Option_t *option="S") const;
           TMatrixT    <Element>  GetSub  (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Option_t *option="S") const;
   virtual TMatrixTBase<Element> &SetSub  (Int_t row_lwb,Int_t col_lwb,const TMatrixTBase<Element> &source);

   virtual TMatrixTBase<Element> &ResizeTo(Int_t nrows,Int_t ncols,Int_t /*nr_nonzeros*/ =-1);
   virtual TMatrixTBase<Element> &ResizeTo(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Int_t /*nr_nonzeros*/ =-1);
   inline  TMatrixTBase<Element> &ResizeTo(const TMatrixT<Element> &m) {
                                            return ResizeTo(m.GetRowLwb(),m.GetRowUpb(),m.GetColLwb(),m.GetColUpb());
                                 }

   virtual Double_t Determinant  () const;
   virtual void     Determinant  (Double_t &d1,Double_t &d2) const;

           TMatrixT<Element> &Invert      (Double_t *det=0);
           TMatrixT<Element> &InvertFast  (Double_t *det=0);
           TMatrixT<Element> &Transpose   (const TMatrixT<Element> &source);
   inline  TMatrixT<Element> &T           () { return this->Transpose(*this); }
           TMatrixT<Element> &Rank1Update (const TVectorT<Element> &v,Element alpha=1.0);
           TMatrixT<Element> &Rank1Update (const TVectorT<Element> &v1,const TVectorT<Element> &v2,Element alpha=1.0);
           Element            Similarity  (const TVectorT<Element> &v) const;

   TMatrixT<Element> &NormByColumn(const TVectorT<Element> &v,Option_t *option="D");
   TMatrixT<Element> &NormByRow   (const TVectorT<Element> &v,Option_t *option="D");

   // Either access a_ij as a(i,j)
   inline       Element                     operator()(Int_t rown,Int_t coln) const;
   inline       Element                    &operator()(Int_t rown,Int_t coln);

   // or as a[i][j]
   inline const TMatrixTRow_const<Element>  operator[](Int_t rown) const { return TMatrixTRow_const<Element>(*this,rown); }
   inline       TMatrixTRow      <Element>  operator[](Int_t rown)       { return TMatrixTRow      <Element>(*this,rown); }

   TMatrixT<Element> &operator= (const TMatrixT      <Element> &source);
   TMatrixT<Element> &operator= (const TMatrixTSym   <Element> &source);
   TMatrixT<Element> &operator= (const TMatrixTSparse<Element> &source);
   TMatrixT<Element> &operator= (const TMatrixTLazy  <Element> &source);
   template <class Element2> TMatrixT<Element> &operator= (const TMatrixT<Element2> &source)
   {
      if (!AreCompatible(*this,source)) {
         //Error("operator=(const TMatrixT2 &)","matrices not compatible");
         return *this;
      }

     TObject::operator=(source);
     const Element2 * const ps = source.GetMatrixArray();
           Element  * const pt = this->GetMatrixArray();
     for (Int_t i = 0; i < this->fNelems; i++)
        pt[i] = ps[i];
     this->fTol = source.GetTol();
     return *this;
   }

   TMatrixT<Element> &operator= (Element val);
   TMatrixT<Element> &operator-=(Element val);
   TMatrixT<Element> &operator+=(Element val);
   TMatrixT<Element> &operator*=(Element val);

   TMatrixT<Element> &operator+=(const TMatrixT   <Element> &source);
   TMatrixT<Element> &operator+=(const TMatrixTSym<Element> &source);
   TMatrixT<Element> &operator-=(const TMatrixT   <Element> &source);
   TMatrixT<Element> &operator-=(const TMatrixTSym<Element> &source);

   TMatrixT<Element> &operator*=(const TMatrixT            <Element> &source);
   TMatrixT<Element> &operator*=(const TMatrixTSym         <Element> &source);
   TMatrixT<Element> &operator*=(const TMatrixTDiag_const  <Element> &diag);
   TMatrixT<Element> &operator/=(const TMatrixTDiag_const  <Element> &diag);
   TMatrixT<Element> &operator*=(const TMatrixTRow_const   <Element> &row);
   TMatrixT<Element> &operator/=(const TMatrixTRow_const   <Element> &row);
   TMatrixT<Element> &operator*=(const TMatrixTColumn_const<Element> &col);
   TMatrixT<Element> &operator/=(const TMatrixTColumn_const<Element> &col);

   const TMatrixT<Element> EigenVectors(TVectorT<Element> &eigenValues) const;

   ClassDef(TMatrixT,4) // Template of General Matrix class
};

#ifndef __CINT__
// When building with -fmodules, it instantiates all pending instantiations,
// instead of delaying them until the end of the translation unit.
// We 'got away with' probably because the use and the definition of the
// explicit specialization do not occur in the same TU.
//
// In case we are building with -fmodules, we need to forward declare the
// specialization in order to compile the dictionary G__Matrix.cxx.
template <> TClass *TMatrixT<double>::Class();
#endif // __CINT__


template <class Element> inline const Element           *TMatrixT<Element>::GetMatrixArray() const { return fElements; }
template <class Element> inline       Element           *TMatrixT<Element>::GetMatrixArray()       { return fElements; }

template <class Element> inline       TMatrixT<Element> &TMatrixT<Element>::Use           (Int_t nrows,Int_t ncols,Element *data)
                                                                                          { return Use(0,nrows-1,0,ncols-1,data); }
template <class Element> inline const TMatrixT<Element> &TMatrixT<Element>::Use           (Int_t nrows,Int_t ncols,const Element *data) const
                                                                                          { return Use(0,nrows-1,0,ncols-1,data); }
template <class Element> inline       TMatrixT<Element> &TMatrixT<Element>::Use           (TMatrixT &a)
                                                                                          {
                                                                                            R__ASSERT(a.IsValid());
                                                                                            return Use(a.GetRowLwb(),a.GetRowUpb(),
                                                                                                       a.GetColLwb(),a.GetColUpb(),a.GetMatrixArray());
                                                                                          }
template <class Element> inline const TMatrixT<Element> &TMatrixT<Element>::Use           (const TMatrixT &a) const
                                                                                          {
                                                                                            R__ASSERT(a.IsValid());
                                                                                            return Use(a.GetRowLwb(),a.GetRowUpb(),
                                                                                                       a.GetColLwb(),a.GetColUpb(),a.GetMatrixArray());
                                                                                          }

template <class Element> inline       TMatrixT<Element>  TMatrixT<Element>::GetSub        (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                                                           Option_t *option) const
                                                                                          {
                                                                                            TMatrixT tmp;
                                                                                            this->GetSub(row_lwb,row_upb,col_lwb,col_upb,tmp,option);
                                                                                            return tmp;
                                                                                          }

template <class Element> inline Element TMatrixT<Element>::operator()(Int_t rown,Int_t coln) const
{
   //R__ASSERT(this->IsValid());
   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;
   if (arown >= this->fNrows || arown < 0) {
      //Error("operator()","Request row(%d) outside matrix range of %d - %d",rown,this->fRowLwb,this->fRowLwb+this->fNrows);
      return TMatrixTBase<Element>::NaNValue();
   }
   if (acoln >= this->fNcols || acoln < 0) {
      //Error("operator()","Request column(%d) outside matrix range of %d - %d",coln,this->fColLwb,this->fColLwb+this->fNcols);
      return TMatrixTBase<Element>::NaNValue();

   }
   return (fElements[arown*this->fNcols+acoln]);
}

template <class Element> inline Element &TMatrixT<Element>::operator()(Int_t rown,Int_t coln)
{
   //R__ASSERT(this->IsValid());
   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;
   if (arown >= this->fNrows || arown < 0) {
      //Error("operator()","Request row(%d) outside matrix range of %d - %d",rown,this->fRowLwb,this->fRowLwb+this->fNrows);
      return TMatrixTBase<Element>::NaNValue();
   }
   if (acoln >= this->fNcols || acoln < 0) {
      //Error("operator()","Request column(%d) outside matrix range of %d - %d",coln,this->fColLwb,this->fColLwb+this->fNcols);
      return TMatrixTBase<Element>::NaNValue();
   }
   return (fElements[arown*this->fNcols+acoln]);
}

template <class Element> TMatrixT<Element>  operator+  (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator+  (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator+  (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator+  (const TMatrixT   <Element> &source ,      Element               val    );
template <class Element> TMatrixT<Element>  operator+  (      Element               val    ,const TMatrixT   <Element> &source );
template <class Element> TMatrixT<Element>  operator-  (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator-  (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator-  (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator-  (const TMatrixT   <Element> &source ,      Element               val    );
template <class Element> TMatrixT<Element>  operator-  (      Element               val    ,const TMatrixT   <Element> &source );
template <class Element> TMatrixT<Element>  operator*  (      Element               val    ,const TMatrixT   <Element> &source );
template <class Element> TMatrixT<Element>  operator*  (const TMatrixT   <Element> &source ,      Element               val    );
template <class Element> TMatrixT<Element>  operator*  (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator*  (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator*  (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator*  (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element> &source2);
// Preventing warnings with -Weffc++ in GCC since overloading the || and && operators was a design choice.
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40600
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif
template <class Element> TMatrixT<Element>  operator&& (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator&& (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator&& (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator|| (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator|| (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator|| (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40600
#pragma GCC diagnostic pop
#endif
template <class Element> TMatrixT<Element>  operator>  (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator>  (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator>  (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator>= (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator>= (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator>= (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator<= (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator<= (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator<= (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator<  (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator<  (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator<  (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator!= (const TMatrixT   <Element> &source1,const TMatrixT   <Element> &source2);
template <class Element> TMatrixT<Element>  operator!= (const TMatrixT   <Element> &source1,const TMatrixTSym<Element> &source2);
template <class Element> TMatrixT<Element>  operator!= (const TMatrixTSym<Element> &source1,const TMatrixT   <Element> &source2);

template <class Element> TMatrixT<Element> &Add        (TMatrixT<Element> &target,      Element               scalar,const TMatrixT   <Element> &source);
template <class Element> TMatrixT<Element> &Add        (TMatrixT<Element> &target,      Element               scalar,const TMatrixTSym<Element> &source);
template <class Element> TMatrixT<Element> &ElementMult(TMatrixT<Element> &target,const TMatrixT   <Element> &source);
template <class Element> TMatrixT<Element> &ElementMult(TMatrixT<Element> &target,const TMatrixTSym<Element> &source);
template <class Element> TMatrixT<Element> &ElementDiv (TMatrixT<Element> &target,const TMatrixT   <Element> &source);
template <class Element> TMatrixT<Element> &ElementDiv (TMatrixT<Element> &target,const TMatrixTSym<Element> &source);

template <class Element> void AMultB (const Element * const ap,Int_t na,Int_t ncolsa,
                                      const Element * const bp,Int_t nb,Int_t ncolsb,Element *cp);
template <class Element> void AtMultB(const Element * const ap,Int_t ncolsa,
                                      const Element * const bp,Int_t nb,Int_t ncolsb,Element *cp);
template <class Element> void AMultBt(const Element * const ap,Int_t na,Int_t ncolsa,
                                      const Element * const bp,Int_t nb,Int_t ncolsb,Element *cp);

#endif

// @(#)root/base:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Jan 2004

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixTCramerInv
#define ROOT_TMatrixTCramerInv

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTCramerInv                                                    //
//                                                                      //
// Encapsulate templates of Cramer Inversion routines.                  //
//                                                                      //
// The 4x4, 5x5 and 6x6 are adapted from routines written by            //
// Mark Fischler and Steven Haywood as part of the CLHEP package        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

//#include "TMatrixT.h"

namespace TMatrixTCramerInv {

   template<class Element> Bool_t Inv2x2(TMatrixT<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv3x3(TMatrixT<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv4x4(TMatrixT<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv5x5(TMatrixT<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv6x6(TMatrixT<Element> &m,Double_t *determ);

}

#endif







// @(#)root/base:$Id$
// Authors: Fons Rademakers, Eddy Offermann  Oct 2004

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixTSymCramerInv
#define ROOT_TMatrixTSymCramerInv

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTSymCramerInv                                                 //
//                                                                      //
// Encapsulate templates of Cramer Inversion routines.                  //
//                                                                      //
// The 4x4, 5x5 and 6x6 are adapted from routines written by            //
// Mark Fischler and Steven Haywood as part of the CLHEP package        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

//#include "TMatrixTSym.h"

namespace TMatrixTSymCramerInv {

   template<class Element> Bool_t Inv2x2(TMatrixTSym<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv3x3(TMatrixTSym<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv4x4(TMatrixTSym<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv5x5(TMatrixTSym<Element> &m,Double_t *determ);
   template<class Element> Bool_t Inv6x6(TMatrixTSym<Element> &m,Double_t *determ);

}

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixTLazy
#define ROOT_TMatrixTLazy

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Templates of Lazy Matrix classes.                                    //
//                                                                      //
//   TMatrixTLazy                                                       //
//   TMatrixTSymLazy                                                    //
//   THaarMatrixT                                                       //
//   THilbertMatrixT                                                    //
//   THilbertMatrixTSym                                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixTBase.h"

template<class Element> class TVectorT;
template<class Element> class TMatrixTBase;
template<class Element> class TMatrixT;
template<class Element> class TMatrixTSym;

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTLazy                                                         //
//                                                                      //
// Class used to make a lazy copy of a matrix, i.e. only copy matrix    //
// when really needed (when accessed).                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTLazy : public TObject {

friend class TMatrixTBase<Element>;
friend class TMatrixT    <Element>;
friend class TVectorT    <Element>;

protected:
   Int_t fRowUpb;
   Int_t fRowLwb;
   Int_t fColUpb;
   Int_t fColLwb;

   TMatrixTLazy(const TMatrixTLazy<Element> &) : TObject(), fRowUpb(0),fRowLwb(0),fColUpb(0),fColLwb(0) { }
   void operator=(const TMatrixTLazy<Element> &) { }

private:
   virtual void FillIn(TMatrixT<Element> &m) const = 0;

public:
   TMatrixTLazy() { fRowUpb = fRowLwb = fColUpb = fColLwb = 0; }
   TMatrixTLazy(Int_t nrows, Int_t ncols)
       : fRowUpb(nrows-1),fRowLwb(0),fColUpb(ncols-1),fColLwb(0) { }
   TMatrixTLazy(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb)
       : fRowUpb(row_upb),fRowLwb(row_lwb),fColUpb(col_upb),fColLwb(col_lwb) { }
   virtual ~TMatrixTLazy() {}

   inline Int_t GetRowLwb() const { return fRowLwb; }
   inline Int_t GetRowUpb() const { return fRowUpb; }
   inline Int_t GetColLwb() const { return fColLwb; }
   inline Int_t GetColUpb() const { return fColUpb; }

   ClassDef(TMatrixTLazy,3)  // Template of Lazy Matrix class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTSymLazy                                                      //
//                                                                      //
// Class used to make a lazy copy of a matrix, i.e. only copy matrix    //
// when really needed (when accessed).                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixTSymLazy : public TObject {

friend class TMatrixTBase<Element>;
friend class TMatrixTSym <Element>;
friend class TVectorT    <Element>;

protected:
   Int_t fRowUpb;
   Int_t fRowLwb;

   TMatrixTSymLazy(const TMatrixTSymLazy<Element> &) : TObject(), fRowUpb(0),fRowLwb(0)  { }
   void operator=(const TMatrixTSymLazy<Element> &) { }

private:
   virtual void FillIn(TMatrixTSym<Element> &m) const = 0;

public:
   TMatrixTSymLazy() { fRowUpb = fRowLwb = 0; }
   TMatrixTSymLazy(Int_t nrows)
       : fRowUpb(nrows-1),fRowLwb(0) { }
   TMatrixTSymLazy(Int_t row_lwb,Int_t row_upb)
       : fRowUpb(row_upb),fRowLwb(row_lwb) { }
   virtual ~TMatrixTSymLazy() {}

   inline Int_t GetRowLwb() const { return fRowLwb; }
   inline Int_t GetRowUpb() const { return fRowUpb; }

   ClassDef(TMatrixTSymLazy,2)  // Template of Lazy Symmeytric class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// THaarMatrixT                                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class THaarMatrixT: public TMatrixTLazy<Element> {

private:
   void FillIn(TMatrixT<Element> &m) const;

public:
   THaarMatrixT() {}
   THaarMatrixT(Int_t n,Int_t no_cols = 0);
   virtual ~THaarMatrixT() {}

   ClassDef(THaarMatrixT,2)  // Template of Haar Matrix class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// THilbertMatrixT                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class THilbertMatrixT : public TMatrixTLazy<Element> {

private:
   void FillIn(TMatrixT<Element> &m) const;

public:
   THilbertMatrixT() {}
   THilbertMatrixT(Int_t no_rows,Int_t no_cols);
   THilbertMatrixT(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb);
   virtual ~THilbertMatrixT() {}

   ClassDef(THilbertMatrixT,2)  // Template of Hilbert Matrix class
};

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// THilbertMatrixTSym                                                   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class THilbertMatrixTSym : public TMatrixTSymLazy<Element> {

private:
   void FillIn(TMatrixTSym<Element> &m) const;

public:
   THilbertMatrixTSym() {}
   THilbertMatrixTSym(Int_t no_rows);
   THilbertMatrixTSym(Int_t row_lwb,Int_t row_upb);
   virtual ~THilbertMatrixTSym() {}

   ClassDef(THilbertMatrixTSym,2)  // Template of Symmetric Hilbert Matrix class
};

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixTSym
#define ROOT_TMatrixTSym

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTSym                                                          //
//                                                                      //
// Implementation of a symmetric matrix in the linear algebra package   //
//                                                                      //
// Note that in this implementation both matrix element m[i][j] and     //
// m[j][i] are updated and stored in memory . However, when making the  //
// object persistent only the upper right triangle is stored .          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixTBase.h"
//#include "TMatrixTUtils.h"

template<class Element>class TMatrixT;
template<class Element>class TMatrixTSymLazy;
template<class Element>class TVectorT;

template<class Element> class TMatrixTSym : public TMatrixTBase<Element> {

protected:

   Element  fDataStack[TMatrixTBase<Element>::kSizeMax]; //! data container
   Element *fElements;                                   //[fNelems] elements themselves

   Element *New_m   (Int_t size);
   void     Delete_m(Int_t size,Element*&);
   Int_t    Memcpy_m(Element *newp,const Element *oldp,Int_t copySize,
                     Int_t newSize,Int_t oldSize);
   void     Allocate(Int_t nrows,Int_t ncols,Int_t row_lwb = 0,Int_t col_lwb = 0,Int_t init = 0,
                     Int_t /*nr_nonzeros*/ = -1);

public:

   enum {kWorkMax = 100}; // size of work array
   enum EMatrixCreatorsOp1 { kZero,kUnit,kTransposed,kInverted,kAtA };
   enum EMatrixCreatorsOp2 { kPlus,kMinus };

   TMatrixTSym() { fElements = 0; }
   explicit TMatrixTSym(Int_t nrows);
   TMatrixTSym(Int_t row_lwb,Int_t row_upb);
   TMatrixTSym(Int_t nrows,const Element *data,Option_t *option="");
   TMatrixTSym(Int_t row_lwb,Int_t row_upb,const Element *data,Option_t *option="");
   TMatrixTSym(const TMatrixTSym<Element> &another);
   template <class Element2> TMatrixTSym(const TMatrixTSym<Element2> &another)
   {
      R__ASSERT(another.IsValid());
      Allocate(another.GetNrows(),another.GetNcols(),another.GetRowLwb(),another.GetColLwb());
      *this = another;
   }

   TMatrixTSym(EMatrixCreatorsOp1 op,const TMatrixTSym<Element> &prototype);
   TMatrixTSym(EMatrixCreatorsOp1 op,const TMatrixT   <Element> &prototype);
   TMatrixTSym(const TMatrixTSym<Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSym<Element> &b);
   TMatrixTSym(const TMatrixTSymLazy<Element> &lazy_constructor);

   virtual ~TMatrixTSym() { Clear(); }

   // Elementary constructors
   void TMult(const TMatrixT   <Element> &a);
   void TMult(const TMatrixTSym<Element> &a);
   void Mult (const TMatrixTSym<Element> &a) { TMult(a); }

   void Plus (const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b);
   void Minus(const TMatrixTSym<Element> &a,const TMatrixTSym<Element> &b);

   virtual const Element *GetMatrixArray  () const;
   virtual       Element *GetMatrixArray  ();
   virtual const Int_t   *GetRowIndexArray() const { return 0; }
   virtual       Int_t   *GetRowIndexArray()       { return 0; }
   virtual const Int_t   *GetColIndexArray() const { return 0; }
   virtual       Int_t   *GetColIndexArray()       { return 0; }

   virtual       TMatrixTBase<Element> &SetRowIndexArray(Int_t * /*data*/) { /*MayNotUse("SetRowIndexArray(Int_t *)");*/ return *this; }
   virtual       TMatrixTBase<Element> &SetColIndexArray(Int_t * /*data*/) { /*MayNotUse("SetColIndexArray(Int_t *)");*/ return *this; }

   virtual void   Clear      (Option_t * /*option*/ ="") { if (this->fIsOwner) Delete_m(this->fNelems,fElements);
                                                           else fElements = 0;
                                                           this->fNelems = 0; }
   virtual Bool_t IsSymmetric() const { return kTRUE; }

           TMatrixTSym <Element> &Use           (Int_t row_lwb,Int_t row_upb,Element *data);
   const   TMatrixTSym <Element> &Use           (Int_t row_lwb,Int_t row_upb,const Element *data) const
                                                  { return (const TMatrixTSym<Element>&)
                                                           ((const_cast<TMatrixTSym<Element> *>(this))->Use(row_lwb,row_upb,const_cast<Element *>(data))); }
           TMatrixTSym <Element> &Use           (Int_t nrows,Element *data);
   const   TMatrixTSym <Element> &Use           (Int_t nrows,const Element *data) const;
           TMatrixTSym <Element> &Use           (TMatrixTSym<Element> &a);
   const   TMatrixTSym <Element> &Use           (const TMatrixTSym<Element> &a) const;

           TMatrixTSym <Element> &GetSub        (Int_t row_lwb,Int_t row_upb,TMatrixTSym<Element> &target,Option_t *option="S") const;
   virtual TMatrixTBase<Element> &GetSub        (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                TMatrixTBase<Element> &target,Option_t *option="S") const;
           TMatrixTSym <Element>  GetSub        (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Option_t *option="S") const;
           TMatrixTSym <Element> &SetSub        (Int_t row_lwb,const TMatrixTBase<Element> &source);
   virtual TMatrixTBase<Element> &SetSub        (Int_t row_lwb,Int_t col_lwb,const TMatrixTBase<Element> &source);

   virtual TMatrixTBase<Element> &SetMatrixArray(const Element *data, Option_t *option="");

   virtual TMatrixTBase<Element> &Shift         (Int_t row_shift,Int_t col_shift);
   virtual TMatrixTBase<Element> &ResizeTo      (Int_t nrows,Int_t ncols,Int_t /*nr_nonzeros*/ =-1);
   virtual TMatrixTBase<Element> &ResizeTo      (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Int_t /*nr_nonzeros*/ =-1);
   inline  TMatrixTBase<Element> &ResizeTo      (const TMatrixTSym<Element> &m) {
                                                return ResizeTo(m.GetRowLwb(),m.GetRowUpb(),m.GetColLwb(),m.GetColUpb()); }

   virtual Double_t      Determinant   () const;
   virtual void          Determinant   (Double_t &d1,Double_t &d2) const;

           TMatrixTSym<Element>  &Invert        (Double_t *det=0);
           TMatrixTSym<Element>  &InvertFast    (Double_t *det=0);
           TMatrixTSym<Element>  &Transpose     (const TMatrixTSym<Element> &source);
   inline  TMatrixTSym<Element>  &T             () { return this->Transpose(*this); }
           TMatrixTSym<Element>  &Rank1Update   (const TVectorT   <Element> &v,Element alpha=1.0);
           TMatrixTSym<Element>  &Similarity    (const TMatrixT   <Element> &n);
           TMatrixTSym<Element>  &Similarity    (const TMatrixTSym<Element> &n);
           Element                Similarity    (const TVectorT   <Element> &v) const;
           TMatrixTSym<Element>  &SimilarityT   (const TMatrixT   <Element> &n);

   // Either access a_ij as a(i,j)
   inline       Element                    operator()(Int_t rown,Int_t coln) const;
   inline       Element                   &operator()(Int_t rown,Int_t coln);

   // or as a[i][j]
   inline const TMatrixTRow_const<Element> operator[](Int_t rown) const { return TMatrixTRow_const<Element>(*this,rown); }
   inline       TMatrixTRow      <Element> operator[](Int_t rown)       { return TMatrixTRow      <Element>(*this,rown); }

   TMatrixTSym<Element> &operator= (const TMatrixTSym    <Element> &source);
   TMatrixTSym<Element> &operator= (const TMatrixTSymLazy<Element> &source);
   template <class Element2> TMatrixTSym<Element> &operator= (const TMatrixTSym<Element2> &source)
   {
      if (!AreCompatible(*this,source)) {
         //Error("operator=(const TMatrixTSym2 &)","matrices not compatible");
         return *this;
      }

      TObject::operator=(source);
      const Element2 * const ps = source.GetMatrixArray();
            Element  * const pt = this->GetMatrixArray();
      for (Int_t i = 0; i < this->fNelems; i++)
         pt[i] = ps[i];
      this->fTol = source.GetTol();
      return *this;
   }

   TMatrixTSym<Element> &operator= (Element val);
   TMatrixTSym<Element> &operator-=(Element val);
   TMatrixTSym<Element> &operator+=(Element val);
   TMatrixTSym<Element> &operator*=(Element val);

   TMatrixTSym &operator+=(const TMatrixTSym &source);
   TMatrixTSym &operator-=(const TMatrixTSym &source);

   TMatrixTBase<Element> &Apply(const TElementActionT   <Element> &action);
   TMatrixTBase<Element> &Apply(const TElementPosActionT<Element> &action);

   virtual TMatrixTBase<Element> &Randomize  (Element alpha,Element beta,Double_t &seed);
   virtual TMatrixTSym <Element> &RandomizePD(Element alpha,Element beta,Double_t &seed);

   const TMatrixT<Element> EigenVectors(TVectorT<Element> &eigenValues) const;

   ClassDef(TMatrixTSym,2) // Template of Symmetric Matrix class
};
#ifndef __CINT__
// When building with -fmodules, it instantiates all pending instantiations,
// instead of delaying them until the end of the translation unit.
// We 'got away with' probably because the use and the definition of the
// explicit specialization do not occur in the same TU.
//
// In case we are building with -fmodules, we need to forward declare the
// specialization in order to compile the dictionary G__Matrix.cxx.
template <> TClass *TMatrixTSym<double>::Class();
#endif // __CINT__

template <class Element> inline const Element               *TMatrixTSym<Element>::GetMatrixArray() const { return fElements; }
template <class Element> inline       Element               *TMatrixTSym<Element>::GetMatrixArray()       { return fElements; }

template <class Element> inline       TMatrixTSym<Element>  &TMatrixTSym<Element>::Use           (Int_t nrows,Element *data) { return Use(0,nrows-1,data); }
template <class Element> inline const TMatrixTSym<Element>  &TMatrixTSym<Element>::Use           (Int_t nrows,const Element *data) const
                                                                                                   { return Use(0,nrows-1,data); }
template <class Element> inline       TMatrixTSym<Element>  &TMatrixTSym<Element>::Use           (TMatrixTSym<Element> &a)
                                                                                                 { return Use(a.GetRowLwb(),a.GetRowUpb(),a.GetMatrixArray()); }
template <class Element> inline const TMatrixTSym<Element>  &TMatrixTSym<Element>::Use           (const TMatrixTSym<Element> &a) const
                                                                                                 { return Use(a.GetRowLwb(),a.GetRowUpb(),a.GetMatrixArray()); }

template <class Element> inline       TMatrixTSym<Element>   TMatrixTSym<Element>::GetSub        (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                                                                  Option_t *option) const
                                                                                                 {
                                                                                                   TMatrixTSym<Element> tmp;
                                                                                                   this->GetSub(row_lwb,row_upb,col_lwb,col_upb,tmp,option);
                                                                                                   return tmp;
                                                                                                 }

template <class Element> inline Element TMatrixTSym<Element>::operator()(Int_t rown,Int_t coln) const
{
   R__ASSERT(this->IsValid());
   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;
   if (arown >= this->fNrows || arown < 0) {
      //Error("operator()","Request row(%d) outside matrix range of %d - %d",rown,this->fRowLwb,this->fRowLwb+this->fNrows);
      return TMatrixTBase<Element>::NaNValue();
   }
   if (acoln >= this->fNcols || acoln < 0) {
      //Error("operator()","Request column(%d) outside matrix range of %d - %d",coln,this->fColLwb,this->fColLwb+this->fNcols);
      return TMatrixTBase<Element>::NaNValue();
   }
   return (fElements[arown*this->fNcols+acoln]);
}

template <class Element> inline Element &TMatrixTSym<Element>::operator()(Int_t rown,Int_t coln)
{
   R__ASSERT(this->IsValid());
   const Int_t arown = rown-this->fRowLwb;
   const Int_t acoln = coln-this->fColLwb;
   if (arown >= this->fNrows || arown < 0) {
      //Error("operator()","Request row(%d) outside matrix range of %d - %d",rown,this->fRowLwb,this->fRowLwb+this->fNrows);
      return TMatrixTBase<Element>::NaNValue();
   }
   if (acoln >= this->fNcols || acoln < 0) {
      //Error("operator()","Request column(%d) outside matrix range of %d - %d",coln,this->fColLwb,this->fColLwb+this->fNcols);
      return TMatrixTBase<Element>::NaNValue();
   }
   return (fElements[arown*this->fNcols+acoln]);
}

template <class Element> Bool_t                operator== (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator+  (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator+  (const TMatrixTSym<Element> &source1,      Element                val);
template <class Element> TMatrixTSym<Element>  operator+  (      Element               val    ,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator-  (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator-  (const TMatrixTSym<Element> &source1,      Element                val);
template <class Element> TMatrixTSym<Element>  operator-  (      Element               val    ,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator*  (const TMatrixTSym<Element> &source,       Element                val    );
template <class Element> TMatrixTSym<Element>  operator*  (      Element               val,    const TMatrixTSym<Element>  &source );
// Preventing warnings with -Weffc++ in GCC since overloading the || and && operators was a design choice.
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40600
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif
template <class Element> TMatrixTSym<Element>  operator&& (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator|| (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40600
#pragma GCC diagnostic pop
#endif
template <class Element> TMatrixTSym<Element>  operator>  (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator>= (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator<= (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);
template <class Element> TMatrixTSym<Element>  operator<  (const TMatrixTSym<Element> &source1,const TMatrixTSym<Element>  &source2);

template <class Element> TMatrixTSym<Element> &Add        (TMatrixTSym<Element> &target,      Element               scalar,const TMatrixTSym<Element> &source);
template <class Element> TMatrixTSym<Element> &ElementMult(TMatrixTSym<Element> &target,const TMatrixTSym<Element> &source);
template <class Element> TMatrixTSym<Element> &ElementDiv (TMatrixTSym<Element> &target,const TMatrixTSym<Element> &source);

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Feb 2004

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixTSparse
#define ROOT_TMatrixTSparse

//#include "TMatrixTBase.h"
//#include "TMatrixTUtils.h"


#ifdef CBLAS
#include <vecLib/vBLAS.h>
//#include <cblas.h>
#endif

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixTSparse                                                       //
//                                                                      //
// Template class of a general sparse matrix in the Harwell-Boeing      //
// format                                                               //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

template<class Element> class TMatrixT;

template<class Element> class TMatrixTSparse : public TMatrixTBase<Element> {

protected:

   Int_t   *fRowIndex;  //[fNrowIndex] row index
   Int_t   *fColIndex;  //[fNelems]    column index
   Element *fElements;  //[fNelems]

   void Allocate(Int_t nrows,Int_t ncols,Int_t row_lwb = 0,Int_t col_lwb = 0,
                 Int_t init = 0,Int_t nr_nonzeros = 0);

  // Elementary constructors
   void AMultB (const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr=0) {
                const TMatrixTSparse<Element> bt(TMatrixTSparse::kTransposed,b); AMultBt(a,bt,constr); }
   void AMultB (const TMatrixTSparse<Element> &a,const TMatrixT<Element>       &b,Int_t constr=0) {
                const TMatrixTSparse<Element> bsp = b;
                const TMatrixTSparse<Element> bt(TMatrixTSparse::kTransposed,bsp); AMultBt(a,bt,constr); }
   void AMultB (const TMatrixT<Element>       &a,const TMatrixTSparse<Element> &b,Int_t constr=0) {
                const TMatrixTSparse<Element> bt(TMatrixTSparse::kTransposed,b); AMultBt(a,bt,constr); }

   void AMultBt(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr=0);
   void AMultBt(const TMatrixTSparse<Element> &a,const TMatrixT<Element>       &b,Int_t constr=0);
   void AMultBt(const TMatrixT<Element>       &a,const TMatrixTSparse<Element> &b,Int_t constr=0);

   void APlusB (const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr=0);
   void APlusB (const TMatrixTSparse<Element> &a,const TMatrixT<Element>       &b,Int_t constr=0);
   void APlusB (const TMatrixT<Element>       &a,const TMatrixTSparse<Element> &b,Int_t constr=0) { APlusB(b,a,constr); }

   void AMinusB(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b,Int_t constr=0);
   void AMinusB(const TMatrixTSparse<Element> &a,const TMatrixT<Element>       &b,Int_t constr=0);
   void AMinusB(const TMatrixT<Element>       &a,const TMatrixTSparse<Element> &b,Int_t constr=0);

public:

   enum EMatrixCreatorsOp1 { kZero,kUnit,kTransposed,kAtA };
   enum EMatrixCreatorsOp2 { kMult,kMultTranspose,kPlus,kMinus };

   TMatrixTSparse() { fElements = 0; fRowIndex = 0; fColIndex = 0; }
   TMatrixTSparse(Int_t nrows,Int_t ncols);
   TMatrixTSparse(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb);
   TMatrixTSparse(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Int_t nr_nonzeros,
                  Int_t *row, Int_t *col,Element *data);
   TMatrixTSparse(const TMatrixTSparse<Element> &another);
   TMatrixTSparse(const TMatrixT<Element>       &another);

   TMatrixTSparse(EMatrixCreatorsOp1 op,const TMatrixTSparse<Element> &prototype);
   TMatrixTSparse(const TMatrixTSparse<Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSparse<Element> &b);
   TMatrixTSparse(const TMatrixTSparse<Element> &a,EMatrixCreatorsOp2 op,const TMatrixT      <Element> &b);
   TMatrixTSparse(const TMatrixT      <Element> &a,EMatrixCreatorsOp2 op,const TMatrixTSparse<Element> &b);

   virtual ~TMatrixTSparse() { Clear(); }

   virtual const Element *GetMatrixArray  () const;
   virtual       Element *GetMatrixArray  ();
   virtual const Int_t    *GetRowIndexArray() const;
   virtual       Int_t    *GetRowIndexArray();
   virtual const Int_t    *GetColIndexArray() const;
   virtual       Int_t    *GetColIndexArray();

   virtual TMatrixTBase<Element>   &SetRowIndexArray(Int_t *data) { memmove(fRowIndex,data,(this->fNrows+1)*sizeof(Int_t)); return *this; }
   virtual TMatrixTBase<Element>   &SetColIndexArray(Int_t *data) { memmove(fColIndex,data,this->fNelems*sizeof(Int_t)); return *this; }

           TMatrixTSparse<Element> &SetSparseIndex  (Int_t nelem_new);
           TMatrixTSparse<Element> &SetSparseIndex  (const TMatrixTBase<Element> &another);
           TMatrixTSparse<Element> &SetSparseIndexAB(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b);
           TMatrixTSparse<Element> &SetSparseIndexAB(const TMatrixT      <Element> &a,const TMatrixTSparse<Element> &b);
           TMatrixTSparse<Element> &SetSparseIndexAB(const TMatrixTSparse<Element> &a,const TMatrixT      <Element> &b)
                                              { return SetSparseIndexAB(b,a); }

   virtual void                     GetMatrix2Array (Element *data,Option_t * /*option*/ ="") const;
   virtual TMatrixTBase<Element>   &SetMatrixArray  (const Element *data,Option_t * /*option*/="")
                                                    { memcpy(fElements,data,this->fNelems*sizeof(Element)); return *this; }
   virtual TMatrixTBase<Element>   &SetMatrixArray  (Int_t nr_nonzeros,Int_t *irow,Int_t *icol,Element *data);
   virtual TMatrixTBase<Element>   &InsertRow       (Int_t row,Int_t col,const Element *v,Int_t n=-1);
   virtual void                     ExtractRow      (Int_t row,Int_t col,      Element *v,Int_t n=-1) const;

   virtual TMatrixTBase<Element>   &ResizeTo(Int_t nrows,Int_t ncols,Int_t nr_nonzeros=-1);
   virtual TMatrixTBase<Element>   &ResizeTo(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Int_t nr_nonzeros=-1);
   inline  TMatrixTBase<Element>   &ResizeTo(const TMatrixTSparse<Element> &m) {return ResizeTo(m.GetRowLwb(),m.GetRowUpb(),m.GetColLwb(),
                                                                                                m.GetColUpb(),m.GetNoElements()); }

   virtual void Clear(Option_t * /*option*/ ="") { if (this->fIsOwner) {
                                                      if (fElements) { delete [] fElements; fElements = 0; }
                                                      if (fRowIndex) { delete [] fRowIndex; fRowIndex = 0; }
                                                      if (fColIndex) { delete [] fColIndex; fColIndex = 0; }
                                                   }
                                                   this->fNelems    = 0;
                                                   this->fNrowIndex = 0;
                                                 }

           TMatrixTSparse<Element> &Use   (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Int_t nr_nonzeros,
                                           Int_t *pRowIndex,Int_t *pColIndex,Element *pData);
   const   TMatrixTSparse<Element> &Use   (Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Int_t nr_nonzeros,
                                           const Int_t *pRowIndex,const Int_t *pColIndex,const Element *pData) const
                                            { return (const TMatrixTSparse<Element>&)
                                                     ((const_cast<TMatrixTSparse<Element> *>(this))->Use(row_lwb,row_upb,col_lwb,col_upb,nr_nonzeros,
                                                                                             const_cast<Int_t *>(pRowIndex),
                                                                                             const_cast<Int_t *>(pColIndex),
                                                                                             const_cast<Element *>(pData))); }
           TMatrixTSparse<Element> &Use   (Int_t nrows,Int_t ncols,Int_t nr_nonzeros,
                                           Int_t *pRowIndex,Int_t *pColIndex,Element *pData);
   const   TMatrixTSparse<Element> &Use   (Int_t nrows,Int_t ncols,Int_t nr_nonzeros,
                                           const Int_t *pRowIndex,const Int_t *pColIndex,const Element *pData) const;
           TMatrixTSparse<Element> &Use   (TMatrixTSparse<Element> &a);
   const   TMatrixTSparse<Element> &Use   (const TMatrixTSparse<Element> &a) const;

   virtual TMatrixTBase<Element>   &GetSub(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                            TMatrixTBase<Element> &target,Option_t *option="S") const;
           TMatrixTSparse<Element>  GetSub(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,Option_t *option="S") const;
   virtual TMatrixTBase<Element>   &SetSub(Int_t row_lwb,Int_t col_lwb,const TMatrixTBase<Element> &source);

   virtual Bool_t IsSymmetric() const { return (*this == TMatrixTSparse<Element>(kTransposed,*this)); }
   TMatrixTSparse<Element> &Transpose (const TMatrixTSparse<Element> &source);
   inline TMatrixTSparse<Element> &T () { return this->Transpose(*this); }

   inline void Mult(const TMatrixTSparse<Element> &a,const TMatrixTSparse<Element> &b) { AMultB(a,b,0); }

   virtual TMatrixTBase<Element> &Zero       ();
   virtual TMatrixTBase<Element> &UnitMatrix ();

   virtual Element RowNorm () const;
   virtual Element ColNorm () const;
   virtual Int_t   NonZeros() const { return this->fNelems; }

   virtual TMatrixTBase<Element> &NormByDiag(const TVectorT<Element> &/*v*/,Option_t * /*option*/)
                                              { /*MayNotUse("NormByDiag");*/ return *this; }

   // Either access a_ij as a(i,j)
   Element  operator()(Int_t rown,Int_t coln) const;
   Element &operator()(Int_t rown,Int_t coln);

   // or as a[i][j]
   inline const TMatrixTSparseRow_const<Element> operator[](Int_t rown) const { return TMatrixTSparseRow_const<Element>(*this,rown); }
   inline       TMatrixTSparseRow      <Element> operator[](Int_t rown)       { return TMatrixTSparseRow      <Element>(*this,rown); }

   TMatrixTSparse<Element> &operator=(const TMatrixT<Element>       &source);
   TMatrixTSparse<Element> &operator=(const TMatrixTSparse<Element> &source);

   TMatrixTSparse<Element> &operator= (Element val);
   TMatrixTSparse<Element> &operator-=(Element val);
   TMatrixTSparse<Element> &operator+=(Element val);
   TMatrixTSparse<Element> &operator*=(Element val);

   TMatrixTSparse<Element> &operator+=(const TMatrixTSparse<Element> &source) { TMatrixTSparse<Element> tmp(*this); Clear();
                                                                                if (this == &source) APlusB (tmp,tmp,1);
                                                                                else                 APlusB (tmp,source,1);
                                                                                return *this; }
   TMatrixTSparse<Element> &operator+=(const TMatrixT<Element>       &source) { TMatrixTSparse<Element> tmp(*this); Clear();
                                                                                APlusB(tmp,source,1); return *this; }
   TMatrixTSparse<Element> &operator-=(const TMatrixTSparse<Element> &source) { TMatrixTSparse<Element> tmp(*this); Clear();
                                                                                if (this == &source) AMinusB (tmp,tmp,1);
                                                                                else                 AMinusB(tmp,source,1);
                                                                                return *this; }
   TMatrixTSparse<Element> &operator-=(const TMatrixT<Element>       &source) { TMatrixTSparse<Element> tmp(*this); Clear();
                                                                                AMinusB(tmp,source,1); return *this; }
   TMatrixTSparse<Element> &operator*=(const TMatrixTSparse<Element> &source) { TMatrixTSparse<Element> tmp(*this); Clear();
                                                                                if (this == &source) AMultB (tmp,tmp,1);
                                                                                else                 AMultB (tmp,source,1);
                                                                                return *this; }
   TMatrixTSparse<Element> &operator*=(const TMatrixT<Element>       &source) { TMatrixTSparse<Element> tmp(*this); Clear();
                                                                                AMultB(tmp,source,1);
                                                                                return *this; }

   virtual TMatrixTBase  <Element> &Randomize  (Element alpha,Element beta,Double_t &seed);
   virtual TMatrixTSparse<Element> &RandomizePD(Element alpha,Element beta,Double_t &seed);

   ClassDef(TMatrixTSparse,3) // Template of Sparse Matrix class
};

#ifndef __CINT__
// When building with -fmodules, it instantiates all pending instantiations,
// instead of delaying them until the end of the translation unit.
// We 'got away with' probably because the use and the definition of the
// explicit specialization do not occur in the same TU.
//
// In case we are building with -fmodules, we need to forward declare the
// specialization in order to compile the dictionary G__Matrix.cxx.
template <> TClass *TMatrixTSparse<double>::Class();
#endif // __CINT__

template <class Element> inline const Element *TMatrixTSparse<Element>::GetMatrixArray  () const { return fElements; }
template <class Element> inline       Element *TMatrixTSparse<Element>::GetMatrixArray  ()       { return fElements; }
template <class Element> inline const Int_t   *TMatrixTSparse<Element>::GetRowIndexArray() const { return fRowIndex; }
template <class Element> inline       Int_t   *TMatrixTSparse<Element>::GetRowIndexArray()       { return fRowIndex; }
template <class Element> inline const Int_t   *TMatrixTSparse<Element>::GetColIndexArray() const { return fColIndex; }
template <class Element> inline       Int_t   *TMatrixTSparse<Element>::GetColIndexArray()       { return fColIndex; }

template <class Element>
inline       TMatrixTSparse<Element> &TMatrixTSparse<Element>::Use   (Int_t nrows,Int_t ncols,Int_t nr_nonzeros,
                                                                      Int_t *pRowIndex,Int_t *pColIndex,Element *pData)
                                                                        { return Use(0,nrows-1,0,ncols-1,nr_nonzeros,pRowIndex,pColIndex,pData); }
template <class Element>
inline const TMatrixTSparse<Element> &TMatrixTSparse<Element>::Use   (Int_t nrows,Int_t ncols,Int_t nr_nonzeros,
                                                                      const Int_t *pRowIndex,const Int_t *pColIndex,const Element *pData) const
                                                                        { return Use(0,nrows-1,0,ncols-1,nr_nonzeros,pRowIndex,pColIndex,pData); }
template <class Element>
inline       TMatrixTSparse<Element> &TMatrixTSparse<Element>::Use   (TMatrixTSparse<Element> &a)
                                                                        { R__ASSERT(a.IsValid());
                                                                           return Use(a.GetRowLwb(),a.GetRowUpb(),a.GetColLwb(),a.GetColUpb(),
                                                                                      a.GetNoElements(),a.GetRowIndexArray(),
                                                                                      a.GetColIndexArray(),a.GetMatrixArray()); }
template <class Element>
inline const TMatrixTSparse<Element> &TMatrixTSparse<Element>::Use   (const TMatrixTSparse<Element> &a) const
                                                                        { R__ASSERT(a.IsValid());
                                                                           return Use(a.GetRowLwb(),a.GetRowUpb(),a.GetColLwb(),a.GetColUpb(),
                                                                                      a.GetNoElements(),a.GetRowIndexArray(),
                                                                                      a.GetColIndexArray(),a.GetMatrixArray()); }

template <class Element>
inline       TMatrixTSparse<Element>  TMatrixTSparse<Element>::GetSub(Int_t row_lwb,Int_t row_upb,Int_t col_lwb,Int_t col_upb,
                                                                      Option_t *option) const
                                                                        {
                                                                          TMatrixTSparse<Element> tmp;
                                                                          this->GetSub(row_lwb,row_upb,col_lwb,col_upb,tmp,option);
                                                                          return tmp;
                                                                        }

template <class Element> TMatrixTSparse<Element>  operator+ (const TMatrixTSparse<Element> &source1,const TMatrixTSparse<Element> &source2);
template <class Element> TMatrixTSparse<Element>  operator+ (const TMatrixTSparse<Element> &source1,const TMatrixT<Element>       &source2);
template <class Element> TMatrixTSparse<Element>  operator+ (const TMatrixT<Element>       &source1,const TMatrixTSparse<Element> &source2);
template <class Element> TMatrixTSparse<Element>  operator+ (const TMatrixTSparse<Element> &source ,      Element                  val    );
template <class Element> TMatrixTSparse<Element>  operator+ (      Element                  val    ,const TMatrixTSparse<Element> &source );
template <class Element> TMatrixTSparse<Element>  operator- (const TMatrixTSparse<Element> &source1,const TMatrixTSparse<Element> &source2);
template <class Element> TMatrixTSparse<Element>  operator- (const TMatrixTSparse<Element> &source1,const TMatrixT<Element>       &source2);
template <class Element> TMatrixTSparse<Element>  operator- (const TMatrixT<Element>       &source1,const TMatrixTSparse<Element> &source2);
template <class Element> TMatrixTSparse<Element>  operator- (const TMatrixTSparse<Element> &source ,      Element                  val    );
template <class Element> TMatrixTSparse<Element>  operator- (      Element                  val    ,const TMatrixTSparse<Element> &source );
template <class Element> TMatrixTSparse<Element>  operator* (const TMatrixTSparse<Element> &source1,const TMatrixTSparse<Element> &source2);
template <class Element> TMatrixTSparse<Element>  operator* (const TMatrixTSparse<Element> &source1,const TMatrixT<Element>       &source2);
template <class Element> TMatrixTSparse<Element>  operator* (const TMatrixT<Element>       &source1,const TMatrixTSparse<Element> &source2);
template <class Element> TMatrixTSparse<Element>  operator* (      Element                  val    ,const TMatrixTSparse<Element> &source );
template <class Element> TMatrixTSparse<Element>  operator* (const TMatrixTSparse<Element> &source,       Element                  val    );

template <class Element> TMatrixTSparse<Element> &Add        (TMatrixTSparse<Element> &target,      Element                   scalar,
                                                              const TMatrixTSparse<Element> &source);
template <class Element> TMatrixTSparse<Element> &ElementMult(TMatrixTSparse<Element> &target,const TMatrixTSparse<Element>  &source);
template <class Element> TMatrixTSparse<Element> &ElementDiv (TMatrixTSparse<Element> &target,const TMatrixTSparse<Element>  &source);

template <class Element> Bool_t AreCompatible(const TMatrixTSparse<Element> &m1,const TMatrixTSparse<Element> &m2,Int_t verbose=0);

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TVectorDfwd
#define ROOT_TVectorDfwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TVectorD                                                             //
//                                                                      //
//  Forward declaration of TVectorT<Double_t>                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TVectorT;
typedef TVectorT<Double_t> TVectorD;

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDUtilsfwd
#define ROOT_TMatrixDUtilsfwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Matrix utility classes.                                              //
//                                                                      //
//  Forward declaration of                                              //
//   TMatrixTRow_const       <Double_t>  TMatrixTRow       <Double_t>   //
//   TMatrixTColumn_const    <Double_t>  TMatrixTColumn    <Double_t>   //
//   TMatrixTDiag_const      <Double_t>  TMatrixTDiag      <Double_t>   //
//   TMatrixTFlat_const      <Double_t>  TMatrixTFlat      <Double_t>   //
//   TMatrixTSub_const       <Double_t>  TMatrixTSub       <Double_t>   //
//   TMatrixTSparseRow_const <Double_t>  TMatrixTSparseRow <Double_t>   //
//   TMatrixTSparseDiag_const<Double_t>  TMatrixTSparseDiag<Double_t>   //
//                                                                      //
//   TElementActionT   <Double_t>                                       //
//   TElementPosActionT<Double_t>                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixTRow_const;
template<class Element> class TMatrixTColumn_const;
template<class Element> class TMatrixTDiag_const;
template<class Element> class TMatrixTFlat_const;
template<class Element> class TMatrixTSub_const;
template<class Element> class TMatrixTSparseRow_const;
template<class Element> class TMatrixTSparseDiag_const;

template<class Element> class TMatrixTRow;
template<class Element> class TMatrixTColumn;
template<class Element> class TMatrixTDiag;
template<class Element> class TMatrixTFlat;
template<class Element> class TMatrixTSub;
template<class Element> class TMatrixTSparseRow;
template<class Element> class TMatrixTSparseDiag;

template<class Element> class TElementActionT;
template<class Element> class TElementPosActionT;

typedef TMatrixTRow_const       <Double_t> TMatrixDRow_const;
typedef TMatrixTColumn_const    <Double_t> TMatrixDColumn_const;
typedef TMatrixTDiag_const      <Double_t> TMatrixDDiag_const;
typedef TMatrixTFlat_const      <Double_t> TMatrixDFlat_const;
typedef TMatrixTSub_const       <Double_t> TMatrixDSub_const;
typedef TMatrixTSparseRow_const <Double_t> TMatrixDSparseRow_const;
typedef TMatrixTSparseDiag_const<Double_t> TMatrixDSparseDiag_const;

typedef TMatrixTRow             <Double_t> TMatrixDRow;
typedef TMatrixTColumn          <Double_t> TMatrixDColumn;
typedef TMatrixTDiag            <Double_t> TMatrixDDiag;
typedef TMatrixTFlat            <Double_t> TMatrixDFlat;
typedef TMatrixTSub             <Double_t> TMatrixDSub;
typedef TMatrixTSparseRow       <Double_t> TMatrixDSparseRow;
typedef TMatrixTSparseDiag      <Double_t> TMatrixDSparseDiag;

typedef TElementActionT         <Double_t> TElementActionD;
typedef TElementPosActionT      <Double_t> TElementPosActionD;

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDUtils
#define ROOT_TMatrixDUtils

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Matrix utility classes.                                              //
//                                                                      //
//  Instantation of                                                     //
//   TMatrixTRow_const       <Double_t>  TMatrixTRow       <Double_t>   //
//   TMatrixTColumn_const    <Double_t>  TMatrixTColumn    <Double_t>   //
//   TMatrixTDiag_const      <Double_t>  TMatrixTDiag      <Double_t>   //
//   TMatrixTFlat_const      <Double_t>  TMatrixTFlat      <Double_t>   //
//   TMatrixTSub_const       <Double_t>  TMatrixTSub       <Double_t>   //
//   TMatrixTSparseRow_const <Double_t>  TMatrixTSparseRow <Double_t>   //
//   TMatrixTSparseDiag_const<Double_t>  TMatrixTSparseDiag<Double_t>   //
//                                                                      //
//   TElementActionT   <Double_t>                                       //
//   TElementPosActionT<Double_t>                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixTUtils.h"
//#include "TMatrixDUtilsfwd.h"

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDSparsefwd
#define ROOT_TMatrixDSparsefwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixDSparse                                                       //
//                                                                      //
//  Forward declaration of TMatrixTSparse<Double_t>                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixTSparse;
typedef TMatrixTSparse<Double_t> TMatrixDSparse;

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDSymfwd
#define ROOT_TMatrixDSymfwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixDSym                                                          //
//                                                                      //
//  Forward declaration of TMatrixTSym<Double_t>                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixTSym;
typedef TMatrixTSym<Double_t> TMatrixDSym;

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDfwd
#define ROOT_TMatrixDfwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixD                                                             //
//                                                                      //
//  Forward declaration of TMatrixT<Double_t>                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixT;
typedef TMatrixT<Double_t> TMatrixD;

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixFSparsefwd
#define ROOT_TMatrixFSparsefwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixFSparse                                                       //
//                                                                      //
//  Forward declaration of TMatrixTSparse<Float_t>                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixTSparse;
typedef TMatrixTSparse<Float_t> TMatrixFSparse;

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixFSymfwd
#define ROOT_TMatrixFSymfwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixFSym                                                          //
//                                                                      //
//  Forward declaration of TMatrixTSym<Float_t>                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixTSym;
typedef TMatrixTSym<Float_t> TMatrixFSym;

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixFfwd
#define ROOT_TMatrixFfwd

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixF                                                             //
//                                                                      //
//  Forward declaration of TMatrixT<Float_t>                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

template<class Element> class TMatrixT;
typedef TMatrixT<Float_t> TMatrixF;

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Feb 2004

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDSparse
#define ROOT_TMatrixDSparse

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixDSparse                                                       //
//                                                                      //
//  Instantation of TMatrixTSparse<Double_t>                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixTSparse.h"
//#include "TMatrixDSparsefwd.h"
//#include "TMatrixDUtils.h"

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDSym
#define ROOT_TMatrixDSym

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixDSym                                                          //
//                                                                      //
//  Instantation of TMatrixTSym<Double_t>                               //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixTSym.h"
//#include "TMatrixDSymfwd.h"
//#include "TMatrixDUtils.h"

#endif

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixD
#define ROOT_TMatrixD

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixD                                                             //
//                                                                      //
//  Instantation of TMatrixT<Double_t>                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixT.h"
//#include "TMatrixDfwd.h"
//#include "TMatrixDUtils.h"

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Nov 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TVectorT
#define ROOT_TVectorT

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TVectorT                                                             //
//                                                                      //
// Template class of Vectors in the linear algebra package              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixT.h"
//#include "TMatrixTSym.h"
//#include "TMatrixTSparse.h"

template<class Element> class TVectorT : public TObject {

protected:
   Int_t    fNrows{0};                // number of rows
   Int_t    fRowLwb{0};               // lower bound of the row index
   Element *fElements{nullptr};             //[fNrows] elements themselves

   enum {kSizeMax = 5};             // size data container on stack, see New_m(),Delete_m()
   enum {kWorkMax = 100};           // size of work array's in several routines

   Element  fDataStack[kSizeMax];  //! data container
   Bool_t   fIsOwner{kTRUE};              //!default kTRUE, when Use array kFALSE

   Element* New_m   (Int_t size);
   void     Delete_m(Int_t size,Element*&);
   Int_t    Memcpy_m(Element *newp,const Element *oldp,Int_t copySize,
                     Int_t newSize,Int_t oldSize);

   void     Allocate(Int_t nrows,Int_t row_lwb = 0,Int_t init = 0);

   enum EVectorStatusBits {
     kStatus = BIT(14) // set if vector object is valid
   };

public:

   TVectorT() : fNrows(0), fRowLwb(0), fElements(0), fDataStack (), fIsOwner(kTRUE) { }
   explicit TVectorT(Int_t n);
   TVectorT(Int_t lwb,Int_t upb);
   TVectorT(Int_t n,const Element *elements);
   TVectorT(Int_t lwb,Int_t upb,const Element *elements);
   TVectorT(const TVectorT            <Element> &another);
   TVectorT(const TMatrixTRow_const   <Element> &mr);
   TVectorT(const TMatrixTColumn_const<Element> &mc);
   TVectorT(const TMatrixTDiag_const  <Element> &md);
   template <class Element2> TVectorT(const TVectorT<Element2> &another)
   {
      R__ASSERT(another.IsValid());
      Allocate(another.GetUpb()-another.GetLwb()+1,another.GetLwb());
      *this = another;
   }
#ifndef __CINT__
   TVectorT(Int_t lwb,Int_t upb,Double_t iv1, ...);
#endif
   virtual ~TVectorT() { Clear(); }

   inline          Int_t     GetLwb       () const { return fRowLwb; }
   inline          Int_t     GetUpb       () const { return fNrows+fRowLwb-1; }
   inline          Int_t     GetNrows     () const { return fNrows; }
   inline          Int_t     GetNoElements() const { return fNrows; }

   inline          Element  *GetMatrixArray  ()       { return fElements; }
   inline const    Element  *GetMatrixArray  () const { return fElements; }

   inline void     Invalidate ()       { SetBit(kStatus); }
   inline void     MakeValid  ()       { ResetBit(kStatus); }
   inline Bool_t   IsValid    () const { return !TestBit(kStatus); }
   inline Bool_t   IsOwner    () const { return fIsOwner; }
   inline void     SetElements(const Element *elements) { R__ASSERT(IsValid());
                                                          memcpy(fElements,elements,fNrows*sizeof(Element)); }
   inline TVectorT<Element> &Shift     (Int_t row_shift)            { fRowLwb += row_shift; return *this; }
          TVectorT<Element> &ResizeTo  (Int_t lwb,Int_t upb);
   inline TVectorT<Element> &ResizeTo  (Int_t n)                    { return ResizeTo(0,n-1); }
   inline TVectorT<Element> &ResizeTo  (const TVectorT<Element> &v) { return ResizeTo(v.GetLwb(),v.GetUpb()); }

          TVectorT<Element> &Use       (Int_t lwb,Int_t upb,Element *data);
   const  TVectorT<Element> &Use       (Int_t lwb,Int_t upb,const Element *data) const
          { return (const TVectorT<Element>&)(const_cast<TVectorT<Element> *>(this))->Use(lwb,upb,const_cast<Element *>(data)); }
          TVectorT<Element> &Use       (Int_t n,Element *data);
   const  TVectorT<Element> &Use       (Int_t n,const Element *data) const ;
          TVectorT<Element> &Use       (TVectorT<Element> &v);
   const  TVectorT<Element> &Use       (const TVectorT<Element> &v) const ;

          TVectorT<Element> &GetSub    (Int_t row_lwb,Int_t row_upb,TVectorT<Element> &target,Option_t *option="S") const;
          TVectorT<Element>  GetSub    (Int_t row_lwb,Int_t row_upb,Option_t *option="S") const;
          TVectorT<Element> &SetSub    (Int_t row_lwb,const TVectorT<Element> &source);

   TVectorT<Element> &Zero();
   TVectorT<Element> &Abs ();
   TVectorT<Element> &Sqr ();
   TVectorT<Element> &Sqrt();
   TVectorT<Element> &Invert();
   TVectorT<Element> &SelectNonZeros(const TVectorT<Element> &select);

   Element Norm1   () const;
   Element Norm2Sqr() const;
   Element NormInf () const;
   Int_t   NonZeros() const;
   Element Sum     () const;
   Element Min     () const;
   Element Max     () const;

   inline const Element &operator()(Int_t index) const;
   inline       Element &operator()(Int_t index);
   inline const Element &operator[](Int_t index) const { return (*this)(index); }
   inline       Element &operator[](Int_t index)       { return (*this)(index); }

   TVectorT<Element> &operator= (const TVectorT                <Element> &source);
   TVectorT<Element> &operator= (const TMatrixTRow_const       <Element> &mr);
   TVectorT<Element> &operator= (const TMatrixTColumn_const    <Element> &mc);
   TVectorT<Element> &operator= (const TMatrixTDiag_const      <Element> &md);
   TVectorT<Element> &operator= (const TMatrixTSparseRow_const <Element> &md);
   TVectorT<Element> &operator= (const TMatrixTSparseDiag_const<Element> &md);
   template <class Element2> TVectorT<Element> &operator= (const TVectorT<Element2> &source)
   {
      if (!AreCompatible(*this,source)) {
         //Error("operator=(const TVectorT2 &)","vectors not compatible");
         return *this;
      }

     TObject::operator=(source);
     const Element2 * const ps = source.GetMatrixArray();
           Element  * const pt = GetMatrixArray();
     for (Int_t i = 0; i < this->fNrows; i++)
        pt[i] = ps[i];
     return *this;
   }

   TVectorT<Element> &operator= (Element val);
   TVectorT<Element> &operator+=(Element val);
   TVectorT<Element> &operator-=(Element val);
   TVectorT<Element> &operator*=(Element val);

   TVectorT<Element> &operator+=(const TVectorT      <Element> &source);
   TVectorT<Element> &operator-=(const TVectorT      <Element> &source);
   TVectorT<Element> &operator*=(const TMatrixT      <Element> &a);
   TVectorT<Element> &operator*=(const TMatrixTSym   <Element> &a);
   TVectorT<Element> &operator*=(const TMatrixTSparse<Element> &a);

   Bool_t operator==(Element val) const;
   Bool_t operator!=(Element val) const;
   Bool_t operator< (Element val) const;
   Bool_t operator<=(Element val) const;
   Bool_t operator> (Element val) const;
   Bool_t operator>=(Element val) const;

   Bool_t MatchesNonZeroPattern(const TVectorT<Element> &select);
   Bool_t SomePositive         (const TVectorT<Element> &select);
   void   AddSomeConstant      (Element val,const TVectorT<Element> &select);

   void   Randomize            (Element alpha,Element beta,Double_t &seed);

   TVectorT<Element> &Apply(const TElementActionT   <Element> &action);
   TVectorT<Element> &Apply(const TElementPosActionT<Element> &action);

   void Add(const TVectorT<Element> &v);
   void Add(const TVectorT<Element> &v1, const TVectorT<Element> &v2);
   void Clear(Option_t * /*option*/ ="") { if (fIsOwner) Delete_m(fNrows,fElements);
                                           else fElements = 0;
                                           fNrows = 0; }
   void Draw (Option_t *option=""); // *MENU*
   void Print(Option_t *option="") const;  // *MENU*

   ClassDef(TVectorT,4)  // Template of Vector class
};

#ifndef __CINT__
// When building with -fmodules, it instantiates all pending instantiations,
// instead of delaying them until the end of the translation unit.
// We 'got away with' probably because the use and the definition of the
// explicit specialization do not occur in the same TU.
//
// In case we are building with -fmodules, we need to forward declare the
// specialization in order to compile the dictionary G__Matrix.cxx.
template <> TClass *TVectorT<double>::Class();
#endif // __CINT__

template<class Element> inline       TVectorT<Element> &TVectorT<Element>::Use     (Int_t n,Element *data) { return Use(0,n-1,data); }
template<class Element> inline const TVectorT<Element> &TVectorT<Element>::Use     (Int_t n,const Element *data) const { return Use(0,n-1,data); }
template<class Element> inline       TVectorT<Element> &TVectorT<Element>::Use     (TVectorT &v)
                                                                                   {
                                                                                     R__ASSERT(v.IsValid());
                                                                                     return Use(v.GetLwb(),v.GetUpb(),v.GetMatrixArray());
                                                                                   }
template<class Element> inline const TVectorT<Element> &TVectorT<Element>::Use     (const TVectorT &v) const
                                                                                   {
                                                                                     R__ASSERT(v.IsValid());
                                                                                     return Use(v.GetLwb(),v.GetUpb(),v.GetMatrixArray());
                                                                                   }
template<class Element> inline       TVectorT<Element>  TVectorT<Element>::GetSub  (Int_t row_lwb,Int_t row_upb,Option_t *option) const
                                                                                   {
                                                                                     TVectorT tmp;
                                                                                     this->GetSub(row_lwb,row_upb,tmp,option);
                                                                                     return tmp;
                                                                                   }

template<class Element> inline const Element &TVectorT<Element>::operator()(Int_t ind) const
{
   // Access a vector element.

   R__ASSERT(IsValid());
   const Int_t aind = ind-fRowLwb;
   if (aind >= fNrows || aind < 0) {
      //Error("operator()","Request index(%d) outside vector range of %d - %d",ind,fRowLwb,fRowLwb+fNrows);
      return TMatrixTBase<Element>::NaNValue();
   }

   return fElements[aind];
}
template<class Element> inline Element &TVectorT<Element>::operator()(Int_t ind)
{
   // Access a vector element.

   R__ASSERT(IsValid());
   const Int_t aind = ind-fRowLwb;
   if (aind >= fNrows || aind < 0) {
      //Error("operator()","Request index(%d) outside vector range of %d - %d",ind,fRowLwb,fRowLwb+fNrows);
      return TMatrixTBase<Element>::NaNValue();
   }

   return fElements[aind];
}

template<class Element> Bool_t              operator==  (const TVectorT      <Element>  &source1,const TVectorT <Element>  &source2);
template<class Element> TVectorT<Element>   operator+   (const TVectorT      <Element>  &source1,const TVectorT <Element>  &source2);
template<class Element> TVectorT<Element>   operator-   (const TVectorT      <Element>  &source1,const TVectorT <Element>  &source2);
template<class Element> Element             operator*   (const TVectorT      <Element>  &source1,const TVectorT <Element>  &source2);
template<class Element> TVectorT<Element>   operator*   (const TMatrixT      <Element>  &a,      const TVectorT <Element>  &source);
template<class Element> TVectorT<Element>   operator*   (const TMatrixTSym   <Element>  &a,      const TVectorT <Element>  &source);
template<class Element> TVectorT<Element>   operator*   (const TMatrixTSparse<Element>  &a,      const TVectorT <Element>  &source);
template<class Element> TVectorT<Element>   operator*   (      Element                   val,    const TVectorT <Element>  &source);
template<class Element>
inline
TVectorT<Element> operator*   (const TVectorT <Element>  &source, Element val) { return val * source; }

template<class Element> Element             Dot         (const TVectorT      <Element>  &source1,const TVectorT <Element>  &source2);
template <class Element1,class Element2>
                        TMatrixT<Element1>  OuterProduct(const TVectorT      <Element1> &v1,     const TVectorT <Element2> &v2);
template <class Element1,class Element2,class Element3>
                        TMatrixT<Element1> &OuterProduct(      TMatrixT      <Element1> &target, const TVectorT <Element2> &v1,     const TVectorT      <Element3> &v2);
template <class Element1,class Element2,class Element3>
                        Element1            Mult        (const TVectorT      <Element1> &v1,     const TMatrixT <Element2> &m,      const TVectorT      <Element3> &v2);

template<class Element> TVectorT<Element>  &Add         (      TVectorT      <Element>  &target,       Element              scalar, const TVectorT      <Element>  &source);
template<class Element> TVectorT<Element>  &Add         (      TVectorT      <Element>  &target,       Element              scalar, const TMatrixT      <Element>  &a,
                                                         const TVectorT<Element> &source);
template<class Element> TVectorT<Element>  &Add         (      TVectorT      <Element>  &target,       Element              scalar, const TMatrixTSym   <Element>  &a,
                                                         const TVectorT<Element> &source);
template<class Element> TVectorT<Element>  &Add         (      TVectorT      <Element>  &target,       Element              scalar, const TMatrixTSparse<Element>  &a,
                                                         const TVectorT<Element> &source);
template<class Element> TVectorT<Element>  &AddElemMult (      TVectorT      <Element>  &target,       Element              scalar, const TVectorT      <Element>  &source1,
                                                         const TVectorT      <Element>  &source2);
template<class Element> TVectorT<Element>  &AddElemMult (      TVectorT      <Element>  &target,       Element              scalar, const TVectorT      <Element>  &source1,
                                                         const TVectorT      <Element>  &source2,const TVectorT <Element>  &select);
template<class Element> TVectorT<Element>  &AddElemDiv  (      TVectorT      <Element>  &target,       Element              scalar, const TVectorT      <Element>  &source1,
                                                         const TVectorT      <Element>  &source2);
template<class Element> TVectorT<Element>  &AddElemDiv  (      TVectorT      <Element>  &target,       Element              scalar, const TVectorT      <Element>  &source1,
                                                         const TVectorT      <Element>  &source2,const TVectorT <Element>  &select);
template<class Element> TVectorT<Element>  &ElementMult (      TVectorT      <Element>  &target, const TVectorT <Element>  &source);
template<class Element> TVectorT<Element>  &ElementMult (      TVectorT      <Element>  &target, const TVectorT <Element>  &source, const TVectorT      <Element>  &select);
template<class Element> TVectorT<Element>  &ElementDiv  (      TVectorT      <Element>  &target, const TVectorT <Element>  &source);
template<class Element> TVectorT<Element>  &ElementDiv  (      TVectorT      <Element>  &target, const TVectorT <Element>  &source, const TVectorT      <Element>  &select);

template<class Element1,class Element2> Bool_t AreCompatible(const TVectorT<Element1> &v1,const TVectorT<Element2> &v2,Int_t verbose=0);
// Check matrix and vector for compatibility in multiply:  M * v and v * M
template<class Element1,class Element2> Bool_t AreCompatible(const TMatrixT<Element1> &m, const TVectorT<Element2> &v, Int_t verbose=0);
template<class Element1,class Element2> Bool_t AreCompatible(const TVectorT<Element1> &v, const TMatrixT<Element2> &m, Int_t verbose=0);

template<class Element> void   Compare              (const TVectorT <Element>  &source1,const TVectorT <Element>  &source2);
template<class Element> Bool_t VerifyVectorValue    (const TVectorT <Element>  &m,            Element val,Int_t verbose, Element maxDevAllow);
template<class Element> Bool_t VerifyVectorValue    (const TVectorT <Element>  &m,            Element val,Int_t verbose)
                                                     { return VerifyVectorValue(m,val,verbose,Element(0.0)); }
template<class Element> Bool_t VerifyVectorValue    (const TVectorT <Element>  &m,            Element val)
                                                     { return VerifyVectorValue(m,val,1,Element(0.0)); }
template<class Element> Bool_t VerifyVectorIdentity (const TVectorT <Element>  &m1,const TVectorT <Element> &m2, Int_t verbose, Element maxDevAllow);
template<class Element> Bool_t VerifyVectorIdentity (const TVectorT <Element>  &m1,const TVectorT <Element> &m2, Int_t verbose)
                                                     { return VerifyVectorIdentity(m1,m2,verbose,Element(0.0)); }
template<class Element> Bool_t VerifyVectorIdentity (const TVectorT <Element>  &m1,const TVectorT <Element> &m2)
                                                     { return VerifyVectorIdentity(m1,m2,1,Element(0.0)); }

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDEigen
#define ROOT_TMatrixDEigen

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixDEigen                                                        //
//                                                                      //
// Eigenvalues and eigenvectors of a real matrix.                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixD.h"
//#include "TVectorD.h"

class TMatrixDEigen
{
protected :

   static void MakeHessenBerg  (TMatrixD &v,TVectorD &ortho,TMatrixD &H);
   static void MakeSchurr      (TMatrixD &v,TVectorD &d,    TVectorD &e,TMatrixD &H);
   static void Sort            (TMatrixD &v,TVectorD &d,    TVectorD &e);

   TMatrixD fEigenVectors;   // Eigen-vectors of matrix
   TVectorD fEigenValuesRe;  // Eigen-values
   TVectorD fEigenValuesIm;  // Eigen-values

public :

   enum {kWorkMax = 100}; // size of work array

   TMatrixDEigen()
     : fEigenVectors(), fEigenValuesRe(), fEigenValuesIm() {};
   TMatrixDEigen(const TMatrixD &a);
   TMatrixDEigen(const TMatrixDEigen &another);
   virtual ~TMatrixDEigen() {}

// If matrix A has shape (rowLwb,rowUpb,rowLwb,rowUpb), then each eigen-vector
// must have an index running between (rowLwb,rowUpb) .
// For convenience, the column index of the eigen-vector matrix
// also runs from rowLwb to rowUpb so that the returned matrix
// has also index/shape (rowLwb,rowUpb,rowLwb,rowUpb) .
// The same is true for the eigen-value vectors an matrix .

   const TMatrixD &GetEigenVectors () const { return fEigenVectors;  }
   const TVectorD &GetEigenValuesRe() const { return fEigenValuesRe; }
   const TVectorD &GetEigenValuesIm() const { return fEigenValuesIm; }
   const TMatrixD  GetEigenValues  () const;

   TMatrixDEigen &operator= (const TMatrixDEigen &source);

   ClassDef(TMatrixDEigen,1) // Eigen-Vectors/Values of a Matrix
};
#endif

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



#ifndef ROOT_TVectorD
#define ROOT_TVectorD

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TVectorD                                                             //
//                                                                      //
//  Instantation of TVectorT<Double_t>                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TVectorT.h"
//#include "TVectorDfwd.h"
//#include "TMatrixD.h"
//#include "TMatrixDSym.h"
//#include "TMatrixDSparse.h"

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TDecompBase
#define ROOT_TDecompBase

///////////////////////////////////////////////////////////////////////////
//                                                                       //
// Decomposition Base class                                              //
//                                                                       //
// This class forms the base for all the decompositions methods in the   //
// linear algebra package .                                              //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

//#include "Rtypes.h"

//#include "TMatrixD.h"
//#include "TMatrixDUtils.h"
//#include "TObject.h"
//#include "TVectorD.h"

#include <limits>

class TDecompBase : public TObject
{
protected :
   Double_t fTol;       // sqrt(epsilon); epsilon is smallest number number so that  1+epsilon > 1
   Double_t fDet1;      // determinant mantissa
   Double_t fDet2;      // determinant exponent for powers of 2
   Double_t fCondition; // matrix condition number
   Int_t    fRowLwb;    // Row    lower bound of decomposed matrix
   Int_t    fColLwb;    // Column lower bound of decomposed matrix

   void          ResetStatus() { for (Int_t i = 14; i < 22; i++) ResetBit(BIT(i)); }
   Int_t         Hager      (Double_t& est,Int_t iter=5);
   static  void  DiagProd   (const TVectorD &diag,Double_t tol,Double_t &d1,Double_t &d2);

   virtual const TMatrixDBase &GetDecompMatrix() const = 0;

   enum EMatrixDecompStat {
      kInit       = BIT(14),
      kPatternSet = BIT(15),
      kValuesSet  = BIT(16),
      kMatrixSet  = BIT(17),
      kDecomposed = BIT(18),
      kDetermined = BIT(19),
      kCondition  = BIT(20),
      kSingular   = BIT(21)
   };

   enum {kWorkMax = 100}; // size of work array's in several routines

public :
   TDecompBase();
   TDecompBase(const TDecompBase &another);
   virtual ~TDecompBase() {};

   inline  Double_t GetTol       () const { return fTol; }
   inline  Double_t GetDet1      () const { return fDet1; }
   inline  Double_t GetDet2      () const { return fDet2; }
   inline  Double_t GetCondition () const { return fCondition; }
   virtual Int_t    GetNrows     () const = 0;
   virtual Int_t    GetNcols     () const = 0;
   Int_t            GetRowLwb    () const { return fRowLwb; }
   Int_t            GetColLwb    () const { return fColLwb; }
   inline Double_t  SetTol       (Double_t tol);

   virtual Double_t Condition  ();
   virtual void     Det        (Double_t &d1,Double_t &d2);
   virtual Bool_t   Decompose  ()                             = 0;
   virtual Bool_t   Solve      (      TVectorD &b)            = 0;
   virtual TVectorD Solve      (const TVectorD& b,Bool_t &ok) = 0;
   virtual Bool_t   Solve      (      TMatrixDColumn& b)      = 0;
   virtual Bool_t   TransSolve (      TVectorD &b)            = 0;
   virtual TVectorD TransSolve (const TVectorD &b,Bool_t &ok) = 0;
   virtual Bool_t   TransSolve (      TMatrixDColumn& b)      = 0;

   virtual Bool_t   MultiSolve (TMatrixD &B);

   void Print(Option_t *opt="") const;

   TDecompBase &operator= (const TDecompBase &source);

   ClassDef(TDecompBase,2) // Matrix Decomposition Base
};

Double_t TDecompBase::SetTol(Double_t newTol)
{
   const Double_t oldTol = fTol;
   if (newTol >= 0.0)
      fTol = newTol;
   return oldTol;
}

Bool_t DefHouseHolder  (const TVectorD &vc,Int_t     lp,Int_t     l,Double_t &up,Double_t &b,Double_t tol=0.0);
void   ApplyHouseHolder(const TVectorD &vc,Double_t  up,Double_t  b,Int_t     lp,Int_t     l,TMatrixDRow &cr);
void   ApplyHouseHolder(const TVectorD &vc,Double_t  up,Double_t  b,Int_t     lp,Int_t     l,TMatrixDColumn &cc);
void   ApplyHouseHolder(const TVectorD &vc,Double_t  up,Double_t  b,Int_t     lp,Int_t     l,TVectorD &cv);
void   DefGivens       (      Double_t  v1,Double_t  v2,Double_t &c,Double_t &s);
void   DefAplGivens    (      Double_t &v1,Double_t &v2,Double_t &c,Double_t &s);
void   ApplyGivens     (      Double_t &z1,Double_t &z2,Double_t  c,Double_t  s);

#endif


// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TDecompLU
#define ROOT_TDecompLU

///////////////////////////////////////////////////////////////////////////
//                                                                       //
// LU Decomposition class                                                //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

//#include "TDecompBase.h"

class TDecompLU : public TDecompBase
{
protected :

   Int_t     fImplicitPivot; // control to determine implicit row scale before
                             //  deciding on the pivot (Crout method)
   Int_t     fNIndex;        // size of row permutation index
   Int_t    *fIndex;         //[fNIndex] row permutation index
   Double_t  fSign;          // = +/- 1 reflecting even/odd row permutations, resp.
   TMatrixD  fLU;            // decomposed matrix so that a = l u where
                             // l is stored lower left and u upper right side

   static Bool_t DecomposeLUCrout(TMatrixD &lu,Int_t *index,Double_t &sign,Double_t tol,Int_t &nrZeros);
   static Bool_t DecomposeLUGauss(TMatrixD &lu,Int_t *index,Double_t &sign,Double_t tol,Int_t &nrZeros);

   virtual const TMatrixDBase &GetDecompMatrix() const { return fLU; }

public :

   TDecompLU();
   explicit TDecompLU(Int_t nrows);
   TDecompLU(Int_t row_lwb,Int_t row_upb);
   TDecompLU(const TMatrixD &m,Double_t tol = 0.0,Int_t implicit = 1);
   TDecompLU(const TDecompLU &another);
   virtual ~TDecompLU() {if (fIndex) delete [] fIndex; fIndex = 0; }

           const TMatrixD  GetMatrix ();
   virtual       Int_t     GetNrows  () const { return fLU.GetNrows(); }
   virtual       Int_t     GetNcols  () const { return fLU.GetNcols(); }
           const TMatrixD &GetLU     ()       { if ( !TestBit(kDecomposed) ) Decompose();
                                                return fLU; }

   virtual       void      SetMatrix (const TMatrixD &a);

   virtual Bool_t   Decompose  ();
   virtual Bool_t   Solve      (      TVectorD &b);
   virtual TVectorD Solve      (const TVectorD& b,Bool_t &ok) { TVectorD x = b; ok = Solve(x); return x; }
   virtual Bool_t   Solve      (      TMatrixDColumn &b);
   virtual Bool_t   TransSolve (      TVectorD &b);
   virtual TVectorD TransSolve (const TVectorD& b,Bool_t &ok) { TVectorD x = b; ok = TransSolve(x); return x; }
   virtual Bool_t   TransSolve (      TMatrixDColumn &b);
   virtual void     Det        (Double_t &d1,Double_t &d2);

   static  Bool_t   InvertLU  (TMatrixD &a,Double_t tol,Double_t *det=0);
   Bool_t           Invert    (TMatrixD &inv);
   TMatrixD         Invert    (Bool_t &status);
   TMatrixD         Invert    () { Bool_t status; return Invert(status); }

   void Print(Option_t *opt ="") const; // *MENU*

   TDecompLU &operator= (const TDecompLU &source);

   ClassDef(TDecompLU,1) // Matrix Decompositition LU
};

#endif

// @(#)root/matrix:$Id$
// Authors: Fons Rademakers, Eddy Offermann   Dec 2003

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TMatrixDSymEigen
#define ROOT_TMatrixDSymEigen

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMatrixDSymEigen                                                     //
//                                                                      //
// Eigenvalues and eigenvectors of a real symmetric matrix.             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#include "TMatrixD.h"
//#include "TMatrixDSym.h"
//#include "TVectorD.h"

class TMatrixDSymEigen
{
protected :

   static void MakeTridiagonal (TMatrixD &v,TVectorD &d,TVectorD &e);
   static void MakeEigenVectors(TMatrixD &v,TVectorD &d,TVectorD &e);

   TMatrixD fEigenVectors; // Eigen-vectors of matrix
   TVectorD fEigenValues;  // Eigen-values

public :

   enum {kWorkMax = 100}; // size of work array

   TMatrixDSymEigen() : fEigenVectors(), fEigenValues() {};
   TMatrixDSymEigen(const TMatrixDSym      &a);
   TMatrixDSymEigen(const TMatrixDSymEigen &another);
   virtual ~TMatrixDSymEigen() {}

// If matrix A has shape (rowLwb,rowUpb,rowLwb,rowUpb), then each eigen-vector
// must have an index running between (rowLwb,rowUpb) .
// For convenience, the column index of the eigen-vector matrix
// also runs from rowLwb to rowUpb so that the returned matrix
// has also index/shape (rowLwb,rowUpb,rowLwb,rowUpb) .
// The same is true for the eigen-value vector .

   const TMatrixD &GetEigenVectors() const { return fEigenVectors; }
   const TVectorD &GetEigenValues () const { return fEigenValues; }

   TMatrixDSymEigen &operator= (const TMatrixDSymEigen &source);

   ClassDef(TMatrixDSymEigen,1) // Eigen-Vectors/Values of a Matrix
};
#endif

/////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////
//////////////////////////////////////
/////////////////////////////////

//class TBrowser;

//class TMultiDimFet : public TNamed {
class TMultiDimFet {

public:
   enum EMDFPolyType {
      kMonomials,
      kChebyshev,
      kLegendre
   };

private:
   static TMultiDimFet* fgInstance; //! Static instance
protected:

   TVectorD     fQuantity;             //! Training sample, dependent quantity
   TVectorD     fSqError;              //! Training sample, error in quantity
   Double_t     fMeanQuantity;         // Mean of dependent quantity
   Double_t     fMaxQuantity;          //! Max value of dependent quantity
   Double_t     fMinQuantity;          //! Min value of dependent quantity
   Double_t     fSumSqQuantity;        //! SumSquare of dependent quantity
   Double_t     fSumSqAvgQuantity;     //! Sum of squares away from mean

   TVectorD     fVariables;            //! Training sample, independent variables
   Int_t        fNVariables;           // Number of independent variables
   TVectorD     fMeanVariables;        //! mean value of independent variables
   TVectorD     fMaxVariables;         // max value of independent variables
   TVectorD     fMinVariables;         // min value of independent variables

   Int_t        fSampleSize;           //! Size of training sample

   TVectorD     fTestQuantity;         //! Test sample, dependent quantity
   TVectorD     fTestSqError;          //! Test sample, Error in quantity
   TVectorD     fTestVariables;        //! Test sample, independent variables

   Int_t        fTestSampleSize;       //! Size of test sample

   Double_t     fMinAngle;             //! Min angle for acepting new function
   Double_t     fMaxAngle;             //! Max angle for acepting new function
   Int_t        fMaxTerms;             // Max terms expected in final expr.
   Double_t     fMinRelativeError;     //! Min relative error accepted
   std::vector<Int_t> fMaxPowers;     //! maximum powers, ex-array
   Double_t     fPowerLimit;           //! Control parameter


   TMatrixD     fFunctions;            //! Functions evaluated over sample
   Int_t        fMaxFunctions;         // max number of functions
   std::vector<Int_t> fFunctionCodes;  //! acceptance code, ex-array
   Int_t        fMaxStudy;             //! max functions to study

   TMatrixD     fOrthFunctions;        //! As above, but orthogonalised
   TVectorD     fOrthFunctionNorms;    //! Norm of the evaluated functions


   std::vector<Int_t> fMaxPowersFinal; //! maximum powers from fit, ex-array
   Int_t	fMaxFunctionsTimesNVariables;	// fMaxFunctionsTimesNVariables
   std::vector<Int_t> fPowers;         // ex-array
   std::vector<Int_t> fPowerIndex;     // Index of accepted powers, ex-array

   TVectorD     fResiduals;            //! Vector of the final residuals
   Double_t     fMaxResidual;          //! Max redsidual value
   Double_t     fMinResidual;          //! Min redsidual value
   Int_t        fMaxResidualRow;       //! Row giving max residual
   Int_t        fMinResidualRow;       //! Row giving min residual
   Double_t     fSumSqResidual;        //! Sum of Square residuals

   Int_t        fNCoefficients;        // Dimension of model coefficients
   TVectorD     fOrthCoefficients;     //! The model coefficients
   TMatrixD     fOrthCurvatureMatrix;  //! Model matrix
   TVectorD     fCoefficients;         // Vector of the final coefficients
   TVectorD     fCoefficientsRMS;      //! Vector of RMS of coefficients
   Double_t     fRMS;                  //! Root mean square of fit
   Double_t     fChi2;                 //! Chi square of fit
   Int_t        fParameterisationCode; //! Exit code of parameterisation

   Double_t     fError;                //! Error from parameterization
   Double_t     fTestError;            //! Error from test
   Double_t     fPrecision;            //! Relative precision of param
   Double_t     fTestPrecision;        //! Relative precision of test
   Double_t     fCorrelationCoeff;     //! Multi Correlation coefficient
   TMatrixD     fCorrelationMatrix;    //! Correlation matrix
   Double_t     fTestCorrelationCoeff; //! Multi Correlation coefficient

   //TList*       fHistograms;           //! List of histograms
   Byte_t       fHistogramMask;        //! Bit pattern of hisograms used

   //TVirtualFitter* fFitter;            //! Fit object (MINUIT)

   EMDFPolyType fPolyType;             // Type of polynomials to use
   Bool_t       fShowCorrelation;      // print correlation matrix
   Bool_t       fIsUserFunction;       // Flag for user defined function
   Bool_t       fIsVerbose;            //

   virtual Double_t EvalFactor(Int_t p, Double_t x);
   virtual Double_t EvalControl(const Int_t *powers);
   //virtual void     MakeCoefficientErrors();
   //virtual void     MakeCorrelation();
   virtual Double_t MakeGramSchmidt(Int_t function);
   virtual void     MakeCoefficients();
   virtual void     MakeCandidates();
   virtual void     MakeNormalized();
   virtual void     MakeParameterization();
   //virtual void     MakeRealCode(const char *filename,
   //                              const char *classname,
   //                              Option_t   *option="");
   virtual Bool_t   Select(const Int_t *iv);
   virtual Bool_t   TestFunction(Double_t squareResidual,
                                 Double_t dResidur);
public:
   TMultiDimFet();
   TMultiDimFet(const TMultiDimFet &in);
   const TMultiDimFet &operator=(const TMultiDimFet &in);
   //TMultiDimFet(TMultiDimFit_wrapper &in);

   TMultiDimFet(Int_t dimension,
                EMDFPolyType type=kMonomials,
                Option_t *option="");
   virtual ~TMultiDimFet();

   virtual void     AddRow(const Double_t *x, Double_t D, Double_t E=0);
   virtual void     AddTestRow(const Double_t *x, Double_t D, Double_t E=0);
   //virtual void     Browse(TBrowser* b);
   virtual void     Clear(Option_t *option=""); // *MENU*
   //virtual void     Draw(Option_t * ="d") { }
   virtual Double_t Eval(const Double_t *x, const Double_t *coeff=0);
   virtual void     FindParameterization(double precision); // *MENU*
   virtual void     ReleaseMemory();
   virtual void     Fit(Option_t *option=""); // *MENU*

   Double_t         GetChi2()              const { return fChi2; }
   const TMatrixD*  GetCorrelationMatrix() const { return &fCorrelationMatrix; }
   const TVectorD*  GetCoefficients()      const { return &fCoefficients; }
   Double_t         GetError()             const { return fError; }
   std::vector<Int_t> GetFunctionCodes()     const { return fFunctionCodes; }
   const TMatrixD*  GetFunctions()         const { return &fFunctions; }
   //virtual TList*   GetHistograms()        const { return fHistograms; }
   Double_t         GetMaxAngle()          const { return fMaxAngle; }
   Int_t            GetMaxFunctions()      const { return fMaxFunctions; }
   std::vector<Int_t> GetMaxPowers()         const { return fMaxPowers; }
   Double_t         GetMaxQuantity()       const { return fMaxQuantity; }
   Int_t            GetMaxStudy()          const { return fMaxStudy; }
   Int_t            GetMaxTerms()          const { return fMaxTerms; }
   const TVectorD*  GetMaxVariables()      const { return &fMaxVariables; }
   Double_t         GetMeanQuantity()      const { return fMeanQuantity; }
   const TVectorD*  GetMeanVariables()     const { return &fMeanVariables; }
   Double_t         GetMinAngle()          const { return fMinAngle; }
   Double_t         GetMinQuantity()       const { return fMinQuantity; }
   Double_t         GetMinRelativeError()  const { return fMinRelativeError; }
   const TVectorD*  GetMinVariables()      const { return &fMinVariables; }
   Int_t            GetNVariables()        const { return fNVariables; }
   Int_t            GetNCoefficients()     const { return fNCoefficients; }
   Int_t            GetPolyType()          const { return fPolyType; }
   std::vector<Int_t> GetPowerIndex()        const { return fPowerIndex; }
   Double_t         GetPowerLimit()        const { return fPowerLimit; }
   std::vector<Int_t> GetPowers()            const { return fPowers; }
   Double_t         GetPrecision()         const { return fPrecision; }
   const TVectorD*  GetQuantity()          const { return &fQuantity; }
   Double_t         GetResidualMax()       const { return fMaxResidual; }
   Double_t         GetResidualMin()       const { return fMinResidual; }
   Int_t            GetResidualMaxRow()    const { return fMaxResidualRow; }
   Int_t            GetResidualMinRow()    const { return fMinResidualRow; }
   Double_t         GetResidualSumSq()     const { return fSumSqResidual; }
   Double_t         GetRMS()               const { return fRMS; }
   Int_t            GetSampleSize()        const { return fSampleSize; }
   const TVectorD*  GetSqError()           const { return &fSqError; }
   Double_t         GetSumSqAvgQuantity()  const { return fSumSqAvgQuantity; }
   Double_t         GetSumSqQuantity()     const { return fSumSqQuantity; }
   Double_t         GetTestError()         const { return fTestError; }
   Double_t         GetTestPrecision()     const { return fTestPrecision; }
   const TVectorD*  GetTestQuantity()      const { return &fTestQuantity; }
   Int_t            GetTestSampleSize()    const { return fTestSampleSize; }
   const TVectorD*  GetTestSqError()       const { return &fTestSqError; }
   const TVectorD*  GetTestVariables()     const { return &fTestVariables; }
   const TVectorD*  GetVariables()         const { return &fVariables; }

   static TMultiDimFet* Instance()               { return fgInstance; }
   virtual Bool_t   IsFolder()             const { return kTRUE; }
   virtual Double_t MakeChi2(const Double_t* coeff=0);
   //virtual void     MakeCode(const char *functionName="MDF", Option_t *option=""); // *MENU*
   //virtual void     MakeHistograms(Option_t* option="A"); // *MENU*
   //virtual void     MakeMethod(const Char_t* className="MDF", Option_t* option=""); // *MENU*
   //virtual void     Print(Option_t *option="ps") const; // *MENU*
   virtual void     PrintPolynomialsSpecial(Option_t *option="m") const; // *MENU*

   void             SetMaxAngle(Double_t angle=0);
   void             SetMaxFunctions(Int_t n) { fMaxFunctions = n; }
   void             SetMaxPowers(const Int_t *powers);
   void             SetMaxStudy(Int_t n) { fMaxStudy  = n; }
   void             SetMaxTerms(Int_t terms) { fMaxTerms = terms; }
   void             SetMinRelativeError(Double_t error);
   void             SetMinAngle(Double_t angle=1);
   void             SetPowerLimit(Double_t limit=1e-3);
   virtual void     SetPowers(const Int_t *powers, Int_t terms);

   void ReducePolynomial(double error);
   void ZeroDoubiousCoefficients(double error);

   ClassDef(TMultiDimFet,1) // Multi dimensional fit class
};
#endif
