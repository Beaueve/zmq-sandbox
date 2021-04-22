#include <iostream>
#include <zmq.hpp>

using namespace zmq;

int main(int argc, const char **argv)
{
    std::cout << "Hello from client" << std::endl;

    context_t ctx;
    socket_t client(ctx, ZMQ_DEALER);
    client.set(sockopt::routing_id, "dealer");
    const std::string addr = "tcp://127.0.0.1:5678";

    client.connect(addr);
    const char * data = "Hello from client";

    message_t msg(data, strlen(data));

    client.send(msg, send_flags::none);

    return 0;
}