FROM pro_and_orb:data

ARG BRANCH=development
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN useradd -m user && yes password | passwd user

RUN echo "== Start build == " && \
    cd /root/catkin_ws/src/srrg_proslam && \
    git remote update && \
    git fetch --all && \
    git checkout ${BRANCH} && \
    git pull && \
    git branch && \
    cd ~/catkin_ws/src && \
    src_build