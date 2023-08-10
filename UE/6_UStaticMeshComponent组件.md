[toc]
# 1 介绍
UStaticMeshComponent是一个静态网格组件

# 2 创建UStaticMeshComponent对象
创建UStaticMeshComponent使用CreateDefaultSubject<UStaticMeshComponent>模板函数。
```c++
template<class TReturnType>
TReturnType* CreateDefaultSubject(FName SubjectName, bool bTransient = false);
```
**作用**: 创建一个默认的组件。如果在创建的C++类中调用了这个函数。那么在基于该C++类创建蓝图的时候，添加的组件就是这个函数返回值对应的组件，组件名称为返回值所对应的变量名。
**参数**：
- SubjectName: 该组件在系统中的一个标识，不可重复
- bTransient: 

**示例**:
```c++
AFloatingActor::AFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent* VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
}
```

# 3 将UStaticMeshComponent添加到父组件中
```c++
void USceneComponent::SetupAttachment(class USceneComponent* InParent, FName InSocketName = NAME_None);
```
**作用**: 将自身作为子组件，添加到InParent父组件上
**参数**:
- InParent： 父组件
- InSocketName： 

**示例**:
```c++
AFloatingActor::AFloatingActor()
{
    StaticMeshComponent* VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
    
    /*RootComponent是AActor的成员变量*/
    VisualMesh->SetupAttachment(RootComponent);
}
```


