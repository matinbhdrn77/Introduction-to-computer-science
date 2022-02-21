from sys import argv, exit
import csv

def main():
    
    if len(argv) != 3:
        csv.exit('usage: python dna.py file1 file2')
    
    with open(argv[2]) as file:
        reader = csv.reader(file)
        for row in reader:
            DNA = row[0]
            break
        
    sequences = {}
    
    with open(argv[1]) as file:
        reader = csv.reader(file)
        
        for row in reader:
            for column in row[1::]:
                sequences[column] = 1
            break        
    
    for dna in sequences:
        length = len(dna)
        tmp = 0
        maxi = 0
        for i in DNA:
            if DNA[i:i+length] == str(dna:
                i = i + length
                while DNA[i:i+length] == DNA[i-length:i]:
                    tmp += 1
                    i = i + length
                    
            if tmp > maxi:
                maxi = tmp
                tmp = 0
        sequences[dna] += maxi
        
    print(sequences)

main()
        

    
