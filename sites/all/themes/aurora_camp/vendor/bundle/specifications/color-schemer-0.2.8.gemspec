# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "color-schemer"
  s.version = "0.2.8"

  s.required_rubygems_version = Gem::Requirement.new(">= 1.3.5") if s.respond_to? :required_rubygems_version=
  s.authors = ["Scott Kellum", "Mason Wendell"]
  s.date = "2011-10-06"
  s.description = "Create color schemes with ease."
  s.email = ["scott@scottkellum.com"]
  s.homepage = "https://github.com/scottkellum/color-schemer"
  s.require_paths = ["lib"]
  s.rubyforge_project = "color-schemer"
  s.rubygems_version = "2.0.3"
  s.summary = "Create color schemes with ease."

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<compass-blend-modes>, ["~> 0.0.2"])
    else
      s.add_dependency(%q<compass-blend-modes>, ["~> 0.0.2"])
    end
  else
    s.add_dependency(%q<compass-blend-modes>, ["~> 0.0.2"])
  end
end
