/*************************************************************************
	> File Name: kfifo_ref.cpp
	> Author: Treasure1029
	> Mail: 992052905@qq.com
	> Created Time: Tue 19 Nov 2024 08:45:24 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

// 一、kfifo_alloc 分配kfifo内存和初始化工作
// 申请的内存空间为 size = 2的幂次方
// 好处： kfifo->in % kfifo->size 可以转化为 kfifo->in & (kfifo->size – 1)
struct kfifo *kfifo_alloc(unsigned int size, gfp_t gfp_mask, spinlock_t *lock)
{
    unsigned char *buffer;
    struct kfifo *ret;

    /*
     * round up to the next power of 2, since our 'let the indices
     * wrap' tachnique works only in this case.
     */
    // (size & (size -1) ： 用于判断size是否为2的幂，条件为真则表示不是2的幂)
    if (size & (size - 1)) {
        BUG_ON(size > 0x80000000);
        size = roundup_pow_of_two(size);  // 将size向上扩展为2的幂
    }

    buffer = kmalloc(size, gfp_mask);
    if (!buffer)
        return ERR_PTR(-ENOMEM);

    ret = kfifo_init(buffer, size, gfp_mask, lock);

    if (IS_ERR(ret))
        kfree(buffer);

    return ret;
}

// 二、__kfifo_put和__kfifo_get巧妙的入队和出队
//
unsigned int __kfifo_put(struct kfifo *fifo,
             unsigned char *buffer, unsigned int len)
{
    unsigned int l;

    // （fifo->in - fifo->out）为buffer已有数据长度
    // ***kfifo每次入队或出队，kfifo->in或kfifo->out只是简单地kfifo->in/kfifo->out += len，并没有对kfifo->size 进行取模运算。***
    // ***kfifo->in和kfifo->out总是一直增大，直到unsigned in最大值时，又会绕回到0这一起始端。***
    // 即使kfifo->in回到0的那端， 该性质保持不变。
    //
    // (fifo->size - (fifo->in - fifo->out)) 为剩余可写空间长度
    // 取较小的作为输入大小
    len = min(len, fifo->size - fifo->in + fifo->out);

    /*
     * Ensure that we sample the fifo->out index -before- we
     * start putting bytes into the kfifo.
     */

    smp_mb();

    // 判断len是否超过右边界，
    /* first put the data starting from fifo->in to buffer end */
    l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
    memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);

    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(fifo->buffer, buffer + l, len - l);

    /*
     * Ensure that we add the bytes to the kfifo -before-
     * we update the fifo->in index.
     */

    smp_wmb();

    fifo->in += len;

    return len;
}

unsigned int __kfifo_get(struct kfifo *fifo,
             unsigned char *buffer, unsigned int len)
{
    unsigned int l;

    len = min(len, fifo->in - fifo->out);

    /*
     * Ensure that we sample the fifo->in index -before- we
     * start removing bytes from the kfifo.
     */

    smp_rmb();

    /* first get the data from fifo->out until the end of the buffer */
    l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
    memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(buffer + l, fifo->buffer, len - l);

    /*
     * Ensure that we remove the bytes from the kfifo -before-
     * we update the fifo->out index.
     */

    smp_mb();

    fifo->out += len;

    return len;
}

