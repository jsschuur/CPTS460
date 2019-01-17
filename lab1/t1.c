#include "ext2.h"

#define TRK 18
#define CYL 36
#define BLK 1024

int color = 0x0A;

int getblk(int blk, char *buf){
    readfd( blk/18, ((blk)%18)/9, ( ((blk)%18)%9)<<1, buf);
}

int prints(char *s){
	while (*s) 
		putc(*s++);
}
		
int gets(char s[]){

	while ((*s = getc()) != '\r') 
		putc(*s++);
	*s = 0;
}

main(){

	char name[64], buf[1024], blk_buf[1024], *cp;

	GD *gp;
	INODE *ip;
	DIR *dp;

	int i;

	u16 iblk;


	prints("Reading block 2\n\r");
	getblk((u16)2, buf);

	gp = (GD*)buf;

	iblk = (u16)gp->bg_inode_table;



	prints("inode_block="); putc(iblk + '0'); prints("\n\r");

	prints("Reading inode table block\n\r");
	getblk(iblk, buf);

	ip = (INODE *)buf + 1;

	//to get rid of garbage characters, copy into a string with length 
	//dp->name_len and print copied string
	
	for(i = 0; i < 12; i++){
		prints("block ["); putc(i + '0'); prints("]: "); prints("\n\r    ");

		if(ip->i_block[i] == 0){
			prints("No entries in block ");
			putc(i + '0');
			prints("\n\r");
			continue;
		}


		getblk((u16)ip->i_block[i], blk_buf);


		cp = blk_buf;
		dp = (DIR *)blk_buf;

		while(cp < blk_buf + 1024)
		{
			prints(dp->name);
			prints(", ");

			cp += dp->rec_len;
			dp = (DIR *)cp;
		}
		prints("\n\r");

	}

	prints("\n\r");

	

	while(1){
		prints("Enter a string: ");
		gets(name);
		if(name[0] == 0)
			break;
		prints("\n\rYou entered: "); 
		prints(name); 
		prints("\n\r");
	}
	prints("return to assembly and hang\n\r");
}

