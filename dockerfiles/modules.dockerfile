FROM proslam:base

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
catkin build srrg_proslam

# RUN echo "== Start Release build == " && \
# cd /root/catkin_ws/src/srrg_proslam && \
# git remote update && \
# git fetch --all && \
# git checkout ${BRANCH} && \
# git pull && \
# git branch && \
# mkdir build_release && cd build_release && \
# cmake -DCMAKE_BUILD_TYPE=Release -GNinja .. && ninja