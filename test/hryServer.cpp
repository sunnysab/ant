//
// Created by hry on 2021/6/24.
//

#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main()
{
    //初始化wsa
    WSADATA wsaData;
    //声明调用winsock 2.2版本 第一位副版本 第二位主版本 利用第二个参数返回请求的socket版本信息
    WORD sockVersion= MAKEWORD(2,2);
    /*使用Socket的程序在使用Socket之前必须调用WSAStartup函数
     * windows异步socket的启动命令
     * 通过WSAStartup函数完成对Winsock服务的初始化
     * 第一个参数指明程序请求使用的Socket版本
     * 第二个参数指明指向WSADATA数据结构的指针，用来接收socket实现细节
     */
    if(WSAStartup(sockVersion,&wsaData)!=0)
    {
        return 0;
    }

    /*创建socket
     * 第一个参数是af，是Address Family IP地址类型
     * 有AF_INET和AF_INET6,前者表示IPv4，后者表示IPv6
     * 第二个参数是数据传输方式/socket类型
     * 常用的有SOCK_STREAM(流格式socket/面向连接的)
     * SOCK_DGRAM（数据报socket/无连接的）
     * 第三个参数是传输协议
     * 常用的有IPPROTO_TCP(TCP传输协议)
     * IPPTOTO_UDP（UDP传输协议）
     * INVALID_SOCKET 指无效socket
     */
    SOCKET serSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(serSocket==INVALID_SOCKET)
    {
        cout<<"socket error!";
        return 0;
    }

    //绑定IP和端口
    /*sockaddr_in是一个结构体，来表示地址，区分了IP地址和端口号
     *而sockaddr结构体没有区分地址和端口号
     *sin_port是本机端口号,需要用htons()函数转换
     *INADDR_ANY是指定地址为0.0.0.0的地址（任意地址）
     * bind()是将socket和特定的IP地址和端口绑定
     * 第二个参数将serAddr类型强制转换成sockaddr
     * 第三个参数是确认强制转换不会改变长度(16字节)
     */
    sockaddr_in serAddr;
    serAddr.sin_family=AF_INET;
    serAddr.sin_port= htons(1234);
    serAddr.sin_addr.S_un.S_addr=INADDR_ANY;
    if(bind(serSocket,(sockaddr*)&serAddr,sizeof(serAddr))==SOCKET_ERROR)
    {
        cout<<"bind error!";
        closesocket(serSocket);
        return 0;
    }

    //循环接收数据
    /* 服务器一直保持监听状态
     * 定义一个长度为255的缓冲区
     * recvfrom()函数从（已连接）socket上接收数据，并捕获数据发送源的地址
     * 第一个参数是自己定义的已连接的socket
     * 第二个参数是接收数据的缓冲区recvData
     * 第三个参数是缓冲区的长度
     * 第四个参数是指定要附加的标志位，通常设置为0
     * 第五个参数是指向sockaddr结构体中缓冲区的可选指针，该缓冲区将在返回时保存源地址
     * 第六个参数是一个可选的指针，指向第五个参数指向的缓冲区的大小
     */
    sockaddr_in remoteAddr;
    int nAddrLen = sizeof(remoteAddr);
    while (true)
    {
        char recvData[255];
        int ret = recvfrom(serSocket, recvData, strlen(recvData), 0, (sockaddr *)&remoteAddr, &nAddrLen);
        if (ret > 0)
        {
            //0x00是16进制的写法，含义是0
            //ret是接收数据的长度，我们初始定义的revData长度是255，
            //下面一句话的意思是让超过ret后面的内容为空
            recvData[ret] = 0x00;
            //inet_ntoa()函数将网络地址转换成“.”点隔的字符串格式
            cout<<"收到一个连接:"<<inet_ntoa(remoteAddr.sin_addr)<<endl;
            cout<<recvData;
        }
        char* sendData = "一个来自服务端的UDP数据包\n";
        /*
		sendto(socket s,const char *buf,int flags,const char * to,int tolen)
		用于发送数据，s是发送端套接字描述符，
        buf指定发送端等待发送数据的缓冲区，
		len指定要发送数据的字节数，
		flags指定需要附加的标志位，
        通常flags设置为0,
		to指定存放接收端等待接收数据的缓冲区，
		tolen指定要接收数据的字节数。
		函数执行成功后返回发送数据的字节数，失败后返回socket_error
		*/
        sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);

    }
    //关闭监听的socket,并释放socket所占用的资源
    closesocket(serSocket);
    /*
	卸载winsocket的dll,操作系统会解除应用程序与socket dll 库的绑定，
    并释放socket dll 库所占用的系统资源
	*/
    WSACleanup();
    return 0;
}