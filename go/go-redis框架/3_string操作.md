[toc]




# 1 设置string
```go
func (c cmdable) Set(ctx context.Context, key string, value interface{}, expiration time.Duration) *StatusCmd
```
**参数：**
<font color=blue>ctx</font> :
<font color=blue>key</font> : 需要设置的key
<font color=blue>value</font> : key的值，可以是字符串或者数字
<font color=blue>expiration</font>:  设置过期时间，单位us;  0表示永久
**返回值：**
<font color=blue>StatusCmd</font>：redis命令的执行状态，StatusCmd.Val()用于获取返回结果字符串

**示例**：
```go
defer redisClient.Close()
ctx := context.Background()
var status *redis.StatusCmd
status = redisClient.Set(ctx, "name", 99, 10*time.Second)
//
str, err := status.Result()
if err != nil {
    fmt.Println("cmd set failed:", err.Error())
} else {
    /*status.Result()返回的第一个参数就是status.Val()*/
    fmt.Println("str=", str) // OK
    fmt.Println("value=", status.Val()) // OK
}
```

# 2 redis.baseCmd的方法
```go
// 返回执行命令的名字，返回的值包括`set`
func (cmd *baseCmd) Name() string

/*返回执行的redis命令*/
func (cmd *baseCmd) Args() []interface{}


```

# 3 redis.StatusCmd的方法
```go
/* 返回redis命令的执行结果 
string: OK:执行成功
error:  错误信息*/
func (cmd *StatusCmd) Result() (string, error)

func (cmd *StatusCmd) Val() string
```