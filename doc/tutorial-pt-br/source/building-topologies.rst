.. include:: replace.txt

..
	========================================================================================
	Translated for portuguese by the students of the inter-institutional doctorate program of IME-USP/UTFPR-CM.
	
	Traduzido para o portugu�s pelos alunos do programa de doutorado inter institucional do Instituto de Matem�tica e Estat�stica da Universidade de S�o Paulo --- IME-USP em parceria com a Universidade Tecnol�gica Federal do Paran� - Campus Campo Mour�o --- UTFPR-CM:
	
	* Frank Helbert (frank@ime.usp.br);
	* Luiz Arthur Feitosa dos Santos (luizsan@ime.usp.br);
	* Rodrigo Campiolo (campiolo@ime.usp.br).
	========================================================================================


..
	Building Topologies

Construindo topologias
----------------------

..
	Building a Bus Network Topology

Construindo uma rede em barramento
**********************************

..
	In this section we are going to expand our mastery of |ns3| network 
	devices and channels to cover an example of a bus network.  |ns3|
	provides a net device and channel we call CSMA (Carrier Sense Multiple Access).


Nesta se��o, o conhecimento sobre dispositivos de rede e canais de comunica��o s�o expandidos de forma a abordar um exemplo de uma rede em barramento. O |ns3| fornece um dispositivo de rede e canal que � chamado de CSMA (*Carrier Sense Multiple Access*).

..
	The |ns3| CSMA device models a simple network in the spirit of 
	Ethernet.  A real Ethernet uses CSMA/CD (Carrier Sense Multiple Access with 
	Collision Detection) scheme with exponentially increasing backoff to contend 
	for the shared transmission medium.  The |ns3| CSMA device and 
	channel models only a subset of this.

O dispositivo CSMA modela uma rede simples no contexto da Ethernet. Uma rede Ethernet real utiliza CSMA/CD (*Carrier Sense Multiple Access with Collision Detection*) com recuo bin�rio exponencial para lidar com o meio de transmiss�o compartilhado. O dispositivo e o canal CSMA do |ns3| modelam apenas um subconjunto deste.

..
	Just as we have seen point-to-point topology helper objects when constructing
	point-to-point topologies, we will see equivalent CSMA topology helpers in
	this section.  The appearance and operation of these helpers should look 
	quite familiar to you.

Assim como foi visto nos assistentes ponto-a-ponto (objetos) na constru��o de topologias ponto-a-ponto, veremos assistentes (objetos) equivalentes da topologia CSMA nesta se��o. O formato e o funcionamento destes assistentes ser�o bastante familiares para o leitor.

..
	We provide an example script in our examples/tutorial} directory.  This script
	builds on the ``first.cc`` script and adds a CSMA network to the 
	point-to-point simulation we've already considered.  Go ahead and open 
	``examples/tutorial/second.cc`` in your favorite editor.  You will have already seen
	enough |ns3| code to understand most of what is going on in this 
	example, but we will go over the entire script and examine some of the output.

Um novo c�digo exemplo � fornecido na pasta ``examples/tutorial``. Este baseia-se no c�digo ``first.cc`` e adiciona uma rede CSMA a simula��o ponto-a-ponto j� considerada. O leitor pode abrir o arquivo ``examples/tutorial/second.cc`` em seu editor favorito para acompanhar o restante desta se��o. Embora seja redundante, o c�digo ser� analisado em sua totalidade, examinando alguns de seus resultados.

..
	Just as in the ``first.cc`` example (and in all ns-3 examples) the file
	begins with an emacs mode line and some GPL boilerplate.

Assim como no exemplo ``first.cc`` (e em todos os exemplos ns-3), o arquivo
come�a com uma linha de modo Emacs e algumas linhas do padr�o GPL.

..
	The actual code begins by loading module include files just as was done in the
	``first.cc`` example.

O c�digo come�a com o carregamento de m�dulos atrav�s da inclus�o dos arquivos.

::

  #include "ns3/core-module.h"
  #include "ns3/network-module.h"
  #include "ns3/csma-module.h"
  #include "ns3/internet-module.h"
  #include "ns3/point-to-point-module.h"
  #include "ns3/applications-module.h"
  #include "ns3/ipv4-global-routing-helper.h"

..
	One thing that can be surprisingly useful is a small bit of ASCII art that
	shows a cartoon of the network topology constructed in the example.  You will
	find a similar "drawing" in most of our examples.

Algo que pode ser surpreendentemente �til � uma pequena arte ASCII que mostra um desenho da topologia da rede constru�da. Um "desenho" similar � encontrado na maioria dos exemplos no projeto.

..
	In this case, you can see that we are going to extend our point-to-point
	example (the link between the nodes n0 and n1 below) by hanging a bus network
	off of the right side.  Notice that this is the default network topology 
	since you can actually vary the number of nodes created on the LAN.  If you
	set nCsma to one, there will be a total of two nodes on the LAN (CSMA 
	channel) --- one required node and one "extra" node.  By default there are
	three "extra" nodes as seen below:

Neste caso, � poss�vel perceber que o exemplo ponto-a-ponto (a liga��o entre os n�s n0 e n1 abaixo) est� sendo estendido, agregando uma rede em barramento ao lado direito. Observe que esta � a topologia de rede padr�o, visto que o n�mero de n�s criados na LAN pode ser mudado. Se o atributo ``nCsma`` for configurado para um, haver� um total de dois n�s na LAN (canal CSMA) --- um n� obrigat�rio e um n� "extra". Por padr�o, existem tr�s n�s "extra", como pode ser observado:

::

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1   n2   n3   n4
//    point-to-point  |    |    |    |
//                    ================
//                      LAN 10.1.2.0

..
	Then the ns-3 namespace is ``used`` and a logging component is defined.
	This is all just as it was in ``first.cc``, so there is nothing new yet.

Em seguida, o `namespace` do ns-3 � `usado` e um componente de registro (`log`) � definido. At� aqui, tudo � exatamente como em ``first.cc``, n�o h� nada novo ainda.

::
  
  using namespace ns3;
  
  NS_LOG_COMPONENT_DEFINE ("SecondScriptExample");

..
	The main program begins with a slightly different twist.  We use a verbose
	flag to determine whether or not the ``UdpEchoClientApplication`` and
	``UdpEchoServerApplication`` logging components are enabled.  This flag
	defaults to true (the logging components are enabled) but allows us to turn
	off logging during regression testing of this example.

O programa principal come�a com um toque ligeiramente diferente. A vari�vel 'verbose' � usada para determinar se os componentes de registro de ``UdpEchoClientApplication`` e ``UdpEchoServerApplication`` estar�o habilitados. O valor padr�o � verdadeiro (os componentes de registro est�o ativados), mas � poss�vel desligar durante os testes de regress�o deste exemplo.

..
	You will see some familiar code that will allow you to change the number
	of devices on the CSMA network via command line argument.  We did something
	similar when we allowed the number of packets sent to be changed in the section
	on command line arguments.  The last line makes sure you have at least one
	"extra" node.

Voc� ver� c�digos familiares que lhe permitir�o mudar o n�mero de dispositivos na rede CSMA via linha de comando. Fizemos algo semelhante, quando permitimos que o n�mero de pacotes enviados em uma sess�o fosse alterado. A �ltima linha garante que voc� tenha pelo menos um n� "extra".

..
	The code consists of variations of previously covered API so you should be
	entirely comfortable with the following code at this point in the tutorial.

O c�digo consiste em varia��es de APIs abordadas anteriormente neste tutorial.

::

  bool verbose = true;
  uint32_t nCsma = 3;

  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc, argv);

  if (verbose)
    {
      LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

  nCsma = nCsma == 0 ? 1 : nCsma;

..
	The next step is to create two nodes that we will connect via the 
	point-to-point link.  The ``NodeContainer`` is used to do this just as was
	done in ``first.cc``.

O pr�ximo passo � a cria��o de dois n�s que iremos conectar atrav�s da liga��o ponto-a-ponto. O ``NodeContainer`` � usado para fazer isto, assim como foi feito em ``first.cc``.

::

  NodeContainer p2pNodes;
  p2pNodes.Create (2);

..
	Next, we declare another ``NodeContainer`` to hold the nodes that will be
	part of the bus (CSMA) network.  First, we just instantiate the container
	object itself.  

Em seguida, declaramos outro ``NodeContainer`` para manter os n�s que ser�o parte da rede em barramento (CSMA). Primeiro, instanciamos somente o cont�iner.

::

  NodeContainer csmaNodes;
  csmaNodes.Add (p2pNodes.Get (1));
  csmaNodes.Create (nCsma);

..
	The next line of code ``Gets`` the first node (as in having an index of one)
	from the point-to-point node container and adds it to the container of nodes
	that will get CSMA devices.  The node in question is going to end up with a 
	point-to-point device *and* a CSMA device.  We then create a number of 
	"extra" nodes that compose the remainder of the CSMA network.  Since we 
	already have one node in the CSMA network -- the one that will have both a
	point-to-point and CSMA net device, the number of "extra" nodes means the
	number nodes you desire in the CSMA section minus one.

Depois, na pr�xima linha de c�digo, ``obt�m-se`` o primeiro n� do cont�iner ponto-a-ponto e o adiciona ao cont�iner de n�s que ir�o receber dispositivos CSMA. O n� em quest�o vai acabar com um dispositivo ponto-a-ponto *e* um dispositivo CSMA. Em seguida, criamos uma s�rie de n�s "extra" que comp�em o restante da rede CSMA. Visto que j� temos um n� na rede CSMA -- aquele que ter� tanto um dispositivo ponto-a-ponto quanto um dispositivo de rede CSMA, o n�mero de n�s "extras" representa o n�mero desejado de n�s na se��o CSMA menos um.

..
	The next bit of code should be quite familiar by now.  We instantiate a
	``PointToPointHelper`` and set the associated default ``Attributes`` so
	that we create a five megabit per second transmitter on devices created using
	the helper and a two millisecond delay on channels created by the helper.

Instanciamos um ``PointToPointHelper`` e definimos os atributos padr�es de forma a criar uma transmiss�o de cinco megabits por segundo e dois mil�simos de segundo de atraso para dispositivos criados utilizando este assistente.

::

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

..
	We then instantiate a ``NetDeviceContainer`` to keep track of the 
	point-to-point net devices and we ``Install`` devices on the 
	point-to-point nodes.

Em seguida, instanciamos um ``NetDeviceContainer`` para gerenciar os dispositivos ponto-a-ponto e ent�o ``Instalamos`` os dispositivos nos n�s ponto-a-ponto.

..
	We mentioned above that you were going to see a helper for CSMA devices and
	channels, and the next lines introduce them.  The ``CsmaHelper`` works just
	like a ``PointToPointHelper``, but it creates and connects CSMA devices and
	channels.  In the case of a CSMA device and channel pair, notice that the data
	rate is specified by a *channel* ``Attribute`` instead of a device 
	``Attribute``.  This is because a real CSMA network does not allow one to mix,
	for example, 10Base-T and 100Base-T devices on a given channel.  We first set 
	the data rate to 100 megabits per second, and then set the speed-of-light delay
	of the channel to 6560 nano-seconds (arbitrarily chosen as 1 nanosecond per foot
	over a 100 meter segment).  Notice that you can set an ``Attribute`` using 
	its native data type.

Mencionamos anteriormente que abordar�amos um assistente para dispositivos e canais CSMA, as pr�ximas linhas o introduzem. O ``CsmaHelper`` funciona como o ``PointToPointHelper``, mas cria e conecta dispositivos e canais CSMA. No caso de um par de dispositivos e canais CSMA, observe que a taxa de dados � especificada por um atributo do canal, ao inv�s de um atributo do dispositivo. Isto ocorre porque uma rede CSMA real n�o permite que se misture, por exemplo, dispositivos 10Base-T e 100Base-T em um mesmo meio. Primeiro definimos a taxa de dados a 100 megabits por segundo e, em seguida, definimos o atraso do canal como a velocidade da luz, 6560 nano-segundos (escolhido arbitrariamente como 1 nanossegundo por 30,48 cent�metros sobre um segmento de 100 metros). Observe que voc� pode definir um atributo usando
seu tipo de dados nativo.

::

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

..
	Just as we created a ``NetDeviceContainer`` to hold the devices created by
	the ``PointToPointHelper`` we create a ``NetDeviceContainer`` to hold 
	the devices created by our ``CsmaHelper``.  We call the ``Install`` 
	method of the ``CsmaHelper`` to install the devices into the nodes of the
	``csmaNodes NodeContainer``.


Assim como criamos um ``NetDeviceContainer`` para manter os dispositivos criados pelo ``PointToPointHelper``, criamos um ``NetDeviceContainer`` para gerenciar os dispositivos criados pelo nosso ``CsmaHelper``. Chamamos o m�todo ``Install`` do ``CsmaHelper`` para instalar os dispositivos nos n�s do ``csmaNodes NodeContainer``.

..
	We now have our nodes, devices and channels created, but we have no protocol
	stacks present.  Just as in the ``first.cc`` script, we will use the
	``InternetStackHelper`` to install these stacks.

Agora temos os nossos n�s, dispositivos e canais criados, mas n�o temos nenhuma pilha de protocolos presente. Assim como no exemplo ``first.cc``, usaremos o ``InternetStackHelper`` para instalar estas pilhas.

::

  InternetStackHelper stack;
  stack.Install (p2pNodes.Get (0));
  stack.Install (csmaNodes);

..
	Recall that we took one of the nodes from the ``p2pNodes`` container and
	added it to the ``csmaNodes`` container.  Thus we only need to install 
	the stacks on the remaining ``p2pNodes`` node, and all of the nodes in the
	``csmaNodes`` container to cover all of the nodes in the simulation.

Lembre-se que pegamos um dos n�s do cont�iner ``p2pNodes`` e o adicionamos ao cont�iner ``csmaNodes``. Assim, s� precisamos instalar as pilhas nos n�s ``p2pNodes`` restantes e todos os n�s do cont�iner ``csmaNodes`` para abranger todos os n�s na simula��o.

..
	Just as in the ``first.cc`` example script, we are going to use the 
	``Ipv4AddressHelper`` to assign IP addresses to our device interfaces.
	First we use the network 10.1.1.0 to create the two addresses needed for our
	two point-to-point devices.

Assim como no exemplo ``first.cc``, vamos usar o ``Ipv4AddressHelper`` para atribuir endere�os IP para as interfaces de nossos dispositivos. Primeiro, usamos a rede 10.1.1.0 para criar os dois endere�os necess�rios para os dispositivos ponto-a-ponto.

::

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);

..
	Recall that we save the created interfaces in a container to make it easy to
	pull out addressing information later for use in setting up the applications.

Lembre-se que salvamos as interfaces criadas em um cont�iner para tornar mais f�cil a obten��o de informa��es sobre o endere�amento para uso na cria��o dos aplicativos.

..
	We now need to assign IP addresses to our CSMA device interfaces.  The 
	operation works just as it did for the point-to-point case, except we now
	are performing the operation on a container that has a variable number of 
	CSMA devices --- remember we made the number of CSMA devices changeable by 
	command line argument.  The CSMA devices will be associated with IP addresses 
	from network number 10.1.2.0 in this case, as seen below.

Precisamos agora atribuir endere�os IP �s interfaces dos dispositivo CSMA. A opera��o � a mesma realizada para o ponto-a-ponto, exceto que agora estamos realizando a opera��o em um cont�iner que possui um n�mero vari�vel de dispositivos CSMA --- lembre-se que fizemos o n�mero de dispositivos CSMA serem passados na linha de comando. Os dispositivos CSMA ser�o associados com endere�os IP da rede 10.1.2.0, como visto a seguir.

::

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);

..
	Now we have a topology built, but we need applications.  This section is
	going to be fundamentally similar to the applications section of 
	``first.cc`` but we are going to instantiate the server on one of the 
	nodes that has a CSMA device and the client on the node having only a 
	point-to-point device.

Agora a topologia j� est� constru�da, mas precisamos de aplica��es. Esta se��o � muito similar a se��o de aplica��es do exemplo ``first.cc``, mas vamos instanciar o servidor em um dos n�s que tem um dispositivo CSMA e o cliente em um n� que tem apenas um dispositivo ponto-a-ponto.

..
	First, we set up the echo server.  We create a ``UdpEchoServerHelper`` and
	provide a required ``Attribute`` value to the constructor which is the server
	port number.  Recall that this port can be changed later using the 
	``SetAttribute`` method if desired, but we require it to be provided to
	the constructor.

Primeiro, vamos configurar o servidor de eco. Criamos um ``UdpEchoServerHelper`` e fornecemos o atributo obrigat�rio do construtor que � o n�mero da porta. Lembre-se que esta porta pode ser alterada posteriormente, utilizando o m�todo ``SetAttribute``.

::

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

..
	Recall that the ``csmaNodes NodeContainer`` contains one of the 
	nodes created for the point-to-point network and ``nCsma`` "extra" nodes. 
	What we want to get at is the last of the "extra" nodes.  The zeroth entry of
	the ``csmaNodes`` container will be the point-to-point node.  The easy
	way to think of this, then, is if we create one "extra" CSMA node, then it
	will be at index one of the ``csmaNodes`` container.  By induction,
	if we create ``nCsma`` "extra" nodes the last one will be at index 
	``nCsma``.  You see this exhibited in the ``Get`` of the first line of 
	code.

Lembre-se que o ``csmaNodes NodeContainer`` cont�m um dos n�s criados para a rede ponto-a-ponto e os ``nCsma`` n�s "extra". O que queremos � o �ltimo dos n�s "extra". A entrada zero do cont�iner ``csmaNodes`` ser� o n� ponto-a-ponto. O jeito f�cil de pensar nisso �, ao criar um n� CSMA "extra", este ser� o n� um do cont�iner ``csmaNodes``. Por indu��o,
se criarmos ``nCsma`` n�s "extra", o �ltimo ser� o de �ndice ``nCsma``. Isto ocorre no ``Get`` da primeira linha de
c�digo.

..
	The client application is set up exactly as we did in the ``first.cc``
	example script.  Again, we provide required ``Attributes`` to the 
	``UdpEchoClientHelper`` in the constructor (in this case the remote address
	and port).  We tell the client to send packets to the server we just installed
	on the last of the "extra" CSMA nodes.  We install the client on the 
	leftmost point-to-point node seen in the topology illustration.

A aplica��o cliente � criada exatamente como fizemos no exemplo ``first.cc``. Novamente, fornecemos os atributos necess�rios no construtor do ``UdpEchoClientHelper`` (neste caso, o endere�o e porta remotos). Dizemos ao cliente para enviar pacotes para o servidor. Instalamos o cliente no n� ponto-a-ponto mais � esquerda visto na ilustra��o da topologia.

::

  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (p2pNodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

..
	Since we have actually built an internetwork here, we need some form of 
	internetwork routing.  |ns3| provides what we call global routing to
	help you out.  Global routing takes advantage of the fact that the entire 
	internetwork is accessible in the simulation and runs through the all of the
	nodes created for the simulation --- it does the hard work of setting up routing 
	for you without having to configure routers.

Visto que constru�mos uma inter-rede, precisamos de alguma forma de roteamento. O |ns3| fornece o que chamamos de roteamento global para simplificar essa tarefa. O roteamento global tira proveito do fato de que toda a inter-rede � acess�vel na simula��o --- ele realiza a disponibiliza��o do roteamento sem a necessidade de configurar roteadores individualmente.

..
	Basically, what happens is that each node behaves as if it were an OSPF router
	that communicates instantly and magically with all other routers behind the
	scenes.  Each node generates link advertisements and communicates them 
	directly to a global route manager which uses this global information to 
	construct the routing tables for each node.  Setting up this form of routing
	is a one-liner:

Basicamente, o que acontece � que cada n� se comporta como se fosse um roteador OSPF que se comunica instantaneamente e magicamente com todos os outros roteadores transparentemente. Cada n� gera an�ncios de liga��es e os comunica diretamente a um gerente de rota global. O gerente, por sua vez, utiliza esta informa��o para construir as tabelas de roteamento de cada n�. A configura��o deste tipo de roteamento � realizada em uma linha:

::

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

..
	Next we enable pcap tracing.  The first line of code to enable pcap tracing 
	in the point-to-point helper should be familiar to you by now.  The second
	line enables pcap tracing in the CSMA helper and there is an extra parameter
	you haven't encountered yet.

Em seguida, vamos habilitar o rastreamento pcap. A primeira linha de c�digo para habilita o rastreamento pcap
no assistente ponto-a-ponto. A segunda linha habilita o rastreamento pcap no assistente CSMA e h� um par�metro extra que ainda n�o hav�amos usado.

::

  pointToPoint.EnablePcapAll ("second");
  csma.EnablePcap ("second", csmaDevices.Get (1), true);

..
	The CSMA network is a multi-point-to-point network.  This means that there 
	can (and are in this case) multiple endpoints on a shared medium.  Each of 
	these endpoints has a net device associated with it.  There are two basic
	alternatives to gathering trace information from such a network.  One way 
	is to create a trace file for each net device and store only the packets
	that are emitted or consumed by that net device.  Another way is to pick 
	one of the devices and place it in promiscuous mode.  That single device
	then "sniffs" the network for all packets and stores them in a single
	pcap file.  This is how ``tcpdump``, for example, works.  That final 
	parameter tells the CSMA helper whether or not to arrange to capture 
	packets in promiscuous mode.  

A rede CSMA � uma rede multi-ponto-a-ponto. Isto significa que pode (e neste caso, de fato h�) v�rios n�s em um meio compartilhado. Cada um destes n�s tem um dispositivo de rede associado. Existem duas alternativas para a coleta de informa��es de rastreamento em uma rede desse tipo. Uma maneira � criar um arquivo de rastreamento para cada dispositivo de rede e armazenar apenas os pacotes que s�o enviados ou recebidos por esse dispositivo. Outra maneira � escolher
um dos dispositivos e coloc�-lo em modo prom�scuo. Esse dispositivo ent�o "sniffs" a rede por todos os pacotes e os armazena em um �nico arquivo pcap. Isto � como o ``tcpdump`` funciona, por exemplo. O �ltimo par�metro informa ao assistente CSMA se deve ou n�o capturar pacotes em modo prom�scuo.

..
	In this example, we are going to select one of the devices on the CSMA
	network and ask it to perform a promiscuous sniff of the network, thereby
	emulating what ``tcpdump`` would do.  If you were on a Linux machine
	you might do something like ``tcpdump -i eth0`` to get the trace.  
	In this case, we specify the device using ``csmaDevices.Get(1)``, 
	which selects the first device in the container.  Setting the final
	parameter to true enables promiscuous captures.

Neste exemplo, vamos selecionar um dos dispositivos CSMA e pedir para realizar uma captura prom�scua na rede, emulando, assim, o que o ``tcpdump`` faria. Se voc� estivesse em uma m�quina Linux faria algo como ``tcpdump -i eth0`` para obter o rastreamento. Neste caso, especificamos o dispositivo usando ``csmaDevices.Get(1)``, que seleciona o primeiro dispositivo no cont�iner. Configurando o �ltimo par�metro para verdadeiro habilita a captura no modo prom�scuo.

..
	The last section of code just runs and cleans up the simulation just like
	the ``first.cc`` example.

A �ltima se��o do c�digo apenas executa e limpa a simula��o como no exemplo ``first.cc``.

::

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
  }

..
	In order to run this example, copy the ``second.cc`` example script into 
	the scratch directory and use waf to build just as you did with
	the ``first.cc`` example.  If you are in the top-level directory of the
	repository you just type,

Para executar este exemplo, copie o arquivo de ``second.cc`` para o diret�rio "scratch" e use o comando waf para compilar exatamente como voc� fez com ``first.cc``. Se voc� estiver no diret�rio raiz do reposit�rio, digite,

::

  cp examples/tutorial/second.cc scratch/mysecond.cc
  ./waf

..
	Warning:  We use the file ``second.cc`` as one of our regression tests to
	verify that it works exactly as we think it should in order to make your
	tutorial experience a positive one.  This means that an executable named 
	``second`` already exists in the project.  To avoid any confusion
	about what you are executing, please do the renaming to ``mysecond.cc``
	suggested above.

Aten��o: Usamos o arquivo ``second.cc`` como um dos nossos testes de regress�o para verificar se ele funciona exatamente como achamos que deve, a fim de fazer o seu tutorial uma experi�ncia positiva. Isto significa que um execut�vel chamado ``second`` j� existe no projeto. Para evitar qualquer confus�o sobre o que voc� est� executando, renomeie para ``mysecond.cc`` como sugerido acima.

..
	If you are following the tutorial religiously (you are, aren't you) you will
	still have the NS_LOG variable set, so go ahead and clear that variable and
	run the program.

Se voc� est� seguindo o tutorial religiosamente (voc� est�? certo?), ainda vai ter a vari�vel ``NS_LOG`` definida, ent�o limpe a vari�vel e execute o programa.

::

  export NS_LOG=
  ./waf --run scratch/mysecond

..
	Since we have set up the UDP echo applications to log just as we did in 
	``first.cc``, you will see similar output when you run the script.

Uma vez que configuramos aplica��es UDP de eco para rastrear, assim como fizemos em ``first.cc``, voc� ver� uma sa�da semelhante quando executar o c�digo.

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.415s)
  Sent 1024 bytes to 10.1.2.4
  Received 1024 bytes from 10.1.1.1
  Received 1024 bytes from 10.1.2.4

..
	Recall that the first message, "``Sent 1024 bytes to 10.1.2.4``," is the 
	UDP echo client sending a packet to the server.  In this case, the server
	is on a different network (10.1.2.0).  The second message, "``Received 1024 
	bytes from 10.1.1.1``," is from the UDP echo server, generated when it receives
	the echo packet.  The final message, "``Received 1024 bytes from 10.1.2.4``,"
	is from the echo client, indicating that it has received its echo back from
	the server.

Lembre-se que a primeira mensagem, "``Sent 1024 bytes to 10.1.2.4``," � o cliente UDP enviando um pacote de eco para o servidor. Neste caso, o servidor est� em uma rede diferente (10.1.2.0). A segunda mensagem, "``Received 1024 bytes from 10.1.1.1``," � do servidor de eco, gerado quando ele recebe o pacote de eco. A mensagem final, "``Received 1024 bytes from 10.1.2.4``," � do cliente de eco, indicando que ele recebeu seu eco de volta.

..
	If you now go and look in the top level directory, you will find three trace 
	files:

Se voc� olhar no diret�rio raiz, encontrar� tr�s arquivos de rastreamento:

::

  second-0-0.pcap  second-1-0.pcap  second-2-0.pcap

..
	Let's take a moment to look at the naming of these files.  They all have the 
	same form, ``<name>-<node>-<device>.pcap``.  For example, the first file
	in the listing is ``second-0-0.pcap`` which is the pcap trace from node 
	zero, device zero.  This is the point-to-point net device on node zero.  The 
	file ``second-1-0.pcap`` is the pcap trace for device zero on node one,
	also a point-to-point net device; and the file ``second-2-0.pcap`` is the
	pcap trace for device zero on node two.

Vamos gastar um tempo para ver a nomea��o desses arquivos. Todos eles t�m a mesma forma, ``<nome>-<n�>-<dispositivo>.pcap``. Por exemplo, o primeiro arquivo na listagem � ``second-0-0.pcap `` que � o rastreamento pcap do n�
zero, dispositivo zero. Este � o dispositivo na rede ponto-a-ponto no n� zero. O arquivo ``second-1-0.pcap`` � o rastreamento pcap para o dispositivo zero no n� um, tamb�m um dispositivo ponto-a-ponto. O arquivo ``second-2-0.pcap`` � o rastreamento pcap para o dispositivo zero no n� dois.

..
	If you refer back to the topology illustration at the start of the section, 
	you will see that node zero is the leftmost node of the point-to-point link
	and node one is the node that has both a point-to-point device and a CSMA 
	device.  You will see that node two is the first "extra" node on the CSMA
	network and its device zero was selected as the device to capture the 
	promiscuous-mode trace.

Se remetermos para a ilustra��o da topologia no in�cio da se��o, vai ver que o n� zero � o n� mais � esquerda da liga��o ponto-a-ponto e o n� um � o n� que tem tanto um dispositivo ponto-a-ponto quanto um CSMA. Observamos que o n� dois � o primeiro n� "extra" na rede CSMA e seu dispositivo zero foi selecionado como o dispositivo para capturar pacotes de modo prom�scuo.

..
	Now, let's follow the echo packet through the internetwork.  First, do a 
	tcpdump of the trace file for the leftmost point-to-point node --- node zero.

Agora, vamos seguir o pacote de eco atrav�s das redes. Primeiro, fa�a um tcpdump do arquivo de rastreamento para o n� ponto-a-ponto mais � esquerda --- n� zero.

::

  tcpdump -nn -tt -r second-0-0.pcap

..
	You should see the contents of the pcap file displayed:

Teremos o conte�do do arquivo pcap:

::

  reading from file second-0-0.pcap, link-type PPP (PPP)
  2.000000 IP 10.1.1.1.49153 > 10.1.2.4.9: UDP, length 1024
  2.007602 IP 10.1.2.4.9 > 10.1.1.1.49153: UDP, length 1024

..
	The first line of the dump indicates that the link type is PPP (point-to-point)
	which we expect.  You then see the echo packet leaving node zero via the 
	device associated with IP address 10.1.1.1 headed for IP address
	10.1.2.4 (the rightmost CSMA node).  This packet will move over the 
	point-to-point link and be received by the point-to-point net device on node 
	one.  Let's take a look:

A primeira linha do despejo (*dump*) indica que o tipo da liga��o � PPP (ponto-a-ponto). Voc� ent�o v� o pacote de eco deixando o n� zero atrav�s do dispositivo associado com o endere�o IP 10.1.1.1, destinado para o endere�o IP 10.1.2.4 (o n� CSMA mais � direita). Este pacote vai passar pela liga��o ponto-a-ponto e ser� recebido pelo dispositivo ponto-a-ponto no n� um. Vamos dar uma olhada:

::

  tcpdump -nn -tt -r second-1-0.pcap

..
	You should now see the pcap trace output of the other side of the point-to-point
	link:

Observamos agora a sa�da de rastreamento pcap do outro lado da liga��o ponto-a-ponto:

::

  reading from file second-1-0.pcap, link-type PPP (PPP)
  2.003686 IP 10.1.1.1.49153 > 10.1.2.4.9: UDP, length 1024
  2.003915 IP 10.1.2.4.9 > 10.1.1.1.49153: UDP, length 1024

..
	Here we see that the link type is also PPP as we would expect.  You see the
	packet from IP address 10.1.1.1 (that was sent at 2.000000 seconds) headed 
	toward IP address 10.1.2.4 appear on this interface.  Now, internally to this 
	node, the packet will be forwarded to the CSMA interface and we should see it 
	pop out on that device headed for its ultimate destination.  

Aqui vemos que o tipo de liga��o tamb�m � PPP. Vemos nesta interface o pacote do endere�o IP 10.1.1.1 (que foi enviado a 2,000000 segundos) endere�ado ao IP 10.1.2.4. Agora, internamente a este n�, o pacote ser� enviado para a interface CSMA e devemos v�-lo saindo nesse dispositivo a caminho de seu destino final.

..
	Remember that we selected node 2 as the promiscuous sniffer node for the CSMA
	network so let's then look at second-2-0.pcap and see if its there.

Lembre-se que selecionamos o n� 2 como o "sniffer" prom�scuo para a rede CSMA, por isso, vamos analisar o arquivo second-2-0.pcap.

::

  tcpdump -nn -tt -r second-2-0.pcap

..
	You should now see the promiscuous dump of node two, device zero:

Temos agora o despejo do n� dois, dispositivo zero:

::

  reading from file second-2-0.pcap, link-type EN10MB (Ethernet)
  2.003696 arp who-has 10.1.2.4 (ff:ff:ff:ff:ff:ff) tell 10.1.2.1
  2.003707 arp reply 10.1.2.4 is-at 00:00:00:00:00:06
  2.003801 IP 10.1.1.1.49153 > 10.1.2.4.9: UDP, length 1024
  2.003811 arp who-has 10.1.2.1 (ff:ff:ff:ff:ff:ff) tell 10.1.2.4
  2.003822 arp reply 10.1.2.1 is-at 00:00:00:00:00:03
  2.003915 IP 10.1.2.4.9 > 10.1.1.1.49153: UDP, length 1024

..
	As you can see, the link type is now "Ethernet".  Something new has appeared,
	though.  The bus network needs ``ARP``, the Address Resolution Protocol.
	Node one knows it needs to send the packet to IP address 10.1.2.4, but it
	doesn't know the MAC address of the corresponding node.  It broadcasts on the
	CSMA network (ff:ff:ff:ff:ff:ff) asking for the device that has IP address
	10.1.2.4.  In this case, the rightmost node replies saying it is at MAC address
	00:00:00:00:00:06.  Note that node two is not directly involved in this 
	exchange, but is sniffing the network and reporting all of the traffic it sees.

Observamos que o tipo de liga��o agora � "Ethernet". Algo novo apareceu. A rede em barramento necessicita do ``ARP``, o "Address Resolution Protocol". O n� um sabe que precisa enviar o pacote para o endere�o IP 10.1.2.4, mas
n�o sabe o endere�o MAC do n� correspondente. Ele transmite na rede CSMA (ff:ff:ff:ff:ff:ff) pedindo ao dispositivo que tem o endere�o IP 10.1.2.4. Neste caso, o n� mais � direita responde dizendo que est� no endere�o MAC 00:00:00:00:00:06. Note que o n� dois n�o est� diretamente envolvido nesta troca, mas est� capturando todo o tr�fego da rede.

..
	This exchange is seen in the following lines,

Esta troca � vista nas seguintes linhas,

::

  2.003696 arp who-has 10.1.2.4 (ff:ff:ff:ff:ff:ff) tell 10.1.2.1
  2.003707 arp reply 10.1.2.4 is-at 00:00:00:00:00:06

..
	Then node one, device one goes ahead and sends the echo packet to the UDP echo
	server at IP address 10.1.2.4. 

Em seguida, o n� um, dispositivo um, envia o pacote de eco UDP para o servidor no endere�o IP 10.1.2.4.

::

  2.003801 IP 10.1.1.1.49153 > 10.1.2.4.9: UDP, length 1024

..
	The server receives the echo request and turns the packet around trying to send
	it back to the source.  The server knows that this address is on another network
	that it reaches via IP address 10.1.2.1.  This is because we initialized global
	routing and it has figured all of this out for us.  But, the echo server node
	doesn't know the MAC address of the first CSMA node, so it has to ARP for it
	just like the first CSMA node had to do.

O servidor recebe a solicita��o de eco e tenta enviar de volta para a origem. O servidor sabe que este endere�o est� em outra rede que chega atrav�s do endere�o IP 10.1.2.1. Isto porque inicializamos o roteamento global. Entretanto, o n� servidor de eco n�o sabe o endere�o MAC do primeiro n� CSMA, por isso tem que solicitar via ARP assim como o primeiro n� CSMA teve que fazer.

::

  2.003811 arp who-has 10.1.2.1 (ff:ff:ff:ff:ff:ff) tell 10.1.2.4
  2.003822 arp reply 10.1.2.1 is-at 00:00:00:00:00:03

..
	The server then sends the echo back to the forwarding node.

O servidor ent�o envia o eco de volta ao n� de encaminhamento.

::

  2.003915 IP 10.1.2.4.9 > 10.1.1.1.49153: UDP, length 1024

..
	Looking back at the rightmost node of the point-to-point link,

Analisando o n� mais � direita da liga��o ponto-a-ponto,

::

  tcpdump -nn -tt -r second-1-0.pcap

..
	You can now see the echoed packet coming back onto the point-to-point link as
	the last line of the trace dump.

Observamos o pacote que ecoou vindo de volta para a linga��o ponto-a-ponto na �ltima linha do despejo.

::

  reading from file second-1-0.pcap, link-type PPP (PPP)
  2.003686 IP 10.1.1.1.49153 > 10.1.2.4.9: UDP, length 1024
  2.003915 IP 10.1.2.4.9 > 10.1.1.1.49153: UDP, length 1024

..
	Lastly, you can look back at the node that originated the echo

Finalmente, analisando o n� que originou o eco,

::

  tcpdump -nn -tt -r second-0-0.pcap

..
	and see that the echoed packet arrives back at the source at 2.007602 seconds,

vericamos que o pacote eco chega de volta na fonte em 2,007602 segundos

::

  reading from file second-0-0.pcap, link-type PPP (PPP)
  2.000000 IP 10.1.1.1.49153 > 10.1.2.4.9: UDP, length 1024
  2.007602 IP 10.1.2.4.9 > 10.1.1.1.49153: UDP, length 1024

..
	Finally, recall that we added the ability to control the number of CSMA devices
	in the simulation by command line argument.  You can change this argument in
	the same way as when we looked at changing the number of packets echoed in the
	``first.cc`` example.  Try running the program with the number of "extra" 
	devices set to four:

Finalmente, lembre-se que adicionamos a habilidade de controlar o n�mero de dispositivos CSMA na simula��o por meio da linha de comando. Voc� pode alterar esse argumento da mesma forma como quando alteramos o n�mero de pacotes de eco no exemplo ``first.cc``. Tente executar o programa com o n�mero de dispositivos "extra" em quatro:

::

  ./waf --run "scratch/mysecond --nCsma=4"

..
	You should now see,

Voc� deve ver agora:

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.405s)
  Sent 1024 bytes to 10.1.2.5
  Received 1024 bytes from 10.1.1.1
  Received 1024 bytes from 10.1.2.5

..
	Notice that the echo server has now been relocated to the last of the CSMA
	nodes, which is 10.1.2.5 instead of the default case, 10.1.2.4.

Observe que o servidor de eco foi agora transferido para o �ltimo dos n�s CSMA, que � 10.1.2.5 em vez de o caso padr�o, 10.1.2.4.

..
	It is possible that you may not be satisfied with a trace file generated by
	a bystander in the CSMA network.  You may really want to get a trace from
	a single device and you may not be interested in any other traffic on the 
	network.  You can do this fairly easily.

� poss�vel que voc� n�o se satisfa�a com um arquivo de rastreamento gerado por um espectador na rede CSMA. Voc� pode querer obter o rastreamento de um �nico dispositivo e pode n�o estar interessado em qualquer outro tr�fego na rede. Voc� pode fazer isso facilmente.

..
	Let's take a look at ``scratch/mysecond.cc`` and add that code enabling us
	to be more specific.  ``ns-3`` helpers provide methods that take a node
	number and device number as parameters.  Go ahead and replace the 
	``EnablePcap`` calls with the calls below.

Vamos dar uma olhada em ``scratch/mysecond.cc`` e adicionar o c�digo permitindo-nos ser mais espec�ficos. Os assistentes do ``ns-3`` fornecem m�todos que recebem um n�mero de n� e um n�mero de dispositivo como par�metros. Substitua as chamadas ``EnablePcap`` pelas seguites:

::

  pointToPoint.EnablePcap ("second", p2pNodes.Get (0)->GetId (), 0);
  csma.EnablePcap ("second", csmaNodes.Get (nCsma)->GetId (), 0, false);
  csma.EnablePcap ("second", csmaNodes.Get (nCsma-1)->GetId (), 0, false);

..
	We know that we want to create a pcap file with the base name "second" and
	we also know that the device of interest in both cases is going to be zero,
	so those parameters are not really interesting.

Sabemos que queremos criar um arquivo pcap com o nome base "second" e sabemos tamb�m que o dispositivo de interesse em ambos os casos vai ser o zero, ent�o estes par�metros n�o s�o interessantes.

..
	In order to get the node number, you have two choices:  first, nodes are 
	numbered in a monotonically increasing fashion starting from zero in the 
	order in which you created them.  One way to get a node number is to figure 
	this number out "manually" by contemplating the order of node creation.  
	If you take a look at the network topology illustration at the beginning of 
	the file, we did this for you and you can see that the last CSMA node is 
	going to be node number ``nCsma + 1``.  This approach can become 
	annoyingly difficult in larger simulations.  


A fim de obter o n�mero do n�, voc� tem duas op��es: primeiro, os n�s s�o numerados de forma crescente a partir de zero na ordem em que voc� os cria. Uma maneira de obter um n�mero de n� � descobrir este n�mero "manualmente" atrav�s da ordem de cria��o. Se olharmos na ilustra��o da topologia da rede no in�cio do arquivo, perceberemos que foi o que fizemos. Isto pode ser visto porque o �ltimo n� CSMA vai ser o de n�mero ``nCsma + 1``. Esta abordagem pode tornar-se muito dif�cil em simula��es maiores.

..
	An alternate way, which we use here, is to realize that the
	``NodeContainers`` contain pointers to |ns3| ``Node`` Objects.
	The ``Node`` Object has a method called ``GetId`` which will return that
	node's ID, which is the node number we seek.  Let's go take a look at the 
	Doxygen for the ``Node`` and locate that method, which is further down in 
	the |ns3| core code than we've seen so far; but sometimes you have to
	search diligently for useful things.

Uma maneira alternativa, que usamos aqui, � perceber que os ``NodeContainers`` cont�m ponteiros para objetos ``Node`` do |ns3|. O objeto ``Node`` tem um m�todo chamado ``GetId`` que retornar� o ID do n�, que � o n�mero do n� que buscamos. Vamos dar uma olhada por ``Node`` no Doxygen e localizar esse m�todo, que est� mais abaixo no c�digo do n�cleo do que vimos at� agora. �s vezes voc� tem que procurar diligentemente por coisas �teis.

..
	Go to the Doxygen documentation for your release (recall that you can find it
	on the project web site).  You can get to the ``Node`` documentation by
	looking through at the "Classes" tab and scrolling down the "Class List" 
	until you find ``ns3::Node``.  Select ``ns3::Node`` and you will be taken
	to the documentation for the ``Node`` class.  If you now scroll down to the
	``GetId`` method and select it, you will be taken to the detailed 
	documentation for the method.  Using the ``GetId`` method can make 
	determining node numbers much easier in complex topologies.

Consulte a documenta��o em Doxygen para a sua distribui��o do ns (lembre-se que voc� pode encontr�-la no site do projeto). Voc� pode chegar a documenta��o sobre o objeto ``Node`` procurando pela guia "Classes", at� encontrar ``ns3::Node`` na "Class List". Selecione ``ns3::Node`` e voc� ser� levado a documenta��o para a classe ``Node``. Se voc� ir at� o m�todo ``GetId`` e selecion�-lo, ser� levado a documenta��o detalhada do m�todo. Usar o m�todo ``getId`` pode tornar muito mais f�cil determinar os n�meros dos n�s em topologias complexas.

..
	Let's clear the old trace files out of the top-level directory to avoid confusion
	about what is going on,

Vamos limpar os arquivos de rastreamento antigos do diret�rio raiz para evitar confus�o sobre o que est� acontecendo,

::

  rm *.pcap
  rm *.tr

..
	If you build the new script and run the simulation setting ``nCsma`` to 100,

Se voc� compilar o novo c�digo e executar a simula��o com ``nCsma`` em 100,

::

  ./waf --run "scratch/mysecond --nCsma=100"

..
	you will see the following output:

voc� vai observar a seguinte sa�da:

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.407s)
  Sent 1024 bytes to 10.1.2.101
  Received 1024 bytes from 10.1.1.1
  Received 1024 bytes from 10.1.2.101

..
	Note that the echo server is now located at 10.1.2.101 which corresponds to
	having 100 "extra" CSMA nodes with the echo server on the last one.  If you
	list the pcap files in the top level directory you will see,

Observe que o servidor de eco est� agora em 10.1.2.101, que corresponde a ter 100 n�s CSMA "extras" com o servidor de eco no �ltimo. Se voc� listar os arquivos pcap no diret�rio principal, voc� ver�,

::

  second-0-0.pcap  second-100-0.pcap  second-101-0.pcap

..
	The trace file ``second-0-0.pcap`` is the "leftmost" point-to-point device
	which is the echo packet source.  The file ``second-101-0.pcap`` corresponds
	to the rightmost CSMA device which is where the echo server resides.  You may 
	have noticed that the final parameter on the call to enable pcap tracing on the 
	echo server node was false.  This means that the trace gathered on that node
	was in non-promiscuous mode.

O arquivo de rastreamento ``second-0-0.pcap`` � o dispositivo ponto-a-ponto "mais � esquerda" que � a origem do pacote de eco. O arquivo ``second-101-0.pcap`` corresponde ao dispositivo CSMA mais � direita que � onde o servidor de eco reside. O leitor deve ter notado que o par�metro final na chamada para ativar o rastreamento no n� servidor era falso. Isto significa que o rastreamento nesse n� estava em modo n�o-prom�scuo.

..
	To illustrate the difference between promiscuous and non-promiscuous traces, we
	also requested a non-promiscuous trace for the next-to-last node.  Go ahead and
	take a look at the ``tcpdump`` for ``second-100-0.pcap``.

Para ilustrar a diferen�a entre o rastreamento prom�scuo e o n�o prom�scuo, tamb�m solicitamos um rastreamento n�o-prom�scuo para o n� vizinho ao �ltimo. D� uma olhada no ``tcpdump`` para ``second-100-0.pcap``.

::

  tcpdump -nn -tt -r second-100-0.pcap

..
	You can now see that node 100 is really a bystander in the echo exchange.  The
	only packets that it receives are the ARP requests which are broadcast to the
	entire CSMA network.

Agora observamos que o n� 100 � realmente um espectador na troca de eco. Os �nicos pacotes que ele recebe s�o os pedidos ARP que s�o transmitidos para a rede CSMA inteira (em broadcast).

::

  reading from file second-100-0.pcap, link-type EN10MB (Ethernet)
  2.003696 arp who-has 10.1.2.101 (ff:ff:ff:ff:ff:ff) tell 10.1.2.1
  2.003811 arp who-has 10.1.2.1 (ff:ff:ff:ff:ff:ff) tell 10.1.2.101

..
	Now take a look at the ``tcpdump`` for ``second-101-0.pcap``.

Agora, d� uma olhada no ``tcpdump`` para ``second-101-0.pcap``.

::

  tcpdump -nn -tt -r second-101-0.pcap

..
	You can now see that node 101 is really the participant in the echo exchange.

Observamos que o n� 101 � realmente o participante na troca de eco.

::

  reading from file second-101-0.pcap, link-type EN10MB (Ethernet)
  2.003696 arp who-has 10.1.2.101 (ff:ff:ff:ff:ff:ff) tell 10.1.2.1
  2.003696 arp reply 10.1.2.101 is-at 00:00:00:00:00:67
  2.003801 IP 10.1.1.1.49153 > 10.1.2.101.9: UDP, length 1024
  2.003801 arp who-has 10.1.2.1 (ff:ff:ff:ff:ff:ff) tell 10.1.2.101
  2.003822 arp reply 10.1.2.1 is-at 00:00:00:00:00:03
  2.003822 IP 10.1.2.101.9 > 10.1.1.1.49153: UDP, length 1024


.. Models, Attributes and Reality

Modelos, atributos e a ``sua`` realidade
*****************************************

..
	This is a convenient place to make a small excursion and make an important
	point.  It may or may not be obvious to you, but whenever one is using a 
	simulation, it is important to understand exactly what is being modeled and
	what is not.  It is tempting, for example, to think of the CSMA devices 
	and channels used in the previous section as if they were real Ethernet 
	devices; and to expect a simulation result to directly reflect what will 
	happen in a real Ethernet.  This is not the case.  

Este � um local conveniente para fazer uma pequena excurs�o e fazer uma observa��o importante. Pode ou n�o ser �bvio para o leitor, mas sempre que algu�m est� usando uma simula��o, � importante entender exatamente o que est� sendo modelado e o que n�o est�. � tentador, por exemplo, pensar nos dispositivos e canais CSMA utilizados na se��o anterior como se fossem dispositivos Ethernet reais, e esperar um resultado que vai refletir diretamente o que aconteceria em uma Ethernet real. Este n�o � o caso.

..
	A model is, by definition, an abstraction of reality.  It is ultimately the 
	responsibility of the simulation script author to determine the so-called
	"range of accuracy" and "domain of applicability" of the simulation as
	a whole, and therefore its constituent parts.

Um modelo �, por defini��o, uma abstra��o da realidade. Em �ltima an�lise, � responsabilidade do autor do c�digo da simula��o determinar a chamada "faixa de precis�o" e "dom�nio de aplicabilidade" da simula��o como um todo e, portanto, suas partes constituintes.

..
	In some cases, like ``Csma``, it can be fairly easy to determine what is 
	*not* modeled.  By reading the model description (``csma.h``) you 
	can find that there is no collision detection in the CSMA model and decide
	on how applicable its use will be in your simulation or what caveats you 
	may want to include with your results.  In other cases, it can be quite easy
	to configure behaviors that might not agree with any reality you can go out
	and buy.  It will prove worthwhile to spend some time investigating a few
	such instances, and how easily you can swerve outside the bounds of reality
	in your simulations.

Em alguns casos, como no ``Csma``, pode ser bastante f�cil de determinar o que � *n�o* modelado. Ao ler a descri��o do fonte (``csma.h``) voc� descobrir� que n�o h� detec��o de colis�o e poder� decidir sobre qu�o aplic�vel a sua utiliza��o ser� em sua simula��o ou quais ressalvas pode querer incluir em seus resultados. Em outros casos, pode ser razoavelmente f�cil configurar comportamentos que podem n�o existir em qualquer equipamento real que possa ser comprado por a�. Vale a pena gastar algum tempo investigando tais casos e qu�o facilmente pode-se desviar para fora dos limites da realidade em suas simula��es.

..
	As you have seen, |ns3| provides ``Attributes`` which a user
	can easily set to change model behavior.  Consider two of the ``Attributes``
	of the ``CsmaNetDevice``:  ``Mtu`` and ``EncapsulationMode``.  
	The ``Mtu`` attribute indicates the Maximum Transmission Unit to the 
	device.  This is the size of the largest Protocol Data Unit (PDU) that the
	device can send.  

Como voc� viu, o |ns3| fornece atributos que um usu�rio pode facilmente configurar para mudar o comportamento do modelo. Considere dois dos ``atributos`` do ``CsmaNetDevice``: ``Mtu`` e ``EncapsulationMode``. O atributo ``Mtu`` indica a unidade m�xima de transmiss�o para o dispositivo. Este � o tamanho m�ximo do Protocol Data Unit (PDU) que o dispositivo pode enviar.

..
	The MTU defaults to 1500 bytes in the ``CsmaNetDevice``.  This default
	corresponds to a number found in RFC 894, "A Standard for the Transmission
	of IP Datagrams over Ethernet Networks."  The number is actually derived 
	from the maximum packet size for 10Base5 (full-spec Ethernet) networks -- 
	1518 bytes.  If you subtract the DIX encapsulation overhead for Ethernet 
	packets (18 bytes) you will end up with a maximum possible data size (MTU) 
	of 1500 bytes.  One can also find that the ``MTU`` for IEEE 802.3 networks
	is 1492 bytes.  This is because LLC/SNAP encapsulation adds an extra eight 
	bytes of overhead to the packet.  In both cases, the underlying hardware can
	only send 1518 bytes, but the data size is different.

O valor padr�o para o MTU � 1500 bytes na ``CsmaNetDevice``. Este padr�o corresponde a um n�mero encontrado na RFC 894, "Um padr�o para a transmiss�o de datagramas IP sobre redes Ethernet". O n�mero � derivado do tamanho m�ximo do pacote para redes 10Base5 (full-spec Ethernet) -- 1518 bytes. Se voc� subtrair a sobrecarga de encapsulamento DIX para pacotes Ethernet (18 bytes), voc� vai acabar com o tamanho m�ximo poss�vel de dados (MTU) de 1500 bytes. Pode-se tamb�m encontrar que o ``MTU`` para redes IEEE 802.3 � 1492 bytes. Isto � porque o encapsulamento LLC/SNAP acrescenta oito bytes extra de sobrecarga para o pacote. Em ambos os casos, o hardware subjacente pode enviar apenas 1518 bytes, mas o tamanho dos dados � diferente.

..
	In order to set the encapsulation mode, the ``CsmaNetDevice`` provides
	an ``Attribute`` called ``EncapsulationMode`` which can take on the 
	values ``Dix`` or ``Llc``.  These correspond to Ethernet and LLC/SNAP
	framing respectively.

A fim de definir o modo de encapsulamento, o ``CsmaNetDevice`` fornece um atributo chamado ``EncapsulationMode`` que pode assumir os valores ``Dix`` ou ``Llc``. Estes correspondem ao enquadramento Ethernet e LLC/SNAP, respectivamente.

..
	If one leaves the ``Mtu`` at 1500 bytes and changes the encapsulation mode
	to ``Llc``, the result will be a network that encapsulates 1500 byte PDUs
	with LLC/SNAP framing resulting in packets of 1526 bytes, which would be 
	illegal in many networks, since they can transmit a maximum of 1518 bytes per
	packet.  This would most likely result in a simulation that quite subtly does
	not reflect the reality you might be expecting.

Se deixarmos o ``Mtu`` com 1500 bytes e mudarmos o encapsulamento para ``Llc``, o resultado ser� uma rede que encapsula PDUs de 1500 bytes com enquadramento LLC/SNAP, resultando em pacotes de 1526 bytes, o que seria ilegal em muitas redes, pois elas podem transmitir um m�ximo de 1518 bytes por pacote. Isto resultaria em uma simula��o que, de maneira sutil, n�o refletiria a realidade que voc� possa estar esperando.

..
	Just to complicate the picture, there exist jumbo frames (1500 < MTU <= 9000 bytes)
	and super-jumbo (MTU > 9000 bytes) frames that are not officially sanctioned
	by IEEE but are available in some high-speed (Gigabit) networks and NICs.  One
	could leave the encapsulation mode set to ``Dix``, and set the ``Mtu``
	``Attribute`` on a ``CsmaNetDevice`` to 64000 bytes -- even though an 
	associated ``CsmaChannel DataRate`` was set at 10 megabits per second.  
	This would essentially model an Ethernet switch made out of vampire-tapped
	1980s-style 10Base5 networks that support super-jumbo datagrams.  This is
	certainly not something that was ever made, nor is likely to ever be made,
	but it is quite easy for you to configure.

S� para complicar o cen�rio, existem quadros jumbo (1500 < MTU <= 9000 bytes) e quadros super-jumbo (MTU > 9000 bytes) que n�o s�o oficialmente especificados pela IEEE, mas est�o dispon�veis em alguns equipamentos de redes de alta velocidade (Gigabit) e NICs. Algu�m poderia deixar o encapsulamento em ``Dix``, e definir o atributo ``Mtu`` em um dispositivo ``CsmaNetDevice`` para 64000 bytes -- mesmo que o atributo ``CsmaChannel DataRate`` associado esteja fixado em 10 megabits por segundo. Isto modelaria um equipamento Ethernet 10Base5, dos anos 80, suportando quadros super-jumbo. Isto � certamente algo que nunca foi feito, nem � prov�vel que alguma vez seja feito, mas � bastante f�cil de configurar.

..
	In the previous example, you used the command line to create a simulation that
	had 100 ``Csma`` nodes.  You could have just as easily created a simulation
	with 500 nodes.  If you were actually modeling that 10Base5 vampire-tap network,
	the maximum length of a full-spec Ethernet cable is 500 meters, with a minimum 
	tap spacing of 2.5 meters.  That means there could only be 200 taps on a 
	real network.  You could have quite easily built an illegal network in that
	way as well.  This may or may not result in a meaningful simulation depending
	on what you are trying to model.

No exemplo anterior, usamos a linha de comando para criar uma simula��o que tinha 100 n�s ``CSMA``. Poder�amos ter facilmente criado uma simula��o com 500 n�s. Se fossemos de fato modelar uma rede com conectores de press�o `(vampire-taps)` 10Base5, o comprimento m�ximo do cabo Ethernet � 500 metros, com um espa�amento m�nimo entre conectores de 2,5 metros. Isso significa que s� poderia haver 200 m�quinas em uma rede real. Poder�amos facilmente construir uma rede ilegal desta maneira tamb�m. Isto pode ou n�o resultar em uma simula��o significativa dependendo do que voc� est� tentando modelar.

..
	Similar situations can occur in many places in |ns3| and in any
	simulator.  For example, you may be able to position nodes in such a way that
	they occupy the same space at the same time, or you may be able to configure
	amplifiers or noise levels that violate the basic laws of physics.

Situa��es similares podem ocorrer em muitos momentos no |ns3|, assim como em qualquer simulador. Por exemplo, voc� pode posicionar os n�s de tal forma que ocupem o mesmo espa�o ao mesmo tempo ou voc� pode ser capaz de configurar amplificadores ou n�veis de ru�do que violam as leis b�sicas da f�sica.

..
	|ns3| generally favors flexibility, and many models will allow freely
	setting ``Attributes`` without trying to enforce any arbitrary consistency
	or particular underlying spec.

O |ns3| geralmente favorece a flexibilidade, e muitos modelos permitir�o a configura��o de atributos sem impor qualquer consist�ncia ou especifica��o especial subjacente.

..
	The thing to take home from this is that |ns3| is going to provide a
	super-flexible base for you to experiment with.  It is up to you to understand
	what you are asking the system to do and to  make sure that the simulations you
	create have some meaning and some connection with a reality defined by you.


Em resumo, o importante � que o |ns3| vai fornecer uma base super flex�vel para experimenta��es. Depende de voc� entender o que est� requisitando ao sistema e se certificar de que as simula��es tem algum significado e alguma liga��o com a sua realidade.

.. 
	Building a Wireless Network Topology

Construindo uma rede sem fio
************************************

..
	In this section we are going to further expand our knowledge of |ns3|
	network devices and channels to cover an example of a wireless network.  
	|ns3| provides a set of 802.11 models that attempt to provide an 
	accurate MAC-level implementation of the 802.11 specification and a 
	"not-so-slow" PHY-level model of the 802.11a specification.

Nesta se��o, vamos expandir ainda mais nosso conhecimento sobre dispositivos e canais do |ns3| para cobrir um exemplo de uma rede sem fio. O |ns3| fornece um conjunto de modelos 802.11 que tentam fornecer uma implementa��o precisa a n�vel MAC da especifica��o 802.11 e uma implementa��o "n�o-t�o-lenta" a n�vel PHY da especifica��o 802.11a.

..
	Just as we have seen both point-to-point and CSMA topology helper objects when
	constructing point-to-point topologies, we will see equivalent ``Wifi``
	topology helpers in this section.  The appearance and operation of these 
	helpers should look quite familiar to you.

Assim como vimos assistentes de topologia (objetos) ponto-a-ponto e CSMA quando da constru��o destes modelos, veremos assistentes ``Wifi`` similares nesta se��o. O formato e o funcionamento destes assistentes devem parecer bastante familiar ao leitor.

..
	We provide an example script in our ``examples/tutorial`` directory.  This script
	builds on the ``second.cc`` script and adds a Wifi network.  Go ahead and
	open ``examples/tutorial/third.cc`` in your favorite editor.  You will have already
	seen enough |ns3| code to understand most of what is going on in 
	this example, but there are a few new things, so we will go over the entire 
	script and examine some of the output.

Fornecemos um exemplo no diret�rio ``examples/tutorial``. Este arquivo baseia-se no c�digo presente em ``second.cc`` e adiciona uma rede Wifi a ele. V� em frente e abra ``examples/tutorial/third.cc`` em seu editor favorito. Voc� j� deve ter visto c�digo |ns3| suficiente para entender a maior parte do que est� acontecendo neste exemplo, existem algumas coisas novas, mas vamos passar por todo o c�digo e examinar alguns dos resultados.

..
	Just as in the ``second.cc`` example (and in all |ns3| examples)
	the file begins with an emacs mode line and some GPL boilerplate.

Assim como no exemplo ``second.cc`` (e em todos os exemplos ns-3), o arquivo
come�a com uma linha de modo emacs e algumas linhas do padr�o GPL.

..
	Take a look at the ASCII art (reproduced below) that shows the default network
	topology constructed in the example.  You can see that we are going to 
	further extend our example by hanging a wireless network off of the left side.
	Notice that this is a default network topology since you can actually vary the
	number of nodes created on the wired and wireless networks.  Just as in the 
	``second.cc`` script case, if you change ``nCsma``, it will give you a 
	number of "extra" CSMA nodes.  Similarly, you can set ``nWifi`` to 
	control how many ``STA`` (station) nodes are created in the simulation.
	There will always be one ``AP`` (access point) node on the wireless 
	network.  By default there are three "extra" CSMA nodes and three wireless 
	``STA`` nodes.

D� uma olhada na arte ASCII (reproduzida abaixo) que mostra topologia de rede constru�da no exemplo. Voc� pode ver que estamos ampliando ainda mais nosso exemplo agregando uma rede sem fio do lado esquerdo. Observe que esta � uma topologia de rede padr�o, pois voc� pode variar o n�mero de n�s criados nas redes com fio e sem fio. Assim como no exemplo ``second.cc``, se voc� mudar ``nCsma``, ele lhe dar� um n�mero "extra" de n�s CSMA. Da mesma forma, voc� pode definir ``nWifi`` para controlar quantos n�s (esta��es) ``STA`` ser�o criados na simula��o. Sempre haver� um n� ``AP`` (*access point*) na rede sem fio. Por padr�o, existem tr�s n�s "extra" no CSMA e tr�s n�s sem fio ``STA``.

..
	The code begins by loading module include files just as was done in the
	``second.cc`` example.  There are a couple of new includes corresponding
	to the Wifi module and the mobility module which we will discuss below.

O c�digo come�a pelo carregamento de m�dulos atrav�s da inclus�o dos arquivos, assim como no exemplo ``second.cc``. H� algumas novas inclus�es correspondentes ao m�dulo Wifi e ao m�dulo de mobilidade que discutiremos a seguir.

::

#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"

..
	The network topology illustration follows:

A ilustra��o da topologia da rede � a seguinte:

::

  // Default Network Topology
  //
  //   Wifi 10.1.3.0
  //                 AP
  //  *    *    *    *
  //  |    |    |    |    10.1.1.0
  // n5   n6   n7   n0 -------------- n1   n2   n3   n4
  //                   point-to-point  |    |    |    |
  //                                   ================
  //                                     LAN 10.1.2.0

..
	You can see that we are adding a new network device to the node on the left 
	side of the point-to-point link that becomes the access point for the wireless
	network.  A number of wireless STA nodes are created to fill out the new 
	10.1.3.0 network as shown on the left side of the illustration.

Observamos que estamos acrescentando um novo dispositivo de rede ao n� � esquerda da liga��o ponto-a-ponto que se torna o ponto de acesso da rede sem fios. Alguns n�s STA sem fio s�o criados para preencher a nova rede 10.1.3.0, como mostrado no lado esquerdo da ilustra��o.

..
	After the illustration, the ``ns-3`` namespace is ``used`` and a logging
	component is defined.  This should all be quite familiar by now.

Ap�s a ilustra��o, o namespace ns-3 � `usado` e um componente de registro � definido. 

::

  using namespace ns3;
  
  NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");

..
	The main program begins just like ``second.cc`` by adding some command line
	parameters for enabling or disabling logging components and for changing the 
	number of devices created.

O programa principal come�a exatamente como em ``second.cc``, adicionando par�metros de linha de comando para habilitar ou desabilitar componentes de registro e para alterar o n�mero de dispositivos criados.

::

  bool verbose = true;
  uint32_t nCsma = 3;
  uint32_t nWifi = 3;

  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
  cmd.AddValue ("nWifi", "Number of wifi STA devices", nWifi);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc,argv);

  if (verbose)
    {
      LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

..
	Just as in all of the previous examples, the next step is to create two nodes
	that we will connect via the point-to-point link.  

Assim como em todos os exemplos anteriores, o pr�ximo passo � a cria��o de dois n�s
que ir�o se ligar atrav�s da liga��o ponto-a-ponto.

::

  NodeContainer p2pNodes;
  p2pNodes.Create (2);

..
	Next, we see an old friend.  We instantiate a ``PointToPointHelper`` and 
	set the associated default ``Attributes`` so that we create a five megabit 
	per second transmitter on devices created using the helper and a two millisecond 
	delay on channels created by the helper.  We then ``Intall`` the devices
	on the nodes and the channel between them.

Em seguida, instanciamos um ``PointToPointHelper`` e definimos os atributos padr�es para criar uma transmiss�o de cinco megabits por segundo e dois mil�simos de segundo de atraso para dispositivos que utilizam este assistente. Ent�o ``instalamos`` os dispositivos nos n�s e o canal entre eles.

::

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

..
	Next, we declare another ``NodeContainer`` to hold the nodes that will be
	part of the bus (CSMA) network.

Em seguida, declaramos outro ``NodeContainer`` para manter os n�s que ser�o parte da rede em barramento (CSMA).

::

  NodeContainer csmaNodes;
  csmaNodes.Add (p2pNodes.Get (1));
  csmaNodes.Create (nCsma);

..
	The next line of code ``Gets`` the first node (as in having an index of one)
	from the point-to-point node container and adds it to the container of nodes
	that will get CSMA devices.  The node in question is going to end up with a 
	point-to-point device and a CSMA device.  We then create a number of "extra"
	nodes that compose the remainder of the CSMA network.

A pr�xima linha de c�digo ``obt�m`` o primeiro n� do cont�iner ponto-a-ponto e o adiciona ao cont�iner de n�s
que ir�o receber dispositivos CSMA. O n� em quest�o vai acabar com um dispositivo ponto-a-ponto e um dispositivo CSMA. Em seguida, criamos uma s�rie de n�s "extra" que comp�em o restante da rede CSMA.

..
	We then instantiate a ``CsmaHelper`` and set its ``Attributes`` as we did
	in the previous example.  We create a ``NetDeviceContainer`` to keep track of
	the created CSMA net devices and then we ``Install`` CSMA devices on the 
	selected nodes.

Em seguida, instanciamos um ``CsmaHelper`` e definimos seus atributos assim como fizemos no exemplo anterior. Criamos um ``NetDeviceContainer`` para gerenciar os dispositivos CSMA criados e ent�o ``instalamos`` dispositivos CSMA nos n�s selecionados.

::

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

..
	Next, we are going to create the nodes that will be part of the Wifi network.
	We are going to create a number of "station" nodes as specified by the 
	command line argument, and we are going to use the "leftmost" node of the 
	point-to-point link as the node for the access point.

Em seguida, vamos criar os n�s que far�o parte da rede Wifi. Vamos criar alguns n�s "esta��es", conforme especificado na linha de comando, e iremos usar o n� "mais � esquerda" da rede ponto-a-ponto como o n� para o ponto de acesso.

::

  NodeContainer wifiStaNodes;
  wifiStaNodes.Create (nWifi);
  NodeContainer wifiApNode = p2pNodes.Get (0);

..
	The next bit of code constructs the wifi devices and the interconnection
	channel between these wifi nodes. First, we configure the PHY and channel
	helpers:

A pr�xima parte do c�digo constr�i os dispositivos Wifi e o canal de interliga��o entre esses n�s. Primeiro, vamos configurar os assistentes PHY e de canal:

::

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();

..
	For simplicity, this code uses the default PHY layer configuration and
	channel models which are documented in the API doxygen documentation for
	the ``YansWifiChannelHelper::Default`` and ``YansWifiPhyHelper::Default``
	methods. Once these objects are created, we create a channel object
	and associate it to our PHY layer object manager to make sure
	that all the PHY layer objects created by the ``YansWifiPhyHelper``
	share the same underlying channel, that is, they share the same
	wireless medium and can communication and interfere:

Para simplificar, este c�digo usa a configura��o padr�o da camada PHY e modelos de canais que est�o documentados na API doxygen para os m�todos ``YansWifiChannelHelper::Default`` e ``YansWifiPhyHelper::Default``. Uma vez que esses objetos s�o instanciados, criamos um objeto de canal e associamos ele ao nosso gerente de objetos da camada PHY para nos certificarmos de que todos os objetos da camada PHY criados pelo ``YansWifiPhyHelper`` compartilham o mesmo canal subjacente, isto �, eles compartilham o mesmo meio f�sico sem fio e podem comunicar-se e interferir:

::

  phy.SetChannel (channel.Create ());

..
	Once the PHY helper is configured, we can focus on the MAC layer. Here we choose to
	work with non-Qos MACs so we use a NqosWifiMacHelper object to set MAC parameters. 

Uma vez que o assistente PHY est� configurado, podemos nos concentrar na camada MAC. Aqui escolhemos
trabalhar com MACs n�o-Qos, por isso usamos um objeto ``NqosWifiMacHelper`` para definir os par�metros MAC.

::

  WifiHelper wifi = WifiHelper::Default ();
  wifi.SetRemoteStationManager ("ns3::AarfWifiManager");

  NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();

..
	The ``SetRemoteStationManager`` method tells the helper the type of 
	rate control algorithm to use.  Here, it is asking the helper to use the AARF
	algorithm --- details are, of course, available in Doxygen.

O m�todo ``SetRemoteStationManager`` diz ao assistente o tipo de algoritmo de controle de taxa a usar. Aqui, ele est� pedindo ao assistente para usar o algoritmo AARF --- os detalhes est�o dispon�veis no Doxygen.

..
	Next, we configure the type of MAC, the SSID of the infrastructure network we
	want to setup and make sure that our stations don't perform active probing:

Em seguida, configuramos o tipo de MAC, o SSID da rede de infraestrutura, e nos certificamos que as esta��es n�o realizam sondagem ativa (active probing):

::

  Ssid ssid = Ssid ("ns-3-ssid");
  mac.SetType ("ns3::StaWifiMac",
    "Ssid", SsidValue (ssid),
    "ActiveProbing", BooleanValue (false));

..
	This code first creates an 802.11 service set identifier (SSID) object
	that will be used to set the value of the "Ssid" ``Attribute`` of
	the MAC layer implementation.  The particular kind of MAC layer that
	will be created by the helper is specified by ``Attribute`` as
	being of the "ns3::StaWifiMac" type.  The use of
	``NqosWifiMacHelper`` will ensure that the "QosSupported"
	``Attribute`` for created MAC objects is set false. The combination
	of these two configurations means that the MAC instance next created
	will be a non-QoS non-AP station (STA) in an infrastructure BSS (i.e.,
	a BSS with an AP).  Finally, the "ActiveProbing" ``Attribute`` is
	set to false.  This means that probe requests will not be sent by MACs
	created by this helper.

Este c�digo primeiro cria um objeto de um identificador de conjunto de servi�os (SSID 802.11) que ser� utilizado para definir o valor do atributo  "Ssid" da implementa��o da camada MAC. O tipo particular da camada MAC que ser� criado pelo assistente � especificado como sendo do tipo "ns3::StaWifiMac". O uso do assistente ``NqosWifiMacHelper`` ir� garantir que o atributo "QosSupported" para os objetos MAC criados ser� falso. A combina��o destas duas configura��es implica que a inst�ncia MAC criada em seguida ser� uma esta��o (STA) n�o-QoS e n�o-AP, em uma infraestrutura BSS (por exemplo, uma BSS com um AP). Finalmente, o atributo "ActiveProbing" � definido como falso. Isto significa que as solicita��es de sondagem n�o ser�o enviados pelos MACs criados por este assistente.

..
	Once all the station-specific parameters are fully configured, both at the
	MAC and PHY layers, we can invoke our now-familiar ``Install`` method to 
	create the wifi devices of these stations:

Depois que todos os par�metros espec�ficos das esta��es est�o completamente configurados, tanto na camada MAC como na PHY, podemos invocar o nosso m�todo j� familiar ``Instalar`` para criar os dispositivos Wifi destas esta��es:

::

  NetDeviceContainer staDevices;
  staDevices = wifi.Install (phy, mac, wifiStaNodes);

..
	We have configured Wifi for all of our STA nodes, and now we need to 
	configure the AP (access point) node.  We begin this process by changing
	the default ``Attributes`` of the ``NqosWifiMacHelper`` to reflect the 
	requirements of the AP.

J� configuramos o Wifi para todos n�s STA e agora precisamos configurar o AP. Come�amos esse processo mudando o atributo padr�o ``NqosWifiMacHelper`` para refletir os requisitos do AP.

::

  mac.SetType ("ns3::ApWifiMac",
    "Ssid", SsidValue (ssid)));

..
	In this case, the ``NqosWifiMacHelper`` is going to create MAC
	layers of the "ns3::ApWifiMac", the latter specifying that a MAC
	instance configured as an AP should be created, with the helper type
	implying that the "QosSupported" ``Attribute`` should be set to
	false - disabling 802.11e/WMM-style QoS support at created APs.

Neste caso, o ``NqosWifiMacHelper`` vai criar camadas MAC do "ns3::ApWifiMac", este �ltimo especificando que uma inst�ncia MAC configurado como um AP deve ser criado, com o tipo de assistente implicando que o atributo "QosSupported" deve ser definido como falso - desativando o suporte a Qos do tipo 802.11e/WMM nos APs criados. 

..
	The next lines create the single AP which shares the same set of PHY-level
	``Attributes`` (and channel) as the stations:

As pr�ximas linhas criam um AP que compartilha os mesmos atributos a n�vel PHY com as esta��es:

::

  NetDeviceContainer apDevices;
  apDevices = wifi.Install (phy, mac, wifiApNode);

..
	Now, we are going to add mobility models.  We want the STA nodes to be mobile,
	wandering around inside a bounding box, and we want to make the AP node 
	stationary.  We use the ``MobilityHelper`` to make this easy for us.
	First, we instantiate a ``MobilityHelper`` object and set some 
	``Attributes`` controlling the "position allocator" functionality.

Agora, vamos adicionar modelos de mobilidade. Queremos que os n�s STA sejam m�veis, vagando dentro de uma caixa delimitadora, e queremos fazer o n� AP estacion�rio. Usamos o ``MobilityHelper`` para facilitar a execu��o desta tarefa.
Primeiro, instanciamos um objeto ``MobilityHelper`` e definimos alguns atributos controlando a funcionalidade de "aloca��o de posi��o".

::

  MobilityHelper mobility;

  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
    "MinX", DoubleValue (0.0),
    "MinY", DoubleValue (0.0),
    "DeltaX", DoubleValue (5.0),
    "DeltaY", DoubleValue (10.0),
    "GridWidth", UintegerValue (3),
    "LayoutType", StringValue ("RowFirst"));

..
	This code tells the mobility helper to use a two-dimensional grid to initially
	place the STA nodes.  Feel free to explore the Doxygen for class 
	``ns3::GridPositionAllocator`` to see exactly what is being done.

Este c�digo diz ao assistente de mobilidade para usar uma grade bidimensional para distribuir os n�s STA. Sinta-se � vontade para explorar a classe ``ns3::GridPositionAllocator`` no Doxygen para ver exatamente o que est� sendo feito.

..
	We have arranged our nodes on an initial grid, but now we need to tell them
	how to move.  We choose the ``RandomWalk2dMobilityModel`` which has the 
	nodes move in a random direction at a random speed around inside a bounding 
	box.

Arranjamos os n�s em uma grade inicial, mas agora precisamos dizer-lhes como se mover. Escolhemos o modelo ``RandomWalk2dMobilityModel`` em que os n�s se movem em uma dire��o aleat�ria a uma velocidade aleat�ria dentro de um delimitador quadrado.

::

  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
    "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)));

..
	We now tell the ``MobilityHelper`` to install the mobility models on the 
	STA nodes.

Agora dizemos ao ``MobilityHelper`` para instalar os modelos de mobilidade nos n�s STA.

::

  mobility.Install (wifiStaNodes);

..
	We want the access point to remain in a fixed position during the simulation.
	We accomplish this by setting the mobility model for this node to be the 
	``ns3::ConstantPositionMobilityModel``:

Queremos que o ponto de acesso permane�a em uma posi��o fixa durante a simula��o. Conseguimos isto definindo o modelo de mobilidade para este n� como ``ns3::ConstantPositionMobilityModel``:

::

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifiApNode);

..
	We now have our nodes, devices and channels created, and mobility models 
	chosen for the Wifi nodes, but we have no protocol stacks present.  Just as 
	we have done previously many times, we will use the ``InternetStackHelper``
	to install these stacks.

Agora temos os nossos n�s, dispositivos e canais e modelos de mobilidade escolhidos para os n�s Wifi, mas n�o temos pilhas de protocolo. Assim como j� fizemos muitas vezes, usaremos o ``InternetStackHelper`` para instalar estas pilhas.

::

  InternetStackHelper stack;
  stack.Install (csmaNodes);
  stack.Install (wifiApNode);
  stack.Install (wifiStaNodes);

..
	Just as in the ``second.cc`` example script, we are going to use the 
	``Ipv4AddressHelper`` to assign IP addresses to our device interfaces.
	First we use the network 10.1.1.0 to create the two addresses needed for our
	two point-to-point devices.  Then we use network 10.1.2.0 to assign addresses
	to the CSMA network and then we assign addresses from network 10.1.3.0 to
	both the STA devices and the AP on the wireless network.

Assim como no exemplo ``second.cc``, vamos usar o ``Ipv4AddressHelper`` para atribuir endere�os IP para as interfaces de nossos dispositivos. Primeiro, usamos a rede 10.1.1.0 para criar os dois endere�os necess�rios para os dois dispositivos ponto-a-ponto. Ent�o, usamos rede 10.1.2.0 para atribuir endere�os � rede CSMA e, por �ltimo, atribuir endere�os da rede 10.1.3.0 para ambos os dispositivos STA e o ponto de acesso na rede sem fio.

::

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  address.Assign (staDevices);
  address.Assign (apDevices);

..
	We put the echo server on the "rightmost" node in the illustration at the
	start of the file.  We have done this before.

Vamos colocar o servidor de eco no n� "mais � direita" na ilustra��o no in�cio do arquivo.

::

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

..
	And we put the echo client on the last STA node we created, pointing it to
	the server on the CSMA network.  We have also seen similar operations before.

E colocamos o cliente de eco no �ltimo n� STA criado, apontando-o para o servidor na rede CSMA. 

::

  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps =
    echoClient.Install (wifiStaNodes.Get (nWifi - 1));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

..
	Since we have built an internetwork here, we need to enable internetwork routing
	just as we did in the ``second.cc`` example script.

Uma vez que constru�mos uma inter-rede aqui, precisamos ativar o roteamento inter-redes, assim como fizemos no exemplo ``second.cc``.

::

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

..
	One thing that can surprise some users is the fact that the simulation we just
	created will never "naturally" stop.  This is because we asked the wireless
	access point to generate beacons.  It will generate beacons forever, and this
	will result in simulator events being scheduled into the future indefinitely,
	so we must tell the simulator to stop even though it may have beacon generation
	events scheduled.  The following line of code tells the simulator to stop so that 
	we don't simulate beacons forever and enter what is essentially an endless
	loop.

Algo que pode surpreender alguns usu�rios � o fato de que a simula��o que acabamos de criar nunca vai parar "naturalmente". Isto acontece porque pedimos para o ponto de acesso gerar *beacons*. Ele ir� gerar *beacons* para sempre, e isso ir� resultar em eventos sendo escalonados no futuro indefinidamente, por isso devemos dizer para o simulador parar, ainda que hajam eventos de gera��o de *beacons* agendados. A seguinte linha de c�digo informa ao simulador para parar, para que n�o simulemos *beacons* para sempre e entremos no que � essencialmente um la�o sem fim.

::

  Simulator::Stop (Seconds (10.0));

..
	We create just enough tracing to cover all three networks:

Criamos rastreamento suficiente para cobrir todas as tr�s redes:

::

  pointToPoint.EnablePcapAll ("third");
  phy.EnablePcap ("third", apDevices.Get (0));
  csma.EnablePcap ("third", csmaDevices.Get (0), true);

..
	These three lines of code will start pcap tracing on both of the point-to-point
	nodes that serves as our backbone, will start a promiscuous (monitor) mode 
	trace on the Wifi network, and will start a promiscuous trace on the CSMA 
	network.  This will let us see all of the traffic with a minimum number of 
	trace files.

Estas tr�s linhas de c�digo ir�o iniciar o rastreamento do pcap em ambos os n�s ponto-a-ponto que funcionam como nosso *backbone*, ir�o iniciar um modo prom�scuo (monitor) de rastreamento na rede Wifi e na rede CSMA. Isto vai permitir ver todo o tr�fego com um n�mero m�nimo de arquivos de rastreamento.

..
	Finally, we actually run the simulation, clean up and then exit the program.

Finalmente, executamos a simula��o, limpamos e, em seguida, saimos do programa.

::

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
  }

..
	In order to run this example, you have to copy the ``third.cc`` example
	script into the scratch directory and use Waf to build just as you did with
	the ``second.cc`` example.  If you are in the top-level directory of the
	repository you would type,

Para executar este exemplo, voc� deve copiar o arquivo ``third.cc`` para o diret�rio ``scratch`` e usar o Waf para compilar exatamente como com o exemplo ``second.cc``. Se voc� est� no diret�rio raiz do reposit�rio voc� dever� digitar,

::

  cp examples/tutorial/third.cc scratch/mythird.cc
  ./waf
  ./waf --run scratch/mythird

..
	Again, since we have set up the UDP echo applications just as we did in the 
	``second.cc`` script, you will see similar output.

Novamente, uma vez que configuramos aplica��es de eco UDP, assim como fizemos no arquivo ``second.cc``, voc� ver� uma sa�da similar.

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.407s)
  Sent 1024 bytes to 10.1.2.4
  Received 1024 bytes from 10.1.3.3
  Received 1024 bytes from 10.1.2.4

..
	Recall that the first message, ``Sent 1024 bytes to 10.1.2.4``," is the 
	UDP echo client sending a packet to the server.  In this case, the client
	is on the wireless network (10.1.3.0).  The second message, 
	"``Received 1024 bytes from 10.1.3.3``," is from the UDP echo server, 
	generated when it receives the echo packet.  The final message, 
	"``Received 1024 bytes from 10.1.2.4``," is from the echo client, indicating
	that it has received its echo back from the server.

Lembre-se que a primeira mensagem, ``Sent 1024 bytes to 10.1.2.4``," � o cliente de eco UDP enviando um pacote para o servidor. Neste caso, o cliente est� na rede wireless (10.1.3.0). A segunda mensagem, "``Received 1024 bytes from 10.1.3.3``," � do servidor de eco UDP, gerado quando este recebe o pacote de eco. A mensagem final, "``Received 1024 bytes from 10.1.2.4``," � do cliente de eco, indicando que este recebeu o seu eco de volta do servidor.

..
	If you now go and look in the top level directory, you will find four trace 
	files from this simulation, two from node zero and two from node one:

No diret�rio raiz, encontraremos quatro arquivos de rastreamento desta simula��o, dois do n� zero e dois do n� um:

::

  third-0-0.pcap  third-0-1.pcap  third-1-0.pcap  third-1-1.pcap

..
	The file "third-0-0.pcap" corresponds to the point-to-point device on node
	zero -- the left side of the "backbone".  The file "third-1-0.pcap" 
	corresponds to the point-to-point device on node one -- the right side of the
	"backbone".  The file "third-0-1.pcap" will be the promiscuous (monitor
	mode) trace from the Wifi network and the file "third-1-1.pcap" will be the
	promiscuous trace from the CSMA network.  Can you verify this by inspecting
	the code?

O arquivo "third-0-0.pcap" corresponde ao dispositivo ponto-a-ponto no n� zero -- o lado esquerdo do *backbone*. O arquivo "third-1-0.pcap" corresponde ao dispositivo ponto-a-ponto no n� um -- o lado direito do *backbone*. O arquivo "third-0-1.pcap" corresponde o rastreamento em modo prom�scuo (modo monitor) da rede Wifi e o arquivo "third-1 1.pcap" ao
rastreamento em modo prom�scuo da rede CSMA. Voc� consegue verificar isto inspecionando o c�digo?

..
	Since the echo client is on the Wifi network, let's start there.  Let's take
	a look at the promiscuous (monitor mode) trace we captured on that network.

Como o cliente de eco est� na rede Wifi, vamos come�ar por a�. Vamos dar uma olhada para a sa�da de rastreamento no modo prom�scuo (modo monitor) capturada nessa rede.

::

  tcpdump -nn -tt -r third-0-1.pcap

..
	You should see some wifi-looking contents you haven't seen here before:

Voc� dever� ver alguns conte�dos ''wifi'' que n�o tinham antes:

::

  reading from file third-0-1.pcap, link-type IEEE802_11 (802.11)
  0.000025 Beacon (ns-3-ssid) [6.0* 9.0 12.0 18.0 24.0 36.0 48.0 54.0 Mbit] IBSS
  0.000263 Assoc Request (ns-3-ssid) [6.0 9.0 12.0 18.0 24.0 36.0 48.0 54.0 Mbit]
  0.000279 Acknowledgment RA:00:00:00:00:00:09 
  0.000552 Assoc Request (ns-3-ssid) [6.0 9.0 12.0 18.0 24.0 36.0 48.0 54.0 Mbit]
  0.000568 Acknowledgment RA:00:00:00:00:00:07 
  0.000664 Assoc Response AID(0) :: Succesful
  0.001001 Assoc Response AID(0) :: Succesful
  0.001145 Acknowledgment RA:00:00:00:00:00:0a 
  0.001233 Assoc Response AID(0) :: Succesful
  0.001377 Acknowledgment RA:00:00:00:00:00:0a 
  0.001597 Assoc Request (ns-3-ssid) [6.0 9.0 12.0 18.0 24.0 36.0 48.0 54.0 Mbit]
  0.001613 Acknowledgment RA:00:00:00:00:00:08 
  0.001691 Assoc Response AID(0) :: Succesful
  0.001835 Acknowledgment RA:00:00:00:00:00:0a 
  0.102400 Beacon (ns-3-ssid) [6.0* 9.0 12.0 18.0 24.0 36.0 48.0 54.0 Mbit] IBSS
  0.204800 Beacon (ns-3-ssid) [6.0* 9.0 12.0 18.0 24.0 36.0 48.0 54.0 Mbit] IBSS
  0.307200 Beacon (ns-3-ssid) [6.0* 9.0 12.0 18.0 24.0 36.0 48.0 54.0 Mbit] IBSS

..
	You can see that the link type is now 802.11 as you would expect.  You can 
	probably understand what is going on and find the IP echo request and response
	packets in this trace.  We leave it as an exercise to completely parse the 
	trace dump.

Observamos que o tipo de liga��o agora � 802.11, como esperado. Voc� provavelmente vai entender o que est� acontecendo e encontrar o pacote de pedido de eco e a resposta nesta sa�da de rastreamento. Vamos deixar como um exerc�cio a an�lise completa da sa�da.

..
	Now, look at the pcap file of the right side of the point-to-point link,

Agora, analisando o arquivo pcap do lado direito da liga��o ponto-a-ponto,

::

  tcpdump -nn -tt -r third-0-0.pcap

..
	Again, you should see some familiar looking contents:

Novamente, temos algumas sa�das familiares:

::

  reading from file third-0-0.pcap, link-type PPP (PPP)
  2.002160 IP 10.1.3.3.49153 > 10.1.2.4.9: UDP, length 1024
  2.009767 IP 10.1.2.4.9 > 10.1.3.3.49153: UDP, length 1024

..
	This is the echo packet going from left to right (from Wifi to CSMA) and back
	again across the point-to-point link.

Este � o pacote de eco indo da esquerda para a direita (do Wifi para o CSMA) e de volta atrav�s da liga��o ponto-a-ponto.

..
	Now, look at the pcap file of the right side of the point-to-point link,

Agora, analisando o arquivo pcap do lado direito da liga��o ponto-a-ponto,

::

  tcpdump -nn -tt -r third-1-0.pcap

..
	Again, you should see some familiar looking contents:

Novamente, temos algumas sa�das familiares:

::

  reading from file third-1-0.pcap, link-type PPP (PPP)
  2.005846 IP 10.1.3.3.49153 > 10.1.2.4.9: UDP, length 1024
  2.006081 IP 10.1.2.4.9 > 10.1.3.3.49153: UDP, length 1024

..
	This is also the echo packet going from left to right (from Wifi to CSMA) and 
	back again across the point-to-point link with slightly different timings
	as you might expect.

Este � o pacote de eco indo da esquerda para a direita (do Wifi para o CSMA) e depois voltando atrav�s do liga��o ponto-a-ponto com tempos um pouco diferentes, como esperado.

..
	The echo server is on the CSMA network, let's look at the promiscuous trace 
	there:

O servidor de eco est� na rede CSMA, vamos olhar para a sa�da de rastreamento prom�scua:

::

  tcpdump -nn -tt -r third-1-1.pcap

..
	You should see some familiar looking contents:

Temos algumas sa�das familiares:

::

  reading from file third-1-1.pcap, link-type EN10MB (Ethernet)
  2.005846 ARP, Request who-has 10.1.2.4 (ff:ff:ff:ff:ff:ff) tell 10.1.2.1, length 50
  2.005870 ARP, Reply 10.1.2.4 is-at 00:00:00:00:00:06, length 50
  2.005870 IP 10.1.3.3.49153 > 10.1.2.4.9: UDP, length 1024
  2.005975 ARP, Request who-has 10.1.2.1 (ff:ff:ff:ff:ff:ff) tell 10.1.2.4, length 50
  2.005975 ARP, Reply 10.1.2.1 is-at 00:00:00:00:00:03, length 50
  2.006081 IP 10.1.2.4.9 > 10.1.3.3.49153: UDP, length 1024

..
	This should be easily understood.  If you've forgotten, go back and look at
	the discussion in ``second.cc``.  This is the same sequence.

Isto deve ser de f�cil entendimento. Se esqueceu, volte e olhe para a discuss�o em ``second.cc``. Este exemplo segue a mesma seq��ncia.

..
	Now, we spent a lot of time setting up mobility models for the wireless network
	and so it would be a shame to finish up without even showing that the STA
	nodes are actually moving around during the simulation.  Let's do this by hooking
	into the ``MobilityModel`` course change trace source.  This is just a sneak
	peek into the detailed tracing section which is coming up, but this seems a very
	nice place to get an example in.

Passamos algum tempo com a cria��o de modelos de mobilidade para a rede sem fio e por isso seria uma vergonha encerrar sem mostrar que os n�s STA est�o realmente se movendo durante a simula��o. Vamos fazer isto ligando o ``MobilityModel`` � fonte de rastreamento. Isto � apenas uma vis�o geral da se��o que detalha o rastreamento, mas � um �timo lugar para um exemplo.

..
	As mentioned in the "Tweaking ns-3" section, the |ns3| tracing system 
	is divided into trace sources and trace sinks, and we provide functions to 
	connect the two.  We will use the mobility model predefined course change 
	trace source to originate the trace events.  We will need to write a trace 
	sink to connect to that source that will display some pretty information for 
	us.  Despite its reputation as being difficult, it's really quite simple.
	Just before the main program of the ``scratch/mythird.cc`` script, add the 
	following function:

Como mencionado na se��o "Aperfei�oando", o sistema de rastreamento � dividido em origem de rastreamento e destino de rastreamento, com fun��es para conectar um ao outro. Vamos usar a mudan�a de curso padr�o do modelo de mobilidade para originar os eventos de rastreamento. Vamos precisar escrever um destino de rastreamento para se conectar a origem que ir� exibir algumas informa��es importantes. Apesar de sua reputa��o como dif�cil, � de fato muito simples. Antes do programa principal do c�digo ``scratch/mythird.cc``, adicione a seguinte fun��o:

::

  void
  CourseChange (std::string context, Ptr<const MobilityModel> model)
  {
    Vector position = model->GetPosition ();
    NS_LOG_UNCOND (context << 
      " x = " << position.x << ", y = " << position.y);
  }

..
	This code just pulls the position information from the mobility model and 
	unconditionally logs the x and y position of the node.  We are
	going to arrange for this function to be called every time the wireless
	node with the echo client changes its position.  We do this using the 
	``Config::Connect`` function.  Add the following lines of code to the
	script just before the ``Simulator::Run`` call.

Este c�digo obt�m as informa��es de posi��o do modelo de mobilidade e registra a posi��o x e y do n�. Vamos criar o c�digo para que esta fun��o seja chamada toda vez que o n� com o cliente de eco mude de posi��o. Fazemos isto usando a fun��o ``Config::Connect``. Adicione as seguintes linhas de c�digo no c�digo antes da chamada ``Simulator::Run``.

::

  std::ostringstream oss;
  oss <<
    "/NodeList/" << wifiStaNodes.Get (nWifi - 1)->GetId () <<
    "/$ns3::MobilityModel/CourseChange";

  Config::Connect (oss.str (), MakeCallback (&CourseChange));

..
	What we do here is to create a string containing the tracing namespace path
	of the event to which we want to connect.  First, we have to figure out which 
	node it is we want using the ``GetId`` method as described earlier.  In the
	case of the default number of CSMA and wireless nodes, this turns out to be 
	node seven and the tracing namespace path to the mobility model would look
	like,

O que fazemos aqui � criar uma `string` contendo o caminho do `namespace` de rastreamento do evento ao qual se deseja conectar. Primeiro, temos que descobrir qual n� que queremos usando o m�todo ``GetId`` como descrito anteriormente. No caso de usar o n�mero padr�o do CSMA e dos n�s de rede sem fio, este acaba sendo o n� sete e o caminho do `namespace` de rastreamento para o modelo de mobilidade seria:

::

  /NodeList/7/$ns3::MobilityModel/CourseChange

..
	Based on the discussion in the tracing section, you may infer that this trace 
	path references the seventh node in the global NodeList.  It specifies
	what is called an aggregated object of type ``ns3::MobilityModel``.  The 
	dollar sign prefix implies that the MobilityModel is aggregated to node seven.
	The last component of the path means that we are hooking into the 
	"CourseChange" event of that model.

Com base na discuss�o na se��o de rastreamento, voc� pode inferir que este caminho referencia o s�timo n� na lista `NodeList` global. Ele especifica o que � chamado de um objeto agregado do tipo ``ns3::MobilityModel``. O prefixo cifr�o implica que o `MobilityModel` � agregado ao n� sete. O �ltimo componente do caminho significa que estamos ligando ao evento "CourseChange" desse modelo.

..
	We make a connection between the trace source in node seven with our trace 
	sink by calling ``Config::Connect`` and passing this namespace path.  Once 
	this is done, every course change event on node seven will be hooked into our 
	trace sink, which will in turn print out the new position.

Fazemos uma conex�o entre a origem de rastreamento no n� sete com o nosso destino de rastreamento chamando ``Config::Connect`` e passando o caminho do `namespace` como par�metro. Feito isto, cada evento de mudan�a de curso no n� sete ser� capturado em nosso destino de rastreamento, que por sua vez ir� imprimir a nova posi��o.

..
	If you now run the simulation, you will see the course changes displayed as 
	they happen.

Se voc� executar a simula��o, ver� as mudan�as de curso assim que elas ocorrerem.

::

  Build finished successfully (00:00:01)
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 10, y = 0
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 9.41539, y = -0.811313
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 8.46199, y = -1.11303
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.52738, y = -1.46869
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 6.67099, y = -1.98503
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 5.6835, y = -2.14268
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 4.70932, y = -1.91689
  Sent 1024 bytes to 10.1.2.4
  Received 1024 bytes from 10.1.3.3
  Received 1024 bytes from 10.1.2.4
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 5.53175, y = -2.48576
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 4.58021, y = -2.17821
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 4.18915, y = -1.25785
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 4.7572, y = -0.434856
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 4.62404, y = 0.556238
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 4.74127, y = 1.54934
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 5.73934, y = 1.48729
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 6.18521, y = 0.59219
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 6.58121, y = 1.51044
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.27897, y = 2.22677
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 6.42888, y = 1.70014
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.40519, y = 1.91654
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 6.51981, y = 1.45166
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.34588, y = 2.01523
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.81046, y = 2.90077
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 6.89186, y = 3.29596
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.46617, y = 2.47732
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.05492, y = 1.56579
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 8.00393, y = 1.25054
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.00968, y = 1.35768
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.33503, y = 2.30328
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.18682, y = 3.29223
  /NodeList/7/$ns3::MobilityModel/CourseChange x = 7.96865, y = 2.66873
