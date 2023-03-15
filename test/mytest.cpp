//用自己写的muduo
#include<mymuduo/TcpServer.h>
#include<mymuduo/Logger.h>

#include<string>
#include<functional>

//执行autobuild脚本安装mymuduo库，执行当前目录makefile文件进行测试

class TTServer
{
public:
    TTServer(EventLoop *loop,
    const InetAddress &addr,
    const std::string &name):server_(loop,addr,name),loop_(loop)
    {
        //注册回调
        server_.setConnectionCallback(
            std::bind(&TTServer::onConnection,this,std::placeholders::_1));
        server_.setMessageCallback(std::bind(&TTServer::onMessage,this,std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3)); //占位符

        //设置线程
        server_.setThreadNum(4);
    }
    void start(){
        server_.start();
    }
private:
   // 连接建立或者断开的回调
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            LOG_INFO("Connection UP : %s", conn->peerAddress().toIpPort().c_str());
        }
        else
        {
            LOG_INFO("Connection DOWN : %s", conn->peerAddress().toIpPort().c_str());
        }
    }
     // 可读写事件回调
    void onMessage(const TcpConnectionPtr &conn,
                Buffer *buf,
                Timestamp time)
    {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
        conn->shutdown(); // 写端   EPOLLHUP =》 closeCallback_
    }
    EventLoop *loop_;
    TcpServer server_;
};

int main()
{
    EventLoop loop;
    InetAddress addr(8000,"127.0.0.1");//"127.0.0.1"参数可以不用给，默认给的127.0.0.1
    TTServer ss(&loop,addr,"TTServer-01");// Acceptor non-blocking listenfd  create bind 
    ss.start();// listen  loopthread  listenfd => acceptChannel => mainLoop =>
    loop.loop();// 启动mainLoop的底层Poller

    return 0;
}


