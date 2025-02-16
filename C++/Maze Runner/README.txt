This program was written to help me with a maze challenge that I had to solve, which involved solving 1000 randomly generated mazes, one by one. 
The challenge was too tedious to do manually, so I decided to write a program to help me solve it.

The program parses through the file "maze.txt" that contains a 16 x 16 maze, for example:

 ##################
 #o              ##
 # # # # ##########
 # # # #         ##
 # ######### # # ##
 #         # # # ##
 # # ##### # ######
 # #   # # #     ##
 # # # # ##########
 # # #           ##
 # ##### # # ######
 #     # # #     ##
 # # ##### ##### ##
 # #     #     # ##
 # # # # # ########
 # # # # #      E##
 ##################
 ##################

 These mazes are randomly generated, but they all start and end at the same point and are 16 x 16, with variations inside of the 16 x 16 grid. 

 The program will read the file containing the maze, and spit out a string of capital letters that give the direction for the maze.
 (For example, LURR would be Left, Up, Right, Right).