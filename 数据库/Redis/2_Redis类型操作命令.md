[toc]
# 1 Redis类型分类
Redis的类型分为string、hash、list、set、sorted_set六种基本类型。此外还有一些高级类型像Bitmaps、HyperLogLog、GEO.
**string**: 存储字符串的key-value键值对。
![string底层存储结构](img/string底层存储结构.png)
**hash**：key对应的不再是一个value, 而是一个数据结构。即一个key中保存了多对键值对数据。底层使用哈希表结构实现数据存储。
![hash底层存储结构](img/hash底层存储结构.png)
**list**:存储列表信息，一个key中可以存储多个value，通过数据可以体现数据的先后顺序，底层使用双向链表实现。
![list底层存储结构](img/list底层存储结构.png)
**set**：储存集合信息，一个key中包含多个value,适合存储大量数据，在查询方面能提供更高的效率。set中的值不允许重复。
底层存储结构与hash相同，但仅存储键，不存储值(nil)。
![set底层存储结构](img/set底层存储结构.png)
**sorted_set**：类似set数据类型，但sorted_set类型可以保存可排序数据。底层存储在set的基础上添加了可排序字段score.
![sorted_set底层存储结构](img/sorted_set底层存储结构.png)
其中score是用于排序，不是数据

-------------------------------------
# 2 string类型
string是Redis中的数据格式之一。是通过key-value的方式存储的。
## 2.2 string的操作命令
### 2.2.1 添加/修改数据
**添加/修改单个数据**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
set key value
```
</td></tr></table>
将key对应的值设置为value, 该命令可以用于添加或修改string类型的key对应的value.
_示例_：

```shell
set name jake # 设置name的值为jake
```
_结果_：
![set命令示例_1](img/set命令示例_1.png)
![set命令示例_1](img/set命令示例_2.png)
**添加/修改多个数据**
<table><tr><td bgcolor="87CEFA"></br>

```shell
mset key1 value1 key2 value2 ...
```
</td></tr></table>

_示例_：
![mset命令示例_1](img/mset命令示例_1.png)
### 2.2.2 获取数据
**获取单个数据**
<table><tr><td bgcolor="87CEFA"></br>

```shell
get key # 获取key对应的值
```
</td></tr></table>

**注意1**：如果没有对应的key，则输出(nil)
_示例_：
```shell
get name # 获取name对应的值
```
_结果_：
![get命令示例_1](img/get命令示例_1.png)
![get命令示例_1](img/get命令示例_2.png)
**获取多个数据**
<table><tr><td bgcolor="87CEFA"></br>

```shell
mget key1 key2 key3 ...
```
</td></tr></table>

_示例_：
![mget命令示例](img/mget命令示例_1.png)
### 2.2.3 删除数据
<table><tr><td bgcolor="87CEFA"></br>

```shell
del key # 删除string类型key对应的value
```
</td></tr></table>

**tips**：del 命令后面可以接多个key, 每个key用空格分开
_示例_：
<font color=Gray>返回的(integer)2说明成功删除了2个key, 如果输出的是(integer)0说明没有删除任何key(一般是没有对应的key)</font>

![del命令示例_1](img/del命令示例_2.png)

### 2.2.4 获取数据字符个数
<table><tr><td bgcolor="#87CEFA"></br>

```shell
strlen key # 获取key对应的字符串长度
```
</td></tr></table>

_示例_：
<font color=Gray>一个ASCCI码的长度算1。<font>
![strlen命令示例_1](img/strlen命令示例_1.png)
<font color=Gray>对于中文，一个字3字节。</font>
![strlen命令示例_2](img/strlen命令示例_2.png)
### 2.2.5 追加信息到原始值后面
<table><tr><td bgcolor="#87CEFA"></br>

```shell
append key value # 将value添加到原本key的值的后面
```

</td></tr></table>

_示例_:
<font color=Gray>append命令的输出(integer) 9表示追加字符后新的字符的长度（字节）。</font>
![append命令示例_1](img/append命令示例_1.png)

---------------------------------------------
# 3 Hash类型
![hash底层存储结构](img/hash底层存储结构.png)
## 3.1 Hash操作命令
### 3.1.1 添加/修改数据
**添加/修改单个hash filed数据**
<table><tr><td bgcolor="#84CEFA"></br>

```shell
hset key field value # 设置/添加key中的field字段为value
```
</td></tr></table>

_示例_:
![hset命令示例_1](img/hset命令示例_1.png)

**添加/修改hash多个filed数据**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 添加/修改hash多个filed数据
hmset key filed1 value1 filed2 value2...
```
</td></tr></table>

_示例_
<font color=Gray>设置person1的name字段为terry, age字段为24</font>
![hmset命令示例_1](img/hmset命令示例_1.png)

### 3.1.2 获取数据
**获取hash的单个filed数据**
<table><tr><td bgcolor="#84CEFA"></br>

```shell
hget key filed # 获取hash key的filed字段的值
```
</td></tr></table>

_示例_:
![hget命令示例_1](img/hget命令示例_1.png)

**获取hash的全部filed数据**
<table><tr><td bgcolor="87CEFA"></br>

```shell
hgetall key # 获取hash的key的全部filed信息
```
</td></tr></table>

_示例_：
![hgetall命令示例_1](img/hgetall命令示例_1.png)

**获取hash指定的多个filed数据**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取hash指定的filed1 filed2...数据
hmget key filed1 filed2 ...
```
</td></tr></table>

_示例_：
获取hash person1下的age和name字段的值
![hmget命令示例_1](img/hmget命令示例_1.png)

**仅添加不存在的hash filed信息，filed存在则不添加**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 设置hash的key的filed为value,如果filed已经存在则会执行失败
hsetnx key filed value
```
</td></tr></table>

_示例_：
<font color=Gray>如果执行成功会输出"(integer) 1", 执行失败会输出
"(integer) 0". 示例中线设置name字段，但因为name字段已经存在，所以会执行失败。后面设置email字段成功</font>
![hsetnx命令示例_1](img/hsetnx命令示例_1.png)

### 3.1.3 删除hash数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 删除hash key的filed1,filed2...字段
hdel key filed1 filed2 ... 
```
</td></tr></table>

_示例_：
![hdel命令示例_1](img/hdel命令示例_1.png)
### 3.1.4 获取hash表中字段的数量
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取hash表key中字段的数量
hlen key
```
</td></tr></table>

_示例_：
![hlen命令示例_1](img/hlen命令示例_1.png)
### 3.1.5 判断hash表中是否存在指定字段
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 判断hash表key中是否存在指定字段filed
hexists key filed
```
</td></tr></table>

_示例_：
![hexists命令示例_1](img/hexists命令示例_1.png)
### 3.1.6 获取hash表中所有的key
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取hash表中所有的key
hkeys key
```
</td></tr></table>

_示例_：
![hkeys命令示例_1](img/hkeys命令示例_1.png)
### 3.1.7 获取hash表中所有字段的值
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取hash表中所有字段的值
hvals key
```
</td></tr></table>

_示例_：
![hvals命令示例_1](img/hvals命令示例_1.png)
### 3.1.8 设置hash指定字段的数值数据增加指定大小
**设置int类型的数据增加指定大小**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取hash表key中的key字段的值增加increment的大小
hincrby key filed increment
```
</td></tr></table>

_示例_：
如果increment的大小为负数则表示'减去'
![hincrby命令示例_1](img/hincrby命令示例_1.png)
**注意**:
1.如果没有这个字段或者key，则会创建它并赋值为increment.
2. 如果filed字段不是int类型会执行失败
   ![hincrby命令示例_2](img/hincrby命令示例_2.png)

**设置float类型的数据增加指定大小**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取hash表key中的key字段的值增加increment的大小
hincrbyfloat key filed increment
```
</td></tr></table>

_示例_：
如果increment的大小为负数则表示'减去'
![hincrbyfloat命令示例_1](img/hincrbyfloat命令示例_1.png)
注意事项同hincrbyfloat命令

## 3.2 Hash类型原理
### 3.2.1 hash类型底层存储
hash类型的key对应的不是一个value, 而是一个数据结构。即一个key中保存了多对键值对数据，类似于C/C++的结构体。底层使用哈希表结构实现数据存储。
![hash底层存储结构](img/hash底层存储结构.png)
### 3.2.2 hash类型数据操作注意事项
- hash类型下的value只能存储字符串，不允许存储其他数据类型，不存在嵌套现象。
- 每个hash可以存储(2^32)-1个键值对
- hash类型十分贴近对象的数据存储形式，并且灵活添加/删除对象的属性。但hash的设计之初并不是为了存储大量对象而设计的，切记不可来滥用，更不可将hash作为对象列表使用。
- hgetall命令可以获取hash key的全部filed, 如果内部的filed过多，遍历整体数据效率就会很低，有可能成为数据访问瓶颈。

-----------------------------------------------
# 4 List类型
## 4.1 list类型操作命令
### 4.1.1 添加list数据
**从list的左边push数据**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 将数据从list的左边push进去
lpush key value1 value2 ...
```
</td></tr></table>

**示例**：
通过lpush进去的数据在内部的排列顺序为: orange,apple
![lpush命令示例_1](img/lpush命令示例_1.png)
**从list的右边push数据**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 将数据从list的右边push进去
rpush key value1 value2 ...
```
</td></tr></table>

**示例**：
通过lpush进去的数据在内部的排列顺序为: apple,orange
![rpush命令示例_1](img/rpush命令示例_1.png)

### 4.1.2 获取list数据
**获取指定list key索引范围内的value**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
#返回索引在区间[start,stop]的数据
lrange key start stop
```
</td></tr></table>

**示例**：
<font color=Gray>返回list fruits索引在[0,1]区间内的value</font>
![lrange命令示例_1](img/lrange命令示例_1.png)
**注意**：
- 如果tart/stop参数为负数，代表是倒数的第start/stop的索引像lrange fruits 0 -1代表返回fruits list中的全部value信息。

**获取指定索引下的value**
 <table><tr><td bgcolor="#87CEFA"></br>

```shell
#返回索引在区间[start,stop]的数据
lindex key index
```
</td></tr></table>

**示例**：
<font color=Gray>如果index下没有value则返回(nil)</font>
![lindex命令示例_1](img/lindex命令示例_1.png)

### 4.1.3 获取list中的元素的个数
<table><tr><td bgcolor="#87CEFA"></br>

```shell
llen key
```
</td></tr></table>

**示例**：
![llen命令示例_1](img/llen命令示例_1.png)

### 4.1.4 获取并移除数据
**获取并移除list key中最左边的一个元素**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
lpop key
```
</td></tr></table>

**示例**：
<font color=Gray>初始时fruits中包含values(apple,orange,watermenoon),移除左边的一个元素后变成了(orange,watermenoon)</font>
![lpop命令示例_1](img/lpop命令示例_1.png).

**获取并移除list key中最右边的一个元素**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
rpop key
```
</td></tr></table>

**示例**：
<font color=Gray>初始时fruits中包含values(apple,orange,watermenoon),移除右边的一个元素后变成了(apple,orange)</font>
![rpop命令示例_1](img/rpop命令示例_1.png)

**阻塞获取并删除数据**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取并删除key中最左边的数据，如果没有获取到数据就阻塞直到timeout秒
blpop key timeout

# 从key的右边阻塞获取并删除一个value
brpop key timeout
```
</td></tr></table>

**示例**：
<font color=Gray>在一个key的values为空的list中执行blpop,并设置超时时间为12秒，在timeout时间内，另一个redis客户端2上执行lpush name jjj. 然后客户端1就可以获取到name中的值了</font>
![blpop命令示例_1](img/blpop命令示例_1.png)

### 4.1.5 删除指定数量的数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 将链表key中的count个value移除（从左开始计数）。如果count是负数则表示从右移除count个value值
#
lrem key count value
```
</td></tr></table>

**示例**
<font color=Gray>起始中fruits中有数据(apple,orange,apple,watermenoon,apple), 从右边开始删除2个apple数据后，fruits中的数据变成了(apple,orange,watermenoon)</font>
![lren命令示例_1](img/lren命令示例_1.png)

### 4.1.6 list截取
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 截取key中索引为[start,stop]范围的value并赋值给原key
# start/stop可以是负数，代表从右边数第|start/stop|个
ltrim key start stop
```
</td></tr></table>

**示例**：
<font color=Gray>起始列表fruits中包含数据(apple,orange,watermenoon), 截取区间[1,2]后，fruits中的值变成了(orange,watermeoon)</font>
![ltrim命令示例_1](img/ltrim命令示例_1.png)

### 4.1.7 更新list数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 将key中索引为index的数据设置为value
lset key index value
```
</td></tr></table>

**示例**：
<font color=Gray>起始fruits中的数据为(watermenoon,apple)，将索引为1的数据修改后变成了(watermenoon,orange)</font>
![lset命令示例_1](img/lset命令示例_1.png)

<font color=Gray>如果index超出了列表的范围会执行失败</font>
![lset命令示例_2](img/lset命令示例_2.png)

### 4.1.8 插入list数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 向key中的值为pivot的前/后面插入一个值value(靠近左边的为前，靠近右边的为后)。
linsert key before|after pivot value
```
</td></tr></table>

**示例**：
<font color=Gray>起始fruits中的数据为(apple,watermenoon,apple)，在watermenoon的前面插入wabibabo后变成了(apple,wabibabo,watermenoon,orange)</font>
![linsert命令示例_1](img/linsert命令示例_1.png)

## 4.2 list使用中的注意事项
- list中保存的数据都是string类型，数据总容量是有限的，最多(2^32)-1 = 4294967295
- list具有索引概念，但是操作数据时通常以队列的形式进行入队出队操作，或以栈的形式进行入栈出栈操作
- 获取全部数据操作结束索引设置为-1
- list可以对数据进行分页操作，通常第一页的信息来自于list,第二页以及更多的信息通过数据库的形式加载
## 4.3 list底层存储结构
存储列表信息，一个key中可以存储多个value，通过数据可以体现数据的先后顺序，底层使用双向链表实现。
![list底层存储结构](img/list底层存储结构.png)

-------------------------------------------------
# 5 Set类型
## set操作命令
### 5.1.1 向set中添加数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
sadd key member1 member2 ...
```
</td></tr></table>

**示例**：
<font color=Gray>向集合symbols中添加数据(s,d,a)</font>
![sadd命令示例_1](img/sadd命令示例_1.png)

### 5.1.2 获取set中的全部数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
smembers key
```
</td></tr></table>

**示例**：
![smembers命令示例_1](img/smembers命令示例_1.png)

### 5.1.3 删除set中的数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
srem key member1 member2 ...
```
</td></tr></table>

**示例**：
![srem命令示例_1](img/srem命令示例_1.png)

### 5.1.4 获取集合数据的总量(按个)
<table><tr><td bgcolor="#87CEFA"></br>

```shell
scard key
```
</td></tr></table>

**示例**:
<font color=Gray>获取到scard中的元素个数为4个。</font>
![scard命令示例_1](img/scard命令示例_1.png)

### 5.1.5 判断集合中是否包含指定member
<table><tr><td bgcolor="#87CEFA"></br>

```shell
sismember key member
```
</td></tr></table>

**示例**:
<font color=Gray>如果返回"(integer) 1"说明集合中存在执行的member, 返回"(integer) 0"说明不存在。</font>
![sismember命令示例_1](img/sismember命令示例_1.png)

### 5.1.6 随机获取并移除set中的n个成员
<table><tr><td bgcolor="#87CEFA"></br>

```shell
spop key number
```
</td></tr></table>

**示例**：
<font color="Gray">随机获取并移除set中的两个元素</font>
![spop命令示例_1.](img/spop命令示例_1.png)

### 5.1.7 求两个set的交集
**仅输出set求交集的结果**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 求key1,key2,key3的交集
sinter key1 key2 key3 ...
```
</td></tr></table>

**示例**：
![sinter命令示例_1](img/sinter命令示例_1.png)

**求交集的结果并存入另一个集合**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 求key1,key2...的交集，并将结果保存在dest中
sinterstore dest key1 key2 ...
```
</td></tr></table>

**示例**：
<font color=Gray>设置集合symbols_1(a,b,c)、symbols_2(b,c,d). 这2个集合的交集(b,c)存入dest中</font>
![sinterstore命令示例_1](img/sinterstore命令示例_1.png)

### 5.1.8 求set的并集
**仅输出求并集的结果**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 求key1,key2...的并集
sunion key1 key2 ...
```
</td></tr></table>

**示例**：
<font color=Gray>设置集合symbols_1(a,b,c)、symbols_2(b,c,d)、symbols_3(b,c,x). 这3个集合的并集为(a,b,c,d,x)</font>
![sunion命令示例_1](img/sunion命令示例_1.png)

**求并集，将结果存入dest**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 求key1,key2...的并集
sunionstore dest key1 key2 ...
```
</td></tr></table>

**示例**：
<font color=Gray>设置集合symbols_1(a,b,c)、symbols_2(b,c,d)、symbols_3(b,c,x). 这3个集合的并集(a,b,c,d,x)存入dest. 如果dest不存在就创建；如果dest中有数据则覆盖；如果dest是其他类型则删除原先的值并改为set类型，在将结果添加进去</font>
![sunionstore命令示例_1](img/sunionstore命令示例_1.png)

### 5.1.9 求集合set的差集
**仅将set求差集的结果输出**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 求key1,key2,key3 ...的差集,key1-key2-key3 
sdiff key1 key2 key3 ...
```
</td></tr></table>

**示例**：
![sdiff命令示例_1](img/sdiff命令示例_1.png)

**将set求差集的结果存入dest**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 求key1,key2,key3 ...的差集(key1-key2-key3) 并存入dest
sdiffstore dest key1 key2 key3 ...
```
</td></tr></table>

**示例**：
![sdiff命令sdiffstore命令示例_1](img/sdiffstore命令示例_1.png)

------------------------------------------
### 5.1.10 移动set元素到另一个set
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 将source中的member元素移动到dest中
smove source dest member
```
</td></tr></table>

**示例**：
<font color=Gray>初始时set symbols_1(a,b,c), symbols_2(b,c,d). 将symbols_1中的元素a移动到symbols_2中后:  symbols_1(b,c), symbols_2(a,b,c,d).</font>
![smove命令示例_1](img/smove命令示例_1.png)

## set类型操作注意事项
- set类型不允许数据重复，如果添加的数据在set中已经存在，则只保留一份。
- set虽然于hash的存储结构相同，但无法启用hash中存储值的空间。

-----------------------------------------------
# 6 sorted_set类型
sorted_set类型是在set类型的基础上为每个member添加了score字段，用于对member进行排序。
## 6.1 sorted_setl类型操作命令
### 6.1.1 添加数据
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 向key中添加成员member1, member1的score为score1
zadd key score1 member1 score2 member2...
```
</td></tr></table>

**示例**：
<font color=Gray>向sorted_set exam中添加math,chinese成员，它们的score分别为123,100</font>
![zadd命令示例_1](img/zadd命令示例_1.png)

### 6.1.2 查看数据
**根据索引来查看数据，以score的升序来进行排序，即索引为0的score是最小的**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 查看key中索引为[start,stop]的成员，以score升序排列.
# 如果添加withscores参数，还会输出对应成员的score
zrange key start stop [withscores]
```
</td></tr></table>

**示例**：
<font color=Gray>获取exam中的全部成员，-1代表索引最后一位。</font>
![zrange命令示例_1](img/zrange命令示例_1.png)

<font color=Gray>获取exam中的全部成员，同时输出对应的score信息。成员chinese的score为100，成员math的score为123。</font>
![zrange命令示例_2](img/zrange命令示例_2.png)

**根据索引来查看数据，以score的降序来进行排序，即索引为0的score是最大的**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 查看key中索引为[start,stop]的成员,按score降序.
# 如果添加withscores参数，还会输出对应成员的score
zrevrange key start stop [withscores]
```
</td></tr></table>

**示例**：
<font color=Gray>获取exam中的全部成员，-1代表索引最后一位。</font>
![zrevrange命令示例_1](img/zrevrange命令示例_1.png)

<font color=Gray>获取exam中的全部成员，同时输出对应的score信息。成员chinese的score为100，成员math的score为123。</font>
![zrevrange命令示例_2](img/zrevrange命令示例_2.png)

**按score条件获取数据，结果为升序**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取score在[min,max]区间的数据
# withscores参数表示同时获取member的score
# limit offset count表示从第offset个开始获取count个
zrangebyscore key min max [withscores] [limit offset count]
```
</td></tr></table>

**示例**：
<font color=Gray>获取exam中score在范围[120,150]的数据，取其中的2个，从偏移量为1处开始获取。
因为exam中满足score在[120,150]的数据有3个，按**升序**排列为(chinese(120),math(130),biology(140)), 偏移为1的是math, 最多取两个member，因此输出结果为(math(130),biology(140)).</font>
![zrangebyscore命令示例_1](img/zrangebyscore命令示例_1.png)

**按score条件获取数据，结果为降序**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取score在[max,min]区间的数据
# withscores参数表示同时获取member的score
# limit offset count表示从第offset个开始获取count个
zrevrangebyscore key max min [withscores] [limit offset count]
```
</td></tr></table>

**示例**：
<font color=Gray>获取exam中score在范围[130,100]的数据，取其中的1个，从偏移量为0处开始获取。
因为exam中满足score在[130,100]的数据有3个，按**降序**排列为(math(130),chinese(120),english(110)), 偏移为0的是math, 最多取1个member，因此输出结果为(math(130))).</font>
![zrevrangebyscore命令示例_1](img/zrevrangebyscore命令示例_1.png)


### 6.1.3 删除sorted_set成员
**根据sorted_set中的元素删除**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 查看key中索引为[start,stop]的成员,按score降序.
zrem key member1 member2 ...
```
</td></tr></table>

**示例**：
<font color=GRAY>删除exam中的math,chinese,english成员，因为exam中没有english成员，因此忽略english。 并且输出的(integer)2表示成功删除2个成员。</font>
![zrem命令示例_1](img/zrem命令示例_1.png)

**根据索引范围删除sorted_set中的元素**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 删除按score升序排列的key中索引在[start,stop]区间的member
zremrangebyrank key start stop
```
</td></tr></table>

**示例**：
<font color=GRAY>起始exam按score的升序排列元素为(english,chinese,math,biology), 因为删除了索引在[1,2]之间的(chinese,math), 因此剩余(english,biology).</font>
![zremrangebyrank命令示例_1](img/zremrangebyrank命令示例_1.png)

**根据score范围删除sorted_set中的元素**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 删除按score升序排列的key中score在[min,max]区间的member
zremrangebyscore key min max
```
</td></tr></table>

**示例**：
<font color=GRAY>起始exam按score的升序排列元素为(english(110),chinese(120),math(130),biology(140)), 因为删除了score在[125,140]之间的(math(130),biology(140)), 因此剩余(english(110),chinese(120)).</font>
![zremrangebyscore命令示例_1](img/zremrangebyscore命令示例_1.png)

### 6.1.4 获取sorted_set中的元素个数
**获取sorted_set中全部元素的个数**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
zcard key
```
</td></tr></table>


**获取sorted_set中指定score区间的元素的个数**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取key中score在[min,max]区间的元素个数
zcount key min max
```
</td></tr></table>

**示例**：
![zcount命令示例_1](img/zcount命令示例_1.png)

### 6.1.5 sorted_set求交集
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 将key1,key2...求交集，其中相同的元素的score相加，结果存入dest中。numkeys是后面接的key的个数
zinterstore dest numkeys key1 key2 ...
```
</td></tr></table>

**示例**：
<font color=Gray>求test与exam的交集，并将score相加</font>
![zinterstore命令示例_1](img/zinterstore命令示例_1.png)

<font color=Gray>如果在zinterstore命令中添加**aggregate max**可以在进行合并时，score取最大值</font>
![zinterstore命令示例_2](img/zinterstore命令示例_2.png)

<font color=Gray>如果在zinterstore命令中添加**aggregate min**可以在进行合并时，score取最大值</font>
![zinterstore命令示例_3](img/zinterstore命令示例_3.png)

### 6.1.6 获取数据对应的索引
**以score的升序排列，获取指定成员的索引**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取member对应的所以，(获取排名)。如果不存在成员则返回(nil)
zrank key member
```
</tr></td></table>

**示例**：
<font color=Gray>获取到math的索引为1</font>
![zrank命令示例_1](img/zrank命令示例_1.png)

**以score的升序排列，获取指定成员的索引**
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取member对应的所以，(获取排名)。如果不存在成员则返回(nil)
zrevrank key member
```
</tr></td></table>

**示例**：
<font color=Gray>以降序排列，获取到math的索引为0</font>
![zrevrank命令示例_1](img/zrevrank命令示例_1.png)

### 6.1.7 sorted_set成员score值的获取
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 获取member的score值，如果member不存在则返回(nil)
zscore key member
```
</td></tr></table>

**示例**:
![zscore命令示例_1](img/zscore命令示例_1.png)
![zscore命令示例_2](img/zscore命令示例_2.png)

### 6.1.8 sorted_set的成员的score值修改
<table><tr><td bgcolor="#87CEFA"></br>

```shell
# 将key的member成员的score增加incremement, incremement可以为负数--表示减少
zincrby key incremement member
```
</td></tr></table>

**示例**：
<font color=Gray>将exam的math的score增加12</font>
![zincrby命令示例_1](img/zincrby命令示例_1.png)

## 6.2 sorted_set使用的注意事项
- scor保存的数据空间是64位，如果是整数，则对应范围是-9007199254740992~9007199254740992
- score保存的数据也可以是一个双精度的double值，基于双精度浮点数的特征，可能会丢失精度，使用时需要谨慎
  ![double_score_1](img/double_score_1.png)
- sorted_set底层存储还是基于set结构的，因此数据不能重复，如果添加相同数据，score值将会反复被覆盖，保留最后一次修改的结果。

# 7 单数据操作和多数据操作
我们在对数据进行操作的时候，会遇到单数据操作和多数据操作。像对string类型的set和mset。它们的区别就是set命令只能设置一对string类型的key-value，而mset可以设置多对key-value的组合。
```shell
set key value
mset key1 value1 key2 value2 ...
```
对于像这样的单数据操作和多数据操作之间如何做选择，可以从效率的角度来思考。
首先我们来看一下一条指令是如何从redis客户端传输到redis服务端执行的。
![redis指令执行过程_2](img/redis指令执行过程_2.png)
1. Redis客户端发送指令到Redis服务器。
2. Reids服务执行命令。
3. Redis服务器将执行结果发送回Redi客户端。</br>

这3个步骤都会消耗时间，如果是3条指令以单指令的方式执行，那么指令在发送到Redis服务器和返回的步骤会执行3x2=6次，执行次数3次。
如果这3条指令以多指令发送，那么3条指令的往返次数就是2次. 执行次数3次。
这样看来似乎是多指令效率更高，但虽然多指令下数据传输的次数变少了，但数据量也变大了，单次传输的时间会更长。因此使用单指令还是多指令需要权衡指令量与传输时长的关系。一般要set的数据多的话用多指令更好，数据量较少使用单指令。
