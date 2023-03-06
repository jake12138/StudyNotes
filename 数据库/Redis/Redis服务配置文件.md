[toc]
# Redis服务配置文件
```shell
bind 127.0.0.1 # Redis服务运行的IP
port 6379 # Redis服务的端口号
deamonize no/yes # 是否以守护进程启动，为no的时候，在终端启动后，会在启动终端打日志。
                 #改为yes后就是在后台启动了，不会打印日志到终端。
# 在后台启动后，存储日志文件的路径名称
logfile "redis-servre-6379.log" 

# 日志文件和其他文件的存放目录
dir "/home/jake/redis/"
```