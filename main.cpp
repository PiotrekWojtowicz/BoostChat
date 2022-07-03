#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

void print(const boost::system::error_code& /*e*/,
           boost::asio::steady_timer* timer, int* count){

    if(*count <= 5){
        std::cout << *count << std::endl;
        ++(*count);

        timer->expires_at(timer->expiry() + boost::asio::chrono::seconds(1));
        timer->async_wait(boost::bind(print, boost::asio::placeholders::error, timer, count));

    }
}

int main() {

    //adding the io_context which is
    //some kind of agent between the program
    //execution program and the OS
    boost::asio::io_context io;

    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(1));

    int count = 1;
    timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &count));

    io.run();

    std::cout << "Final count is: " << count-1 << std::endl;
    return 0;
}
