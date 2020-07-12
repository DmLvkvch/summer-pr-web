FROM ubuntu:18.04
MAINTAINER DmLvkvch

RUN rm /bin/sh && ln -s /bin/bash /bin/sh

ENV LC_ALL C.UTF-8
ENV LANG C.UTF-8
RUN sed -i 's/ universe/ universe multiverse/' /etc/apt/sources.list
RUN apt update && \
	apt upgrade -y && \
	apt dist-upgrade -y && \
	apt install -y \
	git \
	curl \
	g++ \
	libbson-1.0 \
	libmongoc-1.0-0 \
	make \
	libboost-system-dev \
	zlib1g-dev \
	wget \
	cmake \
	libcurl4-openssl-dev \
	xvfb \
	libjsoncpp-dev \
	flex \
	pkg-config \
    	libssl-dev \
    	libsasl2-dev \
	python-dev \
	python3-dev \
	dh-make \
	debhelper \
	checkinstall \
	fuse \
	snapcraft \
	bison \
	libxcursor-dev \
	libxcomposite-dev \
	software-properties-common \
	build-essential \
	libssl-dev \
	libxcb1-dev \
	libx11-dev \
	libgl1-mesa-dev \
	libudev-dev \
	libjsoncpp-dev \
	qt5-default \
	libqt5webkit5-dev \
	qtbase5-private-dev
COPY ./src /home/dmlvkvch
RUN ln -s /usr/include/jsoncpp/json/ /usr/include/json
RUN apt-get -y update \
	&& apt-get -y upgrade

RUN apt-get install -y \
	openssh-server \
	g++ \
	cmake \
	git

#installing the mongoc dependencies and driver
	RUN apt-get -y update \
	&& apt-get -y upgrade

RUN apt-get install -y \
	openssh-server \
	g++ \
	cmake \
	git

#installing the mongoc dependencies and driver
RUN apt-get install -y \
	pkg-config \
	libssl-dev \
	libsasl2-dev
RUN git clone https://github.com/desmoteo/telegram-bot-api
WORKDIR telegram-bot-api
RUN cmake . -DOTHER_HDR_DIR="usr/include/jsoncpp/" && make clean && make && make install
RUN git clone https://github.com/mongodb/mongo-c-driver.git
WORKDIR mongo-c-driver
RUN python build/calc_release_version.py > VERSION_CURRENT
RUN mkdir cmake-build
WORKDIR cmake-build
RUN cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
RUN sudo make install
RUN apt-get install -y qtcreator
ENV HOME /root
WORKDIR $HOME
RUN git clone https://github.com/mongodb/mongo-cxx-driver.git \
    --branch releases/stable --depth 1
WORKDIR mongo-cxx-driver/build
RUN cmake ..                                            \
    -DCMAKE_BUILD_TYPE=Release                      \
    -DBUILD_SHARED_AND_STATIC_LIBS=ON               \
    -DCMAKE_PREFIX_PATH=/opt/mongo-c-driver         \
    -DCMAKE_INSTALL_PREFIX=/opt/mongo-cxx-driver
RUN make && sudo make install
RUN apt-get install -y libpthread-stubs0-dev
WORKDIR /home/dmlvkvch/tufao
RUN git clone https://github.com/vinipsmaker/tufao
WORKDIR tufao/
RUN git checkout 1.1
RUN mkdir build
WORKDIR build
RUN ls
RUN cmake _DCMAKE_INSTALL_PREFIX=/usr ..
RUN make -j5
RUN sudo make install
WORKDIR /home/dmlvkvch
RUN ls
RUN make -C src
RUN qmake "CONFIG+=tg" tg.pro
RUN ls
RUN git clone https://github.com/Kolsha/VK
WORKDIR VK
RUN make
RUN ls
WORKDIR /home/dmlvkvch
RUN cp -i VK/vk.so .
ENTRYPOINT ["./tg"]
