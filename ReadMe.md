# TinyEngine

## 介绍

TinyEngine是一个为编写1MGames而搭建的底层（我实在是不想每次参赛都写新底层了）。

在Release模式下，库本身是300+KB。但是由于使用了模板，helloworld的Demo编译出来有1.07M。但使用UPX压一压能压到400多KB。

## 目录结构

* 3rdlibs：第三方库，主要有
  * glfw：用于搭建窗口
  * glad：用于导入OpenGL
  * miniaudio：用于播放音频
  * nuklear：用于绘制GUI
  * stb：用于加载图片
* demo：一些Demo，指定`ENGINE_BUILD_DEMOS=ON`可以编译Demo。请在工程跟目录下运行Demo
* engine：底层的头文件
* src：底层的源文件
* shader：底层的着色器，需要和底层一起发布
* resources：底层需要的一些资源，需要和底层一起发布
* snapshots：截图

## 编译

使用

```git
git submodule update --init --recursive
```

将需要的第三方库源码拉下来，然后编译：

```bash
cmake -S . -B build
cmake --build build
```

## 注意事项

使用VS编译可以得到最小的大小。MinGW由于自己有一套库，发布的时候要带这些库，所以最后结果贼大，不推荐使用。

## 目前的进展

* [x] 基本2D和3D渲染器
* [x] 鼠标键盘输入
* [x] ECS
* [x] 场景
* [x] 2D/3D摄像机
* [x] Configer
* [x] 定时器
* [x] TileSheet
* [x] GUI (使用nuklear)
* [x] 文字绘制 (使用位图文字，只能绘制英文，数字和标点)
* [x] 音频系统 (使用miniaudio)
* [ ] 2D 物理系统
* [ ] 2D Animation

* [ ] 将底层更换为SDL
* [ ] 制作编辑器


## 目前效果：

![snapshots](./snapshots/snapshot.png)
