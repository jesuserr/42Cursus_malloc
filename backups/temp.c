FUNNCIONA


// Designed to work with TINY and SMALL heaps only. Searches for a free block
// in the linked list of blocks and if found populates its metadata and returns
// its address. If no free block is found, it creates a new heap (linked to 
// previous one) of 'N' PREALLOC_BLOCKS and returns the address of the first
// block of the new set (marked as allocated).
void	*search_free_block(int heap_type, int block_size, size_t mem_req)
{
	t_block	*block;
	size_t	allocated_blocks;

	block = (t_block *)g_heaps[heap_type];
	allocated_blocks = 0;
	while (block->size & 0x1)
	{
		if (block->next->size % PREALLOC_BLOCKS == 0 && block->next->next == END_OF_HEAP_PTR)
			return (add_tiny_or_small_heap(heap_type, block_size, mem_req, block));
		if (block->next->size % PREALLOC_BLOCKS == 0)
		{
			block = block->next->next;
			allocated_blocks++;
		}
		block = block->next + 1;
		allocated_blocks++;
	}
	block->size = mem_req | 1;
	block->next = (t_block *)((unsigned char *)block + sizeof(t_block) \
		+ block_size);
	block->next->size = ++allocated_blocks;
	block->next->next = block->next + 1;
	if (allocated_blocks % PREALLOC_BLOCKS == 0)
		block->next->next = END_OF_HEAP_PTR;
	return (++block);
}