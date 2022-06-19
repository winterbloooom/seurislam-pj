FROM proslam:data

ARG BRANCH=development
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN useradd -m user && yes password | passwd user

RUN echo "== Start Debug build == " && \
    cd /root/catkin_ws/src/srrg_proslam && \
    git remote update && \
    git fetch --all && \
    git checkout ${BRANCH} && \
    git pull && \
    git branch && \
    cd ~/catkin_ws/src && \
    catkin build --make-args tests -- srrg_proslam

RUN echo "== Start Test == " && \
    cd /root/catkin_ws/devel/lib/srrg_proslam && \
    ./test_app