//
// Created by sunnysab on 2021/6/29.
//

#include <iostream>
#include <filesystem>
#include <winsock2.h>
#include "progress_bar.h"
#include "AntClient.h"

int main(int argc, char *argv[]) {
    WSAData data{};
    WSAStartup(MAKEWORD(2, 2), &data);

    std::string file_path = "./test/test-case/pure-text.txt";
    size_t file_size = std::filesystem::file_size(file_path);

    bmc::progress_bar pb{
            0,  // min, also initial value
            file_size,  // max
            80,  // width in percent of screen (including percentage and time)
            true,  // auto increment when outputting
            true   // show time at the end
    };
    AntClient client(file_path);

    client.connect("127.0.0.1", 16006);
    if (!client.try_send()) {
        std::cout << "Server refused the send request." << std::endl;
        return -1;
    }

    client.send([&pb](TransferProcess process) -> bool {
        pb.set(process.completed_size);
        std::cout << pb;
        return true;
    });
    std::cout << pb;

    client.close();
    WSACleanup();
    return 0;
}