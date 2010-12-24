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
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio::ip;

class Client
{
public:
    Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
        : io_service_(io_service), socket_(io_service), initialized_(false), client_counts_(0)
    {
        tcp::endpoint endpoint = *endpoint_iterator;
        socket_.async_connect(endpoint,
            boost::bind(&Client::handle_connect, this,
            boost::asio::placeholders::error, ++endpoint_iterator
            )
            );
    }

    void write(const std::vector<double>& pos)
    {
        if(initialized_)
            io_service_.post(boost::bind(&Client::do_write, this, pos));
    }

    void close()
    {
        io_service_.post(boost::bind(&Client::do_close, this));
    }

    unsigned int getId()
    {
        return id_;
    }

private:
    void handle_connect(const boost::system::error_code& error,
        tcp::resolver::iterator endpoint_iterator)
    {
        if (!error)
        {
            boost::asio::async_read(socket_,
                boost::asio::buffer(head, header_size),
                boost::bind(
                &Client::handle_read_header,
                this,
                boost::asio::placeholders::error
                )
                );
        }
        else if (endpoint_iterator != tcp::resolver::iterator())
        {
            socket_.close();
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint,
                boost::bind(
                &Client::handle_connect,
                this,
                boost::asio::placeholders::error,
                ++endpoint_iterator
                )
                );
        }
    }

    void handle_read_header(const boost::system::error_code& error)
    {
        if (!error && decode_header())
        {
            boost::asio::async_read(socket_,
                boost::asio::buffer(body, body_length),
                boost::bind(
                &Client::handle_read_body,
                this,
                boost::asio::placeholders::error
                )
                );
        }
        else
        {
            do_close();
        }
    }

    void handle_read_body(const boost::system::error_code& error)
    {
        if (!error)
        {
            //////////////////////////////////////////////////////////////////////////
            // received data
            // get client pos data
            int user_size = body_length / (POINT_DIMENSION * sizeof(double));
            int tdx = 0;
            for(int idx = 0; idx < user_size; idx++)
            {
                for(int kdx = 0; kdx < POINT_DIMENSION; kdx++)
                {
                    memcpy(
                        &(client_points_[idx][kdx]),
                        body + (tdx * sizeof(double)),
                        sizeof(double)
                        );
                    tdx++;
                }
            }

            client_counts_ = user_size;
            std::cout << "Client Count: " << client_counts_ << std::endl;
            std::cout << "\n";

            if(initialized_ == false)
                initialized_ = true;
            //////////////////////////////////////////////////////////////////////////

            // wait next packet
            boost::asio::async_read(socket_,
                boost::asio::buffer(head, header_size),
                boost::bind(
                &Client::handle_read_header,
                this,
                boost::asio::placeholders::error
                )
                );
        }
        else
        {
            do_close();
        }
    }

    void do_write(const std::vector<double>& pos)
    {
        int size = sizeof(double) * pos.size();
        encode_header(size);

        // write header
        boost::asio::async_write(socket_,
            boost::asio::buffer(head, header_size),
            boost::bind(
            &Client::handle_write_header,
            this,
            pos,
            boost::asio::placeholders::error
            )
            );
    }

    void handle_write_header(const std::vector<double>& pos, const boost::system::error_code& error)
    {
        if (!error)
        {
            int size = 24;
            static BYTE *payload = new BYTE[24];

            for(int idx = 0; idx < pos.size(); idx++)
            {
                double data = pos[idx];
                memcpy(payload + (idx * sizeof(double)), &data, sizeof(double));
            }

            // write payload
            boost::asio::async_write(socket_,
                boost::asio::buffer(payload, size),
                boost::bind(
                &Client::handle_write,
                this,
                boost::asio::placeholders::error
                )
                );
        }
        else
        {
            do_close();
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            // do nothing
            // send data well done
        }
        else
        {
            do_close();
        }
    }

    void do_close()
    {
        socket_.close();
    }


    // very dangerous!!!
    enum{USER_COUNTER_MAX = 100};
    enum{POINT_DIMENSION = 3};

    unsigned int client_counts_;
    double client_points_[USER_COUNTER_MAX][POINT_DIMENSION];
    unsigned int id_;

private:
    void encode_header(size_t size)
    {
        sprintf(head, "%04d", size);
    }

    bool decode_header()
    {
        body_length = atoi(head);
        if(body_length > body_size) return false;
        return true;
    }

    bool initialized_;

    boost::asio::io_service& io_service_;
    tcp::socket socket_;

    enum {header_size = 4};
    char head[header_size];

    enum {body_size = 1000};
    char body[body_size];
    size_t body_length;

};
