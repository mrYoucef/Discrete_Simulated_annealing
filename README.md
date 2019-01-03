# Discrete_Simulated_annealing
matlab script for Placement-Routing using Discrete_Simulated_annealing


Simulated annealing is a method for solving unconstrained and bound-constrained optimization problems. The method models the physical process of heating a material and then slowly lowering the temperature to decrease defects, thus minimizing the system energy.

At each iteration of the simulated annealing algorithm, a new point is randomly generated. The distance of the new point from the current point, or the extent of the search, is based on a probability distribution with a scale proportional to the temperature. The algorithm accepts all new points that lower the objective, but also, with a certain probability, points that raise the objective. By accepting points that raise the objective, the algorithm avoids being trapped in local minima, and is able to explore globally for more possible solutions. An annealing schedule is selected to systematically decrease the temperature as the algorithm proceeds. As the temperature decreases, the algorithm reduces the extent of its search to converge to a minimum.

Simulated annealing is a general technique that can be applied to both discrete problems and continuous problems. In this project we present an example of solving a discrete problem: the placement-routing problem, Overall, simulated annealing is more often used in discrete cases,

for example, the problem of the commercial traveler or the problem of
flow shop scheduling.

this definition is from mathworks.com

for more informations you can visite 
https://mathworks.com/help/gads/what-is-simulated-annealing.html


we chose to implement this algorihtem using matlab 

The problem is to find the optimal configuration of connection between different blocks, This is a difficult optimization problem requiring the use of heath to find an approximate solution. During a real application the calculation times are very
high given the large number of items to be processed.
In our case the blocks are arranged in a regular way on a square grid.

Function cost (we call it also energie) is calculated by summing the costs of each connection. The cost of a connection
is equal to the distance between the two blocks of this connection. For this problem,
the distance between two blocks is fixed at L=5. Thus, for a grid of size 5 × 5, the optimal value
is 200.

This problem lends itself well to a simulated annealing resolution. We perform a random initialization of the grid then we apply the algorithm seen previously. 
The only The elementary mouvment available is the permutation of the positions of 2 blocks .
The blocks to be swapped are selected randommily at each simulated annealing step.
This problem is also called Placement-Routing (Place and Route).

in this project we transformed this algorithem to a function on matlab called Simulated_annealing(C,XData,YData,L,N,tho);
all the scripts are well explained in the comments


final result after lunching main script for testing ;


