DESTDIR ?= ~/bin
PYTHON = python3
PROJECT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

check_install = @which "$1" 1>/dev/null 2>&1 \
                && echo "✔ $1" \
				|| echo "✘ no '$1' installed, run $2 to fix"
check_python = @$(PYTHON) -c "import $1" 1>/dev/null 2>&1 \
                && echo "✔ $(PYTHON): $1" \
                || echo "✘ $(PYTHON): no package '$1', run $2 to fix"
check_pythonpath = @echo $$PYTHONPATH | grep "$(PROJECT_DIR)/src" 1>/dev/null 2>&1 \
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
	@echo -e "* check       if all prerequisities are installed"
	@echo -e "* madx        install MAD-X. Run 'make madx DESTDIR=your/dir' to specify destination path (default ~/bin)"

.PHONY: check
check:
	$(call check_install,madx,'make madx')
	$(call check_install,pip,'./install_root.sh')
	$(call check_install,python3,'./install_root.sh')
	$(call check_install,root,'./install_root.sh')
	$(call check_rootlibs)
	$(call check_rootimport,LHCOpticsApproximator.so)
	$(call check_python,ROOT,'./install_root.sh')
	$(call check_python,cpymad,'make cpymad')
	$(call check_python,pandas,'make pandas')
	$(call check_python,seaborn,'make seaborn')
	$(call check_python,jupyter,'make jupyter')
	$(call check_pythonpath)

.PHONY: madx
madx:
	wget -L -O madx https://madx.web.cern.ch/madx/releases/last-rel/madx-linux64-gnu
	mkdir -p $(DESTDIR)
	install madx $(DESTDIR)/madx
	-rm madx

cpymad: ; $(PYTHON) -m pip install --user cpymad
pandas: ; $(PYTHON) -m pip install --user pandas
seaborn: ; $(PYTHON) -m pip install --user seaborn
jupyter: ; $(PYTHON) -m pip install --user jupyter

# TODO: this part is hard-coded and may not work properly
.PHONY: set-paths
set-paths:
	grep rmucha -rl . | xargs sed -i "s|/eos/.*/SWAN_projects/|$(pwd)|"
