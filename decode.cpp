#include "decode.h"
#pragma warning(disable : 4996)
void change_to_char(int byte, FILE* fp_o) {
	int table[17] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',' ' };
	fputc(table[byte / 16], fp_o);
	fputc(table[byte % 16], fp_o);
	fputc(table[16], fp_o);
	return;
}

int decodef(char* in_file, char *out_file) {
	/*freopen("out.log", "w", stdout);
	printf("%s", in_file);
	fclose(stdout);*/
	FILE* fp_i, * fp_o;
	fp_i=fopen(in_file, "rb");
	fp_o=fopen(out_file, "w");
	if (!fp_o) {
		//printf("Êä³öÎÄ¼þÎÞÐ§£¡");
		//fclose(fp_i);
		//fclose(fp_o);
		return 3;	// 错误代码3：输出文件创建失败
	}
	if (!fp_i) {
		//fclose(fp_i);
	fclose(fp_o);
		/*freopen("out.log", "w", stdout);
		printf("\n\n%s", in_file);
		fclose(stdout);*/
		return 2;	//错误代码2：写入文件读取失败 
	}
	
	int byte = 0;
	while ((byte = getc(fp_i)) != EOF) {
		change_to_char(byte, fp_o);
	}
	fclose(fp_i);
	fclose(fp_o);
	return 0;
}