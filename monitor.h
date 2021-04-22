#ifndef MONITOR_HEADER_GUARD
#define MONITOR_HEADER_GUARD
#include <iostream>
#include <zmq.hpp>


class connect_monitor_t : public zmq::monitor_t
{
public:
    void on_event_connected(const zmq_event_t &event,
                            const char *addr) override
    {
        std::cout << "on_event_connected " << addr << std::endl;
    }

    void on_event_connect_delayed(const zmq_event_t &event, const char *addr) override
    {
        std::cout << "on_event_connect_delayed" << std::endl;
    }

    void on_event_listening(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "on_event_listening" << std::endl;
    }

    void on_event_bind_failed(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "on_event_bind_failed" << std::endl;
    }

    void on_event_accepted(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "on_event_accepted" << std::endl;
    }

    void on_event_closed(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "on_event_closed" << std::endl;
    }

    void on_monitor_started() override
    {
        std::cout << "on_monitor_started" << std::endl;
    }

    void on_event_unknown(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "on_event_unknown" << std::endl;
    }

    void on_event_disconnected(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "on_event_disconnected" << std::endl;
    }

    void on_event_connect_retried(const zmq_event_t &event_, const char *addr_) override
    {
        std::cout << "on_event_connect_retried" << std::endl;
    }
};

#endif // !MONITOR_HEADER_GUARD