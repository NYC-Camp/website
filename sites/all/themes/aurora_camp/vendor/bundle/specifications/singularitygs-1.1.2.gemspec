# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "singularitygs"
  s.version = "1.1.2"

  s.required_rubygems_version = Gem::Requirement.new(">= 1.2") if s.respond_to? :required_rubygems_version=
  s.authors = ["Scott Kellum", "Sam Richard"]
  s.date = "2013-08-01"
  s.description = "Advanced responsive grid system for Sass and Compass"
  s.email = ["scott@scottkellum.com", "snugug@gmail.com"]
  s.homepage = "http://singularity.gs"
  s.licenses = ["MIT", "GPL"]
  s.require_paths = ["lib"]
  s.rubyforge_project = "singularitygs"
  s.rubygems_version = "2.0.3"
  s.summary = "Singularity is a fluid grid system that can generate uniform columns as well as asymmetric and compound grids. It is designed to be extensable, adding additional outputs or grid generators are easy, and the core syntax is simple to build upon for custom input syntaxes."

  if s.respond_to? :specification_version then
    s.specification_version = 4

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<sass>, [">= 3.2.1"])
      s.add_runtime_dependency(%q<compass>, [">= 0.12.2"])
      s.add_runtime_dependency(%q<breakpoint>, [">= 2.0.1"])
    else
      s.add_dependency(%q<sass>, [">= 3.2.1"])
      s.add_dependency(%q<compass>, [">= 0.12.2"])
      s.add_dependency(%q<breakpoint>, [">= 2.0.1"])
    end
  else
    s.add_dependency(%q<sass>, [">= 3.2.1"])
    s.add_dependency(%q<compass>, [">= 0.12.2"])
    s.add_dependency(%q<breakpoint>, [">= 2.0.1"])
  end
end
