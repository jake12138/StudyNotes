# 获取Node节点
```c++
// 获取根节点
using namespace kanzi;
kanzi::Node2DSharedPtr root = getRoot(); 
// 获取Node2D
kanzi::Node2DSharedPtr node = root->lookup<kanzi::Node2D>("#nodeName")
// 获取EmptyNode2D
kanzi::EmptyNode2DPtr node = root->lookup<kanzi::EmptyNode2D>("#nodeName")

/*如果想要获取EmptyNode2D、EmptyNode3D、Node3D，将模板参数
和返回值改为对应的值即可。等号的左边也可以改为其父类的指针*/
```

# 获取Node的属性值
想要获取其他的类型的属性值就将模板参数改成对应的类型
```c++
std::string name = mCarModle->getProperty(kanzi::DynamicPropertyType<std::string>("name"));
printf("get car modle name propert=%s\n", name.c_str());
```