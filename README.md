# CoverbandExt

This is a C extension to run coverband on Ruby 1.9.3+ much much faster that with the pure Ruby version. This has been tested with Ruby 1.9.3, 2.0,x, 2.1.x

This gem does nothing on its own. So make sure you already have setup the [coverband](https://github.com/danmayer/coverband) gem. I recommend using just `coverband` to get run time code coverage working on your project. Then adding this gem once everything is configured and working to reduce the performance overhead of the original gem.

## Installation

Add this line to your application's Gemfile, after the existing coverband line:

    gem 'coverband_ext'
    gem 'coverband_ext'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install coverband coverband_ext

## Usage

Follow the normal Coverband usage... Include this gem below the coverband gem in your `Gemfile`. Make sure you are on Coverband 1.0.0 or above to have coverband detect and use this extension. With this gem loaded coverband will go ahead and use the available C extension methods to see a significant performance improvement.

No other changes should be required to receive the additional perf improvements.

## Perf Improvements

I have actually slightly improved the perf again since the V2 version in the benchmarks below. 

#### Example perf against smaller app with 100% coverband sampling

`ab -n 100 -c5 http://small.app.com:80/`

* No Coverband
  * Time taken for tests:   3.980 seconds /  3.999 seconds
* Ruby Coverband
  * Time taken for tests:   31.489 seconds / 29.064 seconds
* Ruby Coverband C Ext V1
  * Time taken for tests:   14.679 seconds / 12.033 seconds
* Ruby Coverband C Ext V2 (which includes Regex support)
  * Time taken for tests:   6.131 seconds / 6.321 seconds

##### Example perf against a VERY large rails app with 100% coverband sampling

`ab -n 50 -c5 http://pipeline.lsdev.co:80/pipeline/cities`

* No Coverband
  * Time taken for tests:   31.347 seconds / 31.298 seconds
* Ruby Coverband
  * Time taken for tests:   336.53 seconds / 331.89 seconds
* Ruby Coverband C Ext V2 (which includes Regex support)
  * Time taken for tests:   42.785 seconds / 43.343 seconds

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
