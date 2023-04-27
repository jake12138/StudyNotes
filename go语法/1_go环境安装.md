[toc]
# 1 安装go环境
- 下载对应的go版本
https://golang.google.cn/doc

- 解压到/usr/bin下
    ```shell
    tar -C /usr/local/ -xzf go1.18.1.linux-amd64.tar.gz
    ```
- 配置环境变量
    ```shell
    # 在/etc/profile中添加
    export PATH=$PATH:/usr/local/go/bin

    # 使添加的环境变量立即生效 或者重启
    source /etc/profile

    # 查看go版本，成功则说明环境配置成功
    go version
    ```
- 更改下载源的代理，这样后面下载包会快
    ```shell
    #开启go module (go1.11版本以上)
    go env -w GO111MODULE=on
    # 更改下载源的代理
    go env -w GOPROXY=https://goproxy.io,direct

    # 原始为 GOPROXY="https://proxy.golang.org,direct"
    ```

# 2 go环境变量
环境变量可以用```go env```命令来查看
**GOROOT**：   这是go环境所在位置
**GOPATH**：  将来GO项目所在的位置。GOPATH下有3个文件夹bin、src、package我们的项目源文件方在src目录下，package下存放编译好的包，bin下为可执行程序. 如果电脑上没有$GOPATH，就手动创建

# 3 更换go版本
将/usr/local/go下的文件全部删除，然后重新配置即可

# 4 go 介绍
**特性**
**语法简单** Go在自由与灵活上做了取舍，以此换来了更好的维护性和更低的学习难度。
**交叉编译** 允许跨平台编译代码。
**天然并发** Go语言对并发的支持是纯天然的，语法上只需要一个go关键字就能开启一个协程。
**垃圾回收** GC算不上很出色，但还比较靠谱。
**静态链接** 简化了部署操作，无需安装任何运行环境和诸多第三方库。
**内存分配** 可以说，除偶尔因性能问题而被迫采用对象池和自主内存管理外，基本无须参与内存管理操作。

Go语言抛弃了继承，弱化了OOP，类，元编程，泛型，Lamda表达式等这些特性，拥有不错的性能和较低的上手难度。Go语言非常适合用于云服务开发，应用服务端开发，甚至可以进行部分Linux嵌入式开发，不过由于带有垃圾回收，其性能肯定无法媲美C/C++这类系统级语言，但Go在其擅长的领域表现十分出色。虽然面世只有13年，但也已经有大量的行业采用了Go作为首选语言，总的来说这是一门非常年轻且具有活力的现代语言，值得一学。

# vscode下配置go环境
- 下载go插件---关键字go
- 在$GOPATH/src下创建一个go项目并初始化
    ```shell
    $ cd $GOPATH/src/hello
    $ go mod init
    ```
    ```go mod init```会创建go.mod文件和go.sum文件，go.mod文件是记录我们依赖库以及版本号
- 以后编写完代码后执行```go mod tidy```即可，这个命令会自动下载依赖的库，也会删除多余的库



http://idea.javatiku.cn/