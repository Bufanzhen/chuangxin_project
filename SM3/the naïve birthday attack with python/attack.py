from gmssl import sm3
import random
import time

def collision():
    a=int(input())
    sizeofspace=2**(int(a*4)-1)
    t1=time.time()
    while True:
        listA=[]
        listB=[]
        num1=1
        num2=num1
        for i in range(sizeofspace):
            str01=sm3.sm3_hash(sm3.bytes_to_list(str(num2).encode()))[:a]
            listB.append(str01)
            num2+=1
        for i in range(sizeofspace-1):
            str1=listB[i]
            for j in range(i+1,sizeofspace):
                if (str1==listB[j]):
                    print(num1+i,num1+j)
                    t2=time.time()
                    print("ending",t2-t1)
                    return
        print("1 loop")


collision()
