import argparse
import os
import sys
import modelsFormat


def listTasks():
    f = []
    for (dirpath, dirnames, filenames) in os.walk(modelsFormat.INPUT_DIR_PATH):
        f.extend(dirnames)
        break

    print "Follwing task are saved:" if len(f) > 0 else "No task is recorded yet"
    for i in f:
        print i

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('--savedTasks', action='store_true', dest='saved_tasks', help='display list of saved tasks', default=False)
    parser.add_argument('-s', action='store', dest='state', help='display list of saved tasks', default="")
    results = parser.parse_args()

    print results.state

    if(results.saved_tasks):
        listTasks()


