# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'coverband_ext/version'

Gem::Specification.new do |spec|
  spec.name          = "coverband_ext"
  spec.version       = CoverbandExt::VERSION
  spec.authors       = ["Dan Mayer"]
  spec.email         = ["dan.mayer@livingsocial.com"]
  spec.description   = %q{C extension for fast coverband}
  spec.summary       = %q{C extension for fast coverband}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/)
  spec.extensions    = 'ext/coverband_ext/extconf.rb'
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.3"
  spec.add_development_dependency "rake"

  spec.add_runtime_dependency "coverband"
end
