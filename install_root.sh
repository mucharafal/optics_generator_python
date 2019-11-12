#!/bin/bash
# Automatic installation of ROOT package
# Should work for version 18.04 on ubuntu, fedora and CentOS7

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

if $(python3 -c "import ROOT" 1>/dev/null 2>&1); then
    echo "✔ pyROOT   installed for python3"; echo "Complete!"
    exit 0
elif $(python -c "import ROOT" 1>/dev/null 2>&1); then
    echo "✔ pyROOT   installed for python"; echo "Complete!"
    exit 0
else
    echo "✘ pyROOT   not installed for any python version"
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
        echo "Linux version not recognized. Follow the steps on https://root.cern.ch/build-prerequisites"
        exit 1 ;;
esac

read -r -p "Do you want to install ROOT for python3 [y/N]? " answer
if [[ $answer != [yY]?([eE][sS]) ]]; then
    echo "Nothing to do, finishing..."
    exit 0 
fi

echo "Installing ROOT in `pwd`"
wget -L -O root.tar.gz https://root.cern/download/root_v6.18.04.source.tar.gz
tar -zxf root.tar.gz -C root
rm root.tar.gz
cd root
mkdir obj
cd obj
cmake -DPYTHON_EXECUTABLE=$(which python3) ..
cmake --build -j4 .
