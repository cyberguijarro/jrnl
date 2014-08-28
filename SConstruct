environment = Environment(
    CXXFLAGS=['-O3', '-Wall', '-std=c++0x'],
    **ARGUMENTS
)

if ARGUMENTS.get('USE_BOOST_REGEX') == 'y':
    environment['CPPDEFINES'] = {'USE_BOOST_REGEX': None}
    environment['LIBS'] = ['boost_regex']

environment.Program('jrnl', Glob('*.cpp'))
