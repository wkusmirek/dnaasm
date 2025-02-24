import os, sys, subprocess, re, string

def print_usage(argv):
    """print user help in script mode"""
    print( 'check the version of installed software for BRASTER-INTRO project' )
    print( 'use: python {} '.format( argv[0] ) )

#development packages
versions = {'python': ['3.5.3', ''],
            'g++' : ['6.3.0', ''],
            'scons' : ['2.5.1', ''],
            'boost' : ['1.64', ''],
}

def command_exec(commands):
    """execute system command (subprocess) and return its output"""
    res = subprocess.Popen(commands, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = res.communicate()
    if len(err) > 0:
        print('shell execution error', commands)
    return out

def version_from_oneline_output(commands):
    """execute system command, parse its output to find the N.N.N string"""
    try:
        out = command_exec(commands)
        m = re.search(r'(\d+\.\d+\.\d+)', str(out))
        if m:
            return m.group(1)
    except:
        pass
    return ''

def version_from_file(filename, reg):
    """read filename line by line, search for regex 'reg', return group(1) if found, empty string in other case"""
    with open(filename) as f:
        for line in f:
            m = re.search(reg, line)
            if m:
                return m.group(1)
    return ''

def check_file_for_version(filename, reg):
    """check if filename exists, then call version_from_file"""
    if os.path.isfile(filename):
        return version_from_file(filename, reg)
    return ''

def printVersions(versions):
    """compare and display the installed and required versions"""

    format_string = '%30s %15s %15s %10s'
    print ('\n wersje \n' + format_string %('Nazwa', 'Wymagana', 'Znaleziona', 'Status'))
    for key, values in versions.items():
        if values[0] == values[1]:
            compare = 'OK'
        elif values[1] == '':
            compare = 'Brak!'
        else:
            compare = 'Niezgodna!'
        print (format_string %(key, values[0], values[1], compare))

def readVersions(versions):
    """read versions of applications from dict"""

    if 'python' in versions.keys():
        versions['python'][1] = re.split('[ ]|\+',sys.version)[0]

    if 'scons' in versions.keys():
        versions['scons'][1] = version_from_oneline_output(['scons', '--version'])

    if 'g++' in versions.keys():
        versions['g++'][1] = version_from_oneline_output(['g++', '--version'])

    if 'boost' in versions.keys():
        PATTERN = r'#define BOOST_LIB_VERSION "(.*)"'
        ver = check_file_for_version('/usr/local/include/boost/version.hpp', PATTERN)
        if not ver:
            ver = check_file_for_version('/usr/include/boost/version.hpp', PATTERN)
        versions['boost'][1] =  ver.replace('_','.')

    return versions


if __name__ == "__main__":

    if len(sys.argv) != 1:
        print_usage(sys.argv)
        sys.exit(2)


    readVersions(versions)
    printVersions(versions)
