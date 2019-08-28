#ifndef ROOT_TMultiDimFit_wrapper
#define ROOT_TMultiDimFit_wrapper
#include "TMultiDimFit.h"

class TMultiDimFit_wrapper: public TMultiDimFit {
public:
    Double_t getFMeanQuantity();
    Int_t getFNVariables();
    TVectorD getFMaxVariables();
    TVectorD getFMinVariables();
    Int_t getFMaxTerms();
    Int_t getFMaxFunctions();
    Int_t getFMaxFunctionsTimesNVariables();
    std::vector<Int_t> getFPowers();
    std::vector<Int_t> getFPowerIndex();
    Int_t getFNCoefficients();
    TVectorD getFCoefficients();
    EMDFPolyType getFPolyType();
    Bool_t getFShowCorrelation();
    Bool_t getFIsUserFunction();
    Bool_t getFIsVerbose();

    TMultiDimFit_wrapper();
    TMultiDimFit_wrapper(Int_t dimension);

    ClassDef(TMultiDimFit_wrapper,2) // Multi dimensional fit class
};

#endif