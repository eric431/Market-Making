#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <map>
#include <memory>
#include <string>
#include <string_view>

using Price           = double;
using Qty             = double;
using BuySideBook     = std::map<Price, MarketOrder>;
using SellSideBook    = std::map<Price, MarketOrder>;
using BuySideBookPtr  = std::shared_ptr<BuySideBook>;
using SellSideBookPtr = std::shared_ptr<SellSideBook>;
using BidAsk          = std::pair<MarketOrder, MarketOrder>;
using OrderId         = unsigned long;

enum OrderType
{
    Null,
    Buy,
    Sell,
};

struct MarketOrder
{
    OrderType order_type = OrderType::Null; 
    Price order_price{};
    Qty   order_quantity{};
};

struct LimitOrder
{

};

struct StopOrder
{

};

struct Book
{
    BuySideBookPtr BuySide{};
    SellSideBookPtr SellSide{};
};

class OrderBook
{
    public:
        OrderBook();

        // Determine if string_View can be converted to a string 
        OrderBook(std::string symbol);

        OrderBook(const OrderBook& orderbook);

        OrderBook& operator=(const OrderBook& orderbook);

        OrderBook(OrderBook&& orderbook) noexcept;

        OrderBook& operator=(OrderBook&& orderbook) noexcept;

        ~OrderBook();

        void AddBidOrder();

        void AddAskOrder();

        BidAsk GetBestBidAsk();

        // TODO: find appropriate return type for Bid Ask Spread
        // void GetBidAskSpread();

        void ModifyOrder();

        void CancelOrder();

        std::string_view PrintOrderBook();

        // Determine if input argument can be a string_view instead
        void SetSymbol(std::string symbol);

    private:
        std::string m_symbol{};
        Book m_order_book{};
};

#endif