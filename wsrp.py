import matplotlib.pyplot as plt
import networkx as nx
from queue import deque

def mount_graph():
    """
    theGraph = nx.DiGraph()
    theGraph.add_node('a1', time=1)
    theGraph.add_node('b1', time=1)
    theGraph.add_node('b2', time=1)
    theGraph.add_node('c1', time=1)
    theGraph.add_edge('a1','b1')
    theGraph.add_edge('a1','b2')
    theGraph.add_edge('b1','c1')
    
    theGraph.add_node(7, time=1)
    theGraph.add_node(5, time=1)
    theGraph.add_node(6, time=1)
    theGraph.add_edge(5,6)
    theGraph.add_edge(5,7)
    """
    theGraph = nx.DiGraph()
    theGraph.add_node('5', time=1)
    theGraph.add_node('7', time=1)
    theGraph.add_node('3', time=1)
    theGraph.add_node('11', time=1)
    theGraph.add_node('8', time=1)
    theGraph.add_node('2', time=1)
    theGraph.add_node('9', time=1)
    theGraph.add_node('10', time=1)
    
    theGraph.add_edge('5','11')
    theGraph.add_edge('11','2')
    theGraph.add_edge('7','11')
    theGraph.add_edge('7','8')
    theGraph.add_edge('3','8')
    theGraph.add_edge('11','9')
    theGraph.add_edge('11','10')
    theGraph.add_edge('3','10')

    return theGraph

def plot_graph(theGraph):
    nx.draw(theGraph)
    plt.subplot(121)
    nx.draw(theGraph, with_labels=True, font_weight='bold')
    plt.subplot(122)
    plt.show()

def topological_sort(theGraph):
    
    topSort = []
    q = deque() 

    for vertex in theGraph.in_degree:
        if vertex[1] == 0:
            q.appendleft(vertex[0])
    
    while q:
        vertex = q.pop()
        topSort.append(vertex)
        for adj in theGraph.adj[vertex]:
            if adj not in q:
                q.appendleft(adj)
    
    print(topSort)    
    return topSort

if __name__ == '__main__':
    theGraph = mount_graph()
    plot_graph(theGraph)
    topological_sort(theGraph)