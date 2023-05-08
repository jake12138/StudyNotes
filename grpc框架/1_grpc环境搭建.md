# 1 安装protobuf
1. 安装通用的编译器
地址： https://github.com/protocolbuffers/protobuf/releases
下载对应系统的protoc
将protoc执行程序cp到环境PATH中（/usr/bin）下，方便在终端调用
2. 安装go专用的protoc的生成器
    ```shell
    go get github.com/golang/protobuf/protoc-gen-go
    ```
    安装后会在GOPATH目录下生成可执行文件，protobuf的编译器插件protoc-gen-go
    执行protoc命令会自动调用插件
    <font color=gray>(注意在使用在使用该命令时，如果不成功，就在包含go.mod的路径下执行)</front>

# 2 protobuf介绍
## 2.1 .proto文件格式