#include "serverprocess.h"

#include <boost/thread.hpp>


ServerProcess::ServerProcess()
{
}


ServerProcess::~ServerProcess(void)
{
}

int ServerProcess::run( int argc, char *argv[] )
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: GameServer <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), atoi(argv[1]));
        server_ptr_.reset(new Server(io_service, endpoint));
        boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &io_service));

        boost::asio::io_service io_service_timer;
        boost::asio::deadline_timer timer(io_service_timer, boost::posix_time::seconds(1));
        timer.async_wait(
            boost::bind(
            &ServerProcess::write_position,
            this,
            boost::asio::placeholders::error,
            &timer
            )
            );
        io_service_timer.run();
        io_thread.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

void ServerProcess::write_position( const boost::system::error_code& e, boost::asio::deadline_timer* t )
{
    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(
        boost::bind(
        &ServerProcess::write_position,
        this,
        boost::asio::placeholders::error,
        t
        )
        );

    server_ptr_->deliver_to_clients();

    std::cout << "====================" << std::endl;
    std::cout << "Send Data to clients" << std::endl;
    std::cout << "# Client: " << server_ptr_->get_user_count() << std::endl;
    std::cout << "====================" << std::endl;

    std::cout << std::endl;
}