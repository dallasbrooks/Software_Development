import sys
import os

#get all words from file
def get_words(file_name):
	words = []
	with open(file_name, "r") as file:
		for line in file:
			line = line.replace(".,;()", " ").lower()
			words += line.split()
	return words

#print length ascending (part A)
def print_length_ascending(words):
	lengths = {len(word) for word in words}
	for length in lengths:
		length_words = [word for word in words if len(word) == length]
		frequency = len(length_words)
		print("Count[{0:0=2d}]={1:0=2d};".format(length, frequency))

#print freqeuncy descending (part B)
def print_frequency_descending(words):
	lengths = {len(word) for word in words}
	temp_frequency = 0
	for length in lengths:
		length_words = [word for word in words if len(word) == length]
		frequency = len(length_words)
		if(temp_frequency < frequency):
			temp_frequency = frequency
	for a in range(temp_frequency, 0, -1):
		for length in lengths:
			length_words = [word for word in words if len(word) == length]
			frequency = len(length_words)
			if(a == frequency):
				print("Count[{0:0=2d}]={1:0=2d};".format(length, frequency))

#print frequency descending with words (part C)
def print_frequency_descending_words(words):
	lengths = {len(word) for word in words}
	temp_frequency = 0
	for length in lengths:
		length_words = [word for word in words if len(word) == length]
		frequency = len(length_words)
		if(temp_frequency < frequency):
			temp_frequency = frequency
	for a in range(temp_frequency, 0, -1):
		for length in lengths:
			length_words = [word for word in words if len(word) == length]
			frequency = len(length_words)
			unique = list(set(length_words))
			unique.sort()
			if(a == frequency):
				sys.stdout.write("Count[{0:0=2d}]={1:0=2d}; (words: ".format(length, frequency))
				for a in range(len(unique)):
					sys.stdout.write("\"{0}\"".format(unique[a]))
					if(a+2 == len(unique)):
						sys.stdout.write(" and ")
					elif(a+1 != len(unique)):
						sys.stdout.write(", ")
				print(")")

#print length ascending with words (part C special case)
def print_length_ascending_words(words):
	lengths = {len(word) for word in words}
	for length in lengths:
		length_words = [word for word in words if len(word) == length]
		frequency = len(length_words)
		unique = list(set(length_words))
		unique.sort()
		sys.stdout.write("Count[{0:0=2d}]={1:0=2d}; (words: ".format(length, frequency))
		for a in range(len(unique)):
			sys.stdout.write("\"{0}\"".format(unique[a]))
			if(a+2 == len(unique)):
				sys.stdout.write(" and ")
			elif(a+1 != len(unique)):
				sys.stdout.write(", ")
		print(")")

def main():
	sort = 0
	print_words = 0
	sort_print_words = 0
	if(len(sys.argv) < 3):
		print("Failure: not enough inptus")
		return -1
	for a in range(len(sys.argv)):
		if(sys.argv[a] == "--infile"):
			file_name = sys.argv[a+1]
			if(not os.path.exists(file_name)):
				print("Failure: could not access file")
				return -1
		if(sys.argv[a] == "--sort"):
			sort = 1
		if(sys.argv[a] == "--print-words"):
			print_words = 1
		sort_print_words = sort + print_words
		if(sort_print_words == 2):
			sort = 0
			print_words = 0
	words = get_words(file_name)
	if(sort_print_words == 0):#part A
		print_length_ascending(words)
	if(sort == 1):#part B
		print_frequency_descending(words)
	if(sort_print_words == 2):#part C
		print_frequency_descending_words(words)
	if(print_words == 1):#part C special case
		print_length_ascending_words(words)
		
main()
#run with python3 word_count.py --infile <input_file> <--sort> <--print-words>