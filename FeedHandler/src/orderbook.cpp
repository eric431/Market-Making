#include "orderbook.hpp"

OrderBook::OrderBook(){}

OrderBook::OrderBook(std::string symbol){}

OrderBook::OrderBook(const OrderBook& orderbook){}

OrderBook& operator=(const OrderBook& orderbook){}

OrderBook(OrderBook&& orderbook) noexcept{}

OrderBook& operator=(OrderBook&& orrderbook) noexcept{}

~OrderBook::OrderBook(){}

void OrderBook::AddBidOrder(){}

void OrderBook::AddAskOrder(){}

BidAsk OrderBook::GetBestBidAsk(){}

void OrderBook::ModifyOrder(){}

void OrderBook::CancelOrder(){}

std::string_view OrderBook::PrintOrderBook(){};

void OrderBook::SetSymbol(std::string symbol){}