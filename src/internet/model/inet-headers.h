#ifndef NS3_INET_HEADERS_H
#define NS3_INET_HEADERS_H


#ifdef __WIN32__
    #pragma comment(lib, "ws2_32.lib")
    #define WIN32_LEAN_AND_MEAN
    #include <winsock2.h>
    //#include <windows.h>
    //Undefine MINGW definitions to prevent collisions
    #undef GetObject
    #undef SetPort
    #undef SendMessage
    #undef CreateFile
    #undef Rectangle
    #undef interface    //MSYS2 defines "interface" as a struct in mingw/include/rpc.h

#else
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#endif //NS3_INET_HEADERS_H
