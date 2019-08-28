#include "TMultiDimFit_wrapper.h"
#include "TMultiDimFit.h"

Double_t TMultiDimFit_wrapper::getFMeanQuantity() {
    return fMeanQuantity;
}

Int_t TMultiDimFit_wrapper::getFNVariables() {
    return fNVariables;
}

TVectorD TMultiDimFit_wrapper::getFMaxVariables() {
    return fMaxVariables;
}

TVectorD TMultiDimFit_wrapper::getFMinVariables(){ 
    return fMinVariables;
}
Int_t TMultiDimFit_wrapper::getFMaxTerms(){ 
    return fMaxTerms;
}
Int_t TMultiDimFit_wrapper::getFMaxFunctions(){ 
    return fMaxFunctions;
}
Int_t TMultiDimFit_wrapper::getFMaxFunctionsTimesNVariables(){ 
    return fMaxFunctions * fNVariables;
}
std::vector<Int_t> TMultiDimFit_wrapper::getFPowers(){ 
    return std::vector<Int_t> (fPowers, fPowers + fMaxFuncNV);
}
std::vector<Int_t> TMultiDimFit_wrapper::getFPowerIndex(){ 
    return std::vector<Int_t> (fPowerIndex, fPowerIndex + fMaxTerms);
}
Int_t TMultiDimFit_wrapper::getFNCoefficients(){ 
    return fNCoefficients;
}
TVectorD TMultiDimFit_wrapper::getFCoefficients(){ 
    return fCoefficients;
}
TMultiDimFit::EMDFPolyType TMultiDimFit_wrapper::getFPolyType(){ 
    return fPolyType;
}
Bool_t TMultiDimFit_wrapper::getFShowCorrelation(){ 
    return fShowCorrelation;
}
Bool_t TMultiDimFit_wrapper::getFIsUserFunction(){ 
    return fIsUserFunction;
}
Bool_t TMultiDimFit_wrapper::getFIsVerbose(){ 
    return fIsVerbose;
}

TMultiDimFit_wrapper::TMultiDimFit_wrapper() : TMultiDimFit() {

}

TMultiDimFit_wrapper::TMultiDimFit_wrapper(Int_t dimension) : TMultiDimFit(dimension) {

}