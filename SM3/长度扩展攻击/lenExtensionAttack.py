from gmssl import sm3
"""
def sm3_hash(msg):
    # print(msg)
    len1 = len(msg)
    reserve1 = len1 % 64
    msg.append(0x80)
    reserve1 = reserve1 + 1
    # 56-64, add 64 byte
    range_end = 56
    if reserve1 > range_end:
        range_end = range_end + 64

    for i in range(reserve1, range_end):
        msg.append(0x00)

    bit_length = (len1) * 8
    bit_length_str = [bit_length % 0x100]
    for i in range(7):
        bit_length = int(bit_length / 0x100)
        bit_length_str.append(bit_length % 0x100)
    for i in range(8):
        msg.append(bit_length_str[7-i])

    group_count = round(len(msg) / 64)

    B = []
    for i in range(0, group_count):
        B.append(msg[i*64:(i+1)*64])
######以上为对msg进行填充，得到一个列表B用来储存填充后的消息
        
    V = [] #初始向量，在长度扩展攻击中，需要把其替换为原消息的hash值
    V.append(IV)
    for i in range(0, group_count):
        V.append(sm3_cf(V[i], B[i]))
##此时V[i+1]中就是hash值，下面是将其转为字符串
    y = V[i+1]
    result = ""
    for i in y:
        result = '%s%08x' % (result, i)
    return result

"""


# arg1 msgOfattacker :攻击者要填充的数据
# arg2 hashOfOriginalData :原来数据的hash值
def LenExtensionAttack(msgOfattacker,hashOfOriginalData):
    listOfHash=[]
    for i in range(8):
        listOfHash.append(int(hashOfOriginalData[i*8:(i+1)*8],16))
    V1 = []
    V1.append(listOfHash)
    """ copy from sm3.py"""
    # print(msg)
    len1 = len(msgOfattacker)
    reserve1 = len1 % 64
    msgOfattacker.append(0x80)
    reserve1 = reserve1 + 1
    # 56-64, add 64 byte
    range_end = 56
    if reserve1 > range_end:
        range_end = range_end + 64

    for i in range(reserve1, range_end):
        msgOfattacker.append(0x00)

    bit_length = (len1) * 8
    bit_length_str = [bit_length % 0x100]
    for i in range(7):
        bit_length = int(bit_length / 0x100)
        bit_length_str.append(bit_length % 0x100)
    for i in range(8):
        msgOfattacker.append(bit_length_str[7-i])

    group_count = round(len(msgOfattacker) / 64)

    B = []
    for i in range(0, group_count):
        B.append(msgOfattacker[i*64:(i+1)*64])
    B2 = "%0128s" %hex(sum(B[-1][len(B[-1]) - i - 1] * (256 ** i) for i in range(len(B[-1]))) + 512 * len(B))[2:]
    B[-1] = [int(B2[i:i + 2],16) for i in range(0,128,2)]
    """ copy from sm3.py"""

    for i in range(0, group_count):
        V1.append(sm3.sm3_cf(V1[i], B[i]))
##此时V[i+1]中就是hash值，下面是将其转为字符串
    y = V1[i+1]
    result = ""
    for i in y:
        result = '%s%08x' % (result, i)
    return result





hashOforinginal=sm3.sm3_hash(sm3.bytes_to_list(b"abc"))
hashAfterAttack=LenExtensionAttack(sm3.bytes_to_list(b"hacked_by_bufanzhen"),hashOforinginal)
print(hashAfterAttack)
#我们手动把上面的 abc ||padding|| hacked_by_bufanzhen 编写成ascii码对应的列表
listOfAfterExtension=[97,98,99 ,128] #'abc'||0b10000000
for i in range(64-1-4):
    listOfAfterExtension.append(0)
listOfAfterExtension.append(24) #填充的最后跟上数据的长度，3byte=24
listOfExtension=sm3.bytes_to_list(b"hacked_by_bufanzhen")
listOfAfterExtension=listOfAfterExtension+listOfExtension
hashOforinginal=sm3.sm3_hash(listOfAfterExtension)
print(hashOforinginal)

