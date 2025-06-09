## C++ 语法要点笔记整理

---

### 一、隐式类型转换与 explicit

#### ✅ 拷贝初始化

```cpp
B b = 42;
```

* 是 **拷贝初始化（copy initialization）**。
* 编译器会尝试：先将 `42` 隐式转换为 `B` 类型的临时对象，再调用拷贝构造函数。
* 相当于：

```cpp
B temp(42);
B b = temp;
```

#### ✅ explicit 的作用

```cpp
explicit B(int);
```

* 禁止上述隐式转换，必须显式构造：

```cpp
B b(42);     // OK
B b{42};    // OK (C++11 列表初始化)
B b = 42;   // ❌ 错误
```

#### 示例对比

```cpp
struct Implicit {
    Implicit(int) {}
};
struct Explicit {
    explicit Explicit(int) {}
};
Implicit i = 42;   // OK
Explicit e = 42;   // ❌ 错误
Explicit e2(42);   // OK
```

---

### 二、#include "" 与 #include <>

#### `#include <...>`

* 用于 **标准库头文件**（如 `<iostream>`、`<vector>`）。
* 编译器在标准系统路径（如 `/usr/include`）中查找。

#### `#include "..."`

* 用于 **用户自定义头文件**。
* 编译器先在当前目录查找，再退而搜索系统路径。

#### 示例

```cpp
#include <iostream>       // 系统头文件
#include "myclass.h"     // 用户自定义头文件
```

---

### 三、auto / const auto / const auto& 区别（以访问器返回值为例）

假设函数如下：

```cpp
ConstArrayAccessor1<Vector3D> ParticleSystemData3::forces() const {
    return vectorDataAt(_forceIdx);
}
```

#### ✅ const auto f = forces();

* 拷贝访问器副本，不可修改其成员。
* **推荐使用**，简洁安全。

#### ✅ auto f = forces();

* 同样拷贝访问器副本，可以重新赋值 `f = another_accessor;`
* 元素仍然是只读的（因为访问器类型是 `ConstArrayAccessor1`）。

#### ❌ const auto& f = forces();

* 绑定到一个 **临时对象的引用**。
* C++ 标准允许延长生命周期，但没有性能优势，反而增加理解负担。
* **不推荐使用**。

#### 总结对比表

| 写法              | 是否创建副本   | 是否能修改数据 | 是否能重新赋值 | 是否推荐  |
| --------------- | -------- | ------- | ------- | ----- |
| `const auto f`  | ✅ 是      | ❌ 否     | ❌ 否     | ✅ 推荐  |
| `auto f`        | ✅ 是      | ❌ 否     | ✅ 是     | ✅ 推荐  |
| `const auto& f` | ❌ 引用临时对象 | ❌ 否     | ❌ 否     | ❌ 不推荐 |

#### ✅ 最佳实践建议

使用 `auto f = forces();` 或 `const auto f = forces();`
避免使用 `const auto&` 接受函数按值返回的轻量对象。

## 计算机图形学
### 一、Jet 求解器继承与调用逻辑概览

---

#### 1. `Animation`：基础动画驱动类

```cpp
class Animation {
public:
    void update(const Frame& frame);  // 外部调用入口

protected:
    virtual void onUpdate(const Frame& frame) = 0;  // 子类实现核心更新逻辑
};
````

> 外部通过 `update(frame)` 推进帧，内部转发调用子类的 `onUpdate(frame)`。

---

#### 2. `PhysicsAnimation`：时间推进控制器

```cpp
class PhysicsAnimation : public Animation {
protected:
    void onUpdate(const Frame& frame) override;
    virtual void onAdvanceTimeStep(double timeIntervalInSeconds) = 0;
};
```

#### 🧠 核心逻辑流程：

* 判断是否进入新帧（`frame.index > _currentFrame.index`）
* 若是，调用 `advanceTimeStep(...)`：

  * 固定子步长模式：`_numberOfFixedSubTimeSteps`
  * 自适应子步长模式：`numberOfSubTimeSteps(...)`
* 每个子步长调用：

  ```cpp
  onAdvanceTimeStep(actualTimeInterval);  // 延迟至子类实现
  ```

---

#### 3. `ParticleSystemSolver3`：粒子系统求解器

```cpp
class ParticleSystemSolver3 : public PhysicsAnimation {
protected:
    void onAdvanceTimeStep(double timeStepInSeconds) override;
};
```

#### ⚙️ 实现核心时间推进：

```cpp
void ParticleSystemSolver3::onAdvanceTimeStep(double timeStepInSeconds) {
    beginAdvanceTimeStep(timeStepInSeconds);

    accumulateForces(timeStepInSeconds);
    timeIntegration(timeStepInSeconds);
    resolveCollision();

    endAdvanceTimeStep(timeStepInSeconds);
}
```

---

#### 4. `SphSolver3`：基于 SPH 的求解器

```cpp
class SphSolver3 : public ParticleSystemSolver3 {
protected:
    void accumulateForces(double timeStepInSeconds) override;
};
```

#### 💡 实现 SPH 专属的力累积逻辑：

```cpp
void SphSolver3::accumulateForces(double timeStepInSeconds) {
    accumulateNonPressureForces(timeStepInSeconds);
    accumulatePressureForce(timeStepInSeconds);
}
```

---

#### ✅ 调用链总结

```text
Animation::update() 
  └─▶ PhysicsAnimation::onUpdate()
        └─▶ advanceTimeStep(...)
              └─▶ onAdvanceTimeStep(...)        // ParticleSystemSolver3 实现
                    └─▶ accumulateForces(...)  // SphSolver3 实现
```

---

#### 🧩 设计思路说明：

* `Animation` 提供统一的帧调度接口。
* `PhysicsAnimation` 封装了时间推进逻辑（固定 / 自适应子步长）。
* `ParticleSystemSolver3` 实现了粒子推进步骤的框架。
* `SphSolver3` 重载具体力学模型，聚焦物理细节。

```
```




