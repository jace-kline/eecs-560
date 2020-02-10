import os
import sys
from pathlib import Path
from shutil import copy

access_rights = 0o755

if len(sys.argv) <= 1:
    print("Must provide a relative directory path as argument.")
else:
    dirname = sys.argv[1]
    newdirname = sys.argv[2]
    copyToPath = os.path.realpath(os.path.join("..", newdirname))
    os.mkdir(copyToPath, access_rights)
    for file in os.listdir(dirname):
        targetfile = os.path.realpath(os.path.join(".", os.path.join(dirname, file)))
        followed = os.readlink(targetfile) if os.path.islink(targetfile) else targetfile
        copy(followed, copyToPath)


