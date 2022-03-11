#include "epoll_sysutility.h"
#include "tcp_socket.h"
#include "epoll_tcpsocketdescriptor.h"
#include "event_loop.h"

using namespace std;

int main(int argc, char *argv[])
{
    EpollSysUtil ep;

    EventLoop eventLoop(ep);
    TCPSocket tcpSocket(12345);
    tcpSocket.set_nonblocking();
    tcpSocket.make_listen();
    EpollTCPSocketDescriptor tcp_ds(tcpSocket, ep);
    int iters = -1;
//    if iters is negative the loop will run forever, else for
//    the specified number of iterations and then return
    int loop_result = eventLoop.run_forever(iters);
    return loop_result;
}
