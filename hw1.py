import re
import sys

def picknum(snode):
    #print "snode:", snode
    numlist = []
    num_re = r'(-?[0-9]+)'
    num = re.findall(num_re, snode)
    for i in num:
        numlist.append(eval(i))
    return numlist


def addstr(sname, snode):
    nodelist = []
    for i in range(0, len(snode), 2):
        node = tuple([snode[i], snode[i + 1]])
        nodelist.append(node)
    if len(nodelist) <= 1:
        errStrnode = 'Error: Incomplete coordinates in a "' + sname + '", no end point.\n' 
        sys.stderr.write(errStrnode)
    else:
        pairs = []
        for m in range(len(nodelist) - 1):
            pairs.append([nodelist[m], nodelist[m + 1]])
        for street in streets.values():
            for pair in pairs:
                pairreverse = [pair[1], pair[0]]
                if pair in street or pairreverse in street:
                    errStrnode = 'Error: Segment ' + str(pair) + ' already defined in existing street.\n' 
                    sys.stderr.write(errStrnode)
                    return;
                
        streets[sname] = pairs
   
def gengraph():

    pairlist = streets.values()
    
    activenode = []
    intersection = set([]) # record intersections
    crossset = {}
    edge = []
    
    for i in range(len(pairlist) - 1):
        for j in range(i + 1, len(pairlist)):
            for pair1 in pairlist[i]:
                for pair2 in pairlist[j]:
                    crosspoint = crossvalidation(pair1, pair2)
                    if crosspoint != ():
                        for item in [crosspoint, pair1[0], pair1[1], pair2[0], pair2[1]]:
                            addvertics(item)
                            activenode.append(item)


                        intersection.add(crosspoint)
                        for point in intersection:
                            #print "point format is: ", point
                            
                            if online(point, pair1):
                                if tuple(pair1) not in crossset.keys():
                                    crossset[tuple(pair1)] = [point]
                                else:
                                    crossset[tuple(pair1)].append(point)
  
                            if online(point, pair2):
                                if tuple(pair2) not in crossset.keys():
                                    crossset[tuple(pair2)] = [point]
                                else:
                                    crossset[tuple(pair2)].append(point)
                            
                            #print "crossset:", crossset
            

    activen = list(set(activenode)) # eliminate duplicates in activenode[]

    delnode = []
    for node in V.iterkeys():
        if node not in activen:
            delnode.append(node)

    for n in delnode:
        global V
        del V[n]

    newV = {}
    for newk, newv in zip(V.values(), V.keys()):
        newV[newk] = newv
    sortednk = newV.keys()
    sortednk.sort()

    # display vertics:
    print "V = {"
    for newnode in sortednk:
        print "  " + str(newnode) + ":", newV[newnode]
    print "}"

    
    # add edge:
    for k, v in crossset.items():
        s = list(set(v))
        
        #print s
        
        if len(s) == 1:
            if dist(k[0], s[0]) > 0.001:
                e0 = addedge(k[0], s[0])
                edge.append(e0)
            if dist(s[0], k[1]) > 0.001:
                e1 = addedge(s[0], k[1])
                edge.append(e1)
            
        else:
            distdict = {}
            for i in range(len(s)):
                distdict[dist(k[0],s[i])] = i
            #print "distdict:", distdict
            
            sortednode = []
            keyarray = distdict.keys()
            keyarray.sort()
            
            for j in keyarray:
                #print "j: ", j
                sortednode.append(j)

            #print "sortednode:", sortednode

            if dist(k[0], s[distdict[sortednode[0]]]) > 0.001:
                e0 = addedge(k[0], s[distdict[sortednode[0]]])
                edge.append(e0)
            for m in range(len(sortednode) - 1):
                e = addedge(s[distdict[sortednode[m]]], s[distdict[sortednode[m + 1]]])
                edge.append(e)
            if dist(s[distdict[sortednode[m + 1]]], k[1]) > 0.001:
                e = addedge(s[distdict[sortednode[m + 1]]], k[1])
                edge.append(e)     

    E = list(set(edge)) # eliminate duplicates in edge[]
    # display edges:
    print "E = {"
    for edge in E:
        print "  <" + str(edge[0]) + "," + str(edge[1]) + ">,"
    print "}"

        
# input format: [(x1, y1), (x2, y2)]
def crossvalidation(pair1, pair2):
    x1, y1 = pair1[0]
    x2, y2 = pair1[1]
    x3, y3 = pair2[0]
    x4, y4 = pair2[1]
    
    k1x, k1y, b1 = calline(pair1)
    s11 = k1y * y3 - k1x * x3 - b1
    s12 = k1y * y4 - k1x * x4 - b1
    
    k2x, k2y, b2 = calline(pair2)
    s21 = k2y * y1 - k2x * x1 - b2
    s22 = k2y * y2 - k2x * x2 - b2
    
    if s11 * s12 <= 0 and s21 * s22 <= 0:
        #print pair1, "and", pair2, "are crossed."
        
        if k1y != 0 and k2y != 0:
            xcross = solve("k1x * x + b1 = k2x * x + b2", k1x, b1, k2x, b2, 'x')
            ycross = eval("k1x * x + b1", {'k1x':k1x, 'b1':b1, 'x':xcross})
        elif k1y == 0:
            xcross = -b1
            ycross = solve("y = k2x * (-b1) + b2", k1x, b1, k2x, b2, 'y')
        elif k2y == 0:
            xcross = -b2
            ycross = solve("y = k1x * (-b2) + b1", k1x, b1, k2x, b2, 'y')
        #print "Print from crossvalidation(): cross point is", (xcross, ycross)
        return (xcross, ycross)
    else:
        #print pair1, "and", pair2, "are not crossed."
        return ()

              
def calline(pair):
    x1, y1 = pair[0]
    x2, y2 = pair[1]
    
    if x1 != x2:
        kx = float(y2 - y1) / (x2 - x1)
        ky = 1
        b = (y1 - kx * x1)
    else:
        kx = 1
        ky = 0
        b = -x1
    return kx, ky, b

def solve(eq, k1x, b1, k2x, b2, var='x'):
    eq1 = eq.replace("=","-(") + ")"
    c = eval(eq1,{var:1j, 'k1x':k1x, 'b1':b1, 'k2x':k2x, 'b2':b2})
    return -c.real/c.imag

def addvertics(node): # data studture of node is tuple
    n = tuple(node)
    if not V.has_key(n):
        global I
        V[n] = I # I is declared at the beginning of this program. 
                    # Suppose the index of deleted nodes are not reusable.
        I = I + 1
        

def online(point, pair):
    x1, y1 = pair[0]
    x2, y2 = pair[1]
    x3, y3 = point

    k1x, k1y, b1 = calline(pair)
    s = k1y * y3 - k1x * x3 - b1
    if s < 0.01 and s > -0.01:
        return True
    else:
        return False

  
      
def addedge(node1, node2):
    n1 = tuple(node1)
    n2 = tuple(node2)
    edge = (V[n1], V[n2])
    return edge

def dist(node1, node2):
    x1, y1 = node1
    x2, y2 = node2
    return (x1 - x2) ** 2 + (y1 - y2) ** 2





# generates a dictionary where street names are keys and street nodes are valus
streets = {}
V = {}
I = 1 # index for V. Suppose the index of deleted nodes are not reusable. 


while True:
    try:
        userinput = raw_input()
    except EOFError:
        break;

    # divide multiple lines into list ui
    ui = []
    j = 0 
    for i in range(len(userinput)):
        if userinput[i] == '\n':
            ui.append(userinput[j:i])
            j = i + 1
    ui.append(userinput[j:])
    #print "ui:", ui

    # divide each line into three parts, then generate strname and strnode
    for str0 in ui:
        try:
            slcmode = str0[0]
            str1 = []
            str2 = []
            for i in range(len(str0)):
                if str0[i] == '"' or str0[i] == "'":
                    str1 = str0[(i + 1) :]
                    break
            for j in range(len(str1)):
                if str1[j] == '"' or str1[j] == "'":
                    str2 = str1[(j + 1):]
                    str1 = str1[: j]
                    break
            if len(str1) != 0:
                strname = str1
            if len(str2) != 0:
                strnode = picknum(str2)
            
            if slcmode == 'a':
                if strname in streets.keys():
                    errStra = "Error: 'a' specified for a street that already exists.\n"
                    sys.stderr.write(errStra)
                else:
                    addstr(strname, strnode)
            elif slcmode == 'c':
                if strname not in streets.keys():
                    errStrc = "Error: 'c' specified for a street that does not exist.\n"
                    sys.stderr.write(errStrc)
                else:
                    del streets[strname]
                    addstr(strname, strnode)
            elif slcmode == 'r':
                if strname not in streets.keys():
                    errStrr = "Error: 'r' specified for a street that does not exist.\n"
                    sys.stderr.write(errStrr)
                else:
                    del streets[strname]
            elif slcmode == 'g':
                gengraph()
            else:
                errStrr0 = "Error: '" + str(slcmode) + "' not a command.\n"
                sys.stderr.write(errStrr0)
                
            #print streets
            
        except:
            if len(str0) == 0:
                warnStr = "Warning: Empty line.\n"
                sys.stderr.write(warnStr)
                
     
