require 'mkmf'
if have_func('rb_add_event_hook')
  
  $CFLAGS += " -O0"
  $CFLAGS += " -std=c99"

  case RUBY_VERSION
  when /1.9.2/
    $CFLAGS += " -I./ruby_headers/192/ -DRUBY_192"
  when /1.9.3/
    $CFLAGS += " -I./ruby_headers/193/ -DRUBY_193"
  end

  create_makefile('coverband_ext/coverband_ext')
else
  fail 'missing API: are you using ruby with tracepoint 1.9.3+?'
end
