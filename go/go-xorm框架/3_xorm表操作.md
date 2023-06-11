[toc]

# 1 创建表
xorm中通过结构体按照一定的规则转化为mysql中的表信息。
struct与数据库表的转化规则：
示例：
```go
package main

import (
    "fmt"
    _ "github.com/go-sql-driver/mysql"
    "xorm.io/xorm"
)
// 数据库连接对象
var engine *xorm.Engine = nil
var err error = nil
func init() {...连接数据库...}

type Book struct {
    ID     uint64
    Name   string
    Author string
    Type   int8
    Price  float32
}

func main() {
    // main函数结束后关闭数据库连接
    defer engine.Close()
    /*根据Book结构体信息创建数据库表*/
    err = engine.Sync2(Book{})
    if err != nil {
        fmt.Println("create Table Book failed:", err.Error())
        return
    }

    /*也可以使用CreateTables方法创建表*/
    // err = engine.CreateTables(&Book{})

    /*也可以使用Sync方法创建表*/
    // err = engine.Sync(Book{})
}
```
生成的数据库为：
```shell
mysql> desc book;
+--------+---------------------+------+-----+---------+-------+
| Field  | Type                | Null | Key | Default | Extra |
+--------+---------------------+------+-----+---------+-------+
| i_d    | bigint(20) unsigned | YES  |     | NULL    |       |
| name   | varchar(255)        | YES  |     | NULL    |       |
| author | varchar(255)        | YES  |     | NULL    |       |
| type   | int(11)             | YES  |     | NULL    |       |
| price  | float               | YES  |     | NULL    |       |
+--------+---------------------+------+-----+---------+-------+
5 rows in set (0.00 sec)
```

**Sync和Sync2的区别**：
在xorm中，Sync和Sync2都是用于创建表的方法，它们之间的区别如下：

1. 参数类型不同
Sync方法的参数是结构体类型，而Sync2方法的参数是表名字符串和结构体类型。

2. Sync2方法支持更多的选项
Sync方法仅支持结构体中字段定义的选项，例如not null、unique等。而Sync2方法除了支持结构体中的字段选项，还支持其它一些选项，例如表选项、存储引擎选项等。

3. 兼容性问题
Sync方法是早期版本的API，经过多个版本的迭代之后，Sync2方法逐渐成为了主流API。虽然Sync方法仍然能正常工作，但在一些极端情况下，可能会发生不兼容的问题。

因此，如果在开发中需要使用xorm创建表，建议使用Sync2方法，以获得更好的兼容性和功能。

在使用 `Sync` 和 `Sync2` 方法创建表时，需要注意以下几点：

- 表名称是根据 Go 结构体中的 `TableName` 标签中定义的名称来创建的，如果没有定义 `TableName`，则会使用结构体名称来作为表名称。
- 列名称是根据 Go 结构体中的字段名称来创建的。
- 默认情况下，Go 中的 `int32`、`int64`、`uint32`、`uint64` 类型都会被映射为 MySQL 中的 `BIGINT` 类型。
- 默认情况下，Go 中的 `string` 类型会被映射为 MySQL 中的 `VARCHAR(255)` 类型。
- 如果需要映射到 MySQL 中的其他数据类型，则需要通过在字段上添加 `xorm` 标签来指定数据类型。

总之，`Sync` 和 `Sync2` 方法都是 xorm 中用来创建表的方法，但是它们的参数不同。在使用这些方法时，需要注意表名称和列名称的定义以及字段类型的映射，以确保表结构与预期一致。

## 1.1 结构体与数据库表的映射规则
结构体转化为表时，结构体名字和字段名都会按照一定的规则映射到数据库表的表名和字段名。
结构体的名称默认是驼峰命名(struct)-->小写+下划线
例如，
|结构体名称|表名|
|---------|----|
|Book|book|
|MyBook|my_book|
同时也可以通过设置自定义的表名

### 1.1.1 通过TableName方法设置表名
通过给结构体定义```func TableName() string```方法来设置表名，这个函数返回的字符换就是表的名字
  ```go
    /*给Book结构体添加TableName方法，该方法返回的字符串就用作表名*/
    func (book *Book) TableName() string {
        return "MyBook"
    }
  ```
### 1.1.2 通过engine.Table方法进行命名
通过xorm.Engine.Table(...)进行指定命名的优先级是最高的
示例：
```go
func main() {
	defer engine.Close()
    /*将表名命名为YYY*/
    err = engine.Table("YYY").Sync2(Book{})
	if err != nil {
		fmt.Println("create Table Book failed:", err.Error())
		return
	}
}
```

### 1.1.3 使用xorm提供的映射
- 使用xorm提供的映射
xorm提供了3种映射配置，**<font color=green>names.SnakeMapper ， names.SameMapper ， names.GonicMapper</font>**

**这三种映射不仅会作用到表名中，也会作用到字段名上。**

|映射|描述|
|----|----|
|names.SnakeMapper| 支持struct为驼峰式命名，表结构为下划线命名之间的转换这个是默认的Maper; </br>例如(表名-->字段名):ID --> i_d,  Name --> name,  CreateTime --> create_time|
|names.SameMapper|支持结构体名称和对应的表名称 以及 结构体field名称与对应的表字段名称相同的命名；</br>例如(表名-->字段名):ID --> ID, CreateTime --> CreateTime|
|names.GonicMapper|和SnakeMapper很类似，但是对于特定词支持更好，比如ID会翻译成id而不是i_d|
**示例**:
```go
package main

import (
    "fmt"
    _ "github.com/go-sql-driver/mysql"
    "xorm.io/xorm"
    "xorm.io/xorm/names"
)

var engine *xorm.Engine = nil
var err error = nil

func init() {
    engine, err = xorm.NewEngine("mysql", "test:zxcvbnm1997@(127.0.0.1:3306)"+
    "/test_database?charset=utf8&parseTime=True")
    if err != nil {
        fmt.Println("create database engine failed:", err.Error())
        return
    }
    if err = engine.Ping(); err != nil {
        fmt.Println("connect mysql failed:", err.Error())
        return
    }
    /*设置使用 SmameMapper映射*/
    engine.SetMapper(names.SameMapper{})
    fmt.Println("connected mysql database")
}
func main(){
    defer engine.Close()
}
```

### 1.1.4 前缀映射
通过
```go
names.NewPrefixMapper(names.SnakeMapper{}, "prefix")
```
可以创建一个在SnakeMapper的基础上命名中添加统一的前缀，当然也可以把SnakeMapper更换成SameMapper、GonicMapper或者你自定义的Mapper
**示例**:
```go
func init() {
    engine, err = xorm.NewEngine("mysql", "test:zxcvbnm1997@(127.0.0.1:3306)/test_database"+
        "?charset=utf8&parseTime=True")
    if err != nil {
        fmt.Println("create database engine failed:", err.Error())
        return
    }
    if err = engine.Ping(); err != nil {
        fmt.Println("connect mysql failed:", err.Error())
        return
    }
    /*在SameMapper的基础上添加一个前缀 `My_`*/
    prefixMapper := names.NewPrefixMapper(names.SameMapper{}, "My_")
    engine.SetMapper(prefixMapper)

    fmt.Println("connected mysql database")
}
```
### 1.1.5 后缀映射
```go
//在创建的数据库表名及其字段名上添加后缀_Same
mapper := names.NewSuffixMapper(names.SameMapper{}, "_Same")
engine.SetMapper(mapper)
```
### 1.1.6 缓存映射
通过names.NewCacheMapper(names.SnakeMapper{})可以创建一个组合了其他映射规则，起到在内存中缓存曾经映射过的命名映射。
### 1.1.7 通过标签来进行命名映射
如果所有的命名都是按照Mapper的映射来操作的，那当然是最理想的，但是如果碰到某个表名或者某个字段跟映射规则不匹配时，我们就需要使用标签来改变。
通过struct中对应的Tag中使用
`xorm:"'column_name'"`可以使得该field对应的Column名称指定名称
**示例**：
```go
type Book struct {
    ID     uint64
    /*生成表后，Name字段在表中的名字就是"FullName"*/
    Name   string `xorm:"FullName""`
    Author string
    Type   int8
    Price  float32
}
```
### 1.1.8 各个映射的优先级
当各个映射都存在时，它们的优先级为
**对于表名：**
1.  engine.Table()指定的临时表名优先级最高
2.  TableName() string其次
3. Mapper自动映射的表名优先级最后

**对于字段名字段名**
1. 结构体Tag指定字段名优先级最高
2. Mapper自动映射的字段名优先级较低

## 1.2 字段标签
可用在声明结构体的时候，在每个字段的后面添加标签来对该字段进行描述，使得该结构体映射为数据库表时，对应字段也会添加标签所描述的属性。
标签各个属性描述用空格分开
### 1.2.1 设置字段名
如与其它关键字冲突，请使用单引号括起来。
```go
type Book struct {
    /*该字段映射为数据库表的字段名为id*/
    ID     uint64 `xorm:"id"`
    /*使用单引号将字段名包裹(单引号在内围，否则不生效)*/
    Name   string `xorm:"'FullName'"`
}
```
### 1.2.2 声明为主键
通过声明 `xorm:"pk"`标签来将该字段描述为主键。
**注意**： 对于int类型的Column使用pk标签后还需要是使用autoincr标签来进行声明为自增，不然在插入记录的时候，如果主键的值跟表中已有数据的值重复，则会插入失败。不指定struct种主键的值会使用默认值，头一次插入会成功，但第二次就会出现主键重复。
```go
type Book struct {
    /*声明为主键，字段名映射为id*/
    ID     uint64 `xorm:"id pk autoincr"`
    
    Name   string `xorm:"FullName""`
}
```
### 1.2.3 声明类型
```go
type Book struct {
    ID    uint64  `xorm:"id pk autoincr"`
    Name  string  `xorm:"char(64)"`
    Is    bool    `xorm:"bool"`
    Desc  string  `xorm:"varchar(255)"`
    Price float32 `xorm:"float(6,2)"`
}
```
对应的数据库表
```shell
mysql> desc book;
+-------+---------------------+------+-----+---------+----------------+
| Field | Type                | Null | Key | Default | Extra          |
+-------+---------------------+------+-----+---------+----------------+
| id    | bigint(20) unsigned | NO   | PRI | NULL    | auto_increment |
| name  | char(64)            | YES  |     | NULL    |                |
| is    | tinyint(1)          | YES  |     | NULL    |                |
| desc  | varchar(255)        | YES  |     | NULL    |                |
| price | float(6,2)          | YES  |     | NULL    |                |
+-------+---------------------+------+-----+---------+----------------+
5 rows in set (0.00 sec)
```
xorm类型与数据库类型对应关系如下：
|xorm|go类型|MySQL|取值范围|示例|备注|
|------|----|-----|----|---|-----|
|bit|任意|bit|-|```Value bool `xorm:"bit(1)"` ```|bit的长度最大64;</br>传入的值长度不能</br>超过声明的bit的长度,否则会插入失败|
|tinyint|bool/整形|tinyint|1个字节,范围-128~127|```Value int8 `xorm:"tinyint"` ```||
|smallint|bool/整形|smallint|2个字节,范围(-32768~32767)|```Value int16 `xorm:"smallint(1)"` ```||
|mediumint|bool/整形|mediumint|3个字节 范围(-8388608~8388607)|```Value int32 `xorm:"mediumint"` ```||
|int|bool/整形|int|4个字节 范围(-2147483648~2147483647)|```Value bool `xorm:"int"` ```||
|integer|bool/整形|integer|4个字节 范围(-2147483648~2147483647)|```Value int32  `xorm:"integer"` ```|1.int是作为对象，直接存储数值。</br>2.integer需要实例化对象，实际上是生成一个指针指向对象的地址。</br>3.在mysql中，integer的数据类型是引用数据类型，是对int的封装。|
|bigint|bool/整形/string|bigint|8个字节 范围(+-9.22*10的18次方)|```Value string `xorm:"bigint"` ```|如果go类型是string,那么值一定要是数字|
|float(m,d)|float32/float64|float(m,d)|单精度浮点型 8位精度(4字节) m总个数，d小数位|```Value float32 `xorm:"float(5,3)"`|1. 对于小数位超过的数字，会四舍五入。</br>对于(5,3)，表名数字的总位数是5，小数站3位，因此整数最多部分只能有2位，对于整数部分超过2位的(如100.21)会插入失败。</br>2.存储的精度有误差，甚至在赋值的浮点型很大时，存储却为0|
|double(m,d)|float32/float64|double(m,d)|双精度浮点型 16位精度(8字节) m总个数，d小数位|```Value float64 `xorm:"double(28,6)"` ```||
|decimal(m,d)|float32/float64/string|decimal(m,d)|参数m<65 是总个数，d<30且 d<m 是小数位。|```Value string `xorm:"decimal(45,6)"` ```| go的类型最好使用string类型，且值为数字，这样更精确|
|char|string|char|固定长度,最多255个字符|```Name string `xorm:"char(64)"` ```||
|varchar|string|varchar|固定长度,最多65535个字符|```Name string `xorm:"varchar(64)"` ```||
|tinytext|string|tinytext|可变长度，最多255个字符|```Value string `xorm:"tinytext"` ```||
|text|string|text|可变长度，最多65535个字符|```Value string `xorm:"text"` ```||
|mediumtext|string|mediumtext|可变长度，最多2的24次方-1个字符|```Value string `xorm:"mediumtext"` ```||
|longtext|string|longtext|可变长度，最多2的32次方-1个字符|```Value string `xorm:"longtext"` ```||

**关于mysql中的浮点型**：
mysql的float类型是单精度浮点类型不小心就会导致数据误差. 单精度浮点数用4字节（32bit）表示浮点数 采用IEEE754标准的计算机浮点数，在内部是用二进制表示的 如：7.22用32位二进制是表示不下的。 所以就不精确了。 mysql中float数据类型的问题总结 对于单精度浮点数Float: 当数据范围在±131072（65536×2）以内的时候，float数据精度是正确的，但是超出这个范围的数据就不稳定，没有发现有相关的参数设置建议：将float改成double或者decimal，两者的差别是double是浮点计算，decimal是定点计算，会得到更精确的数据

### 1.2.4 添加索引

**添加单索引**:
```go
type Book struct {
    ID     int32  `xorm:"pk autoincr"`
    Name   string `xorm:"char(12)"`
    Author string `xorm:"char(12) index"`
}
```
**添加联合索引**：
```go
type Book struct {
    ID     int32  `xorm:"pk autoincr"`

    /*添加联合索引，索引名为IDX_Book_my_index*/
    Name   string `xorm:"varchar(12) index(my_index)"`
    Author string `xorm:"char(12) index(my_index)"`
}
```

**创建唯一索引**:
```go
type Book struct {
	ID     int32  `xorm:"pk autoincr"`
	Name   string `xorm:"char(12) unique"`
	Author string `xorm:"char(12)"`
}
```

**创建联合唯一索引**：
```go
type Book struct {
    ID     int32  `xorm:"pk autoincr"`
    Name   string `xorm:"char(12) unique(my_unique)"`
    Author string `xorm:"char(12) unique(my_unique)"`
}
```
定义好以上结构体后，通过 ```Engine.Sync2(xxx)```创建表的时候，会自动创建索引

**CreateIndexes方法创建索引**：
也可以通过Engine.CreateIndexes(xxx)方法创建索引
```go
type Book struct {
    ID     int32  `xorm:"pk autoincr"`
    Name   string `xorm:"char(12) unique(my_unique)"`
    Author string `xorm:"char(12) unique(my_unique)"`
}

func main() {
    engine.ShowSQL(true)

    /*根据Book中的标签信息创建索引*/
    if engine.CreateIndexes(&Book{}) != nil {
        fmt.Println("create index failed:", err.Error())
    }
}
```

### 1.2.5 外键声明
在 xorm 中，可以使用 struct tag `xorm:"foreign"` 来给字段声明外键。

假设你的表 A 中需要对表 B 的字段 b_id 创建外键约束，那么在声明表 A 的结构体时，可以在字段 b_id 上添加 `foreign` tag，指定关联的表名和关联的字段名，例如：

```go
type A struct {
    Id    int64  `xorm:"pk autoincr"`
    BId   int64  `xorm:"notnull foreign(b.id)"` // 表示 A.BId 关联到 B.id
    Name  string `xorm:"varchar(50)"`
}

type B struct {
    Id    int64  `xorm:"pk autoincr"`
    Name  string `xorm:"varchar(50)"`
}
```

在这个示例中，`BId` 字段的类型为 `int64`，并且添加了 `foreign` tag，表示需要为该字段创建外键约束。`(b.id)` 表示该外键约束关联到表 B 的字段 id 上。这里的 `b` 表示要关联的表名，可以是一个已经声明的结构体的名称，或者是字符串类型的表名。

通过这种方式，你可以方便地在 xorm 中声明外键约束，简化了 SQL 语句的编写和维护。 **需要注意的是，xorm 只提供了外键的声明功能，实际的外键约束需要在数据库中使用 SQL 语句创建。** 因此，在使用 xorm 的同时，仍然需要对 SQL 语句的创建和执行有一定的了解。