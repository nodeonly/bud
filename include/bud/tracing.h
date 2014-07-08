#ifndef INCLUDE_BUD_TRACING_H_
#define INCLUDE_BUD_TRACING_H_

#include <stdint.h>  /* uint16_t */

/* Forward declarations */
struct ssl_st;

typedef struct bud_trace_module_s bud_trace_module_t;
typedef struct bud_trace_client_s bud_trace_client_t;
typedef struct bud_trace_backend_s bud_trace_backend_t;
typedef enum bud_trace_balance_e bud_trace_balance_t;
typedef void (*bud_trace_cb_t)(bud_trace_client_t* client);
typedef void (*bud_trace_backend_cb_t)(bud_trace_client_t* client,
                                       bud_trace_backend_t* backend);

#define CONNECTION_FIELDS                                                     \
    int fd;                                                                   \
    uint16_t port;                                                            \
    const char* host;                                                         \

enum bud_trace_balance_e {
  kBudTraceBalanceRoundRobin,
  kBudTraceBalanceSNI,
  kBudTraceBalanceOnFail
};

struct bud_trace_client_s {
  CONNECTION_FIELDS

  /* OpenSSL's SSL* object */
  struct ssl_st* ssl;

  /* Circularly-monotonic semi-unique connection id */
  uint64_t id;
};

struct bud_trace_backend_s {
  CONNECTION_FIELDS

  bud_trace_balance_t balance;
  const char* balance_str;
  int sni_match;
};

#undef CONNECTION_FIELDS

/* All tracing functions */
#define BUD_TRACING_ENUM(X)                                                   \
    BUD_TRACING_CLIENT_ENUM(X)                                                \
    BUD_TRACING_BACKEND_ENUM(X)                                               \

/* Tracing functions that do accept only one argument: client */
#define BUD_TRACING_CLIENT_ENUM(X)                                            \
    X(frontend_accept)                                                        \
    X(end)                                                                    \
    X(handshake)                                                              \

/* Tracing functions that do accept two arguments: client, backend */
#define BUD_TRACING_BACKEND_ENUM(X)                                           \
    X(backend_connect)                                                        \
    X(kill_backend)                                                           \

#define BUD_TRACE_MODULE_CLIENT_DECL(V) bud_trace_cb_t V;
#define BUD_TRACE_MODULE_BACKEND_DECL(V) bud_trace_backend_cb_t V;

struct bud_trace_module_s {
  BUD_TRACING_CLIENT_ENUM(BUD_TRACE_MODULE_CLIENT_DECL)
  BUD_TRACING_BACKEND_ENUM(BUD_TRACE_MODULE_BACKEND_DECL)
};

#undef BUD_TRACE_MODULE_CLIENT_DECL
#undef BUD_TRACE_MODULE_BACKEND_DECL

#define BUD_TRACE_MODULE bud_trace_module_t bud_trace_module

#endif  /* INCLUDE_BUD_TRACING_H_ */
