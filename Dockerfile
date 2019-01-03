FROM ubuntu

#Update packages list
RUN apt-get update

RUN apt-get -y install apt-utils

#Dependencies for git and base NS3
RUN apt-get -y install git gcc g++ cmake 

#Dependencies for NetAnim
RUN apt-get -y install qt4-default 

#Dependencies for python development and pyviz
RUN apt-get -y install mercurial python-setuptools python-pygraphviz python-kiwi python-pygoocanvas libgoocanvas-dev ipython python-pip

#Dependencies for MPI distributed emulation
RUN apt-get -y install openmpi-bin openmpi-common openmpi-doc libopenmpi-dev

#Dependencies for debugging
RUN apt-get -y install gdb valgrind 

#Dependencies for doxygen and manual
#RUN apt-get -y install doxygen graphviz imagemagick texlive-extra-utils texlive-latex-extra texlive-font-utils texlive-lang-portuguese dvipng python-sphinx dia 

#Dependencies for accurate WiFi error models
#RUN apt-get -y install gsl-bin libgsl2 libgsl-dev #can be installed with vcpkg

#Dependencies for Network Simulation Cradle (nsc)
#RUN apt-get -y install flex bison libfl-dev

#Dependencies for pcap traces
RUN apt-get -y install tcpdump 

#Dependencies for statistics framework
#RUN apt-get -y install sqlite sqlite3 libsqlite3-dev 

#Dependencies for config store
RUN apt-get -y install libxml2 libxml2-dev

#Dependencies for python bindings
#RUN apt-get -y install libc6-dev libc6-dev-i386 libclang-dev
#RUN pip -y install cxxfilt

#Dependencies for GTK based configuration system
#RUN apt-get -y install libgtk2.0-0 libgtk2.0-dev 

#Dependencies for virtual machines
#RUN apt-get -y install vtun lxc

#Dependencies for openflow
#RUN apt-get -y install libboost-signals-dev libboost-filesystem-dev

#Dependencies for VcPkg
RUN apt-get -y install curl unzip tar

#Dependencies for PyTorch Lib (C++)
RUN python -m pip install https://download.pytorch.org/whl/cpu/torch-1.0.0-cp27-cp27mu-linux_x86_64.whl
RUN python -m pip install torchvision 

#Clone NS3 with Cmake
#RUN git clone https://github.com/Gabrielcarvfer/NS3.git #fetch from remote source or use the current context with docker build -t ns3 .

#Create a cmake folder, move to it and build project
CMD mkdir cmake && cd cmake && cmake .. && make all -j8
