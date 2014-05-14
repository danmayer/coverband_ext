# bundle exec rake build
# gem uninstall coverband_ext
# gem install pkg/coverband_ext-0.0.1.gem
# ruby example.rb

require 'coverband_ext'

module CoverbandExt

  def self.report(trace_point)
    puts "#{trace_point.path}:#{trace_point.lineno}"
  end

  def self.profile(millisecs=1, &blk)
    stacks = []
    thread = Thread.current
    last_time = Time.new

    new_api = thread.respond_to?(:backtrace_locations)

    trap('ALRM') do
      CoverbandExt.stop
      stack = (new_api ? thread.backtrace_locations : thread.backtrace)
      # I am not sure if this is ensured to run in the thread
      # though in my samples it always does
      if thread == Thread.current
        stack = stack[2..-1]
      end
      stacks << stack
      CoverbandExt.start(millisecs * 1000)
    end

    profile_block(millisecs * 1000, &blk)

    stacks
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

CoverbandExt.linesstart
puts "mooo"
o = Object.new
CoverbandExt.linesstop

puts "end"
