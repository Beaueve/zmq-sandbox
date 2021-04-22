#include <iostream>
#include <zmq.hpp>
#include <string>
#include <thread>
#include "monitor.h"

using namespace zmq;

int main(int argc, const char **argv)
{

    std::cout << "Hello from server" << std::endl;

    context_t ctx;
    socket_t server(ctx, ZMQ_ROUTER);

    const std::string addr = "tcp://127.0.0.1:5678";

    // Now, try it a different way:
    connect_monitor_t mon2;
    // here, default is ZMQ_EVENT_ALL

    server.bind(addr);
    
    //Monitor sock using the given transport for internal communication
    connect_monitor_t mon;

    //mon.init(server, "inproc://conmon", ZMQ_EVENT_ALL);
    std::thread monitor([&] {
        mon.monitor(server, "inproc://conmon", ZMQ_EVENT_ALL);
    });

    //zmq_socket_monitor(server, "inproc://conmon", ZMQ_EVENT_ALL);

    message_t sender;
    message_t msg;
    server.recv(sender, recv_flags::none);

    server.recv(msg, recv_flags::none);

    std::cout << "Sender: " << sender.to_string() << "\nMessage: " << msg.to_string() << std::endl;
    while (true)
    {
    };

    return 0;
}