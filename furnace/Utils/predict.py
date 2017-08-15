import argparse
import pickle
import subprocess
import numpy as np
import matplotlib.pyplot as plt
from modelsFormat import PREDICT_DIR

def predictQsa(taskName, state, prolog):
    path = PREDICT_DIR+taskName+'/'
    f = open(path+"templateQsa.pro", 'r')
    data = f.read(); f.close()

    data += "%% State\n\n" + state + "\n\n"
    f = open(path+"mainQsa.pro",'w')
    f.write(data); f.close()

    cmd = prolog + " -f --noinfo -l mainQsa.pro"
    return subprocess.Popen("cd "+ path +"; " + cmd, shell=True, stdout=subprocess.PIPE).stdout.read().strip()


def predictOQsa(taskName, state, prolog):
    path = PREDICT_DIR+taskName+'/'
    f = open(path+"templateOQsa.pro", 'r')
    data = f.read(); f.close()

    data += "%% State\n\n" + state + "\n\n"
    f = open(path+"mainOQsa.pro",'w')
    f.write(data); f.close()

    cmd = prolog + " -f --noinfo -l mainOQsa.pro"
    return subprocess.Popen("cd "+ path +"; " + cmd, shell=True, stdout=subprocess.PIPE).stdout.read().strip()


def genStatesForHeatMap(prolog, taskName, state, ID, shape, stride=(15,15)):
    toMatch = 'position('+str(ID)+','
    lines = state.strip().split('\n')
    const_state = '\n'.join([l for l in lines if toMatch not in l])

    matrix = []
    for y in range(0, shape[1], stride[1]):
        row = []
        for x in range(0, shape[0], stride[0]):
            dynamic_state = 'position({0}, {1}, {2}).\n'.format(int(ID), x, y)
            newState = const_state + '\n' + dynamic_state
            row.append( predictQsa(taskName, newState, prolog) )
        matrix.append(row)

    matrix = np.array(matrix).astype(np.float32)
    pickle.dump(matrix, open(PREDICT_DIR+"heatMap_matrix.p", "w"))
    plt.imshow(matrix, cmap='hot', interpolation='nearest')
    plt.show()




def getQsaHeatMap(prolog, taskName, state, ID, shape, stride=(2,2)):
    const_state, dynamic_state =  genStatesForHeatMap(state, ID, shape, stride)
    for ds in dynamic_state:
        newState = const_state + '\n' + ds
        predictQsa(taskName, newState, prolog)



if __name__ == '__main__':


    parser = argparse.ArgumentParser()

    parser.add_argument('-t', action='store', dest='taskName', help='Name of the task', default="")
    parser.add_argument('-s', action='store', dest='state', help='Displays list of saved tasks', default="")
    parser.add_argument('-p', action='store', dest='prolog_command', help='the command that runs prolog', default="")
    parser.add_argument('-id', action='store', type=int, dest='heat_id', help='the id for which to generate heat map', default=-1)
    parser.add_argument('--object', action='store_true', dest='returnType', help='Set it to get object ID istead of Q(s,a) value', default=False)
    parser.add_argument('--heatMap', action='store_true', dest='heatMap', help='show heat map', default=False)
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


    recommendedObject = -1
    if(obj):
        recommendedObject = predictOQsa(taskName, state, prolog_cmd).strip()
        print recommendedObject
        if results.heat_id < 0:
            recommendedObject = int(round(float(recommendedObject)))
        else:
            recommendedObject = int(round(float(results.heat_id)))

    else:
        print predictQsa(taskName, state, prolog_cmd).strip()

    if results.heatMap and recommendedObject > 0:
        genStatesForHeatMap(prolog_cmd, taskName, state, recommendedObject, (1280, 720))
