import os
import sys
import subprocess
from modelsFormat import PREDICT_DIR, OUTPUT_DIR_PATH

#File_Path = '/home/sumit/Documents/projects/tilde/between/trash/tilde/trash.out'
#Bg_Path = '/home/sumit/Documents/projects/tilde/between/trash/trash.bg'



def extractPrologCode(File_Path):
    f = open(File_Path, 'r')
    data = f.read()

    program = data.split('Equivalent prolog program:')[1].strip()
    s = program.split('examples.')
    s[-1] = '\n'
    prog = 'examples.'.join(s)
    return prog


def createTemplate(taskName, fileName, File_Path, Bg_Path=None):
    header = """
:- style_check(-singleton).
:- style_check(-discontiguous).
:- initialization(main).
 
main:-
        class(X), 
        pops(X),
        halt.
 
pops([]):- nl.  
pops([H|T]):-   
        write(H),
pops(T).


"""
    if(Bg_Path is not None) and len(Bg_Path) > 1:
        f = open(Bg_Path, 'r')
        bg = '\n' + f.read() + '\n'
        f.close()
    else:
        bg = ''
    code = extractPrologCode(File_Path)

    data = header + "\n\n%% Background KB\n" +  bg.strip() + "\n\n%% Learnt Model\n" + code + "\n\n"

    try:
        os.mkdir(PREDICT_DIR)
    except:
        pass

    try:
        os.mkdir(PREDICT_DIR+taskName)
    except:
        pass

    f = open(PREDICT_DIR+taskName+'/'+fileName, 'w')
    f.write(data)
    f.close()

    return data

if __name__ == '__main__':
    if(len(sys.argv) < 2):
        print "One Argument Required: TaskName"
        exit()

    taskName = sys.argv[1]
    File_Path = OUTPUT_DIR_PATH+taskName+"/qsa/tilde/qsa.out"
    Bg_Path = OUTPUT_DIR_PATH+taskName+"/qsa/qsa.bg"
    fileName = 'templateQsa.pro'
    createTemplate(taskName, fileName, File_Path, Bg_Path)

    File_Path = OUTPUT_DIR_PATH + taskName + "/oqsa/tilde/oqsa.out"
    Bg_Path = OUTPUT_DIR_PATH + taskName + "/oqsa/oqsa.bg"
    fileName = 'templateOQsa.pro'
    createTemplate(taskName, fileName, File_Path, Bg_Path)

    print "Templates created for predictions"

    """
    cmd = " prolog -f --noinfo -l main.pro"
    out = subprocess.Popen("cd furnace; "+cmd, shell=True, stdout=subprocess.PIPE).stdout.read()
    print out
    """


