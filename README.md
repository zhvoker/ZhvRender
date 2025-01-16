# ZhRender 
基于 OpenGL 的实时渲染器
项目前端 GUI 使用 Imgui，渲染 API 使用 OpenGL。
(2025.1.16 目前还在学习阶段， 计划半年内完成渲染器基本功能)
## Dependent Package Install依赖安装
### glfw
```
// opengl 安装
sudo apt-get install build-essential
sudo apt-get install libgl1-mesa-dev

// glfw
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev 
```
### glm
```
git clone https://github.com/g-truc/glm.git
cd glm
cmake     -DGLM_BUILD_TESTS=OFF     -DBUILD_SHARED_LIBS=OFF     -B build .
cmake --build build -- all
cmake --build build -- install
```

## Build and Get start 构建并运行
```
git clone https://github.com/zhvoker/ZhvRender.git
./setup.sh
cd bin
./ZhRender
```
