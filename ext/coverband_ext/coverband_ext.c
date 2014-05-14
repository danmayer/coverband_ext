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

static VALUE
rb_profile_start(VALUE module, VALUE usec)
{
    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = (suseconds_t)NUM2LONG(usec);
    timer.it_value = timer.it_interval;
    setitimer(ITIMER_REAL, &timer, 0);

    return Qnil;
}

static VALUE
rb_profile_stop(VALUE module)
{
    struct itimerval timer;
    memset(&timer, 0, sizeof(timer));
    setitimer(ITIMER_REAL, &timer, 0);

    return Qnil;
}

static VALUE
rb_profile_block(VALUE module, VALUE usec)
{
    rb_need_block();

    rb_profile_start(module, usec);
    rb_yield(Qundef);
    rb_profile_stop(module);

    return Qnil;
}

static VALUE linetracer;
static void stackprof_newobj_handler(VALUE, void*);

static void
stackprof_newobj_handler(VALUE tpval, void *data)
{
  // Call puts, from Kernel
  //rb_funcall(rb_mKernel, rb_intern("puts"), 1, tpval);
  
  //call method in my module
  rb_funcall(rb_const_get(rb_cObject, rb_intern("CoverbandExt")), rb_intern("report"), 1, tpval);
}

static VALUE
rb_lines_start(VALUE module)
{
   linetracer = rb_tracepoint_new(Qnil, RUBY_EVENT_LINE, stackprof_newobj_handler, 0);
   rb_tracepoint_enable(linetracer);
}

static VALUE
rb_lines_stop(VALUE module)
{
  rb_tracepoint_disable(linetracer);
}

void Init_coverband_ext()
{
    VALUE mCoverbandExt = rb_define_module("CoverbandExt");
    rb_define_module_function(mCoverbandExt, "profile_block", rb_profile_block, 1);
    rb_define_module_function(mCoverbandExt, "stop", rb_profile_stop, 0);
    rb_define_module_function(mCoverbandExt, "start", rb_profile_start, 1);
    rb_define_module_function(mCoverbandExt, "linesstop", rb_lines_stop, 0);
    rb_define_module_function(mCoverbandExt, "linesstart", rb_lines_start, 0);
}
