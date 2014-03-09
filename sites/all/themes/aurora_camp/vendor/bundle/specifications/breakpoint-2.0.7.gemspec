# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "breakpoint"
  s.version = "2.0.7"

  s.required_rubygems_version = Gem::Requirement.new(">= 1.3.6") if s.respond_to? :required_rubygems_version=
  s.authors = ["Mason Wendell", "Sam Richard"]
  s.date = "2013-09-17"
  s.description = "Really simple media queries in Sass"
  s.email = ["mason@zivtech.com", "sam@snug.ug"]
  s.homepage = "https://github.com/Team-Sass/breakpoint"
  s.require_paths = ["lib"]
  s.rubyforge_project = "breakpoint"
  s.rubygems_version = "2.0.3"
  s.summary = "An easy to use system for writing and managing media queries."

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<sass>, [">= 3.2.0"])
      s.add_runtime_dependency(%q<compass>, [">= 0.12.1"])
    else
      s.add_dependency(%q<sass>, [">= 3.2.0"])
      s.add_dependency(%q<compass>, [">= 0.12.1"])
    end
  else
    s.add_dependency(%q<sass>, [">= 3.2.0"])
    s.add_dependency(%q<compass>, [">= 0.12.1"])
  end
end
