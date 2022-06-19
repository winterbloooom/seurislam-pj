FROM ubuntu:bionic

MAINTAINER EunGiHan
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN echo "== Install Basic Tools == " && \
    apt-get install build-essential -y && \
    # Related to build...
    apt-get install cmake -y && \
    apt-get install git -y && \
    apt-get install sudo -y && \
    apt-get install wget -y && \
    apt-get install ninja-build -y && \
    apt-get install software-properties-common -y && \
    apt-get install python3 -y && \
    apt-get install python3-pip -y && \
    # Related to JetBrains CLion Docker develpoment...
    apt-get install -y ssh && \
    apt-get install -y gcc && \
    apt-get install -y g++ && \
    apt-get install -y gdb && \
    apt-get install -y clang && \
    apt-get install -y cmake && \
    apt-get install -y rsync && \
    apt-get install -y tar && \
    apt-get install -y mesa-utils && \
    # Related to X11 remote display
    apt-get install -y libgl1-mesa-glx && \
    apt-get install -y libglu1-mesa-dev && \
    apt-get install -y mesa-common-dev && \
    apt-get install -y x11-utils && \
    apt-get install -y x11-apps && \
    apt-get clean

RUN pip3 install pyyaml
RUN pip3 install gitpython

RUN apt-get autoclean

RUN apt-get install vim

RUN echo "== Install ProSLAM Prerequisites == " && \
    apt-get install build-essential -y && \
    libeigen3-dev -y && \
    libsuitesparse-dev  -y && \
    freeglut3-dev  -y && \
    libqglviewer-dev-qt5  -y && \
    libyaml-cpp-dev

RUN apt-get install qt5* -y

RUN apt-get install libssl-dev

# change -j<cores> if you want
RUN echo "== Install CMake Latest version == " && \
    cd home && \
    wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz && \
    tar -xvzf cmake-3.20.0.tar.gz && \
    rm cmake-3.20.0.tar.gz && \
    cd cmake-3.20.0 && \
    ./bootstrap && \
    make -j4 && \
    make install && \
    cmake --version && \
    cd ~

RUN echo "== Install ROS melodic == " && \
    sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' && \
    apt install curl && \
    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add - && \
    apt update && \
    apt install ros-melodic-desktop-full -y && \
    echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc && \
    source ~/.bashrc && \
    apt install python-rosdep -y && \
    apt install python-rosinstall -y && \
    apt install python-rosinstall-generator -y && \
    apt install python-wstool -y && \
    apt install build-essential -y && \
    rosdep update

RUN apt-get install python-catkin-tools -y

RUN apt-get install ninja-build

# change -j<cores> if you want
RUN echo "== Install ceres-solver == " && \
    cd /home && \
    apt-get install libgoogle-glog-dev -y && \
    apt-get install libgflags-dev -y && \
    apt-get install libatlas-base-dev -y && \
    apt-get install libeigen3-dev -y && \
    git clone https://ceres-solver.googlesource.com/ceres-solver && \
    mkdir ceres-bin && \
    cd ceres-bin && \
    cmake ../ceres-solver && \
    make -j4 && \
    make test && \
    make install

RUN echo "== Make Catkin Workspace == " && \
    mkdir -p /root/catkin_ws/src && \
    cd /root/catkin_ws/src && \
    catkin_make

RUN echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc && \
    echo "export ROS_HOSTNAME=localhost" >> ~/.bashrc && \
    echo "export ROS_MASTER_URI=http://localhost:11311" >> ~/.bashrc && \
    source ~/.bashrc

RUN echo "== Install G2O == " && \
    git clone https://github.com/yorsh87/g2o_catkin.git && \
    cd /root/catkin_ws && \
    rm -rf /root/catkin_ws/build && \
    rm -rf /root/catkin_ws/devel && \
    catkin build g2o_catkin -DGIT_TAG=26f775d144f3b09bc072b90b903631036a1e4107

RUN touch /etc/ld.so.conf.d/g2o.conf && \
    echo "/root/catkin_ws/devel/lib" >> /etc/ld.so.conf.d/g2o.conf

RUN echo "== Clone and Build Source Codes == " && \
    cd /root/catkin_ws/src && \
    git clone https://github.com/EunGiHan/seurislam-pj.git && \
    ./pull_srrg_packages.bash && \
    catkin build --make-args tests -- srrg_proslam
    
RUN echo "== Set aliases ==" && \
    echo "alias cb="cd ~/catkin_ws/src && catkin build --make-args tests -- srrg_proslam"" >> ~/.bashrc && \
    echo "alias src="cd ~/catkin_ws/src/srrg_proslam"" >> ~/.bashrc && \
    echo "alias runtest="cd ~/catkin_ws/devel/lib/srrg_proslam && ./test_app"" >> ~/.bashrc && \
    echo "alias rungui="cd ~/catkin_ws/devel/lib/srrg_proslam && ./app -c ~/catkin_ws/src/srrg_proslam/configurations/configuration_kitti.yaml -use-gui"" >> ~/.bashrc && \
    echo "alias gitlogin="echo '(ID)EunGiHan (PW)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'"" >> ~/.bashrc && \
