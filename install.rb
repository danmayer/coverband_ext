`bundle exec rake build`
`gem uninstall coverband_ext`
puts `gem install ./pkg/coverband_ext-0.0.1.gem -- --with-ruby-include=/opt/boxen/rbenv/versions/1.9.3-p448/include/ruby-1.9.1/`
Kernel.exec("ruby example.rb")
