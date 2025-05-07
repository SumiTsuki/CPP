# CMake

## 1. C/C++编译过程

1. 预处理
2. 编译
3. 汇编
4. 链接

### 1.1 预处理

```
gcc -E main.c -o main.i
cpp main.c -o main.i

g++ -E main.cpp -o main.ii
cpp main.cpp -o main.ii
```

**作用:**

1. 去掉注释
2. 预处理指令替换
3. 头文件替换

### 1.2 编译

```
gcc -S main.i -o main.s
g++ -S main.ii -o main.s
cc -S main.i -o main.s
```

**作用:**

1. 将预处理后的代码翻译成汇编语言
2. 进行语法分析,语义分析,类型检查

### 1.3 汇编

```
gcc -c main.s -o main.o

g++ -c main.s -o main.o
```

**作用:**

1. 将汇编代码翻译成二进制
2. 每个 `.cpp` 文件都会生成一个 `.o` 文件
2. 生成的 `.o` 目标文件不能独立运行

### 1.4 链接

```
gcc main.o -o main

g++ main.o -o main
```

**作用:**

1. 将所有 `.o` 文件合并
2. 把库中的函数符号填充进去
3. 处理外部符号,全局变量,函数地址
