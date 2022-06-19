#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

int main(void) 
{
    int fd;
    char buf[1024];
    int len = 0;
    int i;
    char temp[16];
    char *ptemp = temp;
    int val = 0;
    float ave = 0;
    bool flag = true;
    int cnt = 0;
    
    memset(buf, 0, sizeof(buf));
    memset(temp, 0, sizeof(temp));

    fd = open("data.txt", O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
    assert(fd >= 0);
    len = read(fd, buf, sizeof(buf));
    close(fd);

    //最后一个数字也需要有，结尾
    for(i = 0; i <= len; i++) {
        if (',' != buf[i]) {
            *ptemp = buf[i];
            ptemp++;
        } else {
            val = strtol(temp, NULL, 10);
            if (true == flag) {
                ave = val;
                flag = false;
                cnt = 1;
            } else {
                cnt++;
                //x_ave(n) = x_ave(n-1) + (x(n) - x_ave(n-1)) / n
                ave = ave + (val - ave) / cnt;
            }
            memset(temp, 0, sizeof(temp));
            ptemp = temp;
        }
    }
    printf("ave = %f\n", ave);

    return 0;
}
