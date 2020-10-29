import matplotlib.pyplot as plt
import tkinter as tk
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
window = tk.Tk()
tsk = [1]
window.title('商店系统')
window.geometry('500x300')
var = tk.StringVar()
l = tk.Label(window, bg='yellow', width=20, text='请选择你的模式')
l.pack()


def print_selection():
    l.config(text='你选择的模式是' + var.get())


def hit_me():
    tsk[0] = (var.get())
    window.destroy()


r1 = tk.Radiobutton(window, text='对商品进行入库', variable=var, value=1, command=print_selection)
r1.pack()
r2 = tk.Radiobutton(window, text='对商品进行出库', variable=var, value=2, command=print_selection)
r2.pack()
r3 = tk.Radiobutton(window, text='对商品进行删除', variable=var, value=3, command=print_selection)
r3.pack()
r4 = tk.Radiobutton(window, text='对商品进行修改', variable=var, value=4, command=print_selection)
r4.pack()
r5 = tk.Radiobutton(window, text='对商品进行查询', variable=var, value=5, command=print_selection)
r5.pack()
bo = tk.Button(window, text='确定', font=('Arial', 12), width=10, height=1, command=hit_me)
bo.pack()
window.mainloop()
j = int(tsk[0])
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
    f.close()
#入库
if(j==1):
    window = tk.Tk()
    window.title('My Window')
    window.geometry('500x300')
    intsk = [0, 0]
    e1 = tk.Entry(window, show=None)
    e1.pack()
    e2 = tk.Entry(window, show=None)
    e2.pack()
    e1.insert('insert', "请输入商品名称")
    e2.insert('insert', "请输入数量")


    def insert_point():
        intsk[0] = e1.get()
        intsk[1] = e2.get()
        window.destroy()


    b1 = tk.Button(window, text='确定', width=10,
                   height=2, command=insert_point)
    b1.pack()
    window.mainloop()
    na = intsk[0]
    nu = int(intsk[1])

    jk=-1
    for i in range(len(LI)):
        if (LI[i].name == na):
            jk=i
            break
    if(jk==-1):
        sor = myclass.make_struct(na, len(LI)+1,nu)
        f = open("log.txt", "w")
        for i in range(len(LI)):
            f.write(LI[i].name)
            f.write('\r')
            f.write(str(i + 1))
            f.write('\r')
            f.write(LI[i].kc)
            f.write('\r')
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
    plt.title('商品清单')
    plt.show()

#出库
if(j==2):
    window = tk.Tk()
    window.title('My Window')
    window.geometry('500x300')
    intsk = [0, 0]
    e1 = tk.Entry(window, show=None)
    e1.pack()
    e2 = tk.Entry(window, show=None)
    e2.pack()
    e1.insert('insert', "请输入商品名称")
    e2.insert('insert', "请输入数量")


    def insert_point():
        intsk[0] = e1.get()
        intsk[1] = e2.get()
        window.destroy()


    b1 = tk.Button(window, text='确定', width=10,
                   height=2, command=insert_point)
    b1.pack()
    window.mainloop()
    na = intsk[0]
    nu = int(intsk[1])
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
        plt.title('商品清单')
        plt.show()
    else:
        print("该商品不存在")
#删除
if(j==3):
    window = tk.Tk()
    intsk = [0, 0]
    window.title('商品系统')
    window.geometry('500x300')
    var = tk.StringVar()
    l = tk.Label(window, bg='yellow', width=20, text='请输入你要选择的删除方式')
    l.pack()


    def print_selection():
        l.config(text='你选择的模式是' + var.get())


    def hit_me():
        intsk[0] = (var.get())
        intsk[1] = e1.get()
        window.destroy()


    r1 = tk.Radiobutton(window, text='1为名字删除', variable=var, value=1, command=print_selection)
    r1.pack()
    r2 = tk.Radiobutton(window, text='2为序号删除', variable=var, value=2, command=print_selection)
    r2.pack()
    e1 = tk.Entry(window, show=None)
    e1.insert('insert', "请输入相应的信息")
    e1.pack()
    b = tk.Button(window, text='确定', font=('Arial', 12), width=10, height=1, command=hit_me)
    b.pack()
    window.mainloop()
    k = int(intsk[0])
    na = intsk[1]

    if(k==1):
        #na=str(input("输入要删除的名字"))
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
            plt.title('商品清单')
            plt.show()
        else:
            print("商品不存在")
    if (k == 2):
        jk = -1
        #na = str(input("输入要删除的序号"))
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
            plt.title('商品清单')
            plt.show()
        else:
            print("商品不存在")
if(j==4):

    window = tk.Tk()
    intsk = [0, 0, 0]
    window.title('商品系统')
    window.geometry('500x300')
    var = tk.StringVar()
    l = tk.Label(window, bg='yellow', width=20, text='请输入你要选择的修改的数据的方法')
    l.pack()


    def print_selection():
        l.config(text='你选择的模式是' + var.get())


    def hit_me():
        intsk[0] = (var.get())
        intsk[1] = e1.get()
        intsk[2] = e2.get()
        window.destroy()


    r1 = tk.Radiobutton(window, text='1为修改名称', variable=var, value=1, command=print_selection)
    r1.pack()
    r2 = tk.Radiobutton(window, text='2为修改数量', variable=var, value=2, command=print_selection)
    r2.pack()
    e1 = tk.Entry(window, show=None)
    e2 = tk.Entry(window, show=None)
    e1.insert('insert', "输入要更改的商品名")
    e1.pack()
    e2.insert('insert', "输入要更改后的数据")
    e2.pack()
    b = tk.Button(window, text='确定', font=('Arial', 12), width=10, height=1, command=hit_me)
    b.pack()
    window.mainloop()
    k = int(intsk[0])
    nn = intsk[1]
    na = intsk[2]
    if (k == 1):
        #nn = str(input("输入要更改的实验器材名"))
        #na = str(input("输入要更改后的实验器材名"))
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
            plt.title('商品清单')
            plt.show()
        else:
            print("商品不存在")
    if (k == 2):
        #nn = str(input("输入要更改的实验器材名"))
        #na = str(input("输入要更改后的实验器材数量"))
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
            plt.title('商品清单')
            plt.show()
        else:
            print("商品不存在")
if(j==5):
    window = tk.Tk()
    window.title('My Window')
    window.geometry('500x300')
    intsk = [0]
    e1 = tk.Entry(window, show=None)
    e1.pack()
    e1.insert('insert', "输入要查询的名字")


    def insert_point():
        intsk[0] = e1.get()
        window.destroy()


    b1 = tk.Button(window, text='确定', width=10,
                   height=2, command=insert_point)
    b1.pack()
    window.mainloop()
    na = intsk[0]

    for i in range(len(LI)):
        if (LI[i].name == na):
            plt.bar(LI[i].name, int(LI[i].kc))
            plt.title('商品清单')
            plt.show()
            i=-1
            break
        f.close()
    if(i!=-1):
        print("商品不存在")