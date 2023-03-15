#include "InetAddress.h"
#include <strings.h>
#include <string.h>

InetAddress::InetAddress (uint16_t port, std::string ip)
{
    bzero(&addr_, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}
std::string InetAddress::toIp() const
{
    char buff[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buff, sizeof buff);
    return buff;
}
std::string InetAddress::toIpPort() const
{

    char buff[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buff, sizeof buff);
    size_t end = strlen(buff);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buff + end, ":%u", port);
    return buff;
}
uint16_t InetAddress::toPort() const
{
    return ntohs(addr_.sin_port);
}

/*#include <iostream>
int main()
{
    InetAddress addr(8080);
    std::cout << addr.toIpPort() << std::endl;

    return 0;
}*/
