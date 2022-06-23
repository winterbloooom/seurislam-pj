FROM pro_and_orb:data

ARG BRANCH=development
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN useradd -m user && yes password | passwd user

RUN echo "== Start Build == " && \
    cd /root/catkin_ws/src/srrg_proslam && \
    git remote update && \
    git fetch --all && \
    git checkout ${BRANCH} && \
    git pull && \
    git branch && \
    cd ~/catkin_ws/src && \
    catkin build 

RUN echo "== Start Run == " && \
    cd ~/dataset/KITTI_Pro && \
    ~/catkin_ws/devel/lib/srrg_proslam/app -c ~/catkin_ws/src/srrg_proslam/configurations/configuration_kitti.yaml -use-gui