#pragma once

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <list>
#include <set>
#include <vector>
#include <ostream>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/unordered_map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "serverinterface.hpp"

using namespace boost::asio::ip;


class ClientHandler
{
public:
    ClientHandler(boost::asio::io_service& io_service, const unsigned int id, ServerInterface* server)
        : socket_(io_service), id_(id), server_interface_(server)
    {
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    unsigned int getId()
    {
        return id_;
    }

    void start()
    {
        boost::asio::async_read(socket_,
            boost::asio::buffer(header_, HEADER_SIZE),
            boost::bind(
            &ClientHandler::handle_read_header,
            this,
            boost::asio::placeholders::error
            )
            );
    }

    void handle_read_header(const boost::system::error_code& error)
    {
        if (!error && decode_header())
        {
            boost::asio::async_read(socket_,
                boost::asio::buffer(payload_, payload_length_),
                boost::bind(
                &ClientHandler::handle_read_body,
                this,
                boost::asio::placeholders::error
                )
                );
        }
        else
        {
            server_interface_->leave_client(id_);
        }
    }

    void handle_read_body(const boost::system::error_code& error)
    {
        if (!error)
        {
            // notice to server that the position of a client is changed
            std::vector<double> pos;

            // get client pos data
            for(int idx = 0; idx < payload_length_ / sizeof(double); idx++)
            {
                double value = 0.0;
                memcpy(&value, payload_ + (idx * sizeof(double)), sizeof(double));
                pos.push_back(value);
            }

            server_interface_->update_data_from_client(pos, id_);

            // wait another read
            boost::asio::async_read(socket_,
                boost::asio::buffer(header_, HEADER_SIZE),
                boost::bind(
                &ClientHandler::handle_read_header,
                this,
                boost::asio::placeholders::error
                )
                );
        }
        else
        {
            server_interface_->leave_client(id_);
        }
    }

    void deliver(const BYTE* data, const int &size)
    {
        if(size <= 0) return;

        // write header
        encode_header(size);

        boost::asio::async_write(
            socket_,
            boost::asio::buffer(
            header_,
            HEADER_SIZE
            ),
            boost::bind(
            &ClientHandler::deliver_payload,
            this,
            data,
            size,
            boost::asio::placeholders::error
            )
            );

        //// write payload
        //boost::asio::async_write(
        //    socket_,
        //    boost::asio::buffer(
        //        data,
        //        size
        //    ),
        //    boost::bind(
        //        &ClientHandler::handle_write,
        //        this,
        //        boost::asio::placeholders::error
        //    )
        //);
    }

    void deliver_payload(const BYTE* data, const int &size, const boost::system::error_code& error)
    {
        if(!error)
        {
            // write payload
            boost::asio::async_write(
                socket_,
                boost::asio::buffer(
                data,
                size
                ),
                boost::bind(
                &ClientHandler::handle_write,
                this,
                boost::asio::placeholders::error
                )
                );
        }
        else
        {
            server_interface_->leave_client(id_);
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if(error)
        {
            server_interface_->leave_client(id_);
        }
    }


private:

    void encode_header(size_t size)
    {
        sprintf(header_, "%04d", size);
    }

    bool decode_header()
    {
        payload_length_ = atoi(header_);
        if(payload_length_ > PAYLOAD_SIZE)
            return false;
        return true;
    }

    unsigned int            id_;
    tcp::socket             socket_;
    ServerInterface*        server_interface_;

    enum {HEADER_SIZE = 4};
    char header_[HEADER_SIZE];

    enum {PAYLOAD_SIZE = 1000};
    char payload_[PAYLOAD_SIZE];
    size_t payload_length_;
};
