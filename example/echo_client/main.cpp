/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "echo_client.hpp"
#include <thread>
#include <chrono>

int main(int, char**)
{
    xeus::xconfiguration config = xeus::load_configuration("connection.json");

    std::string user_name = "JohanMabille";
    int nb_msg = 4;
    zmq::context_t context;

    echo_client::xclient client(config, user_name, context);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    for (int i = 0; i < nb_msg; ++i)
    {
        client.send_code("double x = std::sqrt(" + std::to_string(i) + ");");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    client.send_stop();

    // Gives time to publish thread so it can log
    // remaining messages
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    return 0;
}
