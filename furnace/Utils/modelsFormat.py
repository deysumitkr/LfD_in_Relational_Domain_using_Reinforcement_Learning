import os
import sys
import glob
import shutil

## ------ Settings -----------

MOVING_OBJECTS_IS_NEGATIVE_VALUE = False
INPUT_DIR_PATH = "../Demonstrations/"
OUTPUT_DIR_PATH = "../Models/train/"
TEMPLATE_DIR_PATH = "../Models/templates/"

PREDICT_DIR = "../Models/predict/"

## ---------------------------



state = {}
header = ''
count = 1
count_oqsa = 1

kb = ""
kbx = ""
kby = ""
kbqsa = ""
kboqsa = ""

def fillState(initialState):
    global state
    #print [ int(y.split(')')[0])  for x in initialState.split('\n') for y in x.split('(')[1].split(', ')]
    for each in [[int(y.split(')')[0]) for y in x.split('(')[1].split(', ')] for x in initialState.split('\n')]:
        state[each[0]] = (each[1], each[2])

def addinKBoqsa(id, qsa):
    global count_oqsa, state
    s = ""
    for i in state.keys():
        if MOVING_OBJECTS_IS_NEGATIVE_VALUE:
            q = qsa if(i == id) else 0.0
        else:
            if (i == id):
                q = qsa
            else:
                continue

        s += "begin(model(task{0})).\n".format(count_oqsa)
        s += header + '\n'
        s += "position({0}, {1}, {2}).\n".format(i, state[i][0], state[i][1])
        s += "move({0}).\n".format(i)
        s += "qsa({0}).\n".format(q)
        s += "end(model(task{0})).\n\n".format(count_oqsa)
        count_oqsa += 1
    return s


def addinKB(step, qsa):
    global state, count, kb, kbx, kby, kbqsa, kboqsa
    m = [step[0], step[1] - state[step[0]][0], step[2] - state[step[0]][1]]
    s = "begin(model(task{0})).\n".format(count)
    s += header+'\n'

    for i in state.keys():
        s += "position({0}, {1}, {2}).\n".format(i, state[i][0], state[i][1])

    sx = s + "move({0}, {1}).\n".format(m[0], m[1])
    sy = s + "move({0}, {1}).\n".format(m[0], m[2])
    sqsa = s + "qsa({0}).\n".format(qsa)
    s += "move({0}, {1}, {2}).\n".format(m[0], m[1], m[2])

    s += "end(model(task{0})).\n\n".format(count)
    sx += "end(model(task{0})).\n\n".format(count)
    sy += "end(model(task{0})).\n\n".format(count)
    sqsa += "end(model(task{0})).\n\n".format(count)

    soqsa = addinKBoqsa(m[0], qsa)

    count += 1
    state[step[0]] = (step[1], step[2])

    kb += s
    kbx += sx
    kby += sy
    kbqsa += sqsa
    kboqsa += soqsa


if __name__ == '__main__':

    taskName = str(sys.argv[1])

    try:
        INPUT_FILES = glob.glob(INPUT_DIR_PATH+ taskName +'/*')
    except:
        print "Error in locating the demonstation files for the task:", taskName
        exit()

    if len(INPUT_FILES) < 1:
        print "No demonstation file found for the task:", taskName
        exit()
    else:
        print "Number of Demonstartions found: ", len(INPUT_FILES)

    OUTPUT_DIR_PATH += taskName + '/'

    try:
        os.mkdir(OUTPUT_DIR_PATH)
    except:
        pass


    try:
        os.mkdir(OUTPUT_DIR_PATH + "qsa")
    except:
        pass


    try:
        os.mkdir(OUTPUT_DIR_PATH + "oqsa")
    except:
        pass


    for file in INPUT_FILES:

        state = {}
        header = ''

        print "Processing file:", file

        f = open(file, 'r')
        data = f.read()
        f.close()

        taskname = data.split('Header:')[0].strip()
        header = data.split('Header:')[1].split('Initial State:')[0].strip()
        initialState = data.split('Initial State:')[1].split('Trajectories:')[0].strip()
        trajectories = [ x.strip() for x in data.split('Trajectories:')[1].split('#') ]

        fillState(initialState)
        print "Number of Objects:", len(state.keys())


        Traj = []
        for trajectory in trajectories:
            trajectory = trajectory.strip()
            for move in  [y.split('(')[1].split(', ') for y in [ x for x in trajectory.split('\n')] if len(y) > 4]:
                Traj.append( [int(i.split(')')[0]) for i in move] )


        print "Number of trajectories: ", len(trajectories)
        print "Total number of sample points (all trajectories): ", len(Traj)

        discountFactor = 0.9
        for i in range(len(Traj)):
            addinKB(Traj[i], 0.9**(len(Traj)-1-i))


    print "Committing to files... ",
    """
    f = open(OUTPUT_DIR_PATH + "xy/xy.kb", 'w')
    f.write(kb)
    f.close()

    f = open(OUTPUT_DIR_PATH + "x/somethingX.kb", 'w')
    f.write(kbx)
    f.close()

    f = open(OUTPUT_DIR_PATH + "y/somethingY.kb", 'w')
    f.write(kby)
    f.close()
    """
    f = open(OUTPUT_DIR_PATH + "qsa/qsa.kb", 'w')
    f.write(kbqsa)
    f.close()

    f = open(OUTPUT_DIR_PATH + "oqsa/oqsa.kb", 'w')
    f.write(kboqsa)
    f.close()

    print "Done!"

    print "Creating Background KB and Settings File...",

    shutil.copy(TEMPLATE_DIR_PATH+"qsa.bg", OUTPUT_DIR_PATH+"qsa/")
    shutil.copy(TEMPLATE_DIR_PATH+"qsa.s", OUTPUT_DIR_PATH+"qsa/")
    shutil.copy(TEMPLATE_DIR_PATH+"oqsa.bg", OUTPUT_DIR_PATH+"oqsa/")
    shutil.copy(TEMPLATE_DIR_PATH+"oqsa.s", OUTPUT_DIR_PATH+"oqsa/")

    print "Done!"


