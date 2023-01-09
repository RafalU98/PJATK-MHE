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

        1ST ARGUMENT = Function (b -> BruteForce, r -> Random-Solution, hd -> Hill Climb Deterministic, hr -> Hill Climb Randomized,
        tabu -> Tabu method Or if you want all functions: all -> all algorithms

        2ND ARGUMENT = Iterations as an Integer
        3RD ARGUMENT = nonogram.json (Edit with your own Nonogram). 
        You can also choose a sample: nonogram*.json, where * is a number from 1 to 3
        
        4TH ARGUMENT = list of tabu size

        5TH ARGUMENT = 1 if you want to see the time, that the function needed. 0 if not
        6TH ARGUMENT = 1 if you want to see the convergence curve of the function. 0 if not
        7TH ARGUMENT = 1 if you want to see the solution of the function. 0 if not
        8TH ARGUMENT = 1 if you want to see the quality or mistakes of the result. 0 if not
        9TH ARGUMENT = 1 if you want to see the total iterations of the function. 0 if not
        10TH ARGUMENT = 1 if you want to see how many times the quality got better. 0 if not
        11TH ARGUMENT = 1 if you want to see the solution nonogram. . 0 if not

### Changelog
        03.10.22 - 09.10.22 |   Added Task 1 (learning how to use json.hpp)
        10.10.22 - 23.10.22 |   Added Task 2 (added classes to display nonogram)
        24.10.22 - 06.11.22 |   Added Task 3 (evaluation function + brute_force algoritm)
        07.11.22 - 20.11.22 |   Added Task 4 (random/hill_climb/hill_climb_deter algoritms were added)
        21.11.22 - 27.11.22 |   Added Task 5 (tabu algoritm)
        28.11.22 - 03.12.22 |   Added Task 6 (added structure for experiments + splitted program into different modules)
        04.12.22 - 10.12.22 |   Added Task 7 (simmulated algortim)
        11.12.22 - 08.01.23 |   Added Task 8 (genetic algoritm)
        

