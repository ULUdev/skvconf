project('skvconf', 'c', license : 'MIT', version : '1.0.2', default_options : ['c_std=c11'])

subdir('src')
include = include_directories('include')

# dependencies
bison = find_program('bison')
flex = find_program('flex')
doxygen = find_program('doxygen', required : false)

# documentation

if doxygen.found()
  doc = custom_target('doc', 
    output : 'doc',
    command : [doxygen,
      '@INPUT0@'],
    input : [meson.source_root() / 'Doxyfile',
      meson.source_root() / 'README.md',
      meson.source_root() / 'include' / 'skvconf.h',
      meson.source_root() / 'include' / 'skvconf_types.h'])
else
  warning('can\'t build documentation. If you don\'t need to build the documentation you can ignore this warning')
endif

# generators
flex_gen = generator(flex, 
  output : ['@BASENAME@.lex.c', '@BASENAME@.lex.h'],
  arguments : ['--header-file=@OUTPUT1@',
    '--outfile=@OUTPUT0@',
    '@INPUT@'])

bison_gen = generator(bison,
  output : ['@BASENAME@.tab.c', '@BASENAME@.tab.h'],
  arguments : ['@INPUT@', 
    '--header=@OUTPUT1@',
    '--output=@OUTPUT0@',
    '--color=always'])

sources += bison_gen.process(parser)
sources += flex_gen.process(lexer)

install_headers('include/skvconf.h')
install_headers('include/skvconf_types.h')
skvconf = library('skvconf', sources, include_directories : include, install : true)

skvconf_dep = declare_dependency(include_directories : include, link_with : skvconf)

pkg = import('pkgconfig')
pkg.generate(libraries : skvconf,
  version : meson.project_version(),
  name : 'skvconf',
  filebase : 'skvconf',
  description : 'A simple key-value configuration language')

subdir('test')
