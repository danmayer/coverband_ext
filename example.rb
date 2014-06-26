# bundle exec rake build
# gem uninstall coverband_ext
# gem install pkg/coverband_ext-0.0.1.gem
# ruby example.rb

require 'redis'
require 'coverband_ext'

module CoverbandExt

  def self.report(trace_point)
    puts "#{trace_point.path}:#{trace_point.lineno}"
  end

end

###
# quick way to override methods for testing without releasing a new gem
###
#module Coverband
#  class Base
#    def add_from_tracepoint(trace_point)
#      #puts "#{trace_point.inspect}"
#      #add_file(trace_point.path, trace_point.lineno)         
#    end
#
#    def add_file(file, line)
#      puts "file: #{file}"
#      puts "line: #{line}"
#    end
#  end
#end


# def fib( n )
#   return  n  if ( 0..1 ).include? n
#   ( fib( n - 1 ) + fib( n - 2 ) )
# end

# stacks = CoverbandExt.profile do
#                     fib(30)
#                   end
# puts stacks.first.inspect

#CoverbandExt.line_trace_start
#puts "mooo"
#o = Object.new
#CoverbandExt.lines_trace_stop

#CoverbandExt.line_trace_start
#puts "mooo2"
#o = Object.new
#CoverbandExt.lines_trace_stop

require 'json'

baseline = Coverband.parse_baseline

Coverband.configure do |config|
  config.root              = Dir.pwd
  config.redis             = Redis.new()
  config.coverage_baseline = baseline
  config.root_paths        = ['example.rb']
  config.ignore            = ['vendor']
  # Since rails and other frameworks lazy load code. I have found it is bad to allow
  # initial requests to record with coverband. This ignores first 15 requests
  config.startup_delay     = 0
  config.percentage        = 100.0
  config.verbose           = true
end

coverband = Coverband::Base.new
puts "is coverband extended: #{coverband.extended?}"

coverband.start
puts "wohooo part 2"
coverband.stop
coverband.save

puts "end"
