project('skvconf', 'c', license : 'MIT', version : '1.0.0', default_options : ['c_std=c11'])

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
      '@INPUT@'],
    input : meson.source_root() / 'Doxyfile')
else
  warning('can\'t build documentation. If you don\'t need to build the documentation you can ignore this warning')
endif

flex_target = custom_target('flex',
  output : ['lexer.lex.h', 'lexer.lex.c'],
  command : [flex,
    '--header-file=@OUTPUT0@',
    '--outfile=@OUTPUT1@',
    '@INPUT@'],
  install : true,
  input : lexer,
  install_dir : [get_option('includedir') / 'skvconf' , false])

bison_target = custom_target('bison',
  command : [bison,
    '@INPUT@',
    '--header=@OUTPUT0@',
    '--output=@OUTPUT1@',
    '--color=always'],
  output : ['parser.tab.h', 'parser.tab.c'],
  install : true,
  input : grammar,
  install_dir : [get_option('includedir') / 'skvconf', false])

sources += bison_target
sources += flex_target

skvconf = library('skvconf', sources, include_directories : include, install : true)

skvconf_dep = declare_dependency(include_directories : include, link_with : skvconf, sources : [bison_target[0], flex_target[0]])
subdir('test')
