# 《智障药盒》
本代码将让你用 Arduino 来做一个~~智障~~药盒，达到定时提醒吃药的目的。
**编写者的水平非常低；还请见谅。欢迎提交改进。**
## 主要功能
- 用你自己的声音作为提醒声。
- 内置 4 个提醒时间，可任意自定义。
- 给你的盒盖加一个驱动，按一下开关即可自动打开 / 关闭。
- 使用蓝牙进行设定 / 读取等操作。
- 显示屏可以显示一些有（无）用的提示。
## 进度
 一部分功能未完善：\
 提醒开关，提醒文字（发送在手机中）

## 组装
### 主控板

**注意：本程序可能不兼容**  ` Arduino Mega ` 、` Due ` **等开发板！**\
**推荐使用` Arduino UNO `。**
### 需要的模块
你需要以下零部件 / 模块：

| 名称 | 作用 |
|---|---|
| 触摸开关或其他开关 | 交互元素 |
| DS1307 时钟芯片 | 加入时间功能|
| 使用 ISD1820PY 或其他**使用方式相同的**录放芯片的录放模块    | 录制提醒音 |
| SSD1306 芯片驱动的 OLED 显示屏 | 显示一些信息 |
| 舵机 | 驱动盒盖开关 |
| 扬声器 x2 | 接在录放模块和 Arduino 中 |
| HC-05 或其他蓝牙模块 | 与兼容的 SPP 设备通信（如手机可定制 APP 等）|

注意：你可能需要针对你使用的模块 / 零部件来相应的更改代码。
有关蓝牙的具体使用，请参照 [蓝牙说明](#蓝牙接口说明) 。

### 连接
引脚的连接如下：（除去电源和 GND 脚）
| Arduino 引脚 | 模块 | 模块的引脚 |
|---           |---  |---        |
| A0 | 按钮 / 触摸开关 1 | SIG / OUT |
| A1 | 按钮 / 触摸开关 2 | SIG / OUT |
| D0 / RX | HC-05 蓝牙模块 | TX ( D ) |
| D1 / TX | HC-05 蓝牙模块 | RX ( D ) |
| D6 | 扬声器 | + |
| D9 | 舵机 | PWM / SIG （橙）|
| D10 | ISD1820PY | PLAYE |
| D11 | ISD1820PY | REC |
| SDA / A4 | OLED 显示屏；DS1307 | SDA |
| SCL / A5 | OLED 显示屏；DS1307 | SCL |
---
## 程序
该节引导你将程序传输到 Arduino 中。\
在进行本操作之前**请先拔出 D0 和 D1 口上的连线**。
### 依赖库
[TimeLib](https://github.com/PaulStoffregen/Time)\
[DS1307RTC](https://github.com/PaulStoffregen/DS1307RTC)\
[Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)\
[Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)

将以上的库文件复制到 Arduino 文件夹 / libraries 下。
### 编译上传
现在重新打开 IDE ，打开本项目。\
选择合适的开发板和端口，即可按下 ` Ctrl + U ` 上传。\
上传完毕之后，即可拔出 USB 连接线，插入 D0 和 D1 。\
连接 DC 电源，就可以使用了。

---
## 使用方法
现在假定连接在 `A0` 接口的开关为 `按钮 1 ` ，连接在 `A2` 接口的开关为 `按钮 2`。\
在待机状态下，屏幕显示时间。\
按下` 按钮 1 `，开关盒盖。\
按下` 按钮 2 `，开启录音。
 - 在按下录音按钮时，如果童锁被激活，屏幕将提示 `不允许录音` 。
### 录音状态
此时屏幕将显示当前录制长度。**最长可以录制 10 秒钟。**\
你可以随时按下 `按钮 2 ` 停止录音。
停止录音后，将回放录音，然后返回待机状态。
### 提醒状态
在预定的时间到达后，机器将先打开盒盖，然后开始提醒。\
提醒时屏幕将显示 “ 该吃药啦 ” 文字和当前时间。按下 `按钮 2 ` 以取消提醒，再按一次关闭盒盖。\
代码中的设定为提醒三次。你可以随意更改。在下一个版本中将会可以设置。

---
## 蓝牙接口说明
通过命令来控制机器。\
### 它能干什么？
 1. 设置任意一个提醒时间。
 2. 读取设置。
 3. 设置童锁，防止误触录音按钮。
 - 在按下录音按钮时，如果童锁被激活，屏幕将提示 `不允许录音` 。
### 格式
每一对方括号表示一个字符；方括号内表示可能的情况。格式如下：
```
[lrs][1234l][,][0-2][0-9][,][0-5][0-9]
```
第一个字符：\
`l` 单独使用。开启和关闭童锁：
```
l
```
`r[时间 ID ]` 读取四个时间段的一个。
```
r1
```
此时返回：
```
09,30
```
`rl` 用来读取童锁状态：
```
rl
```
返回：
```
0
```
`s` 后跟时间 ID 。设置时间。格式：`小时,分钟`
```
s1,15,30
```
此时返回：
```
15,30
```
第二个字符：\
`1-4` 表示对应的时间。
`l` 表示童锁。仅搭配 `r` 使用。

---
## 改进
欢迎你对我的代码提出意见或者直接改进。
