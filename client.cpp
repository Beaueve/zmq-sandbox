#include <iostream>
#include <thread>
#include <zmq.hpp>
#include "monitor.h"

using namespace zmq;

int main(int argc, const char **argv)
{
    std::cout << "Hello from client" << std::endl;

    context_t ctx;
    socket_t client(ctx, ZMQ_DEALER);
    client.set(sockopt::routing_id, "dealer");
    const std::string addr = "tcp://127.0.0.1:5678";

    //Monitor sock using the given transport for internal communication
    connect_monitor_t mon;

    //mon.init(server, "inproc://conmon", ZMQ_EVENT_ALL);
    std::thread monitor([&] {
        mon.monitor(client, "inproc://conmon", ZMQ_EVENT_ALL);
    });

    client.connect(addr);
    const char *data = "Hello from client";

    message_t msg(data, strlen(data));

    client.send(msg, send_flags::none);

    while (true)
        ;
    client.close();
    return 0;
}