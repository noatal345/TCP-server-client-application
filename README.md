# TCP server-client application 
This is a TCP server-client application written in C++ for Linux. The program allows multiple clients to connect to the server using the server's port number. Each client is handled by a unique thread on the server side and by two unique threads on the client side, one for sending messages and one for receiving messages. 

### Server Functionality
Each thread on the server side creates a Command Line Interface (CLI) instance, which is responsible for executing commands for the client user. The server provides a menu display with the following options:
1. Upload classified and unclassified CSV files
2. Get or change the KNN algorithm settings- the distance metric name and k value where k is an integer and a valid distance function name is one of the following: AUC (for [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance)), MAN (for [Manhattan distance](https://en.wikipedia.org/wiki/Taxicab_geometry)), CHB (for [Chebyshev distance](https://en.wikipedia.org/wiki/Chebyshev_distance)), CAN (for [Canberra distance](https://en.wikipedia.org/wiki/Canberra_distance)) or MIN (for [Minkowski distance](https://en.wikipedia.org/wiki/Minkowski_distance)). The default values are k=5 and distance metric = EUC.
3. Classify the unclassified data file using the [KNN algorithms](https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm) according to the classified data (assuming option 1 was completed before option 3).
4. Display the results of the classification (assuming option 3 was completed before).
5. Download the result to a path in the user's computer specified by the user, including the name of the file to be created (assuming option 3 was completed before). This action happens in a different thread.
8. Exit the program. This option will close the server's connection but keep the server running.
 
If the user enters invalid input the program will print "Invalid input" to the screen and return to the menu.  

## **How to Install and Run (UNIX users):**
1. Download files
2. Open the terminal
3. Install a c++ compiler (If you don't have one installed)
4. run `make`  


### compile and run the example:  
Compile and run the server:  
for server run `./server.out [Port number]`  

<img width="119" alt="213941242-e6e6a74c-82cc-4468-ac0b-4db45a32b14f" src="https://github.com/noatal345/TCP-server-client-application/assets/72741540/e5885da8-0792-4938-bb8b-383a4e4d772c">


Run the Client:  
for client run `./client.out [IP number] [Port number]` 

<img src="https://user-images.githubusercontent.com/72741540/213940985-849bc4f1-a73a-4e75-982a-4d29cf71b489.png" width="500" height="500">  
<img width="175" alt="213941016-71b4c603-ef4c-4292-9303-1c68e92c9abf" src="https://github.com/noatal345/TCP-server-client-application/assets/72741540/5f4689f8-ed2b-4162-8871-3bfe548f9498">


