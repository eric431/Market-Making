#ifndef ORDER_BOOK_STRUCT_H
#define ORDER_BOOK_STRUCT_H

#include <string>
#include <vector>

namespace MarketData
{
    struct Header
    {

    };

    struct LogOn
    {

    };

    struct MarketDataRequest
    {

    };

    struct SecurityStatus
    {

    };

    // Market Data Incremental Refresh
    struct MDIR
    {

    };

    // Market Data Snapshot Full Refresh
    struct MDSFR
    {

    };

    // Security List Refresh
    struct SLR
    {

    };

    // Security List
    struct SL
    {

    };

    struct MarketData
    {

    };
}

struct Fix
{
    ;
};

namespace L3Schema
{
    struct Schema
    {
        std::string type{};
        std::string product_id{};
        std::string sequence{};
        std::string order_id{};
        std::string price{};
        std::string size{};
        std::string time{};
    };

    struct Done
    {
        std::string type{};
        std::string product_id{};
        std::string sequence{};
        std::string order_id{};
        std::string time{};
    };

    struct Match
    {
        std::string type{};
        std::string product_id{};
        std::string sequence{};
        std::string maker_order_id{};
        std::string taker_order_id{};
        std::string price{};
        std::string size{};
        std::string time{};
    };

    struct Noop {
        std::string type{};
        std::string product_id{};
        std::string sequence{};
        std::string time{};
    };

    struct Open {
        std::string type{};
        std::string product_id{};
        std::string sequence{};
        std::string order_id{};
        std::string side{};
        std::string price{};
        std::string size{};
        std::string time{};
    };

    struct L3
    {
        std::string type{};
        Schema schema{};
        Done done{};
        Match match{};
        Noop noop{};
        Open open{};
    };
};

namespace CoinbaseRequest
{
    struct Channel
    {
        std::string type{};
        std::string name{};
        std::vector<std::string> product_ids{};
        std::vector<Channel> channel{};
    };
}

#endif