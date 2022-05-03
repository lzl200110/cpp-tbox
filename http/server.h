#ifndef TBOX_HTTP_SERVER_H_20220501
#define TBOX_HTTP_SERVER_H_20220501

#include <tbox/event/loop.h>
#include <tbox/network/sockaddr.h>

#include "common.h"
#include "request.h"
#include "respond.h"
#include "middleware.h"

namespace tbox {
namespace http {

class Server {
  public:
    explicit Server(event::Loop *wp_loop);
    virtual ~Server();

  public:
    bool initialize(const network::SockAddr &bind_addr, int listen_backlog);
    bool start();
    void stop();
    void cleanup();

  public:
    void use(const RequestCallback &cb);
    void use(Middleware *wp_middleware);

    class Impl;

  private:
    Impl *impl_;
};

}
}

#endif //TBOX_HTTP_SERVER_H_20220501