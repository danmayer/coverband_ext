# bundle exec rake build
# gem uninstall coverband_ext
# gem install pkg/coverband_ext-0.0.1.gem
# ruby example.rb

require 'coverband_ext'

module CoverbandExt

  def self.report(trace_point)
    puts "#{trace_point.path}:#{trace_point.lineno}"
  end

end

module Coverband
  class Base
    def add_from_tracepoint(trace_point)
      puts "#{trace_point.path}:#{trace_point.lineno}"
      #add_file(trace_point.path, trace_point.lineno)         
    end
  end
end


# def fib( n )
#   return  n  if ( 0..1 ).include? n
#   ( fib( n - 1 ) + fib( n - 2 ) )
# end

# stacks = CoverbandExt.profile do
#                     fib(30)
#                   end
# puts stacks.first.inspect

CoverbandExt.line_trace_start
puts "mooo"
o = Object.new
CoverbandExt.lines_trace_stop

CoverbandExt.line_trace_start
puts "mooo2"
o = Object.new
CoverbandExt.lines_trace_stop

puts "end"
