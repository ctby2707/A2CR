This read file will explain the structure of the project Pac-Man AI.

# Structure of the project

 - [NeuralData](https://github.com/ctby2707/A2CR/tree/main/NeuralData "NeuralData") : contains all the weights and bias of the best Neural Networks generated previously 
- [Sources](https://github.com/ctby2707/A2CR/tree/main/Sources "Sources") : contains all the files of the project
- [site_web](https://github.com/ctby2707/A2CR/tree/main/site_web "site_web") : contains all the files of the website of the projet

# Files
 - [Makefile](https://github.com/ctby2707/A2CR/tree/main/Makefile "Makefile") : contains the instruction to compile the project, there are two commands : 
	 * make :   compile all the projet in an executable file named "Pac-Man"
	 * make clean : clean all the trash file in Sources directory and the executable.
 - [Sources/main.c](https://github.com/ctby2707/A2CR/tree/main/Sources/main.c "main.c") : contains the first function activated at the begining of the program
	 * `int main()`: execute the function `launchgtk()`
 - [Sources/NeuralNetwork.c](https://github.com/ctby2707/A2Cnb_neuronR/tree/main/Sources/NeuralNetwork.c "NeuralNetwork.c") : contains all function to create, execute and save **one** neural network.
	* `INTERVALL`: variable that contains the value of modification of bias and weights for the next generation.
	* `DIST`: distance  of detection of inputs (pac-gums, super pac-gums, ghosts)
	 * `char Call_Neural_Network(Game *game)`: get all the inputs (17) of pac-man according to the variable : execute `find_pac_gum()`, `find_ghost()` . After that the function `execute_network` and return the direction ('N', ' S', 'G', 'D')
	 * `struct Network init(int nb_layer, int *nb_neuron)`: create a neural network according to the number of layer nb_layer and the array nb_neuron which contains each number of neurons for each layer.
	 * `char execute_network(struct Network *network, double *inputs)`: execute each `output()` function of each neuron according to the input and take the neuron of the output layer with the upper value and return his direction. 
	 * `void randomizeNetwork(struct Network *network)`: randomize all the bias and weights of the neural network between -1 and 1.
	 * `void save_Network(struct Network *network, int child)` : save the bias and weights of the neural network number child in NeuralData directory. (call `savefile()`).
	 * `void load_Network(struct Network *network, int child)` : load the bias and weights of the neural network number child in NeuralData directory. (call `loadfile()`).
	 * `void adjust_Network(struct Network *network)`: modify the bias and weights of the neural network with `INTERVALL` variable defined before.
	* `void weight_set(double *weight, double x, size_t size_tab)`: randomize a list weight of size size_tab with x as upper and lower value.
- [Sources/NeuralNetworks_Detections.c](https://github.com/ctby2707/A2Cnb_neuronR/tree/main/Sources/NeuralNetworks_Detections.c "NeuralNetworks_Detections.c") : contains all the functions to get the inputs for the neural network :
	* `double find_pac_gum(int *map, int pos, int dir, int dist, int type)`:  make a Breadth-first search from the pac-man postion (pos) until distance dist. the type is the object researched (pac-gum or super pac-gum). It return the division of the number of object found by the number of tile traveled.
	* `double find_ghost(int *map, int pos, int dir, int dist, int b, int i, int c, int p)`: make a Breadth-first search from the pac-man postion (pos) until distance dist. The function search if the ghost are next to pac-man. t return the division of the number of ghosts found by the number of ghosts.
	* `queue *enqueue_child_pac_gum(queue *q, int s, int *map, int *Vect_P, int *Vect_D, int dist)`: function use by the previous functions that enqueue the child of a node s. It verify if the potential child are not walls or already traveled. It also updtae the vector of father and distance of the child.
- [Sources/NeuralNetworks_manager.c](https://github.com/ctby2707/A2CR/tree/main/Sources/NeuralNetworks_manager.c ) :  contains all the function to manage the system of generation of neural networks :
	* `void generate_random_generation(int nb_child, Game *game, int type)` generate a array of  `nb_child` neural networks in `game->AI` . It call `init )` to initialize each network then `randomizeNetwork()` to give random values. After that if the `type` is set to 1, the networks of NeuralData directory will be loaded (to continue the generation saved) .
	* `void new_generation(int nb_child, Game *game)`: call `save_generation()` and `generate_generation()`.
	* `void save_generation(int nb_child, Game *game)`: save the half of the generation contained in `game.AI`. It make an sort of the list `game.scoreAI` and it select the the AI with the best score.
	* `void generate_generation(int nb_child, Game *game)`: the function create a generation from the networks in directory NeuralData and call `adjust_Network()`.
	* swap and swap2 are function that are used in bubble sort.
	* `void bubbleSort(int arr[], int n, struct Network **net)`: a simple function put in increase order. 
