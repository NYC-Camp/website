# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "toolkit"
  s.version = "1.3.8"

  s.required_rubygems_version = Gem::Requirement.new(">= 1.2") if s.respond_to? :required_rubygems_version=
  s.authors = ["Sam Richard", "Scott Kellum", "Mason Wendell"]
  s.date = "2013-09-07"
  s.description = "Toolkit for Progressive Enhancement and Responsive Web Design"
  s.email = ["sam@snug.ug", "scott@scottkellum.com", "mason@zivtech.com"]
  s.homepage = "https://github.com/Snugug/toolkit"
  s.licenses = ["MIT", "GPL"]
  s.require_paths = ["lib"]
  s.rubyforge_project = "toolkit"
  s.rubygems_version = "2.0.3"
  s.summary = "Progressive Enhancement and RWD toolkit of awesomeness"

  if s.respond_to? :specification_version then
    s.specification_version = 4

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<compass>, [">= 0.12.2"])
      s.add_runtime_dependency(%q<singularitygs>, [">= 1.1.2"])
      s.add_runtime_dependency(%q<breakpoint>, [">= 2.0.6"])
      s.add_runtime_dependency(%q<sassy-strings>, [">= 1.0.0"])
      s.add_runtime_dependency(%q<color-schemer>, [">= 0.2.7"])
    else
      s.add_dependency(%q<compass>, [">= 0.12.2"])
      s.add_dependency(%q<singularitygs>, [">= 1.1.2"])
      s.add_dependency(%q<breakpoint>, [">= 2.0.6"])
      s.add_dependency(%q<sassy-strings>, [">= 1.0.0"])
      s.add_dependency(%q<color-schemer>, [">= 0.2.7"])
    end
  else
    s.add_dependency(%q<compass>, [">= 0.12.2"])
    s.add_dependency(%q<singularitygs>, [">= 1.1.2"])
    s.add_dependency(%q<breakpoint>, [">= 2.0.6"])
    s.add_dependency(%q<sassy-strings>, [">= 1.0.0"])
    s.add_dependency(%q<color-schemer>, [">= 0.2.7"])
  end
end
