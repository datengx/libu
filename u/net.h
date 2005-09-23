/*
 * Copyright (c) 2005, KoanLogic s.r.l. - All rights reserved.
 */

#ifndef _U_NET_H_
#define _U_NET_H_

#include <sys/types.h>
#include <stdio.h>
#include <u/uri.h>

#ifdef HAVE_CONF_H
#include "conf.h"
#endif /* HAVE_CONF_H */

#define U_NET_BACKLOG 300

/* The Net module defines the following (private) URI types: 
 *    {tc,ud}p[46]://<host>:<port> for TCP/UDP over IPv[46] addresses,
 *    unix://<abs_path> for UNIX IPC endpoints. 
 * Internally, they are translated into an u_net_addr_t structure. */
struct u_net_addr_s
{
    enum { 
        U_NET_TYPE_MIN,
        U_NET_TCP4,
        U_NET_TCP6,
        U_NET_UDP4,
        U_NET_UDP6,
#ifdef OS_UNIX
        U_NET_UNIX,
#endif /* OS_UNIX */
        U_NET_TYPE_MAX
    } type;
    union
    {
        struct sockaddr_in  sin;
        struct sockaddr_in6 sin6;
#ifdef OS_UNIX
        struct sockaddr_un  sun;
#endif /* OS_UNIX */
    } sa;
};

typedef struct u_net_addr_s u_net_addr_t;

/* socket creation semantics: server or client (the 'mode' in u_net_sock) */
enum { U_NET_SSOCK, U_NET_CSOCK };

/* I/O */
int u_net_io (ssize_t (*f) (int, void *, size_t), int sd, void *buf, size_t l);
int u_net_write (int sd, void *buf, size_t nbytes);
int u_net_read (int sd, void *buf, size_t nbytes);

/* hi-level */
int u_net_sock (const char *uri, int mode);
int u_net_sock_tcp (u_net_addr_t *addr, int mode);
int u_net_sock_udp (u_net_addr_t *addr, int mode);
int u_net_sock_unix (u_net_addr_t *addr, int mode);

/* low-level */
int u_net_tcp4_ssock (struct sockaddr_in *sad, int reuse, int backlog);
int u_net_tcp6_ssock (struct sockaddr_in6 *sad, int reuse, int backlog);
int u_net_tcp4_csock (struct sockaddr_in *sad);
int u_net_tcp6_csock (struct sockaddr_in6 *sad);

/* uri string -> u_uri -> u_net_addr -> struct sockaddr */
int u_net_uri2addr (const char *uri, u_net_addr_t **pa);
int u_net_uri2sin (u_uri_t *uri, struct sockaddr_in *sad);
#ifdef OS_UNIX
int u_net_uri2sun (u_uri_t *uri, struct sockaddr_un *sad);
#endif /* OS_UNIX */

/* u_net_addr */
int u_net_addr_new (int type, u_net_addr_t **pa);
void u_net_addr_free (u_net_addr_t *addr);

#endif /* !_U_NET_H_ */