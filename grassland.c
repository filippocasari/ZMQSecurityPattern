
#include <czmq.h>
#define VERBOSE true
int main (void)
{
    //  Create and bind server socket
    zsock_t *server = zsock_new (ZMQ_PUSH);
    zactor_t *client_monitor= zactor_new(zmonitor, server);
    if(VERBOSE){

        zstr_sendx(client_monitor, "VERBOSE",NULL);
        zstr_sendx (client_monitor, "LISTEN", "LISTENING", "ACCEPTED", NULL);
        zstr_sendx (client_monitor, "START", NULL);
    }

    zsock_bind (server, "tcp://*:9000");

    //  Create and connect client socket
    zsock_t *client = zsock_new (ZMQ_PULL);
    zsock_connect (client, "tcp://127.0.0.1:9000");

    //  Send a single message from server to client
    zstr_send (server, "Hello");
    char *message = zstr_recv (client);

    free (message);
    puts ("Grasslands test OK");

    zsock_destroy (&client);
    zsock_destroy (&server);

   zactor_destroy(&client_monitor);


    return 0;
}
