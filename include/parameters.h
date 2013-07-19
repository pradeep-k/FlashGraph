#ifndef __MY_PARAMETERS_H__
#define __MY_PARAMETERS_H__

#define USE_GCLOCK
#define PER_CPU

#define PAGE_SIZE 4096
#define LOG_PAGE_SIZE 12

#define MIN_BLOCK_SIZE 512

const int AIO_DEPTH_PER_FILE = 32;

const int IO_QUEUE_SIZE = 32 * 5;
const int MAX_FETCH_REQS = 10;
const int MAX_DISK_CACHED_REQS = 8;

/**
 * The number of requests issued by user applications
 * in one access.
 */
const int NUM_REQS_BY_USER = 1000;

/**
 * The initial size of the queue for pending IO requests
 * in the global cache.
 */
const int INIT_GCACHE_PENDING_SIZE = NUM_REQS_BY_USER * 100;

/**
 * The min size of IO vector allocated for an IO request..
 */
const int MIN_NUM_ALLOC_IOVECS = 16;
const int NUM_EMBEDDED_IOVECS = 1;

/**
 * The maximal size of IO vector issued by the global cache.
 * The experiment shows AIO with 16 pages in a request can achieve
 * the best performance.
 */
const int MAX_NUM_IOVECS = 16;

const int CELL_SIZE = 16;
const int CELL_MIN_NUM_PAGES = 8;

const int MAX_NUM_DIRTY_CELLS_IN_QUEUE = 1000;
const int DIRTY_PAGES_THRESHOLD = CELL_SIZE / 2;
const int NUM_WRITEBACK_DIRTY_PAGES = 2;

const long MAX_CACHE_SIZE = ((long) 4096) * 1024 * 1024 * 2;

const int NUMA_REQ_CACHE_SIZE = 600;
const int NUMA_REQ_QUEUE_SIZE = 2000;
const int NUMA_REQ_BUF_SIZE = 600;
const int NUMA_REPLY_CACHE_SIZE = 50;
const int NUMA_REPLY_QUEUE_SIZE = 1024;
const int NUMA_REPLY_BUF_SIZE = 200;
const int NUMA_NUM_PROCESS_THREADS = 8;

const int CONST_A = 27644437;
const long CONST_P = 68718952447L;

const int FILE_CONST_A = 31;
const int FILE_CONST_P = 191;

const int LOCAL_BUF_SIZE = 100;

#endif