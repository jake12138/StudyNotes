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

# 4 替换初学者内容包中的Pawn
将我们自己创建的Pawn替换初学者内容包中的Pawn来作为玩家。
1. 在`内容浏览器`中的`C++类`区域选择继承自`Game Mode Base`的类，如果没有就自己创建一个c++类，选择继承`Game Mode Base`类。
2. 基于创建的游戏模式类，创建蓝图。
3. 双击创建的蓝图，进入蓝图编辑界面。在`Details`区域中`Classes`的`Default Pawn Class`选项选择前面基于Pawn创建的BP_MyPawn蓝图类。然后编译保存
![](img/blueprint7.png)
4. 打开`World Setting`。在`World Outliner`中选中根节点，右击。即可找到`World Setting`选项
![](img/blueprint8.png)
5. 在`Game Mode`下的`GameMode Override`中选择我们前面创建的基于`Game Mode Class`的蓝图类BP_MyGameModeBase
![](img/gamemode_1.png)
6. 这时候点击`Play`就会发现我们自己创建的Pawn就替换变成了游戏角色，但是还不能移动和旋转视角。
下面将添加视角和移动
7. 在我们创建的BP_MyPawn蓝图类中，在`Details`区域中设置`Auto Prossess Player`为`Player 0`。 这里的Player 0的含义表示在网络游戏中，我们自己操控的本地角色或则单机游戏中我们操控的角色。
![](img/mypawn_1.png)

8. 在我们创建的c++类`MyPawn`的构造函数中添加代码
`AutoPossessPlayer = EAutoReceiveInput::Player0;`
