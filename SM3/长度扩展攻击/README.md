# 卜凡臻202000460039完成

# 代码运行说明

代码用编辑器打开后运行，会输出两个hash值，其中第一个是敌手可以根据原文的hash值伪造出来的，扩展后的hash  
第二个hash是正常通过把原文、padding、扩展 进行拼接后在进行hash的值，可以看到是一样的
![图片](https://user-images.githubusercontent.com/71548447/181908023-6b8f302c-a9a0-42cd-8f98-224e58dba807.png)

# 代码大体思路

![图片](https://user-images.githubusercontent.com/71548447/181908047-1d817a2f-dede-4e62-949c-3a28f12ba8a3.png)

根据此页ppt我们知道了此次长度扩展攻击就是，敌手已知一段消息M的哈希H（M）但是不知道M本身，然后得到H（M||extension）的值，其中extension是可以是任意的值。
具体实现我们显示从gmssl的第三方python库中的sm3.py中提取到了填充函数，然后把已知的一段hash作为iv，将攻击者的扩展消息作为要加密的并输入，即可得到一段伪造后的hash值。
