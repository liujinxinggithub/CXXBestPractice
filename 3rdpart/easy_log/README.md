# 一.Easylogging简介：
Easyloggingpp是一个C++开源log库，其在github的地址：https://github.com/muflihun/easyloggingpp
Easyloggingpp最大的特点是只需一个头文件，且所有功能都是内部实现，无需依靠其他第三方库，所以使用起来非常方便。同时，该库又有很丰富的特性：
(0)跨平台：windows，linux，Android等平台
(1)轻量级
(2)高性能
(3)线程和类型安全性
(4)高可配置性：可配置log输出目的设备，自定义log格式，log等级调控等。
(5)性能跟踪
(6)支持STL  log，第三方库(QT,boost等)log
(7)可扩展：支持自定义类log输出

# 二.Easylogging使用
在写这篇文章时(2017-08-10)，Easyloggingpp的最新版本为v9.95.0。在V8.91之后的版本都会用到C++11的一些特性，所以，如果你的项目所使用的编译器不能完全支持C++11的特性，可考虑使用V8.91版。V8.91是目前很稳定的支持C++98和C++03的版本。
使用Easyloggingpp非常简单，只需两个步骤：
(1)把easylogging++.h 包含进你的项目中；
(2)用一个宏进行初始化：INITIALIZE_EASYLOGGINGPP
```c++
#include "easylogging++.h"
_INITIALIZE_EASYLOGGINGPP

int _tmain(int argc, _TCHAR* argv[])
{
LOG(INFO) << "My First Easylog!" ;
return 0 ;
}
```


Easyloggingpp的使用就是怎么简单。

# 三.Easylogging配置
默认情况下，在windows中，logs将会输出到当前工作目录下的logs/myeasylog.log下，可通过配置改变这个路径。在开始配置之前，需要了解下Easylogging中的等级概念，其共有下面的一些等级：
ALL     INFO      DEBUG       WARNING      ERROR       FATAL  等等，其中ALL是一个概念上的等级，不能用于实际的LOG输出。当配置了ALL等级了之后，其他没有配置的等级都按照ALL等级的配置。

比较常用的配置项如下：  
(1)是否输出log (ENABLED)  
(2)log是输出到标准输出还是输出到log文件 (TO_FILE , TO_STANDARD_OUTPUT)  
(3)log文件名和路径名 (FILENAME)  
(4)log格式 (FORMAT)  
(5)log文件达到多大的时候清除掉log，重新开始 (ROLL_OUT_SIZE)  
括号内的为每一个配置项的关键字  


配置信息的格式如下：  
// 为注释符号  
*LEVEL:  
CONFIGURATION_NAME = CONFIGURATION_VALUE  

一个简单的配置项例子如下：  
```shell
* ALL: // We need to start level with star '*' and end with colon ':'
  FORMAT   ="%level: %log"  // Quotes are not necessary but to make it more readable we wrap quotes around.
  FILENAME = "logs/testLog.log"
  ENABLED =true
  TO_FILE =true
  TO_STANDARD_OUTPUT =false
  MILLISECONDS_WIDTH =3
  PERFORMANCE_TRACKING =false
  ROLL_OUT_SIZE           =  2097152 // Throw log files away after 2MB

           // Following configuration only defines FORMAT for INFO, rest of the configurations are used from ALL configurations above
          * INFO:
          FORMAT ="%datetime %level %log"

```
 
版权声明：本文为CSDN博主「CccWeiXian」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/woshichenweixian/article/details/77018452