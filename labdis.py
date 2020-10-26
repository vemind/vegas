import os
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
class Myclass(object):
    class Struct(object):
        def __init__(self, name, nuber,kc):
            self.name = name
            self.nuber = nuber
            self.kc = kc

    def make_struct(self, name, nuber,kc):
        return self.Struct(name, nuber,kc)

myclass = Myclass()
print("请选择你要执行的功能")
print("输入1对实验器材进行入库")
print("输入2对实验器材进行出库")
print("输入3对实验器材进行删除")
print("输入4对实验器材进行修改")
print("输入5对实验器材进行查询")
LI = []
#打开文件
try:
    f = open("log.txt", "r+")
except IOError:
    print("文件不存在")
else:

    i = 0
    while 1:
        n = f.readline()
        if n == '':
            break
        s = f.readline()
        k = f.readline()
        n = n[:-1]
        s = s[:-1]
        k = k[:-1]
        sor= myclass.make_struct(n, s,k)
        LI .append(sor)
        #print (LI[i].name)
        #print (LI[i].nuber)
        i = i + 1
j=int(input())
#入库
if(j==1):
    na=input("请输入实验器材名称")
    nu=input("请输入实验器材数量")
    jk=-1
    for i in range(len(LI)):
        if (LI[i].name == na):
            jk=i
            break
    if(jk==-1):
        sor = myclass.make_struct(na, len(LI)+1,nu)
        f.write(sor.name)
        f.write('\r')
        f.write(str(sor.nuber))
        f.write('\r')
        f.write(str(sor.kc))
        f.write('\r')
        f.close()
    else:
        LI[i].kc = str(int(LI[i].kc) +int(nu))
        f.close()
        f = open("log.txt", "w")
        i = 0
        for i in range(len(LI)):
            f.write(LI[i].name)
            f.write('\r')
            f.write(str(i + 1))
            f.write('\r')
            f.write(LI[i].kc)
            f.write('\r')
        f.close()
    LI = []
    # 打开文件
    try:
        f = open("log.txt", "r+")
    except IOError:
        print("文件不存在")
    else:
        i = 0
        while 1:
            n = f.readline()
            if n == '':
                break
            s = f.readline()
            k = f.readline()
            n = n[:-1]
            s = s[:-1]
            k = k[:-1]
            sor = myclass.make_struct(n, s, k)
            LI.append(sor)
            # print (LI[i].name)
            # print (LI[i].nuber)
            i = i + 1
    syster =[]
    buy_number=[]
    for i in range(len(LI)):
        syster.append(LI[i].name)
        buy_number.append(int(LI[i].kc))
    #print(syster)
    #print(buy_number)
    plt.bar(syster, buy_number)
    plt.title('***********')
    plt.show()

#出库
if(j==2):
    na = input("请输入实验器材名称")
    nu = input("请输入实验器材数量")
    jk=-1
    for i in range(len(LI)):
        if (LI[i].name == na):
            jk = i
            break
    if (jk != -1):
        LI[jk].kc = str(int(LI[jk].kc)-int(nu))
        if(int(LI[jk].kc)<=0):
            LI.pop(jk)
        f.close()
        f = open("log.txt", "w")
        for i in range(len(LI)):
            f.write(LI[i].name)
            f.write('\r')
            f.write(str(i+1))
            f.write('\r')
            f.write(LI[i].kc)
            f.write('\r')
        f.close()
        LI = []
    # 打开文件
        try:
            f = open("log.txt", "r+")
        except IOError:
            print("文件不存在")
        else:
            i = 0
            while 1:
                n = f.readline()
                if n == '':
                    break
                s = f.readline()
                k = f.readline()
                n = n[:-1]
                s = s[:-1]
                k = k[:-1]
                sor = myclass.make_struct(n, s, k)
                LI.append(sor)
                # print (LI[i].name)
                # print (LI[i].nuber)
                i = i + 1
        syster =[]
        buy_number=[]
        for i in range(len(LI)):
            syster.append(LI[i].name)
            buy_number.append(int(LI[i].kc))
        #print(syster)
        #print(buy_number)
        plt.bar(syster, buy_number)
        plt.title('***********')
        plt.show()
    else:
        print("该实验器材不存在")
#删除
if(j==3):
    k=int(input("请输入你要选择的删除方式 \n1为名字删除\n2为序号删除"))
    if(k==1):
        na=str(input("输入要删除的名字"))
        jk=-1
        for t in range(len(LI)):
            for i in range(len(LI)):
                if (LI[i].name == na):
                    LI.pop(i)
                    jk =i
                    break
        if(jk!=-1):
            f.close()
            f = open("log.txt", "w")
            for i in range(len(LI)):
                f.write(LI[i].name)
                f.write('\r')
                f.write(str(i + 1))
                f.write('\r')
                f.write(LI[i].kc)
                f.write('\r')
            f.close()
            LI = []
            # 打开文件
            try:
                f = open("log.txt", "r+")
            except IOError:
                print("文件不存在")
            else:
                i = 0
                while 1:
                    n = f.readline()
                    if n == '':
                        break
                    s = f.readline()
                    k = f.readline()
                    n = n[:-1]
                    s = s[:-1]
                    k = k[:-1]
                    sor = myclass.make_struct(n, s, k)
                    LI.append(sor)
                    # print (LI[i].name)
                    # print (LI[i].nuber)
                    i = i + 1
            syster = []
            buy_number = []
            for i in range(len(LI)):
                syster.append(LI[i].name)
                buy_number.append(int(LI[i].kc))
            # print(syster)
            # print(buy_number)
            plt.bar(syster, buy_number)
            plt.title('***********')
            plt.show()
        else:
            print("实验器材不存在")
    if (k == 2):
        jk = -1
        na = str(input("输入要删除的序号"))
        for i in range(len(LI)):
            if (LI[i].nuber == na):
                    LI.pop(i)
                    jk = i
                    break
        if (jk != -1):
            f.close()
            f = open("log.txt", "w")
            for i in range(len(LI)):
                f.write(LI[i].name)
                f.write('\r')
                f.write(str(i + 1))
                f.write('\r')
                f.write(LI[i].kc)
                f.write('\r')
            f.close()
            LI = []
            # 打开文件
            try:
                f = open("log.txt", "r+")
            except IOError:
                print("文件不存在")
            else:
                i = 0
                while 1:
                    n = f.readline()
                    if n == '':
                        break
                    s = f.readline()
                    k = f.readline()
                    n = n[:-1]
                    s = s[:-1]
                    k = k[:-1]
                    sor = myclass.make_struct(n, s, k)
                    LI.append(sor)
                    # print (LI[i].name)
                    # print (LI[i].nuber)
                    i = i + 1
            syster = []
            buy_number = []
            for i in range(len(LI)):
                syster.append(LI[i].name)
                buy_number.append(int(LI[i].kc))
            # print(syster)
            # print(buy_number)
            plt.bar(syster, buy_number)
            plt.title('***********')
            plt.show()
        else:
            print("实验器材不存在")
if(j==4):
    k = int(input("请输入你要选择的修改的数据 \n1为修改名称\n2为修改数量"))
    if (k == 1):
        nn = str(input("输入要更改的实验器材名"))
        na = str(input("输入要更改后的实验器材名"))
        jk = -1
        for i in range(len(LI)):
            if (LI[i].name == nn):
                jk = i
                break
        if (jk != -1):
            LI[i].name = na
            f.close()
            f = open("log.txt", "w")
            for i in range(len(LI)):
                f.write(LI[i].name)
                f.write('\r')
                f.write(str(i + 1))
                f.write('\r')
                f.write(LI[i].kc)
                f.write('\r')
            f.close()
            LI = []
            # 打开文件
            try:
                f = open("log.txt", "r+")
            except IOError:
                print("文件不存在")
            else:
                i = 0
                while 1:
                    n = f.readline()
                    if n == '':
                        break
                    s = f.readline()
                    k = f.readline()
                    n = n[:-1]
                    s = s[:-1]
                    k = k[:-1]
                    sor = myclass.make_struct(n, s, k)
                    LI.append(sor)
                    # print (LI[i].name)
                    # print (LI[i].nuber)
                    i = i + 1
            syster = []
            buy_number = []
            for i in range(len(LI)):
                syster.append(LI[i].name)
                buy_number.append(int(LI[i].kc))
            # print(syster)
            # print(buy_number)
            plt.bar(syster, buy_number)
            plt.title('***********')
            plt.show()
        else:
            print("实验器材不存在")
    if (k == 2):
        nn = str(input("输入要更改的实验器材名"))
        na = str(input("输入要更改后的实验器材数量"))
        jk = -1
        for i in range(len(LI)):
            if (LI[i].name == nn):
                jk = i
                break
        if (jk != -1):
            LI[i].kc = na
            f.close()
            f = open("log.txt", "w")
            for i in range(len(LI)):
                f.write(LI[i].name)
                f.write('\r')
                f.write(str(i + 1))
                f.write('\r')
                f.write(LI[i].kc)
                f.write('\r')
            f.close()
            LI = []
            # 打开文件
            try:
                f = open("log.txt", "r+")
            except IOError:
                print("文件不存在")
            else:
                i = 0
                while 1:
                    n = f.readline()
                    if n == '':
                        break
                    s = f.readline()
                    k = f.readline()
                    n = n[:-1]
                    s = s[:-1]
                    k = k[:-1]
                    sor = myclass.make_struct(n, s, k)
                    LI.append(sor)
                    # print (LI[i].name)
                    # print (LI[i].nuber)
                    i = i + 1
            syster = []
            buy_number = []
            for i in range(len(LI)):
                syster.append(LI[i].name)
                buy_number.append(int(LI[i].kc))
            # print(syster)
            # print(buy_number)
            plt.bar(syster, buy_number)
            plt.title('***********')
            plt.show()
        else:
            print("实验器材不存在")
if(j==5):
        na=str(input("输入要查询的名字"))
        for i in range(len(LI)):
            if (LI[i].name == na):
                print("查找的商品序号为",LI[i].nuber)
                print("查找的商品库存为", LI[i].kc)
                i=-1
                break
        f.close()
        if(i!=-1):
            print("实验器材不存在")
os.system("pause")