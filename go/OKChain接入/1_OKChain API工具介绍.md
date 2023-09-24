[toc]

# 1 OKChain介绍

- 技术架构：OKChain基于Tendermint共识算法和Cosmos SDK开发框架构建。Tendermint采用权益证明(PoS)共识机制，具有高吞吐量和快速确认的特点，可以实现快速的交易处理和区块生成。Cosmos SDK提供了开发区块链应用的工具和模块，使开发者可以构建自己的定制化区块链应用。

https://www.delicacydaily.com/cn/oktc

开发指南：
https://www.delicacydaily.com/cn/oktc/docs/dev/quick-start/overview
https://www.ouxyi.club/cn/oktc/docs/dev/quick-start/overview
https://www.denbiao.com/cn/oktc/docs/dev/quick-start/overview


<font color=red>注意</font>
- https://www.okex.me/  网址不可信

git获取
git clone -b mainnet https://github.com/okx/exchain

# 2 安装OKTC工具
参考网址：https://www.delicacydaily.com/cn/oktc/docs/dev/quick-start/install-oktc
```shell
# 获取下载OKT工具C
git clone https://github.com/okx/exchain

# 开启GO module
export GO111MODULE=on

cd exchain 

# 安装前置
make rocksdb

# 编译主网
make mainnet

# 编译测试网
make testnet
```

**注意**:
- OKTC要求go环境且版本在1.17及其以上。执行make命令的时候又可能会提示需要更高的go版本。

**验证是否安装成功**：
```shell
exchaind version --long
exchaincli version --long
```

# 3 安装go开发工具包
```shell
go get github.com/okx/exchain-go-sdk
```
**注意**：
- 执行命令后可能提示
<table><tr><td bgcolor=black>
<font color= white>
go: github.com/okx/exchain-go-sdk@v1.5.6: parsing go.mod:</br>
module declares its path as: github.com/okex/exchain-go-sdk</br>
but was required as: github.com/okx/exchain-go-sdk</br>
</font>
</td></tr></table>
需要在go.mod中添加
```go

```

# 3 概念和名词

- **TPS**： 每秒交易单数
- **Dpos**： 委托权益证明


# API接口文档地址
https://www.delicacydaily.com/cn/oktc/docs/dev/api/oktc-api/http