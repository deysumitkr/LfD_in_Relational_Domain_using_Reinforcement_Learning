import argparse
import subprocess
from modelsFormat import PREDICT_DIR

def predictQsa(taskName, state, prolog):
    path = PREDICT_DIR+taskName+'/'
    f = open(path+"templateQsa.pro", 'r')
    data = f.read(); f.close()

    data += "%% State\n\n" + state + "\n\n"
    f = open(path+"mainQsa.pro",'w')
    f.write(data); f.close()

    cmd = prolog + " -f --noinfo -l mainQsa.pro"
    return subprocess.Popen("cd "+ path +"; " + cmd, shell=True, stdout=subprocess.PIPE).stdout.read()


def predictOQsa(taskName, state, prolog):
    path = PREDICT_DIR+taskName+'/'
    f = open(path+"templateOQsa.pro", 'r')
    data = f.read(); f.close()

    data += "%% State\n\n" + state + "\n\n"
    f = open(path+"mainOQsa.pro",'w')
    f.write(data); f.close()

    cmd = prolog + " -f --noinfo -l mainOQsa.pro"
    return subprocess.Popen("cd "+ path +"; " + cmd, shell=True, stdout=subprocess.PIPE).stdout.read()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('-t', action='store', dest='taskName', help='Name of the task', default="")
    parser.add_argument('-s', action='store', dest='state', help='Displays list of saved tasks', default="")
    parser.add_argument('-p', action='store', dest='prolog_command', help='the command that runs prolog', default="")
    parser.add_argument('--object', action='store_true', dest='returnType', help='Set it to get object ID istead of Q(s,a) value', default=False)
    results = parser.parse_args()


    taskName = results.taskName
    state = results.state
    prolog_cmd = results.prolog_command
    obj = results.returnType

    if(len(taskName)<1):
        print "Invalid Task name"
        exit()

    if (len(state) < 5):
        print "Invalid state received."
        exit()

    if len(prolog_cmd) < 1:
        print "A valid prolog command is required for predictions"
        exit()



    if(obj):
        print predictOQsa(taskName, state, prolog_cmd).strip()
    else:
        print predictQsa(taskName, state, prolog_cmd).strip()