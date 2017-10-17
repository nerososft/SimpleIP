OpenIP

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

### 2. PixelMap 像素矩阵

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

