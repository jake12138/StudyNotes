1. get-apt
  **作用**：主要用于自动从互联网的软件仓库中搜索、安装、升级、卸载软件或操作系统
  **参数**：
  - ```apt-get update``` 更新源文件，并不会做任何安装升级操作. 这里的源文件是记录了安装包与其对应的下载地址的对应关系。
  - ```apt-get upgrade``` 升级所有已安装的包
  - ```apt-get install <packagename>``` 安装指定包名的包。
    A、下载的软件的存放位置：/var/cache/apt/archives

    B、安装后软件的默认位置：/usr/share

    C、可执行文件位置：/usr/bin

    D、配置文件位置：/etc

    E、lib文件位置：/usr/lib
  - ```sudo apt-get source <packagename>``` 下载该包名的源码
  - ```apt-get remove <packagename>``` 删除指定的包
  - ```apt-get remove -- purge <packagename> ``` 删除包，包括删除配置文件等
  - ```apt-get clean``` 清除无用的包
  - ```apt-get check``` 检查是否有损坏的依赖