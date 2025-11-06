#pragma once

#include "../../Common/Types.hpp"
#include "../../Common/ThreadUtils.hpp"
#include "../../Common/LFQueue.hpp"
#include "../../Common/Macros.hpp"
#include "../../Common/MCastSocket.hpp"
#include "../../Common/MemoryPool.hpp"
#include "../../Common/Logging.hpp"

#include "MarketUpdate.hpp"
#include "../Matcher/MatchingEngineOrder.hpp"

using namespace Common;

namespace Exchange 
{
  class SnapshotSynthesizer 
  {
  public:
    SnapshotSynthesizer(MDPMarketUpdateLFQueue *market_updates, const std::string &iface,
                        const std::string &snapshot_ip, int snapshot_port);

    ~SnapshotSynthesizer();

    auto start() -> void;

    auto stop() -> void;

    auto addToSnapshot(const MDPMarketUpdate *market_update);

    auto publishSnapshot();

    auto run() -> void;

    // Deleted default, copy & move constructors and assignment-operators.
    SnapshotSynthesizer() = delete;

    SnapshotSynthesizer(const SnapshotSynthesizer &) = delete;

    SnapshotSynthesizer(const SnapshotSynthesizer &&) = delete;

    SnapshotSynthesizer &operator=(const SnapshotSynthesizer &) = delete;

    SnapshotSynthesizer &operator=(const SnapshotSynthesizer &&) = delete;

  private:
    MDPMarketUpdateLFQueue *snapshot_md_updates_ = nullptr;

    Logger logger_;

    volatile bool run_ = false;

    std::string time_str_;

    McastSocket snapshot_socket_;

    std::array<std::array<MEMarketUpdate *, ME_MAX_ORDER_IDS>, ME_MAX_TICKERS> ticker_orders_;
    size_t last_inc_seq_num_ = 0;
    Nanos last_snapshot_time_ = 0;

    MemPool<MEMarketUpdate> order_pool_;
  };
}

