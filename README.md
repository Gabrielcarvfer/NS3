# ns3-O-RL: Framework de Prototipagem Rápida de xApps com Aprendizagem por Reforço em redes O-RAN

A Inteligência Artificial (IA) é um elemento essencial nos controla-
dores inteligentes O-RAN (RICs), na pilha de redes 6G e futuras. Reduzir a
barreira para a prototipagem de aplicações de Aprendizado por Reforço (RL)
nos stacks 3GPP e O-RAN permitindo inovações no setor. Estes mesmos modelos podem
ser portados posteriormente para um RIC real. Como prova de
conceito, implementamos um xApp de controle de handover no O-RAN, integrando
a ferramenta ns3-ORAN com um modelo de RL baseado em PyTorch,
treinável offline ou online. O framework tem baixa sobrecarga de comunicação
em comparação à ns3-ai e ns3-gym. Também é mais acessível que o desenvolvimento nativo de xApps, com a complicada configuração e operação de testbeds.

# Selos Considerados

Os selos considerados são: Disponíveis e Funcionais.

# Informações básicas

O código-fonte da ferramenta está disponível no repositório https://github.com/Gabrielcarvfer/NS3/tree/NS3.40-ns3-o-rl, juntamente a outros artefatos, como: pesos do modelo treinado, scripts auxiliares para simulações, arquivos Dockerfile e docker-compose para configuração do ambiente de simulação.

O modelo de aprendizagem por reforço, junto a scripts de treinamento com dados sintéticos e plotagem de resultados estão disponíveis no repositório https://github.com/MatheusOCruz/Handover_ORAN. 

A documentação da ferramenta se encontra no seguinte link https://gabrielcarvfer.github.io/NS3/ns3_ORAN_RL/.

Foram utilizadas plataformas Ampere ARM com Ubuntu 20.04, 128GB de RAM ECC DDR4 2600MTs, 160 cores. E Intel i7-13900HX, Ubuntu 22.04 e 24.04, 16GB de RAM DDR5 5600MTs. Em ambos os casos, foram utilizados SSDs NVMe.

# Dependências

Foram utilizadas as últimas versões disponíveis de releases estáveis de longo suporte do Ubuntu. Os pacotes geridos pelo sistema necessários são:

- g++ 
- ninja-build
- python3
- cmake
- libarmadillo-dev
- libmlpack-dev
- pybind11-dev
- python3-dev
- ca-certificates
- python3-pip
- git

Para o modelo de aprendizagem por reforço, são necessários os seguintes pacotes e versões via gerenciador PIP para pacotes Python:

- torch >= 2.6.0
- numpy >= 2.2.2
- matplotlib >= 3.10.0

# Preocupações com segurança

Os artefatos em si não oferecem riscos de segurança aos examinadores, porém as dependências utilizadas podem oferecer algum risco, visto que são controladas por terceiros.

# Instalação

Existem dois meios de se configurar o ambiente necessário. Manualmente, ou através de docker-compose.

Manualmente pode ser instalado e executado com 

```
apt-get update && apt-get install -y \
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
    git
git clone -b NS3.40-ns3-o-rl https://github.com/Gabrielcarvfer/NS3
cd NS3
git clone -b multiple_ue https://github.com/MatheusOCruz/Handover_ORAN.git
pip install ./Handover_ORAN/HandoverRL
./ns3 configure --enable-examples -d release
./ns3 run "HandoverXappsScenario --scenario=5 --outputFile=0_outputRLRicInitiated.csv --useThreeGppChannel=1
```

Alternativamente, pode ser usado

```
git clone -b NS3.40-ns3-o-rl https://github.com/Gabrielcarvfer/NS3
cd NS3
docker-compose build
docker run “./ns3 run HandoverXappsScenario – --scenario=5 --outputFile=0_outputRLRicInitiated.csv --useThreeGppChannel=1”
```

O processo de baixar e instalar a aplicação deve ser descrito nesta seção. Ao final deste processo já é esperado que a aplicação/benchmark/ferramenta consiga ser executada.

# Teste mínimo

Para verificar que tudo está funcionando como esperado, é possível executar o script ``PlotAllScenarios.sh``. Utilizando a instalação via docker-compose:
```
git clone -b NS3.40-ns3-o-rl https://github.com/Gabrielcarvfer/NS3
cd NS3
docker-compose build
docker run ns3-oran ./PlotAllScenarios.sh”
```

Este script deve gerar 6 figuras (dentro do container), duas para cada padrão de movimento, relativas às vazões dos UEs em cada um dos cenários (assim como medidos em sua camada de rede, e KPMs reportados pelos E2Nodes ao RIC).

- triangle_kpms.png
- triangle_ueThrLog.png
- opp_senoids_kpms.png
- opp_senoids_ueThrLog.png
- offset_senoids_kpms.png
- offset_senoids_ueThrLog.png

# LICENSE

O projeto é distribuído sob a licença GPLv2. Veja o arquivo LICENSE para mais detalhes.

