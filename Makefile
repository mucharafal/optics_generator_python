PROJECT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

DISTRO := $(or $(if $(wildcard /etc/debian_version), ubuntu), \
			   $(if $(wildcard /etc/redhat-release), fedora))
DISTRO := $(strip $(DISTRO))

check_install = @which $1 1>/dev/null 2>&1 \
                && echo "✔ $1" \
                || echo "✘ no '$1' installed, run 'make $1' to fix"
check_python3 = @python3 -c "import $1" 1>/dev/null 2>&1 \
                && echo "✔ python3: $1" \
                || echo "✘ python3: no package '$1', run $2 to fix"
check_pythonpath = @echo $$PYTHONPATH | grep $(PROJECT_DIR)/src 1>/dev/null 2>&1 \
                && echo "✔ env: PYTHONPATH" \
                || echo "✘ env: PYTHONPATH: run 'export PYTHONPATH=\$$PYTHONPATH:$(PROJECT_DIR)/src' to fix"
check_rootlibs = @[[ -d root_libs ]] \
                && echo "✔ root: root_libs" \
                || echo "✘ no 'root_libs', run 'make shared' inside src/root_classes/src to fix"
check_rootimport = @root -l -q -e 'gSystem->Load("$1")' 1>/dev/null 2>&1 \
                && echo "✔ root: $1" \
                || echo "✘ root: no '$1', 'export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:`pwd`/root_libs' to fix"

.PHONY: help
help:
	@echo "* check             check if all prerequisities are installed"
	@echo "* root              install root with pyROOT bindings for python3"
	@echo "* madx              install MAD-X"
	@echo "* clean             clean output files"

####################
#  PREREQUISITIES
####################

.PHONY: check
check:
	$(call check_install,madx)
	$(call check_install,pip)
	$(call check_install,python3)
	$(call check_install,root)
	$(call check_rootlibs)
	$(call check_rootimport,LHCOpticsApproximator.so)
	$(call check_python3,ROOT,'make root')
	$(call check_python3,cpymad,'python3 -m pip install --user cpymad')
	$(call check_python3,jupyter,'python3 -m pip install --user jupyter')
	$(call check_pythonpath)

root: root-dep
ifeq (,$(shell which root 2> /dev/null))
	wget -L -O root.tar.gz https://root.cern/download/root_v6.18.04.source.tar.gz
	tar -zxf root.tar.gz -C root
	rm root.tar.gz
	cd root
	mkdir obj
	cd obj
	cmake -DPYTHON_EXECUTABLE=$(which python3) ..
	cmake --build -j4 .
endif

.PHONY: root-dep
root-dep:
ifeq ($(DISTRO), ubuntu)
	apt-get update
	apt-get install python3 python3-devel python-pip
	apt-get install git dpkg-dev cmake g++ gcc binutils \
		libx11-dev libxpm-dev libxft-dev libxext-dev
else ifeq ($(DISTRO), fedora)
	dnf update
	dnf install python3 python3-devel python3-numpy \
		git cmake gcc-c++ gcc binutils \
		libX11-devel libXpm-devel libXft-devel libXext-devel
	dnf history info last | head -n1 > .installed
else
	$(error 'Linux version not recognized. Check https://root.cern.ch/build-prerequisites' )
endif

.PHONY: madx
madx:
	wget -L -O madx https://madx.web.cern.ch/madx/releases/last-rel/madx-linux64-gnu
	mkdir -p ~/.local/bin
	install madx ~/.local/bin/madx
	-rm madx

.PHONY: set-paths
set-paths:
	grep rmucha -rl . | xargs sed -i "s|/eos/.*/SWAN_projects/|$(pwd)|"

.PHONY: clean
clean:
