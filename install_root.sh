#!/bin/bash
# Automatic check and installation of ROOT package
# Should work for version 18.04 on ubuntu, fedora and CentOS7

INSTALL_PATH=$(pwd)
PYTHON=python3
ROOT_VERSION=6.18.04

echo "Checking linux distribution..."
distr=unrecognized
[[ -f /etc/debian_version ]] && distro=ubuntu
[[ -f /etc/redhat-release ]] && distro=fedora
[[ -f /etc/centos-release ]] && distro=centos
echo "* [$distro]";


echo "Checking ROOT and pyROOT installation..."
if [[ $(which root 2> /dev/null) ]]; then
    echo "✔ ROOT     installed"
else
    echo "✘ ROOT     not installed"
fi

if $($PYTHON -c "import ROOT" 1>/dev/null 2>&1); then
    echo "✔ pyROOT   installed for $PYTHON"; echo "Complete!"
    exit 0
else
    echo "✘ pyROOT   not installed for $PYTHON"
fi


echo "Installing necessary prerequisities..."
case $distro in
    ubuntu)
        sudo apt-get update
        sudo apt-get install python3 python3-devel python-pip \
            git dpkg-dev cmake g++ gcc binutils \
            libx11-dev libxpm-dev libxft-dev libxext-dev ;;
    fedora)
        sudo dnf update
        sudo dnf install python3 python3-devel python3-numpy \
            git cmake gcc-c++ gcc binutils \
            libX11-devel libXpm-devel libXft-devel libXext-devel ;;
    centos)
        sudo dnf update
        sudo dnf install python3 python3-devel python3-numpy \
            git cmake gcc-c++ gcc binutils \
            libX11-devel libXpm-devel libXft-devel libXext-devel ;;
    *)
        echo "Linux distribution not recognized. Follow the steps on https://root.cern.ch/build-prerequisites"
        exit 1 ;;
esac


echo ""
echo "Ready to install ROOT in '$INSTALL_PATH'"
echo "If you want to install it somewhere else, change \$INSTALL_PATH variable in this script"
echo "or run $0 from your desired directory."
echo "Also, if you want to use pyROOT bindings for other version than '$PYTHON', change"
echo "\$PYTHON variable in this script."
echo ""
echo "Installation requires around 4 GB of free memory."
read -r -p "Proceed? [y/N] " answer
[[ $answer != [yY]?([eE][sS]) ]] && { echo "Complete!"; exit 0; }

cd "$INSTALL_PATH" || { echo "error: '$INSTALL_PATH' is not a directory"; exit 1; }
wget -L -O root.tar.gz https://root.cern/download/root_v$ROOT_VERSION.source.tar.gz
tar -zxf root.tar.gz
rm root.tar.gz
[[ -d root-$ROOT_VERSION ]] || { echo "error: no such directory '$INSTALL_PATH/root-$ROOT_VERSION'"; exit 1; }
cd root-$ROOT_VERSION
mkdir obj
cd obj
cmake -DPYTHON_EXECUTABLE=$(which $PYTHON) ..
cmake --build . -j4

if [[ $? -eq 0 ]]; then
    echo "ROOT successfully installed in '$INSTALL_PATH/root-$ROOT_VERSION'"
    echo "Run 'source $INSTALL_PATH/root-$ROOT_VERSION/obj/bin/thisroot.sh' and start using ROOT"
    echo "Complete!"
    exit 0
fi

