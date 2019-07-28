import subprocess
import warnings
import re

NM = 'x86_64-w64-mingw32-nm'
DLLTOOL = 'x86_64-w64-mingw32-dlltool'
EXPORT_PATTERN = r'^[_]{1,2}imp_(?P<export>.*) in python\d+\.dll'

def build_libpython(ver, nm=NM, dlltool=DLLTOOL,
                    export_pattern=EXPORT_PATTERN):
    pylib = 'python%s.lib' % ver
    pydef = 'python%s.def' % ver
    pydll = 'python%s.dll' % ver
    libpy = 'libpython%s.a' % ver
    warning = '%s failed - ' + '%s not built' % libpy
    match_export = re.compile(export_pattern).match
    cmd_nm = [nm, '-Cs', pylib]
    cmd_dlltool = [dlltool, 
                   '--dllname', pydll, 
                   '--def', pydef,
                   '--output-lib', libpy]
    with open(pydef, 'w') as f:
        f.write('LIBRARY %s\nEXPORTS\n' % pydll)
        p_nm = subprocess.Popen(cmd_nm, 
                                stdout=subprocess.PIPE,
                                universal_newlines=True)
        for line in sorted(p_nm.stdout):
            m = match_export(line)
            if m:
                f.write(m.group('export') + '\n')
        if p_nm.wait() != 0:
            warnings.warn(warning % nm)
            return False
    if subprocess.call(cmd_dlltool) != 0:
        warnings.warn(warning % dlltool)
        return False
    return True
#For example:

import os
for n in (27, 33, 35, 37):
    pylib = 'python%s.lib' % n
    if os.path.exists(pylib):
        build_libpython(n)
        pydef = 'python%s.def' % n            
        lc_def = sum(1 for line in open(pydef))
        libpy = 'libpython%s.a' % n
        lc_lib = sum(1 for line in os.popen('ar -t %s' % libpy))
        assert lc_def == lc_lib
#share improve this answer
#answered
#Jul 18 '11 at 10:50
