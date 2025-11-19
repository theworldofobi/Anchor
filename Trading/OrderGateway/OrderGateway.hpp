#pragma once

// #include <functional>

#include "../../Common/ThreadUtils.hpp"
#include "../../Common/Macros.hpp"
#include "../../Common/TCPServer.hpp"

#include "../../Exchange/OrderServer/ClientRequest.hpp"
#include "../../Exchange/OrderServer/ClientResponse.hpp"

namespace Trading 
{
  class OrderGateway 
  {
  public:
    OrderGateway(ClientId client_id,
                 Exchange::ClientRequestLFQueue *client_requests,
                 Exchange::ClientResponseLFQueue *client_responses,
                 std::string ip, const std::string &iface, int port);

    ~OrderGateway() 
    {
      stop();

      using namespace std::literals::chrono_literals;
      std::this_thread::sleep_for(5s);
    }

    auto start() 
    {
      run_ = true;
      ASSERT(tcp_socket_.connect(ip_, iface_, port_, false) >= 0,
             "Unable to connect to ip:" + ip_ + " port:" + std::to_string(port_) + " on iface:" + iface_ + " error:" + std::string(std::strerror(errno)));
      ASSERT(Common::createAndStartThread(4, "Trading/OrderGateway", [this]() { run(); }) != nullptr, "Failed to start OrderGateway thread.");
    }

    auto stop() -> void 
    {
      run_ = false;
    }

    // Deleted default, copy & move constructors and assignment-operators.
    OrderGateway() = delete;

    OrderGateway(const OrderGateway &) = delete;

    OrderGateway(const OrderGateway &&) = delete;

    OrderGateway &operator=(const OrderGateway &) = delete;

    OrderGateway &operator=(const OrderGateway &&) = delete;

  private:
    const ClientId client_id_;

    std::string ip_;
    const std::string iface_;
    const int port_ = 0;

    Exchange::ClientRequestLFQueue *outgoing_requests_ = nullptr;
    Exchange::ClientResponseLFQueue *incoming_responses_ = nullptr;

    volatile bool run_ = false;

    std::string time_str_;
    Logger logger_;

    size_t next_outgoing_seq_num_ = 1;
    size_t next_exp_seq_num_ = 1;
    Common::TCPSocket tcp_socket_;

    auto run() noexcept -> void;

    auto recvCallback(TCPSocket *socket, Nanos rx_time) noexcept -> void;
  };
}

