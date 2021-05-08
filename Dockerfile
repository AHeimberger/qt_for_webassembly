FROM emscripten/emsdk:1.39.8


# setup environment
ENV DEBIAN_FRONTEND     noninteractive
ENV DIR_DEPLOY          /deploy/
ENV DIR_SOURCE          /source/


# setup default build arguments
ARG GROUP_ID=1000
ARG USER_ID=1000
ARG USER_NAME=builduser


# prerequisites
RUN apt-get -qq update && \
    apt-get -qq dist-upgrade && \
    # install dependencies
    apt-get install -qq -y --no-install-recommends \
    tzdata locales \
    software-properties-common \
    ca-certificates \
    build-essential \
    wget tar ssh git \
    python3 python3-pip python3-dev \
    mesa-common-dev \
    libgl1-mesa-dev

# install qt
RUN wget -c https://download.qt.io/archive/qt/5.15/5.15.2/single/qt-everywhere-src-5.15.2.tar.xz && \
    tar -xvf qt-everywhere-src-5.15.2.tar.xz && \
    cd qt-everywhere-src-5.15.2 && \
    ./configure -xplatform wasm-emscripten -nomake examples -nomake tests -opensource -prefix $PWD/qtbase --confirm-license && \
    make -j


# create group and user, user will be set after copying files
RUN groupmod --new-name ${USER_NAME} emscripten && \
    usermod -l ${USER_NAME} emscripten


# create volume mounts
RUN mkdir ${DIR_DEPLOY} && \
    chown -R ${USER_NAME}:${USER_NAME} ${DIR_DEPLOY}


# copy scripts
COPY . ${DIR_SOURCE}
RUN chown -R ${USER_NAME}:${USER_NAME} ${DIR_SOURCE}


# switch USER all commands using RUN will be executed as user
USER ${USER_NAME}


# set working directory
WORKDIR ${DIR_SOURCE}


# build novigo project
ENTRYPOINT ["./entrypoint.sh"]
CMD ["help"]
