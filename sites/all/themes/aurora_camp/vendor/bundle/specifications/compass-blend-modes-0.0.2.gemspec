# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "compass-blend-modes"
  s.version = "0.0.2"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Grady Kuhnline"]
  s.date = "2013-03-23"
  s.description = "Using standard color blending functions in Sass."
  s.email = ["github@heygrady.net"]
  s.homepage = "https://github.com/heygrady/scss-blend-modes"
  s.licenses = ["MIT"]
  s.require_paths = ["lib"]
  s.rubygems_version = "2.0.3"
  s.summary = "Using standard color blending functions in Sass."

  if s.respond_to? :specification_version then
    s.specification_version = 4

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<compass>, [">= 0"])
    else
      s.add_dependency(%q<compass>, [">= 0"])
    end
  else
    s.add_dependency(%q<compass>, [">= 0"])
  end
end
