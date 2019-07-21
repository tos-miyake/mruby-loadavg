/*
** mrb_loadavg.c - Loadavg class
**
** Copyright (c) tos-miyake 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_loadavg.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  mrb_int len;
} mrb_loadavg_data;

static const struct mrb_data_type mrb_loadavg_data_type = {
  "mrb_loadavg_data", mrb_free,
};

static mrb_value mrb_loadavg_init(mrb_state *mrb, mrb_value self)
{
  mrb_loadavg_data *data;
  char *str;
  mrb_int len;

  data = (mrb_loadavg_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_loadavg_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_loadavg_data *)mrb_malloc(mrb, sizeof(mrb_loadavg_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_loadavg_hello(mrb_state *mrb, mrb_value self)
{
  mrb_loadavg_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_loadavg_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_loadavg_gem_init(mrb_state *mrb)
{
  struct RClass *loadavg;
  loadavg = mrb_define_class(mrb, "Loadavg", mrb->object_class);
  mrb_define_method(mrb, loadavg, "initialize", mrb_loadavg_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, loadavg, "hello", mrb_loadavg_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, loadavg, "hi", mrb_loadavg_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_loadavg_gem_final(mrb_state *mrb)
{
}

