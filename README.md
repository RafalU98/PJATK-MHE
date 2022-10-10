# PJATK-MHE
Metaheuristics at PJATK-Gdańsk - Solving Nanogram with using diffrent algorithms

## Nanogram
Nanogram also known as Paint by numbers is a logical puzzle which consist of a grid in which cell are either colored or left blank according to the numbers at the side, the solution of such a puzzle reveals a pixel-art picture. The numbers of this puzzle are displayed in a form of discrete tomography which measures how many consistent lines are filled/colored squeres that are in a given row or column. 
        
### Example: Letter R  __________________________ Solution:
                        2 2 4 4                             2 2 4 4
                  0 9 9 2 3 2 2 1 0                   0 9 9 2 3 2 2 1 0
                0| | | | | | | | | |                0| | | | | | | | | |
                4| | | | | | | | | |                4| |X|X|X|X| | | | |
                6| | | | | | | | | |                6| |X|X|X|X|X|X| | |
              2 2| | | | | | | | | |              2 2| |X|X| | |X|X| | |
              2 2| | | | | | | | | |              2 2| |X|X| | |X|X| | |
                6| | | | | | | | | |                6| |X|X|X|X|X|X| | |
                4| | | | | | | | | |                4| |X|X|X|X| | | | |
              2 2| | | | | | | | | |              2 2| |X|X| |X|X| | | |
              2 2| | | | | | | | | |              2 2| |X|X| | |X|X| | |
              2 2| | | | | | | | | |              2 2| |X|X| | | |X|X| |
                0| | | | | | | | | |                0| | | | | | | | | |
                   
        
 
### ZADANIE 1
        Implement the data structures for the task.
 
        You need a task structure to be solved. In the case of a traveling salesman, 
        it will be a set of cities with distances between cities (or a measure of distance function).
 
        You need a solution structure. In the case of a traveling salesman, 
        this will be a list that sets the order of the cities to visit.

