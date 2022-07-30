# Project: implement the Rho method of reduced SM3
# 卜凡臻202000460039独立完成 
# 用c语言实现sm3，并进行rho的简化版碰撞


首先我们测试c语言编写的sm3的正确性和速度，可以看到加密字符串abc是正确的，平均加密100万次需要1.5s

测试的时候需要把main文件中的difine改成TEST，目前库里的项目是进行碰撞所需要的模式。

图片如下

![This is an image](https://github.com/Bufanzhen/chuangxin_project/blob/main/SM3/implement%20of%20c%2B%2B%20and%20rho%20method/%E5%9B%BE%E7%89%87.png)


# rho方法攻击  

最长是实现了24bit长的碰撞，直接运行即可进行碰撞的寻找
![图片](https://user-images.githubusercontent.com/71548447/181870699-bb7b420d-6d18-4ace-93c0-08036e561671.png)
