// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdIFitCint

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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "../include/LHCOpticsApproximator.h"

// Header files passed via #pragma extra_include

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
         instance("LHCOpticsApproximator", ::LHCOpticsApproximator::Class_Version(), "../include/LHCOpticsApproximator.h", 39,
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
         instance("LHCApertureApproximator", ::LHCApertureApproximator::Class_Version(), "../include/LHCOpticsApproximator.h", 120,
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
         instance("vector<string>", -2, "vector", 339,
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
         instance("vector<LHCOpticsApproximator>", -2, "vector", 339,
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
         instance("vector<LHCApertureApproximator>", -2, "vector", 339,
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
"../include/LHCOpticsApproximator.h",
0
    };
    static const char* includePaths[] = {
"/usr/include/root",
"/home/rafalmucha/Pobrane/optic/optics_generator_python/src/root_classes/tmultidimfit_version/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "FitCint dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Aperture approximator)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$../include/LHCOpticsApproximator.h")))  LHCApertureApproximator;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate(R"ATTRDUMP(Proton transport approximator)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$../include/LHCOpticsApproximator.h")))  LHCOpticsApproximator;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "FitCint dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../include/LHCOpticsApproximator.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"LHCApertureApproximator", payloadCode, "@",
"LHCOpticsApproximator", payloadCode, "@",
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
