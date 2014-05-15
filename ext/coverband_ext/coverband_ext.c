/************************************************

  coverband_ext.c -

  $Author: $

  Copyright (c) 2014 Dan Mayer

************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <ruby.h>
#include <ruby/encoding.h>
#include <ruby/debug.h>
#include <ruby/st.h>
#include <ruby/io.h>
#include <ruby/intern.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>

static VALUE linetracer;
static void trace_line_handler(VALUE, void*);

static void
trace_line_handler(VALUE tpval, void *data)
{
  // Call puts, from Kernel
  //rb_funcall(rb_mKernel, rb_intern("puts"), 1, tpval);
  //call method in Coverband
  rb_funcall(rb_const_get(rb_cObject, rb_intern("CoverbandExt")), rb_intern("report"), 1, tpval);
}

static VALUE
ext_line_trace_start(VALUE module)
{
  linetracer = rb_tracepoint_new(Qnil, RUBY_EVENT_LINE, trace_line_handler, 0);
  rb_tracepoint_enable(linetracer);
  return Qnil;
}

static VALUE
ext_lines_trace_stop(VALUE module)
{
  rb_tracepoint_disable(linetracer);
  return Qnil;
}

void Init_coverband_ext( void)
{
    VALUE mCoverbandExt = rb_define_module("CoverbandExt");
    rb_define_module_function(mCoverbandExt, "line_trace_start", ext_line_trace_start, 0);
    rb_define_module_function(mCoverbandExt, "lines_trace_stop", ext_lines_trace_stop, 0);
}
