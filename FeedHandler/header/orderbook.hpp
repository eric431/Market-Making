#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <map>
#include <memory>
#include <string>
#include <string_view>

using Price   = double;
using Qty     = double;
using Book    = std::map<Price, Order>;
using BookPtr = std::shared_ptr<Book>;
using BidAsk  = std::pair<Order, Order>;

enum OrderType
{
    Null,
    Buy,
    Sell,
};

struct Order
{
    OrderType order_type = OrderType::Null; 
    Price order_price{};
    Qty   order_quantity{};
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

        // Determine if input argument can be a string_view instead
        void SetSymbol(std::string symbol);

    private:
        std::string m_symbol{};
        BookPtr m_order_book{};
};

#endif