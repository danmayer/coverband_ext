/************************************************

  coverband_ext.c -

  $Author: $

  Copyright (c) 2014 Dan Mayer

************************************************/

#include "ruby.h"

static VALUE hello_world(VALUE mod)
{
  return rb_str_new2("hello world");
}

void Init_coverband_ext()
{
    /* VALUE rb_mCoverage = rb_define_module("Coverage"); */
    /* rb_define_module_function(rb_mCoverage, "start", rb_coverage_start, 0); */
    /* rb_define_module_function(rb_mCoverage, "result", rb_coverage_result, 0); */
    /* rb_gc_register_address(&rb_coverages); */
    VALUE mCoverbandExt = rb_define_module("CoverbandExt");
    rb_define_singleton_method(mCoverbandExt, "hello_world", hello_world, 0);
}
