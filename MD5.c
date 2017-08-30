#include<stdio.h>
#include<stdlib.h>
#include<openssl/md5.h>
#include<string.h>
int pptv(char buf[],int n);
//#define PATH "./test.txt"
int  main(int  argc,  char  **argv )
{
	MD5_CTX ctx;
	unsigned char md5[17] = {0};
	FILE *fp;
	int block_size = 0;
	char  buf[33]={ '\0' };
	char  tmp[3]={ '\0' };
	int block_num  = 0;
	int Time = 0;
	unsigned char *data= (unsigned char*)malloc(1024*1024*1024);
	if(!data)
	{
		printf("malloc the data errer\n");
		return -1;
	}
	printf("the block num !input\n");
	scanf("%d",&block_num);
	printf("the block size is ?\n");
	scanf("%d",&block_size);
	int time = 0;
	int  i = 0,mlen = 0;
	printf("will to open the faile:%s\n",argv[1]);
	fp = fopen(argv[1],"rb");
	if(fp == NULL)
	{
		printf("fopen faile\n");
		return -1;
	}
	int a = fseek(fp, 0, SEEK_END);
	if(a == -1)
	{
		printf("fseek is faile\n");
	}
	int len_f = ftell(fp);
	printf("faile data len_f:%d\n",len_f);
	fseek(fp, 0, SEEK_SET);
	while(block_num)
	{	
		printf("block num:%d\n",++Time);
		if(block_num == 1)
		{
			block_size = len_f - mlen;
		}
		block_num--;
		int len = 0;
		printf("the size is:%d\n", block_size);
		len = fread(data, 1, block_size, fp);
		if(len != block_size)
		{
			printf("the len is:\n",len);
			printf("the read errer\n");
			break;
		}
		printf("the read len:%d\n",len);
		sleep(1);
		mlen = mlen + len;
		MD5_Init(&ctx);
		printf("the data buf:%s\nthe data len is :%d\n",data,sizeof(data));
		MD5_Update(&ctx, data, block_size);
		MD5_Final(md5,&ctx);
		for ( i=0; i<16; i++ )
		{
			sprintf (tmp, "%02X" , md5[i]);
			strcat (buf, tmp);
		}
		pptv(buf,17);
		printf ( "MD5's value to con:%s\n" ,buf);
		memset(data, 0, sizeof(data));
		memset(buf, 0, sizeof(buf));
	}
	fclose(fp);
	free(data);
	return  0;
}

int pptv(char buf[], int n)
{
	printf("MD5 befor did:%s\n", buf);
	int num = 0;
	char t = '0';
	num = n;
	int bufnum = 0;
	int ne = 6;
	int _num = 0;
	while(_num < 2)
	{	
		t = buf[bufnum];
		buf[bufnum] = buf[bufnum + ne];
		buf[bufnum + ne] = t;
		bufnum++;
		t = buf[bufnum];
		buf[bufnum] = buf[bufnum + ne];
		buf[bufnum + ne] = t;
		ne = ne - 4;
		bufnum++;
		_num++;
	}
	int _ne = 2;
	bufnum = bufnum + 4;
	_num = 0;
	t = '0';
	while(_num < 2)
	{	
		t = buf[bufnum];
		buf[bufnum] = buf[bufnum + _ne];
		buf[bufnum + _ne] = t;
		bufnum++;
		t = buf[bufnum];
		buf[bufnum] = buf[bufnum + _ne];
		buf[bufnum + _ne] = t;
		bufnum = bufnum + 3;
		_num++;
	}
	return 0;
}
