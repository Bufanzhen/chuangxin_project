from gmssl import sm3
import random
import time

def collision():
    a=9
    sizeofspace=2**(int(a*4)-1)
    t1=time.time()
    while True:
        listA=[]
        listB=[]
        num1=1
        num2=num1
        for i in range(sizeofspace):
            str01=sm3.sm3_hash(sm3.bytes_to_list(str(num2).encode()))[:a]
            if str01 in listB:
                print(num2)
                print(listB.index(str01)+num1)
                print(sm3.sm3_hash(sm3.bytes_to_list(str(num2).encode())))
                print(sm3.sm3_hash(sm3.bytes_to_list(str(listB.index(str01)+num1).encode())))
                t2=time.time()
                print("ending",t2-t1)
                return
            listB.append(str01)
            num2+=1
        print("1 loop")


collision()
