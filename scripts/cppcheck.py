import os
import subprocess

# 遍历项目文件夹找到对应的cpp/h文件，然后执行cppcheck，并将错误输出到对应的文件夹
if __name__ == '__main__':

    target = 'lru'
    which = 0
    # -------------------------------------------------------------------
    cmds = ['cppcheck']
    cmd = cmds[which]
    args = ['--language=c++', '--std=c++20', '--enable=all']

    current_file = os.path.abspath(__file__)
    project_dir = os.path.dirname(os.path.dirname(current_file))

    log_file = os.path.join(project_dir, 'log', 'cppcheck', target + '.log')

    target_path = ''
    for root, _, files in os.walk(project_dir):
        for file in files:
            if file == target + '.cpp' or file == target + '.h':
                target_path = os.path.join(root, file)

    with open(log_file, 'w') as log:
        subprocess.run([cmd, target_path] + args, stdout=subprocess.PIPE, stderr=log, text=True)
