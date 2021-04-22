#include <iostream>
#include <zmq.hpp>
#include <string>
#include <thread>

using namespace zmq;

class connect_monitor_t : public zmq::monitor_t
{
public:
    void on_event_connected(const zmq_event_t &event,
                            const char *addr) override
    {
        std::cout << "got connection from " << addr << std::endl;
    }

    void on_event_listening(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "Listening event?" << std::endl;
    }
};

int main(int argc, const char **argv)
{

    std::cout << "Hello from server" << std::endl;

    context_t ctx;
    socket_t server(ctx, ZMQ_ROUTER);

    const std::string addr = "tcp://127.0.0.1:5678";

    // Now, try it a different way:
    connect_monitor_t mon2;
    // here, default is ZMQ_EVENT_ALL


    const int events = ZMQ_EVENT_CONNECTED;
    // Monitor sock using the given transport for internal communication
    connect_monitor_t mon;
    mon.init(server, "inproc://conmon", events);
    std::thread monitor([&] {
        while (true)
        {
            if (!mon.check_event(1000))
            {
                std::cout << "timeout" << std::endl;
            }
            else
            {
                std::cout << "event" << std::endl;
            }
        }
    });

    server.bind(addr);
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