#Download base image ubuntu 23.04
FROM ubuntu:22.04
# Update Ubuntu Software repository
RUN apt update && apt upgrade -y
ARG DEBIAN_FRONTEND=noninteractive

RUN apt install -y wget unzip cmake python3 python3-distutils python3-apt
RUN apt install -y git
RUN apt install -y uuid-dev pkg-config
RUN apt install -y build-essential
RUN apt install iverilog
RUN apt install -y vim
ENV PYTHON=python3
RUN apt install -y python3-virtualenv

RUN git clone https://bitbucket.org/debjitp/goldminer.git
WORKDIR "/goldminer"
RUN virtualenv --python="/usr/bin/python3" 3vgoldmine

SHELL ["/bin/bash", "-c"]
RUN source 3vgoldmine/bin/activate
RUN apt install -y graphviz libgraphviz-dev
RUN pip install pygraphviz
RUN pip install -r requirements3.txt
WORKDIR "/goldminer/src3/vcd_parser"
RUN python3 setup.py build_ext --inplace
RUN cp build/temp.linux-x86_64-3.10/parse_timeframes.o vcd_parser/
RUN ln -s ./vcd_parser/parse_timeframe*.so parse_timeframes.so
RUN wget https://www.dropbox.com/s/cym1olcdsrc7rxs/pyverilog3_customized.tar.gz?dl=0 -O ./pyverilog3.tar.gz
RUN tar -xzvf pyverilog3.tar.gz
RUN cp pyverilog /usr/lib/python3.10/ -r
WORKDIR "/goldminer"
RUN mkdir work
WORKDIR "/goldminer/work"




# run the command
CMD ["bash"]

