FROM ubuntu:22.04 AS ns3-oran

WORKDIR .
# install dependecies
RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    ninja-build \
    python3 \
    cmake \
    libarmadillo-dev \
    libmlpack-dev \
                pybind11-dev \
                python3-dev \
                ca-certificates \
                python3-pip \
                git \
    && rm -rf /var/lib/apt/lists/*

# setup RL model
RUN git clone -b multiple_ue https://github.com/MatheusOCruz/Handover_ORAN.git



RUN pip install /Handover_ORAN/HandoverRL

#CMD ["./ns3", "run", "HandoverXappsScenario --scenario=5 --outputFile=0_outputRlRicInitiated.csv --useThreeGppChannel=1"]
