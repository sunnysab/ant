//
// Created by sunnysab on 2021/6/29.
//

#include <iostream>
#include "AntClient.h"

int main(int argc, char *argv[]) {
    AntClient client("./test/test-case/pure-text.txt");

    client.connect("127.0.0.1", 16006);
    if (!client.try_send()) {
        std::cout << "Server refused the send request." << std::endl;
        return -1;
    }

    client.send([](TransferProcess process) -> bool {
        std::cout << process.completed_size / process.total_size << std::endl;

        return true;
    });

    client.close();
    return 0;
}