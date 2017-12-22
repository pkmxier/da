#include <iostream>
#include <cstring>
#include "zhelpers.hpp"
#include <unistd.h>
#include <algorithm>
#include <string>

struct ship {
    double x;
    double y;
    int angle;

    void operator =(ship ship_) {
        x = ship_.x;
        y = ship_.y;
        angle = ship_.angle;
    }
};

struct MessageData {
    int clientId;
    ship ships[10];
    char message[128];
    int type;
};

class Field {
private:
    ship ships[10];

public:
    Field(ship ships_[10]) {
        for (int i = 0; i < 10; ++i) {
            ships[i] = ships_[i];
        }
    }

    ~Field();
};

void make_connection(zmq::socket_t &server, std::vector<std::string> &player) {
    while (player.size() != 2) {
        std::string message = s_recv(server);
        std::cout << message << std::endl;
        for (;;) {
            if (s_recv(server) == "hi") {
                if (std::find(player.begin(), player.end(), message) == player.end()) {
                    player.push_back(message);
                    s_sendmore(server, message);
                    s_send(server, "go!");
                    break;
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    zmq::context_t context(1);
    zmq::socket_t server(context, ZMQ_ROUTER);
    server.bind("tcp://*:4040");

    std::vector<std::string> player;
    make_connection(server, player);

    std::cout << "Database created" << std::endl;

    std::vector< std::pair<double, double> *> field;
    while (field.size() < 2) {
        std::string who = s_recv(server);
        zmq::message_t message;
        server.recv(&message);

        field.push_back(NULL);
        field[field.size() - 1] = new std::pair<double, double>[10];

        std::pair<double, double> *x =  static_cast< std::pair<double, double> *>(message.data());
        memcpy(field[field.size() - 1], x, message.size());

        if (who == player[0]) {
            s_sendmore(server, player[1]);
        } else {
            s_sendmore(server, player[0]);
        }

        zmq::message_t message1(sizeof(field[field.size() - 1]) * 20);
        memcpy(message1.data(), field[field.size() - 1], sizeof(field[field.size() - 1]) * 20);
        server.send(message1);

        for (int i = 0; i < 10; ++i) {
            std::cout << field[field.size() - 1][i].first << " : " << field[field.size() - 1][i].second << std::endl;
        }
    }

    return 0;
}
