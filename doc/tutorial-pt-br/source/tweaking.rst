.. include:: replace.txt

..
	========================================================================================
	Translated for portuguese by the students of the inter-institutional doctorate program of IME-USP/UTFPR-CM.
	
	Traduzido para o portugu�s pelos alunos do programa de doutorado inter institucional do Instituto de Matem�tica e Estat�stica da Universidade de S�o Paulo --- IME-USP em parceria com a Universidade Tecnol�gica Federal do Paran� - Campus Campo Mour�o --- UTFPR-CM:
	
	* Frank Helbert (frank@ime.usp.br);
	* Luiz Arthur Feitosa dos Santos (luizsan@ime.usp.br);
	* Rodrigo Campiolo (campiolo@ime.usp.br).
	========================================================================================

.. Tweaking

Aprofundando Conhecimentos
----------------------------------------

.. 
	Using the Logging Module


Usando o M�dulo de Registro
***************************

..
	We have already taken a brief look at the |ns3| logging module while
	going over the ``first.cc`` script.  We will now take a closer look and 
	see what kind of use-cases the logging subsystem was designed to cover.

J� demos uma breve olhada no m�dulo de Registro (do ingl�s, `log` ou `logging`) do |ns3|, enquanto analis�vamos o c�digo ``first.cc``. Agora iremos aprofundar nossos conhecimento sobre este m�dulo para utiliz�-lo de forma mais eficiente.

.. 
	Logging Overview

Vis�o Geral Sobre o Sistema de Registro
+++++++++++++++++++++++++++++++++++++++

..
	Many large systems support some kind of message logging facility, and 
	|ns3| is not an exception.  In some cases, only error messages are 
	logged to the "operator console" (which is typically ``stderr`` in Unix-
	based systems).  In other systems, warning messages may be output as well as 
	more detailed informational messages.  In some cases, logging facilities are 
	used to output debug messages which can quickly turn the output into a blur.

A maioria dos sistemas de grande porte suportam mensagens de registros (mensagens de 'log' que informam o que esta ocorrendo no sistema) e o |ns3| n�o � nenhuma exce��o. Em alguns casos, somente mensagens de erros s�o reportadas para o "operador do console" (que � geralmente o ``stderr`` dos sistemas baseados no Unix). Em outros sistemas, mensagens de avisos podem ser impressas detalhando informa��es do sistema. Em alguns casos, o sistema de registro fornece mensagens de depura��o que podem rapidamente mostrar o que est� ocorrendo de errado.

..
	|ns3| takes the view that all of these verbosity levels are useful 
	and we provide a selectable, multi-level approach to message logging.  Logging
	can be disabled completely, enabled on a component-by-component basis, or
	enabled globally; and it provides selectable verbosity levels.  The 
	|ns3| log module provides a straightforward, relatively easy to use
	way to get useful information out of your simulation.

O |ns3| permite que o usu�rio tenha vis�es de todos os n�veis do sistema atrav�s das mensagens de registro. Podemos selecionar o n�vel de sa�da das mensagens de registro(`verbosty`), atrav�s de um abordagem multin�vel. As mensagens de registro podem ser desabilitadas completamente, habilitadas componente por componente ou habilitada globalmente. Ou seja,  permite selecionar o n�vel de detalhamento das mensagens de sa�da. O m�dulo de registro do |ns3| fornece uma forma correta e segura de obtermos informa��es sobre as simula��es.

..
	You should understand that we do provide a general purpose mechanism --- 
	tracing --- to get data out of your models which should be preferred for 
	simulation output (see the tutorial section Using the Tracing System for
	more details on our tracing system).  Logging should be preferred for 
	debugging information, warnings, error messages, or any time you want to 
	easily get a quick message out of your scripts or models.

No |ns3| foi implementado um mecanismo de --- rastreamento --- de prop�sito geral, que permite a obten��o de sa�das de dados dos modelos simulados (veja a se��o Usando o Sistema de Rastreamento do tutorial para mais detalhes). O sistema de registro deve ser usado para depurar informa��es, alertas, mensagens de erros ou para mostrar qualquer informa��o dos `scripts` ou modelos.

..
	There are currently seven levels of log messages of increasing verbosity
	defined in the system.  

Atualmente existem sete n�veis de mensagens de registro definidas no sistema.

..
	* NS_LOG_ERROR --- Log error messages;
	* NS_LOG_WARN --- Log warning messages;
	* NS_LOG_DEBUG --- Log relatively rare, ad-hoc debugging messages;
	* NS_LOG_INFO --- Log informational messages about program progress;
	* NS_LOG_FUNCTION --- Log a message describing each function called;
	* NS_LOG_LOGIC -- Log messages describing logical flow within a function;
	* NS_LOG_ALL --- Log everything.

* NS_LOG_ERROR --- Registra mensagens de erro;
* NS_LOG_WARN --- Registra mensagens de alertas;
* NS_LOG_DEBUG --- Registra mensagens mais raras, mensagens de depura��o `ad-hoc`;
* NS_LOG_INFO ---  Registra mensagens informativas sobre o progresso do programa;
* NS_LOG_FUNCTION --- Registra mensagens descrevendo cada fun��o chamada;
* NS_LOG_LOGIC --- Registra mensagens que descrevem o fluxo l�gico dentro de uma fun��o;
* NS_LOG_ALL --- Registra tudo.

..
	We also provide an unconditional logging level that is always displayed,
	irrespective of logging levels or component selection.

Tamb�m � fornecido um n�vel de registro incondicional, que sempre � exibido independente do n�vel de registro ou do componente selecionado.

..
	*  NS_LOG_UNCOND -- Log the associated message unconditionally.

*  NS_LOG_UNCOND --- Registra mensagens incondicionalmente.

..
	Each level can be requested singly or cumulatively; and logging can be set 
	up using a shell environment variable (NS_LOG) or by logging system function 
	call.  As was seen earlier in the tutorial, the logging system has Doxygen 
	documentation and now would be a good time to peruse the Logging Module 
	documentation if you have not done so.

Cada n�vel pode ser requerido individualmente ou de forma cumulativa. O registro pode ser configurado usando uma vari�vel de ambiente (``NS_LOG``) ou atrav�s de uma chamada ao sistema de registro. J� hav�amos abordado anteriormente o sistema de registro, atrav�s da documenta��o Doxygen, agora � uma boa hora para ler com aten��o esta documenta��o no Doxygen.

..
	Now that you have read the documentation in great detail, let's use some of
	that knowledge to get some interesting information out of the 
	``scratch/myfirst.cc`` example script you have already built.

Depois de ler a documenta��o, vamos usar nosso conhecimento para obter algumas informa��es importante do c�digo de exemplo ``scratch/myfirst.cc``.

.. 
	Enabling Logging

Habilitando o Sistema de Registro
+++++++++++++++++++++++++++++++++

..
	Let's use the NS_LOG environment variable to turn on some more logging, but
	first, just to get our bearings, go ahead and run the last script just as you 
	did previously,

Utilizaremos a vari�vel de ambiente ``NS_LOG`` para habilitar o sistema de Registro, mas antes de prosseguir, execute o c�digo feito na se��o anterior,

::

  ./waf --run scratch/myfirst

..
	You should see the now familiar output of the first |ns3| example
	program

Veremos a sa�da do nosso primeiro programa |ns3| de exemplo, tal como visto anteriormente.

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.413s)
  Sent 1024 bytes to 10.1.1.2
  Received 1024 bytes from 10.1.1.1
  Received 1024 bytes from 10.1.1.2


..
	It turns out that the "Sent" and "Received" messages you see above are
	actually logging messages from the ``UdpEchoClientApplication`` and 
	``UdpEchoServerApplication``.  We can ask the client application, for 
	example, to print more information by setting its logging level via the 
	NS_LOG environment variable.  

As mensagens de envio e recebimentos apresentadas anteriormente s�o mensagens de registro, obtidas de ``UdpEchoClientApplication`` e ``UdpEchoServerApplication``. Podemos pedir para a aplica��o cliente, por exemplo, imprimir mais informa��es configurando o n�vel de registro atrav�s da vari�vel de ambiente ``NS_LOG``.


..
	I am going to assume from here on that you are using an sh-like shell that uses 
	the"VARIABLE=value" syntax.  If you are using a csh-like shell, then you 
	will have to convert my examples to the "setenv VARIABLE value" syntax 
	required by those shells.

Aqui estamos assumindo que voc� est� usando um `shell` parecido com o ``sh``, que usa a sintaxe "VARIABLE=value". Se voc� estiver usando um `shell` parecido com o ``csh``, ent�o ter� que converter os exemplos para a sintaxe "setenv VARIABLE value", requerida por este `shell`.

..
	Right now, the UDP echo client application is responding to the following line
	of code in ``scratch/myfirst.cc``,

Agora, a aplica��o cliente de eco UDP ir� responder a seguinte linha de c�digo ``scratch/myfirst.cc``,

::

  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);

..
	This line of code enables the ``LOG_LEVEL_INFO`` level of logging.  When 
	we pass a logging level flag, we are actually enabling the given level and
	all lower levels.  In this case, we have enabled ``NS_LOG_INFO``,
	``NS_LOG_DEBUG``, ``NS_LOG_WARN`` and ``NS_LOG_ERROR``.  We can
	increase the logging level and get more information without changing the
	script and recompiling by setting the NS_LOG environment variable like this:

Essa linha de c�digo habilita o n�vel ``LOG_LEVEL_INFO`` de registro. Quando habilitamos um dado n�vel de registro, estamos habilitando este n�vel e todos os n�veis inferiores a este. Neste caso, habilitamos ``NS_LOG_INFO``,	``NS_LOG_DEBUG``, ``NS_LOG_WARN`` e ``NS_LOG_ERROR``. Podemos aumentar o n�vel de registro e obter mais informa��es sem alterar o `script`, ou seja, sem ter que recompilar. Conseguimos isto atrav�s da configura��o da vari�vel de ambiente ``NS_LOG``, tal como:

::

  export NS_LOG=UdpEchoClientApplication=level_all

.. 
	This sets the shell environment variable ``NS_LOG`` to the string,

Isto configura a vari�vel de ambiente ``NS_LOG`` no `shell` para,

::

  UdpEchoClientApplication=level_all

..
	The left hand side of the assignment is the name of the logging component we
	want to set, and the right hand side is the flag we want to use.  In this case,
	we are going to turn on all of the debugging levels for the application.  If
	you run the script with NS_LOG set this way, the |ns3| logging 
	system will pick up the change and you should see the following output:

Do lado esquerdo do comando temos o nome do componente de registro que n�s queremos configurar, no lado direito fica o valor que estamos passando. Neste caso, estamos ligando todos os n�veis de depura��o para a aplica��o. Se executarmos o c�digo com o ``NS_LOG`` configurado desta forma, o sistema de registro do |NS3| observar� a mudan�a e mostrar� a seguinte sa�da:


::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.404s)
  UdpEchoClientApplication:UdpEchoClient()
  UdpEchoClientApplication:SetDataSize(1024)
  UdpEchoClientApplication:StartApplication()
  UdpEchoClientApplication:ScheduleTransmit()
  UdpEchoClientApplication:Send()
  Sent 1024 bytes to 10.1.1.2
  Received 1024 bytes from 10.1.1.1
  UdpEchoClientApplication:HandleRead(0x6241e0, 0x624a20)
  Received 1024 bytes from 10.1.1.2
  UdpEchoClientApplication:StopApplication()
  UdpEchoClientApplication:DoDispose()
  UdpEchoClientApplication:~UdpEchoClient()

..
	The additional debug information provided by the application is from
	the NS_LOG_FUNCTION level.  This shows every time a function in the application
	is called during script execution.  Note that there are no requirements in the
	|ns3| system that models must support any particular logging 
	functionality.  The decision regarding how much information is logged
	is left to the individual model developer.  In the case of the echo 
	applications, a good deal of log output is available.

As informa��es de depura��o extras, apresentadas aqui, s�o fornecidas pela aplica��o no n�vel de registros ``NS_LOG_FUNCTION``. Isto � apresentado toda vez que a aplica��o chamar a fun��o. N�o � obrigat�rio que o modelo forne�a suporte a registro, no |ns3|, esta decis�o cabe ao desenvolvedor do modelo. No caso da aplica��o de eco uma grande quantidade de sa�das de `log` est�o dispon�veis.

..
	You can now see a log of the function calls that were made to the application.
	If you look closely you will notice a single colon between the string 
	``UdpEchoClientApplication`` and the method name where you might have 
	expected a C++ scope operator (``::``).  This is intentional.  

Podemos ver agora registros de v�rias fun��es executadas pela aplica��o. Se olharmos mais de perto veremos que as informa��es s�o dadas em colunas separadas por (``::``), do lado esquerdo est� o nome da aplica��o (no exemplo, ``UdpEchoClientApplication``) e do outro lado o nome do m�todo esperado pelo escopo C++. Isto � incremental.

..
	The name is not actually a class name, it is a logging component name.  When 
	there is a one-to-one correspondence between a source file and a class, this 
	will generally be the class name but you should understand that it is not 
	actually a class name, and there is a single colon there instead of a double
	colon to remind you in a relatively subtle way to conceptually separate the 
	logging component name from the class name.

O nome que est� aparece no registro n�o � necessariamente o nome da classe, mas sim o nome do componente de registro. Quando existe uma correspond�ncia um-para-um, entre c�digo fonte e classe, este geralmente ser� o nome da classe, mas isto nem sempre � verdade. A maneira sutil de diferenciar esta situa��o � usar ``:`` quando for o nome do componente de registro e ``::`` quando for o nome da classe.

..
	It turns out that in some cases, it can be hard to determine which method
	actually generates a log message.  If you look in the text above, you may
	wonder where the string "``Received 1024 bytes from 10.1.1.2``" comes
	from.  You can resolve this by OR'ing the ``prefix_func`` level into the
	``NS_LOG`` environment variable.  Try doing the following, 

Em alguns casos pode ser complicado determinar qual m�todo gerou a mensagem. Se olharmos o texto anterior, veremos a mensagem "``Received 1024 bytes from 10.1.1.2``", nesta n�o existe certeza de onde a mensagem veio. Podemos resolver isto usando um "OU" (`OR`) entre o n�vel de registro e o ``prefix_func``, dentro do ``NS_LOG``. 

::

  export 'NS_LOG=UdpEchoClientApplication=level_all|prefix_func'

..
	Note that the quotes are required since the vertical bar we use to indicate an
	OR operation is also a Unix pipe connector.

As aspas s�o requeridas quando usamos o `|` (`pipe`) para indicar uma opera��o de OU.

..
	Now, if you run the script you will see that the logging system makes sure 
	that every message from the given log component is prefixed with the component
	name.

Agora, se executarmos o `script` devemos ver que o sistema de registro informa de qual componente de registro vem a mensagem.

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.417s)
  UdpEchoClientApplication:UdpEchoClient()
  UdpEchoClientApplication:SetDataSize(1024)
  UdpEchoClientApplication:StartApplication()
  UdpEchoClientApplication:ScheduleTransmit()
  UdpEchoClientApplication:Send()
  UdpEchoClientApplication:Send(): Sent 1024 bytes to 10.1.1.2
  Received 1024 bytes from 10.1.1.1
  UdpEchoClientApplication:HandleRead(0x6241e0, 0x624a20)
  UdpEchoClientApplication:HandleRead(): Received 1024 bytes from 10.1.1.2
  UdpEchoClientApplication:StopApplication()
  UdpEchoClientApplication:DoDispose()
  UdpEchoClientApplication:~UdpEchoClient()

..
	You can now see all of the messages coming from the UDP echo client application
	are identified as such.  The message "Received 1024 bytes from 10.1.1.2" is
	now clearly identified as coming from the echo client application.  The 
	remaining message must be coming from the UDP echo server application.  We 
	can enable that component by entering a colon separated list of components in
	the NS_LOG environment variable.

Podemos ver, depois da configura��o, que todas as mensagens do cliente de eco UDP est�o identificadas. Agora a mensagem "Received 1024 bytes from 10.1.1.2" � claramente identificada como sendo do cliente de eco. O restante das mensagens devem estar vindo do servidor de eco UDP. Podemos habilitar mais do que um componente usando ``:``, para separ�-los na vari�vel ``NS_LOG``.

::

  export 'NS_LOG=UdpEchoClientApplication=level_all|prefix_func:
                 UdpEchoServerApplication=level_all|prefix_func'

..
	Warning:  You will need to remove the newline after the ``:`` in the
	example text above which is only there for document formatting purposes.

Aten��o: n�o podemos quebrar a entrada da vari�vel em v�rias linhas como foi feito no exemplo, tudo deve estar em uma �nica linha. O exemplo ficou assim por uma quest�o de formata��o do documento.

..
	Now, if you run the script you will see all of the log messages from both the
	echo client and server applications.  You may see that this can be very useful
	in debugging problems.

Agora, se executarmos o `script` veremos todas as mensagens de registro tanto do cliente quando do servidor. Isto � muito �til na depura��o de problemas.

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.406s)
  UdpEchoServerApplication:UdpEchoServer()
  UdpEchoClientApplication:UdpEchoClient()
  UdpEchoClientApplication:SetDataSize(1024)
  UdpEchoServerApplication:StartApplication()
  UdpEchoClientApplication:StartApplication()
  UdpEchoClientApplication:ScheduleTransmit()
  UdpEchoClientApplication:Send()
  UdpEchoClientApplication:Send(): Sent 1024 bytes to 10.1.1.2
  UdpEchoServerApplication:HandleRead(): Received 1024 bytes from 10.1.1.1
  UdpEchoServerApplication:HandleRead(): Echoing packet
  UdpEchoClientApplication:HandleRead(0x624920, 0x625160)
  UdpEchoClientApplication:HandleRead(): Received 1024 bytes from 10.1.1.2
  UdpEchoServerApplication:StopApplication()
  UdpEchoClientApplication:StopApplication()
  UdpEchoClientApplication:DoDispose()
  UdpEchoServerApplication:DoDispose()
  UdpEchoClientApplication:~UdpEchoClient()
  UdpEchoServerApplication:~UdpEchoServer()

..
	It is also sometimes useful to be able to see the simulation time at which a
	log message is generated.  You can do this by ORing in the prefix_time bit.

As vezes tamb�m � �til registrar o tempo em que uma mensagem � gerada. Podemos fazer isto atrav�s de um OU com o `prefix_time`, exemplo:


::

  export 'NS_LOG=UdpEchoClientApplication=level_all|prefix_func|prefix_time:
                 UdpEchoServerApplication=level_all|prefix_func|prefix_time'

..
	Again, you will have to remove the newline above.  If you run the script now,
	you should see the following output:

Novamente, teremos que deixar tudo em uma �nica linha e n�o em duas como no exemplo anterior. Executando o `script`, veremos a seguinte sa�da:

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.418s)
  0s UdpEchoServerApplication:UdpEchoServer()
  0s UdpEchoClientApplication:UdpEchoClient()
  0s UdpEchoClientApplication:SetDataSize(1024)
  1s UdpEchoServerApplication:StartApplication()
  2s UdpEchoClientApplication:StartApplication()
  2s UdpEchoClientApplication:ScheduleTransmit()
  2s UdpEchoClientApplication:Send()
  2s UdpEchoClientApplication:Send(): Sent 1024 bytes to 10.1.1.2
  2.00369s UdpEchoServerApplication:HandleRead(): Received 1024 bytes from 10.1.1.1
  2.00369s UdpEchoServerApplication:HandleRead(): Echoing packet
  2.00737s UdpEchoClientApplication:HandleRead(0x624290, 0x624ad0)
  2.00737s UdpEchoClientApplication:HandleRead(): Received 1024 bytes from 10.1.1.2
  10s UdpEchoServerApplication:StopApplication()
  10s UdpEchoClientApplication:StopApplication()
  UdpEchoClientApplication:DoDispose()
  UdpEchoServerApplication:DoDispose()
  UdpEchoClientApplication:~UdpEchoClient()
  UdpEchoServerApplication:~UdpEchoServer()

.. 
	You can see that the constructor for the UdpEchoServer was called at a 
	simulation time of 0 seconds.  This is actually happening before the 
	simulation starts, but the time is displayed as zero seconds.  The same is true
	for the UdpEchoClient constructor message.

Podemos ver que o construtor para o ``UdpEchoServer`` foi chamado pelo simulador no segundo 0 (zero). Isto acontece antes do simulador ser iniciado, mas o tempo � mostrado como zero, o mesmo acontece para o construtor do ``UdpEchoClient``.

..
	Recall that the ``scratch/first.cc`` script started the echo server 
	application at one second into the simulation.  You can now see that the 
	``StartApplication`` method of the server is, in fact, called at one second.
	You can also see that the echo client application is started at a simulation 
	time of two seconds as we requested in the script.

Lembre-se que o `script` ``scratch/first.cc`` inicia a aplica��o servidor de eco no primeiro segundo da simula��o. Repare que o m�todo ``StartApplication`` do servidor �, de fato, chamado com um segundo. Tamb�m podemos notar que a aplica��o cliente de eco � iniciada com dois segundos de simula��o, como n�s pedimos no `script`.

..
	You can now follow the progress of the simulation from the 
	``ScheduleTransmit`` call in the client that calls ``Send`` to the 
	``HandleRead`` callback in the echo server application.  Note that the 
	elapsed time for the packet to be sent across the point-to-point link is 3.69
	milliseconds.  You see the echo server logging a message telling you that it
	has echoed the packet and then, after another channel delay, you see the echo
	client receive the echoed packet in its ``HandleRead`` method.

.. 
	>> rever tradu��o

Agora podemos acompanhar o andamento da simula��o: ``ScheduleTransmit`` � chamado no cliente, que invoca o ``Send`` e o ``HandleRead``, que � usado na aplica��o servidor de eco. Repare que o tempo decorrido entre o envio de cada pacote � de 3.69 milissegundos. Veja que a mensagem de registro do servidor diz que o pacote foi ecoado e depois houve um atraso no canal. Podemos ver que o cliente recebeu o pacote ecoado pelo m�todo ``HandleRead``.

..
	There is a lot that is happening under the covers in this simulation that you
	are not seeing as well.  You can very easily follow the entire process by
	turning on all of the logging components in the system.  Try setting the 
	``NS_LOG`` variable to the following,

Existe muita coisa acontecendo por baixo dos panos e que n�o estamos vendo. Podemos facilmente seguir as entradas de processo configurando todos os componentes de registro do sistema. Configure a vari�vel de ``NS_LOG`` da seguinte forma,

::

  export 'NS_LOG=*=level_all|prefix_func|prefix_time'

..
	The asterisk above is the logging component wildcard.  This will turn on all 
	of the logging in all of the components used in the simulation.  I won't 
	reproduce the output here (as of this writing it produces 1265 lines of output
	for the single packet echo) but you can redirect this information into a file 
	and look through it with your favorite editor if you like,

O asterisco � um componente coringa, que ira ligar todos os componentes de registro usados na simula��o. N�o vamos reproduzir a sa�da aqui (cada pacote de eco produz 1265 linhas de sa�da), mas podemos redirecionar esta informa��o para um arquivo e visualiz�-lo depois em um editor de textos,

::

  ./waf --run scratch/myfirst > log.out 2>&1

..
	I personally use this extremely verbose version of logging when I am presented 
	with a problem and I have no idea where things are going wrong.  I can follow the 
	progress of the code quite easily without having to set breakpoints and step 
	through code in a debugger.  I can just edit up the output in my favorite editor
	and search around for things I expect, and see things happening that I don't 
	expect.  When I have a general idea about what is going wrong, I transition into
	a debugger for a fine-grained examination of the problem.  This kind of output 
	can be especially useful when your script does something completely unexpected.
	If you are stepping using a debugger you may miss an unexpected excursion 
	completely.  Logging the excursion makes it quickly visible.


utilizamos uma vers�o extremamente detalhada de registro quando surge um problema e n�o temos ideia do que est� errado. Assim, podemos seguir o andamento do c�digo e depurar o erro. Podemos assim visualizar a sa�da em um editor de texto e procurar por coisas que n�s esperamos e principalmente por coisa que n�o esper�vamos. Quando temos uma ideia geral sobre o que est� acontecendo de errado, usamos um depurador de erros para examinarmos de forma mais detalhada o problema. Este tipo de sa�da pode ser especialmente �til quando nosso `script` faz algo completamente inesperado. Se estivermos depurando o problema passo a passo, podemos nos perder completamente. O registro pode tornar as coisas mais vis�veis.

.. 
	Adding Logging to your Code

Adicionando registros ao C�digo
+++++++++++++++++++++++++++++++

..
	You can add new logging to your simulations by making calls to the log 
	component via several macros.  Let's do so in the ``myfirst.cc`` script we
	have in the ``scratch`` directory.

Podemos adicionar novos registros nas simula��es fazendo chamadas para o componente de registro atrav�s de v�rias macros. Vamos fazer isto em nosso c�digo ``myfirst.cc`` no diret�rio ``scratch``

..
	Recall that we have defined a logging component in that script:

Lembre-se que n�s temos que definir o componente de registro em nosso c�digo:

::

  NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

..
	You now know that you can enable all of the logging for this component by
	setting the ``NS_LOG`` environment variable to the various levels.  Let's
	go ahead and add some logging to the script.  The macro used to add an 
	informational level log message is ``NS_LOG_INFO``.  Go ahead and add one 
	(just before we start creating the nodes) that tells you that the script is 
	"Creating Topology."  This is done as in this code snippet,

Agora que sabemos habilitar todos os registros em v�rios n�veis configurando a vari�vel ``NS_LOG``. Vamos adicionar alguns registros ao c�digo. O macro usado para adicionar uma mensagem ao n�vel de informa��o � ``NS_LOG_INFO``, ent�o vamos adicionar uma mensagem dessas (pouco antes de criar os n�s de rede) que diz que a "Topologia foi Criada". Isto � feito como neste trecho do c�digo,

..
	Open ``scratch/myfirst.cc`` in your favorite editor and add the line,

Abra o arquivo ``scratch/myfirst.cc`` e adicione a linha,

::

  NS_LOG_INFO ("Creating Topology");

..
	right before the lines,

antes das linhas,

::

  NodeContainer nodes;
  nodes.Create (2);

..
	Now build the script using waf and clear the ``NS_LOG`` variable to turn 
	off the torrent of logging we previously enabled:

Agora construa o c�digo usando o Waf e limpe a vari�vel ``NS_LOG`` desabilite o registro que n�s hav�amos habilitado anteriormente: 

::

  ./waf
  export NS_LOG=

..
	Now, if you run the script, 

Agora, se executarmos o c�digo,

::

  ./waf --run scratch/myfirst

..
	you will ``not`` see your new message since its associated logging 
	component (``FirstScriptExample``) has not been enabled.  In order to see your
	message you will have to enable the ``FirstScriptExample`` logging component
	with a level greater than or equal to ``NS_LOG_INFO``.  If you just want to 
	see this particular level of logging, you can enable it by, 

veremos novas mensagens, pois o componente de registro n�o est� habilitado. Agora para ver a mensagem devemos habilitar o componente de registro do ``FirstScriptExample`` com um n�vel maior ou igual a ``NS_LOG_INFO``. Se s� esperamos ver um n�vel particular de registro, devemos habilita-lo,

::

  export NS_LOG=FirstScriptExample=info

..
	If you now run the script you will see your new "Creating Topology" log
	message,

Agora se executarmos o c�digo veremos nossa mensagem de registro "Creating Topology",

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.404s)
  Creating Topology
  Sent 1024 bytes to 10.1.1.2
  Received 1024 bytes from 10.1.1.1
  Received 1024 bytes from 10.1.1.2

.. 
	Using Command Line Arguments

Usando Argumentos na Linha de Comando
*************************************

.. 
	Overriding Default Attributes

Sobrepondo Atributos Padr�es
+++++++++++++++++++++++++++++

..
	Another way you can change how |ns3| scripts behave without editing
	and building is via *command line arguments.*  We provide a mechanism to 
	parse command line arguments and automatically set local and global variables
	based on those arguments.

Podemos alterar o comportamento dos c�digos do |ns3| sem precisar editar ou construir c�digos, isto � feito atrav�s de linhas de comandos. Para isto o |ns3| fornece um mecanismo de analise de argumentos de linha de comando (`parse`), que configura automaticamente vari�veis locais e globais atrav�s desses argumentos.

..
	The first step in using the command line argument system is to declare the
	command line parser.  This is done quite simply (in your main program) as
	in the following code,

O primeiro passo para usar argumentos de linha de comando � declarar o analisador de linha de comandos. Isto � feito com a seguinte linha de programa��o, em seu programa principal,

::

  int
  main (int argc, char *argv[])
  {
    ...  

    CommandLine cmd;
    cmd.Parse (argc, argv);

    ...
  }

..
	This simple two line snippet is actually very useful by itself.  It opens the
	door to the |ns3| global variable and ``Attribute`` systems.  Go 
	ahead and add that two lines of code to the ``scratch/myfirst.cc`` script at
	the start of ``main``.  Go ahead and build the script and run it, but ask 
	the script for help in the following way,

Estas duas linhas de programa��o s�o muito uteis. Isto abre uma porta para as vari�veis globais e atributos do |ns3|. Adicione estas duas linhas no c�digo em nosso exemplo ``scratch/myfirst.cc``, bem no inicio da fun��o principal (``main``). Na sequencia construa o c�digo e execute-o, mas pe�a para o c�digo "ajudar" da seguinte forma,

::

  ./waf --run "scratch/myfirst --PrintHelp"

..
	This will ask Waf to run the ``scratch/myfirst`` script and pass the command
	line argument ``--PrintHelp`` to the script.  The quotes are required to 
	sort out which program gets which argument.  The command line parser will
	now see the ``--PrintHelp`` argument and respond with,

Isto pede ao Waf para executar o ``scratch/myfirst`` e passa via linha de comando o argumento ``--PrintHelp``. As aspas s�o necess�rias para ordenar os argumentos. O analisador de linhas de comandos agora tem como argumento o ``--PrintHelp`` e responde com,

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.413s)
  TcpL4Protocol:TcpStateMachine()
  CommandLine:HandleArgument(): Handle arg name=PrintHelp value=
  --PrintHelp: Print this help message.
  --PrintGroups: Print the list of groups.
  --PrintTypeIds: Print all TypeIds.
  --PrintGroup=[group]: Print all TypeIds of group.
  --PrintAttributes=[typeid]: Print all attributes of typeid.
  --PrintGlobals: Print the list of globals.

..
	Let's focus on the ``--PrintAttributes`` option.  We have already hinted
	at the |ns3| ``Attribute`` system while walking through the 
	``first.cc`` script.  We looked at the following lines of code,

Vamos focar na op��o ``--PrintAttributes``. J� demos a dica sobre atributos no |ns3| enquanto explor�vamos o c�digo do ``first.cc``. N�s olhamos as seguintes linhas de c�digo,

::

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
    pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

..
	and mentioned that ``DataRate`` was actually an ``Attribute`` of the 
	``PointToPointNetDevice``.  Let's use the command line argument parser
	to take a look at the ``Attributes`` of the PointToPointNetDevice.  The help
	listing says that we should provide a ``TypeId``.  This corresponds to the
	class name of the class to which the ``Attributes`` belong.  In this case it
	will be ``ns3::PointToPointNetDevice``.  Let's go ahead and type in,

e mencionamos que ``DataRate`` � um atributo de ``PointToPointNetDevice``. Vamos usar os argumentos de linha de comando para ver os atributos de ``PointToPointNetDevice``. A lista de ajuda diz que n�s devemos fornecer um ``TypeId``, este corresponde ao nome da classe do atributo. Neste caso ser� ``ns3::PointToPointNetDevice``. Seguindo em frente digite,

::

  ./waf --run "scratch/myfirst --PrintAttributes=ns3::PointToPointNetDevice"

..
	The system will print out all of the ``Attributes`` of this kind of net device.
	Among the ``Attributes`` you will see listed is,

O sistema ir� mostrar todos os atributos dos tipos de dispositivos de rede (`net device`). Entre os atributos veremos, 

::

  --ns3::PointToPointNetDevice::DataRate=[32768bps]:
    The default data rate for point to point links

..
	This is the default value that will be used when a ``PointToPointNetDevice``
	is created in the system.  We overrode this default with the ``Attribute``
	setting in the ``PointToPointHelper`` above.  Let's use the default values 
	for the point-to-point devices and channels by deleting the 
	``SetDeviceAttribute`` call and the ``SetChannelAttribute`` call from 
	the ``myfirst.cc`` we have in the scratch directory.

.. 
	>> rever revis�o

32768 bits por segundos � o valor padr�o que ser� usado quando criarmos um ``PointToPointNetDevice`` no sistema. Vamos alterar este valor padr�o do ``PointToPointHelper``. Para isto iremos usar os valores dos dispositivos ponto-a-ponto e dos canais, deletando a chamada ``SetDeviceAttribute`` e ``SetChannelAttribute`` do ``myfirst.cc``, que n�s temos no diret�rio ``scratch``.

..
	Your script should now just declare the ``PointToPointHelper`` and not do 
	any ``set`` operations as in the following example,

Nosso c�digo agora deve apenas declarar o ``PointToPointHelper`` sem configurar qualquer opera��o, como no exemplo a seguir,

::

  ...

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  ...

..
	Go ahead and build the new script with Waf (``./waf``) and let's go back 
	and enable some logging from the UDP echo server application and turn on the 
	time prefix.

Agora construa o novo c�digo com o Waf (``./waf``) e depois vamos habilitar alguns registros para o servidor de eco UDP e ligar o prefixo de informa��es sobre tempo de execu��o.

::

  export 'NS_LOG=UdpEchoServerApplication=level_all|prefix_time'

..
	If you run the script, you should now see the following output,

Agora ao executar o c�digo veremos a seguinte sa�da,

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.405s)
  0s UdpEchoServerApplication:UdpEchoServer()
  1s UdpEchoServerApplication:StartApplication()
  Sent 1024 bytes to 10.1.1.2
  2.25732s Received 1024 bytes from 10.1.1.1
  2.25732s Echoing packet
  Received 1024 bytes from 10.1.1.2
  10s UdpEchoServerApplication:StopApplication()
  UdpEchoServerApplication:DoDispose()
  UdpEchoServerApplication:~UdpEchoServer()

..
	Recall that the last time we looked at the simulation time at which the packet
	was received by the echo server, it was at 2.00369 seconds.

Lembre-se que o �ltimo tempo que vimos na simula��o quando recebemos um pacote de eco no servidor, foi de 2.00369 segundos.

::

  2.00369s UdpEchoServerApplication:HandleRead(): Received 1024 bytes from 10.1.1.1

..
	Now it is receiving the packet at 2.25732 seconds.  This is because we just dropped
	the data rate of the ``PointToPointNetDevice`` down to its default of 
	32768 bits per second from five megabits per second.

Agora o pacote � recebido em 2.25732 segundos. Isto porque retiramos a taxa de transfer�ncia do ``PointToPointNetDevice`` e portanto foi assumido o valor padr�o 32768 bits por segundos ao inv�s de cinco megabits por segundo.

..
	If we were to provide a new ``DataRate`` using the command line, we could 
	speed our simulation up again.  We do this in the following way, according to
	the formula implied by the help item:

Se n�s passarmos uma nova taxa de dados usando a linha de comando, podemos aumentar a velocidade da rede novamente. N�s podemos fazer isto da seguinte forma, usando um `help`:

::

  ./waf --run "scratch/myfirst --ns3::PointToPointNetDevice::DataRate=5Mbps"

..
	This will set the default value of the ``DataRate`` ``Attribute`` back to 
	five megabits per second.  Are you surprised by the result?  It turns out that
	in order to get the original behavior of the script back, we will have to set 
	the speed-of-light delay of the channel as well.  We can ask the command line 
	system to print out the ``Attributes`` of the channel just like we did for
	the net device:

Isto ira configurar o valor do atributo ``DataRate`` para cinco megabits por segundos. Ficou surpreso com o resultado? Acontece que para obtermos o resultado do c�digo original, teremos que configurar tamb�m o atraso do canal de comunica��o. Podemos fazer isto via linha de comandos, tal como fizemos com o dispositivo de rede:

::

  ./waf --run "scratch/myfirst --PrintAttributes=ns3::PointToPointChannel"

..
	We discover the ``Delay`` ``Attribute`` of the channel is set in the following
	way:

Ent�o descobrimos que o atributo ``Delay`` do canal esta configurado com o seguinte valor padr�o:

::

  --ns3::PointToPointChannel::Delay=[0ns]:
    Transmission delay through the channel

..
	We can then set both of these default values through the command line system,

Podemos configurar ambos valores via linha de comando,

::

  ./waf --run "scratch/myfirst
    --ns3::PointToPointNetDevice::DataRate=5Mbps
    --ns3::PointToPointChannel::Delay=2ms"

..
	in which case we recover the timing we had when we explicitly set the
	``DataRate`` and ``Delay`` in the script:

neste caso voltamos com os tempos de ``DataRate`` e ``Delay`` que t�nhamos inicialmente no c�digo original:

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.417s)
  0s UdpEchoServerApplication:UdpEchoServer()
  1s UdpEchoServerApplication:StartApplication()
  Sent 1024 bytes to 10.1.1.2
  2.00369s Received 1024 bytes from 10.1.1.1
  2.00369s Echoing packet
  Received 1024 bytes from 10.1.1.2
  10s UdpEchoServerApplication:StopApplication()
  UdpEchoServerApplication:DoDispose()
  UdpEchoServerApplication:~UdpEchoServer()

..
	Note that the packet is again received by the server at 2.00369 seconds.  We 
	could actually set any of the ``Attributes`` used in the script in this way.
	In particular we could set the ``UdpEchoClient Attribute MaxPackets`` 
	to some other value than one.

Repare que o pacote � recebido novamente pelo servidor com 2.00369 segundos. Ent�o desta forma, podemos configurar qualquer atributo usado no c�digo. Em particular n�s podemos configurar o atributo ``MaxPackets`` do ``UdpEchoClient`` para qualquer outro valor.

..
	How would you go about that?  Give it a try.  Remember you have to comment 
	out the place we override the default ``Attribute`` and explicitly set 
	``MaxPackets`` in the script.  Then you have to rebuild the script.  You 
	will also have to find the syntax for actually setting the new default attribute
	value using the command line help facility.  Once you have this figured out 
	you should be able to control the number of packets echoed from the command 
	line.  Since we're nice folks, we'll tell you that your command line should 
	end up looking something like,

� importante lembrar que devemos retirar todas as configura��es com valores expl�citos do c�digo. Depois disto devemos re-construir o c�digo (fazer novamente os bin�rios). Tamb�m teremos que achar a sintaxe do atributo usando o `help` da linha de comando. Uma vez que tenhamos este cen�rio estaremos aptos para controlar o n�meros de pacotes ecoados via linha de comando. No final a linha de comando deve parecer com algo como:

::

  ./waf --run "scratch/myfirst 
    --ns3::PointToPointNetDevice::DataRate=5Mbps 
    --ns3::PointToPointChannel::Delay=2ms 
    --ns3::UdpEchoClient::MaxPackets=2"

.. 
	Hooking Your Own Values

.. 
	>> rever tradu��o de Hooking neste contexto

Conectando Seus Pr�prios Valores
++++++++++++++++++++++++++++++++
..
	You can also add your own hooks to the command line system.  This is done
	quite simply by using the ``AddValue`` method to the command line parser.

Podemos tamb�m adicionar conectores (op��es que alteram valores de vari�veis) ao sistema de linha de comando. Isto nada mais � do que criar uma op��o na linha de comando, a qual permitir� a configura��o de uma vari�vel dentro do c�digo. Isto � feito usando o m�todo ``AddValue`` no analisador da linha de comando.

..
	Let's use this facility to specify the number of packets to echo in a 
	completely different way.  Let's add a local variable called ``nPackets``
	to the ``main`` function.  We'll initialize it to one to match our previous 
	default behavior.  To allow the command line parser to change this value, we
	need to hook the value into the parser.  We do this by adding a call to 
	``AddValue``.  Go ahead and change the ``scratch/myfirst.cc`` script to
	start with the following code,

Vamos usar esta facilidade para especificar o n�mero de pacotes de eco de uma forma completamente diferente. Iremos adicionar uma vari�vel local chamada ``nPackets`` na fun��o ``main``. Vamos iniciar com nosso valor anterior. Para permitir que a linha de comando altere este valor, precisamos fixar o valor no `parser`. Fazemos isto adicionando uma chamada para ``AddValue``. Altere o c�digo ``scratch/myfirst.cc`` come�ando pelo seguinte trecho de c�digo,

::

  int
  main (int argc, char *argv[])
  {
    uint32_t nPackets = 1;

    CommandLine cmd;
    cmd.AddValue("nPackets", "Number of packets to echo", nPackets);
    cmd.Parse (argc, argv);

    ...

..
	Scroll down to the point in the script where we set the ``MaxPackets``
	``Attribute`` and change it so that it is set to the variable ``nPackets``
	instead of the constant ``1`` as is shown below.

D� uma olhada um pouco mais para baixo, no c�digo e veja onde configuramos o atributo ``MaxPackets``, retire o ``1`` e coloque em seu lugar a vari�vel ``nPackets``, como � mostrado a seguir:

::

  echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));

..
	Now if you run the script and provide the ``--PrintHelp`` argument, you 
	should see your new ``User Argument`` listed in the help display.

Agora se executarmos o c�digo e fornecermos o argumento ``--PrintHelp``, deveremos ver nosso argumento de usu�rio (`User Arguments`), listado no `help`.

..
	Try,

Execute,

::

  ./waf --run "scratch/myfirst --PrintHelp"

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.403s)
  --PrintHelp: Print this help message.
  --PrintGroups: Print the list of groups.
  --PrintTypeIds: Print all TypeIds.
  --PrintGroup=[group]: Print all TypeIds of group.
  --PrintAttributes=[typeid]: Print all attributes of typeid.
  --PrintGlobals: Print the list of globals.
  User Arguments:
      --nPackets: Number of packets to echo

..
	If you want to specify the number of packets to echo, you can now do so by
	setting the ``--nPackets`` argument in the command line,

Agora para especificar o n�mero de pacotes de eco podemos utilizar o argumento ``--nPackets`` na linha de comando, 

::

  ./waf --run "scratch/myfirst --nPackets=2"

..
	You should now see

Agora deveremos ver,

::

  Waf: Entering directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  Waf: Leaving directory `/home/craigdo/repos/ns-3-allinone/ns-3-dev/build'
  'build' finished successfully (0.404s)
  0s UdpEchoServerApplication:UdpEchoServer()
  1s UdpEchoServerApplication:StartApplication()
  Sent 1024 bytes to 10.1.1.2
  2.25732s Received 1024 bytes from 10.1.1.1
  2.25732s Echoing packet
  Received 1024 bytes from 10.1.1.2
  Sent 1024 bytes to 10.1.1.2
  3.25732s Received 1024 bytes from 10.1.1.1
  3.25732s Echoing packet
  Received 1024 bytes from 10.1.1.2
  10s UdpEchoServerApplication:StopApplication()
  UdpEchoServerApplication:DoDispose()
  UdpEchoServerApplication:~UdpEchoServer()

..
	You have now echoed two packets.  Pretty easy, isn't it?

Agora, ecoamos dois pacotes. Muito f�cil, n�o �?

..
	You can see that if you are an |ns3| user, you can use the command 
	line argument system to control global values and ``Attributes``.  If you are
	a model author, you can add new ``Attributes`` to your ``Objects`` and 
	they will automatically be available for setting by your users through the
	command line system.  If you are a script author, you can add new variables to 
	your scripts and hook them into the command line system quite painlessly.

Usando o |ns3|, podemos usar argumentos via linha de comando para controlar valores de atributos. Ao construir modelos de simula��o podemos adicionar novos atributos aos objetos e isto ficar� dispon�vel, automaticamente para ajustes atrav�s do sistema via linha de comando. Ao criarmos nossos c�digos poderemos adicionar novas vari�veis e conect�-las ao sistema de forma simples.

.. 
	Using the Tracing System

Usando o Sistema de Rastreamento
********************************

..
	The whole point of simulation is to generate output for further study, and 
	the |ns3| tracing system is a primary mechanism for this.  Since 
	|ns3| is a C++ program, standard facilities for generating output 
	from C++ programs could be used:  

O ponto principal da simula��o � gerar informa��es de sa�da para estudos futuros e o sistema de rastreamento (`Tracing System`) do |ns3| � o mecanismo prim�rio para isto. Devido ao fato do |ns3| ser um programa escrito em C++, as funcionalidades para se gerar sa�das podem ser utilizadas:

::

  #include <iostream>
  ...
  int main ()
  {
    ...
    std::cout << "The value of x is " << x << std::endl;
    ...
  } 

..
	You could even use the logging module to add a little structure to your 
	solution.  There are many well-known problems generated by such approaches
	and so we have provided a generic event tracing subsystem to address the 
	issues we thought were important.

Podemos usar o m�dulo de registro (visto anteriormente) para verificar pequenas estruturas de nossas solu��es. Por�m, os problemas gerados por esta abordagem j� s�o bem conhecidos e portanto fornecemos um subsistema para rastrear eventos gen�ricos para localizar problemas importantes.

..
	The basic goals of the |ns3| tracing system are:

Os objetivos b�sicos do sistema de rastreamento |ns3| s�o:

..
	* For basic tasks, the tracing system should allow the user to generate 
	  standard tracing for popular tracing sources, and to customize which objects
	  generate the tracing;
	* Intermediate users must be able to extend the tracing system to modify
	  the output format generated, or to insert new tracing sources, without 
	  modifying the core of the simulator;
	* Advanced users can modify the simulator core to add new tracing sources
	  and sinks.

* Para as tarefas b�sicas, o sistemas de rastreamento fornece ao usu�rio um rastreamento padr�o atrav�s de rastreamentos conhecidos e customiza��o dos objetos que geram o rastreamento;
* Os usu�rios podem estender o sistema de rastreamento para modificar os formatos das sa�das geradas ou inserir novas fontes de rastreamento, sem modificar o n�cleo do simulador;
* Usu�rios avan�ados podem modificar o n�cleo do simulador para adicionar novas origens de rastreamentos e destino do rastreamento.

..
	The |ns3| tracing system is built on the concepts of independent 
	tracing sources and tracing sinks, and a uniform mechanism for connecting
	sources to sinks.  Trace sources are entities that can signal events that
	happen in a simulation and provide access to interesting underlying data. 
	For example, a trace source could indicate when a packet is received by a net
	device and provide access to the packet contents for interested trace sinks.


O sistema de rastreamento do |ns3| � feito atrav�s de conceitos independentes de rasteamento na origem e no destino, e um mecanismo uniforme para conectar a origem ao destino. O rastreador na origem s�o entidades que podem demonstrar eventos que ocorrem na simula��o e fornece acesso aos dados importantes. Por exemplo, um rastreador de origem podem indicar quando um pacote � recebido por um dispositivo de rede e prove acesso aos coment�rios de pacote para os interessados no rastreador do destino.

..
	Trace sources are not useful by themselves, they must be "connected" to
	other pieces of code that actually do something useful with the information 
	provided by the sink.  Trace sinks are consumers of the events and data
	provided by the trace sources.  For example, one could create a trace sink 
	that would (when connected to the trace source of the previous example) print 
	out interesting parts of the received packet.

Os rastreadores de origem n�o s�o usados sozinhos, eles devem ser "conectados" a outros peda�os de c�digo que fazem alguma coisa �til com a informa��o fornecida pelo destino. Rastreador de destino s�o consumidores dos eventos e dados fornecidos pelos rastreadores de origem. Por exemplo, pode-se criar um rastreador de destino que (quando conectado ao rastreador de origem do exemplo anterior) mostrar� sa�das de partes importantes de pacotes recebidos.

..
	The rationale for this explicit division is to allow users to attach new
	types of sinks to existing tracing sources, without requiring editing and 
	recompilation of the core of the simulator.  Thus, in the example above, 
	a user could define a new tracing sink in her script and attach it to an 
	existing tracing source defined in the simulation core by editing only the 
	user script.

A l�gica desta divis�o explicita � permitir que os usu�rios apliquem novos tipos de rastreadores de destinos em rastreadores de origem existentes, sem precisar editar ou recompilar o n�cleo do simulador. Assim, no exemplo anterior, o usu�rio pode definir um novo rastreador de destino em seu c�digo e aplicar isto a um rastreador de origem definido no n�cleo da simula��o editando, para isto, somente o c�digo do usu�rio.

..
	In this tutorial, we will walk through some pre-defined sources and sinks and
	show how they may be customized with little user effort.  See the ns-3 manual
	or how-to sections for information on advanced tracing configuration including
	extending the tracing namespace and creating new tracing sources.

Neste tutorial, abordamos alguns rastreadores de origem e de destino j� predefinidos e demonstramos como esses podem ser customizados, com um pouco de esfor�o. Veja o manual do ns-3 ou a se��o de `how-to` para informa��es avan�adas sobre configura��o de rastreamento incluindo extens�o do `namespace` de rastreamento e cria��o de novos rastreadores de origem.

.. 
	ASCII Tracing

Rastreamento ASCII
++++++++++++++++++

..
	|ns3| provides helper functionality that wraps the low-level tracing
	system to help you with the details involved in configuring some easily 
	understood packet traces.  If you enable this functionality, you will see
	output in a ASCII files --- thus the name.  For those familiar with 
	|ns2| output, this type of trace is analogous to the ``out.tr``
	generated by many scripts.

O |ns3| fornece uma funcionalidade de ajuda (`helper`) que cobre rastreamento em baixo n�vel e ajuda com detalhes envolvendo configura��o e rastros de pacotes. Se habilitarmos essa funcionalidade, veremos as sa�das em arquivos ASCII (texto puro) --- da� o nome. Isto � parecido com a sa�da do |ns2|. Este tipo de rastreamento � parecido com o ``out.tr`` gerado por outros c�digos.

..
	Let's just jump right in and add some ASCII tracing output to our 
	``scratch/myfirst.cc`` script.  Right before the call to 
	``Simulator::Run ()``, add the following lines of code:

Vamos adicionar algumas sa�das de rastreamento ASCII em nosso c�digo ``scratch/myfirst.cc``. Antes de chamar ``Simulator::Run ()`` adicione as seguintes linhas de c�digo:

::

  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("myfirst.tr"));

..
	Like in many other |ns3| idioms, this code uses a  helper object to 
	help create ASCII traces.  The second line contains two nested method calls.  
	The "inside" method, ``CreateFileStream()`` uses an unnamed object idiom
	to create a file stream object on the stack (without an object  name) and pass
	it down to the called method.  We'll go into this more in the future, but all
	you have to know at this point is that you are creating an object representing
	a file named "myfirst.tr" and passing it into ``ns-3``.  You are telling 
	``ns-3`` to deal with the lifetime issues of the created object and also to 
	deal with problems caused by a little-known (intentional) limitation of C++ 
	ofstream objects relating to copy constructors. 

.. 
	>> rever tradu��o no final o que � ofstream?

Tal como j� vimos no |ns3|, este c�digo usa o objeto Assistente para criar o rastreador ASCII. A segunda linha aninhada duas chamadas para m�todos. Dentro do m�todo ``CreateFileStream()`` � utilizado um objeto para criar um outro objeto, que trata um arquivo, que � passado para o m�todo. Iremos detalhar isto depois, agora tudo que precisamos saber � que estamos criando um objeto que representa um arquivo chamado "myfirst.tr". Estamos dizendo para o ``ns-3`` tratar problemas de cria��o de objetos e tamb�m para tratar problemas causados por limita��es do C++ com objetos relacionados com c�pias de construtores.

..
	The outside call, to ``EnableAsciiAll()``, tells the helper that you 
	want to enable ASCII tracing on all point-to-point devices in your simulation; 
	and you want the (provided) trace sinks to write out information about packet 
	movement in ASCII format.

Fora da chamada, para ``EnableAsciiAll()``, dizemos para o Assistente que esperamos habilitar o rastreamento ASCII para todo dispositivo ponto-a-ponto da simula��o; e esperamos rastrear destinos e escrever as informa��es de sa�da sobre o movimento de pacotes no formato ASCII.

..
	For those familiar with |ns2|, the traced events are equivalent to 
	the popular trace points that log "+", "-", "d", and "r" events.

Para queles familiarizados com |ns2|, os eventos rastreados s�o equivalentes aos populares pontos de rastreadores (`trace points`) que registram eventos "+", "-", "d", e "r"  

..
	You can now build the script and run it from the command line:

Agora podemos construir o c�digo e executa-lo:

::

  ./waf --run scratch/myfirst

..
	Just as you have seen many times before, you will see some messages from Waf and then
	"'build' finished successfully" with some number of messages from 
	the running program.  

Veremos algumas mensagens do Waf, seguida da mensagem "'build' finished successfully", bem como algumas mensagens do programa.

..
	When it ran, the program will have created a file named ``myfirst.tr``.  
	Because of the way that Waf works, the file is not created in the local 
	directory, it is created at the top-level directory of the repository by 
	default.  If you want to control where the traces are saved you can use the 
	``--cwd`` option of Waf to specify this.  We have not done so, thus we 
	need to change into the top level directory of our repo and take a look at 
	the ASCII trace file ``myfirst.tr`` in your favorite editor.

Quando isto for executado, o programa criar� um arquivo chamado ``myfirst.tr``. Devido a forma que o Waf trabalha, o arquivo n�o � criado no diret�rio local, mas sim no diret�rio raiz do reposit�rio. Se voc� espera controlar o que � salvo, ent�o use a op��o ``-cwd`` do Waf. Agora mude para o diret�rio raiz do reposit�rio e veja o arquivo ``myfirst.tr`` com um editor de texto.

.. 
	Parsing Ascii Traces

An�lise de Rastros ASCII
~~~~~~~~~~~~~~~~~~~~~~~~
..
	There's a lot of information there in a pretty dense form, but the first thing
	to otice is that there are a number of distinct lines in this file.  It may
	be difficult to see this clearly unless you widen your window considerably.

Uma grande quantidade de informa��o � gerada pelo sistema de rastreamento e pode ser dif�cil analis�-las de forma clara e consistente.

..
	Each line in the file corresponds to a *trace event*.  In this case
	we are tracing events on the *transmit queue* present in every 
	point-to-point net device in the simulation.  The transmit queue is a queue 
	through which every packet destined for a point-to-point channel must pass.
	Note that each line in the trace file begins with a lone character (has a 
	space after it).  This character will have the following meaning:

Cada linha do arquivo corresponde a um evento de rastreamento (`trace event`). Neste caso s�o eventos rastreados da fila de transmiss�o (`transmit queue`). A fila de transmiss�o � um lugar atrav�s do qual todo pacote destinado para o canal ponto-a-ponto deve passar. Note que cada linha no arquivo inicia com um �nico caractere (com um espa�o depois). Este caractere tem o seguinte significado:

..
	* ``+``: An enqueue operation occurred on the device queue;
	* ``-``: A dequeue operation occurred on the device queue;
	* ``d``: A packet was dropped, typically because the queue was full;
	* ``r``: A packet was received by the net device.

* ``+``: Uma opera��o de enfileiramento (bloqueio) ocorreu no dispositivo de fila;
* ``-``: Uma opera��o de desenfileiramento (desbloqueio) ocorre no dispositivo de fila;
* ``d``: Um pacote foi descartado, normalmente por que a fila est� cheia;
* ``r``: Um pacote foi recebido por um dispositivo de rede.

..
	Let's take a more detailed view of the first line in the trace file.  I'll 
	break it down into sections (indented for clarity) with a two digit reference
	number on the left side:

Vamos detalhar mais a primeira linha do arquivo de rastreamento. Vamos dividi-la em se��es com n�meros de dois d�gitos para refer�ncia:

::

  00 + 
  01 2 
  02 /NodeList/0/DeviceList/0/$ns3::PointToPointNetDevice/TxQueue/Enqueue 
  03 ns3::PppHeader (
  04   Point-to-Point Protocol: IP (0x0021)) 
  05   ns3::Ipv4Header (
  06     tos 0x0 ttl 64 id 0 protocol 17 offset 0 flags [none] 
  07     length: 1052 10.1.1.1 > 10.1.1.2)
  08     ns3::UdpHeader (
  09       length: 1032 49153 > 9) 
  10       Payload (size=1024)

..
	The first line of this expanded trace event (reference number 00) is the 
	operation.  We have a ``+`` character, so this corresponds to an
	*enqueue* operation on the transmit queue.  The second line (reference 01)
	is the simulation time expressed in seconds.  You may recall that we asked the 
	``UdpEchoClientApplication`` to start sending packets at two seconds.  Here
	we see confirmation that this is, indeed, happening.

A primeira linha do evento expandido (refer�ncia n�mero 00) � a opera��o. Temos um caractere ``+``, que corresponde a uma opera��o de enfileiramento na fila de transmiss�o. A segunda linha (refer�ncia 01) � o tempo da simula��o em segundos. Lembre-se que pedimos ao ``UdpEchoClientApplication`` para iniciar o envio de pacotes depois de dois segundos (aqui podemos confirmar que isto est� acontecendo).

..
	The next line of the example trace (reference 02) tell us which trace source
	originated this event (expressed in the tracing namespace).  You can think
	of the tracing namespace somewhat like you would a filesystem namespace.  The 
	root of the namespace is the ``NodeList``.  This corresponds to a container
	managed in the |ns3| core code that contains all of the nodes that are
	created in a script.  Just as a filesystem may have directories under the 
	root, we may have node numbers in the ``NodeList``.  The string 
	``/NodeList/0`` therefore refers to the zeroth node in the ``NodeList``
	which we typically think of as "node 0".  In each node there is a list of 
	devices that have been installed.  This list appears next in the namespace.
	You can see that this trace event comes from ``DeviceList/0`` which is the 
	zeroth device installed in the node. 

A pr�xima linha do exemplo (refer�ncia 02) diz qual rastreador de origem iniciou este evento (expressado pelo `namespace` de rastreamento). Podemos pensar no `namespace` do rastreamento como algo parecido com um sistema de arquivos. A raiz do `namespace` � o ``NodeList``. Este corresponde a um gerenciador de `container` no n�cleo |ns3| que cont�m todos os n�s de rede que foram criados no c�digo. Assim, como um sistema de arquivos pode ter diret�rios dentro da raiz, podemos ter n�s de rede no ``NodeList``. O texto ``/NodeList/0`` desta forma refere-se ao n� de rede 0 (zero) no ``NodeList``, ou seja � o "node 0". Em cada n�s existe uma lista de dispositivos que est�o instalados nestes n�s de rede. Esta lista aparece depois do `namespace`. Podemos ver que este evento de rastreamento vem do ``DeviceList/0`` que � o dispositivo 0 instalado neste n�.

..
	The next string, ``$ns3::PointToPointNetDevice`` tells you what kind of 
	device is in the zeroth position of the device list for node zero.
	Recall that the operation ``+`` found at reference 00 meant that an enqueue 
	operation happened on the transmit queue of the device.  This is reflected in 
	the final segments of the "trace path" which are ``TxQueue/Enqueue``.

O pr�ximo texto, ``$ns3::PointToPointNetDevice`` informa qual � o tipo de dispositivo na posi��o zero da lista de dispositivos para o n� 0 (`node 0`). Lembre-se que a opera��o ``+`` significa que uma opera��o de enfileiramento est� acontecendo na fila de transmiss�o do dispositivo. Isto reflete no segmento final do caminho de rastreamento, que s�o ``TxQueue/Enqueue``.

..
	The remaining lines in the trace should be fairly intuitive.  References 03-04
	indicate that the packet is encapsulated in the point-to-point protocol.  
	References 05-07 show that the packet has an IP version four header and has
	originated from IP address 10.1.1.1 and is destined for 10.1.1.2.  References
	08-09 show that this packet has a UDP header and, finally, reference 10 shows
	that the payload is the expected 1024 bytes.

As linhas restantes no rastreamento devem ser intuitivas. As refer�ncias 03-04 indicam que o pacote � encapsulado pelo protocolo ponto-a-ponto. Referencias 05-07 mostram que foi usado o cabe�alho do IP na vers�o 4, o endere�o IP de origem � o 10.1.1.1 e o destino � o 10.1.1.2. As refer�ncias 08-09 mostram que o pacote tem um cabe�alho UDP e finalmente na refer�ncia 10 � apresentado que a �rea de dados possui 1024 bytes.

..
	The next line in the trace file shows the same packet being dequeued from the
	transmit queue on the same node. 

A pr�xima linha do arquivo de rastreamento mostra que o mesmo pacote inicia o desenfileiramento da fila de transmiss�o do mesmo n� de rede.

..
	The Third line in the trace file shows the packet being received by the net
	device on the node with the echo server. I have reproduced that event below.

A terceira linha no arquivo mostra o pacote sendo recebido pelo dispositivo de rede no n� que representa o servidor de eco. Reproduzimos o evento a seguir.

::

  00 r 
  01 2.25732 
  02 /NodeList/1/DeviceList/0/$ns3::PointToPointNetDevice/MacRx 
  03   ns3::Ipv4Header (
  04     tos 0x0 ttl 64 id 0 protocol 17 offset 0 flags [none]
  05     length: 1052 10.1.1.1 > 10.1.1.2)
  06     ns3::UdpHeader (
  07       length: 1032 49153 > 9) 
  08       Payload (size=1024)

..
	Notice that the trace operation is now ``r`` and the simulation time has
	increased to 2.25732 seconds.  If you have been following the tutorial steps
	closely this means that you have left the ``DataRate`` of the net devices
	and the channel ``Delay`` set to their default values.  This time should 
	be familiar as you have seen it before in a previous section.

A opera��o agora � o ``r`` e o tempo de simula��o foi incrementado para 2.25732 segundos. Se voc� seguiu os passos do tutorial isto significa que temos o tempo padr�o tanto para ``DataRate`` quanto para o ``Delay``. J� vimos este tempo na se��o anterior.

..
	The trace source namespace entry (reference 02) has changed to reflect that
	this event is coming from node 1 (``/NodeList/1``) and the packet reception
	trace source (``/MacRx``).  It should be quite easy for you to follow the 
	progress of the packet through the topology by looking at the rest of the 
	traces in the file.

Na refer�ncia 02, a entrada para o `namespace` foi alterada para refletir o evento vindo do n� 1 (``/NodeList/1``) e o recebimento do pacote no rastreador de origem (``/MacRx``). Isto deve facilitar o acompanhamento dos pacotes atrav�s da topologia, pois basta olhar os rastros no arquivo.

.. 
	PCAP Tracing

Rastreamento PCAP
+++++++++++++++++

..
	The |ns3| device helpers can also be used to create trace files in the
	``.pcap`` format.  The acronym pcap (usually written in lower case) stands
	for packet capture, and is actually an API that includes the 
	definition of a ``.pcap`` file format.  The most popular program that can
	read and display this format is Wireshark (formerly called Ethereal).
	However, there are many traffic trace analyzers that use this packet format.
	We encourage users to exploit the many tools available for analyzing pcap
	traces.  In this tutorial, we concentrate on viewing pcap traces with tcpdump.

Tamb�m podemos usar o formato ``.pcap`` para fazer rastreamento no |ns3|. O pcap (normalmente escrito em letras min�sculas) permite a captura de pacotes e � uma API que inclui a descri��o de um arquivo no formato ``.pcap``. O programa mais conhecido para ler o mostrar este formato � o Wireshark (formalmente chamado de Etherreal). Entretanto, existem muitos analisadores de tr�fego que usam este formato. N�s encorajamos que os usu�rios explorem v�rias ferramentas dispon�veis para an�lise do pcap. Neste tutorial nos concentraremos em dar uma r�pida olhada no tcpdump.

..
	The code used to enable pcap tracing is a one-liner.  

O c�digo usado para habilitar o rastreamento pcap consiste de uma linha.

::

  pointToPoint.EnablePcapAll ("myfirst");

..
	Go ahead and insert this line of code after the ASCII tracing code we just 
	added to ``scratch/myfirst.cc``.  Notice that we only passed the string
	"myfirst," and not "myfirst.pcap" or something similar.  This is because the 
	parameter is a prefix, not a complete file name.  The helper will actually 
	create a trace file for every point-to-point device in the simulation.  The 
	file names will be built using the prefix, the node number, the device number
	and a ".pcap" suffix.

Insira esta linha depois do c�digo do rastreamento ASCII, no arquivo ``scratch/myfirst.cc``. Repare que passamos apenas o texto "myfirst" e n�o "myfirst.pcap", isto ocorre por que � um prefixo e n�o um nome de arquivo completo. O assistente ir� criar um arquivo contendo um prefixo e o n�mero do n� de rede, o n�mero de dispositivo e o sufixo ".pcap".

..
	In our example script, we will eventually see files named "myfirst-0-0.pcap" 
	and "myfirst-1-0.pcap" which are the pcap traces for node 0-device 0 and 
	node 1-device 0, respectively.

Em nosso c�digo, n�s iremos ver arquivos chamados "myfirst-0-0.pcap" 
e  "myfirst-1-0.pcap" que s�o rastreamentos pcap do dispositivo 0 do n� 0 e do dispositivo 0 do n� de rede 1, respectivamente.

..
	Once you have added the line of code to enable pcap tracing, you can run the
	script in the usual way:

Uma vez que adicionamos a linha de c�digo que habilita o rastreamento pcap, podemos executar o c�digo da forma habitual:

::

  ./waf --run scratch/myfirst

..
	If you look at the top level directory of your distribution, you should now
	see three log files:  ``myfirst.tr`` is the ASCII trace file we have 
	previously examined.  ``myfirst-0-0.pcap`` and ``myfirst-1-0.pcap``
	are the new pcap files we just generated.  

Se olharmos no diret�rio da distribui��o, veremos agora tr�s novos arquivos de registro: ``myfirst.tr`` que � o arquivo ASCII, que n�s examinamos na se��o anterior. ``myfirst-0-0.pcap`` e ``myfirst-1-0.pcap``, que s�o os novos arquivos pcap gerados.

.. 
	Reading output with tcpdump

Lendo a sa�da com o tcpdump
~~~~~~~~~~~~~~~~~~~~~~~~~~~

..
	The easiest thing to do at this point will be to use ``tcpdump`` to look
	at the ``pcap`` files.  

A forma mais confort�vel de olhar os arquivos pcap � usando o ``tcpdump``.

::

  tcpdump -nn -tt -r myfirst-0-0.pcap
  reading from file myfirst-0-0.pcap, link-type PPP (PPP)
  2.000000 IP 10.1.1.1.49153 > 10.1.1.2.9: UDP, length 1024
  2.514648 IP 10.1.1.2.9 > 10.1.1.1.49153: UDP, length 1024

  tcpdump -nn -tt -r myfirst-1-0.pcap
  reading from file myfirst-1-0.pcap, link-type PPP (PPP)
  2.257324 IP 10.1.1.1.49153 > 10.1.1.2.9: UDP, length 1024
  2.257324 IP 10.1.1.2.9 > 10.1.1.1.49153: UDP, length 1024

..
	You can see in the dump of ``myfirst-0-0.pcap`` (the client device) that the 
	echo packet is sent at 2 seconds into the simulation.  If you look at the
	second dump (``myfirst-1-0.pcap``) you can see that packet being received
	at 2.257324 seconds.  You see the packet being echoed back at 2.257324 seconds
	in the second dump, and finally, you see the packet being received back at 
	the client in the first dump at 2.514648 seconds.

Podemos ver no primeiro `dump` do arquivo ``myfirst-0-0.pcap`` (dispositivo cliente), que o pacote de eco � enviado com dois segundos de simula��o. Olhando o segundo `dump` veremos que o pacote � recebido com 2.257324 segundos. O pacote � ecoado de volta com 2.257324 segundos e finalmente � recebido de volta pelo cliente com 2.514648 segundos.

.. 
	Reading output with Wireshark


Lendo sa�das com o Wireshark
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
..
	If you are unfamiliar with Wireshark, there is a web site available from which
	you can download programs and documentation:  http://www.wireshark.org/.

Podemos obter o Wireshark em http://www.wireshark.org/, bem como sua documenta��o.

..
	Wireshark is a graphical user interface which can be used for displaying these
	trace files.  If you have Wireshark available, you can open each of the trace
	files and display the contents as if you had captured the packets using a
	*packet sniffer*.

O Wireshark � um programa que usa interface gr�fica e pode ser usado para mostrar os arquivos de rastreamento. Com o Wireshark, podemos abrir cada arquivo de rastreamento e visualizar conte�do como se tiv�ssemos capturando os pacotes usando um analisador de tr�fego de redes (`packet sniffer`).
