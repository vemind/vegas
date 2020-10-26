import numpy as np
na=[]
pyth=[]
nuber=[]
intoduce=[]
try:
    f = open("maplog.txt", "r+")
except IOError:
    print("文件不存在")
else:

    i = 0
    while 1:
        n = f.readline()
        if n == '':
            break
        s = f.readline()
        into = f.readline()
        n = n[:-1]
        s = s[:-1]
        into = into[:-1]
        na.append(n)
        nuber.append(s)
        intoduce.append(into)
        #print (LI[i].name)
        #print (LI[i].nuber)
        i = i + 1
    f.close()

try:
    f = open("pathlog.txt", "r+")
except IOError:
    print("文件不存在")
else:

    i =0
    for i in range(len(na)):
        pyth.append(f.readline()[:-1])
    f.close()
    k=i+1
    napath = [[0 for i in range(k)] for j in range(k)]
    i=j=0
    for i in range(k):
        for j in range(k):
            napath[i][j]=int(pyth[i].split(" ")[j])
    f.close()

N = k
M = 100
edge = np.array(napath)
A = edge[:]
path = np.zeros((N, N))


def Floyd():
    for i in range(N):
        for j in range(N):
            if (edge[i, j] != 100 and edge[i, j] != 0):
                path[i][j] = i

    #print("init:")
    #print(A, "\n", "\n", path)
    #print("\n")
    for a in range(N):
        for b in range(N):
            for c in range(N):
                if (A[b, a] + A[a, c] < A[b, c]):
                    A[b, c] = A[b, a] + A[a, c]
                    path[b][c] = path[a][c]
Floyd()
print("请选择你要执行的功能")
print("输入1进行进行景点信息查询")
print("输入2查看浏览路线")
print("输入3查找两个景点之间的最短路线")
print("输入4学校景点介绍")
print("输入5更改景点间的信息")
print("输入6查询景点间可行路径")
sl=int(input())
if sl==1:
    sr=str(input("输入你要查找的景点名称"))
    for i in range(len(na)):
        if (sr==na[i]):
            print(intoduce[i])
if sl==2:
    print('result:')
    print(A, '\n', '\n', path)
if sl==3:

    sr1 = str(input("输入你要查找的景点1名称"))
    sr2 = str(input("输入你要查找的景点2名称"))
    for i in range(len(na)):
        if (sr1 == na[i]):
            jd1=i
        if (sr2 == na[i]):
            jd2=i
    print("两地的距离为",A[jd1, jd2])
if sl==4:
    for i in range(len(na)):
        print(na[i],"\n")
if sl==5:
    sr = int(input("输入你要修改的类型\n1为修改景点名称\n2为修改景点介绍\n3为修改景点间的路径\n"))
    if (sr==1):
        sr1 = str(input("输入你要更改的的景点名称"))
        sr2 = str(input("输入更改后的的景点名称"))
        for i in range(len(na)):
            if (sr1 == na[i]):
                jd1 = i
        na[jd1]=sr2
        f = open("maolog.txt", "w")
        for i in range(len(na)):
            f.write(na[i])
            f.write('\r')
            f.write(str(i + 1))
            f.write('\r')
            f.write(intoduce[i])
            if (i != len(na) - 1):
                f.write('\r')
        f.close()
    if (sr==2):
        sr1 = str(input("输入你要更改的的景点名称"))
        sr2 = str(input("输入修改后景点介绍"))
        for i in range(len(na)):
            if (sr1 == na[i]):
                jd1 = i
        intoduce[jd1]=sr2
        f = open("maplog.txt", "w")
        for i in range(len(na)):
            f.write(na[i])
            f.write('\r')
            f.write(str(i + 1))
            f.write('\r')
            f.write(intoduce[i])
            if (i != len(na) - 1):
                f.write('\r')
        f.close()
    if (sr == 3):
        sr1 = str(input("输入你要更改的的第一个景点名称"))
        sr2 = str(input("输入你要更改的的第二个景点名称"))
        p=int(input("输入更改后的两点距离"))
        for i in range(len(na)):
            if (sr1 == na[i]):
                jd1 = i
            if (sr2 == na[i]):
                jd2 = i
        napath[jd1][jd2]=p
        try:
            f = open("pathlog.txt", "w")
        except IOError:
            print("文件不存在")
        else:
            for i in range(len(na)):
                for j in range(len(na)):
                    f.write(str(napath[i][j]))
                    f.write( " ")
                f.write('\r')
            f.close()
if sl==6:
    def findAllPath(graph, start, end, path6=[]):
        path6 = path6 + [start]
        if start == end:
            return [path6]

        paths = []  # 存储所有路径
        for node in graph[start]:
            if node not in path6:
                newpaths = findAllPath(graph, node, end, path6)
                for newpath in newpaths:
                    paths.append(newpath)
        return paths

    cway = [[] for i in range(len(na))]
    graph = {}
    glo = {}
    for i in range(len(na)):
        for j in range(len(na)):
            if (napath[i][j]!=0 and napath[i][j]!=100):
                cway[i].append(na[j])
    for i in range(len(cway)):
        glo={na[i]:cway[i]}
        graph.update(glo)
    #print(graph)
    sr1 = str(input("输入你要查找的的第一个景点名称"))
    sr2 = str(input("输入你要查找的的第二个景点名称"))
    for i in range(len(na)):
        if (sr1 == na[i]):
            jd1 = i
        if (sr2 == na[i]):
            jd2 = i
    allpath = findAllPath(graph, na[jd1], na[jd2])
    print('\n所有路径：', allpath)
