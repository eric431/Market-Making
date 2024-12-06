#include "coinbase_client.hpp"
#include "trading_messages.hpp"

using namespace Coinbase;

static const std::string URI = "advanced-trade-ws.coinbase.com";

int main()
{
    std::string host{URI};
    std::string port{"443"};
    std::string msg = R"({"type": "subscribe", "product_ids": ["BTC-USD"], "channel": "ticker"})";

    net::io_context ioc;

    ssl::context ctx{ssl::context::tlsv12_client};

    // add loop to continuously get data
    std::make_shared<AsynchronousMarketDataClient>(ioc, ctx)->run(host, port, msg);

    ioc.run();

    return EXIT_SUCCESS;
}