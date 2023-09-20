[toc]

# 1 使用OKChain API接口
OKChain是OKEx交易平台所建立的公链，它的API接口主要是为了与OKEx交易平台进行交互和集成。
要使用OKChain提供的API接口，你可以按照以下步骤进行：

1. 首先，你需要注册一个OKChain账号并获取你的API密钥（API Key）和密钥（Secret Key）。你可以在OKChain的官方网站上完成注册和申请。

2. 一旦你拥有了API密钥和密钥，你可以使用任何支持HTTP请求的编程语言（比如Python、JavaScript、Java等）来发送HTTP请求来调用OKChain的API接口。

3. 在每个API请求中，你需要包含以下信息：

   - API Key（作为请求头中的X-API-KEY参数）：用来标识你的API密钥。
   - Timestamp（作为请求头中的X-API-TIMESTAMP参数）：当前的时间戳。
   - Signature（作为请求头中的X-API-SIGNATURE参数）：根据API Key、Timestamp和请求参数计算出的签名值。
   - 请求参数：根据API接口文档指定的参数，包括方法名、参数值等。

4. 通过发送HTTP请求来调用OKChain的API接口，可以获取到所需的数据或执行所需的操作。根据你的具体需求，你可以调用不同的API接口，如获取账户信息、查询交易信息、发起交易等。

请注意，确保在使用OKChain的API接口时，遵守OKChain的使用条款和限制，并按照官方提供的API文档使用正确的参数和方式调用API接口。

https://github.com/okex/okchain

# 2 OKChain

- 技术架构：OKChain基于Tendermint共识算法和Cosmos SDK开发框架构建。Tendermint采用权益证明(PoS)共识机制，具有高吞吐量和快速确认的特点，可以实现快速的交易处理和区块生成。Cosmos SDK提供了开发区块链应用的工具和模块，使开发者可以构建自己的定制化区块链应用。

https://www.delicacydaily.com/cn/oktc

开发指南：
https://www.delicacydaily.com/cn/oktc/docs/dev/quick-start/overview

git获取
git clone -b mainnet https://github.com/okx/exchain