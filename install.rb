`bundle exec rake build`
`gem uninstall coverband_ext`
puts `gem install ./pkg/coverband_ext-0.0.1.gem`
Kernel.exec("ruby example.rb")
