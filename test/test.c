#include <stdio.h>
#include <stdlib.h>


enum CMD_ID{
	DEV_INFO = 0,
};

typedef unsigned char uint8_t;
typedef int int32;

/*
typedef struct devinfo{ 
	int head; 
	int ver; 
	int seqNo; 
	int cid; 
	int reFlag;  
}__attribute__((__packed__)) devinfo_t;

#define DEVINFO_SIZE 	sizeof(struct devinfo)
#define VER_1			(1)

static int g_seq = 0;


static int packet_add_head(struct devinfo *dev);
static void print_info(char *);
*/

void hex_print(uint8_t *buf, int32 size, uint8_t crc);
uint8_t get_crc_value(uint8_t *buf, int buf_size);

int main(void)
{
	/*
	struct devinfo *devinfo_test = NULL;
	devinfo_test = (struct devinfo *)malloc(DEVINFO_SIZE);

	devinfo_test->reFlag = packet_add_head(devinfo_test);

	char *str = devinfo_test;
	str = str - 1;
	str[0] = '1';
	print_info(str);

	free(str);
	*/
	// 获取设备基本信息
	uint8_t devinfo_test[8] = {0xaa, 0x55, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};
	uint8_t crc_0 = get_crc_value(devinfo_test, sizeof(devinfo_test));
	printf("the crc of devinfo_test is %d\r\n", crc_0);
	hex_print(devinfo_test, sizeof(devinfo_test), crc_0);

	printf("\n=================================================================\r\n");

	// 获取当前状态
	uint8_t event_test[8] = {0xaa, 0x55, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00};
	uint8_t crc_1 = get_crc_value(event_test, sizeof(event_test));
	printf("the crc of event_test is %d\r\n", crc_1);
	hex_print(event_test, sizeof(event_test), crc_1);

	printf("\n=================================================================\r\n");

	// 模组主动发送
	// 待终端后续测试
	

	// 获取可以连接的wifi
	uint8_t wifilist_test[8] = {0xaa, 0x55, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00};
	uint8_t crc_2 = get_crc_value(wifilist_test, sizeof(wifilist_test));
	printf("the crc of wifilist_test is %d\r\n", crc_2);
	hex_print(wifilist_test, sizeof(wifilist_test), crc_2);

	printf("\n=================================================================\r\n");


	// 设置可以连接的wifi
	// RedmiK70 12345678 
	uint8_t wifiset_test[104] = {0xaa, 0x55, 0x00, 0x04, 0x05, 0x00, 0x00, 0x60,
								0x52, 0x65, 0x64, 0x6D, 0x69, 0x4B, 0x37, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
								, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
								, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
								,0x79, 0x75, 0x61, 0x6E, 0x63, 0x68, 0x75, 0x61, 0x6e, 0x67, 0x6a, 0x75, 0x6E, 0x2E, 0x6D, 0x6F, 0x79, 0x69, 
								0x6E, 0x2E, 0x63, 0x6F, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t crc_3 = get_crc_value(wifiset_test, sizeof(wifiset_test));
	printf("the crc of wifiset_test is %d\r\n", crc_3);
	hex_print(wifiset_test, sizeof(wifiset_test), crc_3);

	// 应该写一个转换为十六进制的函数的
	printf("\n=================================================================\r\n");
	
	// 
	printf("under is test sn get\r\n");
	uint8_t sn_array[8] = {0xaa, 0x55, 0x00, 0x03, 0x0B, 0x00, 0x00, 0x00};
	uint8_t crc_4 = get_crc_value(sn_array, sizeof(sn_array));
	printf("the crc of sn_array is %d\r\n", crc_4);
	hex_print(sn_array, sizeof(sn_array), crc_4);


	printf("\n=================================================================\r\n");
	
	// 
	printf("under is test sn set\r\n");
	uint8_t sn_array1[28] = {0xaa, 0x55, 0x00, 0x03, 0x0C, 0x00, 0x00, 0x14, 
							0x46, 0x36, 0x30, 0x31, 0x30, 0x41, 0x30, 0x41, 0x30, 0x30, 0x30, 0x30, 0x32, 0x33,
							0x00, 0x00, 0x00};
	uint8_t crc_5 = get_crc_value(sn_array1, sizeof(sn_array1));
	printf("set sn should is F6010A0A000023");
	printf("the crc of sn_array1 is %d\r\n", crc_5);
	hex_print(sn_array1, sizeof(sn_array1), crc_5);

	getchar();

	return 0;
}



uint8_t get_crc_value(uint8_t *buf, int buf_size)
{
	uint8_t crc = 0;
	for (int i = 0; i < buf_size; i++) {
		crc += buf[i];
		// printf("crc = %d\r\n", crc);
	}
	crc = crc % 256;
	return crc;
}
// 传入总数据 和 总长度
void hex_print(uint8_t *buf, int32 size, uint8_t crc) // (1):头部加0x00，0x01 (2):尾部输出 crc
{
	printf("size = %d\r\n", size);
	int i = 0;
	int flag = 0;
	int t_size = size;
	int cnt = 0;
	if (size <= 18) {
		printf("31 ");
	} else {
		printf("30 ");
	}

	do {
		printf("%02x ", buf[i]);
		i++;
		cnt++;
		if (i % 19 == 0 && (t_size - i) > 18) {
			printf("30 ");
			cnt = 0;
		} else if (flag == 0 && (t_size - i) <= 18 && cnt == 19) {
			printf("31 ");
			flag = 1;
		}
		size--;
	}while(size != 0);

	// printf("i = %d\r\n", i);
	printf("%02x ", crc);
	printf("\r\n");
}

/*static void print_info(char *str)
{
	if (str[0] == '1') {
		struct devinfo *dev = (struct devinfo *)(str + 1);
		printf("head : %d\r\n", dev->head);
		printf("ver : %d\r\n", dev->ver);
		printf("seqNo : %d\r\n", dev->seqNo);
		printf("cid : %d\r\n", dev->cid);
	} else {
		printf("str[0] is not character '1'\r\n");
	}
}

static int packet_add_head(struct devinfo *dev)
{
	dev->head = 3;
	dev->ver = VER_1;
	dev->seqNo = g_seq++;
	dev->cid = DEV_INFO;

	return 0;
}*/