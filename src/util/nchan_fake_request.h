#include <nchan_module.h>
#include <util/nchan_slist.h>

ngx_connection_t *nchan_create_fake_connection(ngx_pool_t *pool);
void nchan_close_fake_connection(ngx_connection_t *c);
ngx_http_request_t *nchan_create_fake_request(ngx_connection_t *c);
ngx_http_request_t *nchan_create_derivative_fake_request(ngx_connection_t *c, ngx_http_request_t *rsrc);
void nchan_finalize_fake_request(ngx_http_request_t *r, ngx_int_t rc);
void nchan_free_fake_request(ngx_http_request_t *r);

typedef struct nchan_fakereq_subrequest_data_s nchan_fakereq_subrequest_data_t;
typedef struct nchan_requestmachine_s nchan_requestmachine_t;

struct nchan_fakereq_subrequest_data_s {
  ngx_http_request_t *r;
  ngx_http_request_t *sr;
  void          *pd;
  callback_pt    cb;
  nchan_requestmachine_t *rm;
  ngx_event_t    cleanup_timer;
  unsigned       running:1;
  unsigned       aborted:1;
  struct {
    nchan_fakereq_subrequest_data_t *prev;
    nchan_fakereq_subrequest_data_t *next;
  }              slist;
};// nchan_fakereq_subrequest_data_t

struct nchan_requestmachine_s {
  ngx_http_request_t *template_request;
  nchan_slist_t       request_queue;
  unsigned            shutdown_when_finished;
};// nchan_requestmachine_t;

ngx_int_t nchan_requestmachine_initialize(nchan_requestmachine_t *rm, ngx_http_request_t *template_request);
ngx_int_t nchan_requestmachine_request(nchan_requestmachine_t *rm, ngx_pool_t *pool, ngx_str_t *url, ngx_buf_t *body, callback_pt cb, void *pd);
ngx_int_t nchan_requestmachine_abort(nchan_requestmachine_t *rm);
ngx_int_t nchan_requestmachine_shutdown(nchan_requestmachine_t *rm);
