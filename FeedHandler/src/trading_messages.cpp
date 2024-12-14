#include "trading_messages.hpp"

void CoinbaseRequest::ToJson(CoinbaseRequest::Channel message, json output_json)
{
    output_json["type"] = message.type;
    output_json["name"] = message.name;
    output_json["product_ids"] = message.product_ids;

    json channelObjects = json::array();
    for( auto& el : message.channel)
    {
        json channel_i{};
        CoinbaseRequest::ToJson(el, channel_i);
        channelObjects.push_back(channel_i);
    }
    output_json["channel"] = channelObjects;
}

void CoinbaseRequest::FromJson(json message_j)
{
    ;
}