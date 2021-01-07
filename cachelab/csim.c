#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int valid;
	int tag;
	int lru;
} Line;
//每一行有一个block
typedef struct {
	Line * lines;
} Set;

typedef struct {
	int s;
	int E;
	int b;
	Set * sets;
} Cache;
//struct

void updateLru(Cache * cache, int set, int index);
void printHelpMenu();
void release(Cache * cache);
void checkRight(char *curOptarg);
void initCache(int s, int E, int b, Cache *cache);
bool miss(Cache *cache, int set, int tag);
void loadcache(Cache * cache, long unsigned int addr, int size ,int set, int tag , int vFlag);
//function

int hits, misses, evictions, max;

int main(int argc, char **argv) {
	char filename[100];
	hits = misses = evictions = 0;
	int s = 0, b = 0, E = 0;
	int vFlag = 0;
	const char * option = "hvs:E:b:t:";
	char op;
	Cache cache;
	while((op = getopt(argc, argv, option)) != -1) {
		switch(op) {
			case 'h':
				//checkRight(optarg);
				printHelpMenu();
				exit(0);
			case 'v': {
				vFlag = 1;
				break;
			}
			//checkRight(optarg);
			case 's':
				checkRight(optarg);
				s = atol(optarg);
				break;
			case 'E':
				checkRight(optarg);
				E = atol(optarg);
				break;
			case 'b':
				checkRight(optarg);
				b = atol(optarg);
				break;
			case 't':
				checkRight(optarg);
				strcpy(filename, optarg);
				break;

			default:
				printf("The input is wrong\n");
				exit(1);
		}
	}
	if(s == 0 || E == 0 || b == 0) {
		printf("please attach the right parameter.\n");
		exit(1);
	}
	//参数读入, 并记录这种读取方式。atol 是为了处理数据。
	initCache(s, E, b, &cache);
	max = (1 << s) * E * b;
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		perror("Failed to find the file.\n");
		exit(1);
	}

	long unsigned int addr;
	char opt[10];
	int size;
	memset(opt, 0, sizeof(char) * 10);
	while(fscanf(fp, "%s %lx,%d", opt, &addr, &size) != EOF) { //used to be char, but failed
		int set = ((addr >> b) & ((1 << s) - 1));
		int tag = (addr>>(s + b)); 
		//printf("\n%d %d", set, tag);
		if(strcmp(opt, "I") == 0) 
			continue;
		if(vFlag == 1)
			printf("\n%s %lx,%d", opt, addr, size);

		if(strcmp(opt, "S") == 0 || strcmp(opt, "L") == 0)
			loadcache(&cache, addr, size, set, tag, vFlag);
		else if(strcmp(opt, "M") == 0) {
			loadcache(&cache, addr, size, set, tag, vFlag);
			loadcache(&cache, addr, size, set, tag, vFlag);
		}
	}
	printf("\n");
	printSummary(hits, misses, evictions);
	release(&cache);
	fclose(fp);
	return 0;
}

void updateLru(Cache * cache, int set, int index) {
	int i;
	cache->sets[set].lines[index].lru = max;
	for(i = 0; i < cache->E; i++)
		if(i != index)
			cache->sets[set].lines[i].lru--;

}

bool miss(Cache *cache, int set, int tag) {
	int i;
	for(i = 0; i < cache->E ; i++) {
		if(cache->sets[set].lines[i].valid == 1)
			//find the cache
			if(cache->sets[set].lines[i].tag == tag) {
				//modify lru in cache
				updateLru(cache, set, i);
				return false;
			}
	}
	return true;//miss in the cache
}

void loadcache(Cache * cache, long unsigned int addr, int size, int set, int tag , int vFlag) {
	int i, flag = 1, minIndex = 0, j;
	int minLru = max;
	max = minLru;
	if(miss(cache, set, tag)) {
		misses++;
		if(vFlag == 1)
			printf("  miss");
		for(i = 0; i < cache->E; i++) {
			if(cache->sets[set].lines[i].valid == 0) {
				flag = 0; //not full in this set
				break;
			}
		}
		if(flag == 0) {
			cache->sets[set].lines[i].valid = 1;
			cache->sets[set].lines[i].tag = tag;
			updateLru(cache, set, i);
		} else { //this set is full, need to change lines
			for(j = 0; j < cache->E; j++) {
				if(cache->sets[set].lines[j].lru < minLru) {
					minIndex = j;
					minLru = cache->sets[set].lines[j].lru;
				}
			}
			cache->sets[set].lines[minIndex].valid = 1;
			cache->sets[set].lines[minIndex].tag = tag;
			updateLru(cache, set, minIndex);

			evictions++;
			if(vFlag == 1)
				printf("  eviction");
		}
	} else {
		hits++;
		if(vFlag == 1)
			printf("  hit");
	}
}


void release(Cache * cache) {
	int s = cache->s;
	int i;
	for(i = 0; i < s; i++) {
		free(cache->sets[i].lines);
	}
	free(cache->sets);

}

void initCache(int s, int E, int b, Cache * cache) {
	if(s < 0) {
		printf("Wrong number.\n");
		exit(1);
	}
	cache->s = 1 << s;
	cache->E = E;
	cache->b = b;
	cache->sets = (Set * )malloc(cache->s * sizeof(Set));
	if(!cache->sets) {
		printf("Set Memory error\n");
		exit(1);
	}
	int i, j;
	for(i = 0; i < cache->s; i++) {
		cache->sets[i].lines = (Line *)malloc(E * sizeof(Line));
		if(!cache->s) {
			printf("Line Memory error\n");
			exit(1);
		}
		for(j = 0; j < E; j++) {
			cache->sets[i].lines[j].valid = 0;
			cache->sets[i].lines[j].lru = 0;
		}
	}

}

void checkRight(char *curOptarg) {
	if(curOptarg[0]=='-') {
		printf("./csim :Missing required command line argument\n");
		printHelpMenu();
		exit(0);
	}
}

void printHelpMenu() {
	printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
	printf("Options:\n");
	printf("	-h         Print this help message.\n");
	printf("	-v         Optional verbose flag.\n");
	printf("	-s <num>   Number of set index bits.\n");
	printf("	-E <num>   Number of lines per set.\n");
	printf("	-b <num>   Number of block offset bits.\n");
	printf("	-t <file>  Trace file.\n\n");
	printf("Examples:\n");
	printf("	linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
	printf("	linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}









