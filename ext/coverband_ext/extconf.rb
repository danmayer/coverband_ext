require 'mkmf'
if have_func('rb_add_event_hook')
  create_makefile('coverband_ext/coverband_ext')
else
  fail 'missing API: are you using ruby with tracepoint 1.9.3+?'
end
