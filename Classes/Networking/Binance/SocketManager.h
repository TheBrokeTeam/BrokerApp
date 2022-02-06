//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#ifndef BROKERAPP_SOCKETMANAGER_H
#define BROKERAPP_SOCKETMANAGER_H

namespace binance {
    class SocketManager {
        public:
        SocketManager();
        ~SocketManager();
        void openStream();
    };
}


#endif //BROKERAPP_SOCKETMANAGER_H
