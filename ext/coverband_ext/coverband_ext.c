/************************************************

  coverband.c -

  $Author: $

  Copyright (c) 2014 Dan Mayer

************************************************/

#include "ruby.h"
static VALUE hello_world(VALUE mod)
{
  return rb_str_new2("hello world");
}

void Init_coverband(void)
{
    /* VALUE rb_mCoverage = rb_define_module("Coverage"); */
    /* rb_define_module_function(rb_mCoverage, "start", rb_coverage_start, 0); */
    /* rb_define_module_function(rb_mCoverage, "result", rb_coverage_result, 0); */
    /* rb_gc_register_address(&rb_coverages); */
    VALUE mCoverband = rb_define_module("Coverband");
    rb_define_singleton_method(mCoverband, "hello_world", hello_world, 0);
}
