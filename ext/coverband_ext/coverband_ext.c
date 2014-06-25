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

// If you create a Ruby object from C and store it in a C global variable without exporting it to Ruby, you must at least tell the garbage collector about it, lest ye be reaped inadvertently:
//VALUE obj;
//obj = rb_ary_new();
//rb_global_variable(obj);
static VALUE currentCoverbandBase;
static VALUE linetracer_ext;
static void trace_line_handler_ext(VALUE, void*);

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

static void
trace_line_handler_ext(VALUE tpval, void *data)
{
  // Call puts, from Kernel
  //rb_funcall(rb_mKernel, rb_intern("puts"), 1, tpval);
  //call method in Coverband
  //rb_funcall(rb_const_get(rb_cObject, rb_intern("CoverbandExt")), rb_intern("report"), 1, tpval);
  rb_funcall(rb_mKernel, rb_intern("puts"), 1, currentCoverbandBase);
  rb_funcall(currentCoverbandBase, rb_intern("add_from_tracepoint"), 1, tpval);
}

static VALUE 
cb_extended(VALUE self) {
  return Qtrue;
}

static VALUE
cb_set_tracer(VALUE self) {
  //VALUE rb_call_super(int argc, VALUE *args)
  //Calls the current method in the superclass of the current object.
  //rb_funcall(rb_mKernel, rb_intern("puts"), 1, rb_intern("ext set trace"));
  currentCoverbandBase = self;
  linetracer_ext = rb_tracepoint_new(Qnil, RUBY_EVENT_LINE, trace_line_handler_ext, 0);
  rb_tracepoint_enable(linetracer_ext);
  return Qnil;
}

static VALUE
cb_unset_tracer(VALUE self) {
  //rb_funcall(rb_mKernel, rb_intern("puts"), 1, rb_intern("ext unset trace"));
  currentCoverbandBase = Qnil;
  rb_tracepoint_disable(linetracer_ext);
  return Qnil;
}

void Init_coverband_ext(void)
{
    VALUE mCoverbandExt = rb_define_module("CoverbandExt");
    rb_define_module_function(mCoverbandExt, "line_trace_start", ext_line_trace_start, 0);
    rb_define_module_function(mCoverbandExt, "lines_trace_stop", ext_lines_trace_stop, 0);

    VALUE coverbandBase = rb_path2class("Coverband::Base");
    rb_define_method(coverbandBase, "extended?", cb_extended, 0);
    rb_define_method(coverbandBase, "set_tracer", cb_set_tracer, 0);
    rb_define_method(coverbandBase, "unset_tracer", cb_unset_tracer, 0);
}
