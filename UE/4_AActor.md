来源：https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPProgrammingQuickStart/
# 1 创建Actor的C++类
- 在虚幻编辑器中，单击**文件**下拉菜单，然后选择新建**C++**类...命令。
- 将显示“**选择父类**”菜单。您可以选择要扩展的现有类，将其功能添加到您自己的类中。选择**Actor**，因为它是可以放置在世界中的最基本的对象类型，然后单击**下一步**。
- 在“命名您的新Actor”菜单中，将“Actor”命名为自己想要创建的C++类名，然后单击“创建类”。
- 创建好后就可以在创建C++类时指定的路径下，创建好的C++类继承自AActor类。
创建好的类头文件为：
```c++
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h" // 必须写在其他include之后

UCLASS() // 表明该类要参与反射与垃圾回收系统，需要包含$(类名).generated.h头文件
class STATING_API AFloatingActor : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AFloatingActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;s
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
```

# 2 AActor类的类型和变量
## 2.1 UStaticMeshComponent类型
UStaticMeshComponent将充当我们对象的可视化表示。可以通过函数
```c++
CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
```
来创建其指针

# 3 AActor类中方法作用
## 3.1 BeginPlay
```
void BeginPlay();
```
在游戏开始的时候执行，可用于初始化
## 3.2 Tick
```c++
void Tick(float DeltaTime);
```
在游戏每一帧时调用一次


# 5 代码示例
C++类的头文件
```c++
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS(Blueprintable) // Blueprintable表明可以在蓝图中访问，可以使用反射
class STATING_API AFloatingActor : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AFloatingActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(BlueprintReadWrite, Category="MY")  // BlueprintReadWrite指明可以在蓝图中读写
	float MyFloat;

	UFUNCTION(BlueprintCallable)  // BlueprintCallable表明可以在蓝图中调用
	void MyFunction();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
```

C++源文件
```c++
#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if(USceneComponent* ExistingRootComponent = GetRootComponent()){
		VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		VisualMesh->SetupAttachment(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Content/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

		if(CubeVisualAsset.Succeeded()){
			VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
			VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			UE_LOG(LogTemp, Log, TEXT("find a cube"));
		}else{
			UE_LOG(LogTemp, Error, TEXT("not find a cube"));
		}
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 实现立方体的上下移动并旋转
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) + FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;
	float DeltaRotation = DeltaTime * 20.0f;
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void AFloatingActor::MyFunction(){
	UE_LOG(LogTemp, Log, TEXT("hello world!"));
	UE_LOG(LogTemp, Warning, TEXT("hello world!"));
	UE_LOG(LogTemp, Error, TEXT("hello world!"));
}
```