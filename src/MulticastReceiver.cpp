#include "MulticastReceiver.hpp"

// https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/example/cpp11/multicast/receiver.cpp

const short receiver_multicast_port = 30001;

MulticastReceiver::MulticastReceiver(boost::asio::io_service &io_service,
                                     const boost::asio::ip::address &listen_address, 
                                     const boost::asio::ip::address &multicast_address)
    : socket_(io_service)
{
    // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(listen_address, receiver_multicast_port);

    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    // Join the multicast group.
    socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address));

    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(
            &MulticastReceiver::handle_receive_from,
            this,
            boost::asio::placeholders::error, 
            boost::asio::placeholders::bytes_transferred));
}

void MulticastReceiver::handle_receive_from(const boost::system::error_code &error, std::size_t bytes_recvd)
{
    if (!error)
    {
        std::cout << "Receiving " ;
        std::cout.write(data_, bytes_recvd);
        std::cout << std::endl;

        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&MulticastReceiver::handle_receive_from, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}

void MulticastReceiver::Run()
{
    std::cout << "MulticastReceiver Run" << std::endl;

    auto listen_address = boost::asio::ip::address::from_string("0.0.0.0");
    auto multicast_address = boost::asio::ip::address::from_string("239.255.0.1");

    try
    {
        boost::asio::io_service io_service;
        MulticastReceiver r(io_service, listen_address, multicast_address);
        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}