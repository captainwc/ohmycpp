

def make(compiler,file, target,  cxx_flags):
    """
    编译单个文件
    """
    cmd = [compiler, file, '-o', target]
