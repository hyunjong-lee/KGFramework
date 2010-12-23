#pragma once

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <list>
#include <set>
#include <vector>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/unordered_map.hpp>

#include "server_interface.h"
#include "client_handler.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

class Server : ServerInterface
{
public:
    Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
        : io_service_(io_service), acceptor_(io_service, endpoint)
    {
        memset(user_positions_, 0, sizeof(double) * USER_COUNTER_MAX * POINT_DIMENSION);
        memset(client_list_, 0, sizeof(ClientHandler *) * USER_COUNTER_MAX);

        client_list_[user_counter_] = new ClientHandler(io_service_, user_counter_, this);
        acceptor_.async_accept(client_list_[user_counter_]->socket(),
            boost::bind(
                &Server::handle_accept,
                this,
                boost::asio::placeholders::error
            )
        );
    }

    void handle_accept(const boost::system::error_code& error)
    {
        if (!error)
        {
            client_list_[user_counter_]->start();
            user_counter_++;

            client_list_[user_counter_] = new ClientHandler(io_service_, user_counter_, this);
            acceptor_.async_accept(client_list_[user_counter_]->socket(),
                boost::bind(
                    &Server::handle_accept,
                    this,
                    boost::asio::placeholders::error
                )
            );
        }
    }

    void update_data_from_client(const std::vector<double>& pos, const int id)
    {
        for(int idx = 0; idx < pos.size(); idx++)
        {
            if(idx >= POINT_DIMENSION) continue;

            user_positions_[id][idx] = pos[idx];
        }
    }

    void deliver_to_clients()
    {
        int size = user_counter_ * POINT_DIMENSION * sizeof(double);
        static BYTE *packetData = new BYTE[1000];

        int tdx = 0;
        for(int idx = 0; idx < user_counter_; idx++)
        {
            std::cout << "User<" << idx << "> START" << std::endl;

            for(int kdx = 0; kdx < POINT_DIMENSION; kdx++)
            {
                std::cout << "Dim" << kdx << ": " << user_positions_[idx][kdx] << std::endl;

                memcpy(packetData + tdx, &(user_positions_[idx][kdx]), sizeof(double));
                tdx += sizeof(double);
            }
            
            std::cout << "User<" << idx << "> END" << std::endl;
        }

        for(int idx = 0; idx < user_counter_; idx++)
        {
            if(client_list_[idx] != NULL)
                client_list_[idx]->deliver(packetData, size);
        }
    }

    void leave_client(unsigned int playerId)
    {
		ClientHandler *pClientHandler = client_list_[playerId];
        client_list_[playerId] = NULL;

		//delete pClientHandler;
    }

    unsigned int get_user_count()
    {
        return user_counter_;
    }

private:
    io_service&     io_service_;
    tcp::acceptor   acceptor_;

    enum{USER_COUNTER_MAX = 100};
    enum{POINT_DIMENSION = 3};

    static unsigned int user_counter_;
    ClientHandler* client_list_[USER_COUNTER_MAX];

    double user_positions_[USER_COUNTER_MAX][POINT_DIMENSION];
};

unsigned int Server::user_counter_ = 0;

typedef boost::shared_ptr<Server> server_ptr;
