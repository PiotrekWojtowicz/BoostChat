#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>

class Printer{
public:
    Printer(boost::asio::io_context& ioc):
    strand_(boost::asio::make_strand(ioc)),
    timer_1(ioc, boost::asio::chrono::seconds(1)),
    timer_2(ioc, boost::asio::chrono::seconds(1)),
    count_(0){
        timer_1.async_wait(boost::asio::bind_executor(strand_,boost::bind(
                &Printer::print1, this)));
        timer_2.async_wait(boost::asio::bind_executor(strand_, boost::bind(
                &Printer::print2, this)));
    }

    ~Printer(){
        std::cout << "FINAL COUNT : " << count_-1<< std::endl;
    }

    void print1(){
        if(count_ <= 10){
            std::cout << "TIMER 1: "<<  count_ << std::endl;
            ++count_;

            timer_1.expires_at(timer_1.expiry() + boost::asio::chrono::seconds(1));
            timer_1.async_wait(boost::asio::bind_executor(strand_, boost::bind(
                    &Printer::print1, this)));

        }
    }
    void print2(){
        if(count_ <= 10){
            std::cout << "TIMER 2: "<<  count_ << std::endl;
            ++count_;

            timer_2.expires_at(timer_2.expiry() + boost::asio::chrono::seconds(1));
            timer_2.async_wait(boost::asio::bind_executor(strand_, boost::bind(
                    &Printer::print2, this)));

        }
    }

private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer_1;
    boost::asio::steady_timer timer_2;
    int count_;
};

int main() {

    //adding the io_context which is
    //some kind of agent between the program
    //execution program and the OS
    boost::asio::io_context io;

    Printer prt(io);
    boost::thread tr1(boost::bind(&boost::asio::io_context::run, &io));
    io.run();
    tr1.join();

    return 0;
}
