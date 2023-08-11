find_element = executable('find_element', 'find_element.c', dependencies : skvconf_dep)
find_group = executable('find_group', 'find_group.c', dependencies : skvconf_dep)
find_nonexistent_element = executable('find_nonexistent_element', 'find_nonexistent_element.c', dependencies : skvconf_dep)

test('find_element', find_element, args : [meson.current_source_dir() / 'test.txt'])
test('find_group', find_group, args : [meson.current_source_dir() / 'test.txt'])
test('find_nonexistent_element', find_nonexistent_element, args : [meson.current_source_dir() / 'test.txt'])
