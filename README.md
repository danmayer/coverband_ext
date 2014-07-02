# CoverbandExt

This is a native C extension to run coverband on Ruby 1.9.3 much much faster that with the pure Ruby version.

## Installation

Add this line to your application's Gemfile:

    gem 'coverband_ext'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install coverband_ext

## Usage

Follow the normal Coverband usage... Include this gem below the coverband gem in your `Gemfile`. Make sure you are on Coverband 0.0.27 or above to have coverband detect and use this extension.

## Perf Improvements

#### Example perf against small app with 100% coverband sampling

`ab -n 100 -c5 http://small.app.com:80/`

* No Coverband
  * Time taken for tests:   3.980 seconds /  3.999 seconds
* Ruby Coverband
  * Time taken for tests:   31.489 seconds / 29.064 seconds
* Ruby Coverband C Ext V1
  * Time taken for tests:   14.679 seconds / 12.033 seconds
* Ruby Coverband C Ext V2 with Regex
  * Time taken for tests:   6.131 seconds / 6.321 seconds

##### Example perf against large rails app with 100% coverband sampling

`ab -n 50 -c5 http://pipeline.lsdev.co:80/pipeline/cities`

* No Coverband
  * Time taken for tests:   31.347 seconds / 31.298 seconds
* Ruby Coverband
  * Time taken for tests:   336.53 seconds / 331.89 seconds
* Ruby Coverband C Ext V2 with Regex
  * Time taken for tests:   42.785 seconds / 43.343 seconds

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
