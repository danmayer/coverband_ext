require 'mkmf'
if have_func('rb_postponed_job_register_one') &&
   have_func('rb_profile_frames') &&
   have_func('rb_tracepoint_new') &&
   have_const('RUBY_INTERNAL_EVENT_NEWOBJ')
  create_makefile('coverband_ext/coverband_ext')
else
  fail 'missing API: are you using ruby 2.1+?'
end