/*
 *==================================================================
 *
 *       Filename:  mem_monitor.c
 *
 *    Description:  Monitoring the memory utilization
 *
 *        Version:  1.0
 *        Created:  06/28/2013 01:55:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ixiami
 *
 *==================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char* skip_token(char* ptr)
{
  if (!ptr) {
		return NULL;
	}
	while(*ptr && !(*ptr<='9' && *ptr >='0')) {
		++ptr;
	}
	return ptr;
}


float get_meminfo()
{
	char buf[512];
	int fd = open("/proc/meminfo", O_RDONLY);
	if (fd < 0) {
		perror("Failed to open /proc/meminfo");
		return -1;
	}
	int len = read(fd, buf, sizeof(buf));
	close(fd);
	buf[len] = '\0';

	char *ptr = buf;
	ptr = skip_token(ptr);
	unsigned long total_mem = strtoul(ptr, &ptr, 10);
	ptr = strchr(ptr, '\n');
	++ptr;
	ptr = strchr(ptr, '\n');
	++ptr;
	ptr = strchr(ptr, '\n');
	++ptr;
	ptr = strchr(ptr, '\n');
	++ptr;
	ptr = strchr(ptr, '\n');
	ptr = skip_token(ptr);
	unsigned long used_mem = strtoul(ptr, &ptr, 10);
	return (float)used_mem / total_mem;
}
int main(void)
{
	while (1) {
		printf("%.2f\n", get_meminfo());
		sleep(1);
	}
	return 0;
}
