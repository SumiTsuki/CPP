# CMake

## 1. C/C++编译过程

1. 预处理
2. 编译
3. 汇编
4. 链接

### 1.1 预处理

```bash
gcc -E main.c -o main.i
g++ -E main.cpp -o main.ii
```

**作用:**

1. 去掉注释
2. 预处理指令替换
3. 头文件替换

### 1.2 编译

```
gcc -S main.i -o main.s
g++ -S main.ii -o main.s
```

**作用:**

1. 将预处理后的代码翻译成汇编语言
2. 进行语法分析,语义分析,类型检查

### 1.3 汇编

```bash
gcc -c main.s -o main.o
g++ -c main.s -o main.o
```

**作用:**

1. 将汇编代码翻译成二进制
2. 每个 `.cpp` 文件都会生成一个 `.o` 文件
3. 生成的 `.o` 目标文件不能独立运行

### 1.4 链接

```bash
gcc main.o -o main
g++ main.o -o main
```

**作用:**

1. 将所有 `.o` 文件合并
2. 把库中的函数符号填充进去
3. 处理外部符号,全局变量,函数地址

## 2. 静态库与动态库

### 2.1 静态库

**创建静态库:**

首先编译源文件为目标文件 `g++ -c [src] -o [obj]` .
然后将目标文件归档成静态库 `ar rcs lib[staticlib] [obj]` .

**使用静态库:**

`g++ main.cpp -o main -L[staticlibpath] -l[staticlibname]`

静态库在编译阶段时会被链接到可执行程序中.
当多个程序使用同一个静态库时,会重复包含静态库,造成硬盘和内存空间的浪费.
更新静态库时,也要重新编译使用了该静态库的二进制文件.

### 2.2 动态库

**创建动态库:**

首先生成与位置无关的目标文件 `g++ -c -fPIC [src] -o [obj]` .
然后将目标文件生成动态链接库 `g++ -shared [obj] -o lib[sharedlib]`

**使用动态库:**

`g++ main.cpp -o main -L[sharedlibpath] -l[sharedlibname]`

然后可以将动态库文件复制到 `/lib` 或 `/usr/lib` 下(Linux),即可运行(不建议).
也可以设置环境变量指定动态库路径 `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:[sharedlibpath]` (仅影响当前shell会话).
或者在编译可执行程序时指定动态库位置, `g++ main.cpp -o main -L[sharedlibpath] -l[sharedlibname] -Wl,-rpath=[sharedlibpath]` .

多个程序共享同一个动态库,节省了内存和存储空间.
更新动态库时,不需要重新编译或链接依赖该库的程序,只需更新动态库文件即可,不需要重新编译程序,只要接口保持一致,程序就能直接使用新版本的动态库.

## 3. CMake
