// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdIFitCint
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "./../interface/LHCOpticsApproximator.h"
#include "./../interface/TMultiDimFet.h"
#include "./../interface/TNtupleDcorr.h"
#include "./../interface/TMultiDimFit_wrapper.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TMultiDimFit_wrapper(void *p = 0);
   static void *newArray_TMultiDimFit_wrapper(Long_t size, void *p);
   static void delete_TMultiDimFit_wrapper(void *p);
   static void deleteArray_TMultiDimFit_wrapper(void *p);
   static void destruct_TMultiDimFit_wrapper(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMultiDimFit_wrapper*)
   {
      ::TMultiDimFit_wrapper *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMultiDimFit_wrapper >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMultiDimFit_wrapper", ::TMultiDimFit_wrapper::Class_Version(), "../interface/TMultiDimFit_wrapper.h", 5,
                  typeid(::TMultiDimFit_wrapper), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMultiDimFit_wrapper::Dictionary, isa_proxy, 4,
                  sizeof(::TMultiDimFit_wrapper) );
      instance.SetNew(&new_TMultiDimFit_wrapper);
      instance.SetNewArray(&newArray_TMultiDimFit_wrapper);
      instance.SetDelete(&delete_TMultiDimFit_wrapper);
      instance.SetDeleteArray(&deleteArray_TMultiDimFit_wrapper);
      instance.SetDestructor(&destruct_TMultiDimFit_wrapper);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMultiDimFit_wrapper*)
   {
      return GenerateInitInstanceLocal((::TMultiDimFit_wrapper*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMultiDimFit_wrapper*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMultiDimFet(void *p = 0);
   static void *newArray_TMultiDimFet(Long_t size, void *p);
   static void delete_TMultiDimFet(void *p);
   static void deleteArray_TMultiDimFet(void *p);
   static void destruct_TMultiDimFet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMultiDimFet*)
   {
      ::TMultiDimFet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMultiDimFet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMultiDimFet", ::TMultiDimFet::Class_Version(), "../interface/TMultiDimFet.h", 30,
                  typeid(::TMultiDimFet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMultiDimFet::Dictionary, isa_proxy, 4,
                  sizeof(::TMultiDimFet) );
      instance.SetNew(&new_TMultiDimFet);
      instance.SetNewArray(&newArray_TMultiDimFet);
      instance.SetDelete(&delete_TMultiDimFet);
      instance.SetDeleteArray(&deleteArray_TMultiDimFet);
      instance.SetDestructor(&destruct_TMultiDimFet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMultiDimFet*)
   {
      return GenerateInitInstanceLocal((::TMultiDimFet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMultiDimFet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LHCOpticsApproximator(void *p = 0);
   static void *newArray_LHCOpticsApproximator(Long_t size, void *p);
   static void delete_LHCOpticsApproximator(void *p);
   static void deleteArray_LHCOpticsApproximator(void *p);
   static void destruct_LHCOpticsApproximator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LHCOpticsApproximator*)
   {
      ::LHCOpticsApproximator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LHCOpticsApproximator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LHCOpticsApproximator", ::LHCOpticsApproximator::Class_Version(), "../interface/LHCOpticsApproximator.h", 39,
                  typeid(::LHCOpticsApproximator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LHCOpticsApproximator::Dictionary, isa_proxy, 4,
                  sizeof(::LHCOpticsApproximator) );
      instance.SetNew(&new_LHCOpticsApproximator);
      instance.SetNewArray(&newArray_LHCOpticsApproximator);
      instance.SetDelete(&delete_LHCOpticsApproximator);
      instance.SetDeleteArray(&deleteArray_LHCOpticsApproximator);
      instance.SetDestructor(&destruct_LHCOpticsApproximator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LHCOpticsApproximator*)
   {
      return GenerateInitInstanceLocal((::LHCOpticsApproximator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LHCOpticsApproximator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_LHCApertureApproximator(void *p = 0);
   static void *newArray_LHCApertureApproximator(Long_t size, void *p);
   static void delete_LHCApertureApproximator(void *p);
   static void deleteArray_LHCApertureApproximator(void *p);
   static void destruct_LHCApertureApproximator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LHCApertureApproximator*)
   {
      ::LHCApertureApproximator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::LHCApertureApproximator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("LHCApertureApproximator", ::LHCApertureApproximator::Class_Version(), "../interface/LHCOpticsApproximator.h", 122,
                  typeid(::LHCApertureApproximator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::LHCApertureApproximator::Dictionary, isa_proxy, 4,
                  sizeof(::LHCApertureApproximator) );
      instance.SetNew(&new_LHCApertureApproximator);
      instance.SetNewArray(&newArray_LHCApertureApproximator);
      instance.SetDelete(&delete_LHCApertureApproximator);
      instance.SetDeleteArray(&deleteArray_LHCApertureApproximator);
      instance.SetDestructor(&destruct_LHCApertureApproximator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LHCApertureApproximator*)
   {
      return GenerateInitInstanceLocal((::LHCApertureApproximator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::LHCApertureApproximator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TNtupleDcorr(void *p = 0);
   static void *newArray_TNtupleDcorr(Long_t size, void *p);
   static void delete_TNtupleDcorr(void *p);
   static void deleteArray_TNtupleDcorr(void *p);
   static void destruct_TNtupleDcorr(void *p);
   static void directoryAutoAdd_TNtupleDcorr(void *obj, TDirectory *dir);
   static Long64_t merge_TNtupleDcorr(void *obj, TCollection *coll,TFileMergeInfo *info);
   static void reset_TNtupleDcorr(void *obj, TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TNtupleDcorr*)
   {
      ::TNtupleDcorr *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TNtupleDcorr >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TNtupleDcorr", ::TNtupleDcorr::Class_Version(), "../interface/TNtupleDcorr.h", 30,
                  typeid(::TNtupleDcorr), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TNtupleDcorr::Dictionary, isa_proxy, 4,
                  sizeof(::TNtupleDcorr) );
      instance.SetNew(&new_TNtupleDcorr);
      instance.SetNewArray(&newArray_TNtupleDcorr);
      instance.SetDelete(&delete_TNtupleDcorr);
      instance.SetDeleteArray(&deleteArray_TNtupleDcorr);
      instance.SetDestructor(&destruct_TNtupleDcorr);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_TNtupleDcorr);
      instance.SetMerge(&merge_TNtupleDcorr);
      instance.SetResetAfterMerge(&reset_TNtupleDcorr);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TNtupleDcorr*)
   {
      return GenerateInitInstanceLocal((::TNtupleDcorr*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TNtupleDcorr*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TMultiDimFit_wrapper::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMultiDimFit_wrapper::Class_Name()
{
   return "TMultiDimFit_wrapper";
}

//______________________________________________________________________________
const char *TMultiDimFit_wrapper::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFit_wrapper*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMultiDimFit_wrapper::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFit_wrapper*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMultiDimFit_wrapper::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFit_wrapper*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMultiDimFit_wrapper::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFit_wrapper*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TMultiDimFet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMultiDimFet::Class_Name()
{
   return "TMultiDimFet";
}

//______________________________________________________________________________
const char *TMultiDimFet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMultiDimFet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMultiDimFet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMultiDimFet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMultiDimFet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LHCOpticsApproximator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LHCOpticsApproximator::Class_Name()
{
   return "LHCOpticsApproximator";
}

//______________________________________________________________________________
const char *LHCOpticsApproximator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHCOpticsApproximator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LHCOpticsApproximator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHCOpticsApproximator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LHCOpticsApproximator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHCOpticsApproximator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LHCOpticsApproximator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHCOpticsApproximator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr LHCApertureApproximator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LHCApertureApproximator::Class_Name()
{
   return "LHCApertureApproximator";
}

//______________________________________________________________________________
const char *LHCApertureApproximator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHCApertureApproximator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LHCApertureApproximator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::LHCApertureApproximator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LHCApertureApproximator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHCApertureApproximator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LHCApertureApproximator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::LHCApertureApproximator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TNtupleDcorr::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNtupleDcorr::Class_Name()
{
   return "TNtupleDcorr";
}

//______________________________________________________________________________
const char *TNtupleDcorr::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNtupleDcorr*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNtupleDcorr::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TNtupleDcorr*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNtupleDcorr::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNtupleDcorr*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNtupleDcorr::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TNtupleDcorr*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TMultiDimFit_wrapper::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMultiDimFit_wrapper.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMultiDimFit_wrapper::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMultiDimFit_wrapper::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMultiDimFit_wrapper(void *p) {
      return  p ? new(p) ::TMultiDimFit_wrapper : new ::TMultiDimFit_wrapper;
   }
   static void *newArray_TMultiDimFit_wrapper(Long_t nElements, void *p) {
      return p ? new(p) ::TMultiDimFit_wrapper[nElements] : new ::TMultiDimFit_wrapper[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMultiDimFit_wrapper(void *p) {
      delete ((::TMultiDimFit_wrapper*)p);
   }
   static void deleteArray_TMultiDimFit_wrapper(void *p) {
      delete [] ((::TMultiDimFit_wrapper*)p);
   }
   static void destruct_TMultiDimFit_wrapper(void *p) {
      typedef ::TMultiDimFit_wrapper current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMultiDimFit_wrapper

//______________________________________________________________________________
void TMultiDimFet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMultiDimFet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMultiDimFet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMultiDimFet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMultiDimFet(void *p) {
      return  p ? new(p) ::TMultiDimFet : new ::TMultiDimFet;
   }
   static void *newArray_TMultiDimFet(Long_t nElements, void *p) {
      return p ? new(p) ::TMultiDimFet[nElements] : new ::TMultiDimFet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMultiDimFet(void *p) {
      delete ((::TMultiDimFet*)p);
   }
   static void deleteArray_TMultiDimFet(void *p) {
      delete [] ((::TMultiDimFet*)p);
   }
   static void destruct_TMultiDimFet(void *p) {
      typedef ::TMultiDimFet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMultiDimFet

//______________________________________________________________________________
void LHCOpticsApproximator::Streamer(TBuffer &R__b)
{
   // Stream an object of class LHCOpticsApproximator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LHCOpticsApproximator::Class(),this);
   } else {
      R__b.WriteClassBuffer(LHCOpticsApproximator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LHCOpticsApproximator(void *p) {
      return  p ? new(p) ::LHCOpticsApproximator : new ::LHCOpticsApproximator;
   }
   static void *newArray_LHCOpticsApproximator(Long_t nElements, void *p) {
      return p ? new(p) ::LHCOpticsApproximator[nElements] : new ::LHCOpticsApproximator[nElements];
   }
   // Wrapper around operator delete
   static void delete_LHCOpticsApproximator(void *p) {
      delete ((::LHCOpticsApproximator*)p);
   }
   static void deleteArray_LHCOpticsApproximator(void *p) {
      delete [] ((::LHCOpticsApproximator*)p);
   }
   static void destruct_LHCOpticsApproximator(void *p) {
      typedef ::LHCOpticsApproximator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LHCOpticsApproximator

//______________________________________________________________________________
void LHCApertureApproximator::Streamer(TBuffer &R__b)
{
   // Stream an object of class LHCApertureApproximator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(LHCApertureApproximator::Class(),this);
   } else {
      R__b.WriteClassBuffer(LHCApertureApproximator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_LHCApertureApproximator(void *p) {
      return  p ? new(p) ::LHCApertureApproximator : new ::LHCApertureApproximator;
   }
   static void *newArray_LHCApertureApproximator(Long_t nElements, void *p) {
      return p ? new(p) ::LHCApertureApproximator[nElements] : new ::LHCApertureApproximator[nElements];
   }
   // Wrapper around operator delete
   static void delete_LHCApertureApproximator(void *p) {
      delete ((::LHCApertureApproximator*)p);
   }
   static void deleteArray_LHCApertureApproximator(void *p) {
      delete [] ((::LHCApertureApproximator*)p);
   }
   static void destruct_LHCApertureApproximator(void *p) {
      typedef ::LHCApertureApproximator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LHCApertureApproximator

//______________________________________________________________________________
void TNtupleDcorr::Streamer(TBuffer &R__b)
{
   // Stream an object of class TNtupleDcorr.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TNtupleDcorr::Class(),this);
   } else {
      R__b.WriteClassBuffer(TNtupleDcorr::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TNtupleDcorr(void *p) {
      return  p ? new(p) ::TNtupleDcorr : new ::TNtupleDcorr;
   }
   static void *newArray_TNtupleDcorr(Long_t nElements, void *p) {
      return p ? new(p) ::TNtupleDcorr[nElements] : new ::TNtupleDcorr[nElements];
   }
   // Wrapper around operator delete
   static void delete_TNtupleDcorr(void *p) {
      delete ((::TNtupleDcorr*)p);
   }
   static void deleteArray_TNtupleDcorr(void *p) {
      delete [] ((::TNtupleDcorr*)p);
   }
   static void destruct_TNtupleDcorr(void *p) {
      typedef ::TNtupleDcorr current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_TNtupleDcorr(void *p, TDirectory *dir) {
      ((::TNtupleDcorr*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t merge_TNtupleDcorr(void *obj,TCollection *coll,TFileMergeInfo *info) {
      return ((::TNtupleDcorr*)obj)->Merge(coll,info);
   }
   // Wrapper around the Reset function.
   static void reset_TNtupleDcorr(void *obj,TFileMergeInfo *info) {
      ((::TNtupleDcorr*)obj)->ResetAfterMerge(info);
   }
} // end of namespace ROOT for class ::TNtupleDcorr

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 386,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 386,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlELHCOpticsApproximatorgR_Dictionary();
   static void vectorlELHCOpticsApproximatorgR_TClassManip(TClass*);
   static void *new_vectorlELHCOpticsApproximatorgR(void *p = 0);
   static void *newArray_vectorlELHCOpticsApproximatorgR(Long_t size, void *p);
   static void delete_vectorlELHCOpticsApproximatorgR(void *p);
   static void deleteArray_vectorlELHCOpticsApproximatorgR(void *p);
   static void destruct_vectorlELHCOpticsApproximatorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<LHCOpticsApproximator>*)
   {
      vector<LHCOpticsApproximator> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<LHCOpticsApproximator>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<LHCOpticsApproximator>", -2, "vector", 386,
                  typeid(vector<LHCOpticsApproximator>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELHCOpticsApproximatorgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<LHCOpticsApproximator>) );
      instance.SetNew(&new_vectorlELHCOpticsApproximatorgR);
      instance.SetNewArray(&newArray_vectorlELHCOpticsApproximatorgR);
      instance.SetDelete(&delete_vectorlELHCOpticsApproximatorgR);
      instance.SetDeleteArray(&deleteArray_vectorlELHCOpticsApproximatorgR);
      instance.SetDestructor(&destruct_vectorlELHCOpticsApproximatorgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<LHCOpticsApproximator> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<LHCOpticsApproximator>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELHCOpticsApproximatorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<LHCOpticsApproximator>*)0x0)->GetClass();
      vectorlELHCOpticsApproximatorgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELHCOpticsApproximatorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELHCOpticsApproximatorgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LHCOpticsApproximator> : new vector<LHCOpticsApproximator>;
   }
   static void *newArray_vectorlELHCOpticsApproximatorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LHCOpticsApproximator>[nElements] : new vector<LHCOpticsApproximator>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELHCOpticsApproximatorgR(void *p) {
      delete ((vector<LHCOpticsApproximator>*)p);
   }
   static void deleteArray_vectorlELHCOpticsApproximatorgR(void *p) {
      delete [] ((vector<LHCOpticsApproximator>*)p);
   }
   static void destruct_vectorlELHCOpticsApproximatorgR(void *p) {
      typedef vector<LHCOpticsApproximator> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<LHCOpticsApproximator>

namespace ROOT {
   static TClass *vectorlELHCApertureApproximatorgR_Dictionary();
   static void vectorlELHCApertureApproximatorgR_TClassManip(TClass*);
   static void *new_vectorlELHCApertureApproximatorgR(void *p = 0);
   static void *newArray_vectorlELHCApertureApproximatorgR(Long_t size, void *p);
   static void delete_vectorlELHCApertureApproximatorgR(void *p);
   static void deleteArray_vectorlELHCApertureApproximatorgR(void *p);
   static void destruct_vectorlELHCApertureApproximatorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<LHCApertureApproximator>*)
   {
      vector<LHCApertureApproximator> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<LHCApertureApproximator>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<LHCApertureApproximator>", -2, "vector", 386,
                  typeid(vector<LHCApertureApproximator>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELHCApertureApproximatorgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<LHCApertureApproximator>) );
      instance.SetNew(&new_vectorlELHCApertureApproximatorgR);
      instance.SetNewArray(&newArray_vectorlELHCApertureApproximatorgR);
      instance.SetDelete(&delete_vectorlELHCApertureApproximatorgR);
      instance.SetDeleteArray(&deleteArray_vectorlELHCApertureApproximatorgR);
      instance.SetDestructor(&destruct_vectorlELHCApertureApproximatorgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<LHCApertureApproximator> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<LHCApertureApproximator>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELHCApertureApproximatorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<LHCApertureApproximator>*)0x0)->GetClass();
      vectorlELHCApertureApproximatorgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELHCApertureApproximatorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELHCApertureApproximatorgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LHCApertureApproximator> : new vector<LHCApertureApproximator>;
   }
   static void *newArray_vectorlELHCApertureApproximatorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<LHCApertureApproximator>[nElements] : new vector<LHCApertureApproximator>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELHCApertureApproximatorgR(void *p) {
      delete ((vector<LHCApertureApproximator>*)p);
   }
   static void deleteArray_vectorlELHCApertureApproximatorgR(void *p) {
      delete [] ((vector<LHCApertureApproximator>*)p);
   }
   static void destruct_vectorlELHCApertureApproximatorgR(void *p) {
      typedef vector<LHCApertureApproximator> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<LHCApertureApproximator>

namespace {
  void TriggerDictionaryInitialization_FitCint_Impl() {
    static const char* headers[] = {
"./../interface/LHCOpticsApproximator.h",
"./../interface/TMultiDimFet.h",
"./../interface/TNtupleDcorr.h",
"./../interface/TMultiDimFit_wrapper.h",
0
    };
    static const char* includePaths[] = {
"/usr/include/root",
"/home/rafalmucha/Pobrane/optic/optics_generator_python/src/root_classes/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "FitCint dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Aperture approximator)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$./../interface/LHCOpticsApproximator.h")))  LHCApertureApproximator;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate(R"ATTRDUMP(Proton transport approximator)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$./../interface/LHCOpticsApproximator.h")))  LHCOpticsApproximator;
class __attribute__((annotate(R"ATTRDUMP(Multi dimensional fit class)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$./../interface/LHCOpticsApproximator.h")))  TMultiDimFit_wrapper;
class __attribute__((annotate(R"ATTRDUMP(Multi dimensional fit class)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$./../interface/LHCOpticsApproximator.h")))  TMultiDimFet;
class __attribute__((annotate(R"ATTRDUMP(A simple tree with branches of floats.)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$./../interface/TNtupleDcorr.h")))  TNtupleDcorr;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "FitCint dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "./../interface/LHCOpticsApproximator.h"
#include "./../interface/TMultiDimFet.h"
#include "./../interface/TNtupleDcorr.h"
#include "./../interface/TMultiDimFit_wrapper.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"LHCApertureApproximator", payloadCode, "@",
"LHCOpticsApproximator", payloadCode, "@",
"TMultiDimFet", payloadCode, "@",
"TMultiDimFit_wrapper", payloadCode, "@",
"TNtupleDcorr", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("FitCint",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_FitCint_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_FitCint_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_FitCint() {
  TriggerDictionaryInitialization_FitCint_Impl();
}
