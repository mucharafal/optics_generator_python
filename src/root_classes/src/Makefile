interfaceOptions =  `root-config --libs` `root-config --glibs` -I`root-config --incdir` -I./../interface
pathToRootLibraries = ../../../root_libs
compileOption = -std=c++14 -fPIC

clean:
	rm -rf ./../obj
	rm -rf $(pathToRootLibraries)

shared: clean
	mkdir $(pathToRootLibraries)
	rootcint -f ./FitCint.cc -c ./../interface/LHCOpticsApproximator.h ./../interface/TMultiDimFet.h ./../interface/TNtupleDcorr.h ./../interface/TMultiDimFit_wrapper.h ./../interface/FitCintLinkDef.h 
	mv ./FitCint_rdict.pcm $(pathToRootLibraries)
	mkdir ./../obj
	gcc -c $(compileOption) $(interfaceOptions) FitCint.cc 				-o ./../obj/FitCint.o
	gcc -c $(compileOption) $(interfaceOptions) TMultiDimFet.cc 				-o ./../obj/TMultiDimFet.o
	gcc -c $(compileOption) $(interfaceOptions) TMultiDimFit_wrapper.cc		-o ./../obj/TMultiDimFit_wrapper.o
	gcc -c $(compileOption) $(interfaceOptions) TNtupleDcorr.cc 				-o ./../obj/TNtupleDcorr.o
	gcc -c $(compileOption) $(interfaceOptions) LHCOpticsApproximator.cc -o ./../obj/LHCOpticsApproximator.o
	rootcint -f $(pathToRootLibraries)/LHCOpticsApproximator.cxx -c ./../interface/LHCOpticsApproximator.h ./../interface/TMultiDimFet.h ./../interface/TNtupleDcorr.h ./../interface/TMultiDimFit_wrapper.h ./../interface/FitCintLinkDef.h 
	rm $(pathToRootLibraries)/LHCOpticsApproximator.cxx*
	gcc -shared $(compileOption) $(interfaceOptions) ./../obj/LHCOpticsApproximator.o ./../obj/TMultiDimFet.o ./../obj/TNtupleDcorr.o ./../obj/FitCint.o ./../obj/TMultiDimFit_wrapper.o -o $(pathToRootLibraries)/LHCOpticsApproximator.so
	rootcint -f $(pathToRootLibraries)/FitCint.cxx -c $(interfaceOptions) ../interface/FitCintLinkDef.h