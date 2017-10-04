.. include:: replace.txt

..
	========================================================================================
	Translated for portuguese by the students of the inter-institutional doctorate program of IME-USP/UTFPR-CM.
	
	Traduzido para o portugu�s pelos alunos do programa de doutorado inter institucional do Instituto de Matem�tica e Estat�stica da Universidade de S�o Paulo --- IME-USP em parceria com a Universidade Tecnol�gica Federal do Paran� - Campus Campo Mour�o --- UTFPR-CM:
	
	* Frank Helbert (frank@ime.usp.br);
	* Luiz Arthur Feitosa dos Santos (luizsan@ime.usp.br);
	* Rodrigo Campiolo (campiolo@ime.usp.br).
	========================================================================================


Introdu��o 
-----------


..
	The |ns3| simulator is a discrete-event network simulator targeted 
	primarily for research and educational use.  The 
	`ns-3 project
	<http://www.nsnam.org>`_, 
	started in 2006, is an open-source project developing |ns3|.

O |ns3| � um simulador de redes baseado em eventos discretos desenvolvido especialmente para pesquisa e uso educacional. O `projeto ns-3 <http://www.nsnam.org>`_ iniciou em 2006 e tem seu c�digo aberto.


..
	The purpose of this tutorial is to introduce new |ns3| users to the 
	system in a structured way.  It is sometimes difficult for new users to
	glean essential information from detailed manuals and to convert this
	information into working simulations.  In this tutorial, we will build 
	several example simulations, introducing and explaining key concepts and
	features as we go.

O objetivo deste tutorial � apresentar o |ns3| de forma estruturada aos usu�rios iniciantes. Algumas vezes torna-se dif�cil obter informa��es b�sicas de manuais detalhados e converter em informa��es �teis para as simula��es. Neste tutorial s�o ilustrados v�rios exemplos de simula��es, introduzindo e explicando os principais conceitos necess�rios ao longo do texto.

..
	As the tutorial unfolds, we will introduce the full |ns3| documentation 
	and provide pointers to source code for those interested in delving deeper
	into the workings of the system.

A documenta��o completa do |ns3| e trechos do c�digo fonte s�o apresentados para os interessados em aprofundar-se no funcionamento do sistema.

.. 
	A few key points are worth noting at the onset:

Alguns pontos importantes para se observar:

.. 
	* Ns-3 is not an extension of `ns-2
	<http://www.isi.edu/nsnam/ns>`_; 
	it is a new simulator.  The two simulators are both written in C++ but 
	|ns3| is a new simulator that does not support the ns-2 APIs.  Some 
	models from ns-2 have already been ported from ns-2 to |ns3|. The 
	project will continue to maintain ns-2 while |ns3| is being built,
	and will study transition and integration mechanisms.

* O |ns3| n�o � uma extens�o do ns-2; O |ns3| � um simulador novo. Ambos s�o escritos em C++, mas o |ns3| � totalmente novo e n�o suporta as APIs da vers�o anterior. Algumas funcionalidades do ns-2 j� foram portadas para o |ns3|. O projeto continuar� mantendo o ns-2 enquanto o |ns3| estiver em fase de desenvolvimento e formas de integra��o e transi��o est�o em estudo.

..
	* |ns3| is open-source, and the project strives to maintain an 
	open  environment for researchers to contribute and share their software. 

* O |ns3| � c�digo aberto e existe um grande esfor�o para manter um ambiente aberto para pesquisadores que queiram contribuir e compartilhar software com o projeto.
 
.. 
	For ns-2 Users

Para os usu�rios do ns-2
*************************

..
	For those familiar with ns-2, the most visible outward change when moving to 
	|ns3| is the choice of scripting language.  Ns-2 is 
	scripted in OTcl and results of simulations can be visualized using the 
	Network Animator nam.  It is not possible to run a simulation
	in ns-2 purely from C++ (i.e., as a main() program without any OTcl).
	Moreover, some components of ns-2 are written in C++ and others in OTcl.
	In |ns3|, the simulator is written entirely in C++, with optional
	Python bindings.  Simulation scripts can therefore be written in C++
	or in Python.  The results of some simulations can be visualized by
	nam, but new animators are under development.  Since |ns3|
	generates pcap packet trace files, other utilities can be used to
	analyze traces as well.
	In this tutorial, we will first concentrate on scripting 
	directly in C++ and interpreting results via trace files.  

Para aqueles familiarizados com o ns-2 a mudan�a mais vis�vel � a escolha da linguagem de codifica��o (*scripting*). O ns-2 utiliza a linguagem OTcl e os resultados das simula��es podem ser visualizados utilizando o *Network Animator - nam*. Entretanto, n�o � poss�vel executar uma simula��o escrita inteira em C++ no ns-2 (por exemplo, com um ``main()`` sem nenhum c�digo OTcl). Assim sendo, no ns-2 alguns componentes s�o escritos em C++ e outros em OTcl. No |ns3|, todo o simulador � escrito em C++ com suporte opcional a Python. Desta forma, os c�digos de simula��o podem ser escritos somente em C++ ou Python. Os resultados de algumas simula��es podem ser visualizados pelo *nam*, mas novas formas de visualiza��o est�o sendo desenvolvidas. O |ns3| gera arquivos de rastreamento de pacotes *(packet trace)* no formato *pcap*, assim, � poss�vel utilizar outras ferramentas para a an�lise de pacotes. Neste tutorial iremos nos concentrar inicialmente nos c�digos de simula��o escritos em C++ e na interpreta��o dos pacotes nos arquivos de rastreamento.

..
	But there are similarities as well (both, for example, are based on C++ 
	objects, and some code from ns-2 has already been ported to |ns3|).
	We will try to highlight differences between ns-2 and |ns3|
	as we proceed in this tutorial.

Tamb�m existem semelhan�as entre o ns-2 e o |ns3|. Ambos, por exemplo, s�o orientados a objeto e parte do c�digo do ns-2 j� foi portado para o |ns3|. As diferen�as entre as vers�es ser�o destacadas ao longo deste tutorial.

..
	A question that we often hear is "Should I still use ns-2 or move to
	|ns3|?"  The answer is that it depends.  |ns3| does not have
	all of the models that ns-2 currently has, but on the other hand, |ns3|
	does have new capabilities (such as handling multiple interfaces on nodes 
	correctly, use of IP addressing and more alignment with Internet
	protocols and designs, more detailed 802.11 models, etc.).  ns-2
	models can usually be ported to |ns3| (a porting guide is under
	development).  There is active development on multiple fronts for 
	|ns3|.  The |ns3| developers believe (and certain early users
	have proven) that |ns3| is ready for active use, and should be an 
	attractive alternative for users looking to start new simulation projects.  

Uma quest�o que frequentemente aparece �: "Eu devo continuar usando o ns-2 ou devo migrar para o |ns3|?". A resposta �: depende. O |ns3| n�o tem todos os modelos do ns-2, contudo, possui novas funcionalidades (tais como: trabalha corretamente com n�s de rede com m�ltiplas interfaces de rede (por exemplo, computadores com v�rias placas de rede), usa endere�amento IP, � mais consistente com arquiteturas e protocolos da Internet, detalha mais o modelo 802.11, etc.). Em todo o caso, os modelos do ns-2 podem ser portados para o |ns3| (um guia est� em desenvolvimento). Atualmente existem v�rias frentes de trabalho para o desenvolvimento do simulador. Os desenvolvedores acreditam (e os primeiros usu�rios concordam) que o |ns3| est� pronto para o uso e � uma �tima alternativa para usu�rios que querem iniciar novos projetos de simula��o.

.. 
	Contributing

Contribuindo
************

.. 
	|ns3| is a research and educational simulator, by and for the 
	research community.  It will rely on the ongoing contributions of the 
	community to develop new models, debug or maintain existing ones, and share 
	results.  There are a few policies that we hope will encourage people to 
	contribute to |ns3| like they have for ns-2:

O |ns3| � um simulador para pesquisas e de uso educacional, feito por e para pesquisadores. Este conta com contribui��es da comunidade para desenvolver novos modelos, corrigir erros ou manter c�digos e compartilhar os resultados. Existem pol�ticas de incentivo para que as pessoas contribuam com o projeto, assim como foi feito no ns-2, tais como:

.. 
	* Open source licensing based on GNU GPLv2 compatibility

* Licen�a de c�digo aberto compat�vel com GNU GPLv2;

* `Wiki	<http://www.nsnam.org/wiki>`_;

.. 
	* `Contributed Code
	<http://www.nsnam.org/wiki/Contributed_Code>`_ page, similar to ns-2's popular Contributed Code
	`page
	<http://nsnam.isi.edu/nsnam/index.php/Contributed_Code>`_ 

* P�gina para `contribui��o com o c�digo <http://www.nsnam.org/wiki/Contributed_Code>`_, similar a p�gina de contribui��o do `ns-2 <http://nsnam.isi.edu/nsnam/index.php/Contributed_Code>`_;

.. 
	* Open `bug tracker
	<http://www.nsnam.org/bugzilla>`_

* `Registro de erros (bugs) <http://www.nsnam.org/bugzilla>`_ aberto.

..
	We realize that if you are reading this document, contributing back to 
	the project is probably not your foremost concern at this point, but
	we want you to be aware that contributing is in the spirit of the project and
	that even the act of dropping us a note about your early experience 
	with |ns3| (e.g. "this tutorial section was not clear..."), 
	reports of stale documentation, etc. are much appreciated. 

Se voc� est� lendo este documento, provavelmente contribuir diretamente n�o seja o foco neste momento, mas esteja ciente que contribuir est� no esp�rito do projeto, mesmo que seja deixando uma mensagem descrevendo suas experi�ncias com o |ns3| (por exemplo, voc� pode relatar qual se��o deste tutorial n�o esta clara), reportar a desatualiza��o da documenta��o, etc. Toda ajuda ser� muita bem vinda.

.. 
	Tutorial Organization

Organiza��o do Tutorial
***********************

..
	The tutorial assumes that new users might initially follow a path such as the
	following:

Este tutorial assume que os novos usu�rios podem iniciar da seguinte forma:

.. 
	* Try to download and build a copy;

* Baixar e compilar uma c�pia do |ns3|;

.. 
	* Try to run a few sample programs;

* Executar alguns programas exemplo;

.. 
	* Look at simulation output, and try to adjust it.

* Analisar as sa�das de simula��o e ajust�-las.

.. 
	As a result, we have tried to organize the tutorial along the above
	broad sequences of events.

Assim, tentamos organizar este tutorial nesta sequ�ncia.
