[toc]
# 1 创建Pawn
根创建C++类流程一样，只是把所继承的类改为继承Pawn.
创建好的代码为：
头文件：
```c++ 
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class STATING_API AMyPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AMyPawn();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
```

# 2 给创建的Pawn添加根组件
在构造函数中通过`CreateDefaultSubject`给`RootComponent`赋值

```c++
// 头文件
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class STATING_API AMyPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AMyPawn();
	
    UPROPERTY(VisibleAnywhere, Category="My Pawn Property")
	class UStaticMeshComponent* VisibleMesh;
	
    UPROPERTY(VisibleAnywhere, Category="My Pawn Propwerty")
	class UCameraComponent* MyCamera;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
};
```
-------------------------
```c++
// cpp 构造函数
#include "Components/StaticMeshComponent.h"
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 创建默认的RootComponent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // 创建默认的静态网格
	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));

    // 将静态网格附加到RootComponent上
	VisibleMesh->SetupAttachment(GetRootComponent());
}
```
代码编辑完成后，在Unreal编辑器中编译，编译完成后，再创建基于C++类的蓝图。创建蓝图完成后像这样：
![](img/blueprint5.png)
正如我们再代码中编写的那样，创建了RootComponent根组件，然后将VisibleMesh附加到根组件上。

# 3 添加UCameraComponent组件
```c++
// cpp 构造函数
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
AMyPawn::AMyPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // 创建默认的RootComponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // 创建默认的静态网格
    VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));

    // 将静态网格附加到RootComponent上
    VisibleMesh->SetupAttachment(GetRootComponent());

    MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
    MyCamera->SetupAttachment(RootComponent);

    // 设置CameraComponent组件相对于父组件的位置
    MyCamera->SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f));
    
    // 设置CameraComponent组件相对于父组件的旋转角度
    MyCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); 
}
```
代码编写完后再Unreal编辑器中编译，然后打开蓝图给VisibleMesh添加`Static Mesh` 和材质`Materials`
![](img/blueprint6.png)