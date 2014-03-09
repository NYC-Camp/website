# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "sassy-strings"
  s.version = "1.0.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 1.2") if s.respond_to? :required_rubygems_version=
  s.authors = ["Sam Richard"]
  s.date = "2013-08-16"
  s.description = "Superpower Strings!"
  s.email = ["snugug@gmail.com"]
  s.homepage = "https://github.com/snugug/sassy-strings"
  s.licenses = ["MIT"]
  s.require_paths = ["lib"]
  s.rubyforge_project = "sassy-strings"
  s.rubygems_version = "2.0.3"
  s.summary = "Advanced String handling for Sass"

  if s.respond_to? :specification_version then
    s.specification_version = 4

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<compass>, [">= 0.12.2"])
    else
      s.add_dependency(%q<compass>, [">= 0.12.2"])
    end
  else
    s.add_dependency(%q<compass>, [">= 0.12.2"])
  end
end
