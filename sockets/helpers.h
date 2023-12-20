#include <arpa/inet.h>   // htons(), ntohs()
#include <netdb.h>       // gethostbyname(), struct hostent
#include <netinet/in.h>  // struct sockaddr_in
#include <stdio.h>       // perror(), fprintf()
#include <string.h>      // memcpy()
#include <sys/socket.h>  // getsockname()
#include <unistd.h>      // stderr

// make a server sockaddr given a port
int make_server_sockaddr(struct sockaddr_in *addr, int port) {
    // specify socket family
    addr->sin_family = AF_INET;

    // specify socket address (hostname)
    addr->sin_addr.s_addr = INADDR_ANY;

    // set the port value
    addr->sin_port = htons(port);

    return 0;
}

// make a client sockaddr given a remote hostname and port
int make_client_sockaddr(struct sockaddr_in *addr, const char *hostname, int port) {
    // specify socket family
    addr->sin_family = AF_INET;

    // specify socket address (hostname)
    struct hostent *host = gethostbyname(hostname);
    if (host == NULL) {
        fprintf(stderr, "unknown host: %s\n", hostname);
        return -1;
    }
    memcpy(&addr->sin_addr, host->h_addr, host->h_length);

    // set the port value
    addr->sin_port = htons(port);

    return 0;
}

// return the port number assigned to a socket
int get_port_number(int sockfd) {
    struct sockaddr_in addr;
    socklen_t length = sizeof(addr);
    if (getsockname(sockfd, (struct sockaddr *)&addr, &length) == -1) {
        perror("Error getting port of socket");
        return -1;
    }
    return ntohs(addr.sin_port);
}
