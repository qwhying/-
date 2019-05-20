#include <stdio.h>
#include<list>
//using namespace std;

#define MEM_SIZE 32

#define RAM_SIZE  16
#define SWAP_SIZE 32

struct page_item { // 页表项
	int ram_addr;
	int swap_addr;
	unsigned access;
	bool present;
	bool modified;
};

static char ram[RAM_SIZE];
static char swap[SWAP_SIZE];
static struct page_item page_table[MEM_SIZE];
std::list<int> pages;

// 换页算法
static int algo_swap(int &a)
{
	//int min_access = -1;
	//std::stack<struct page_item> temppages;
	int min_access_page = -1;

	int temp = pages.front();
	pages.pop_front();
	pages.push_back(a);
	min_access_page = temp;
	/*for(int i=0;i<MEM_SIZE;i++)
	{
		if(page_table[i].present&&page_table[i].ram_addr==temp.ram_addr)
		{
			min_access_page=i;
			break;
		}
	}*/
	//for (int i = 0; i < MEM_SIZE; i++) {
	//	if (page_table[i].present &&
	//			(min_access == -1 || page_table[i].access < min_access)) {
	//		min_access = page_table[i].access;
	//		min_access_page = i;
	//	}
	//}

	return min_access_page;
}

// 逻辑地址laddr转换为物理地址paddr
static int mem_access(int laddr)
{
	if (page_table[laddr].present) {
		pages.remove(laddr);
		pages.push_back(laddr);
		page_table[laddr].access++;
		return page_table[laddr].ram_addr;
	}

	// 缺页处理

	// 根据特定算法选择被换出的页
	int page = algo_swap(laddr);

	// 换出
	if (page_table[page].modified) { // 写回
		int data = ram[page_table[page].ram_addr];
		swap[page_table[page].swap_addr] = data;
	}
	page_table[page].present = false;

	// 替换
	int paddr = page_table[page].ram_addr;
	page_table[laddr].ram_addr = paddr;

	ram[paddr] = swap[page_table[laddr].swap_addr];

	page_table[laddr].modified = false;
	page_table[laddr].present = true;
	page_table[laddr].access = 1;

	return paddr;
}

int mem_read(int addr, char *buf)
{
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	*buf = ram[paddr];

	return 0;
}

int mem_write(int addr, char buf)
{
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	ram[paddr] = buf;
	page_table[addr].modified = true;

	return 0;
}

void mem_init(void)
{
	// 全部加载到交换空间
	for (int i = 0; i < MEM_SIZE; i++) {
		page_table[i].swap_addr = i;
		page_table[i].present = false;
		page_table[i].modified = false;
	}
	// 部分加载到内存
	for (int i = 0; i < RAM_SIZE; i++) {
		page_table[i].ram_addr = i;
		page_table[i].present = true;
		page_table[i].access = 0;
		pages.push_back(i);
	}
}

void mem_state(void)
{
	printf("ram state:\t");
	for (int i = 0; i < RAM_SIZE; i++) {
		printf("%02x ", ram[i]);//输出两位十六进制
	}
	printf("\nswap state:\t");
	for (int i = 0; i < SWAP_SIZE; i++) {
		printf("%02x ", swap[i]);
	}
	printf("\n\n");
}

void mem_test(void)
{
	char temp;
	mem_state();
	for (int i = RAM_SIZE; i < MEM_SIZE; i++)
	{
		mem_write(i,'a'+i-RAM_SIZE);
	}
	mem_state();
	mem_read(RAM_SIZE, &temp);
	mem_read(2, &temp);
	mem_state();
	mem_write(19, 2);
	mem_write(23, 50);
	mem_state();
	mem_read(17, &temp);
	mem_state();

}

int main(int argc, const char *argv[])
{
	mem_init();

	mem_test();

	return 0;
}
