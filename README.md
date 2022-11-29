# PJATK-MHE
Metaheuristics at PJATK-Gdańsk - Solving Nonogram with using diffrent algorithms

## Nonogram
Nonogram also known as Paint by numbers is a logical puzzle which consist of a grid in which cell are either colored or left blank according to the numbers at the side, the solution of such a puzzle reveals a pixel-art picture. The numbers of this puzzle are displayed in a form of discrete tomography which measures how many consistent lines are filled/colored squeres that are in a given row or column. 
        
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
                   
### TUTORIAL
        To start the Program enter following:

        1ST ARGUMENT = Function (b -> BruteForce, r -> Random-Solution, hd -> Hill Climb Deterministic, hr -> Hill Climb Randomized, tabu -> Tabu method
        Or if you want all functions: all -> all algorithms

        2ND ARGUMENT = Iterations as an Integer
        3RD ARGUMENT = nonogram.json (Edit with your own Nonogram). You can also choose a sample: nonogram*.json, where * is a number from 1 to 3
        4TH ARGUMENT = list of tabu size

        5TH ARGUMENT = 1 if you want to see the time, that the function needed. 0 if not
        6TH ARGUMENT = 1 if you want to see the convergence curve of the function. 0 if not
        7TH ARGUMENT = 1 if you want to see the solution of the function. 0 if not
        8TH ARGUMENT = 1 if you want to see the quality or mistakes of the result. 0 if not
        9TH ARGUMENT = 1 if you want to see the total iterations of the function. 0 if not
        10TH ARGUMENT = 1 if you want to see how many times the quality got better. 0 if not
        11TH ARGUMENT = 1 if you want to see the solution nonogram. . 0 if not
                   
                   
                   
        
### Task 1 - Lab 03/10/2022
         Small introdction before starting the "real project"
         
         NAME
    task1 - displaying the text in a frame according to the configuration in a JSON file
        SYNTAX
    job1 FILENAME
        DESCRIPTION
    The program loads the configuration from the FILENAME file in which it is described
    the size of the frame and the text to be placed inside. The frame will be text with dimensions w to h
    with text vertically and horizontally centered.
    
    The configuration file has the following format:
       {"w": WIDTH FRAMES, "h": FRAMES, "text": FRAME TEXT}
        EXAMPLE
    task1 config.json


### Task 2 - Lab 10/10/2022
        Implement the data structures for the task.
 
        You need a task structure to be solved. In the case of a traveling salesman, 
        it will be a set of cities with distances between cities (or a measure of distance function).
 
        You need a solution structure. In the case of a traveling salesman, 
        this will be a list that sets the order of the cities to visit.

