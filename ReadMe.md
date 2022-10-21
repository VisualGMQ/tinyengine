# TinyEngine

## 介绍

TinyEngine是一个为编写1MGames而搭建的底层（我实在是不想每次参赛都写新底层了）。

**这个分支是纯SDL分支，除了Toml++库之外没有用其他的非SDL库**

在Release模式下，helloworld的Demo编译出来有500+KB。但使用UPX压一压能压到200+KB。

## 目录结构

* 3rdlibs：第三方库，主要有
  * tomlplusplus：用于读写TOML文件
* demo：一些Demo，指定`ENGINE_BUILD_DEMOS=ON`可以编译Demo。请在工程跟目录下运行Demo
* engine：底层的头文件
* src：底层的源文件
* resources：测试使用的资源
* snapshots：截图
* init.toml：\[可选\]程序初始化的一些设置（Debug模式下，会读取`init.toml`文件。Release模式下则会在编译时打包进程序，无需随程序发布）

## 编译

```bash
cmake -S . -B build -DSDL2_ROOT=<your sdl2 root dir> -DSDL2_TTF_ROOT=<your sdl2_ttf root dir> -DSDL2_MIXER_ROOT=<your sdl2_mixer root dir>
cmake --build build
```

如果觉得设置路径的命令麻烦，也可以使用cmake-gui:

![cmake-gui](./snapshots/cmake-gui.png)

## 运行Demo

使用

```bash
cmake --build build --target demo-<demo name>
```

来运行。这里的`demo-name`是Demo的名称。目前有两个：

* helloworld
* small_man

## 注意事项

本框架目前只支持使用VS编译，因为VS编译出的体积最小，且VS运行库不计入空间。

MinGW由于自己有一套库，发布的时候要带这些库，所以最后结果贼大，不使用。

本工程在VS2022下编译通过。

## 目前的进展

* [x] 基本2D渲染器（使用SDL渲染器）
* [x] 鼠标键盘输入
* [x] ECS
* [x] 场景
* [x] 2D/3D摄像机
* [x] 定时器
* [x] TileSheet
* [x] 文字绘制
* [x] 音频系统
* [x] 2D Animation
* [x] 使用TOML读取/编写配置文件
* [x] 2D 物理系统（只支持矩形碰撞盒子，很简陋）

* 延后：
  * [ ] 加入反射，制作编辑器

## 目前效果

![snapshots](./snapshots/snapshot.png)
