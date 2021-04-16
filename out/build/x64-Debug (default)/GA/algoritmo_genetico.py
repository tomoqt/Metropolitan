import numpy as np
from scipy.spatial import distance
import networkx as nx
import math 
from geneticalgorithm import geneticalgorithm as ga

#proviamo prima una fully connected
n = int(input("Enter the number of raws: "))
m = int(input("Enter the number of columns: "))
k=n*m
RailCost=10

#la mappa è un lattice i cui nodi rappresentano le POSSIBILI stazioni 
MapMatrix= np.zeros(shape=( n, m))

MaxPeople=1000

#costruzione matrice spostamenti
TravelPeople=np.random.randint(MaxPeople,size=(n*m))
TravelMatrix=np.zeros(shape=(n*m,n*m,))
TravelMatrix = np.random.rand(n*m, n*m)
for i in range(k):
    for j in range(k):
        if(i==j):
            TravelMatrix[i,j]=0

#normalizzazione
for i in range(k):
    somma=TravelMatrix[i].sum()
    for j in range(k):
        TravelMatrix[i,j]=TravelMatrix[i,j]/somma

print("Population built")

#distanza euclidea
def EuclDist(raws, columns):
	indexes = [[r,c] for c in range(columns) for r in range(raws)]
	return distance.cdist(indexes, indexes, 'euclidean')

#calcolo le distanze, tutte insieme
distances = EuclDist(n, m)

#convertitore vettore-matrice
def trasf(righe, colonne, vettore):
	dim=righe*colonne
	matrice= np.zeros(shape=(dim,dim))
	j=0
	for i in range(dim):
		if((not(i))+((i+1)%colonne)):
			matrice[i,i+1]=vettore[j]
			matrice[i+1,i]=vettore[j]
			j=j+1	
		if (i+colonne<dim):
			matrice[i,i+colonne]=vettore[j]
			matrice[i+colonne,i]=vettore[j]		 
			j=j+1
	return matrice

MaxBinari=int(input("Enter the limit number of railways: "))

def CleanRewardFunctionSmooth(StateVector):
    Reward=0
    CountBinari=0
    StateMatrix=trasf(n, m, StateVector)
    
    for i in range(len(StateVector)):
        if (StateVector[i] == 1):
            CountBinari+=1
    
    #modifico le velocità di percorrenza
    StateMatrix[StateMatrix == 0] = 1000
    np.fill_diagonal(StateMatrix, 0)
    
    #applico la metrica alla state matrix
    StateMatrix = distances*StateMatrix
    
    StateGraph=nx.DiGraph(StateMatrix)
    
    for i in range(k):
        for j in range((k)):
            if(i!=j):
                Reward+=(TravelPeople[i]*TravelMatrix[i,j])/(nx.algorithms.shortest_paths.weighted.dijkstra_path_length(StateGraph,i,j))
    Reward -= RailCost* CountBinari
    return -Reward
    
def RewardFunction1(StateVector):
    Reward=0
    CountBinari=0
    StateMatrix=trasf(n, m, StateVector)
    
    for i in range(len(StateVector)):
        if (StateVector[i] == 1):
            CountBinari+=1
    
    #modifico le velocità di percorrenza
    StateMatrix[StateMatrix == 0] = 1000
    np.fill_diagonal(StateMatrix, 0)
    
    #applico la metrica alla state matrix
    StateMatrix = distances*StateMatrix
    
    StateGraph=nx.DiGraph(StateMatrix)
    
    for i in range(k):
        for j in range((k)):
            if(i!=j):
                Reward+=(TravelPeople[i]*TravelMatrix[i,j])/(nx.algorithms.shortest_paths.weighted.dijkstra_path_length(StateGraph,i,j))
    Reward -= RailCost* CountBinari
    if(CountBinari>MaxBinari):
        Reward-=50000*(CountBinari-MaxBinari)
    return -Reward



algorithm_param = {'max_num_iteration': 750,\
                   'population_size':100,\
                   'mutation_probability':0.3,\
                   'elit_ratio': 0.05,\
                   'crossover_probability': 0.5,\
                   'parents_portion': 0.2,\
                   'crossover_type':'uniform',\
                   'max_iteration_without_improv':700}
model=ga(function=RewardFunction1,dimension=(2*n*m-n-m),variable_type='bool', algorithm_parameters=algorithm_param)
print("Beginning of genetic algorithm")
model.run()
array = model.output_dict["variable"]
print(array)

countFinale=0
for i in range(len(array)):
        if (array[i] == 1):
            countFinale+=1

out = trasf(n, m, array)


File=open("outputMatrice.txt","w")
File.write(str(n))
File.write(' ')
File.write(str(m))
File.write(' ')
for i in TravelPeople:
    File.write(str(i))
    File.write(' ')
for i in range(k):
    for j in range(k):
        File.write(str(TravelMatrix[i,j]))
        File.write(' ')
for i in range(k):
    for j in range(k):
         File.write(str(out[i,j]))
         File.write(' ')
File.close()


OutGraph=nx.DiGraph(out)
nx.draw(OutGraph)
print(out)
print("count: ",countFinale)
print("Result: ", CleanRewardFunctionSmooth(array))