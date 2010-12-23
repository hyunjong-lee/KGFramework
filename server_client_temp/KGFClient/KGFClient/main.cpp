#include "client.hpp"

#include <iostream>
#include <vector>
#include <ctime>

#include <boost/thread.hpp>


void write_position(const boost::system::error_code& e, boost::asio::deadline_timer* t, Client* client)
{
    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(
        boost::bind(
            write_position,
            boost::asio::placeholders::error,
            t,
            client
        )
    );

    std::vector<double> pos;
    pos.push_back((rand()%10000) / 0.578);
    pos.push_back((rand()%10000) / 0.789);
    pos.push_back((rand()%10000) / 0.124);

    client->write(pos);

    std::cout << "===========" << std::endl;
    std::cout << "Client DATA" << std::endl;
    printf("%.08f\n", pos[0]);
    printf("%.08f\n", pos[1]);
    printf("%.08f\n", pos[2]);
    std::cout << "===========" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        srand(time(0));

        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], argv[2]);
        tcp::resolver::iterator iterator = resolver.resolve(query);

        Client client(io_service, iterator);
        boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &io_service));

        boost::asio::io_service io_service_timer;
        boost::asio::deadline_timer timer(io_service_timer, boost::posix_time::seconds(1));
        timer.async_wait(
            boost::bind(
                write_position,
                boost::asio::placeholders::error,
                &timer,
                &client
            )
        );
        io_service_timer.run();

        client.close();
        io_thread.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;

}
