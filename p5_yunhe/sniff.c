#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void printsb(struct superblock* sb);
int checksb(struct superblock* sb);
int check_dir(struct dinode* dir_inode);
void printdn(struct dinode* dn);
void printdir(struct dirent* dir);

//remember to check function return value

int 
main(int argc, char* argv[])
{

  int fd = open("fs.img", O_RDWR);
  if (fd < 0)
  {
	printf("error: fd < 0\n");
  }

  struct superblock* sb;
  sb = (struct superblock*)(malloc(sizeof(struct superblock)));

  if (lseek(fd, BSIZE, SEEK_SET) < 0)
  {
	printf("error: lseek failed\n");
  }

  if (read(fd, sb, sizeof(struct superblock)) < 0)
  {
	printf("error: read failed\n");
  }

    printsb(sb);


  //inode struct
  struct dinode* dn;
  dn = (struct dinode*)(malloc(sizeof(struct dinode)));

  if ( lseek(fd, BSIZE * 2, SEEK_SET) < 0)
  {
       printf("error: lseek failed\n");
  }

  if (read(fd, dn, 200 * sizeof(struct dinode)) < 0)
  {
        printf("error: read failed\n");
  }

  printf("inode0 is reserved. Not printing.\n");


  int inode_cnt;
  for(inode_cnt = 1; inode_cnt < 200; inode_cnt++)
  {
	dn++;
	printf("inode%d\n", inode_cnt);
	printdn(dn);
  }

/*
	dn++;
	printf("inode%d\n", 1);
	printdn(dn);
  
	dn++;
	printf("inode%d\n", 2);
	printdn(dn);
  
	dn++;
	printf("inode%d\n", 3);
	printdn(dn);
  
	dn++;
	printf("inode%d\n", 4);
	printdn(dn);
*/  

  //dirent struct
  
  //struct dirent* dir;
  //dir = (struct dirent*)(malloc(sizeof(struct dirent)));
  char bitmap[512];
  if ( lseek(fd, BSIZE * 28, SEEK_SET) < 0)
  {
       printf("error: lseek failed\n");
  }

  if (read(fd, &bitmap, BSIZE) < 0)
  {
        printf("error: read failed\n");
  }

  
  //printf("dirent%d\n",1);
  //printdir(dir);
  printf("====\nBit map is:\n");
  int j;
  for(j = 0; j<512; j++)
  {
	printf("bitmap[%d] is : %c\n",j, bitmap[j]);
  }

  return 0;



  
}

void 
printsb(struct superblock* sb)
{
  printf("=====================\nSuperblock info:");
  printf("size = %d\n nblocks = %d\n ninodes = %d\n", sb->size, sb->nblocks, sb->ninodes);
  printf("=====================\n");
}
int 
checksb(struct superblock* sb){
	//TODO 
	return 0;	
}

void
printdn(struct dinode* dn)
{
  printf("=====================\ndinode info:");
  printf("type = %u\n major = %u\n minor = %u\n nlink = %u\n size = %d\n", dn->type, dn->major, dn->minor, dn->nlink, dn->size);
  printf("Data block addresses(%d entries):\n", NDIRECT+1);

  int i;
  for(i = 0; i < NDIRECT + 1; i++)
  {
	printf("addrs[%d] = %d\n",i, dn->addrs[i]);
  }

  printf("=====================\n");
}


void 
printdir(struct dirent* dir)
{
 
  printf("=====================\ndirent info:\n");
  printf("inum = %u\n", dir->inum);
  printf("name(%d entries):\n", DIRSIZ);

  int i;
  for(i = 0; i < DIRSIZ; i++)
  {
	printf("name[%d] = %d\n",i, dir->name[i]);
  }


  printf("=====================\n");

}

int
check_dir(){
int inode_cnt;
  for(inode_cnt = 1; inode_cnt < 200; inode_cnt++)
  {
	dn++;
	printf("inode%d\n", inode_cnt);
	printdn(dn);
  }
}
