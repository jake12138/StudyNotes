[toc]
# 1 scons安装
## 1.1 ubuntu上安装scons
1. 安装python
   因为sCons是采用python脚本编写的。
   ```shell
    sudo apt-get install python3
   ```
   安装完成后在终端执行```python -V```可以查看python的版本,SCons适配的python版本为2.7.x或者3.5以后的版本.
   <table><tr><td bgcolor="black">
   <font color=white>
   jake@JK:~$ python -V</br>
    Python 3.6.9</br>
   </font>
   </td></tr></table>

2. 安装sCons
   ```shell
   python3 -m pip install scons
   ```

# 2 简单编译
使用scons进行编译的时候需要创建SConstruct文件，在里面编写编译规则，然后在同级目录的终端执行scons命令即可进行编译。


示例：
<table><tr><td bgcolor=gray></br>

```c++
// main.cpp程序
#include<iostream>
using namespace std;
 
int main()
{
    cout << "Hello, World!" << endl;
    return 0;
}
```

```python
# SConstruct文件
Program('main.cpp')
```

</td></tr></table>

在执行scons编译后，会在编译目录下留下一些编译文件，如需要在删除这些编译文件(包括目标文件)，可以使用
  ```
  scons -c
 ```

# 3 SConstruct文件

SConstruct文件实际上就是一个Python脚本。可以在SConstruct文件中使用Python的注释.
重要的一点是SConstruct文件并不完全像一个正常的Python脚本那样工作，其工作方式更像一个Makefile，那就是在SConstruct文件中SCons函数被调用的顺序并不影响SCons你实际想编译程序和目标文件的顺序。换句话说，当你调用Program方法，你并不是告诉SCons在调用这个方法的同时马上就编译这个程序，而是告诉SCons你想编译这个程序。

<table><tr><td bgcolor=gray></br>

```python
# 这会编译出两个可执行程序
print("build main")
Program('main.cpp')
print("build hello")
Program('hello.cpp')
print("end build")
```

```shell
# 执行scons的输出（输出打印跟编写的顺序并不一致）
scons: Reading SConscript files ...
build main
build hello
end build
scons: done reading SConscript files.
scons: Building targets ...
g++ -o hello.o -c hello.cpp
g++ -o hello hello.o
g++ -o main.o -c main.cpp
g++ -o main main.o
scons: done building targets.
```
</td></tr></table>

# 4 scons语法
## 4.1 编译多个源文件
通常情况下，你需要使用多个输入源文件编译一个程序。在SCons里，只需要就多个源文件放到一个Python列表中就行了
```python
# 将main.cpp和test.cpp文件编译成mytest可执行程序
Program('mytest',['main.cpp','test.cpp'])
```

- 可以使用Glob函数来定义定义一个匹配规则来指定源文件列表，比如*,?以及[abc]等标准的shell模式
  ```python
  Program('program',Glob('*.cpp'))
  ```
- 为了更容易处理文件名长列表，SCons提供了一个Split函数，这个Split函数可以将一个用引号引起来，并且以空格或其他空白字符分隔开的字符串分割成一个文件名列表，示例如下：
  ```python
  Program('program', Split('main.cpp  file1.cpp  file2.cpp'))

  # 或者
  src_files=Split('main.cpp  file1.cpp  file2.cpp')
  Program('program', src_files)
  ```

- SCons允许使用Python关键字参数来标识输出文件和输入文件。输出文件是target，输入文件是source，示例如下：
  ```python
  src_files=Split('main.cpp  file1.cpp  file2.cpp')
  Program(target='program', source=src_files)
  
  # 或者：
  src_files=Split('main.cpp  file1.cpp  file2.cpp')
  Program(source=src_files, target='program')
  ```
  如果需要用同一个SConstruct文件编译多个程序，只需要调用Program方法多次：
  ```python
  Program('foo.cpp')
  Program('bar', ['bar1.cpp', 'bar2.cpp'])
  ```

## 4.2 编译静态库文件

```python
# 编译生成 libltest.a静态库文件
Library('ltest',['test.cpp'])
```

除了使用源文件外，Library也可以使用目标文件
```python
Library('foo', ['f1.c', 'f2.o', 'f3.c', 'f4.o'])
```

你甚至可以在文件List里混用源文件和目标文件
```python
lib_srcs = Split('f1.cpp f2.o f3.c f4.0')
Library('foo', lib_srcs)
```
使用StaticLibrary显示编译静态库
```python
StaticLibrary('foo', ['f1.cpp', 'f2.cpp', 'f3.cpp'])
```

## 4.3 编译动态库：
如果想编译动态库（在POSIX系统里）或DLL文件（Windows系统），可以使用SharedLibrary：

```python
SharedLibrary('foo', ['f1.cpp', 'f2.cpp', 'f3.cpp'])
```

## 4.4 链接库文件

```python
Library("ltest",Split("test.cpp"))
# 注意在运行时要执行下"export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:."
# 临时导入下环境变量以便程序能够找到生成的库
Program(target="main", source="main.cpp", LIBS=["ltest"], LIBPATH=".")
```

# 5 节点对象
所有编译方法会返回一个节点对象列表，这些节点对象标识了那些将要被编译的目标文件。这些返回出来的节点可以作为参数传递给其他的编译方法。例如，假设我们想编译两个目标文件，这两个目标有不同的编译选项，并且最终组成一个完整的程序。这意味着对每一个目标文件调用Object编译方法，如下所示：
```python
Object('hello.cpp', CCFLAGS='-DHELLO')
Object('goodbye.cpp', CCFLAGS='-DGOODBYE')
Program(['hello.o', 'goodbye.o'])
```

这样指定字符串名字的问题就是我们的SConstruct文件不再是跨平台的了。因为在Windows里，目标文件成为了hello.obj和goodbye.obj。一个更好的解决方案就是将Object编译方法返回的目标列表赋值给变量，这些变量然后传递给Program编译方法： 
```python
hello_list = Object('hello.cpp', CCFLAGS='-DHELLO')
goodbye_list = Object('goodbye.c', CCFLAGS='-DGOODBYE')
Program(hello_list + goodbye_list)
```

