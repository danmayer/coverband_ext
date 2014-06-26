/************************************************

  coverband_ext.c -

  $Author: $

  Copyright (c) 2014 Dan Mayer

************************************************/

#include <ruby.h>

// TODO I read below do I need to do this for my variables below?
// If you create a Ruby object from C and store it in a C global variable without exporting it to Ruby, you must at least tell the garbage collector about it, lest ye be reaped inadvertently:
// VALUE obj;
// obj = rb_ary_new();
// rb_global_variable(obj);

static VALUE currentCoverbandBase;
static void trace_line_handler_ext(VALUE rb_event_flag_t, VALUE data, VALUE self, ID id, VALUE klass);

static void
trace_line_handler_ext(VALUE rb_event_flag_t, VALUE data, VALUE self, ID id, VALUE klass)
{
  // TODO moving regex from ruby to this point and doing the regex in C would dramatically reduce the perf cost of coverband
  rb_funcall(currentCoverbandBase, rb_intern("add_file"), 2, rb_str_new2(rb_sourcefile()),INT2NUM(rb_sourceline()));
}

static VALUE 
cb_extended(VALUE self) {
  return Qtrue;
}

static VALUE
cb_set_tracer(VALUE self) {
  if(!rb_iv_get(self, "@tracer_set")) {
    // TODO there has got to be a better way to do this
    // somehow have self in the hook point to the class. Is this thread safe
    currentCoverbandBase = self;
  
    // NOTE: We are using rb_add_event_hook opposed to rb_tracepoint_new for 1.9.X compat
    // not using higher level C functions of set_trace_func to avoid extra overhead we don't need since we only need the RUBY_EVENT_LINE hook as well as only needing file / line number opposed to everything else.
    // TODO possibly use rb_thread_add_event_hook
    rb_add_event_hook(trace_line_handler_ext, RUBY_EVENT_LINE, 0);
    rb_iv_set(self, "@tracer_set", Qtrue);
  }
  return Qnil;
}

static VALUE
cb_unset_tracer(VALUE self) {
  if(rb_iv_get(self, "@tracer_set")) {
    currentCoverbandBase = Qnil;
    rb_remove_event_hook(trace_line_handler_ext);
    rb_iv_set(self, "@tracer_set", Qfalse);
  }
  return Qnil;
}

void Init_coverband_ext(void)
{
  VALUE coverbandBase = rb_path2class("Coverband::Base");
  rb_define_method(coverbandBase, "extended?", cb_extended, 0);
  rb_define_method(coverbandBase, "set_tracer", cb_set_tracer, 0);
  rb_define_method(coverbandBase, "unset_tracer", cb_unset_tracer, 0);
}
