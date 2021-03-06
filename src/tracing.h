#ifndef SRC_TRACING_H_
#define SRC_TRACING_H_

#include "include/bud/tracing.h"  /* public dso API */

/* Forward declarations */
struct bud_client_s;
struct bud_config_backend_s;

#define BUD_TRACE_CLIENT_DECL(V)                                              \
    void bud_trace_##V(struct bud_client_s* client);                          \

#define BUD_TRACE_BACKEND_DECL(V)                                             \
    void bud_trace_##V(struct bud_client_s* client,                           \
                       struct bud_config_backend_s* backend);                 \

#define BUD_TRACE_CLOSE_DECL(V)                                               \
    void bud_trace_##V(struct bud_client_s* client, bud_error_t err);         \

BUD_TRACING_CLIENT_ENUM(BUD_TRACE_CLIENT_DECL)
BUD_TRACING_BACKEND_ENUM(BUD_TRACE_BACKEND_DECL)
BUD_TRACING_CLOSE_ENUM(BUD_TRACE_CLOSE_DECL)

#undef BUD_TRACE_CLIENT_DECL
#undef BUD_TRACE_BACKEND_DECL
#undef BUD_TRACE_CLOSE_DECL

#endif  /* SRC_TRACING_H_ */
