### SimpleIP (Simple Image-Processing) 是一个不想用matlab写图像处理作业的学生写的跨平台图像处理框架。

![屏幕快照 2017-10-17 下午8.31.29](https://raw.githubusercontent.com/nerososft/SimpleIP/master/屏幕快照%202017-10-18%20下午4.15.18.png)

### 尚在测试中的即将加入的增强学习部分的 demo
![屏幕快照 2017-10-17 下午8.31.29](https://raw.githubusercontent.com/nerososft/SimpleIP/master/%E5%B1%8F%E5%B9%95%E5%BF%AB%E7%85%A7%202017-10-20%20%E4%B8%8B%E5%8D%882.32.19.png)
## 窗口

### 1. 新建窗口

```c++
OpenIP::Board* board = new OpenIP::Board("MyWindow",640,480,new OpenIP::ColorRGB(255,255,255));
```

### 2. 窗口事件绑定

```c++
 board->setEventHandling();
```

### 3. 窗口渲染

```c++
 board->run();
```



##  图片操作

### 1. 读取png图片为RGB矩阵`std::vector<std::vector<ColorRGB*>>`

```c++
 PNGLoader *pngloader = new PNGLoader();
        std::vector<std::vector<ColorRGB *>> pixelsMap = pngloader->loadPNG("yz.png");
```

### 2.读取图像到PixelMap

```c++
PixelMap* pixelMap = new PixelMap(0, 0, width, height, new ColorRGB(255, 255, 255));
        pngLoader->loadPNGToPixelMap("yz.png",pixelMap);
```



### 3. PixelMap 像素矩阵

```c++
PixelMap* pixelmap = new PixelMap(0, 0, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
```

### 3. PixelMap像素矩阵像素填充

```c++
for (int i = 0; i < this->width / 4; i++) {
            std::vector<Pixel *> pp;
            for (int j = 0; j < this->height / 2; j++) {
                pp.push_back(new Pixel(i, j, pixelsMap[j][i]));
            }
            pixels.push_back(pp);
}
pixelmap->setPixelMap(pixels);
        
```

### 4. PixelMap像素矩阵标准化【根据窗口大小】

```c++
pixelmap->normalize(width, height);
```

## 图像处理

### 1. 图像滤波

#### 中值滤波

```c++
Fliter* fliter = new Fliter(pixelMap);
        pixelMap = fliter->median();
```

#### 最大值滤波

```c++
Fliter* fliter = new Fliter(pixelMap);
       pixelMap = fliter->max();
```



#### 最小值滤波

```c++
Fliter* fliter = new Fliter(pixelMap);
        pixelMap = fliter->min();
```



#### 算数均值滤波

```c++
Fliter* fliter = new Fliter(pixelMap);
        pixelMap = fliter->arithmetic_mean();
```



#### 几何均值滤波

```c++
Fliter* fliter = new Fliter(pixelMap);
        pixelMap = fliter->geometric_mean();
```



#### 谐波均值滤波

```c++
Fliter* fliter = new Fliter(pixelMap);
        pixelMap = fliter->harmonics();
```



#### 逆波均值滤波

```c++
Fliter* fliter = new Fliter(pixelMap);
        pixelMap = fliter->inverse_harmonic();
```

## 字体

### 1. 字体渲染

#### 初始化

```c++
Font* font = new Font("default.otf", FONT_MODE::TRANSPARENT,new ColorRGB(255,255,255), new ColorRGB(0,255,0), 500, 500,100, 200);
```

#### 绘制

```c++
 font->draw("this is my font");
        font->normalize(width,height);
```

#### 渲染

```
font->render();
```

