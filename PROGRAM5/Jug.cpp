#include "Jug.h"
#include <climits>
using namespace std;

Vertex::Vertex(int A, int B) {
    this->jugAqty = A;
    this->jugBqty = B;
    this->previous = std::numeric_limits<int>::max();;
    this->distance = std::numeric_limits<int>::max();;
    this->next = -1;
}

Vertex::Vertex() {
    
}

Edge::Edge(string string, int cost) {
    this->action = string;
    this->cost = cost;
}

Jug::Jug(int cA, int cB, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
    /*
    A problem is given by (Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA), where Ca 
    and Cb are the capacities of the jugs A and B, respectively, and N is the 
    goal. cfA is the cost to fill A, cfB is the cost to fill B, ceA, is the cost
    to empty A, ceB is the cost to empty B, cpAB is the cost to pour A to B and
    cpBA is the cost to pour B to A. A solution is a sequence of steps that 
    leaves jug A empty, and exactly N gallons in jug B. 
    */
    this->cA = cA;          // capacity of A
    this->cB = cB;          // capacity of B
    this->N = N;            // goal
    this->cfA = cfA;        // cost to fill A
    this->cfB = cfB;        // cost to fill B
    this->ceA = ceA;        // cost to empty A
    this->ceB = ceB;        // cost to empty B
    this->cpAB = cpAB;      // cost to pour A->B
    this->cpBA = cpBA;      // cost to pour B->A
    
    makeGraph();
    this->numVerticies = verticies.size();
}

Jug::~Jug() {
    
}

void Jug::makeGraph() {
    
    Vertex *newVertex;
    queue<Vertex> Queue;
    int currentjugA, currentjugB, existing, newA, newB;
    
    this->verticies.push_back(Vertex(0,0));         // Start where jug qty is (0,0)
                                                    // Then move on to where one jug or the other is filled.
    this->verticies.push_back(Vertex(cA,0));        // JugA is filled. Push it onto (0,0)'s neighbors.
    verticies.at(0).neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("Fill A",cfA)));
    
    this->verticies.push_back(Vertex(0,cB));        // JugB is filled. Push it onto (0,0)'s neighbors.
    verticies.at(0).neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("Fill B",cfB)));
    
    // Push the first two verticies onto the queue
    
    updateindicies();
    Queue.push(verticies.at(1));                    
    updateindicies();
    Queue.push(verticies.at(2));
    
    // Build the graph from there
    while(!Queue.empty()) {
        Vertex curr = Queue.front();
        Queue.pop();
        currentjugA = curr.jugAqty;
        currentjugB = curr.jugBqty;
        cout << "Assessing adjacent nodes to: (" << currentjugA << "," << currentjugB << ")..."<< endl;
        
        updateindicies();
        // ACTION: fillA
        newVertex = new Vertex(cA,currentjugB);
        existing = searchExisting(*newVertex);      // returns index of a matching node, else returns -1
        if (existing != -1) {
            cout << "fillA outcome (" << cA << "," << currentjugB << ") exists...";
            // if existing != -1, then there is a matching node which exists.
            // add verticies.at(existing) to curr's neighbors
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("fill A",cfA)));
            cout << "Added neighbor. " << curr.neighbors.size() << " total neighbors to this vertex..." << endl;
        } else {
            cout << "fillA outcome (" << cA << "," << currentjugB << ") doesn't exist...";
            // otherwise the node doesn't exist. create it.
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("fill A",cfA)));
            // and then push this onto the queue
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
        // ACTION: fillB
        newVertex = new Vertex(currentjugA,cB);
        existing = searchExisting(*newVertex);      // returns index of a matching node, else returns -1
        if (existing != -1) {
            cout << "fillB outcome (" << currentjugA << "," << cB << ") exists...";
            // if existing != -1, then there is a matching node which exists.
            // add verticies.at(existing) to curr's neighbors
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("fill B",cfB)));
            cout << "Added neighbor. " << curr.neighbors.size() << " total neighbors to this vertex..." << endl;
        } else {
            cout << "fillB outcome (" << currentjugA << "," << cB << ") doesn't exist...";
            // otherwise the node doesn't exist. create it.
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("fill B",cfB)));
            // and then push this onto the queue
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
        // ACTION: pourAB
        newA = currentjugA;
        newB = currentjugB;
        newB = newB + newA;
        if (newB > cB) {
            newA = newB - cB;
            newB = cB;
        } else {
            newA = 0;
        }
        newVertex = new Vertex(newA,newB);
        existing = searchExisting(*newVertex);      // returns index of a matching node, else returns -1
        if (existing != -1) {
            cout << "pourAB outcome (" << newA << "," << newB << ") exists...";
            // if existing != -1, then there is a matching node which exists.
            // add verticies.at(existing) to curr's neighbors
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("pour A B",cpAB)));
            
            cout << "Added neighbor. " << curr.neighbors.size() << " total neighbors to this vertex..." << endl;
        } else {
            cout << "pourAB outcome (" << newA << "," << newB << ") doesn't exist...";
            // otherwise the node doesn't exist. create it.
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("pour A B",cpAB)));
            // and then push this onto the queue
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
        // ACTION: pourBA
        newA = currentjugA;
        newB = currentjugB;
        newA = newB + newA;
        if (newA > cA) {
            newB = newA - cA;
            newA = cA;
        } else {
            newB = 0;
        }
        newVertex = new Vertex(newA,newB);
        existing = searchExisting(*newVertex);      // returns index of a matching node, else returns -1
        if (existing != -1) {
            cout << "pourBA outcome (" << newA << "," << newB << ") exists...";
            // if existing != -1, then there is a matching node which exists.
            // add verticies.at(existing) to curr's neighbors
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("pour B A",cpBA)));
            
            cout << "Added neighbor. " << curr.neighbors.size() << " total neighbors to this vertex..." << endl;
        } else {
            cout << "pourBA outcome (" << newA << "," << newB << ") doesn't exist...";
            // otherwise the node doesn't exist. create it.
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("pour B A",cpBA)));
            // and then push this onto the queue
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
        // ACTION: emptyA
        newVertex = new Vertex(0,currentjugB);
        existing = searchExisting(*newVertex);      // returns index of a matching node, else returns -1
        if (existing != -1) {
            cout << "emptyA outcome (" << "0" << "," << currentjugB << ") exists...";
            // if existing != -1, then there is a matching node which exists.
            // add verticies.at(existing) to curr's neighbors
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("empty A",ceA)));
            
            cout << "Added neighbor. " << curr.neighbors.size() << " total neighbors to this vertex..." << endl;
        } else {
            cout << "emptyA outcome (" << "0" << "," << currentjugB << ") doesn't exist...";
            // otherwise the node doesn't exist. create it.
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("empty A",ceA)));
            // and then push this onto the queue
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
        // ACTION: emptyB
        newVertex = new Vertex(currentjugA,0);
        existing = searchExisting(*newVertex);      // returns index of a matching node, else returns -1
        if (existing != -1) {
            cout << "emptyB outcome (" << currentjugA << "," << "0" << ") exists...";
            // if existing != -1, then there is a matching node which exists.
            // add verticies.at(existing) to curr's neighbors
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("empty B",ceB)));
            
            cout << "Added neighbor. " << curr.neighbors.size() << " total neighbors to this vertex..." << endl;
        } else {
            cout << "emptyB outcome (" << currentjugA << "," << "0" << ") doesn't exist...";
            // otherwise the node doesn't exist. create it.
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("empty B",ceB)));
            // and then push this onto the queue
            Queue.push(verticies.at(verticies.size()-1));
        }
        cout << endl;
        verticies.at(curr.index).neighbors = curr.neighbors;
    }
    cout << verticies.size() << " verticies generated." << endl;
}

void Jug::dijkstra(int source) {
    cout << "here" << endl;

    // verticies.at(source).distance = 0;
    // verticies.at(source).previous = -1; // to denote undefined
    
    queue<Vertex> Queue;
    Vertex curr;
    list< pair<int,Edge> >::iterator it;
    for (int i=0; i<numVerticies; i++) 
    {
        verticies.at(i).distance = INT_MAX;
        Queue.push(verticies.at(i));
    }
    verticies.at(source).distance = 0;
    verticies.at(source).previous = -1;
    while (!Queue.empty()) {
        // currentV = Pop unvisitedQueue
        curr = Queue.front();
        Queue.pop();
        for (it=curr.neighbors.begin(); it!=curr.neighbors.end(); ++it) {
            // edgeWeight = weight of edge from currentV to adjV
            int edgeWeight = it->second.cost;
            // alternativePathDistance = currentV->distance + edgeWeight
            int alternativePathDistance = curr.distance + edgeWeight;
            // if (alternativePathDistance < adjV->distance)
            if (alternativePathDistance < verticies.at(it->first).distance) {
            //         adjV->distance = alternativePathDistance
            //         adjV->predV = currentV
                verticies.at(it->first).distance = alternativePathDistance;
                verticies.at(it->first).previous = curr.index;
            }
            
            
            
            //           while (unvisitedQueue is not empty) {
            //   // Visit vertex with minimum distance from startV
            //   currentV = PopMin unvisitedQueue <------------------- popmin, can't use that
            // works with a regular queue
            //   for each vertex adjV adjacent to currentV {
            //      edgeWeight = weight of edge from currentV to adjV
            //      alternativePathDistance = currentV->distance + edgeWeight
                          
            //      // If shorter path from startV to adjV is found,
            //      // update adjV's distance and predecessor
            //      if (alternativePathDistance < adjV->distance) {
            //         adjV->distance = alternativePathDistance
            //         adjV->predV = currentV
            //      }
            //   }
                    
            
            
            //arent you supposed to compare current + edge weight to neighbor + edge weight?
            // int old_dist = verticies.at(it->first).distance;
            // int new_dist = curr.distance + it->second.cost;
            // cout << "Old dist: " << old_dist << " New dist: " << new_dist << "...";
            // if (old_dist > new_dist) {
            //     cout << "Updated distance for (" << curr.jugAqty << "," << curr.jugBqty << ") ...";
            //     cout << "Setting prev for index " << verticies.at(it->first).index << " to " << curr.index << endl;
            //     verticies.at(it->first).previous = curr.index;
            //     verticies.at(it->first).distance = new_dist;
            // }
        }
    }
}

int Jug::searchExisting(Vertex current) {
    for (unsigned i=0; i<verticies.size(); i++) {
        if ((verticies.at(i).jugAqty == current.jugAqty) && (verticies.at(i).jugBqty == current.jugBqty)) {
            return i;
        }
    }
    return -1;
}

void Jug::updateindicies() {
    for (unsigned i=0; i<verticies.size(); i++) {
        verticies.at(i).index = i;
    }
}

int Jug::solve(string &solution) {
    dijkstra(0);
    Vertex finalVertex(0,N);
    int index = searchExisting(finalVertex);        // the index of the goal vertex
    int nextIndex = verticies.at(index).previous;
    list< pair<int,Edge> >::iterator it;
    int errorbreak = 100;
    
    
    while (nextIndex != -1) {
        cout << "Current Index: " << index << " Next Index: " << nextIndex << endl;
        for (it=verticies.at(nextIndex).neighbors.begin(); it!=verticies.at(nextIndex).neighbors.end(); it++) {
            if (it->first == index) {
                cout << it->second.action << endl;
            }
        }
        index = nextIndex;
        nextIndex = verticies.at(index).previous;
        errorbreak--;
        if (errorbreak<0) {
            break;
        }
        
    }
    
    
    return 0;
}
