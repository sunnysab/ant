//
// Created by hry on 2021/6/24.
//

#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main()
{
    WSADATA wsaData;
    WORD socketVersion = MAKEWORD(2,2);
    if(WSAStartup(socketVersion, &wsaData) != 0)
    {
        return 0;
    }
    SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sclient==INVALID_SOCKET)
    {
        cout<<"socket error!";
        return 0;
    }
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    int len = sizeof(sin);
    char* sendData = "data from client.";
    sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);

    char recvData[255];
    int ret = recvfrom(sclient, recvData, strlen(recvData), 0, (sockaddr *)&sin, &len);
    if(ret > 0)
    {
        recvData[ret] = 0x00;
        cout<<recvData<<endl;
    }
    closesocket(sclient);
    WSACleanup();
    return 0;
}