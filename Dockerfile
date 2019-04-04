# How to use:
#
# 1   : make sure you start the apt-cacher container first, if you plan on recreating this container while debugging the Dockerfile script
#
# 2   : to stop and remove the current container, use "docker stop ns3_container && docker rm ns3_container"
#
# 3   : to rebuild the container and start it, use "docker build -t ns3 - < Dockerfile" to prepare the container
#
# 4   : Choose the following based on your OS
# 4.1 : Windows,   use "docker run -i -t -v %cd%\:/NS3 --name ns3_container ns3"
# 4.2 : Unix-like, use "docker run -i -t -v `cwd`\:/NS3 --name ns3_container ns3"

FROM ubuntu:18.10

#Uncomment the following lines if using the apt-cacher container
#Use docker apt-get caching to prevent redownloads
#RUN  echo 'Acquire::http::No-Cache true;' >> /etc/apt/apt.conf
#RUN  echo 'Acquire::http::Pipeline-Depth 0;' >> /etc/apt/apt.conf
#RUN  echo 'Acquire::http { Proxy "http://docker.for.win.localhost:3142"; };' >> /etc/apt/apt.conf.d/01proxy

#Update packages list
RUN apt update

RUN apt -y install apt-utils

#Dependencies for git and base NS3
RUN apt-get -y install git gcc g++ cmake python

#Dependencies for NetAnim
RUN apt-get -y install qt4-default 

#Dependencies for debugging
RUN apt-get -y install gdb valgrind 

#Dependencies for pcap traces
RUN apt-get -y install tcpdump 

#Dependencies for VcPkg
RUN apt-get -y install curl unzip tar


#Unnecessary but kept for reference

#Origin of NS3 files
#	0 : share host folder with container, requires "docker run -v host_path:container_path" (faster on Docker for Windows, as it doesn't copy the whole current folder to the Linux VM)
#	1 : copy from current folder, requires "docker build -t ns3 ."
#		ADD ./ /NS3
#	2: clone from git repo
#		RUN git clone https://github.com/Gabrielcarvfer/NS3.git 

#Other dependencies
#	Dependencies for python development and pyviz
#	RUN apt-get -y install mercurial python-setuptools python-pygraphviz python-kiwi python-pygoocanvas libgoocanvas-dev ipython
#	
#	Dependencies for MPI distributed emulation
#	RUN apt-get -y install openmpi-bin openmpi-common openmpi-doc libopenmpi-dev
#	
#	Dependencies for statistics framework
#	RUN apt-get -y install sqlite sqlite3 libsqlite3-dev 
#	
#	Dependencies for config store
#	RUN apt-get -y install libxml2 libxml2-dev
#	
#	Dependencies for python bindings
#	RUN apt-get -y install libc6-dev libc6-dev-i386 libclang-dev
#	RUN pip -y install cxxfilt
#	
#	Dependencies for GTK based configuration system
#	RUN apt-get -y install libgtk2.0-0 libgtk2.0-dev 
#	
#	Dependencies for virtual machines
#	RUN apt-get -y install vtun lxc
#	
#	Dependencies for openflow
#	RUN apt-get -y install libboost-signals-dev libboost-filesystem-dev
#
#	Dependencies for doxygen and manual
#	RUN apt-get -y install doxygen graphviz imagemagick texlive-extra-utils texlive-latex-extra texlive-font-utils texlive-lang-portuguese dvipng python-sphinx dia 
#	
#	Dependencies for accurate WiFi error models
#	RUN apt-get -y install gsl-bin libgsl2 libgsl-dev 
#	
#	Dependencies for Network Simulation Cradle (nsc)
#	RUN apt-get -y install flex bison libfl-dev


#Navigate into the NS3 folder, create a cmake cache folder, navigate into it and build project
#RUN cd /NS3 && mkdir cmake-cache && cd cmake-cache && cmake .. && make all -j8

#Navigate into NS3 folder and execute a binary every time the container is started
#CMD cd /NS3 && sh
