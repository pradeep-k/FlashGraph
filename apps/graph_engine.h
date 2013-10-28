#ifndef __GRAPH_ENGINE_H__
#define __GRAPH_ENGINE_H__

#include "thread.h"
#include "container.h"
#include "concurrency.h"

#include "vertex.h"

class graph_engine;

class compute_vertex: public in_mem_vertex_info
{
	atomic_flags<long> activated_levels;
public:
	compute_vertex(vertex_id_t id, off_t off, int size): in_mem_vertex_info(
			id, off, size) {
	}

	/**
	 * This is an atomic operation. We can only activate a vertex in a level
	 * higher than the level where it was activated. i.e., the level of
	 * a vertex can only increase monotonically.
	 * Return true if the vertex is activated in the level successfully.
	 */
	bool activate_in(int level) {
		// This implementation is fast, but it's kind of tricky.
		// We can have only 64 levels at most. Maybe it's enough for
		// most graph algorithms and graphs.
		assert(level < activated_levels.get_num_tot_flags());
		return !activated_levels.set_flag(level);
	}

	bool is_activated(int level) const {
		return activated_levels.test_flag(level);
	}

	virtual void run(graph_engine &graph, ext_mem_vertex &vertex,
			std::vector<vertex_id_t> &activated_vertices) = 0;
};

class graph_index
{
public:
	virtual compute_vertex &get_vertex(vertex_id_t id) = 0;

	virtual vertex_id_t get_max_vertex_id() const = 0;

	virtual vertex_id_t get_min_vertex_id() const = 0;
};

class graph_engine
{
	graph_index *vertices;

	// These are two global queues. One contains the vertices that are being
	// processed in the current level. The other contains the vertices that
	// will be processed in the next level.
	// The queue for the current level.
	thread_safe_FIFO_queue<vertex_id_t> *queue;
	// The queue for the next level.
	thread_safe_FIFO_queue<vertex_id_t> *next_queue;
	atomic_integer level;
	volatile bool is_complete;

	// These are used for switching queues.
	pthread_mutex_t lock;
	pthread_barrier_t barrier1;
	pthread_barrier_t barrier2;

	thread *first_thread;
	std::vector<thread *> worker_threads;

protected:
	graph_engine(int num_threads, int num_nodes, const std::string &graph_file,
			graph_index *index);
public:
	static graph_engine *create(int num_threads, int num_nodes,
			const std::string &graph_file, graph_index *index) {
		return new graph_engine(num_threads, num_nodes, graph_file, index);
	}

	compute_vertex &get_vertex(vertex_id_t id) {
		return vertices->get_vertex(id);
	}

	void start(vertex_id_t id);

	/**
	 * The algorithm progresses to the next level.
	 * It returns true if no more work can progress.
	 */
	bool progress_next_level();

	/**
	 * Activate vertices that may be processed in the next level.
	 */
	void activate_next_vertices(vertex_id_t vertices[], int num);

	/**
	 * Get vertices to be processed in the current level.
	 */
	int get_curr_activated_vertices(vertex_id_t vertices[], int num) {
		return queue->fetch(vertices, num);
	}

	vertex_id_t get_max_vertex_id() const {
		return vertices->get_max_vertex_id();
	}

	vertex_id_t get_min_vertex_id() const {
		return vertices->get_min_vertex_id();
	}

	void wait4complete();

	int get_num_threads() const {
		return worker_threads.size();
	}
};

#endif