project (FlashGraph)

add_library(graph-algs STATIC
	diameter_graph.cpp
	directed_triangle_graph.cpp
	fast_triangle_graph.cpp
	graph_transitivity.cpp
	k_core.cpp
	local_scan_graph.cpp
	overlap.cpp
	page_rank.cpp
	scan_graph.cpp
	scc.cpp
	sstsg.cpp
	topK_scan_graph.cpp
	undirected_triangle_graph.cpp
	wcc.cpp
)
